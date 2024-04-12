#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <omp.h>

using namespace cv;
using namespace std;

int check_open_image(Mat image) {
	if (image.empty()) {
		cout << "Ошибка! Не удалось открыть изображение!" << endl;
		return -1;
	}
	return 0;
}

Mat conv_gray(Mat image) {
	Mat image_conv_gray(image.rows, image.cols, CV_8UC1);
#pragma omp parallel for
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			int gray_value = 0.11 * pixel[0] + 0.58 * pixel[1] + 0.29 * pixel[2];
			image_conv_gray.at<uchar>(i, j) = gray_value;
		}
	}
	return image_conv_gray;
}

Mat conv_sepia(Mat image) {
	Mat image_conv_sepia(image.rows, image.cols, CV_8UC3);
#pragma omp parallel for
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			int B = (int)(0.272 * pixel[0] + 0.534 * pixel[1] + 0.131 * pixel[2]);
			int G = (int)(0.349 * pixel[0] + 0.686 * pixel[1] + 0.168 * pixel[2]);
			int R = (int)(0.393 * pixel[0] + 0.769 * pixel[1] + 0.189 * pixel[2]);
			image_conv_sepia.at<Vec3b>(i, j) = Vec3b(min(B, 255), min(G, 255), min(R, 255));
		}
	}
	return image_conv_sepia;
}

Mat conv_negative(Mat image) {
	Mat image_conv_negative(image.rows, image.cols, CV_8UC3);
#pragma omp parallel for
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			Vec3b pixel = image.at<Vec3b>(i, j);
			image_conv_negative.at<Vec3b>(i, j) = Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
		}
	}
	return image_conv_negative;
}

Mat conv_contour(Mat image) {
	Mat image_conv_contour(image.rows, image.cols, CV_8UC1);
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
#pragma omp parallel for
	for (int i = 1; i < gray.rows - 1; i++) {
		for (int j = 1; j < gray.cols - 1; j++) {
			float gx = gray.at<uchar>(i + 1, j + 1) + 2 * gray.at<uchar>(i, j + 1) + gray.at<uchar>(i - 1, j + 1) - gray.at<uchar>(i + 1, j - 1) - 2 * gray.at<uchar>(i, j - 1) - gray.at<uchar>(i - 1, j - 1);
			float gy = gray.at<uchar>(i + 1, j + 1) + 2 * gray.at<uchar>(i + 1, j) + gray.at<uchar>(i + 1, j - 1) - gray.at<uchar>(i - 1, j - 1) - 2 * gray.at<uchar>(i - 1, j) - gray.at<uchar>(i - 1, j + 1);
			image_conv_contour.at<uchar>(i, j) = 255 - sqrt(pow(gx, 2) + pow(gy, 2));
		}
	}
	return image_conv_contour;
}

int main() {
	setlocale(0, "");

	Mat image = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/image.jpg");
	check_open_image(image);
	Mat image_conv_gray, image_conv_contour, image_conv_negative, image_conv_sepia;

#pragma omp parallel sections
	{
#pragma omp section
		{
			image_conv_gray = conv_gray(image);
		}
#pragma omp section
		{
			image_conv_sepia = conv_sepia(image);

		}
#pragma omp section
		{
			image_conv_negative = conv_negative(image);
		}
#pragma omp section
		{
			image_conv_contour = conv_contour(image);
		}
	}

#pragma omp critical
	{
		namedWindow("Исходное изображение", WINDOW_NORMAL);
		imshow("Исходное изображение", image);
		namedWindow("Серый", WINDOW_NORMAL);
		imshow("Серый", image_conv_gray);
		namedWindow("Сепия", WINDOW_NORMAL);
		imshow("Сепия", image_conv_sepia);
		namedWindow("Негатив", WINDOW_NORMAL);
		imshow("Негатив", image_conv_negative);
		namedWindow("Контур", WINDOW_NORMAL);
		imshow("Контур", image_conv_contour);
	}

	waitKey(0);
	return 0;
}