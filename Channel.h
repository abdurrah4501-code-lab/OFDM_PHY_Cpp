#pragma once
#include<vector>
#include "system_parameters.h"
#include "Transmitter_operations.h"

class channel
{
public:
	
	vector<double> power_delay_profile;     // expressed in dB
	vector<double> power_delay_profile_lin;
	vector<complex<double>> channel_current_frame;

	channel(system_parameters s);

	vector<complex<double>> channel_conv(system_parameters s, Transmitter_operations t);

};

