#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <complex>  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
#define two_pi 6.2831
# define M_PI           3.14159265358979323846

Mat image;
Mat FFTImg_After;
Mat FFTImg_Before;
Mat FilterImg;
Mat IFFTImg;
float inc = 0.05;

class ComplexFloat {
public:
	double real;
	double img;

public:
	ComplexFloat()
	{
		this->real = 0;
		this->img = 0;
	}
	ComplexFloat(double real, double img)
	{
		this->real = real;
		this->img = img;
	}
	ComplexFloat operator+(const ComplexFloat& b)
	{
		double r = real + b.real;
		double i = img + b.img;
		return ComplexFloat(r, i);
	}
	ComplexFloat operator-(const ComplexFloat& b)
	{
		double r = real - b.real;
		double i = img - b.img;
		return ComplexFloat(r, i);
	}
	ComplexFloat operator*(const ComplexFloat& b)
	{
		double k1 = b.real * (real + img);
		double k2 = real * (b.img - b.real);
		double k3 = img * (b.img + b.real);
		return ComplexFloat(k1 - k3, k1 + k2);
	}

	ComplexFloat operator*(const double& b)
	{
		return ComplexFloat(real * b, img * b);
	}

	void operator*=(const double& b)
	{
		real *= b;
		img *= b;
	}

	ComplexFloat operator/(const double& b)
	{
		return ComplexFloat(real / b, img / b);
	}

	void operator=(const double& b)
	{
		real = b;
		img = 0;
	}

	double magnitude()
	{
		return sqrt(real * real + img * img);
	}
	void print() {
		cout << real << " + " << img << "i";
	}

};

