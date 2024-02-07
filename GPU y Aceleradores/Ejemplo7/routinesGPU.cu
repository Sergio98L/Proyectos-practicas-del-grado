#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#include "routinesGPU.h"
#include "routinesCPU.h"

// Thread block size
#define BLOCK_SIZE 16 

// Globals
const float PI = 3.141593;
const float level = 1000.0f;

// Forward declarations of functions
__global__ void noise_reduction(uint8_t*, float*, int, int);
__global__ void img_gradient(float*,float*, float*,float*, float*, int, int);
__global__ void no_max_supression(uint8_t *,uint8_t * ,float* , float* , int ,int , float, float);
__global__ void houghtransform(uint8_t *, int , int ,float ,float , float , uint32_t *, int , int , float *, float *);

void getlines(int , uint32_t *, int , int , int , int , float *, float *,int *, int *, int *, int *, int *);

void line_asist_GPU(uint8_t *im, int height, int width, float *sin_table, float *cos_table, uint32_t *accum, int *x1, int *x2, int *y1, int *y2, int *nlines) {

	//Noise Reduction
	float* NR_d;
	uint8_t* img_in_d;
	int sizeNR = height * width * sizeof(float);
	int sizeIMG = sizeof(uint8_t) * width * height;

	cudaMalloc((void**)&NR_d, sizeNR);
	cudaMalloc((void**)&img_in_d, sizeIMG);
	cudaMemcpy(img_in_d, im, size, cudaMemcpyHostToDevice);

	dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid(width / dimBlock.x, height / dimBlock.y);

	noise_reduction<<<dimGrid,dimBlock>>>(img_in_d,NR_d,height,width);

	//Img Gradient
	float* Gx_d,*Gy_d,*G_d,*phi_d;
	int sizeXY = height * width * sizeof(float);

	cudaMalloc((void**)&Gx_d, sizeXY);	
	cudaMalloc((void**)&Gy_d, sizeXY);
	cudaMalloc((void**)&G_d, sizeXY);							
	cudaMalloc((void**)&phi_d, sizeXY);	

	img_gradient<<<dimGrid,dimBlock>>>(NR_d,Gx_d,Gy_d,G_d,phi_d,height,width);

	//No max Supresion
	uint8_t* imgEdge_d, *pedge_d;
	int sizePE = sizeof(uint8_t) * width * height;
	cudaMalloc((void**)&imgEdge_d, sizePE);
	cudaMalloc((void**)&pedge_d, sizePE);

	float lowthres = level/2;
	float hithres  = 2*(level);

	no_max_supression<<<dimGrid,dimBlock>>>(pedge_d,imgEdge_d,G_d,phi_d,height,width,lowthres,hithres);

	//Hough Transform
	float* sin_table_d, * cos_table_d;
	int sizeTABLE = 180 * sizeof(float);
	cudaMalloc((void**)&sin_table_d, sizeTABLE);
	cudaMalloc((void**)&cos_table_d, sizeTABLE);
	cudaMemcpy(sin_table_d, sin_table, sizeTABLE, cudaMemcpyHostToDevice);
	cudaMemcpy(cos_table_d, cos_table, sizeTABLE, cudaMemcpyHostToDevice);

	float hough_h = ((sqrt(2.0) * (float)(height>width?height:width)) / 2.0);
	float center_x = width/2.0; 
	float center_y = height/2.0;
	int accu_height = hough_h * 2.0;
	int accu_width  = 180;

	uint32_t *accum_d;
	int sizeACCUM = accu_width*accu_height * sizeof(uint32_t);																
	cudaMalloc((void**)&accum_d, sizeACCUM);
	cudaMemset(&accum_d, 0, sizeACCUM);

	houghtransform<<<dimGrid,dimBlock>>>(imgEdge_d,width, height,hough_h, center_x,center_y,accum_d,accu_width,accu_height,sin_table_d,cos_table_d);

	int threshold = height/6;
	if (width>height) threshold = width/6;
	cudaMemcpy(accum, accum_d, size, cudaMemcpyDeviceToHost);

	//Get Lines
	getlines(threshold, accum, accu_width, accu_height, width, height, sin_table, cos_table, x1, y1, x2, y2, nlines);

	// Free device memory
	cudaFree(NR_d);
	cudaFree(img_in_d);
	cudaFree(Gx_d);
	cudaFree(Gy_d);
	cudaFree(G_d);
	cudaFree(phi_d);
	cudaFree(imgEdge_d);
	cudaFree(pedge_d);
	cudaFree(accum_d);
	cudaFree(cos_table_d);
	cudaFree(sin_table_d);
}

