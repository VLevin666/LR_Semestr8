#include <opencv2/opencv.hpp>
#include <complex>
#include <mpi.h>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv) {
    setlocale(0, "");

    int width = 1000;
    int height = 800;
    int kolvo_iteration = 800;
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int start = rank * (height / size);
    int end = min((rank + 1) * (height / size), height);

    int color_1, color_2, color_3;
    Mat image = Mat::zeros(end - start, width, CV_8UC3);

    for (int i = start; i < end; i++) {
        for (int j = 0; j < width; j++) {
            double a = -2.5 + (2.5 - (-2.5)) * j / width;
            double b = -2.5 + (2.5 - (-2.5)) * i / height;

            complex <double> z(0, 0);
            complex<double> c(a, b);
            int n = 0;
            while (abs(z) <= 4 && n < kolvo_iteration) {
                z = z * z + c;
                n++;
            }
            if (n == kolvo_iteration - 1) {
                color_1 = 0;
                color_2 = 0;
                color_3 = 0;
            }
            else {
                color_1 = (n % 8) * 32 + 128;
                color_2 = (n % 4) * 1;
                color_3 = (n % 8) * 16 + 128;
            }
            image.at<Vec3b>(i - start, j) = Vec3b(color_1, color_2, color_3);
        }
    }
    Mat fractal(height, width, CV_8UC3);

    MPI_Gather(image.data, (end - start) * width * 3, MPI_UNSIGNED_CHAR,
        fractal.data, (end - start) * width * 3, MPI_UNSIGNED_CHAR,
        0, MPI_COMM_WORLD);

    if (rank == 0) {
        imshow("Фрактал Мандельброта", fractal);
        waitKey(0);
    }

    MPI_Finalize();
    return 0;
}