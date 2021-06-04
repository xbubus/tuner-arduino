#ifndef fourier_hpp
#define fourier_hpp

#include "arduinoFFT.h"
#define SAMPLES 512                 //128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2 * 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.

extern arduinoFFT FFT;

extern unsigned int samplingPeriod;
extern unsigned long microSeconds;

extern double vReal[SAMPLES];
extern double vImag[SAMPLES];

void fill_fft_arrays();
double find_freq();

#endif