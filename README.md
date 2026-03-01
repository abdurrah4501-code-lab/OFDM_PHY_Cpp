# OFDM_PHY_C-
C++ based OFDM simulator yielding SNR versus BER performance. 

**Dependencies**

1 fftw3: Fast Fourier Transform library

**Features**

1, Constellation: QAM (Order 2,4,16,64,...)  
2, Channel: Multipath channel of any power delay profile  

3, Equalization: Zero forcing equalization

**File organization**

1, system_parameters.h contains all necessary system parameters such as Number of subcarriers, Constellation size, Cyclic prefix size, power delay profile  

2, Transmitter_operations.h contains all varaiables and functions related to the transmitter  

3, channel.h contains all varaiables and functions related to the wireless channel  

4, Receiver_operations.h contains all varaiables and functions related to the receiver  

5, analysis.h contains all functions to analyse system performance such as BER  


Every header file is supported by a source file of the same name containing the relevant function definitions  



**Where to start ?**

The entry point of the project is main_iterator.cpp. It handles iteration over different SNR values and the number of OFDM frames. All essential system parameters are also configured within this file.








