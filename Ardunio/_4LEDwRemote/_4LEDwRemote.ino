/* RGB Remote Control
   by: Jim Lindblom
   SparkFun Electronics
   date: October 1, 2013

   This sketch uses Ken Shirriff's *awesome* IRremote library:
       https://github.com/shirriff/Arduino-IRremote

   RGB Remote Control uses a combination of SparkFun's 
   IR Remote (https://www.sparkfun.com/products/11759) and an
   IR receiver diode (https://www.sparkfun.com/products/10266) to
   control an RGB LED.

   The IR Remote's power button turns the LED on or off. The A, B, 
   and C buttons select a channel (red, green, or blue). The up
   and down arrows increment or decrement the LED brightness on that channel.
   The left and right arrows turn a channel to min or max, and
   circle set it to the middle.

   Hardware setup:
     * The output of an IR Receiver Diode (38 kHz demodulating
       version) should be connected to the Arduino's pin 11.
       * The IR Receiver diode should also be powered off the
         Arduino's 5V and GND rails.
     * A common cathode RGB LED is connected to Arduino's pins 
       5, 9, and 6 (red, green, and blue pins).
 */

#include <IRremote.h> // Include the IRremote library

/* Setup constants for SparkFun's IR Remote: */
#define NUM_BUTTONS 9 // The remote has 9 buttons
/* Define the IR remote button codes. We're only using the
   least signinficant two bytes of these codes. Each one 
   should actually have 0x10EF in front of it. Find these codes
   by running the IRrecvDump example sketch included with
   the IRremote library.*/
const uint16_t BUTTON_POWER = 0xD827; // i.e. 0x10EFD827
const uint16_t BUTTON_A = 0xF807;
const uint16_t BUTTON_B = 0x7887;
const uint16_t BUTTON_C = 0x58A7;
const uint16_t BUTTON_UP = 0xA05F;
const uint16_t BUTTON_DOWN = 0x00FF;
const uint16_t BUTTON_LEFT = 0x10EF;
const uint16_t BUTTON_RIGHT = 0x807F;
const uint16_t BUTTON_CIRCLE = 0x20DF;

/* Connect the output of the IR receiver diode to pin 11. */
int RECV_PIN = 11;
/* Initialize the irrecv part of the IRremote  library */
IRrecv irrecv(RECV_PIN);
decode_results results; // This will store our IR received codes
uint16_t lastCode = 0; // This keeps track of the last code RX'd

/* Setup RGB LED pins: */
enum ledOrder // Make an enum to add some clarity in the code
{
  RED,   // 0
  GREEN, // 1
  BLUE   // 2
};
const int rgbPins[3] = {5, 9, 6}; // Red, green, blue pins respectively
byte rgbValues[3] = {55, 23, 200}; // This keeps track of channel brightness
byte activeChannel = RED; // Start with RED as the active channel
boolean ledEnable = 1; // Start with the LED on.

int FR = 5;
int FL = 10;
int RR = 6;
int RL = 9;

int FRspeed = 0;
int FLspeed = 0;
int RRspeed = 0;
int RLspeed = 0;

void setup()
{
  Serial.begin(9600); // Use serial to debug. 
  irrecv.enableIRIn(); // Start the receiver

  /* Set up the RGB LED pins: */
  pinMode(FR, OUTPUT);     
  pinMode(FL, OUTPUT);     
  pinMode(RL, OUTPUT);     
  pinMode(RR, OUTPUT);     
}

// loop() constantly checks for any received IR codes. At the
// end it updates the RGB LED.
void loop() 
{
  
  if (irrecv.decode(&results)) 
  {
    /* read the RX'd IR into a 16-bit variable: */
    uint16_t resultCode = (results.value & 0xFFFF);
    Serial.println(results.value, HEX);

    /* The remote will continue to spit out 0xFFFFFFFF if a 
     button is held down. If we get 0xFFFFFFF, let's just
     assume the previously pressed button is being held down */
    if (resultCode == 0xFFFF)
      resultCode = lastCode;
    else
      lastCode = resultCode;

    // This switch statement checks the received IR code against
    // all of the known codes. Each button press produces a 
    // serial output, and has an effect on the LED output.
 
    switch (resultCode)
    {
      case BUTTON_UP:
        if (FRspeed>0) {
          FRspeed--; }
        if (FLspeed>0) {
          FLspeed--; }          
        if (RRspeed<255) {
          RRspeed++; }
        if (RLspeed<255) {
          RLspeed++; }
        break;
      case BUTTON_DOWN:
        if (FRspeed<255) {
          FRspeed++; }
        if (FLspeed<255) {
          FLspeed++; }          
        if (RRspeed>0) {
          RRspeed--; }
        if (RLspeed>0) {
          RLspeed--; }    
        break;           
      case BUTTON_LEFT:
        if (FRspeed<255) {
          FRspeed++; }
        if (FLspeed>0) {
          FLspeed--; }          
        if (RRspeed<255) {
          RRspeed++; }
        if (RLspeed>0) {
          RLspeed--; }    
        break;
      case BUTTON_RIGHT:
        if (FRspeed>0) {
          FRspeed--; }
        if (FLspeed<255) {
          FLspeed++; }          
        if (RRspeed>0) {
          RRspeed--; }
        if (RLspeed<255) {
          RLspeed++; }    
        break;
      case BUTTON_CIRCLE:
         RLspeed=127;
         RRspeed=127;
         FRspeed=127;
         FLspeed=127;
        break;
        /*      case BUTTON_POWER:
        Serial.println("Power");
        if (ledEnable) ledEnable = 0;
        else ledEnable = 1; // Flip ledEnable
        break;
      case BUTTON_A:
        Serial.println("A");
        activeChannel = RED;
        break;
      case BUTTON_B:
        Serial.println("B");
        activeChannel = GREEN;
        break;
      case BUTTON_C:
        Serial.println("C");
        activeChannel = BLUE;
        break; */
      default:
//        Serial.print("Unrecognized code received: 0x");
//        Serial.println(results.value, HEX);
        break;        
    }    
    analogWrite(FL,FLspeed);
    analogWrite(FR,FRspeed);
    analogWrite(RR,RRspeed);
    analogWrite(RL,RLspeed);
//    
//    Serial.print("Front Left: ");
//    Serial.println(FLspeed);
//    
//    Serial.print("Front Right: ");
//    Serial.println(FRspeed);
//    
//    Serial.print("Rear Left: ");
//    Serial.println(RLspeed);
    
    irrecv.resume(); // Receive the next value
  }

}
