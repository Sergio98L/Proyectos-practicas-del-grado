//==============================================================
// Copyright © 2020 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================

// on your development system.
#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/numeric>
#include <oneapi/dpl/execution>
#include <oneapi/dpl/iterator>

#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>
#include <iomanip>  // setprecision library
#include <iostream>
#include <numeric> 

// dpc_common.hpp can be found in the dev-utilities include folder.
// e.g., $ONEAPI_ROOT/dev-utilities/<version>/include/dpc_common.hpp
#include "dpc_common.hpp"

using namespace sycl;
constexpr int master = 0;

// cpu_seq is a simple sequential CPU routine
// that calculates all the slices and then
// does a reduction.
float calc_pi_cpu_seq(int num_steps) {
  float step = 1.0 / (float)num_steps;
  float x;
  float sum = 0.0;
  for (int i = 1; i < num_steps; i++) {
    x = (i - 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x);
  }
  return sum / (float)num_steps;
}

// cpu_tbb is a simple parallel_reduce tbb routine
// that calculates all the slices and then
// uses tbb reduce to combine results.
float calc_pi_cpu_tbb(int num_steps) {
  float step = 1.0 / (float)num_steps;

  auto tbbtotal =
      tbb::parallel_reduce(tbb::blocked_range<int>(1, num_steps), 0.0,
                           [=](tbb::blocked_range<int> r, float running_total) {
                             float y;
                             for (int i = r.begin(); i != r.end(); i++) {
                               y = (i - 0.5) * step;
                               running_total += 4.0 / (1.0 + y * y);
                             }
                             return running_total;
                           },
                           std::plus<float>());
  return tbbtotal / (float)num_steps;
}

// onedpl_native uses a parallel_for to fill
// a buffer with all the slice calculations and
// then uses a single_task to combine all the results
// This is not the highest performing example but shows
// how to do calculations directly in dpc++ with
// mininmal complexity.
template <typename Policy>
float calc_pi_onedpl_native(size_t num_steps, Policy&& policy) {

  float data[num_steps];

  // Create buffer using host allocated "data" array
  buffer<float, 1> buf{data, range<1>{num_steps}};

  policy.queue().submit([&](handler& h) {
    accessor writeresult(buf,h,write_only);
    h.parallel_for(range<1>{num_steps}, [=](id<1> idx) {
      float x = ((float)idx[0] - 0.5) / (float)num_steps;
      writeresult[idx[0]] = 4.0f / (1.0 + x * x);
    });
  });
  policy.queue().wait();

  // Single task is needed here to make sure
  // data is not written over.
  policy.queue().submit([&](handler& h) {
    accessor a(buf,h);
    h.single_task([=]() {
      for (int i = 1; i < num_steps; i++) a[0] += a[i];
    });
  });
  policy.queue().wait();


  // float mynewresult = buf.get_access<access::mode::read>()[0] / (float)num_steps;
  host_accessor answer(buf,read_only) ; 
  float mynewresult = answer[0]/(float)num_steps; 
  
  return mynewresult;
}

// This option uses a parallel for to fill the buffer and then
// uses a tranform_init with plus/no_op and then
// a local reduction then global reduction.
template <typename Policy>
float calc_pi_oneapi_reduction(size_t num_steps, Policy&& policy) {

  float data[num_steps];
  float reduct[1];

  // Create buffer using host allocated "data" array
  buffer<float, 1> buf{data, range<1>{num_steps}};
  buffer<float, 1> sum_buf{reduct, range<1>{1}};

  // fill the buffer with the calculation using parallel for
  policy.queue().submit([&](auto &h) {
      sycl::accessor buf_acc(buf, h, sycl::read_write);
      sycl::accessor sum_acc(sum_buf, h, sycl::write_only, sycl::no_init);

      h.parallel_for(num_steps, [=](auto index) {
        size_t glob_id = index[0];
        float x = ((float)glob_id - 0.5) / (float)num_steps;
        buf_acc[glob_id] = 4.0f / (1.0 + x * x);

	dpct::atomic_fetch_add(&sum_acc[0], buf_acc[glob_id]);
      });
  });
  policy.queue().wait();

  host_accessor answer(sum_buf,read_only) ; 
  return answer[0]/(float)num_steps;
}


int main(int argc, char** argv) {
  int num_steps = 1000000;
  int groups = 10000;
  int name_len=0;
  int id=0;
  int num_procs=0;
  float pi=0.0;
  queue myQueue{property::queue::in_order()};
  auto policy = oneapi::dpl::execution::make_device_policy(
      queue(gpu_selector{}, dpc_common::exception_handler));


  std::cout << ", uses device: "
            << myQueue.get_device().get_info<info::device::name>() << "\n";

  if (id == master) {
    printf("Number of steps is %d\n", num_steps);

    pi = calc_pi_onedpl_native(num_steps, policy);

    pi = calc_pi_oneapi_reduction(num_steps, policy);

    dpc_common::TimeInterval T;
    pi = calc_pi_cpu_seq(num_steps);
    auto stop = T.Elapsed();
    std::cout << "Cpu Seq calc: \t\t";
    std::cout << std::setprecision(3) << "PI =" << pi;
    std::cout << " in " << stop << " seconds\n";

    dpc_common::TimeInterval T2;
    pi = calc_pi_cpu_tbb(num_steps);
    auto stop2 = T2.Elapsed();
    std::cout << "Cpu TBB  calc: \t\t";
    std::cout << std::setprecision(3) << "PI =" << pi;
    std::cout << " in " << stop2 << " seconds\n";

    dpc_common::TimeInterval T3;
    pi = calc_pi_onedpl_native(num_steps, policy);
    auto stop3 = T3.Elapsed();
    std::cout << "oneDPL native:\t\t";
    std::cout << std::setprecision(3) << "PI =" << pi;
    std::cout << " in " << stop3 << " seconds\n";

    dpc_common::TimeInterval T4;
    pi = calc_pi_oneapi_reduction(num_steps, policy);
    auto stop4 = T4.Elapsed();
    std::cout << "oneDPL atomic:\t\t";
    std::cout << std::setprecision(3) << "PI =" << pi;
    std::cout << " in " << stop4 << " seconds\n";
  }


  return 0;
}
