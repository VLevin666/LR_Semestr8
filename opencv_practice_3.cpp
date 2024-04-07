#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

int check_open_image(Mat image) {
    if (image.empty()) {
        cout << "Ошибка! Не удалось открыть изображение!" << endl;
        return -1;
    }
}

int main() {
    setlocale(0, "");
   
    Mat image1 = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/opencv_practice_3/image1_openCV_lab3.jpg");
    check_open_image(image1);

    Mat image_gray, image_gauss_blur, poisk_angle;
    vector<vector<Point>> contours;

    cvtColor(image1, image_gray, COLOR_BGR2GRAY);
    GaussianBlur(image_gray, image_gauss_blur, Size(5, 5), 0);
    Canny(image_gauss_blur, poisk_angle, 100, 200);
    findContours(poisk_angle, contours, RETR_TREE, CHAIN_APPROX_TC89_L1);
    imshow("Фильтр + границы", poisk_angle);

    Mat contours_draw = Mat::zeros(poisk_angle.size(), CV_8UC3);

    for (size_t i = 0; i < contours.size(); i++) {
        vector<Point> approx;
        approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.01, true);
        size_t kolvo_uglov = approx.size();

        string name_figure;
        Scalar color_figure;
        Moments poisk_center = moments(contours[i]);
        if (kolvo_uglov == 4) {
            name_figure = "Square";
            color_figure = Scalar(0, 0, 255);
        }
        else {
            if (kolvo_uglov == 3) {
                name_figure = "Triangle";
                color_figure = Scalar(0, 255, 0);
            }
            else {
                name_figure = "Circle";
                color_figure = Scalar(255, 0, 0);
            }
        }
        
        drawContours(contours_draw, contours, i, color_figure, 2);
        Point text_coord(poisk_center.m10 / poisk_center.m00 - 40, poisk_center.m01 / poisk_center.m00);
        putText(contours_draw, name_figure, text_coord, FONT_HERSHEY_SIMPLEX, 0.8, color_figure, 2);
    }
    imshow("Названия фигур", contours_draw);

    Mat image2 = imread("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/opencv_practice_3/image2_openCV_lab3.jpg");
    check_open_image(image2);

    Mat image2_gauss_blur, image2_canny;
    GaussianBlur(image2, image2_gauss_blur, Size(7, 7), 0);
    Canny(image2_gauss_blur, image2_canny, 100, 200);
    resize(image2_canny, image2_canny, Size(900, 700), INTER_LINEAR);
    imshow("Выделенный текст", image2_canny);

    waitKey(0);
    return 0;
}