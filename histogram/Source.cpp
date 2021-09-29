#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <cmath>
#include <algorithm>
using namespace std;
using namespace cv;
vector<int>create_hist(Mat img)
{
    vector<int>hist;
    hist.resize(256, 0);
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            int val = (int)img.at<uchar>(i, j);
            hist[val]++;
        }
    }
    return hist;
}
vector<double>normalhist(vector<int>hist, double val)
{
    vector<double>nor_hist;

    nor_hist.resize(256, 0);
    for (int i = 0; i < 256; i++)
    {
        nor_hist[i] = hist[i] / val;
    }
    //for (auto x : nor_hist) cout << x << " ";
    return nor_hist;
}
vector<int>sum_all(vector<double>nor_hist)
{
    vector<int>last;
    vector<double>last1;
    last1.resize(256, 0);
    last.resize(256, 0);
    last1[0] = nor_hist[0];
    for (int i = 1; i < 256; i++)
    {
        last1[i] = nor_hist[i] + last1[i - 1];
    }

    for (int i = 0; i < 256; i++)
    {
        last1[i] = last1[i] * 255;
    }
    for (int i = 0; i < 256; i++)
    {
        last[i] = floor(last1[i]);
    }
    //for (auto x : last) cout << x << " ";
    return last;
}
/*
vector<float>histmatching(vector<double>source_cdf, vector<double>target_cdf)
{
    vector<float>histmat;
    int mini = INT_MAX;
    histmat.resize(256, 0);
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            mini = abs(source_cdf[i] - target_cdf[j]);
        }
        histmat[i] = mini;
    }
    return histmat;
}
*/
void showHistogram(Mat& image, string fileName) {

    int bins = 256;    // number of bins
    Mat histogram;     // for storing the histogram
    Mat canvas;		   // for displaying the histogram
    int hmax = 0;      // peak value for each histogram

    histogram = Mat::zeros(1, bins, CV_32SC1);

    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++) {
            uchar val = image.at<uchar>(i, j);
            histogram.at<int>(val) += 1;
        }

    for (int j = 0; j < bins - 1; j++)
        hmax = histogram.at<int>(j) > hmax ? histogram.at<int>(j) : hmax;

    canvas = Mat::ones(125, bins, CV_8UC3);

    for (int j = 0, rows = canvas.rows; j < bins - 1; j++)
        line(canvas, Point(j, rows), Point(j, rows - (histogram.at<int>(j) * rows / hmax)), Scalar(255, 255, 255), 1, 8, 0);

    imshow(fileName, canvas);

}

int main()
{
    Mat img = imread("C:/opencv/cameraman.jpg", -1);
    double val = (double)(img.rows * img.cols);
    if (img.channels() == 1)
    {
        vector<int>hist = create_hist(img);//create and return the histogram array.
        vector<double>nor_hist = normalhist(hist, val);//create normalized histogram
        vector<int>summation = sum_all(nor_hist);//This is equalized histogram
        Mat outputImage = img.clone();
        for (int y = 0; y < img.rows; y++) {
            for (int x = 0; x < img.cols; x++) {
                outputImage.at<uchar>(y, x) = (summation[img.at<uchar>(y, x)]);//create output image
            }
        }
        imshow("H", outputImage);
        //imwrite("C:/opencv/New folder/walkbridge.jpg", outputImage);
        showHistogram(img, " Original Histogram");
        showHistogram(outputImage, " output Histogram");
        waitKey();
    }
    else
    {
        Mat for_RGB;
        cvtColor(img, for_RGB, COLOR_BGR2YCrCb);
        vector<double>yellow_channel;
        yellow_channel.resize(256, 0);
        for (int i = 0; i < for_RGB.rows; i++)
        {
            for (int j = 0; j < for_RGB.cols; j++)
            {
                int k = int(for_RGB.data[(i * for_RGB.rows + for_RGB.cols) * img.channels()]);
                yellow_channel[k] = yellow_channel[k] + 1.0 / (for_RGB.rows * for_RGB.cols);
            }
        }
        vector<int>summation = sum_all(yellow_channel);
        Mat outputimage(img.rows, img.cols, img.type());
        for (int y = 0; y < img.rows; y++) {
            for (int x = 0; x < img.cols; x++) {
                outputimage.at<uchar>(y, x) = (summation[img.at<uchar>(y, x)]);//create output image
            }
        }
        cvtColor(for_RGB, outputimage, COLOR_YCrCb2BGR);
        imwrite("C:/opencv/New folder/peppers_color.bmp", outputimage);
        showHistogram(outputimage, " output Histogram");
        waitKey();
    }
    return 0;
}