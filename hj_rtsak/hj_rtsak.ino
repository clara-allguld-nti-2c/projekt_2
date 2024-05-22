#include <SPI.h> //inkluderar bibliotek
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 srituhobby = Adafruit_SSD1306(128, 64, &Wire); // storleken på oleden, ett objekt med variabler typ

#define sensor A0 //S-pin definierad (la den på A0)
#define Highpulse 540 //satte hög pulse på 540
const int Buzzer = 3;
bool BuzzerOn = false;
            

//variabler, sätter värden i förhand för att enklare användas senare i koden
int sX = 0;
int sY = 60;
int x = 0;
int Svalue;
int value;
long Stime = 0;
long Ltime = 0;
int count = 0;
int Bpm = 0;
int ledPin = 2;

void setup() { // engångs skript so  kommer gå en gång
  Serial.begin(9600);
  srituhobby.begin(SSD1306_SWITCHCAPVCC, 0x3C); //adress
  delay(1000);
  srituhobby.clearDisplay(); //rensar skärmen
  pinMode(Buzzer, OUTPUT);
}

void loop() { //ett skript som kan gå om o om igen i koden (loop) när matad med variabler
  Svalue = analogRead(sensor);
  Serial.println(Svalue);
  value = map(Svalue, 0, 1024, 0, 45);

  int y = 60 - value;

  if (x > 128) {
    x = 0;
    sX = 0;
    srituhobby.clearDisplay();
  }

  if (y < 50) {//hanterar led-lampan
    digitalWrite(ledPin, HIGH);
    tone(Buzzer, 50);
    delay(20);
    noTone(Buzzer);
    digitalWrite(ledPin, LOW);
  }
  srituhobby.drawLine(sX, sY, x, y, WHITE); //ritar grafen som används för att mäta pulsen
  sX = x;
  sY = y;
  x ++;

  BPM();

  srituhobby.setCursor(0, 0); //innehåller information för displayen
  srituhobby.setTextSize(2);
  srituhobby.setTextColor(SSD1306_WHITE);
  srituhobby.print("BPM<3 :");
  srituhobby.display();

}

void BPM() { //uträkningar för pulsen

  if (Svalue > Highpulse) {
    Stime = millis() - Ltime;
    count++;

    if (Stime / 1000 >= 60) {
      Ltime = millis();
      Serial.println(count);
      srituhobby.setCursor(60, 0);
      srituhobby.setTextSize(2);
      srituhobby.setTextColor(SSD1306_WHITE);
      srituhobby.print(count);
      srituhobby.print("   ");
      srituhobby.display();
      count = 0;
    }
  }
}
