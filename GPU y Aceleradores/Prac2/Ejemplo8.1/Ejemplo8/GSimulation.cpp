  /*
    This file is part of the example codes which have been used
    for the "Code Optmization Workshop".
    
    Copyright (C) 2016  Fabio Baruffa <fbaru-dev@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "GSimulation.hpp"
#include "cpu_time.hpp"
#include <CL/sycl.hpp>

#include <dpct/dpct.hpp>
#include "dpc_common.hpp"


using  namespace  cl::sycl;

GSimulation :: GSimulation()
{
  std::cout << "===============================" << std::endl;
  std::cout << " Initialize Gravity Simulation" << std::endl;
  set_npart(16000); 
  set_nsteps(10);
  set_tstep(0.1); 
  set_sfreq(1);
}

void GSimulation :: set_number_of_particles(int N)  
{
  set_npart(N);
}

void GSimulation :: set_number_of_steps(int N)  
{
  set_nsteps(N);
}

void GSimulation :: init_pos()  
{
  std::random_device rd;	//random number generator
  std::mt19937 gen(42);      
  std::uniform_real_distribution<real_type> unif_d(0,1.0);
  
  for(int i=0; i<get_npart(); ++i)
  {
    particles->pos_x[i] = unif_d(gen);
    particles->pos_y[i] = unif_d(gen);
    particles->pos_z[i] = unif_d(gen);
  }
}

void GSimulation :: init_vel()  
{
  std::random_device rd;        //random number generator
  std::mt19937 gen(42);
  std::uniform_real_distribution<real_type> unif_d(-1.0,1.0);

  for(int i=0; i<get_npart(); ++i)
  {
    particles->vel_x[i] = unif_d(gen) * 1.0e-3f;
    particles->vel_y[i] = unif_d(gen) * 1.0e-3f;
    particles->vel_z[i] = unif_d(gen) * 1.0e-3f; 
  }
}

void GSimulation :: init_acc() 
{
  for(int i=0; i<get_npart(); ++i)
  {
    particles->acc_x[i] = 0.f; 
    particles->acc_y[i] = 0.f;
    particles->acc_z[i] = 0.f;
  }
}

void GSimulation :: init_mass() 
{
  real_type n   = static_cast<real_type> (get_npart());
  std::random_device rd;        //random number generator
  std::mt19937 gen(42);
  std::uniform_real_distribution<real_type> unif_d(0.0,1.0);

  for(int i=0; i<get_npart(); ++i)
  {
    particles->mass[i] = n * unif_d(gen); 
  }
}

// GPU VERSION
void GSimulation :: get_acceleration(int n,sycl::queue Q, ParticleSoA *particles_d) {

    const float softeningSquared = 1e-3f;
    const float G = 6.67259e-11f;

    Q.submit([&](handler &h) {

      h.parallel_for(range<1>(n), [=](id<1> id) {
        auto i = id[0];

            real_type x,y,z = 0;

            for (int j = 0; j < n; j++) {

                real_type dx, dy, dz;
                real_type distanceSqr = 0.0f;
                real_type distanceInv = 0.0f;
            
                dx = particles_d->pos_x[j] - particles_d->pos_x[i];	//1flop
                dy = particles_d->pos_y[j] - particles_d->pos_y[i];	//1flop	
                dz = particles_d->pos_z[j] - particles_d->pos_z[i];	//1flop
                
                distanceSqr = dx*dx + dy*dy + dz*dz + softeningSquared;	//6flops
                distanceInv = 1.0f / sqrtf(distanceSqr);			//1div+1sqrt

                x += dx * G * particles_d->mass[j] * distanceInv * distanceInv * distanceInv; //6flops
                y += dy * G * particles_d->mass[j] * distanceInv * distanceInv * distanceInv; //6flops
                z += dz * G * particles_d->mass[j] * distanceInv * distanceInv * distanceInv; //6flops
            }
            particles_d->acc_x[i] = x;
            particles_d->acc_y[i] = y;
            particles_d->acc_z[i] = z;

        });     
    }).wait();
}

// GPU VERSION
real_type GSimulation :: updateParticles(int n, real_type dt, sycl::queue Q, ParticleSoA *particles_d) {

    real_type energy = 0;
    real_type resultados[n];

    buffer<real_type, 1> buf{resultados, range<1>{static_cast<unsigned long>(n)}};

    Q.submit([&](handler &h) {

      sycl::accessor sum_acc(buf, h, sycl::write_only, sycl::noinit);

      h.parallel_for(range<1>(n), [=](id<1> id) {
        auto i = id[0];
      
        particles_d->vel_x[i] += particles_d->acc_x[i] * dt; 
        particles_d->vel_y[i] += particles_d->acc_y[i] * dt; 
        particles_d->vel_z[i] += particles_d->acc_z[i] * dt; 
        
        particles_d->pos_x[i] += particles_d->vel_x[i] * dt; 
        particles_d->pos_y[i] += particles_d->vel_y[i] * dt; 
        particles_d->pos_z[i] += particles_d->vel_z[i] * dt;
        
        particles_d->acc_x[i] = 0.;
        particles_d->acc_y[i] = 0.;
        particles_d->acc_z[i] = 0.;

        sum_acc[i] = particles_d->mass[i] * ( particles_d->vel_x[i]*particles_d->vel_x[i] 
                                              +  particles_d->vel_y[i]*particles_d->vel_y[i]
                                              +  particles_d->vel_z[i]*particles_d->vel_z[i] );;

        // energy += particles_d->mass[i] * ( particles_d->vel_x[i]*particles_d->vel_x[i] 
        //                                 +  particles_d->vel_y[i]*particles_d->vel_y[i]
        //                                 +  particles_d->vel_z[i]*particles_d->vel_z[i] ); 

      });
    }).wait(); 

    Q.submit([&](handler &h) {

      sycl::accessor a(buf, h);

      h.single_task([=](){
        for (int i = 1; i < n; i++) a[0] += a[i];
      });
    }).wait();

    host_accessor result(buf,read_only) ; 
    return result[0];
}

void GSimulation :: start()  {
  
  real_type energy;
  real_type dt = get_tstep();
  int n = get_npart();
  
  //allocate particles
  particles = new ParticleSoA;
  
  particles->pos_x = new real_type[n];
  particles->pos_y = new real_type[n];
  particles->pos_z = new real_type[n];
  particles->vel_x = new real_type[n];
  particles->vel_y = new real_type[n];
  particles->vel_z = new real_type[n];
  particles->acc_x = new real_type[n];
  particles->acc_y = new real_type[n];
  particles->acc_z = new real_type[n];
  particles->mass  = new real_type[n]; 


  init_pos();	
  init_vel();
  init_acc();
  init_mass();
  
  print_header();
  
  _totTime = 0.; 
  
  
  CPUTime time;
  double ts0 = 0;
  double ts1 = 0;
  double nd = double(n);
  double gflops = 1e-9 * ( (11. + 18. ) * nd*nd  +  nd * 19. );
  double av=0.0, dev=0.0;
  int nf = 0;
  

  // Allocate particles device

  sycl::queue Q;

  ParticleSoA *particles_d = static_cast<ParticleSoA *> (malloc_device (sizeof(ParticleSoA),Q));;
  
  particles_d->pos_x = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));
  particles_d->pos_y = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));
  particles_d->pos_z = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));

  particles_d->vel_x = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));
  particles_d->vel_y = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));
  particles_d->vel_z = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));

  particles_d->acc_x = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));
  particles_d->acc_y = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));
  particles_d->acc_z = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q));

  particles_d->mass  = static_cast<real_type *> (malloc_device (n*sizeof(real_type),Q)); 

  Q.memcpy(particles_d->acc_x, particles->acc_x, n*sizeof(real_type));
  Q.memcpy(particles_d->acc_y, particles->acc_y, n*sizeof(real_type));    
  Q.memcpy(particles_d->acc_z, particles->acc_z, n*sizeof(real_type));

  Q.memcpy(particles_d->vel_x, particles->vel_x, n*sizeof(real_type));
  Q.memcpy(particles_d->vel_y, particles->vel_y, n*sizeof(real_type));    
  Q.memcpy(particles_d->vel_z, particles->vel_z, n*sizeof(real_type));    

  Q.memcpy(particles_d->pos_x, particles->pos_x, n*sizeof(real_type));
  Q.memcpy(particles_d->pos_y, particles->pos_y, n*sizeof(real_type));    
  Q.memcpy(particles_d->pos_z, particles->pos_z, n*sizeof(real_type));

  Q.memcpy(particles_d->mass, particles->mass, n*sizeof(real_type));

  // ---------------------------------------------------------------------

  const double t0 = time.start();
  for (int s=1; s<=get_nsteps(); ++s) {   
   
    ts0 += time.start(); 
    get_acceleration(n,Q,particles_d);

    energy = updateParticles(n, dt,Q,particles_d);
    _kenergy = 0.5 * energy; 
    
    ts1 += time.stop();

    if(!(s%get_sfreq())) {

      nf += 1;      
      std::cout << " " 
      <<  std::left << std::setw(8)  << s
      <<  std::left << std::setprecision(5) << std::setw(8)  << s*get_tstep()
      <<  std::left << std::setprecision(5) << std::setw(12) << _kenergy
      <<  std::left << std::setprecision(5) << std::setw(12) << (ts1 - ts0)
      <<  std::left << std::setprecision(5) << std::setw(12) << gflops*get_sfreq()/(ts1 - ts0)
      <<  std::endl;

      if(nf > 2) {
        av  += gflops*get_sfreq()/(ts1 - ts0);
        dev += gflops*get_sfreq()*gflops*get_sfreq()/((ts1-ts0)*(ts1-ts0));
      }
      
      ts0 = 0;
      ts1 = 0;
    }
  
  } //end of the time step loop
  
    // Copiar datos de vuelta en Host
    Q.memcpy(particles->acc_x,particles_d->acc_x, n*sizeof(real_type));
    Q.memcpy(particles->acc_y,particles_d->acc_y, n*sizeof(real_type));    
    Q.memcpy(particles->acc_z,particles_d->acc_z, n*sizeof(real_type));

    Q.memcpy(particles->vel_x,particles_d->vel_x, n*sizeof(real_type));
    Q.memcpy(particles->vel_y,particles_d->vel_y, n*sizeof(real_type));    
    Q.memcpy(particles->vel_z,particles_d->vel_z, n*sizeof(real_type));    

    Q.memcpy(particles->pos_x,particles_d->pos_x, n*sizeof(real_type));
    Q.memcpy(particles->pos_y,particles_d->pos_y, n*sizeof(real_type));    
    Q.memcpy(particles->pos_z,particles_d->pos_z, n*sizeof(real_type)); 

    Q.memcpy(particles->mass,particles_d->mass, n*sizeof(real_type));     

    free(particles_d->acc_x,Q);
    free(particles_d->acc_y,Q);
    free(particles_d->acc_z,Q);

    free(particles_d->vel_x,Q);
    free(particles_d->vel_y,Q);
    free(particles_d->vel_z,Q);

    free(particles_d->pos_x,Q);
    free(particles_d->pos_y,Q);
    free(particles_d->pos_z,Q);

    free(particles_d->mass,Q);

  // ---------------------------------------------------------------------

  const double t1 = time.stop();
  _totTime  = (t1-t0);
  _totFlops = gflops*get_nsteps();
  
  av/=(double)(nf-2);
  dev=sqrt(dev/(double)(nf-2)-av*av);
  

  std::cout << std::endl;
  std::cout << "# Total Time (s)      : " << _totTime << std::endl;
  std::cout << "# Average Performance : " << av << " +- " <<  dev << std::endl;
  std::cout << "===============================" << std::endl;

}


void GSimulation :: print_header()
{
	    
  std::cout << " nPart = " << get_npart()  << "; " 
	    << "nSteps = " << get_nsteps() << "; " 
	    << "dt = "     << get_tstep()  << std::endl;
	    
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << " " 
	    <<  std::left << std::setw(8)  << "s"
	    <<  std::left << std::setw(8)  << "dt"
	    <<  std::left << std::setw(12) << "kenergy"
	    <<  std::left << std::setw(12) << "time (s)"
	    <<  std::left << std::setw(12) << "GFlops"
	    <<  std::endl;
  std::cout << "------------------------------------------------" << std::endl;


}

GSimulation :: ~GSimulation()
{
  delete [] particles->pos_x;
  delete [] particles->pos_y;
  delete [] particles->pos_z;
  delete [] particles->vel_x;
  delete [] particles->vel_y;
  delete [] particles->vel_z;
  delete [] particles->acc_x;
  delete [] particles->acc_y;
  delete [] particles->acc_z;
  delete [] particles->mass;
  delete particles;
}
