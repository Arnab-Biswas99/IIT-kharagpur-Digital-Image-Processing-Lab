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



/***********************************************************************************************************************************************************/

void kernal_for_1(vector<vector<int>> arr, Mat img, int option)
{
    vector<vector<int>> arr_for_padding(img.rows + 2, vector<int>(img.cols + 2, 0));
    for (int i = 1; i < img.rows; i++)
    {
        for (int j = 1; j < img.cols; j++)
        {
            arr_for_padding[i][j] = arr[i][j];
        }
    }
    vector<vector<int>> output(img.rows + 0, vector<int>(img.cols + 0, 0));
    if (option == 1)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i][j-1] == 0 or arr_for_padding[i][j] == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 2)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i][j - 1] == 255 or arr_for_padding[i][j] == 255) output[i][j] = 255;
                else output[i][j] = 0;
            }
        }
    }
    if (option == 3)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i][j - 1] == 0 or arr_for_padding[i][j] == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                output[i][j] = arr_for_padding[i][j];
            }
        }
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i][j - 1] == 255 or arr_for_padding[i][j] == 255) output[i][j] = 255;
                else output[i][j] = 0;
            }
        }
    }
    if (option == 4)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i][j - 1] == 255 or arr_for_padding[i][j] == 255) output[i][j] = 255;
                else output[i][j] = 0;
            }
        }
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                output[i][j] = arr_for_padding[i][j];
            }
        }
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i][j - 1] == 0 or arr_for_padding[i][j] == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    Mat output_img = img.clone();
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            output_img.at<uchar>(i, j) = output[i][j];
        }
    }
    imshow("Output Image", output_img);
}

/***********************************************************************************************************************************************************/

void kernal_for_2(vector<vector<int>> arr, Mat img, int option)
{
    vector<vector<int>> arr_for_padding(img.rows + 2, vector<int>(img.cols + 2, 0));
    for (int i = 1; i < img.rows; i++)
    {
        for (int j = 1; j < img.cols; j++)
        {
            arr_for_padding[i][j] = arr[i][j];
        }
    }
    vector<vector<int>> output(img.rows + 0, vector<int>(img.cols + 0, 0));
    if (option == 1)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i + 1][j + 1] == 255 or arr_for_padding[i + 1][j-1] == 255 or arr_for_padding[i - 1][j+1] == 255 or arr_for_padding[i - 1][j-1] == 255 or arr_for_padding[i + 1][j] == 0 or arr_for_padding[i][j+1] == 0 or arr_for_padding[i][j-1] == 0 or arr_for_padding[i - 1][j] == 0 or arr_for_padding[i][j] == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 2)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i - 1][j] == 255 or arr_for_padding[i][j] == 255) output[i][j] = 255;
                else output[i][j] = 0;
            }
        }
    }
    if (option == 3)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i - 1][j] == 0 or arr_for_padding[i][j] == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                output[i][j] = arr_for_padding[i][j];
            }
        }
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i - 1][j] == 255 or arr_for_padding[i][j] == 255) output[i][j] = 255;
                else output[i][j] = 0;
            }
        }
    }
    if (option == 4)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i - 1][j] == 255 or arr_for_padding[i][j] == 255) output[i][j] = 255;
                else output[i][j] = 0;
            }
        }
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                output[i][j] = arr_for_padding[i][j];
            }
        }
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                if (arr_for_padding[i - 1][j] == 0 or arr_for_padding[i][j] == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    Mat output_img = img.clone();
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            output_img.at<uchar>(i, j) = output[i][j];
        }
    }
    imshow("Output Image", output_img);
}


/**************************************************************************************************************************************************************/

int check(vector<vector<int>> arr_for_padding, int i, int j)
{
    for (int k = i-1; k <= i+1; k++)
    {
        for (int m = j-1; m <= j + 1; m++)
        {
            //cout << k << endl;
            if (arr_for_padding[k][m] == 0) return 0;
        }
    }
    return 1;
}

int check1(vector<vector<int>> arr_for_padding, int i, int j)
{
    for (int k = i - 1; k <= i + 1; k++)
    {
        for (int m = j - 1; m <= j + 1; m++)
        {
            //cout << k << endl;
            if (arr_for_padding[k][m] == 255) return 1;
        }
    }
    return 0;
}

