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

int  change_color(Mat image, int number, string str) {
    Mat color_space;
    cvtColor(image, color_space, number);
    namedWindow(str, WINDOW_NORMAL);
    imshow(str, color_space);
    return 0;
}


int main() {
    setlocale(0, "");
    int n;
    cout << "Возможности программы:" << endl;
    cout << "1. Вывод изображения в различных цветовых пространствах" << endl;
    cout << "2. Вывод изображения с фильтром Гаусса. Обнаружение и рисование линий." << endl;
    cout << "3. Обнаружение и рисование окружностей." << endl;
    cout << "Введите число от 1 до 3: ";
    cin >> n;
    if ((cin.fail()) || ((n!=1) && (n!=2) && (n!=3))){
        cout << "Неправильный ввод!" << endl;
        cout << "Программа завершена";
        cout << endl;
        system("pause");
        return 0;
    }
    

    if (n == 1) {
        Mat image = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/opencv_practice_2/image1_openCV_lab2.jpg");
        check_open_image(image);

        namedWindow("BGR", WINDOW_NORMAL);
        imshow("BGR", image);

        change_color(image, COLOR_BGR2RGB, "RGB");
        change_color(image, COLOR_BGR2HSV, "HSV");
        change_color(image, COLOR_BGR2Lab, "LAB");
        change_color(image, COLOR_BGR2GRAY, "GRAY");
        change_color(image, COLOR_BGR2XYZ, "XYZ");
    }

    if (n == 2) {
        Mat image2 = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/opencv_practice_2/image2_openCV_lab2.jpg");
        check_open_image(image2);

        Mat image2_gauss_blur;
        GaussianBlur(image2, image2_gauss_blur, Size(7, 7), 0);
        imshow("Размытое изображение", image2_gauss_blur);

        vector<Vec4i> lines;
        Mat poisk_angle;
        Canny(image2_gauss_blur, poisk_angle, 150, 300);
        HoughLinesP(poisk_angle, lines, 1, CV_PI / 180, 50, 50, 20);
        for (size_t i = 0; i < lines.size(); i++) {
            Vec4i line_i = lines[i];
            line(image2, Point(line_i[0], line_i[1]), Point(line_i[2], line_i[3]), Scalar(0, 0, 255), 4);
        }
        imshow("Обведенные линии", image2);
    }
   
    if (n == 3) {
        Mat image3 = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/opencv_practice_2/image2_openCV_lab2.jpg");
        check_open_image(image3);

        vector<Vec3f> circles;
        Mat image3_gauss_blur;
        cvtColor(image3, image3_gauss_blur, COLOR_BGR2GRAY);
        GaussianBlur(image3_gauss_blur, image3_gauss_blur, Size(7, 7), 0);
        HoughCircles(image3_gauss_blur, circles, HOUGH_GRADIENT, 2, image3_gauss_blur.rows / 4, 10, 200);

        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(image3, center, radius, Scalar(0, 0, 255), 4, 8, 0);
        }
        imshow("Обведенные круги", image3);
    }

    waitKey(0);
    return 0;
}