#include "FFT1D.h"
#include <cmath>
#include <complex>
#define FORWARD  1
#define INVERSE -1

const double PI = 3.14159265358979323846264338327;

// One Dimensional Constructor
FFT::FFT(Real* data, int Nn)
{
	N = Nn;
	InitializeFFT();
	for (int i = 0; i < N; i++)  *(x + i) = complex<double>(*(data + i), 0.0);
}
FFT::FFT(int Nn)
{
	N = Nn;
	InitializeFFT();
}
FFT::~FFT()
{
	delete x;
	delete X;
	delete W;
}
void FFT::InitializeFFT()
{
	x = new complex<double>[N];
	X = new complex<double>[N];
	W = new complex<double>[N];
	Real pi2N = PI * 2.0 / (Real)N;

	NU = 0; int k = 1;
	while (k != N) { k *= 2; NU += 1; }
	for (int i = 0; i < N; i++)   W[i] = complex<double>(cos(-pi2N * (Real)i), sin(-pi2N * (Real)i));
}

/**************************************
	 Decimation in time FFT algorithm
	 Forward and inverse FFT
	(Oppenheim and Shafer Page 608)
	 At the first time when the routine is called,
	 initialization is performed.
***************************************/

void FFT::ForwardFFT() { DITFFT(FORWARD); }
void FFT::InverseFFT() { DITFFT(INVERSE); }
void FFT::ForwardDFT() { DITDFT(FORWARD); }
void FFT::InverseDFT() { DITDFT(INVERSE); }

void FFT::DITFFT(int mode)
{
	int i, j, ip, k, len, le, le1, msb, lsb, now;
	complex<double> t, * XX;
	if (mode == FORWARD) { XX = X; for (i = 0; i < N; i++) XX[i] = x[i]; }
	else { XX = x; for (i = 0; i < N; i++) XX[i] = X[i]; }
	/* BitReversed Swaping of Input */
	int* index = new int[N];
	for (i = 0; i < N; i++) index[i] = 0;
	for (i = 1; i < N; i++)
	{
		msb = N / 2; lsb = 1;  j = 0;
		for (k = 0; k < NU; k++)
		{
			if ((msb & i) != 0) j += lsb;
			msb >>= 1; lsb <<= 1;
		}
		if (index[i] == 0)
		{
			index[i] = index[j] = 1;
			t = *(XX + j); *(XX + j) = *(XX + i);  *(XX + i) = t;
		}
	}
	delete index;
	/* NU stages of butterfly */
	k = N / 2;
	for (le = 2, le1 = 1; le1 < N; le <<= 1, le1 <<= 1, k >>= 1)
	{
		complex <double> u = complex<double>(1.0, 0.0);
		len = 0;
		for (j = 0; j < le1; j++)
		{
			for (i = j; i < N; i += le)
			{
				// a butterfly
				ip = i + le1;
				t = XX[ip] * u;
				XX[ip] = XX[i] - t;
				XX[i] = XX[i] + t;
			}
			len += k;
			while (len >= N) len -= N;
			while (len < 0)  len += N;
			if (mode == FORWARD)     now = len % N;
			else if ((len % N) != 0) now = N - len % N;
			else               now = 0;
			u = W[now];
		}
	}
	if (mode == INVERSE) for (i = 0; i < N; i++) *(XX + i) = *(XX + i) / (double)N;
}

void FFT::DITDFT(int)
{
	complex<double>* ejwt;

}