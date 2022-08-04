void loop() {
//  Serial.print("X-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.println(analogRead(Z_pin));
  int a = analogRead(Y_pin);
  // int b = analogRead(X_pin);
  int button = analogRead(Z_pin);
  if (button == 0)
  {
    myStepper.setSpeed(4 * rolePerMinute);
    myStepper.step(-pos);
    pos = 0;
    Serial.println(a);
    
  }
/*
  else if (b < 200)
  {
    myStepper.setSpeed(max(rolePerMinute, rolePerMinute - 40));
  }
  
  else if (b > 900)
  {
    myStepper.setSpeed(min(6 * rolePerMinute, rolePerMinute + 40));
  }
 */
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
