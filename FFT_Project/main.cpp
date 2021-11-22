#include <iostream>
#include "FFT1D.h"

using namespace std;

int main(int argc, char* argv[])
{
	complex<double> z1(3.0, 4.0), z2(2.0, 1.5);

	cout << "\n Complex Calculation\n\n";

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



	return 0;
}