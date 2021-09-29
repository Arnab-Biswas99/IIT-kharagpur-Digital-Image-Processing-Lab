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
vector<double>normalhist(vector<int>hist)
{
    vector<double>nor_hist;
    double val = 256.0 * 256.0;
    nor_hist.resize(256, 0);
    for (int i = 0; i < 256; i++)
    {
        nor_hist[i] = hist[i] / val;
    }
    //for (auto x : nor_hist) cout << x << " ";
    return nor_hist;
}
vector<double>sum_all(vector<double>nor_hist)
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
    return last1;
}

vector<double>histmatching(vector<double>source_cdf, vector<double>target_cdf)
{
    vector<double>histmat;
    vector<int>histmat1;
    histmat.resize(256, 0);
    histmat1.resize(256, 0);
    for (int i = 0; i < 256; i++)
    {
        double mini = (double)INT_MAX;
        for (int j = 0; j < 256; j++)
        {

            if ((abs(source_cdf[i] - target_cdf[j]) < mini))
            {
                //cout << source_cdf[i] << " " << target_cdf[j] << " " << source_cdf[i] - target_cdf[j];
                mini = abs(source_cdf[i] - target_cdf[j]);
                // cout << mini << " ";
                histmat[i] = j;
            }
        }
    }
    for (int i = 0; i < 256; i++) cout << histmat[i] << " ";
    return histmat;
}

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
    Mat img = imread("C:/opencv/4.1.01.tiff", -1);
    Mat target = imread("C:/opencv/peppers_color.bmp", -1);
    if (img.channels() == 1 and target.channels() == 1)
    {
        vector<int>hist = create_hist(img);//create and return the histogram array.
        vector<double>nor_hist = normalhist(hist);//create normalized histogram
        vector<double>summation = sum_all(nor_hist);//This is equalized histogram
        vector<int>hist1 = create_hist(target);//create and return the histogram array.
        vector<double>nor_hist1 = normalhist(hist1);//create normalized histogram
        vector<double>summation1 = sum_all(nor_hist1);
        vector<double>outputhist = histmatching(summation, summation1);
        Mat outputImage = img.clone();

        for (int y = 0; y < img.rows; y++) {
            for (int x = 0; x < img.cols; x++) {
                outputImage.at<uchar>(y, x) = (int)(outputhist[img.at<uchar>(y, x)]);
            }
        }
        imshow("ff", outputImage);

        //imwrite("C:/opencv/New folder/walkbridge.jpg", outputImage);
        //showHistogram(img, " Original Histogram");
        //showHistogram(outputImage, " output Histogram");
        waitKey();
    }
    else
    {
        Mat for_RGB, for_RGB_target;
        Mat imgcopy = img.clone();
        cvtColor(img, for_RGB, COLOR_BGR2YCrCb);
        vector<double>yellow_channel;
        yellow_channel.resize(256, 0);
        for (int i = 0; i < for_RGB.rows; i++)
        {
            for (int j = 0; j < for_RGB.cols; j++)
            {
                int k = int(for_RGB.data[(i * for_RGB.rows + j) * img.channels()]);
                yellow_channel[k] = yellow_channel[k] + 1.0 / (for_RGB.rows * for_RGB.cols);
            }
        }
        vector<double>summation = sum_all(yellow_channel);

        cvtColor(target, for_RGB_target, COLOR_BGR2YCrCb);
        vector<double>yellow_channel1;
        yellow_channel1.resize(256, 0);
        for (int i = 0; i < for_RGB_target.rows; i++)
        {
            for (int j = 0; j < for_RGB_target.cols; j++)
            {
                int k = int(for_RGB_target.data[(i * for_RGB_target.rows + for_RGB_target.cols) * target.channels()]);
                yellow_channel1[k] = yellow_channel1[k] + 1.0 / (for_RGB_target.rows * for_RGB_target.cols);
            }
        }
        vector<double>summation1 = sum_all(yellow_channel1);

        vector<double>outputhist = histmatching(summation, summation1);
        for (int i = 0; i < for_RGB.rows; i++)
        {
            for (int j = 0; j < for_RGB.cols; j++)
            {
                int k = int(imgcopy.data[(i * for_RGB.rows + j) * for_RGB.channels()]);
                imgcopy.data[(i * for_RGB.rows + j) * for_RGB.channels()] = outputhist[k];
            }
        }
        //       for (int i = 0; i < for_RGB.rows; i++)
         //       {
         //           for (int j = 0; j < for_RGB.cols; j++)
         //           {
         //               int k = int(imgcopy.data[(i * for_RGB.rows + j) * for_RGB.channels()]);

         //           }
         //       }
        Mat outputimage(img.rows, img.cols, img.type());


        cvtColor(imgcopy, outputimage, COLOR_YCrCb2BGR);

        //imshow("GG", outputimage);
      //  imwrite("C:/opencv/New folder/peppers_color.bmp", outputimage);
       // showHistogram(outputimage, " output Histogram");
        waitKey();
    }
    return 0;
}