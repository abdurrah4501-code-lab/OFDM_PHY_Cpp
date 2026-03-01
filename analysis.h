#pragma once
#include "Transmitter_operations.h"
#include "Receiver_operations.h"

class analysis {

public:
	double ber_curr_frame;
	void compute_ber(Transmitter_operations t, Receiver_operations r, system_parameters s);

};


