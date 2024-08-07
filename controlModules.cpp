#include <Wire.h>
#include <Servo.h>
#include <MPU6050.h>

MPU6050 mpu;
Servo esc1, esc2, esc3, esc4;

int throttle, yaw, pitch, roll;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  esc1.attach(9);  // ESC1 Pin
  esc2.attach(10); // ESC2 Pin
  esc3.attach(11); // ESC3 Pin
  esc4.attach(12); // ESC4 Pin

  // Başlangıç değerlerini sıfırla
  esc1.writeMicroseconds(1000);
  esc2.writeMicroseconds(1000);
  esc3.writeMicroseconds(1000);
  esc4.writeMicroseconds(1000);

  delay(1000); // ESC kalibrasyonu için bekle
}

void loop() {
  // RC kumanda sinyallerini oku
  throttle = pulseIn(2, HIGH); // Throttle sinyali pin 2
  yaw = pulseIn(3, HIGH);      // Yaw sinyali pin 3
  pitch = pulseIn(4, HIGH);    // Pitch sinyali pin 4
  roll = pulseIn(5, HIGH);     // Roll sinyali pin 5

  // MPU6050'den veri oku
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Motor hızlarını hesapla
  int esc1Speed = throttle + pitch + roll - yaw;
  int esc2Speed = throttle + pitch - roll + yaw;
  int esc3Speed = throttle - pitch + roll + yaw;
  int esc4Speed = throttle - pitch - roll - yaw;

  // Motor hızlarını sınırla
  esc1Speed = constrain(esc1Speed, 1000, 2000);
  esc2Speed = constrain(esc2Speed, 1000, 2000);
  esc3Speed = constrain(esc3Speed, 1000, 2000);
  esc4Speed = constrain(esc4Speed, 1000, 2000);

  // Motor hızlarını ayarla
  esc1.writeMicroseconds(esc1Speed);
  esc2.writeMicroseconds(esc2Speed);
  esc3.writeMicroseconds(esc3Speed);
  esc4.writeMicroseconds(esc4Speed);

  // Seri monitörde verileri göster
  Serial.print("Throttle: "); Serial.print(throttle);
  Serial.print(" Yaw: "); Serial.print(yaw);
  Serial.print(" Pitch: "); Serial.print(pitch);
  Serial.print(" Roll: "); Serial.print(roll);
  Serial.println();

  delay(20); // Döngü hızı
}
