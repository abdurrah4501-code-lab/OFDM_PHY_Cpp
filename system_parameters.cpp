#include <iostream>
#include <cmath>
#include <complex>

#include "system_parameters.h"
using namespace std::complex_literals;  
using namespace std;


  void system_parameters::compute_num_raw_bits()
    {
     Num_rawbits = N_sc * log2(Constellation_size); 
    }


  void system_parameters::compute_noise_var()
  {

      noise_var = 1.0 / (pow(10, curr_snr / 10));         // The Tx power is normalized to 1

         
  }


    
  void system_parameters::create_constellation()
  {
     double n_axis =   sqrt(Constellation_size);
     
     vector<double> axis_arr;

     for(double j= -n_axis+1; j<= n_axis; j = j+2)
     { axis_arr.push_back(j); }


     double norm_fac_temp = 0, normalization_factor;

     for (double ele_out: axis_arr)
     {
        for (double ele_in: axis_arr)
         {

           constellation_arr.push_back(ele_out + ele_in*1i);

           norm_fac_temp = norm_fac_temp + pow(abs(ele_out + ele_in * 1i),2);
        
        }
     }

     normalization_factor = 1/ sqrt(norm_fac_temp / Constellation_size);


     for (auto& t : constellation_arr)
     {
         t = t * normalization_factor; 
     }


 
   
  
    }


      