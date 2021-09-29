#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

Mat gaussian(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			double val = (0.3679 * arr[i - 1][j - 1] + 0.6065 * arr[i - 1][j] + 0.3679 * arr[i - 1][j + 1] + 0.6065 * arr[i][j - 1] + 1.000 * arr[i][j] + 0.6065 * arr[i][j + 1] + 0.3679 * arr[i + 1][j - 1] + 0.6065 * arr[i + 1][j] + 0.3679 * arr[i + 1][j + 1]);
			val = val / 4.8976;
			val = (int)val;
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}





int main()
{
	Mat img = imread("C:/opencv/lena_gray_512.jpg", -1);
	vector<vector<int>>arr(512 + 2, vector<int>(512 + 2, 0));
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			arr[i][j] = img.at<uchar>(i, j);
		}
	}
	Mat output_blurred = gaussian(img, arr);
	vector<vector<int>>main_input(512 + 2, vector<int>(512 + 2, 0));
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			main_input[i][j] = output_blurred.at<uchar>(i, j);
		}
	}
	int k = 1;
	vector<vector<int>>I_K(512 + 2, vector<int>(512 + 2, 0));
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			I_K[i][j] = main_input[i][j];
		}
	}
	while (k--)
	{
		vector<vector<int>>arr1(512 + 2, vector<int>(512 + 2, 0));
		for (int i = 1; i < 512; i++)
		{
			for (int j = 1; j < 512; j++)
			{
				arr1[i][j] = I_K[i][j];
			}
		}
		Mat A = gaussian(output_blurred, arr1);
		vector<vector<int>>B(512 + 2, vector<int>(512 + 2, 0));
		for (int i = 1; i < 512; i++)
		{
			for (int j = 1; j < 512; j++)
			{
				double val = (1.0) * (main_input[i][j]);
				val = val / (A.at<uchar>(i, j));
				val = (int)val;
				B[i][j] = val;
			}
		}
		Mat C = gaussian(img, B);

		for (int i = 1; i < 512; i++)
		{
			for (int j = 1; j < 512; j++)
			{
				int val = (C.at<uchar>(i, j)) * (arr1[i][j]);
				I_K[i][j] = val;
			}
		}
	}
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			output.at<uchar>(i, j) = I_K[i][j];
		}
	}
	imwrite("C:/opencv/lena_gray_5121.jpg", output);
	waitKey();
	return 0;
}
