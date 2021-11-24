#pragma comment(lib, "../x64/Release/FFT_Lib.lib")
#include <iostream>
#include <fstream>
#include "../FFT_Lib/FFT1D.h"

using namespace std;

int main(int argc, char* argv[])
{
	fstream fio("fft x[i].csv", ios::in);
	if (fio.fail()) { cout << "fail to open file!" << endl; return 400; }
	int dataSize = 128;
	FFT fft(dataSize);
	for (int i = 0; i < dataSize; i++)
	{
		double buf;
		fio >> buf;
		fft.X[i] = complex<double>(buf, 0.);
	}
	fio.close();

	fft.InverseDFT();

	fio.open("ifftx[i].csv", ios::out);
	if (fio.fail()) { cout << "fail to open file!" << endl; return 400; }
	for (int i = 0; i < dataSize; i++)
	{
		fio << fft.x[i].real() << endl;
	}
	fio.close();

	cout << "Done!" << endl;

	return 0;
}