__global__ void noise_reduction(uint8_t* im,float* NR, int height, int width) {

	int i = blockIdx.y * blockDim.y + threadIdx.y + 2;						
	int j = blockIdx.x * blockDim.x + threadIdx.x + 2;						

	if(i < height-2 && j < width-2) {
			NR[i*width+j] =
				 (2.0*im[(i-2)*width+(j-2)] +  4.0*im[(i-2)*width+(j-1)] +  5.0*im[(i-2)*width+(j)] +  4.0*im[(i-2)*width+(j+1)] + 2.0*im[(i-2)*width+(j+2)]
				+ 4.0*im[(i-1)*width+(j-2)] +  9.0*im[(i-1)*width+(j-1)] + 12.0*im[(i-1)*width+(j)] +  9.0*im[(i-1)*width+(j+1)] + 4.0*im[(i-1)*width+(j+2)]
				+ 5.0*im[(i  )*width+(j-2)] + 12.0*im[(i  )*width+(j-1)] + 15.0*im[(i  )*width+(j)] + 12.0*im[(i  )*width+(j+1)] + 5.0*im[(i  )*width+(j+2)]
				+ 4.0*im[(i+1)*width+(j-2)] +  9.0*im[(i+1)*width+(j-1)] + 12.0*im[(i+1)*width+(j)] +  9.0*im[(i+1)*width+(j+1)] + 4.0*im[(i+1)*width+(j+2)]
				+ 2.0*im[(i+2)*width+(j-2)] +  4.0*im[(i+2)*width+(j-1)] +  5.0*im[(i+2)*width+(j)] +  4.0*im[(i+2)*width+(j+1)] + 2.0*im[(i+2)*width+(j+2)])
				/159.0;

	}
}

__global__ void img_gradient(float* NR,float* Gx, float* Gy,float* G, float* phi, int height, int width) {

	int i = blockIdx.y * blockDim.y + threadIdx.y + 2;						
	int j = blockIdx.x * blockDim.x + threadIdx.x + 2;						

	if(i < height-2 && j < width-2) {
		Gx[i*width+j] = 
				(1.0*NR[(i-2)*width+(j-2)] +  2.0*NR[(i-2)*width+(j-1)] +  (-2.0)*NR[(i-2)*width+(j+1)] + (-1.0)*NR[(i-2)*width+(j+2)]
			+ 4.0*NR[(i-1)*width+(j-2)] +  8.0*NR[(i-1)*width+(j-1)] +  (-8.0)*NR[(i-1)*width+(j+1)] + (-4.0)*NR[(i-1)*width+(j+2)]
			+ 6.0*NR[(i  )*width+(j-2)] + 12.0*NR[(i  )*width+(j-1)] + (-12.0)*NR[(i  )*width+(j+1)] + (-6.0)*NR[(i  )*width+(j+2)]
			+ 4.0*NR[(i+1)*width+(j-2)] +  8.0*NR[(i+1)*width+(j-1)] +  (-8.0)*NR[(i+1)*width+(j+1)] + (-4.0)*NR[(i+1)*width+(j+2)]
			+ 1.0*NR[(i+2)*width+(j-2)] +  2.0*NR[(i+2)*width+(j-1)] +  (-2.0)*NR[(i+2)*width+(j+1)] + (-1.0)*NR[(i+2)*width+(j+2)]);


		Gy[i*width+j] = 
				((-1.0)*NR[(i-2)*width+(j-2)] + (-4.0)*NR[(i-2)*width+(j-1)] +  (-6.0)*NR[(i-2)*width+(j)] + (-4.0)*NR[(i-2)*width+(j+1)] + (-1.0)*NR[(i-2)*width+(j+2)]
			+ (-2.0)*NR[(i-1)*width+(j-2)] + (-8.0)*NR[(i-1)*width+(j-1)] + (-12.0)*NR[(i-1)*width+(j)] + (-8.0)*NR[(i-1)*width+(j+1)] + (-2.0)*NR[(i-1)*width+(j+2)]
			+    2.0*NR[(i+1)*width+(j-2)] +    8.0*NR[(i+1)*width+(j-1)] +    12.0*NR[(i+1)*width+(j)] +    8.0*NR[(i+1)*width+(j+1)] +    2.0*NR[(i+1)*width+(j+2)]
			+    1.0*NR[(i+2)*width+(j-2)] +    4.0*NR[(i+2)*width+(j-1)] +     6.0*NR[(i+2)*width+(j)] +    4.0*NR[(i+2)*width+(j+1)] +    1.0*NR[(i+2)*width+(j+2)]);


		// CALCULO DE G Y DE PHI	(G = √Gx²+Gy²)
		G[i*width+j] = sqrtf((Gx[i*width+j]*Gx[i*width+j])+(Gy[i*width+j]*Gy[i*width+j]));				
		phi[i*width+j] = atan2f(fabs(Gy[i*width+j]),fabs(Gx[i*width+j]));

		if(fabs(phi[i*width+j])<=PI/8 ){
			phi[i*width+j] = 0;
		}
		else if (fabs(phi[i*width+j])<= 3*(PI/8)){
			phi[i*width+j] = 45;
		}
		else if (fabs(phi[i*width+j]) <= 5*(PI/8)){
			phi[i*width+j] = 90;
		}
		else if (fabs(phi[i*width+j]) <= 7*(PI/8)){
			phi[i*width+j] = 135;
		}
		else{
			phi[i*width+j] = 0;
		}
	}
}

