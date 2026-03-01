#pragma once
#include "analysis.h"
#include <cmath>
#include<iostream>

using namespace std;

void analysis::compute_ber(Transmitter_operations t, Receiver_operations r, system_parameters s)
{

	int temp = 0;

	int count = 0;

	for (int j = 0; j < s.Num_rawbits; j++)
	{
		

		temp = temp + ( t.bits_stream[j] ^ r.rx_bits_stream[j] );
		count++;

	

	}
     
	ber_curr_frame = double(temp) / s.Num_rawbits;

}