template<typename T>
void Transpose(T** matrix, int N)
{
	T temp;
	for (int i = 0; i < N; i++) {
		T* start = matrix[i] + i;
		for (int j = i + 1; j < N; j++) {
			temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
}

ComplexFloat* FFT(uchar* x, int N, int arrSize, int zeroLoc, int gap)
{
	ComplexFloat* fft;
	fft = new ComplexFloat[N];

	int i;
	if (N == 2)
	{
		fft[0] = ComplexFloat(x[zeroLoc] + x[zeroLoc + gap], 0);
		fft[1] = ComplexFloat(x[zeroLoc] - x[zeroLoc + gap], 0);
	}
	else
	{
		ComplexFloat wN = ComplexFloat(cos(2 * M_PI / N), sin(-2 * M_PI / N));//exp(-j2*pi/N)
		ComplexFloat w = ComplexFloat(1, 0);
		gap *= 2;
		ComplexFloat* X_even = FFT(x, N / 2, arrSize, zeroLoc, gap); //N/2 POINT DFT OF EVEN X's
		ComplexFloat* X_odd = FFT(x, N / 2, arrSize, zeroLoc + (arrSize / N), gap); //N/2 POINT DFT OF ODD X's
		ComplexFloat todd;
		for (i = 0; i < N / 2; ++i)
		{
			//FFT(0) IS EQUAL TO FFT(N-1) SYMMETRICAL AROUND N/2
			todd = w * X_odd[i];
			fft[i] = X_even[i] + todd;
			fft[i + N / 2] = X_even[i] - todd;
			w = w * wN;
		}

		delete[] X_even;
		delete[] X_odd;
	}

	return fft;
}
ComplexFloat* FFT(ComplexFloat* x, int N, int arrSize, int zeroLoc, int gap)
{
	ComplexFloat* fft;
	fft = new ComplexFloat[N];

	int i;
	if (N == 2)
	{
		fft[0] = x[zeroLoc] + x[zeroLoc + gap];
		fft[1] = x[zeroLoc] - x[zeroLoc + gap];
	}
	else
	{
		ComplexFloat wN = ComplexFloat(cos(2 * M_PI / N), sin(-2 * M_PI / N));//exp(-j2*pi/N)
		ComplexFloat w = ComplexFloat(1, 0);
		gap *= 2;
		ComplexFloat* X_even = FFT(x, N / 2, arrSize, zeroLoc, gap); //N/2 POINT DFT OF EVEN X's
		ComplexFloat* X_odd = FFT(x, N / 2, arrSize, zeroLoc + (arrSize / N), gap); //N/2 POINT DFT OF ODD X's
		ComplexFloat todd;
		for (i = 0; i < N / 2; ++i)
		{
			//FFT(0) IS EQUAL TO FFT(N-1) SYMMETRICAL AROUND N/2
			todd = w * X_odd[i];
			fft[i] = X_even[i] + todd;
			fft[i + N / 2] = X_even[i] - todd;
			w = w * wN;
		}

		delete[] X_even;
		delete[] X_odd;
	}

	return fft;
}
ComplexFloat* IFFT(ComplexFloat* fft, int N, int arrSize, int zeroLoc, int gap)
{
	ComplexFloat* signal;
	signal = new ComplexFloat[N];

	int i;
	if (N == 2)
	{
		signal[0] = fft[zeroLoc] + fft[zeroLoc + gap];
		signal[1] = fft[zeroLoc] - fft[zeroLoc + gap];
	}
	else
	{
		ComplexFloat wN = ComplexFloat(cos(2 * M_PI / N), sin(2 * M_PI / N));//exp(j2*pi/N)
		ComplexFloat w = ComplexFloat(1, 0);
		gap *= 2;
		ComplexFloat* X_even = IFFT(fft, N / 2, arrSize, zeroLoc, gap); //N/2 POINT DFT OF EVEN X's
		ComplexFloat* X_odd = IFFT(fft, N / 2, arrSize, zeroLoc + (arrSize / N), gap); //N/2 POINT DFT OF ODD X's
		ComplexFloat todd;
		for (i = 0; i < N / 2; ++i)
		{
			//FFT(0) IS EQUAL TO FFT(N-1) SYMMETRICAL AROUND N/2
			todd = w * X_odd[i];
			signal[i] = (X_even[i] + todd) * 0.5;
			signal[i + N / 2] = (X_even[i] - todd) * 0.5;
			w = w * wN; // Get the next root(conjugate) among Nth roots of unity
		}

		delete[] X_even;
		delete[] X_odd;
	}

	return signal;
}

ComplexFloat** FFT2(Mat& source) {
	cout << "Applying FFT2" << endl;

	if (source.rows != source.cols) {
		cout << "Image is not Valid";
		return nullptr;
	}
	int N = source.rows;
	//cout << "Image size:" << N << endl;
	ComplexFloat** FFT2Result_h;
	FFT2Result_h = new ComplexFloat * [N];

	// ROW WISE FFT
	for (int i = 0; i < N; i++) {
		uchar* row = source.ptr<uchar>(i);
		FFT2Result_h[i] = FFT(row, N, N, 0, 1);
	}

	//cout << "final: " << endl;
	Transpose<ComplexFloat>(FFT2Result_h, N);

	// COLUMN WISE FFT
	for (int i = 0; i < N; i++) {
		FFT2Result_h[i] = FFT(FFT2Result_h[i], N, N, 0, 1);
	}
	Transpose<ComplexFloat>(FFT2Result_h, N);

	return FFT2Result_h;
}

ComplexFloat** IFFT2(ComplexFloat** source, int N) {

	cout << "Applying IFFT2" << endl;

	ComplexFloat** ifftResult;
	ifftResult = new ComplexFloat * [N];
	// ROW WISE FFT
	for (int i = 0; i < N; i++) {
		ifftResult[i] = IFFT(source[i], N, N, 0, 1);
	}

	//cout << "final: " << endl;
	Transpose<ComplexFloat>(ifftResult, N);

	int d = N * N;
	// COLUMN WISE FFT
	for (int i = 0; i < N; i++) {
		ifftResult[i] = IFFT(ifftResult[i], N, N, 0, 1);
		for (int j = 0; j < N; j++) {
			ifftResult[i][j] = ifftResult[i][j] / d;
		}
	}
	Transpose<ComplexFloat>(ifftResult, N);

	cout << endl;

	return ifftResult;
}

int main()
{
	Mat img = imread("C:/opencv/dip.tif", -1);
	imshow("h", img);
	vector<vector<int>>arr(img.rows, vector<int>(img.cols, 0));
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			arr[i][j] = img.at<uchar>(i, j);
		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			arr[i][j] = arr[i][j] * (pow((-1), i + j));
		}
	}
	Mat img1 = img.clone();
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img1.at<uchar>(i,j) = arr[i][j];
		}
	}
	ComplexFloat** FFT2Result_h;
	FFT2Result_h = FFT2(img1);
	ComplexFloat** ifft2result = IFFT2(FFT2Result_h, image.rows);
	//cout << ifft2result[10][34].magnitude();
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			arr[i][j] = ifft2result[i][j].magnitude() * (pow((-1), i + j));
		}
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img.at<uchar>(i,j)=arr[i][j];
		}
	}
	imshow("h", img);
	imwrite("C:/opencv/cameraman.jpg", img); 
	waitKey();
	return 0;
}