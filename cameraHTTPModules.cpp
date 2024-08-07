#include <opencv2/opencv.hpp>
#include "civetweb.h"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

// HTTP yanıtı için bir handler fonksiyonu
int video_handler(struct mg_connection *conn, void *ignored) {
    Mat frame;
    VideoCapture cap(0); // Varsayılan kamera
    if (!cap.isOpened()) {
        cerr << "Kamera açılamadı!" << endl;
        return 500; // İç sunucu hatası
    }

    cap >> frame; // Bir kare yakala
    if (frame.empty()) {
        cerr << "Boş kare!" << endl;
        return 204; // İçerik yok
    }

    vector<uchar> buf;
    imencode(".jpg", frame, buf); // JPEG'e kodla
    string jpeg_data(buf.begin(), buf.end());

    // HTTP yanıtını oluştur
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: image/jpeg\r\n"
              "Content-Length: %lu\r\n"
              "\r\n",
              jpeg_data.size());
    mg_write(conn, jpeg_data.data(), jpeg_data.size());

    return 200; // Başarılı
}

int main() {
    const char *options[] = {
        "document_root", ".", "listening_ports", "8080", 0
    };

    // Civetweb konfigürasyonu ve başlatma
    struct mg_callbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    struct mg_context *ctx = mg_start(&callbacks, 0, options);

    // "/video_feed" yolunu ayarla
    mg_set_request_handler(ctx, "/video_feed", video_handler, 0);

    cout << "Sunucu çalışıyor: http://localhost:8080/video_feed" << endl;
    getchar(); // Kullanıcı girişini bekle

    // Sunucuyu durdur
    mg_stop(ctx);
    return 0;
}
