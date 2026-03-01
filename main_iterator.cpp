#pragma once
#include<iostream>
#include <vector>
#include "system_parameters.h"
#include <iomanip> 

double Tx_channel_Rx(system_parameters s);


int main() {

	system_parameters s;

	s.N_sc = 512;
	s.Constellation_size = 4;

	s.power_delay_profile = { 0,-5,-10};    
	s.CP_length = 4;                         // CP length should be larger than the length of power delay profile
	s.snr_array = {3,6,9,12,15,18,21};     // SNR is define with the TX power is normalized to  1 . The RX snr can be computed later
	s.number_of_frames = 2000;
	double avg_ber = 0;
	double curr_ber;


	cout << "SNR	BER"<<endl; 

	for (auto curr_snr : s.snr_array)
	{
		s.curr_snr = curr_snr;
		s.compute_noise_var();
		cout << fixed << setprecision(2) << s.curr_snr << "\t";
		for (int frame_idx = 0; frame_idx < s.number_of_frames; frame_idx++)
		{
			s.curr_frame_indx = frame_idx;
		    curr_ber  =  Tx_channel_Rx(s);
			avg_ber =  avg_ber + curr_ber; 


		}
		avg_ber = avg_ber / s.number_of_frames;
		s.avg_ber_array.push_back(avg_ber);
		cout << scientific << avg_ber << endl;
	}




}