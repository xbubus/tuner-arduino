#include "fourier.hpp"

arduinoFFT FFT = arduinoFFT();
unsigned int samplingPeriod = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
unsigned long microSeconds;
double vReal[SAMPLES];
double vImag[SAMPLES];

void fill_fft_arrays()
{
    for (int i = 0; i < SAMPLES; i++)
    {
        microSeconds = micros();

        vReal[i] = analogRead(A0); //
        vImag[i] = 0;

        while (micros() < (microSeconds + samplingPeriod))
        {
        }
    }
}

double find_freq()
{
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    return FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
}