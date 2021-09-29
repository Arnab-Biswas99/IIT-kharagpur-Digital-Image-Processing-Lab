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

int gradient_H_3[3][3] = { {-1, -1, -1 },
					{ 0,  0,  0 },
					{ 1,  1,  1 } };

int gradient_H_5[5][5] = { { -1, -1, -1, -1, -1 },
				   { -2, -2, -2, -2, -2 },
				   {  0,  0,  0,  0,  0 },
				   {  2,  2,  2,  2,  2 },
				   {  1,  1,  1,  1,  1 } };

int gradient_H_7[7][7] = { { -1, -1, -1, -1, -1, -1, -1 },
					{ -2, -2, -2, -2, -2, -2, -2 },
					{ -3, -3, -3, -3, -3, -3, -3 },
					{ 0, 0, 0, 0, 0, 0, 0 },
					{ 3, 3, 3, 3, 3, 3, 3 },
					{ 2, 2, 2, 2, 2, 2, 2 },
					{ 1, 1, 1, 1, 1, 1, 1 } };
int gradient_H_9[9][9] = { { -1, -1, -1, -1, -1, -1, -1 },
					{ -2, -2, -2, -2, -2, -2, -2 },
					{ -3, -3, -3, -3, -3, -3, -3 },
					{ 0, 0, 0, 0, 0, 0, 0 },
					{ 3, 3, 3, 3, 3, 3, 3 },
					{ 2, 2, 2, 2, 2, 2, 2 },
};
int prewitt_3[3][3] = { {-1, -1, -1 },
					{ 0,  0,  0 },
					{ 1,  1,  1 } };

int prewitt_5[5][5] = { { -1, -1, -1, -1, -1 },
				   { -2, -2, -2, -2, -2 },
				   {  0,  0,  0,  0,  0 },
				   {  2,  2,  2,  2,  2 },
				   {  1,  1,  1,  1,  1 } };

int prewitt_7[7][7] = { { -1, -1, -1, -1, -1, -1, -1 },
					{ -2, -2, -2, -2, -2, -2, -2 },
					{ -3, -3, -3, -3, -3, -3, -3 },
					{ 0, 0, 0, 0, 0, 0, 0 },
					{ 3, 3, 3, 3, 3, 3, 3 },
					{ 2, 2, 2, 2, 2, 2, 2 },
					{ 1, 1, 1, 1, 1, 1, 1 } };
int prewitt_9[9][9] = { { -1, -1, -1, -1, -1, -1, -1 },
					{ -2, -2, -2, -2, -2, -2, -2 },
					{ -3, -3, -3, -3, -3, -3, -3 },
					{ 0, 0, 0, 0, 0, 0, 0 },
					{ 3, 3, 3, 3, 3, 3, 3 },
					{ 2, 2, 2, 2, 2, 2, 2 },
					{ 1, 1, 1, 1, 1, 1, 1 } };

int gradient_V_3[3][3] = { { 1, 0, -1 },
				   { 1, 0, -1 },
				   { 1, 0, -1 } };

int gradient_V_5[5][5] = { {-1,-2,0,2,1},
{-1,-2,0,2,1},
{-1,-2,0,2,1},
{-1,-2,0,2,1},
{-1,-2,0,2,1}
};

int gradient_V_7[7][7] = { {-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1} };
int gradient_V_9[9][9] = { {-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1},
{-1,-2,-3,0,3,2,1} };


int laplacian_3[3][3] = { {-1, -1, -1},
							{-1, 8, -1},
							{-1, -1, -1} };

int laplacian_5[5][5] = { {-1, 3, -4, -3, -1},
					{-3, 0,  6,  0, -3},
					{-4, 6, 20,  6, -4},
					{-3, 0,  6,  0, -3},
					{-1,-3, -4, -3, -1} };

int laplacian_7[7][7] = { {-2, -3, -4, -6, -4, -3, -2},
					{-3, -5, -4, -3, -4, -5, -3},
					{-4, -4,  9, 20,  9, -4, -4},
					{-6, -3, 20, 36, 20, -3, -6},
					{-4, -4,  9, 20,  9, -4, -4},
					{-3, -5, -4, -3, -4, -5, -3},
					{-2, -3, -4, -6, -4, -3, -2} };

int laplacian_9[9][9] = {
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{1,1,1,1,-16,1,1,1,1},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
};

int sobel_H_3[3][3] = { {  1,  2,  1},
						{  0,  0,  0},
						{ -1, -2, -1} };

int sobel_H_5[5][5] = { { 1,   4,   7,   4,  1},
						{ 2,  10,  17,  10,  2},
						{ 0,   0,   0,   0,  0},
						{-2, -10, -17, -10, -2},
						{ -1, -4, -7, -4, -1 } };

int sobel_H_7[7][7] = { {  1,  4,  9,  13,  9,  4,  1},
						{  3, 11, 26,  34, 26, 11,  3},
						{  3, 13, 30,  40, 30, 13,  3},
						{  0,  0,  0,   0,  0,  0,  0},
						{ -3, -13,-30,-40,-30,-13, -3},
						{ -3, -11,-26, 34,-26,-11, -3},
						{ -1, -4, -9, -13, -9, -4, -1} };

