#pragma comment(lib, "../x64/Release/FFT_Lib.lib")
#pragma comment(lib, "../x64/Release/Wave_Lib.lib")
#include <iostream>
#include <fstream>
#include "../FFT_Lib/FFT1D.h"
#include "../Wave_Lib/Wave.h"
#include "bmpNew.h"

using namespace std;

typedef short WAVDATATYPE;

int main(int argc, char* argv[])
{
	Wave wav("Beatles.wav");
	const int fftSize = 1024;
	FFT fft(fftSize);
	if (wav.data == nullptr) { cout << "fail to read file!" << endl; return 400; }
	
	cout 
		<< wav.bytePerSymbol << endl 
		<< wav.channelNum << endl 
		<< wav.frequency << endl 
		<< wav.length << endl 
		<< wav.dataNum() << endl 
		<< wav.indexMax() << endl;

	for (int i = 0; i < fftSize; i++)
	{
		fft.x[i] = *(short*)wav(1, i + 23000);
	}
	fft.ForwardFFT();
	fstream fio("Beatles2sec.csv", ios::out);
	for (int i = 0; i < 1024; i++)
	{
		fio << i / (double)wav.frequency << ',' << fft.x[i].real() << ',' << i * wav.frequency / (double)fftSize << ',' << norm(fft.X[i]) << endl;
	}
	fio.close();
	
	double* raw;
	unsigned char* img;
	int height = fftSize / 2;
	int width = wav.indexMax() / fftSize;
	width = 1280;

	cout << width << ", " << height << endl;
	raw = new double[width * height];
	img = new unsigned char[width * height * 3];

	for (int x = 0; x < width; x++)
	{
		for (int i = 0; i < fftSize; i++) {
			fft.x[i] = *(short*)wav(0, i + (x * fftSize));
		}
		fft.ForwardFFT();
		for (int y = 0; y < height; y++)
		{
			raw[y * width + x] = 10. * log10(norm(fft.X[y]));
		}
	}

	{
		double max = 0, min = 60;
		for (int i = 0; i < width * height; i++)
		{
			if (raw[i] > max) max = raw[i];
			//if (raw[i] < min) min = raw[i];
		}
		for (int i = 0; i < width * height; i++)
		{
			raw[i] = 765. * (raw[i] - min) / (max - min);
			if (raw[i] < 0) raw[i] = 0.;
		}
		cout << max << ", " << min << endl;
	}
	fio.open("bmpraw.csv", ios::out);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			fio << raw[y * width + x] << ',';
		}
		fio << endl;
	}
	fio.close();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			double buf = raw[y * width + x];
			img[3 * (y * width + x) + 2] = (buf > 255) ? (buf > 510 ? 765 - (int)buf : (int)buf - 255) : 0;
			img[3 * (y * width + x) + 1] = (buf > 255) ? (buf > 510 ? 0 : 510 - (int)buf) : (int)buf;
			img[3 * (y * width + x) + 0] = (buf > 255) ? 0 : 255 - (int)buf;
		}
	}
	bool wb = WriteBmp((char*)"Spectrum.bmp", img, width, height);
	if (!wb) cout << "fail to write bmp!" << endl;
	delete[] raw;
	delete[] img;	

	return 0;

}