void kernal_for_3(vector<vector<int>> arr,Mat img, int option)
{
    vector<vector<int>> arr_for_padding(img.rows+2, vector<int>(img.cols+2, 0));
    for (int i = 1; i < img.rows; i++)
    {
        for (int j = 1; j < img.cols; j++)
        {
            arr_for_padding[i][j]=arr[i][j];
        }
    }
    vector<vector<int>> output(img.rows + 0, vector<int>(img.cols + 0, 0));
    if (option == 1)
    {
        for (int i = 1; i < img.rows - 2; i++)
        {
            for (int j = 1; j < img.cols - 2; j++)
            {
                if (check(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 2)
    {
        for (int i = 1; i < img.rows - 2; i++)
        {
            for (int j = 1; j < img.cols - 2; j++)
            {
                if (check1(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 3)
    {
        for (int i = 1; i < img.rows - 2; i++)
        {
            for (int j = 1; j < img.cols - 2; j++)
            {
                if (check(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }

        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                arr_for_padding[i][j] = output[i][j];
            }
        }

        for (int i = 1; i < img.rows - 2; i++)
        {
            for (int j = 1; j < img.cols - 2; j++)
            {
                if (check1(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 4)
    {
        for (int i = 1; i < img.rows - 2; i++)
        {
            for (int j = 1; j < img.cols - 2; j++)
            {
                if (check1(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }

        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                arr_for_padding[i][j] = output[i][j];
            }
        }

        for (int i = 1; i < img.rows - 2; i++)
        {
            for (int j = 1; j < img.cols - 2; j++)
            {
                if (check(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    Mat output_img = img.clone();
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            output_img.at<uchar>(i, j) = output[i][j];
        }
    }
    imshow("Output Image", output_img);
}


/*****************************************************************************************************************************************************/

int check3(vector<vector<int>> arr_for_padding, int i, int j)
{
    for (int k = i - 4; k <= i + 4; k++)
    {
        for (int m = j - 4; m <= j + 4; m++)
        {
            //cout << k << endl;
            if (arr_for_padding[k][m] == 0) return 0;
        }
    }
    return 1;
}

int check13(vector<vector<int>> arr_for_padding, int i, int j)
{
    for (int k = i - 4; k <= i + 4; k++)
    {
        for (int m = j - 4; m <= j + 4; m++)
        {
            //cout << k << endl;
            if (arr_for_padding[k][m] == 255) return 1;
        }
    }
    return 0;
}

void kernal_for_4(vector<vector<int>> arr, Mat img, int option)
{
    vector<vector<int>> arr_for_padding(img.rows + 8, vector<int>(img.cols + 8, 0));
    for (int i = 4; i < img.rows; i++)
    {
        for (int j = 4; j < img.cols; j++)
        {
            arr_for_padding[i][j] = arr[i][j];
        }
    }
    vector<vector<int>> output(img.rows + 0, vector<int>(img.cols + 0, 0));
    if (option == 1)
    {
        for (int i = 4; i < img.rows - 4; i++)
        {
            for (int j = 4; j < img.cols - 4; j++)
            {
                if (check3(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 2)
    {
        for (int i = 4; i < img.rows - 4; i++)
        {
            for (int j = 4; j < img.cols - 4; j++)
            {
                if (check13(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 3)
    {
        for (int i = 4; i < img.rows - 4; i++)
        {
            for (int j = 4; j < img.cols - 4; j++)
            {
                if (check3(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }

        for (int i = 4; i < img.rows; i++)
        {
            for (int j = 4; j < img.cols; j++)
            {
                arr_for_padding[i][j] = output[i][j];
            }
        }

        for (int i = 4; i < img.rows - 4; i++)
        {
            for (int j = 4; j < img.cols - 4; j++)
            {
                if (check13(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 4)
    {
        for (int i = 4; i < img.rows - 4; i++)
        {
            for (int j = 4; j < img.cols - 4; j++)
            {
                if (check13(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }

        for (int i = 4; i < img.rows; i++)
        {
            for (int j = 4; j < img.cols; j++)
            {
                arr_for_padding[i][j] = output[i][j];
            }
        }

        for (int i = 4; i < img.rows - 4; i++)
        {
            for (int j = 4; j < img.cols - 4; j++)
            {
                if (check3(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    Mat output_img = img.clone();
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            output_img.at<uchar>(i, j) = output[i][j];
        }
    }
    imshow("Output Image", output_img);
}

/************************************************************************************************************************************************************/

int check2(vector<vector<int>> arr_for_padding, int i, int j)
{
    for (int k = i - 7; k <= i + 7; k++)
    {
        for (int m = j - 7; m <= j + 7; m++)
        {
            //cout << k << endl;
            if (arr_for_padding[k][m] == 0) return 0;
        }
    }
    return 1;
}

int check12(vector<vector<int>> arr_for_padding, int i, int j)
{
    for (int k = i - 7; k <= i + 7; k++)
    {
        for (int m = j - 7; m <= j + 7; m++)
        {
            //cout << k << endl;
            if (arr_for_padding[k][m] == 255) return 1;
        }
    }
    return 0;
}

void kernal_for_5(vector<vector<int>> arr, Mat img, int option)
{
    vector<vector<int>> arr_for_padding(img.rows + 14, vector<int>(img.cols + 14, 0));
    for (int i = 7; i < img.rows; i++)
    {
        for (int j = 7; j < img.cols; j++)
        {
            arr_for_padding[i][j] = arr[i][j];
        }
    }
    vector<vector<int>> output(img.rows + 0, vector<int>(img.cols + 0, 0));
    if (option == 1)
    {
        for (int i = 7; i < img.rows - 7; i++)
        {
            for (int j = 7; j < img.cols - 7; j++)
            {
                if (check2(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 2)
    {
        for (int i = 7; i < img.rows - 7; i++)
        {
            for (int j = 7; j < img.cols - 7; j++)
            {
                if (check12(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 3)
    {
        for (int i = 7; i < img.rows - 7; i++)
        {
            for (int j = 7; j < img.cols - 7; j++)
            {
                if (check2(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }

        for (int i = 7; i < img.rows; i++)
        {
            for (int j = 7; j < img.cols; j++)
            {
                arr_for_padding[i][j] = output[i][j];
            }
        }

        for (int i = 7; i < img.rows - 7; i++)
        {
            for (int j = 7; j < img.cols - 7; j++)
            {
                if (check12(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    if (option == 4)
    {
        for (int i = 7; i < img.rows - 7; i++)
        {
            for (int j = 7; j < img.cols - 7; j++)
            {
                if (check12(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }

        for (int i = 7; i < img.rows; i++)
        {
            for (int j = 7; j < img.cols; j++)
            {
                arr_for_padding[i][j] = output[i][j];
            }
        }

        for (int i = 7; i < img.rows - 7; i++)
        {
            for (int j = 7; j < img.cols - 7; j++)
            {
                if (check2(arr_for_padding, i, j) == 0) output[i][j] = 0;
                else output[i][j] = 255;
            }
        }
    }
    Mat output_img = img.clone();
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            output_img.at<uchar>(i, j) = output[i][j];
        }
    }
    imshow("Output Image", output_img);
}


/*********************************************************************************************************************************************************/
int main()
{
	Mat img = imread("C:/opencv/ricegrains_mono.bmp",-1);
    int option;
    cout << "Select the following options" << endl;
    cout << "   1.  Erode Binary" << endl;
    cout << "   2.  Dilate Binary" << endl;
    cout << "   3.  Open Binary" << endl;
    cout << "   4.  Close Binary" << endl;
    cin >> option;
    int structureOption;
    cout << "Please enter the type of stuctural Element" << endl;
    cout << "   1. A rectangle with of 1x2" << endl;
    cout << "   2. A diamond with all 1 3x3" << endl;
    cout << "   3. A Square with all 1 3x3" << endl;
    cout << "   4. A Square with all 1 9x9" << endl;
    cout << "   5. A Square with all 1 15x15" << endl;
    cin >> structureOption;
	vector<vector<int>> arr(img.rows, vector<int>(img.cols, 0));
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            arr[i][j] = img.at<uchar>(i, j);
        }
    }

    if (structureOption == 1) {
        kernal_for_1(arr, img, option);
        imshow("Input Image", img);
    }
    else if (structureOption == 2) {
        kernal_for_2(arr, img, option);
        imshow("Input Image", img);
    }
    else if (structureOption == 3) {
        kernal_for_3(arr, img, option);
        imshow("Input Image", img);
    }
    else if (structureOption == 4) {
        kernal_for_4(arr, img, option);
        imshow("Input Image", img);
    }
    else if (structureOption == 5) {
        kernal_for_5(arr, img, option);
        imshow("Input Image", img);
    }
	waitKey();
	return 0;
}