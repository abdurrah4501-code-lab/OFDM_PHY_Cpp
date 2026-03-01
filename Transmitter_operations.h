#pragma once
#include <cmath>
#include <complex>
#include <vector>
#include<random>
#include "system_parameters.h"


using namespace std;
using namespace std::complex_literals;




class Transmitter_operations
{

public:

vector<int> bits_stream;

vector<complex<double>> symbol_stream;

vector<complex<double> > ofdm_symbol_stream;

vector<complex<double> > ofdm_symbol_stream_with_CP;



void gen_bits(system_parameters s);

void bits_to_symbols(system_parameters s);

void OFDM_modulation(system_parameters s);



};




