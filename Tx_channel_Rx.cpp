#pragma once
#include<iostream>
#include "Transmitter_operations.h"
#include <vector>
#include "channel.h"
#include "system_parameters.h"
#include "Receiver_operations.h"
#include "analysis.h"


using namespace std;
using namespace std::complex_literals;





double Tx_channel_Rx(system_parameters s)
{

 

 
 Transmitter_operations t;
 channel c(s);
 Receiver_operations r;
 analysis a;

 

 s.compute_num_raw_bits();
 s.create_constellation();
 
 t.gen_bits(s);
 t.bits_to_symbols(s);
 t.OFDM_modulation(s);
 
 r.received_time_symbols_cp = c.channel_conv(s, t);
 r.awgn(s);



 r.OFDM_demodulation(s,c);
 r.Equalization(s, c);
 r.symbol_demapping(s);
 r.symbols_to_bits(s);

 a.compute_ber(t,r,s);

 

 return a.ber_curr_frame;
}

