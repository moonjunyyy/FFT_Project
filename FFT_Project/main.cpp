#include <iostream>
#include <fstream>
#include <chrono>
#include "FFT1D.h"

using namespace std;

int main(int argc, char* argv[])
{
	// A1 : S1
	cout << "\nAssignment 1 : Sprint 1\n\n";
	complex<double> z1(3.0, 4.0), z2(2.0, 1.5);

	cout << "Complex Calculation\n\n";

	cout << "z1\t: " << z1 << endl;
	cout << "z2\t: " << z2 << endl << endl;

	cout << "z1 + z2\t: " << z1 + z2 << endl;
	cout << "z1 - z2\t: " << z1 - z2 << endl;
	cout << "z1 * z2\t: " << z1 * z2 << endl;
	cout << "z1 / z2\t: " << z1 / z2 << endl << endl;

	cout << "real(z2) : " << real(z2) << endl;
	cout << "imag(z2) : " << imag(z2) << endl;
	cout << "abs(z2)  : " << abs(z2) << endl;
	cout << "arg(z2)  : " << arg(z2) << endl;
	cout << "norm(z2) : " << norm(z2) << endl;

	// A1 : S2
	cout << "\nAssignment 1 : Sprint 2\n\n";

	auto start = chrono::system_clock::now();
	chrono::duration<double> duration;
	//duration = chrono::system_clock::now() - start;

	int dataSize = 128;
	double* data;
	data = new double[dataSize];
	for (int i = 0; i < dataSize; i++)
		data[i] = (i < 10 || i > 118 ? 1. : 0.);

	FFT* fft;
	fft = new FFT(data, dataSize);
	fstream fio("fft.csv", ios::out);

	start = chrono::system_clock::now();
	fft->ForwardFFT();
	duration = chrono::system_clock::now() - start;
	cout << "Excution Time : " << duration.count() << endl;
	for (int i = 0; i < dataSize; i++)
		fio << i << ',' << data[i] << ',' << fft->X[i].real() << endl;
	fio.close();

	// A1 : S3
	cout << "\nAssignment 1 : Sprint 3\n\n";

	fio.open("dft.csv", ios::out);
	start = chrono::system_clock::now();
	fft->ForwardDFT();
	duration = chrono::system_clock::now() - start;
	cout << "Excution Time : " << duration.count() << endl;
	for (int i = 0; i < dataSize; i++)
		fio << i << ',' << data[i] << ',' << fft->X[i].real() << endl;
	fio.close();

	// A1 : S4
	cout << "\nAssignment 1 : Sprint 4\n\n";

	delete fft;
	fft = new FFT(dataSize);
	for (int i = 0; i < dataSize; i++)
	{
		fft->X[i] = complex<double>(data[i], 0.);
	}
	fio.open("ifft.csv", ios::out);
	start = chrono::system_clock::now();
	fft->InverseFFT();
	duration = chrono::system_clock::now() - start;
	cout << "Excution Time : " << duration.count() << endl;
	for (int i = 0; i < dataSize; i++)
		fio << i << ',' << fft->x[i].real() << ',' << fft->X[i].real() << endl;

	delete fft;
	delete[] data;

	return 0;
}