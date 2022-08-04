/* Definición de constantes */

const int stepsPerRevolution = 1600;  // number of steps per revolution
const int rolePerMinute = 40; // speed

const int Z_pin = 0; // analog pin connected to button
const int Y_pin = 1; // analog pin connected to Y output
const int X_pin = 2; // analog pin connected to X output

const int dir_pin = 3; // direction pin
const int stp_pin = 2; // step pin

int pos = 0; // posición original como referencia para la funcionalidad del click

Stepper myStepper(stepsPerRevolution, stp_pin, dir_pin); // instancia de motor stepper
// Adafruit_SSD1306 display(OLED_RESET); // instancia de pantalla
