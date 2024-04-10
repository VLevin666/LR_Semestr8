#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime> 


using namespace cv;
using namespace std;


int main() {
    unsigned int start_prog = clock();
    setlocale(0, "");

    VideoCapture cap("ZUA.mp4");
    if (!cap.isOpened()) {
        cout << "Ошибка!" << endl;
        return -1;
    }

    int cap_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int cap_height = cap.get(CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("Результат.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(cap_width, cap_height));


    CascadeClassifier face_cascade_eye;
    if (!face_cascade_eye.load(samples::findFile("haarcascade_eye.xml"))) {
        cout << "Ошибка! Файл <глаза>" << endl;
        return -1;
    }

    CascadeClassifier face_cascade_face;
    if (!face_cascade_face.load(samples::findFile("haarcascade_frontalface_default.xml"))) {
        cout << "Ошибка! Файл <лицо>" << endl;
        return -1;
    }

    CascadeClassifier face_cascade_smile;
    if (!face_cascade_smile.load(samples::findFile("haarcascade_smile.xml"))) {
        cout << "Ошибка! Файл <улыбка>" << endl;
        return -1;
    }


    while (1) {
        Mat image1;
        cap >> image1;
        if (image1.empty())
            break;
        Mat resized_image1;
        resize(image1, resized_image1, Size(), 0.4, 0.4, INTER_LANCZOS4);
        Mat image1_gray;
        cvtColor(resized_image1, image1_gray, COLOR_BGR2GRAY);


        vector<Rect> faces;
        face_cascade_face.detectMultiScale(image1_gray, faces, 1.1, 5);
        for (const auto& face : faces) {
            rectangle(resized_image1, face, Scalar(255, 0, 139), 1);
        }

        vector<Rect> eyes;
        face_cascade_eye.detectMultiScale(image1_gray, eyes, 1.1, 5);
        for (const auto& eye : eyes) {
            rectangle(resized_image1, eye, Scalar(0, 255, 0), 1);
        }

        vector<Rect> smiles;
        face_cascade_smile.detectMultiScale(image1_gray, smiles, 2.0, 20);
        for (const auto& smile : smiles) {
            rectangle(resized_image1, smile, Scalar(0, 255, 255), 1);
        }

        resize(resized_image1, resized_image1, Size(cap_width, cap_height));
        imshow("Результат", resized_image1);
        video.write(resized_image1);
        char c = (char)waitKey(30);
        if (c == 32)
            break;
    }
    unsigned int end_prog = clock();
    cout << "Время работы: " << (end_prog - start_prog) / 1000 << " сек." << endl;

    cap.release();
    destroyAllWindows();

    return 0;
}
