#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Görüntüyü yükle
    cv::Mat image = cv::imread("path_to_image.jpg", cv::IMREAD_COLOR);

    // Görüntü yükleme hatasını kontrol et
    if(image.empty()) {
        std::cerr << "Görüntü yüklenemedi!" << std::endl;
        return -1;
    }

    // Görüntüyü gri tonlamaya dönüştür
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    // Gri tonlama görüntüyü kaydet
    cv::imwrite("gray_image.jpg", gray_image);

    std::cout << "Gri tonlama görüntü kaydedildi." << std::endl;

    return 0;
}
