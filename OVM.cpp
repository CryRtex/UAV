#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

int main() {
    // HOGDescriptor nesnesi oluştur
    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

    // Görüntüyü yükle
    cv::Mat image = cv::imread("path_to_image.jpg");

    // Görüntü yükleme hatasını kontrol et
    if (image.empty()) {
        std::cerr << "Görüntü yüklenemedi!" << std::endl;
        return -1;
    }

    // İnsanları tespit et
    std::vector<cv::Rect> detections;
    hog.detectMultiScale(image, detections);

    // Tespit edilen insanları dikdörtgenle işaretle
    for (size_t i = 0; i < detections.size(); i++) {
        cv::rectangle(image, detections[i], cv::Scalar(0, 255, 0), 2);
    }

    // Sonucu göster
    cv::imshow("Detections", image);
    cv::waitKey(0);

    // Sonucu kaydet
    cv::imwrite("detections.jpg", image);

    return 0;
}
