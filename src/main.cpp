#include <Arduino.h>
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <LowPower.h>
#include <LiquidCrystal_I2C.h>

#define detect 2
#define pump_pin 5

volatile float temp;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);

void detected();

void setup() {
  pinMode(detect, INPUT);
  pinMode(pump_pin,OUTPUT);
  Serial.begin(9600);
  mlx.begin();
  lcd.init();
  lcd.noBacklight();
}

void loop() {
  while(digitalRead(detect) == HIGH){
    delay(200);
    digitalWrite(pump_pin, LOW);
  }
  
  if(digitalRead(detect) == LOW){
    temp = mlx.readObjectTempC();
    lcd.backlight();
    lcd.setCursor(6, 0);
    lcd.print(temp);
    digitalWrite(pump_pin,HIGH);
    LowPower.idle(SLEEP_2S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,SPI_OFF, USART0_OFF, TWI_OFF);
    delay(1000);
    digitalWrite(pump_pin, LOW);
    lcd.init();
    lcd.noBacklight();
    while(digitalRead(detect) == LOW){
      digitalWrite(pump_pin, LOW);
      delay(200);
    }
  }
}
