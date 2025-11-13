#include <Servo.h>
#include <NewPing.h>

// --- Konfigurasi pin ---
#define TRIG_PIN A0
#define ECHO_PIN A1
#define SERVO_PIN 10
#define MAX_DISTANCE 30
#define BUKA_JARAK 10    
#define WAKTU_TUTUP 3000  

// --- Pengaturan kecepatan servo ---
#define KECEPATAN_BUKA 10 
#define KECEPATAN_TUTUP 8 

// --- Sudut servo ---
#define SUDUT_TERTUTUP 0
#define SUDUT_TERBUKA 55  

Servo tutup;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  tutup.attach(SERVO_PIN);
  tutup.write(SUDUT_TERTUTUP); 
  delay(1000);
  Serial.println("=== TEMPAT SAMPAH OTOMATIS AKTIF ===");
}

void loop() {
  delay(50);
  unsigned int jarak = sonar.ping_cm();

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");

  if (jarak > 0 && jarak < BUKA_JARAK) {
    Serial.println("🖐 Tangan terdeteksi! Membuka tutup...");
    bukaPelan();
    delay(WAKTU_TUTUP);
    Serial.println("Menutup kembali...");
    tutupPelan();
  }
}

void bukaPelan() {
  for (int pos = SUDUT_TERTUTUP; pos <= SUDUT_TERBUKA; pos++) {
    tutup.write(pos);
    delay(KECEPATAN_BUKA);
  }
}

void tutupPelan() {
  for (int pos = SUDUT_TERBUKA; pos >= SUDUT_TERTUTUP; pos--) {
    tutup.write(pos);
    delay(KECEPATAN_TUTUP);
  }
}
