#include <Stepper.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Constantes del motor
const int StepsPerRevolution = 1000;
const int Speed = 120;
const int dir_pin = 4;
const int stp_pin = 5;

//Constantes del Joystick
const int button_pin = 0; // analog pin connected to button
const int Y_pin = 1; // analog pin connected to Y output
const int X_pin = 2; // analog pin connected to X output
const int Joystick_speed = 40;
const int Joystick_step = 40;

int pos = 0;

//Instancias
Stepper motor(StepsPerRevolution, stp_pin, dir_pin);  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  motor.setSpeed(Speed);

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
  //Joyscik
  int y_axis = analogRead(Y_pin);
  //int x_axis = analogRead(X_pin);
  int button = analogRead(button_pin);

  //Presionar boton
  if (button == 0){
    motor.setSpeed(Speed);
    motor.step(-pos);
    pos = 0;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display(); 
  }
  
  //Mover Eje Y
  else if (y_axis < 400){
    motor.setSpeed(Joystick_speed);
    motor.step(-Joystick_step);
    pos -= Joystick_step;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display(); 
  }
  else if (y_axis > 530){
    motor.setSpeed(Joystick_speed);
    motor.step(Joystick_step);
    pos += Joystick_step;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(pos);
    display.display();
  }

  //Conexion con PC
  if (Serial.available() > 0 ){
    int data = Serial.parseInt();
    
    // Movimiento
    if (data > 10000 && data < 20000) { 
      int steps = data - 10000;
      motor.step(steps); 
    }

    //Ajustar Velocidad
    else if (data > 20000 && data < 30000){
      int speed = data - 20000;
      motor.setSpeed(speed);
      Serial.println("velocidad");
    }
  }
}
