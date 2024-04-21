#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
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

void new_card(Mat& image, vector<string>& name_card, string way_file, vector<Mat>& all_card_image, string name_of_card) {
	image = imread(way_file);
	check_open_image(image);
	GaussianBlur(image, image, Size(5, 5), 2);
	all_card_image.push_back(image);
	name_card.push_back(name_of_card);
}

void poisk_card(string& cardName, Mat& card, vector<Mat>& cardsImages, vector<string>& name_card, vector<Mat>& cardsDescriptors, vector<vector<KeyPoint>>& cardsKeypoints) {
	Mat cardDescriptors;
	vector<KeyPoint> cardKeypoints;
	Ptr<ORB> detector = ORB::create();
	Ptr<BFMatcher> matcher = BFMatcher::create();
	detector->detectAndCompute(card, noArray(), cardKeypoints, cardDescriptors);

	int i_name = -1;
	int maxCount = 0;

	for (int i = 0; i < cardsImages.size(); i++) {
		vector<vector<DMatch>> kolvo_sovpadeniy;
		matcher->knnMatch(cardsDescriptors[i], cardDescriptors, kolvo_sovpadeniy, 3);
		vector<DMatch> correct;
		for (size_t i = 0; i < kolvo_sovpadeniy.size(); i++) {
			if (kolvo_sovpadeniy[i][0].distance < 0.75 * kolvo_sovpadeniy[i][1].distance) {
				correct.push_back(kolvo_sovpadeniy[i][0]);
			}
		}

		if (maxCount < correct.size()) {
			maxCount = static_cast<int>(correct.size());
			i_name = i;
		}
	}

	if (i_name == -1) {
		cardName = "";
	}
	else {
		cardName = name_card[i_name];
	}
}

int main() {
	setlocale(0, "");

	vector<Mat> all_card_image;
	vector<string> name_card;
	vector<Mat> card_descr;
	vector<vector<KeyPoint>> card_key;

	Mat image;
	string way_file;
	string name_of_card;

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/ace_diamonds.jpg";
	name_of_card = "ace_diamonds";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/queen_hearts.jpg";
	name_of_card = "queen_hearts";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/king_spades.jpg";
	name_of_card = "king_spades";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/king_clubs.jpg";
	name_of_card = "king_clubs";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/jack_hearts.jpg";
	name_of_card = "jack_hearts";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/8_hearts.jpg";
	name_of_card = "8_hearts";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	way_file = "C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/6_spades.jpg";
	name_of_card = "6_spades";
	new_card(image, name_card, way_file, all_card_image, name_of_card);

	Ptr<ORB> detector = ORB::create();

	for (int i = 0; i < all_card_image.size(); i++) {
		Mat dis;
		vector<KeyPoint> keys;
		detector->detectAndCompute(all_card_image[i], noArray(), keys, dis);
		card_key.push_back(keys);
		card_descr.push_back(dis);
	}

	image = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/practice_cards/all_cards.jpg");
	check_open_image(image);

	vector<vector<Point>> contours;
	Mat image_gray, image_gauss;
	cvtColor(image, image_gray, COLOR_BGR2GRAY);
	GaussianBlur(image_gray, image_gauss, Size(7, 7), 2);
	Canny(image_gauss, image_gauss, 100, 300);
	findContours(image_gauss, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	for (const auto& contour : contours) {
		vector<Point> contoursPoly;
		approxPolyDP(contour, contoursPoly, 1, true);
		RotatedRect cardRect = minAreaRect(contoursPoly);
		if (cardRect.size.width < 100 || cardRect.size.height < 100) {
			continue;
		}

		Mat card, rotatedMatrix, rotatedImage;
		string cardName;

		rotatedMatrix = getRotationMatrix2D(cardRect.center, cardRect.angle, 1.0);
		warpAffine(image, rotatedImage, rotatedMatrix, image.size(), INTER_CUBIC);
		getRectSubPix(rotatedImage, cardRect.size, cardRect.center, card);

		poisk_card(cardName, card, all_card_image, name_card, card_descr, card_key);

		if (cardName != "") {
			Point2f boxPoints[4];
			cardRect.points(boxPoints);
			for (int j = 0; j < 4; j++) {
				line(image, boxPoints[j], boxPoints[(j + 1) % 4], Scalar(255, 0, 0), 2, LINE_AA);
			}
			putText(image, cardName, cardRect.center, 1, 2, Scalar(0, 255, 255), 3);
		}
	}

	resize(image, image, Size(800, 600));
	imshow("Результат", image);
	imwrite("Результат.jpg", image);
	waitKey(0);
}