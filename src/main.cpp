#include <Arduino.h>
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <LowPower.h>
#include <LiquidCrystal_I2C.h>

#define work 2
#define motor_pin 5
#define en_pin  4

//volatile float temp;
volatile int val = HIGH;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);

void detected();

void setup() {
  pinMode(work, INPUT);
  pinMode(motor_pin,OUTPUT);
  pinMode(en_pin,OUTPUT);
  digitalWrite(en_pin,HIGH);
  Serial.begin(9600);
  mlx.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  //lcd.clear();
  digitalWrite(motor_pin,LOW);
  delay(100);
  val = digitalRead(work);
  while(val == HIGH){
    delay(100);
    val = digitalRead(work);
    if(val == LOW){
      break;
    }
  }
    digitalWrite(motor_pin,HIGH);
    float temp = mlx.readObjectTempC();
    lcd.print(String(temp) + " C");
    Serial.print(String(temp) + " C");
    delay(1000);
    digitalWrite(motor_pin,LOW);
    while(val == LOW){
      delay(100);
      val = digitalRead(work);
      if(val == HIGH){
        break;
      }
    }
}
