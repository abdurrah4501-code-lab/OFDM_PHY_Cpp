#include "Transmitter_operations.h"
#include <random>
#include <complex>
#include <cmath>
#include<iostream>
#include<fftw3.h>
#include "Channel.h"


void Transmitter_operations::gen_bits(system_parameters s)
{

          
    std::mt19937 gen(s.curr_frame_indx);            // Mersenne Twister generator seeded with rd()
    std::uniform_int_distribution<> dist(0, 1);    // Define the distribution ( 0 to 1)

    for (int i=0; i<s.Num_rawbits; i++)
    {
        bits_stream.push_back(dist(gen)) ;
       

    }

}



void Transmitter_operations::bits_to_symbols(system_parameters s)
{

    int k = log2(s.Constellation_size);

    int count = 0;
    for (int m = 0; m < s.Num_rawbits; m = m + k)
    {
        int idx = 0;
        for (int n = m, p=k-1; n < k+m; n++, p--)

        {

            idx = idx + (bits_stream[n] << p );
            

        }
     
        symbol_stream.push_back(s.constellation_arr[idx]);
      
    }

}




void Transmitter_operations::OFDM_modulation(system_parameters s)
{

	ofdm_symbol_stream.resize(s.N_sc);      //allocate size for the output of IFFT
	
    fftw_plan plan = fftw_plan_dft_1d(s.N_sc, reinterpret_cast<fftw_complex*>(symbol_stream.data()), reinterpret_cast<fftw_complex*>(ofdm_symbol_stream.data()), FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    // Normalize by (1/sqrt(N))
    for (auto &temp : ofdm_symbol_stream)
    {
        temp = temp / sqrt(s.N_sc);
    }

	// Add cyclic prefix

    ofdm_symbol_stream_with_CP = ofdm_symbol_stream;
    ofdm_symbol_stream_with_CP.insert(ofdm_symbol_stream_with_CP.begin(), ofdm_symbol_stream.end()-s.CP_length, ofdm_symbol_stream.end());

   

}