__global__ void no_max_supression(uint8_t *pedge,uint8_t *img_out ,float* G, float* phi, int height,int width, float lowthres, float hithres ) {

	int i = blockIdx.y * blockDim.y + threadIdx.y + 3;						
	int j = blockIdx.x * blockDim.x + threadIdx.x + 3;						

	if(i < height-3 && j < width-3) {

		pedge[i*width+j] = 0;
		if(phi[i*width+j] == 0){
			if(G[i*width+j]>G[i*width+j+1] && G[i*width+j]>G[i*width+j-1]){
				pedge[i*width+j] = 1;
			} 
		} 
		else if(phi[i*width+j] == 45) {
			if(G[i*width+j]>G[(i+1)*width+j+1] && G[i*width+j]>G[(i-1)*width+j-1]){
				pedge[i*width+j] = 1;
			}
		} 
		else if(phi[i*width+j] == 90) {
			if(G[i*width+j]>G[(i+1)*width+j] && G[i*width+j]>G[(i-1)*width+j]){
				pedge[i*width+j] = 1;
			}
		} 
		else if(phi[i*width+j] == 135) {
			if(G[i*width+j]>G[(i+1)*width+j-1] && G[i*width+j]>G[(i-1)*width+j+1]){
				pedge[i*width+j] = 1;
			}		
		}
	}

	int ii,jj;

	if(i < height-3 && j < width-3) {
		img_out[i*width+j] = 0;
		if(G[i*width+j]>hithres && pedge[i*width+j]){
			img_out[i*width+j] = 255;
		}
		else if(pedge[i*width+j] && G[i*width+j]>=lowthres && G[i*width+j]<hithres){
			for (ii=-1;ii<=1; ii++){
				for (jj=-1;jj<=1; jj++){
					if (G[(i+ii)*width+j+jj]>hithres){
						img_out[i*width+j] = 255;
					}
				} 
			} 
		}				
	}
}

__global__ void houghtransform(uint8_t *im, int width, int height,float hough_h,float center_x, float center_y, uint32_t *accumulators, int accu_width, int accu_height,  float *sin_table, float *cos_table) {

	int i = blockIdx.y * blockDim.y + threadIdx.y;						
	int j = blockIdx.x * blockDim.x + threadIdx.x;

	if(i < height && j < width){
		if(im[ (i*width) + j] > 250){						
			for(int theta=0;theta<180;theta++){  
				float rho = ( ((float)j - center_x) * cos_table[theta]) + (((float)i - center_y) * sin_table[theta]);
				atomicAdd(&accumulators[ (int)((round(rho + hough_h) * 180.0)) + theta], 1);
			} 
		} 
	}
}

void getlines(int threshold, uint32_t *accumulators, int accu_width, int accu_height, int width, int height, float *sin_table, float *cos_table, int *x1, int *y1, int *x2, int *y2, int *lines)
{
	int rho, theta;
	uint32_t max;

	for(rho=0;rho<accu_height;rho++){
		for(theta=0;theta<accu_width;theta++){  
			if(accumulators[(rho*accu_width) + theta] >= threshold){  
				
				max = accumulators[(rho*accu_width) + theta]; 
				for(int ii=-4;ii<=4;ii++){  
					for(int jj=-4;jj<=4;jj++){  
						if( (ii+rho>=0 && ii+rho<accu_height) && (jj+theta>=0 && jj+theta<accu_width) ){  
							if( accumulators[((rho+ii)*accu_width) + (theta+jj)] > max ){
								max = accumulators[((rho+ii)*accu_width) + (theta+jj)];
							}  
						}  
					}  
				}  

				if(max == accumulators[(rho*accu_width) + theta]){
					int x1_aux, y1_aux, x2_aux, y2_aux;  
					x1_aux = y1_aux = x2_aux = y2_aux = 0;  

					if(theta >= 45 && theta <= 135){
						if (theta > 90){
							x1_aux = width/2;  
							y1_aux = ((float)(rho-(accu_height/2)) - ((x1_aux - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2);
							x2_aux = width;  
							y2_aux = ((float)(rho-(accu_height/2)) - ((x2_aux - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2);  
						} 
						else{  
							x1_aux = 0;  
							y1_aux = ((float)(rho-(accu_height/2)) - ((x1_aux - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2);
							x2_aux = width*2/5;  
							y2_aux = ((float)(rho-(accu_height/2)) - ((x2_aux - (width/2) ) * cos_table[theta])) / sin_table[theta] + (height / 2); 
						}
					} 
					else{  
						y1_aux = 0;  
						x1_aux = ((float)(rho-(accu_height/2)) - ((y1_aux - (height/2) ) * sin_table[theta])) / cos_table[theta] + (width / 2);  
						y2_aux = height;  
						x2_aux = ((float)(rho-(accu_height/2)) - ((y2_aux - (height/2) ) * sin_table[theta])) / cos_table[theta] + (width / 2);  
					}

					x1[*lines] = x1_aux;
					y1[*lines] = y1_aux;
					x2[*lines] = x2_aux;
					y2[*lines] = y2_aux;
					(*lines)++;
				}
			}
		}
	}
}