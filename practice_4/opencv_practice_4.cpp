#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("C:/Users/VALev/OneDrive/Рабочий стол/Политех/8 семестр/Лабы openCV/opencv_practice_4/video.mp4");
    if (!cap.isOpened()) {
        cout << "Ошибка!" << endl;
        return -1;
    }

    int cap_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int cap_height = cap.get(CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("Результат.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(cap_width, cap_height));

    int hmin = 95, smin = 20, vmin = 140, hmax = 125, smax = 70, vmax = 255;
    while (1) {
        Mat image;
        cap >> image;
        if (image.empty())
            break;

        Mat image_hsv;
        cvtColor(image, image_hsv, COLOR_BGR2HSV);

        Mat image_white;
        inRange(image_hsv, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), image_white);

        Mat image_gauss;
        GaussianBlur(image_white, image_gauss, Size(5, 5), 0);
        Canny(image_white, image_white, 100, 200);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(image_gauss, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            vector<Point> approx;
            approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.01, true);
            size_t kolvo_uglov = approx.size();

            Moments poisk_center = moments(contours[i]);
            if (kolvo_uglov == 4) {
                Scalar color_figure = Scalar(0, 0, 255);
                drawContours(image, contours, i, color_figure, 2);
                Point text_coord(poisk_center.m10 / poisk_center.m00 - 40, poisk_center.m01 / poisk_center.m00);
                putText(image, "Square", text_coord, FONT_HERSHEY_SIMPLEX, 0.8, color_figure, 2);
                break;
            }
        }
        imshow("Результат", image);
        video.write(image);
        char c = (char)waitKey(25);
        if (c == 27)
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}