/*
  Four LED test platform for $100 quadcopter.
  By Mike Soltys.
  This example code is in the public domain.
 */
 
// Label the four motors, and what pins they're connected to
const int FR = 11;
const int FL = 10;
const int RR = 6;
const int RL = 9;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the pins as output.
  pinMode(FR, OUTPUT);     
  pinMode(FL, OUTPUT);     
  pinMode(RL, OUTPUT);     
  pinMode(RR, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
blink();       // Blinks the LEDs for 1 second in CCW order
rampUpDown();  // Ramps up and then down the LEDsin CCW order
}

/* Blinks the motors on in CCW order, then off in CCW order */
void blink() {
    digitalWrite(FR, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second 
  digitalWrite(FL, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(RL, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(RR, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second

  digitalWrite(FR, LOW);   // turn the LED off (LOW is the voltage level)
  delay(1000);               // wait for a second 
  digitalWrite(FL, LOW);   // turn the LED off (LOW is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(RL, LOW);   // turn the LED off (LOW is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(RR, LOW);   // turn the LED off (LOW is the voltage level)
  delay(1000);               // wait for a second
}

/* Blinks the motors on in CCW order, then off in CCW order */
void rampUpDown() {
  int speed;
  // Ramp up the Front Right motor
  for(speed = 0; speed <= 255; speed++) {
    analogWrite(FR,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
  // decelerate the motor
  for(speed = 255; speed >= 0; speed--) {
    analogWrite(FR,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
  // Ramp up the Front Left motor
  for(speed = 0; speed <= 255; speed++) {
    analogWrite(FL,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
  // decelerate the motor
  for(speed = 255; speed >= 0; speed--) {
    analogWrite(FL,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
    // Ramp up the Rear Left motor
  for(speed = 0; speed <= 255; speed++) {
    analogWrite(RL,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
  // decelerate the motor
  for(speed = 255; speed >= 0; speed--) {
    analogWrite(RL,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
      // Ramp up the Rear Right motor
  for(speed = 0; speed <= 255; speed++) {
    analogWrite(RR,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
  // decelerate the motor
  for(speed = 255; speed >= 0; speed--) {
    analogWrite(RR,speed);	// set the new speed
    delay(5);           	// delay between speed steps
  }
  
}