int sobel_H_9[9][9] = { {-4,-4,-4,-4,-8,-4,-4,-4,-4},
						{-3,-3,-3,-3,-6,-3,-3,-3,-3},
						{-2,-2,-2,-2,-4,-2,-2,-2,-2},
						{-1,-1,-1,-1,-2,-1,-1,-1,-1},
						{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
						{1, 1, 1, 1, 2, 1, 1, 1, 1},
						{2, 2, 2, 2, 4, 2, 2, 2, 2},
						{3, 3, 3, 3, 6, 3, 3, 3, 3},
						{4, 4, 4, 4, 8, 4, 4, 4, 4} };

int sobel_V_3[3][3] = { { -1, 0, 1 },
						{ -2, 0, 2 },
						{ -1, 0, 1 } };


int sobel_V_5[5][5] = { { -1,  -2, 0,  2, 1 },
						{ -4, -10, 0, 10, 4 },
						{ -7, -17, 0, 17, 7 },
						{ -4, -10, 0, 10, 4 },
						{ -1,  -2, 0, -2, 1 } };



int sobel_V_7[7][7] = { { -1,  -3,  -3, 0, 3,  3,   1},
						{ -4, -11, -13, 0, 13, 11,  4},
						{ -9, -26, -30, 0, 30, 26,  9},
						{ -13, -34,-40, 0, 40, 34, 13},
						{  -9, -26,-30, 0, 30, 26,  9},
						{  -4, -11,-13, 0, 13, 11,  4},
						{   1,  -3, -3, 0,  3,  3,  1} };

int sobel_V_9[9][9] = { { -1,  -3,  -3, 0, 3,  3,   1},
						{ -4, -11, -13, 0, 13, 11,  4},
						{ -9, -26, -30, 0, 30, 26,  9},
						{ -13, -34,-40, 0, 40, 34, 13},
						{  -9, -26,-30, 0, 30, 26,  9},
						{  -4, -11,-13, 0, 13, 11,  4},
						{   1,  -3, -3, 0,  3,  3,  1} };
int sobel_D_3[3][3] = { { 0,  1, 2},
						{ -1, 0, 1},
						{ -2,-1, 0} };

int laplacianOfGaussian_3[3][3] = { {0, -1, 0},
									{-1, 4, -1},
									{0, -1, 0},
};

int laplacianOfGaussian_5[5][5] = { {0, 0, 1,0,0},
									{0, 1, 2,1,0},
									{1, 2, -16,2,1},
									{0, 1, 2,1,0},
									{0, 0, 1,0,0} };
int laplacianOfGaussian_7[7][7] = {
					{1, 6, 15, 20, 15, 6, 1},
					{6, 36, 90, 120, 90, 36, 6},
					{15, 90, 225, 300, 225, 90, 15},
					{20, 120, 300, 400, 300, 120, 20},
					{15, 90, 225, 300, 225, 90, 15},
					{6, 36, 90, 120, 90, 36, 6},
					{1, 6, 15, 20, 15, 6, 1},
};
int laplacianOfGaussian_9[9][9] = {
					{1, 6, 15, 20, 15, 6, 1},
					{6, 36, 90, 120, 90, 36, 6},
					{15, 90, 225, 300, 225, 90, 15},
					{20, 120, 300, 400, 300, 120, 20},
					{15, 90, 225, 300, 225, 90, 15},
					{6, 36, 90, 120, 90, 36, 6},
					{1, 6, 15, 20, 15, 6, 1} };

int gaussian_3[3][3] = { {1, -2, 1},
						{-2, 4, -2},
						{1,-2,1} };

int gaussian_5[5][5] = { {0, 0, 1,0,0},
						{0, 1, 2,1,0},
						{1, 2, -16,2,1},
						{0, 1, 2,1,0},
						{0, 0, 1,0,0} };
int gaussian_7[7][7] = {
					{1, 6, 15, 20, 15, 6, 1},
					{6, 36, 90, 120, 90, 36, 6},
					{15, 90, 225, 300, 225, 90, 15},
					{20, 120, 300, 400, 300, 120, 20},
					{15, 90, 225, 300, 225, 90, 15},
					{6, 36, 90, 120, 90, 36, 6},
					{1, 6, 15, 20, 15, 6, 1},
};
int gaussian_9[9][9] = {
					{1, 6, 15, 20, 15, 6, 1},
					{6, 36, 90, 120, 90, 36, 6},
					{15, 90, 225, 300, 225, 90, 15},
					{20, 120, 300, 400, 300, 120, 20},
					{15, 90, 225, 300, 225, 90, 15},
					{6, 36, 90, 120, 90, 36, 6},
					{1, 6, 15, 20, 15, 6, 1},
};

Mat prewitt(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			double val = ((-1) * arr[i - 1][j - 1] + (-1) * arr[i - 1][j] + (-1) * arr[i - 1][j + 1] + (0) * arr[i][j - 1] + (0) * arr[i][j] + (0) * arr[i][j + 1] + (1) * arr[i + 1][j - 1] + (1) * arr[i + 1][j] + (1) * arr[i + 1][j + 1]);
			//val = val / 4.8976;
			val = (int)val;
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat lapgaussian(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			int val = ((0) * arr[i - 1][j - 1] + (-1) * arr[i - 1][j] + (0) * arr[i - 1][j + 1] + (-1) * arr[i][j - 1] + (4) * arr[i][j] + (-1) * arr[i][j + 1] + (0) * arr[i + 1][j - 1] + (-1) * arr[i + 1][j] + (0) * arr[i + 1][j + 1]);
			//val = val / 4.8976;

			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat prewitt5(Mat img, vector<vector<int>>arr1)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = ((-1) * arr1[i - 2][j - 2] + (-1) * arr1[i - 2][j - 1] + (-1) * arr1[i - 2][j - 0] + (-1) * arr1[i - 2][j + 1] + (-1) * arr1[i - 2][j + 2] + (-2) * arr1[i - 1][j - 2] + (-2) * arr1[i - 1][j - 1] + (-2) * arr1[i - 1][j] + (-2) * arr1[i - 1][j + 1] + (-2) * arr1[i - 1][j + 2] + 0 * arr1[i][j - 2] + (0) * arr1[i][j - 1] + (0) * arr1[i][j] + (0) * arr1[i][j + 1] + 0 * arr1[i][j + 2] + 2 * arr1[i + 1][j - 2] + (2) * arr1[i + 1][j - 1] + (2) * arr1[i + 1][j] + (2) * arr1[i + 1][j + 1] + 2 * arr1[i + 1][j + 2] + (1) * arr1[i + 2][j - 2] + (1) * arr1[i + 2][j - 1] + (1) * arr1[i + 2][j - 0] + (1) * arr1[i + 2][j + 1] + (1) * arr1[i + 2][j + 2]);
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat laplacian5(Mat img, vector<vector<int>>arr1)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = ((-1) * arr1[i - 2][j - 2] + (3) * arr1[i - 2][j - 1] + (-4) * arr1[i - 2][j - 0] + (-3) * arr1[i - 2][j + 1] + (-1) * arr1[i - 2][j + 2] + (-3) * arr1[i - 1][j - 2] + (0) * arr1[i - 1][j - 1] + (6) * arr1[i - 1][j] + (0) * arr1[i - 1][j + 1] + (-3) * arr1[i - 1][j + 2] + (-4) * arr1[i][j - 2] + (6) * arr1[i][j - 1] + (20) * arr1[i][j] + (6) * arr1[i][j + 1] + (-4) * arr1[i][j + 2] + (-3) * arr1[i + 1][j - 2] + (0) * arr1[i + 1][j - 1] + (6) * arr1[i + 1][j] + (0) * arr1[i + 1][j + 1] + (-3) * arr1[i + 1][j + 2] + (-1) * arr1[i + 2][j - 2] + (-3) * arr1[i + 2][j - 1] + (-4) * arr1[i + 2][j - 0] + (-3) * arr1[i + 2][j + 1] + (-1) * arr1[i + 2][j + 2]);
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_x5(Mat img, vector<vector<int>>arr1)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = ((sobel_H_5[0][0])) * arr1[i - 2][j - 2] + ((sobel_H_5[0][1])) * arr1[i - 2][j - 1] + ((sobel_H_5[0][2])) * arr1[i - 2][j - 0] + ((sobel_H_5[0][3])) * arr1[i - 2][j + 1] + ((sobel_H_5[0][4])) * arr1[i - 2][j + 2] + ((sobel_H_5[1][0])) * arr1[i - 1][j - 2] + ((sobel_H_5[1][1])) * arr1[i - 1][j - 1] + ((sobel_H_5[1][2])) * arr1[i - 1][j] + ((sobel_H_5[1][3])) * arr1[i - 1][j + 1] + ((sobel_H_5[1][4])) * arr1[i - 1][j + 2] + ((sobel_H_5[2][0])) * arr1[i][j - 2] + ((sobel_H_5[2][1])) * arr1[i][j - 1] + ((sobel_H_5[2][2])) * arr1[i][j] + ((sobel_H_5[2][3])) * arr1[i][j + 1] + ((sobel_H_5[2][4])) * arr1[i][j + 2] + ((sobel_H_5[3][0])) * arr1[i + 1][j - 2] + ((sobel_H_5[3][1])) * arr1[i + 1][j - 1] + ((sobel_H_5[3][2])) * arr1[i + 1][j] + ((sobel_H_5[3][3])) * arr1[i + 1][j + 1] + ((sobel_H_5[3][4])) * arr1[i + 1][j + 2] + ((sobel_H_5[4][0])) * arr1[i + 2][j - 2] + ((sobel_H_5[4][1])) * arr1[i + 2][j - 1] + ((sobel_H_5[4][2])) * arr1[i + 2][j - 0] + ((sobel_H_5[4][3])) * arr1[i + 2][j + 1] + ((sobel_H_5[4][4])) * arr1[i + 2][j + 2];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_y5(Mat img, vector<vector<int>>arr1)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = ((sobel_V_5[0][0])) * arr1[i - 2][j - 2] + ((sobel_V_5[0][1])) * arr1[i - 2][j - 1] + ((sobel_V_5[0][2])) * arr1[i - 2][j - 0] + ((sobel_V_5[0][3])) * arr1[i - 2][j + 1] + ((sobel_V_5[0][4])) * arr1[i - 2][j + 2] + ((sobel_V_5[1][0])) * arr1[i - 1][j - 2] + ((sobel_V_5[1][1])) * arr1[i - 1][j - 1] + ((sobel_V_5[1][2])) * arr1[i - 1][j] + ((sobel_V_5[1][3])) * arr1[i - 1][j + 1] + ((sobel_V_5[1][4])) * arr1[i - 1][j + 2] + ((sobel_V_5[2][0])) * arr1[i][j - 2] + ((sobel_V_5[2][1])) * arr1[i][j - 1] + ((sobel_V_5[2][2])) * arr1[i][j] + ((sobel_V_5[2][3])) * arr1[i][j + 1] + ((sobel_V_5[2][4])) * arr1[i][j + 2] + ((sobel_V_5[3][0])) * arr1[i + 1][j - 2] + ((sobel_V_5[3][1])) * arr1[i + 1][j - 1] + ((sobel_V_5[3][2])) * arr1[i + 1][j] + ((sobel_V_5[3][3])) * arr1[i + 1][j + 1] + ((sobel_V_5[3][4])) * arr1[i + 1][j + 2] + ((sobel_V_5[4][0])) * arr1[i + 2][j - 2] + ((sobel_V_5[4][1])) * arr1[i + 2][j - 1] + ((sobel_V_5[4][2])) * arr1[i + 2][j - 0] + ((sobel_V_5[4][3])) * arr1[i + 2][j + 1] + ((sobel_V_5[4][4])) * arr1[i + 2][j + 2];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat gaussian5(Mat img, vector<vector<int>>arr1)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = ((gaussian_5[0][0])) * arr1[i - 2][j - 2] + ((gaussian_5[0][1])) * arr1[i - 2][j - 1] + ((gaussian_5[0][2])) * arr1[i - 2][j - 0] + ((gaussian_5[0][3])) * arr1[i - 2][j + 1] + ((gaussian_5[0][4])) * arr1[i - 2][j + 2] + ((gaussian_5[1][0])) * arr1[i - 1][j - 2] + ((gaussian_5[1][1])) * arr1[i - 1][j - 1] + ((gaussian_5[1][2])) * arr1[i - 1][j] + ((gaussian_5[1][3])) * arr1[i - 1][j + 1] + ((gaussian_5[1][4])) * arr1[i - 1][j + 2] + ((gaussian_5[2][0])) * arr1[i][j - 2] + ((gaussian_5[2][1])) * arr1[i][j - 1] + ((gaussian_5[2][2])) * arr1[i][j] + ((gaussian_5[2][3])) * arr1[i][j + 1] + ((gaussian_5[2][4])) * arr1[i][j + 2] + ((gaussian_5[3][0])) * arr1[i + 1][j - 2] + ((gaussian_5[3][1])) * arr1[i + 1][j - 1] + ((gaussian_5[3][2])) * arr1[i + 1][j] + ((gaussian_5[3][3])) * arr1[i + 1][j + 1] + ((gaussian_5[3][4])) * arr1[i + 1][j + 2] + ((gaussian_5[4][0])) * arr1[i + 2][j - 2] + ((gaussian_5[4][1])) * arr1[i + 2][j - 1] + ((gaussian_5[4][2])) * arr1[i + 2][j - 0] + ((gaussian_5[4][3])) * arr1[i + 2][j + 1] + ((gaussian_5[4][4])) * arr1[i + 2][j + 2];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat lap_gaussian5(Mat img, vector<vector<int>>arr1)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = ((laplacianOfGaussian_5[0][0])) * arr1[i - 2][j - 2] + ((laplacianOfGaussian_5[0][1])) * arr1[i - 2][j - 1] + ((laplacianOfGaussian_5[0][2])) * arr1[i - 2][j - 0] + ((laplacianOfGaussian_5[0][3])) * arr1[i - 2][j + 1] + ((laplacianOfGaussian_5[0][4])) * arr1[i - 2][j + 2] + ((laplacianOfGaussian_5[1][0])) * arr1[i - 1][j - 2] + ((laplacianOfGaussian_5[1][1])) * arr1[i - 1][j - 1] + ((laplacianOfGaussian_5[1][2])) * arr1[i - 1][j] + ((laplacianOfGaussian_5[1][3])) * arr1[i - 1][j + 1] + ((laplacianOfGaussian_5[1][4])) * arr1[i - 1][j + 2] + ((laplacianOfGaussian_5[2][0])) * arr1[i][j - 2] + ((laplacianOfGaussian_5[2][1])) * arr1[i][j - 1] + ((laplacianOfGaussian_5[2][2])) * arr1[i][j] + ((laplacianOfGaussian_5[2][3])) * arr1[i][j + 1] + ((laplacianOfGaussian_5[2][4])) * arr1[i][j + 2] + ((laplacianOfGaussian_5[3][0])) * arr1[i + 1][j - 2] + ((laplacianOfGaussian_5[3][1])) * arr1[i + 1][j - 1] + ((laplacianOfGaussian_5[3][2])) * arr1[i + 1][j] + ((laplacianOfGaussian_5[3][3])) * arr1[i + 1][j + 1] + ((laplacianOfGaussian_5[3][4])) * arr1[i + 1][j + 2] + ((laplacianOfGaussian_5[4][0])) * arr1[i + 2][j - 2] + ((laplacianOfGaussian_5[4][1])) * arr1[i + 2][j - 1] + ((laplacianOfGaussian_5[4][2])) * arr1[i + 2][j - 0] + ((laplacianOfGaussian_5[4][3])) * arr1[i + 2][j + 1] + ((laplacianOfGaussian_5[4][4])) * arr1[i + 2][j + 2];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat prewitt7(Mat img, vector<vector<int>>arr2)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (prewitt_7[0][0]) * arr2[i - 3][j - 3] + (prewitt_7[0][1]) * arr2[i - 3][j - 2] + (prewitt_7[0][2]) * arr2[i - 3][j - 1] + (prewitt_7[0][3]) * arr2[i - 3][j - 0] + (prewitt_7[0][4]) * arr2[i - 3][j + 1] + (prewitt_7[0][5]) * arr2[i - 3][j + 2] + (prewitt_7[0][6]) * arr2[i - 3][j + 3] + (prewitt_7[1][0]) * arr2[i - 2][j - 3] + ((prewitt_7[1][1])) * arr2[i - 2][j - 2] + ((prewitt_7[1][2])) * arr2[i - 2][j - 1] + ((prewitt_7[1][3])) * arr2[i - 2][j - 0] + ((prewitt_7[1][4])) * arr2[i - 2][j + 1] + ((prewitt_7[1][5])) * arr2[i - 2][j + 2] + (prewitt_7[1][6]) * arr2[i - 2][j + 3] + (prewitt_7[2][0]) * arr2[i - 1][j - 3] + ((prewitt_7[2][1])) * arr2[i - 1][j - 2] + ((prewitt_7[2][2])) * arr2[i - 1][j - 1] + ((prewitt_7[2][3])) * arr2[i - 1][j] + ((prewitt_7[2][4])) * arr2[i - 1][j + 1] + ((prewitt_7[2][5])) * arr2[i - 1][j + 2] + (prewitt_7[2][6]) * arr2[i - 1][j + 3] + (prewitt_7[3][0]) * arr2[i][j - 3] + ((prewitt_7[3][1])) * arr2[i][j - 2] + ((prewitt_7[3][2])) * arr2[i][j - 1] + ((prewitt_7[3][3])) * arr2[i][j] + ((prewitt_7[3][4])) * arr2[i][j + 1] + ((prewitt_7[3][5])) * arr2[i][j + 2] + (prewitt_7[3][6]) * arr2[i][j + 3] + (prewitt_7[4][0]) * arr2[i + 1][j - 3] + ((prewitt_7[4][1])) * arr2[i + 1][j - 2] + ((prewitt_7[4][2])) * arr2[i + 1][j - 1] + ((prewitt_7[4][3])) * arr2[i + 1][j] + ((prewitt_7[4][4])) * arr2[i + 1][j + 1] + ((prewitt_7[4][5])) * arr2[i + 1][j + 2] + (prewitt_7[4][6]) * arr2[i + 1][j + 3] + (prewitt_7[5][0]) * arr2[i + 2][j - 3] + ((prewitt_7[5][1])) * arr2[i + 2][j - 2] + ((prewitt_7[5][2])) * arr2[i + 2][j - 1] + ((prewitt_7[5][3])) * arr2[i + 2][j - 0] + ((prewitt_7[5][4])) * arr2[i + 2][j + 1] + ((prewitt_7[5][5])) * arr2[i + 2][j + 2] + (prewitt_7[5][6]) * arr2[i + 2][j + 3] + (prewitt_7[6][0]) * arr2[i + 3][j - 3] + (prewitt_7[6][1]) * arr2[i + 3][j - 2] + (prewitt_7[6][2]) * arr2[i + 3][j - 1] + (prewitt_7[6][3]) * arr2[i + 3][j - 0] + (prewitt_7[6][4]) * arr2[i + 3][j + 1] + (prewitt_7[6][5]) * arr2[i + 3][j + 2] + (prewitt_7[6][6]) * arr2[i + 3][j + 3];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat laplacian7(Mat img, vector<vector<int>>arr2)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (laplacian_7[0][0]) * arr2[i - 3][j - 3] + (laplacian_7[0][1]) * arr2[i - 3][j - 2] + (laplacian_7[0][2]) * arr2[i - 3][j - 1] + (laplacian_7[0][3]) * arr2[i - 3][j - 0] + (laplacian_7[0][4]) * arr2[i - 3][j + 1] + (laplacian_7[0][5]) * arr2[i - 3][j + 2] + (laplacian_7[0][6]) * arr2[i - 3][j + 3] + (laplacian_7[1][0]) * arr2[i - 2][j - 3] + ((laplacian_7[1][1])) * arr2[i - 2][j - 2] + ((laplacian_7[1][2])) * arr2[i - 2][j - 1] + ((laplacian_7[1][3])) * arr2[i - 2][j - 0] + ((laplacian_7[1][4])) * arr2[i - 2][j + 1] + ((laplacian_7[1][5])) * arr2[i - 2][j + 2] + (laplacian_7[1][6]) * arr2[i - 2][j + 3] + (laplacian_7[2][0]) * arr2[i - 1][j - 3] + ((laplacian_7[2][1])) * arr2[i - 1][j - 2] + ((laplacian_7[2][2])) * arr2[i - 1][j - 1] + ((laplacian_7[2][3])) * arr2[i - 1][j] + ((laplacian_7[2][4])) * arr2[i - 1][j + 1] + ((laplacian_7[2][5])) * arr2[i - 1][j + 2] + (laplacian_7[2][6]) * arr2[i - 1][j + 3] + (laplacian_7[3][0]) * arr2[i][j - 3] + ((laplacian_7[3][1])) * arr2[i][j - 2] + ((laplacian_7[3][2])) * arr2[i][j - 1] + ((laplacian_7[3][3])) * arr2[i][j] + ((laplacian_7[3][4])) * arr2[i][j + 1] + ((laplacian_7[3][5])) * arr2[i][j + 2] + (laplacian_7[3][6]) * arr2[i][j + 3] + (laplacian_7[4][0]) * arr2[i + 1][j - 3] + ((laplacian_7[4][1])) * arr2[i + 1][j - 2] + ((laplacian_7[4][2])) * arr2[i + 1][j - 1] + ((laplacian_7[4][3])) * arr2[i + 1][j] + ((laplacian_7[4][4])) * arr2[i + 1][j + 1] + ((laplacian_7[4][5])) * arr2[i + 1][j + 2] + (laplacian_7[4][6]) * arr2[i + 1][j + 3] + (laplacian_7[5][0]) * arr2[i + 2][j - 3] + ((laplacian_7[5][1])) * arr2[i + 2][j - 2] + ((laplacian_7[5][2])) * arr2[i + 2][j - 1] + ((laplacian_7[5][3])) * arr2[i + 2][j - 0] + ((laplacian_7[5][4])) * arr2[i + 2][j + 1] + ((laplacian_7[5][5])) * arr2[i + 2][j + 2] + (laplacian_7[5][6]) * arr2[i + 2][j + 3] + (laplacian_7[6][0]) * arr2[i + 3][j - 3] + (laplacian_7[6][1]) * arr2[i + 3][j - 2] + (laplacian_7[6][2]) * arr2[i + 3][j - 1] + (laplacian_7[6][3]) * arr2[i + 3][j - 0] + (laplacian_7[6][4]) * arr2[i + 3][j + 1] + (laplacian_7[6][5]) * arr2[i + 3][j + 2] + (laplacian_7[6][6]) * arr2[i + 3][j + 3];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_x7(Mat img, vector<vector<int>>arr2)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (sobel_H_7[0][0]) * arr2[i - 3][j - 3] + (sobel_H_7[0][1]) * arr2[i - 3][j - 2] + (sobel_H_7[0][2]) * arr2[i - 3][j - 1] + (sobel_H_7[0][3]) * arr2[i - 3][j - 0] + (sobel_H_7[0][4]) * arr2[i - 3][j + 1] + (sobel_H_7[0][5]) * arr2[i - 3][j + 2] + (sobel_H_7[0][6]) * arr2[i - 3][j + 3] + (sobel_H_7[1][0]) * arr2[i - 2][j - 3] + ((sobel_H_7[1][1])) * arr2[i - 2][j - 2] + ((sobel_H_7[1][2])) * arr2[i - 2][j - 1] + ((sobel_H_7[1][3])) * arr2[i - 2][j - 0] + ((sobel_H_7[1][4])) * arr2[i - 2][j + 1] + ((sobel_H_7[1][5])) * arr2[i - 2][j + 2] + (sobel_H_7[1][6]) * arr2[i - 2][j + 3] + (sobel_H_7[2][0]) * arr2[i - 1][j - 3] + ((sobel_H_7[2][1])) * arr2[i - 1][j - 2] + ((sobel_H_7[2][2])) * arr2[i - 1][j - 1] + ((sobel_H_7[2][3])) * arr2[i - 1][j] + ((sobel_H_7[2][4])) * arr2[i - 1][j + 1] + ((sobel_H_7[2][5])) * arr2[i - 1][j + 2] + (sobel_H_7[2][6]) * arr2[i - 1][j + 3] + (sobel_H_7[3][0]) * arr2[i][j - 3] + ((sobel_H_7[3][1])) * arr2[i][j - 2] + ((sobel_H_7[3][2])) * arr2[i][j - 1] + ((sobel_H_7[3][3])) * arr2[i][j] + ((sobel_H_7[3][4])) * arr2[i][j + 1] + ((sobel_H_7[3][5])) * arr2[i][j + 2] + (sobel_H_7[3][6]) * arr2[i][j + 3] + (sobel_H_7[4][0]) * arr2[i + 1][j - 3] + ((sobel_H_7[4][1])) * arr2[i + 1][j - 2] + ((sobel_H_7[4][2])) * arr2[i + 1][j - 1] + ((sobel_H_7[4][3])) * arr2[i + 1][j] + ((sobel_H_7[4][4])) * arr2[i + 1][j + 1] + ((sobel_H_7[4][5])) * arr2[i + 1][j + 2] + (sobel_H_7[4][6]) * arr2[i + 1][j + 3] + (sobel_H_7[5][0]) * arr2[i + 2][j - 3] + ((sobel_H_7[5][1])) * arr2[i + 2][j - 2] + ((sobel_H_7[5][2])) * arr2[i + 2][j - 1] + ((sobel_H_7[5][3])) * arr2[i + 2][j - 0] + ((sobel_H_7[5][4])) * arr2[i + 2][j + 1] + ((sobel_H_7[5][5])) * arr2[i + 2][j + 2] + (sobel_H_7[5][6]) * arr2[i + 2][j + 3] + (sobel_H_7[6][0]) * arr2[i + 3][j - 3] + (sobel_H_7[6][1]) * arr2[i + 3][j - 2] + (sobel_H_7[6][2]) * arr2[i + 3][j - 1] + (sobel_H_7[6][3]) * arr2[i + 3][j - 0] + (sobel_H_7[6][4]) * arr2[i + 3][j + 1] + (sobel_H_7[6][5]) * arr2[i + 3][j + 2] + (sobel_H_7[6][6]) * arr2[i + 3][j + 3];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_y7(Mat img, vector<vector<int>>arr2)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (sobel_V_7[0][0]) * arr2[i - 3][j - 3] + (sobel_V_7[0][1]) * arr2[i - 3][j - 2] + (sobel_V_7[0][2]) * arr2[i - 3][j - 1] + (sobel_V_7[0][3]) * arr2[i - 3][j - 0] + (sobel_V_7[0][4]) * arr2[i - 3][j + 1] + (sobel_V_7[0][5]) * arr2[i - 3][j + 2] + (sobel_V_7[0][6]) * arr2[i - 3][j + 3] + (sobel_V_7[1][0]) * arr2[i - 2][j - 3] + ((sobel_V_7[1][1])) * arr2[i - 2][j - 2] + ((sobel_V_7[1][2])) * arr2[i - 2][j - 1] + ((sobel_V_7[1][3])) * arr2[i - 2][j - 0] + ((sobel_V_7[1][4])) * arr2[i - 2][j + 1] + ((sobel_V_7[1][5])) * arr2[i - 2][j + 2] + (sobel_V_7[1][6]) * arr2[i - 2][j + 3] + (sobel_V_7[2][0]) * arr2[i - 1][j - 3] + ((sobel_V_7[2][1])) * arr2[i - 1][j - 2] + ((sobel_V_7[2][2])) * arr2[i - 1][j - 1] + ((sobel_V_7[2][3])) * arr2[i - 1][j] + ((sobel_V_7[2][4])) * arr2[i - 1][j + 1] + ((sobel_V_7[2][5])) * arr2[i - 1][j + 2] + (sobel_V_7[2][6]) * arr2[i - 1][j + 3] + (sobel_V_7[3][0]) * arr2[i][j - 3] + ((sobel_V_7[3][1])) * arr2[i][j - 2] + ((sobel_V_7[3][2])) * arr2[i][j - 1] + ((sobel_V_7[3][3])) * arr2[i][j] + ((sobel_V_7[3][4])) * arr2[i][j + 1] + ((sobel_V_7[3][5])) * arr2[i][j + 2] + (sobel_V_7[3][6]) * arr2[i][j + 3] + (sobel_V_7[4][0]) * arr2[i + 1][j - 3] + ((sobel_V_7[4][1])) * arr2[i + 1][j - 2] + ((sobel_V_7[4][2])) * arr2[i + 1][j - 1] + ((sobel_V_7[4][3])) * arr2[i + 1][j] + ((sobel_V_7[4][4])) * arr2[i + 1][j + 1] + ((sobel_V_7[4][5])) * arr2[i + 1][j + 2] + (sobel_V_7[4][6]) * arr2[i + 1][j + 3] + (sobel_V_7[5][0]) * arr2[i + 2][j - 3] + ((sobel_V_7[5][1])) * arr2[i + 2][j - 2] + ((sobel_V_7[5][2])) * arr2[i + 2][j - 1] + ((sobel_V_7[5][3])) * arr2[i + 2][j - 0] + ((sobel_V_7[5][4])) * arr2[i + 2][j + 1] + ((sobel_V_7[5][5])) * arr2[i + 2][j + 2] + (sobel_V_7[5][6]) * arr2[i + 2][j + 3] + (sobel_V_7[6][0]) * arr2[i + 3][j - 3] + (sobel_V_7[6][1]) * arr2[i + 3][j - 2] + (sobel_V_7[6][2]) * arr2[i + 3][j - 1] + (sobel_V_7[6][3]) * arr2[i + 3][j - 0] + (sobel_V_7[6][4]) * arr2[i + 3][j + 1] + (sobel_V_7[6][5]) * arr2[i + 3][j + 2] + (sobel_V_7[6][6]) * arr2[i + 3][j + 3];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat lapgaussian7(Mat img, vector<vector<int>>arr2)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (laplacianOfGaussian_7[0][0]) * arr2[i - 3][j - 3] + (laplacianOfGaussian_7[0][1]) * arr2[i - 3][j - 2] + (laplacianOfGaussian_7[0][2]) * arr2[i - 3][j - 1] + (laplacianOfGaussian_7[0][3]) * arr2[i - 3][j - 0] + (laplacianOfGaussian_7[0][4]) * arr2[i - 3][j + 1] + (laplacianOfGaussian_7[0][5]) * arr2[i - 3][j + 2] + (laplacianOfGaussian_7[0][6]) * arr2[i - 3][j + 3] + (laplacianOfGaussian_7[1][0]) * arr2[i - 2][j - 3] + ((laplacianOfGaussian_7[1][1])) * arr2[i - 2][j - 2] + ((laplacianOfGaussian_7[1][2])) * arr2[i - 2][j - 1] + ((laplacianOfGaussian_7[1][3])) * arr2[i - 2][j - 0] + ((laplacianOfGaussian_7[1][4])) * arr2[i - 2][j + 1] + ((laplacianOfGaussian_7[1][5])) * arr2[i - 2][j + 2] + (laplacianOfGaussian_7[1][6]) * arr2[i - 2][j + 3] + (laplacianOfGaussian_7[2][0]) * arr2[i - 1][j - 3] + ((laplacianOfGaussian_7[2][1])) * arr2[i - 1][j - 2] + ((laplacianOfGaussian_7[2][2])) * arr2[i - 1][j - 1] + ((laplacianOfGaussian_7[2][3])) * arr2[i - 1][j] + ((laplacianOfGaussian_7[2][4])) * arr2[i - 1][j + 1] + ((laplacianOfGaussian_7[2][5])) * arr2[i - 1][j + 2] + (laplacianOfGaussian_7[2][6]) * arr2[i - 1][j + 3] + (laplacianOfGaussian_7[3][0]) * arr2[i][j - 3] + ((laplacianOfGaussian_7[3][1])) * arr2[i][j - 2] + ((laplacianOfGaussian_7[3][2])) * arr2[i][j - 1] + ((laplacianOfGaussian_7[3][3])) * arr2[i][j] + ((laplacianOfGaussian_7[3][4])) * arr2[i][j + 1] + ((laplacianOfGaussian_7[3][5])) * arr2[i][j + 2] + (laplacianOfGaussian_7[3][6]) * arr2[i][j + 3] + (laplacianOfGaussian_7[4][0]) * arr2[i + 1][j - 3] + ((laplacianOfGaussian_7[4][1])) * arr2[i + 1][j - 2] + ((laplacianOfGaussian_7[4][2])) * arr2[i + 1][j - 1] + ((laplacianOfGaussian_7[4][3])) * arr2[i + 1][j] + ((laplacianOfGaussian_7[4][4])) * arr2[i + 1][j + 1] + ((laplacianOfGaussian_7[4][5])) * arr2[i + 1][j + 2] + (laplacianOfGaussian_7[4][6]) * arr2[i + 1][j + 3] + (laplacianOfGaussian_7[5][0]) * arr2[i + 2][j - 3] + ((laplacianOfGaussian_7[5][1])) * arr2[i + 2][j - 2] + ((laplacianOfGaussian_7[5][2])) * arr2[i + 2][j - 1] + ((laplacianOfGaussian_7[5][3])) * arr2[i + 2][j - 0] + ((laplacianOfGaussian_7[5][4])) * arr2[i + 2][j + 1] + ((laplacianOfGaussian_7[5][5])) * arr2[i + 2][j + 2] + (laplacianOfGaussian_7[5][6]) * arr2[i + 2][j + 3] + (laplacianOfGaussian_7[6][0]) * arr2[i + 3][j - 3] + (laplacianOfGaussian_7[6][1]) * arr2[i + 3][j - 2] + (laplacianOfGaussian_7[6][2]) * arr2[i + 3][j - 1] + (laplacianOfGaussian_7[6][3]) * arr2[i + 3][j - 0] + (laplacianOfGaussian_7[6][4]) * arr2[i + 3][j + 1] + (laplacianOfGaussian_7[6][5]) * arr2[i + 3][j + 2] + (laplacianOfGaussian_7[6][6]) * arr2[i + 3][j + 3];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat gaussian7(Mat img, vector<vector<int>>arr2)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (gaussian_7[0][0]) * arr2[i - 3][j - 3] + (gaussian_7[0][1]) * arr2[i - 3][j - 2] + (gaussian_7[0][2]) * arr2[i - 3][j - 1] + (gaussian_7[0][3]) * arr2[i - 3][j - 0] + (gaussian_7[0][4]) * arr2[i - 3][j + 1] + (gaussian_7[0][5]) * arr2[i - 3][j + 2] + (gaussian_7[0][6]) * arr2[i - 3][j + 3] + (gaussian_7[1][0]) * arr2[i - 2][j - 3] + ((gaussian_7[1][1])) * arr2[i - 2][j - 2] + ((gaussian_7[1][2])) * arr2[i - 2][j - 1] + ((gaussian_7[1][3])) * arr2[i - 2][j - 0] + ((gaussian_7[1][4])) * arr2[i - 2][j + 1] + ((gaussian_7[1][5])) * arr2[i - 2][j + 2] + (gaussian_7[1][6]) * arr2[i - 2][j + 3] + (gaussian_7[2][0]) * arr2[i - 1][j - 3] + ((gaussian_7[2][1])) * arr2[i - 1][j - 2] + ((gaussian_7[2][2])) * arr2[i - 1][j - 1] + ((gaussian_7[2][3])) * arr2[i - 1][j] + ((gaussian_7[2][4])) * arr2[i - 1][j + 1] + ((gaussian_7[2][5])) * arr2[i - 1][j + 2] + (gaussian_7[2][6]) * arr2[i - 1][j + 3] + (gaussian_7[3][0]) * arr2[i][j - 3] + ((gaussian_7[3][1])) * arr2[i][j - 2] + ((gaussian_7[3][2])) * arr2[i][j - 1] + ((gaussian_7[3][3])) * arr2[i][j] + ((gaussian_7[3][4])) * arr2[i][j + 1] + ((gaussian_7[3][5])) * arr2[i][j + 2] + (gaussian_7[3][6]) * arr2[i][j + 3] + (gaussian_7[4][0]) * arr2[i + 1][j - 3] + ((gaussian_7[4][1])) * arr2[i + 1][j - 2] + ((gaussian_7[4][2])) * arr2[i + 1][j - 1] + ((gaussian_7[4][3])) * arr2[i + 1][j] + ((gaussian_7[4][4])) * arr2[i + 1][j + 1] + ((gaussian_7[4][5])) * arr2[i + 1][j + 2] + (gaussian_7[4][6]) * arr2[i + 1][j + 3] + (gaussian_7[5][0]) * arr2[i + 2][j - 3] + ((gaussian_7[5][1])) * arr2[i + 2][j - 2] + ((gaussian_7[5][2])) * arr2[i + 2][j - 1] + ((gaussian_7[5][3])) * arr2[i + 2][j - 0] + ((gaussian_7[5][4])) * arr2[i + 2][j + 1] + ((gaussian_7[5][5])) * arr2[i + 2][j + 2] + (gaussian_7[5][6]) * arr2[i + 2][j + 3] + (gaussian_7[6][0]) * arr2[i + 3][j - 3] + (gaussian_7[6][1]) * arr2[i + 3][j - 2] + (gaussian_7[6][2]) * arr2[i + 3][j - 1] + (gaussian_7[6][3]) * arr2[i + 3][j - 0] + (gaussian_7[6][4]) * arr2[i + 3][j + 1] + (gaussian_7[6][5]) * arr2[i + 3][j + 2] + (gaussian_7[6][6]) * arr2[i + 3][j + 3];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat gaussian9(Mat img, vector<vector<int>>arr3)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (gaussian_9[0][0]) * arr3[i - 4][j - 4] + (gaussian_9[0][1]) * arr3[i - 4][j - 3] + (gaussian_9[0][2]) * arr3[i - 4][j - 2] + (gaussian_9[0][3]) * arr3[i - 4][j - 1] + (gaussian_9[0][4]) * arr3[i - 4][j - 0] + (gaussian_9[0][5]) * arr3[i - 4][j + 1] + (gaussian_9[0][6]) * arr3[i - 4][j + 2] + (gaussian_9[0][7]) * arr3[i - 4][j + 3] + (gaussian_9[0][8]) * arr3[i - 4][j + 4] + (gaussian_9[1][0]) * arr3[i - 3][j - 4] + (gaussian_9[1][1]) * arr3[i - 3][j - 3] + (gaussian_9[1][2]) * arr3[i - 3][j - 2] + (gaussian_9[1][3]) * arr3[i - 3][j - 1] + (gaussian_9[1][4]) * arr3[i - 3][j - 0] + (gaussian_9[1][5]) * arr3[i - 3][j + 1] + (gaussian_9[1][6]) * arr3[i - 3][j + 2] + (gaussian_9[1][7]) * arr3[i - 3][j + 3] + (gaussian_9[1][8]) * arr3[i - 3][j + 4] + (gaussian_9[2][0]) * arr3[i - 2][j - 4] + (gaussian_9[2][1]) * arr3[i - 2][j - 3] + ((gaussian_9[2][2])) * arr3[i - 2][j - 2] + ((gaussian_9[2][3])) * arr3[i - 2][j - 1] + ((gaussian_9[2][4])) * arr3[i - 2][j - 0] + ((gaussian_9[2][5])) * arr3[i - 2][j + 1] + ((gaussian_9[2][6])) * arr3[i - 2][j + 2] + (gaussian_9[2][7]) * arr3[i - 2][j + 3] + (gaussian_9[2][8]) * arr3[i - 2][j + 4] + (gaussian_9[3][0]) * arr3[i - 1][j - 3] + (gaussian_9[3][1]) * arr3[i - 1][j - 3] + ((gaussian_9[3][2])) * arr3[i - 1][j - 2] + ((gaussian_9[3][3])) * arr3[i - 1][j - 1] + ((gaussian_9[3][4])) * arr3[i - 1][j] + ((gaussian_9[3][5])) * arr3[i - 1][j + 1] + ((gaussian_9[3][6])) * arr3[i - 1][j + 2] + (gaussian_9[3][7]) * arr3[i - 1][j + 3] + (gaussian_9[3][8]) * arr3[i - 1][j + 4] + (gaussian_9[4][0]) * arr3[i][j - 4] + (gaussian_9[4][1]) * arr3[i][j - 3] + ((gaussian_9[4][2])) * arr3[i][j - 2] + ((gaussian_9[4][3])) * arr3[i][j - 1] + ((gaussian_9[4][4])) * arr3[i][j] + ((gaussian_9[4][5])) * arr3[i][j + 1] + ((gaussian_9[4][6])) * arr3[i][j + 2] + (gaussian_9[4][7]) * arr3[i][j + 3] + (gaussian_9[4][8]) * arr3[i][j + 4] + (gaussian_9[5][0]) * arr3[i + 1][j - 4] + (gaussian_9[5][1]) * arr3[i + 1][j - 3] + ((gaussian_9[5][2])) * arr3[i + 1][j - 2] + ((gaussian_9[5][3])) * arr3[i + 1][j - 1] + ((gaussian_9[5][4])) * arr3[i + 1][j] + ((gaussian_9[5][5])) * arr3[i + 1][j + 1] + ((gaussian_9[5][6])) * arr3[i + 1][j + 2] + (gaussian_9[5][7]) * arr3[i + 1][j + 3] + (gaussian_9[5][8]) * arr3[i + 1][j + 4] + (gaussian_9[6][0]) * arr3[i + 2][j - 4] + (gaussian_9[6][1]) * arr3[i + 2][j - 3] + ((gaussian_9[6][2])) * arr3[i + 2][j - 2] + ((gaussian_9[6][3])) * arr3[i + 2][j - 1] + ((gaussian_9[6][4])) * arr3[i + 2][j - 0] + ((gaussian_9[6][5])) * arr3[i + 2][j + 1] + ((gaussian_9[6][6])) * arr3[i + 2][j + 2] + (gaussian_9[6][7]) * arr3[i + 2][j + 3] + (gaussian_9[6][8]) * arr3[i + 2][j + 4] + (gaussian_9[7][0]) * arr3[i + 3][j - 4] + (gaussian_9[7][1]) * arr3[i + 3][j - 3] + (gaussian_9[7][2]) * arr3[i + 3][j - 2] + (gaussian_9[7][3]) * arr3[i + 3][j - 1] + (gaussian_9[7][4]) * arr3[i + 3][j - 0] + (gaussian_9[7][5]) * arr3[i + 3][j + 1] + (gaussian_9[7][6]) * arr3[i + 3][j + 2] + (gaussian_9[7][7]) * arr3[i + 3][j + 3] + (gaussian_9[7][8]) * arr3[i + 3][j + 4] + (gaussian_9[8][0]) * arr3[i + 4][j - 4] + (gaussian_9[8][1]) * arr3[i + 4][j - 3] + (gaussian_9[8][2]) * arr3[i + 4][j - 2] + (gaussian_9[8][3]) * arr3[i + 4][j - 1] + (gaussian_9[8][4]) * arr3[i + 4][j - 0] + (gaussian_9[8][5]) * arr3[i + 4][j + 1] + (gaussian_9[8][6]) * arr3[i + 4][j + 2] + (gaussian_9[8][7]) * arr3[i + 4][j + 3] + (gaussian_9[8][8]) * arr3[i + 4][j + 4];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_x9(Mat img, vector<vector<int>>arr3)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (sobel_H_9[0][0]) * arr3[i - 4][j - 4] + (sobel_H_9[0][1]) * arr3[i - 4][j - 3] + (sobel_H_9[0][2]) * arr3[i - 4][j - 2] + (sobel_H_9[0][3]) * arr3[i - 4][j - 1] + (sobel_H_9[0][4]) * arr3[i - 4][j - 0] + (sobel_H_9[0][5]) * arr3[i - 4][j + 1] + (sobel_H_9[0][6]) * arr3[i - 4][j + 2] + (sobel_H_9[0][7]) * arr3[i - 4][j + 3] + (sobel_H_9[0][8]) * arr3[i - 4][j + 4] + (sobel_H_9[1][0]) * arr3[i - 3][j - 4] + (sobel_H_9[1][1]) * arr3[i - 3][j - 3] + (sobel_H_9[1][2]) * arr3[i - 3][j - 2] + (sobel_H_9[1][3]) * arr3[i - 3][j - 1] + (sobel_H_9[1][4]) * arr3[i - 3][j - 0] + (sobel_H_9[1][5]) * arr3[i - 3][j + 1] + (sobel_H_9[1][6]) * arr3[i - 3][j + 2] + (sobel_H_9[1][7]) * arr3[i - 3][j + 3] + (sobel_H_9[1][8]) * arr3[i - 3][j + 4] + (sobel_H_9[2][0]) * arr3[i - 2][j - 4] + (sobel_H_9[2][1]) * arr3[i - 2][j - 3] + ((sobel_H_9[2][2])) * arr3[i - 2][j - 2] + ((sobel_H_9[2][3])) * arr3[i - 2][j - 1] + ((sobel_H_9[2][4])) * arr3[i - 2][j - 0] + ((sobel_H_9[2][5])) * arr3[i - 2][j + 1] + ((sobel_H_9[2][6])) * arr3[i - 2][j + 2] + (sobel_H_9[2][7]) * arr3[i - 2][j + 3] + (sobel_H_9[2][8]) * arr3[i - 2][j + 4] + (sobel_H_9[3][0]) * arr3[i - 1][j - 3] + (sobel_H_9[3][1]) * arr3[i - 1][j - 3] + ((sobel_H_9[3][2])) * arr3[i - 1][j - 2] + ((sobel_H_9[3][3])) * arr3[i - 1][j - 1] + ((sobel_H_9[3][4])) * arr3[i - 1][j] + ((sobel_H_9[3][5])) * arr3[i - 1][j + 1] + ((sobel_H_9[3][6])) * arr3[i - 1][j + 2] + (sobel_H_9[3][7]) * arr3[i - 1][j + 3] + (sobel_H_9[3][8]) * arr3[i - 1][j + 4] + (sobel_H_9[4][0]) * arr3[i][j - 4] + (sobel_H_9[4][1]) * arr3[i][j - 3] + ((sobel_H_9[4][2])) * arr3[i][j - 2] + ((sobel_H_9[4][3])) * arr3[i][j - 1] + ((sobel_H_9[4][4])) * arr3[i][j] + ((sobel_H_9[4][5])) * arr3[i][j + 1] + ((sobel_H_9[4][6])) * arr3[i][j + 2] + (sobel_H_9[4][7]) * arr3[i][j + 3] + (sobel_H_9[4][8]) * arr3[i][j + 4] + (sobel_H_9[5][0]) * arr3[i + 1][j - 4] + (sobel_H_9[5][1]) * arr3[i + 1][j - 3] + ((sobel_H_9[5][2])) * arr3[i + 1][j - 2] + ((sobel_H_9[5][3])) * arr3[i + 1][j - 1] + ((sobel_H_9[5][4])) * arr3[i + 1][j] + ((sobel_H_9[5][5])) * arr3[i + 1][j + 1] + ((sobel_H_9[5][6])) * arr3[i + 1][j + 2] + (sobel_H_9[5][7]) * arr3[i + 1][j + 3] + (sobel_H_9[5][8]) * arr3[i + 1][j + 4] + (sobel_H_9[6][0]) * arr3[i + 2][j - 4] + (sobel_H_9[6][1]) * arr3[i + 2][j - 3] + ((sobel_H_9[6][2])) * arr3[i + 2][j - 2] + ((sobel_H_9[6][3])) * arr3[i + 2][j - 1] + ((sobel_H_9[6][4])) * arr3[i + 2][j - 0] + ((sobel_H_9[6][5])) * arr3[i + 2][j + 1] + ((sobel_H_9[6][6])) * arr3[i + 2][j + 2] + (sobel_H_9[6][7]) * arr3[i + 2][j + 3] + (sobel_H_9[6][8]) * arr3[i + 2][j + 4] + (sobel_H_9[7][0]) * arr3[i + 3][j - 4] + (sobel_H_9[7][1]) * arr3[i + 3][j - 3] + (sobel_H_9[7][2]) * arr3[i + 3][j - 2] + (sobel_H_9[7][3]) * arr3[i + 3][j - 1] + (sobel_H_9[7][4]) * arr3[i + 3][j - 0] + (sobel_H_9[7][5]) * arr3[i + 3][j + 1] + (sobel_H_9[7][6]) * arr3[i + 3][j + 2] + (sobel_H_9[7][7]) * arr3[i + 3][j + 3] + (sobel_H_9[7][8]) * arr3[i + 3][j + 4] + (sobel_H_9[8][0]) * arr3[i + 4][j - 4] + (sobel_H_9[8][1]) * arr3[i + 4][j - 3] + (sobel_H_9[8][2]) * arr3[i + 4][j - 2] + (sobel_H_9[8][3]) * arr3[i + 4][j - 1] + (sobel_H_9[8][4]) * arr3[i + 4][j - 0] + (sobel_H_9[8][5]) * arr3[i + 4][j + 1] + (sobel_H_9[8][6]) * arr3[i + 4][j + 2] + (sobel_H_9[8][7]) * arr3[i + 4][j + 3] + (sobel_H_9[8][8]) * arr3[i + 4][j + 4];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat laplasian9(Mat img, vector<vector<int>>arr3)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (laplacian_9[0][0]) * arr3[i - 4][j - 4] + (laplacian_9[0][1]) * arr3[i - 4][j - 3] + (laplacian_9[0][2]) * arr3[i - 4][j - 2] + (laplacian_9[0][3]) * arr3[i - 4][j - 1] + (laplacian_9[0][4]) * arr3[i - 4][j - 0] + (laplacian_9[0][5]) * arr3[i - 4][j + 1] + (gaussian_9[0][6]) * arr3[i - 4][j + 2] + (gaussian_9[0][7]) * arr3[i - 4][j + 3] + (laplacian_9[0][8]) * arr3[i - 4][j + 4] + (laplacian_9[1][0]) * arr3[i - 3][j - 4] + (laplacian_9[1][1]) * arr3[i - 3][j - 3] + (laplacian_9[1][2]) * arr3[i - 3][j - 2] + (laplacian_9[1][3]) * arr3[i - 3][j - 1] + (laplacian_9[1][4]) * arr3[i - 3][j - 0] + (laplacian_9[1][5]) * arr3[i - 3][j + 1] + (laplacian_9[1][6]) * arr3[i - 3][j + 2] + (laplacian_9[1][7]) * arr3[i - 3][j + 3] + (laplacian_9[1][8]) * arr3[i - 3][j + 4] + (laplacian_9[2][0]) * arr3[i - 2][j - 4] + (laplacian_9[2][1]) * arr3[i - 2][j - 3] + ((laplacian_9[2][2])) * arr3[i - 2][j - 2] + ((laplacian_9[2][3])) * arr3[i - 2][j - 1] + ((laplacian_9[2][4])) * arr3[i - 2][j - 0] + ((laplacian_9[2][5])) * arr3[i - 2][j + 1] + ((laplacian_9[2][6])) * arr3[i - 2][j + 2] + (laplacian_9[2][7]) * arr3[i - 2][j + 3] + (laplacian_9[2][8]) * arr3[i - 2][j + 4] + (laplacian_9[3][0]) * arr3[i - 1][j - 3] + (laplacian_9[3][1]) * arr3[i - 1][j - 3] + ((laplacian_9[3][2])) * arr3[i - 1][j - 2] + ((laplacian_9[3][3])) * arr3[i - 1][j - 1] + ((laplacian_9[3][4])) * arr3[i - 1][j] + ((laplacian_9[3][5])) * arr3[i - 1][j + 1] + ((laplacian_9[3][6])) * arr3[i - 1][j + 2] + (laplacian_9[3][7]) * arr3[i - 1][j + 3] + (laplacian_9[3][8]) * arr3[i - 1][j + 4] + (laplacian_9[4][0]) * arr3[i][j - 4] + (laplacian_9[4][1]) * arr3[i][j - 3] + ((laplacian_9[4][2])) * arr3[i][j - 2] + ((laplacian_9[4][3])) * arr3[i][j - 1] + ((laplacian_9[4][4])) * arr3[i][j] + ((laplacian_9[4][5])) * arr3[i][j + 1] + ((laplacian_9[4][6])) * arr3[i][j + 2] + (laplacian_9[4][7]) * arr3[i][j + 3] + (laplacian_9[4][8]) * arr3[i][j + 4] + (laplacian_9[5][0]) * arr3[i + 1][j - 4] + (laplacian_9[5][1]) * arr3[i + 1][j - 3] + ((laplacian_9[5][2])) * arr3[i + 1][j - 2] + ((laplacian_9[5][3])) * arr3[i + 1][j - 1] + ((laplacian_9[5][4])) * arr3[i + 1][j] + ((laplacian_9[5][5])) * arr3[i + 1][j + 1] + ((laplacian_9[5][6])) * arr3[i + 1][j + 2] + (laplacian_9[5][7]) * arr3[i + 1][j + 3] + (laplacian_9[5][8]) * arr3[i + 1][j + 4] + (laplacian_9[6][0]) * arr3[i + 2][j - 4] + (laplacian_9[6][1]) * arr3[i + 2][j - 3] + ((laplacian_9[6][2])) * arr3[i + 2][j - 2] + ((laplacian_9[6][3])) * arr3[i + 2][j - 1] + ((laplacian_9[6][4])) * arr3[i + 2][j - 0] + ((laplacian_9[6][5])) * arr3[i + 2][j + 1] + ((laplacian_9[6][6])) * arr3[i + 2][j + 2] + (laplacian_9[6][7]) * arr3[i + 2][j + 3] + (laplacian_9[6][8]) * arr3[i + 2][j + 4] + (laplacian_9[7][0]) * arr3[i + 3][j - 4] + (laplacian_9[7][1]) * arr3[i + 3][j - 3] + (laplacian_9[7][2]) * arr3[i + 3][j - 2] + (laplacian_9[7][3]) * arr3[i + 3][j - 1] + (laplacian_9[7][4]) * arr3[i + 3][j - 0] + (laplacian_9[7][5]) * arr3[i + 3][j + 1] + (laplacian_9[7][6]) * arr3[i + 3][j + 2] + (laplacian_9[7][7]) * arr3[i + 3][j + 3] + (laplacian_9[7][8]) * arr3[i + 3][j + 4] + (laplacian_9[8][0]) * arr3[i + 4][j - 4] + (laplacian_9[8][1]) * arr3[i + 4][j - 3] + (laplacian_9[8][2]) * arr3[i + 4][j - 2] + (laplacian_9[8][3]) * arr3[i + 4][j - 1] + (laplacian_9[8][4]) * arr3[i + 4][j - 0] + (laplacian_9[8][5]) * arr3[i + 4][j + 1] + (laplacian_9[8][6]) * arr3[i + 4][j + 2] + (laplacian_9[8][7]) * arr3[i + 4][j + 3] + (laplacian_9[8][8]) * arr3[i + 4][j + 4];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_y9(Mat img, vector<vector<int>>arr3)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (sobel_V_9[0][0]) * arr3[i - 4][j - 4] + (sobel_V_9[0][1]) * arr3[i - 4][j - 3] + (sobel_V_9[0][2]) * arr3[i - 4][j - 2] + (sobel_V_9[0][3]) * arr3[i - 4][j - 1] + (sobel_V_9[0][4]) * arr3[i - 4][j - 0] + (sobel_V_9[0][5]) * arr3[i - 4][j + 1] + (sobel_V_9[0][6]) * arr3[i - 4][j + 2] + (sobel_V_9[0][7]) * arr3[i - 4][j + 3] + (sobel_V_9[0][8]) * arr3[i - 4][j + 4] + (sobel_V_9[1][0]) * arr3[i - 3][j - 4] + (sobel_V_9[1][1]) * arr3[i - 3][j - 3] + (sobel_V_9[1][2]) * arr3[i - 3][j - 2] + (sobel_V_9[1][3]) * arr3[i - 3][j - 1] + (sobel_V_9[1][4]) * arr3[i - 3][j - 0] + (sobel_V_9[1][5]) * arr3[i - 3][j + 1] + (sobel_V_9[1][6]) * arr3[i - 3][j + 2] + (sobel_V_9[1][7]) * arr3[i - 3][j + 3] + (sobel_V_9[1][8]) * arr3[i - 3][j + 4] + (sobel_V_9[2][0]) * arr3[i - 2][j - 4] + (sobel_V_9[2][1]) * arr3[i - 2][j - 3] + ((sobel_V_9[2][2])) * arr3[i - 2][j - 2] + ((sobel_V_9[2][3])) * arr3[i - 2][j - 1] + ((sobel_V_9[2][4])) * arr3[i - 2][j - 0] + ((sobel_V_9[2][5])) * arr3[i - 2][j + 1] + ((sobel_V_9[2][6])) * arr3[i - 2][j + 2] + (sobel_V_9[2][7]) * arr3[i - 2][j + 3] + (sobel_V_9[2][8]) * arr3[i - 2][j + 4] + (sobel_V_9[3][0]) * arr3[i - 1][j - 3] + (sobel_V_9[3][1]) * arr3[i - 1][j - 3] + ((sobel_V_9[3][2])) * arr3[i - 1][j - 2] + ((sobel_V_9[3][3])) * arr3[i - 1][j - 1] + ((sobel_V_9[3][4])) * arr3[i - 1][j] + ((sobel_V_9[3][5])) * arr3[i - 1][j + 1] + ((sobel_V_9[3][6])) * arr3[i - 1][j + 2] + (sobel_V_9[3][7]) * arr3[i - 1][j + 3] + (sobel_V_9[3][8]) * arr3[i - 1][j + 4] + (sobel_V_9[4][0]) * arr3[i][j - 4] + (sobel_V_9[4][1]) * arr3[i][j - 3] + ((sobel_V_9[4][2])) * arr3[i][j - 2] + ((sobel_V_9[4][3])) * arr3[i][j - 1] + ((sobel_V_9[4][4])) * arr3[i][j] + ((sobel_V_9[4][5])) * arr3[i][j + 1] + ((sobel_V_9[4][6])) * arr3[i][j + 2] + (sobel_V_9[4][7]) * arr3[i][j + 3] + (sobel_V_9[4][8]) * arr3[i][j + 4] + (sobel_V_9[5][0]) * arr3[i + 1][j - 4] + (sobel_V_9[5][1]) * arr3[i + 1][j - 3] + ((sobel_V_9[5][2])) * arr3[i + 1][j - 2] + ((sobel_V_9[5][3])) * arr3[i + 1][j - 1] + ((sobel_V_9[5][4])) * arr3[i + 1][j] + ((sobel_V_9[5][5])) * arr3[i + 1][j + 1] + ((sobel_V_9[5][6])) * arr3[i + 1][j + 2] + (sobel_V_9[5][7]) * arr3[i + 1][j + 3] + (sobel_V_9[5][8]) * arr3[i + 1][j + 4] + (sobel_V_9[6][0]) * arr3[i + 2][j - 4] + (sobel_V_9[6][1]) * arr3[i + 2][j - 3] + ((sobel_V_9[6][2])) * arr3[i + 2][j - 2] + ((sobel_V_9[6][3])) * arr3[i + 2][j - 1] + ((sobel_V_9[6][4])) * arr3[i + 2][j - 0] + ((sobel_V_9[6][5])) * arr3[i + 2][j + 1] + ((sobel_V_9[6][6])) * arr3[i + 2][j + 2] + (sobel_V_9[6][7]) * arr3[i + 2][j + 3] + (sobel_V_9[6][8]) * arr3[i + 2][j + 4] + (sobel_V_9[7][0]) * arr3[i + 3][j - 4] + (sobel_V_9[7][1]) * arr3[i + 3][j - 3] + (sobel_V_9[7][2]) * arr3[i + 3][j - 2] + (sobel_V_9[7][3]) * arr3[i + 3][j - 1] + (sobel_V_9[7][4]) * arr3[i + 3][j - 0] + (sobel_V_9[7][5]) * arr3[i + 3][j + 1] + (sobel_V_9[7][6]) * arr3[i + 3][j + 2] + (sobel_V_9[7][7]) * arr3[i + 3][j + 3] + (sobel_V_9[7][8]) * arr3[i + 3][j + 4] + (sobel_V_9[8][0]) * arr3[i + 4][j - 4] + (sobel_V_9[8][1]) * arr3[i + 4][j - 3] + (sobel_V_9[8][2]) * arr3[i + 4][j - 2] + (sobel_V_9[8][3]) * arr3[i + 4][j - 1] + (sobel_V_9[8][4]) * arr3[i + 4][j - 0] + (sobel_V_9[8][5]) * arr3[i + 4][j + 1] + (sobel_V_9[8][6]) * arr3[i + 4][j + 2] + (sobel_V_9[8][7]) * arr3[i + 4][j + 3] + (sobel_V_9[8][8]) * arr3[i + 4][j + 4];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat lapgaussian9(Mat img, vector<vector<int>>arr3)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{

			int val = (laplacianOfGaussian_9[0][0]) * arr3[i - 4][j - 4] + (laplacianOfGaussian_9[0][1]) * arr3[i - 4][j - 3] + (laplacianOfGaussian_9[0][2]) * arr3[i - 4][j - 2] + (laplacianOfGaussian_9[0][3]) * arr3[i - 4][j - 1] + (laplacianOfGaussian_9[0][4]) * arr3[i - 4][j - 0] + (laplacianOfGaussian_9[0][5]) * arr3[i - 4][j + 1] + (laplacianOfGaussian_9[0][6]) * arr3[i - 4][j + 2] + (laplacianOfGaussian_9[0][7]) * arr3[i - 4][j + 3] + (laplacianOfGaussian_9[0][8]) * arr3[i - 4][j + 4] + (laplacianOfGaussian_9[1][0]) * arr3[i - 3][j - 4] + (laplacianOfGaussian_9[1][1]) * arr3[i - 3][j - 3] + (laplacianOfGaussian_9[1][2]) * arr3[i - 3][j - 2] + (laplacianOfGaussian_9[1][3]) * arr3[i - 3][j - 1] + (laplacianOfGaussian_9[1][4]) * arr3[i - 3][j - 0] + (laplacianOfGaussian_9[1][5]) * arr3[i - 3][j + 1] + (laplacianOfGaussian_9[1][6]) * arr3[i - 3][j + 2] + (laplacianOfGaussian_9[1][7]) * arr3[i - 3][j + 3] + (laplacianOfGaussian_9[1][8]) * arr3[i - 3][j + 4] + (laplacianOfGaussian_9[2][0]) * arr3[i - 2][j - 4] + (laplacianOfGaussian_9[2][1]) * arr3[i - 2][j - 3] + ((laplacianOfGaussian_9[2][2])) * arr3[i - 2][j - 2] + ((laplacianOfGaussian_9[2][3])) * arr3[i - 2][j - 1] + ((laplacianOfGaussian_9[2][4])) * arr3[i - 2][j - 0] + ((laplacianOfGaussian_9[2][5])) * arr3[i - 2][j + 1] + ((laplacianOfGaussian_9[2][6])) * arr3[i - 2][j + 2] + (laplacianOfGaussian_9[2][7]) * arr3[i - 2][j + 3] + (laplacianOfGaussian_9[2][8]) * arr3[i - 2][j + 4] + (laplacianOfGaussian_9[3][0]) * arr3[i - 1][j - 3] + (laplacianOfGaussian_9[3][1]) * arr3[i - 1][j - 3] + ((laplacianOfGaussian_9[3][2])) * arr3[i - 1][j - 2] + ((laplacianOfGaussian_9[3][3])) * arr3[i - 1][j - 1] + ((laplacianOfGaussian_9[3][4])) * arr3[i - 1][j] + ((laplacianOfGaussian_9[3][5])) * arr3[i - 1][j + 1] + ((laplacianOfGaussian_9[3][6])) * arr3[i - 1][j + 2] + (laplacianOfGaussian_9[3][7]) * arr3[i - 1][j + 3] + (laplacianOfGaussian_9[3][8]) * arr3[i - 1][j + 4] + (laplacianOfGaussian_9[4][0]) * arr3[i][j - 4] + (laplacianOfGaussian_9[4][1]) * arr3[i][j - 3] + ((laplacianOfGaussian_9[4][2])) * arr3[i][j - 2] + ((laplacianOfGaussian_9[4][3])) * arr3[i][j - 1] + ((laplacianOfGaussian_9[4][4])) * arr3[i][j] + ((laplacianOfGaussian_9[4][5])) * arr3[i][j + 1] + ((laplacianOfGaussian_9[4][6])) * arr3[i][j + 2] + (laplacianOfGaussian_9[4][7]) * arr3[i][j + 3] + (laplacianOfGaussian_9[4][8]) * arr3[i][j + 4] + (laplacianOfGaussian_9[5][0]) * arr3[i + 1][j - 4] + (laplacianOfGaussian_9[5][1]) * arr3[i + 1][j - 3] + ((laplacianOfGaussian_9[5][2])) * arr3[i + 1][j - 2] + ((laplacianOfGaussian_9[5][3])) * arr3[i + 1][j - 1] + ((laplacianOfGaussian_9[5][4])) * arr3[i + 1][j] + ((laplacianOfGaussian_9[5][5])) * arr3[i + 1][j + 1] + ((laplacianOfGaussian_9[5][6])) * arr3[i + 1][j + 2] + (laplacianOfGaussian_9[5][7]) * arr3[i + 1][j + 3] + (laplacianOfGaussian_9[5][8]) * arr3[i + 1][j + 4] + (laplacianOfGaussian_9[6][0]) * arr3[i + 2][j - 4] + (laplacianOfGaussian_9[6][1]) * arr3[i + 2][j - 3] + ((laplacianOfGaussian_9[6][2])) * arr3[i + 2][j - 2] + ((laplacianOfGaussian_9[6][3])) * arr3[i + 2][j - 1] + ((laplacianOfGaussian_9[6][4])) * arr3[i + 2][j - 0] + ((laplacianOfGaussian_9[6][5])) * arr3[i + 2][j + 1] + ((laplacianOfGaussian_9[6][6])) * arr3[i + 2][j + 2] + (laplacianOfGaussian_9[6][7]) * arr3[i + 2][j + 3] + (laplacianOfGaussian_9[6][8]) * arr3[i + 2][j + 4] + (laplacianOfGaussian_9[7][0]) * arr3[i + 3][j - 4] + (laplacianOfGaussian_9[7][1]) * arr3[i + 3][j - 3] + (laplacianOfGaussian_9[7][2]) * arr3[i + 3][j - 2] + (laplacianOfGaussian_9[7][3]) * arr3[i + 3][j - 1] + (laplacianOfGaussian_9[7][4]) * arr3[i + 3][j - 0] + (laplacianOfGaussian_9[7][5]) * arr3[i + 3][j + 1] + (laplacianOfGaussian_9[7][6]) * arr3[i + 3][j + 2] + (laplacianOfGaussian_9[7][7]) * arr3[i + 3][j + 3] + (laplacianOfGaussian_9[7][8]) * arr3[i + 3][j + 4] + (laplacianOfGaussian_9[8][0]) * arr3[i + 4][j - 4] + (laplacianOfGaussian_9[8][1]) * arr3[i + 4][j - 3] + (laplacianOfGaussian_9[8][2]) * arr3[i + 4][j - 2] + (laplacianOfGaussian_9[8][3]) * arr3[i + 4][j - 1] + (laplacianOfGaussian_9[8][4]) * arr3[i + 4][j - 0] + (laplacianOfGaussian_9[8][5]) * arr3[i + 4][j + 1] + (laplacianOfGaussian_9[8][6]) * arr3[i + 4][j + 2] + (laplacianOfGaussian_9[8][7]) * arr3[i + 4][j + 3] + (laplacianOfGaussian_9[8][8]) * arr3[i + 4][j + 4];
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat mean(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			double val = (arr[i - 1][j - 1] + arr[i - 1][j] + arr[i - 1][j + 1] + arr[i][j - 1] + arr[i][j] + arr[i][j + 1] + arr[i + 1][j - 1] + arr[i + 1][j] + arr[i + 1][j + 1]);
			val = val / 9;
			val = (int)val;
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat median(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			vector<int>v;
			v.push_back(arr[i - 1][j - 1]);
			v.push_back(arr[i - 1][j]);
			v.push_back(arr[i - 1][j + 1]);
			v.push_back(arr[i][j - 1]);
			v.push_back(arr[i][j]);
			v.push_back(arr[i][j + 1]);
			v.push_back(arr[i + 1][j - 1]);
			v.push_back(arr[i + 1][j]);
			v.push_back(arr[i + 1][j + 1]);
			sort(v.begin(), v.end());
			//cout << v[4];

			output.at<uchar>(i, j) = v[4];
		}
	}
	return output;
}

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

Mat laplasian(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			int val = (0 * arr[i - 1][j - 1] + 1 * arr[i - 1][j] + 0 * arr[i - 1][j + 1] + 1 * arr[i][j - 1] + (-4) * arr[i][j] + 1 * arr[i][j + 1] + 0 * arr[i + 1][j - 1] + 1 * arr[i + 1][j] + 0 * arr[i + 1][j + 1]);
			//val = val / 4.8976;

			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_y(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			double val = ((-1) * arr[i - 1][j - 1] + (-2) * arr[i - 1][j] + (-1) * arr[i - 1][j + 1] + (0) * arr[i][j - 1] + (0) * arr[i][j] + 0 * arr[i][j + 1] + (1) * arr[i + 1][j - 1] + 2 * arr[i + 1][j] + 1 * arr[i + 1][j + 1]);
			//val = val / 4.8976;
			val = (int)val;
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_x(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			double val = ((-1) * arr[i - 1][j - 1] + (0) * arr[i - 1][j] + (1) * arr[i - 1][j + 1] + (-2) * arr[i][j - 1] + (0) * arr[i][j] + (2) * arr[i][j + 1] + (-1) * arr[i + 1][j - 1] + (0) * arr[i + 1][j] + (1) * arr[i + 1][j + 1]);
			//val = val / 4.8976;
			val = (int)val;
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

Mat sobel_d(Mat img, vector<vector<int>>arr)
{
	Mat output = img.clone();
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			double val = ((0) * arr[i - 1][j - 1] + (1) * arr[i - 1][j] + (2) * arr[i - 1][j + 1] + (-1) * arr[i][j - 1] + (0) * arr[i][j] + 1 * arr[i][j + 1] + (-2) * arr[i + 1][j - 1] + (-1) * arr[i + 1][j] + (0) * arr[i + 1][j + 1]);
			//val = val / 4.8976;
			val = (int)val;
			output.at<uchar>(i, j) = val;
		}
	}
	return output;
}

int main()
{
	//Mat img = imread("C:/opencv/Cameraman_Salt&Pepper_0.02.jpg",-1);
	Mat img = imread("C:/opencv/lena_gray_512.jpg", -1);
	vector<vector<int>>arr(512 + 2, vector<int>(512 + 2, 0));
	vector<vector<int>>arr1(512 + 4, vector<int>(512 + 4, 0));
	vector<vector<int>>arr2(512 + 6, vector<int>(512 + 6, 0));
	vector<vector<int>>arr3(512 + 8, vector<int>(512 + 8, 0));
	for (int i = 1; i < 512; i++)
	{
		for (int j = 1; j < 512; j++)
		{
			arr[i][j] = img.at<uchar>(i, j);
		}
	}
	for (int i = 2; i < 512; i++)
	{
		for (int j = 2; j < 512; j++)
		{
			arr1[i][j] = img.at<uchar>(i, j);
		}
	}
	for (int i = 3; i < 512; i++)
	{
		for (int j = 3; j < 512; j++)
		{
			arr2[i][j] = img.at<uchar>(i, j);
		}
	}
	for (int i = 4; i < 512; i++)
	{
		for (int j = 4; j < 512; j++)
		{
			arr3[i][j] = img.at<uchar>(i, j);
		}
	}
	Mat output; img.copyTo(output);
	output = lapgaussian9(img, arr3);
	//Sobel(img, output, CV_64F, 1, 1, 5);
	Mat out1, out2;
	out1 = sobel_x(img, arr);
	out2 = sobel_y(img, arr);
	/*for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			output.at<uchar>(i, j) = sqrt((out1.at<uchar>(i, j)) * (out1.at<uchar>(i, j)) * (out2.at<uchar>(i, j)) * (out2.at<uchar>(i, j)));
		}
	}*/
	Mat output1 = sobel_x(img, arr) + sobel_y(img, arr);
	imwrite("C:/opencv/lena_gray_512 - prewitt.jpg", output);
	imshow("h", img);
	waitKey();
	return 0;
}
