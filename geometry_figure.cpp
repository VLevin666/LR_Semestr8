#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int check_open_image(Mat image) {
	if (image.empty()) {
		cout << "Ошибка! Не удалось открыть изображение!" << endl;
		return -1;
	}
}

int geom_figures(Mat image) {
	int lines = image.rows;
	int columns = image.cols;

	putText(image, to_string(columns), Point(650, 590), FONT_HERSHEY_SIMPLEX, 1, Scalar(190, 0, 0), 2);
	putText(image, "x", Point(710, 590), FONT_HERSHEY_SIMPLEX, 1, Scalar(190, 0, 0), 2);
	putText(image, to_string(lines), Point(730, 590),FONT_HERSHEY_SIMPLEX, 1, Scalar(190, 0, 0), 2);

	line(image, Point(640, 550), Point(800, 550), Scalar(0, 0, 190), 2);
	line(image, Point(640, 550), Point(640, 600), Scalar(0, 0, 190), 2);

	circle(image, Point(140, 300), 25, Scalar(0, 0, 255), 3);

	circle(image, Point(580, 460), 70, Scalar(255, 255, 255), -1);
	circle(image, Point(580, 360), 50, Scalar(255, 255, 255), -1);
	circle(image, Point(580, 290), 25, Scalar(255, 255, 255), -1);
	rectangle(image, Point(578, 378), Point(582, 382), Scalar(0, 0, 0), -1);
	rectangle(image, Point(578, 358), Point(582, 362), Scalar(0, 0, 0), -1);
	rectangle(image, Point(578, 338), Point(582, 342), Scalar(0, 0, 0), -1);
	
	imshow("Image", image);
}

int split_on_pieces(Mat image) {
	int lines = image.rows;
	int columns = image.cols;

	Mat piece_1 = image(Range(0, lines / 2), Range(0, columns / 2));
	Mat piece_2 = image(Range(0, lines / 2), Range(columns / 2, columns));
	Mat piece_3 = image(Range(lines / 2, lines), Range(0, columns / 2));
	Mat piece_4 = image(Range(lines / 2, lines), Range(columns / 2, columns));

	imshow("Piece 1", piece_1);
	imshow("Piece 2", piece_2);
	imshow("Piece 3", piece_3);
	imshow("Piece 4", piece_4);
}

int maska(Mat image) {
	Mat mask(image.size(), CV_8UC1, Scalar(0));
	rectangle(mask, Point(150, 320), Point(300,500), Scalar(255, 255, 255), -1);
	Mat result;
	image.copyTo(result, mask);
	imshow("Mask Result", result);
}

int main() {
	setlocale(0, "");

	Mat image = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/geometry_figure/image_lab1.jpg");
	check_open_image(image);
	geom_figures(image);
	split_on_pieces(image);
	maska(image);

	waitKey(0);
	return 0;
}