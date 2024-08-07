#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <LiquidCrystal_I2C.h>

// BMP180 sensör nesnesi oluştur
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// LCD ekran nesnesi oluştur (I2C adresi 0x27 olabilir)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Seri haberleşmeyi başlat
  Serial.begin(9600);

  // LCD ekranı başlat
  lcd.begin();
  lcd.backlight();

  // BMP180 sensörünü başlat ve kontrol et
  if (!bmp.begin()) {
    Serial.print("BMP180 sensörü bulunamadı!");
    while (1);
  }
}

void loop() {
  // Sensörden basınç ve sıcaklık verilerini al
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    // Yüksekliği hesapla
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    float altitude = bmp.pressureToAltitude(seaLevelPressure, event.pressure);

    // LCD ekranda yüksekliği göster
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Yukseklik: ");
    lcd.setCursor(0, 1);
    lcd.print(altitude);
    lcd.print(" m");

    // Seri monitörde yüksekliği göster
    Serial.print("Yukseklik: ");
    Serial.print(altitude);
    Serial.println(" m");
  }

  // Biraz bekle
  delay(2000);
}
