#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//StepperMotor
const int StepsPerRevolution = 1000;
const int Speed = 60;
const int dir_pin = 4;
const int stp_pin = 5;

//Joystick
const int button_pin = 8;
const int Y_pin = 1; // analog pin connected to Y output
const int X_pin = 2; // analog pin connected to X output
const int Joystick_speed = 40;
const int Joystick_step = 60;

int pos = 0;

//Instancias

Stepper stepper(StepsPerRevolution, stp_pin, dir_pin);  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  stepper.setSpeed(Speed);
  pinMode(button_pin,INPUT_PULLUP);
  
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
  //Read Joyscik pins
  int y_axis = analogRead(Y_pin);
  int x_axis = analogRead(X_pin);
  int button = digitalRead(button_pin);

  //Press Button
  if (button == 0){
    stepper.setSpeed(Speed);
    stepper.step(-pos);
    pos = 0;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display(); 
  }
  
  //Y-Axis Move
  else if (y_axis < 50){
    stepper.setSpeed(Joystick_speed);
    stepper.step(-Joystick_step);
    pos -= Joystick_step;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display(); 
  }
  else if (y_axis > 973){
    stepper.setSpeed(Joystick_speed);
    stepper.step(Joystick_step);
    pos += Joystick_step;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display();
  }
  else if (x_axis < 50){
    stepper.setSpeed(Joystick_speed);
    stepper.step(1);
    pos += 1;
    delay(500);
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display(); 
  }
  else if (x_axis > 973){
    stepper.setSpeed(Joystick_speed);
    stepper.step(10);
    pos += 10;
    delay(500);
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display(); 
  }
  
  //Conexion con PC
  if (Serial.available() > 0 ){
    int data = Serial.parseInt();
    
    // Counterclockwise
    if (data > 10000 && data < 20000) { 
      int steps = data - 10000;
      stepper.step(steps); 
      pos += steps;
      display.clearDisplay();
      display.setCursor(0, 10);
      display.println(pos);
      display.display(); 
    }
     // Clockkwise
    else if (data > 20000 && data < 30000) { 
      int steps = data - 20000;
      stepper.step(-steps); 
      pos -= steps;
      display.clearDisplay();
      display.setCursor(0, 10);
      display.println(pos);
      display.display(); 
    }
    //Ajustar Velocidad
    else if (data > 30000 && data < 32750){
      int speed = data - 30000;
      stepper.setSpeed(speed);
    }
  }
}
