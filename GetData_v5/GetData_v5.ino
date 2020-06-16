#include <Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#define NOTE_A5 880 
#define STOP 89
#define RUN 100


// https://github.com/tockn/MPU6050_tockn library info
MPU6050 mpu6050(Wire);

const int buttonPin = 7;    
const int ledPin = 8;    
const int speakerPin = 9;
const int servoPin = 10;

Servo myservo;
int ledState = LOW;         // the current state of the output pin
bool buttonState = false;             // the current reading from the input pin
bool lastButtonState = false;   // the previous reading from the input pin
bool alarm = false;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int boto = 1;
int botoPrevi = 0;

uint32_t timer = 0;
float roll,pitch,rollF,pitchF=0;

void setup() {
  Serial.begin(250000);
  Wire.begin();
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  myservo.attach(servoPin);
  myservo.write(STOP);
}

void loop() {
  mpu6050.update();
  if(millis() - timer > 20){
    roll = atan(mpu6050.getAccY() / sqrt(pow(mpu6050.getAccX(), 2) + pow(mpu6050.getAccZ(), 2))) * 180 / PI;
    pitch = atan(-1 * mpu6050.getAccX() / sqrt(pow(mpu6050.getAccY(), 2) + pow(mpu6050.getAccZ(), 2))) * 180 / PI;
    //Low pass filter
    rollF = 0.94 * rollF + 0.06 * roll;
    pitchF = 0.94 * pitchF + 0.06 * pitch;
    
    Serial.print(rollF);
    Serial.print("/");
    Serial.println(pitchF);
    timer = millis();
  }
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState) {
        boto++;
      }
    }
  }
   if(botoPrevi%3 != boto%3){
    if (boto%3 == 2){
        alarm = true;
    }
    else if (boto%3 == 1){
        alarm = false;
    }
    else if (boto%3 == 0){
        ledState = false;
        digitalWrite(ledPin, ledState);
        myservo.write(RUN);
        delay(650);
        myservo.write(STOP);
         delay(2000);
        myservo.write(RUN);
        delay(650);
        myservo.write(STOP); 
    }
    botoPrevi = boto;
  }
  if(boto%3 == 1 || boto%3 ==2){
    if (alarm){
      tone(speakerPin, NOTE_A5, 10);
      ledState = true;;
    }
    else{
      noTone(speakerPin);
      ledState = false;
    }
  }
  digitalWrite(ledPin,ledState);
  lastButtonState = reading;
}
