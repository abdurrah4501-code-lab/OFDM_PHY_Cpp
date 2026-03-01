#pragma once
#include <vector>
#include "system_parameters.h"
#include "channel.h"

class Receiver_operations
{
public: 

	vector<complex<double>> received_time_symbols_cp;
	vector<complex<double>> received_time_symbols;
	vector<complex<double>> received_freq_symbols;
	vector<complex<double>> equalized_freq_symbols;
	vector<complex<double>> demapped_symbols;
	vector<int> demapped_symbols_idx;
	vector<int> rx_bits_stream;



	void Equalization(system_parameters s, channel c);
	void OFDM_demodulation(system_parameters s, channel c);
	void symbols_to_bits(system_parameters s);
	void symbol_demapping(system_parameters s);
	void awgn(system_parameters s);

};