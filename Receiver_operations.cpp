#pragma once
#include <vector>
#include "system_parameters.h"
#include "Receiver_operations.h"
#include<fftw3.h>
#include<iostream>
#include<cmath>
#include "channel.h"

using namespace std;


void Receiver_operations::OFDM_demodulation(system_parameters s, channel c)
{

	// Remove CP
	
	received_time_symbols.assign(received_time_symbols_cp.begin() + s.CP_length, received_time_symbols_cp.end() );



	// FFT operationn

	received_freq_symbols.resize(s.N_sc);

	fftw_plan plan = fftw_plan_dft_1d(s.N_sc,
		              reinterpret_cast<fftw_complex*>(received_time_symbols.data()),
		              reinterpret_cast<fftw_complex*>(received_freq_symbols.data()),
		              FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(plan);
	fftw_destroy_plan(plan);

	for (auto& temp : received_freq_symbols)
	{
		temp = temp / sqrt(s.N_sc);
	}


	






}

void Receiver_operations::Equalization(system_parameters s, channel c)
{

		// Compute freq domain channel;

	vector<complex<double>> freq_dom_channel(s.N_sc);

	c.channel_current_frame.resize(s.N_sc, 0);
	fftw_plan plan = fftw_plan_dft_1d(s.N_sc,
		reinterpret_cast<fftw_complex*>(c.channel_current_frame.data()),
		reinterpret_cast<fftw_complex*>(freq_dom_channel.data()),
		FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	// Equalization: 

	equalized_freq_symbols.resize(s.N_sc);
	for (int k = 0; k < received_freq_symbols.size(); k++)
	{	
		equalized_freq_symbols[k] = received_freq_symbols[k] / freq_dom_channel[k]; 
		
	}



}


void Receiver_operations::symbol_demapping(system_parameters s)
{
	double euclidean_distance, euclidean_distance_curr;
	int sym_idx;

	complex<double> temp_cons_symbol;

	for (int m = 0; m < s.N_sc; m++)
	{
		complex<double> curr_sym = equalized_freq_symbols[m];

		euclidean_distance = INFINITY;

		for (int n = 0; n < s.Constellation_size; n++)
		{

			euclidean_distance_curr = sqrt(pow(curr_sym.real() - s.constellation_arr[n].real(), 2) +
				                      pow(curr_sym.imag() - s.constellation_arr[n].imag(), 2));

			if (euclidean_distance_curr < euclidean_distance)
			{
				temp_cons_symbol = s.constellation_arr[n];
				euclidean_distance = euclidean_distance_curr;
				sym_idx = n;
			}

		}

		demapped_symbols.push_back(temp_cons_symbol);
		demapped_symbols_idx.push_back(sym_idx);

	}




}




void  Receiver_operations::symbols_to_bits(system_parameters s)
{
	int temp;

	for (int k = 0; k < s.N_sc; k++)
	{
		temp = demapped_symbols_idx[k];
		vector<int> temp_bits;

		for (int l = 0; l < log2(s.Constellation_size); l++)
		{

			temp_bits.push_back( ( (temp % 2 == 1) ? 1 : 0 ));
			temp = temp / 2;
		}
		reverse(temp_bits.begin(), temp_bits.end());

		rx_bits_stream.insert(rx_bits_stream.end(), temp_bits.begin(), temp_bits.end());


	}
   
}



void Receiver_operations::awgn(system_parameters s)
{

	std::mt19937 gen(s.curr_frame_indx);
	std::normal_distribution<> dist(0.0, sqrt(s.noise_var));

	complex<double> noise_curr; 
	
	for (int k = 0; k < (s.N_sc+s.CP_length); k++)
	{
		noise_curr = dist(gen)  + 1i * dist(gen);
		received_time_symbols_cp[k] = received_time_symbols_cp[k] + noise_curr;

	}



}