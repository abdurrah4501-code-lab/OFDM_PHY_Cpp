#pragma once
#include<iostream>
#include<vector>
#include "channel.h"
#include <random>
#include<cmath>
#include "Transmitter_operations.h"

using namespace std;

channel::channel(system_parameters s)
{


	// COmpute the normalization factor and Normalize the PDP
	double normal_factor =0;
	for (auto temp: s.power_delay_profile)
	{normal_factor = normal_factor + temp;}

	for (auto &pdp_curr : s.power_delay_profile)
	{
		pdp_curr = pdp_curr*(1.0/normal_factor);
	}


	power_delay_profile = s.power_delay_profile;
	
	std::mt19937 gen(s.curr_frame_indx);
	std::normal_distribution<> dist(0.0, 1.0);

	channel_current_frame.resize(power_delay_profile.size());

	for (int k = 0; k < power_delay_profile.size(); k++)
	{
	  channel_current_frame[k] = (dist(gen) * sqrt(pow(10, (power_delay_profile[k] / 10))/2)) +  1i* (dist(gen) * sqrt(pow(10, (power_delay_profile[k] / 10))/2));
		 
	}



}



vector<complex<double>> channel::channel_conv(system_parameters s, Transmitter_operations t )
{
	//int size_rx = s.N_sc + s.CP_length + s.power_delay_profile.size() - 1;

	int size_rx = s.N_sc + s.CP_length;

	vector<complex<double>> received_time_symbols_cp(size_rx);

	for (int n = 0; n < size_rx; n++)
	{
		complex<double> temp = 0;

		for (int k = 0; k < t.ofdm_symbol_stream_with_CP.size(); k++)
		{
			if (n - k >= 0 &&  (n-k) < channel_current_frame.size())
			{		 
				temp = temp + (t.ofdm_symbol_stream_with_CP[k] * channel_current_frame[n - k]);
			}

		}
		received_time_symbols_cp[n] = temp;

	}


	return received_time_symbols_cp;

}

