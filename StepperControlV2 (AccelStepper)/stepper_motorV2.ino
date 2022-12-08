#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
char serialData;

//Stepper
const int accel = 100;
const int maxspeed = 500;
const int dir_pin = 4;
const int stp_pin = 5;

//Joystick
const int button_pin = 8;
const int Y_pin = 1; // analog pin connected to Y output
const int X_pin = 2; // analog pin connected to X output
boolean directio = true; //direction clockwise or anticlockwise of joystick
boolean serial = false; //movement of joystick or serial comunication


//Instances
AccelStepper stepper(1,stp_pin,dir_pin); // 1 makes reference to motor number 1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  

  pinMode(1,INPUT);
  pinMode(2,INPUT);

  //Stepper parameters
  serialData = (char)(("0"));
  stepper.setSpeed(0);
  stepper.setAcceleration(accel);
  stepper.setMaxSpeed(maxspeed);

  //Inicialize screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Iniciando...");
  display.display(); 
}

void loop() {
  joystick();
  seriall();
  positio();
}

void joystick() {
  unsigned long period = 100;
  static unsigned long previousMillis = 0;

    if (( millis() - previousMillis) > period) {
      //Read Joyscik pins
      int y_axis = analogRead(Y_pin);
      int x_axis = analogRead(X_pin);
      int button = digitalRead(button_pin);
  
      if (y_axis < 50 && serial == false) {
        if (directio == false){
          stepper.setSpeed(0); 
          directio = true;
        }
        stepper.move(10000); //this value is only to set te direction anticlockwise or clockwise
        stepper.run();
       }
      else if (y_axis > 973 && serial == false) {
        if (directio == true){
          stepper.setSpeed(0);
          directio = false;
        }
        stepper.move(-10000);
        stepper.run();
       }
     }
 }

 void seriall() {
  unsigned long period = 100;
  static unsigned long previousMillis = 0;
  if (( millis() - previousMillis) > period) {
   
   if (Serial.available() > 0) {
    int steps = Serial.parseInt();
    stepper.setSpeed(0);
    stepper.move(steps);
    serial = true;
   }
   if (serial == true) {
    stepper.run();
     if (stepper.distanceToGo() == 0){
      serial = false;
      stepper.setSpeed(0);
     }
   }
   } 
 }

void positio() {
  unsigned long period = 100;
  static unsigned long previousMillis = 0;
  if (( millis() - previousMillis) > period) {
    Serial.println((String(stepper.currentPosition()) + String(",") + String(stepper.speed())));
    
  }
}
