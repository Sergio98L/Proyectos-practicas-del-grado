#include <CL/sycl.hpp>

using  namespace  cl::sycl;

#define MAX_WINDOW_SIZE 5*5

void buble_sort2(float*, int );

void remove_noise_SYCL(sycl::queue Q, float *im, float *image_out, float thredshold, int window_size, int height, int width){

	int ws2 = (window_size - 1)>>1;
	
	Q.submit([&](handler &h){
		h.parallel_for(range<2>(height, width), [=](id<2> item){
			auto i = item[0]-ws2;
			auto j = item[1]-ws2;
			int ii,jj;
			float window[MAX_WINDOW_SIZE];

			for(ii = -ws2; ii <= ws2; ii++){
				for(jj = -ws2; jj <= ws2; jj++){
					window[(ii+ws2)*window_size + jj+ws2] = im[(i+ii)*width + j+jj];
				}
			}

			buble_sort2(window, window_size*window_size);
        	median = window[(window_size*window_size-1)>>1];

            if (fabsf((median-im[i*width+j])/median) <=thredshold)
		        image_out[i*width + j] = im[i*width+j];
            else
                image_out[i*width + j] = median;
		});
	}).wait();
}

void buble_sort2(float *array, int size)
{
	int i, j;
	float tmp;

	for (i=1; i<size; i++)
		for (j=0 ; j<size - i; j++)
			if (array[j] > array[j+1]){
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
}
