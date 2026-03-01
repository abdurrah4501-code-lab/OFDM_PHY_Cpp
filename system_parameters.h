#pragma once
#include <cmath>
#include <complex>
#include <vector>

using namespace std;
using namespace std::complex_literals;

class system_parameters 
{

    // A class that contains the necessary system paramters

 public:

    int N_sc;                       // Number of subcarriers
    int Constellation_size;        // Constellation order
    int Num_rawbits; 

    int Num_OFDM_symbols;                 // Num frames
    
    int CP_length;                  // cyclic prefix length
    
    int curr_frame_indx; 
    int number_of_frames;


    double noise_var;
    vector<double> avg_ber_array;

    double curr_snr;

    vector<double> snr_array;
    vector<complex<double>> constellation_arr;
    vector<double> power_delay_profile;        //expressed in dB
    vector<double> pdp_db;


public:


     void compute_num_raw_bits();
    
     void create_constellation();

     void compute_noise_var();

     


};



