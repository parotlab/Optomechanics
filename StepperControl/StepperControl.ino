
#include <Stepper.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #define OLED_RESET 20

const int stepsPerRevolution = 1600;  // change this to fit the number of steps per revolution
const int rolePerMinute = 40;
const int Y_pin = 0; // analog pin connected to Y output
const int Z_pin = 1; // analog pin connected to button
int pos = 0;

Stepper myStepper(stepsPerRevolution, 2, 3);
// Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  myStepper.setSpeed(rolePerMinute);
  
  //Initialize display by providing the display type and its I2C address.
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //Set the text size and color.
  // display.setTextSize(1.5);
  // display.setTextColor(WHITE);
  // display.print("Hello World!");
  // delay(1000);
}

void loop() {
//  Serial.print("X-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.println(analogRead(Z_pin));
  int a = analogRead(Y_pin);
  int button = analogRead(Z_pin);
  if (button == 1023)
  {
    myStepper.setSpeed(4 * rolePerMinute);
    myStepper.step(-pos);
    Serial.println(a);
    
  }
  else if (a < 400)
  {
    myStepper.setSpeed(rolePerMinute);
    myStepper.step(-40);
    Serial.println(a);
    pos -= 40;
  }
  else if (a > 530)
  {
    myStepper.setSpeed(rolePerMinute);
    myStepper.step(40);
    Serial.println(a);
    pos += 40;
  }
  /*
  //Clear previous image.
  display.clearDisplay();
  display.setCursor(0, 15);
  display.print("Position: ");
  display.print(pos);
  //Display changes if any were made.
  display.display();
  */
}
