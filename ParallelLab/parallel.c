//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Yu-Wei Vincent Yeh
 * UCLA ID : 005123289
 * Email : vincentywyeh@gmail.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;

#pragma omp parallel for lastprivate (ton , moving_average) reduction(+:dot_product)
  for(i=0; i<DIM-1;i++)
    {
      super[i] += simple[i];
      dot_product += super[i]*simple[i];
    
      moving_average = 0;
      for(ton=i;ton<DIM-1-WINDOW_SIZE;ton++)
	{
	  moving_average += simple[ton];
	}
    }

  int a_secret = 5;
  fibonacci[0] = 1;
  fibonacci[1] = 1;
  #pragma omp single nowait
  for(i=2; i<DIM-1;i++)
  {
    fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
    if(i==3)
    {
      printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
    }
  }

  step = 1.0 / NUM_STEPS;
#pragma omp parallel for private(x) reduction(+:sum)
  for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 
  
  double tempr = r*r;

#pragma omp parallel for private(x , y) reduction(+:nCirc)
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= tempr) {
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

  long tempagg = 0.0;
  long tempnew = 0;
  int tempnumber;
  int temp0 = 0;
  int temp1 = 0;
  int temp2 = 0;
  int temp3 = 0;
  int temp4 = 0;
  int temp5 = 0;
  int temp6 = 0;
  int temp7 = 0;
  int temp8 = 0;
  int temp9 = 0;
   int dimsq = DIM*DIM;
#pragma omp parallel for collapse(3) private (tempnew , compute_it , u , v , w , tempnumber) reduction(+: tempagg , temp9 , temp8, temp7, temp6 , temp5, temp4 , temp3 , temp2, temp1 , temp0) 
  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        tempnumber = i*dimsq+j*DIM+k;
	compute_it = old[tempnumber] * we_need_the_func();
        tempagg += compute_it / gimmie_the_func();
        new[tempnumber]=0;
	tempnew+=old[tempnumber-dimsq-DIM-1];
        tempnew+=old[tempnumber-dimsq-DIM];
        tempnew+=old[tempnumber-dimsq-DIM+1];
        tempnew+=old[tempnumber-dimsq-1];
        tempnew+=old[tempnumber-dimsq];
        tempnew+=old[tempnumber-dimsq+1];
        tempnew+=old[tempnumber-dimsq+DIM-1];
        tempnew+=old[tempnumber-dimsq+DIM];
        tempnew+=old[tempnumber-dimsq+DIM+1];
	tempnew+=old[tempnumber-DIM-1];
        tempnew+=old[tempnumber-DIM];
        tempnew+=old[tempnumber-DIM+1];
        tempnew+=old[tempnumber-1];
        tempnew+=old[tempnumber];
        tempnew+=old[tempnumber+1];
        tempnew+=old[tempnumber+DIM-1];
        tempnew+=old[tempnumber+DIM];
        tempnew+=old[tempnumber+DIM+1];
	tempnew+=old[tempnumber+dimsq-DIM-1];
        tempnew+=old[tempnumber+dimsq-DIM];
        tempnew+=old[tempnumber+dimsq-DIM+1];
        tempnew+=old[tempnumber+dimsq-1];
        tempnew+=old[tempnumber+dimsq];
        tempnew+=old[tempnumber+dimsq+1];
        tempnew+=old[tempnumber+dimsq+DIM-1];
        tempnew+=old[tempnumber+dimsq+DIM];
        tempnew+=old[tempnumber+dimsq+DIM+1];
	new[tempnumber] = tempnew;
        new[tempnumber]/=27;
	u=(new[tempnumber]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
       	switch(u){
	case(0):
	  temp0++;
	  break;
	case(1):
          temp1++;
          break;
	case(2):
          temp2++;
          break;
	case(3):
          temp3++;
          break;
	case(4):
          temp4++;
          break;
	case(5):
          temp5++;
          break;
	case(6):
          temp6++;
          break;
	case(7):
          temp7++;
          break;
	case(8):
          temp8++;
          break;
	case(9):
          temp9++;
          break;
	 }
	tempnew = 0;
      }
    }
  }
    histogrammy[0]+= temp0;
    histogrammy[1]+= temp1;
    histogrammy[2]+= temp2;
    histogrammy[3]+= temp3;
    histogrammy[4]+= temp4;
    histogrammy[5]+= temp5;
    histogrammy[6]+= temp6;
    histogrammy[7]+= temp7;
    histogrammy[8]+= temp8;
    histogrammy[9]+= temp9;
  aggregate += tempagg;
  printf("AGGR:%ld\n",aggregate);
  return (double) (dot_product+moving_average+pi+pi2);

}
