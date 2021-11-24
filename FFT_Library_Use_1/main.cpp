#pragma comment(lib, "../x64/Release/FFT_Lib.lib")
#include <iostream>
#include <fstream>
#include "../FFT_Lib/FFT1D.h"

using namespace std;

int main(int argc, char* argv[])
{
	int dataSize = 128;
	FFT fft(dataSize);
	for (int i = 0; i < dataSize; i++)
	{
		fft.x[i] = complex<double>(cos(8. * PI * (double)i / (double)dataSize), 0.);
	}

	fft.ForwardFFT();

	fstream fio("x[i].csv", ios::out);
	if (fio.fail()) { cout << "fail to open file!" << endl; return 400; }
	for (int i = 0; i < dataSize; i++)
	{
		fio << fft.x[i].real() << endl;
	}
	fio.close();

	fio.open("fft x[i].csv", ios::out);
	if (fio.fail()) { cout << "fail to open file!" << endl; return 400; }
	for (int i = 0; i < dataSize; i++)
	{
		fio << fft.X[i].real() << endl;
	}
	fio.close();

	cout << "Done!" << endl;

	return 0;
}