#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 40
#define OLED_RESET 4

// const int stepsPerRevolution = 1600;  // change this to fit the number of steps per revolution
// const int rolePerMinute = 40;
const int Y_pin = 0; // analog pin connected to Y output
const int Z_pin = 1; // analog pin connected to button
int pos = 0;
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //Initialize display by providing the display type and its I2C address.
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //Set the text size and color.
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.print("Hello World!");
  delay(1000);
}

void loop() {
  
  int a = analogRead(Y_pin);
  int button = analogRead(Z_pin);
  //float escalador = a / 1000;
  
  //if (button == 1023) {}

  if (a > 530) {
    // Set the spinning direction clockwise:
    digitalWrite(dirPin, HIGH);
    // Spin the stepper motor 1 revolution slowly:
    for (int i = 0; i < stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      //int retraso = round(500 / escalador^3);
      digitalWrite(stepPin, HIGH);
      //delayMicroseconds(retraso);
      delayMicroseconds(2000);
      digitalWrite(stepPin, LOW);
      //delayMicroseconds(retraso);
      delayMicroseconds(2000);
    }
    pos += 40;
  }

  else if (a < 400) {
    // Set the spinning direction counterclockwise:
    digitalWrite(dirPin, LOW);
    
    // Spin the stepper motor 1 revolution slowly:
    for (int i = 0; i < stepsPerRevolution; i++) {
      // These four lines result in 1 step:
      //int retraso = round(500 / (1 - escalador));
      digitalWrite(stepPin, HIGH);
      //delayMicroseconds(retraso);
      delayMicroseconds(2000);
      digitalWrite(stepPin, LOW);
      //delayMicroseconds(retraso);
      delayMicroseconds(2000);
    }
    pos -= 40;
  }

  //Clear previous image.
  display.clearDisplay();
  display.setCursor(0, 15);
  display.print("Position: ");
  display.print(pos);
  //Display changes if any were made.
  display.display();

  //delay(1000);
   /*
  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  }

  delay(1000);

  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(5000);
  }

  delay(1000);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  //Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  delay(1000);
  */
}
