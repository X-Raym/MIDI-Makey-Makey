 /*
Original version by MineMooder for http://www.instructables.com/id/Makey-Makey-MIDI-controller/.
Moded by X-Raym @http://www.extremraym.com
Mod Changes:
- Added Note Off message instead of Note On a velocity 0.
- Default velocity is 96.
*/

/*
This program is written for the makey makey ( http://www.makeymakey.com/ )
This program is based on the original arduino code for makey makey, which can be found here: https://dlnmh9ip6v2uc.cloudfront.net/tutorialimages/MaKey_MaKey_QuickStart/makey_makey_1_4_1.zip
In order for it to work you'll need this addon: https://dlnmh9ip6v2uc.cloudfront.net/tutorialimages/MaKey_MaKey_QuickStart/MaKeyMaKey-13-8-12.zip
Instructions for installing this addon can be found here: https://www.sparkfun.com/tutorials/388
The program send serial messages to your computer. These serial messages can be transformed into midi messages using a serial to midi converter like Hairless Midi ( http://projectgus.github.io/hairless-midiserial/ )
Make sure you go to the preferences to change the baud speed to 38400 !!

Problems or complaints (or compliments) can be send to minemooder@gmail.com
I think you are free to use this program. If it causes damage, that's not my fault!

*/
/////////////////////////
// Defining variables
////////////////////////

#define NUM_INPUTS       18    // 6 on the front + 12 on the back
#define TARGET_LOOP_TIME 744  // (1/56 seconds) / 24 samples = 744 microseconds per sample

// input status LED pin numbers
const int inputLED_a = 9;
const int inputLED_b = 10;
const int inputLED_c = 11;
const int outputK = 14;
const int outputM = 16;
byte ledCycleCounter = 0;

// timing
int loopTime = 0;
int prevTime = 0;
int loopCounter = 0;

// pins
int pinNumbers[NUM_INPUTS] = {
  12, 8, 13, 15, 7, 6,     // top of makey makey board
  5, 4, 3, 2, 1, 0,        // left side of female header
  23, 22, 21, 20, 19, 18   // right side of female header
};
boolean pinChange[NUM_INPUTS] = {0,0,0,0,0,0,0,0,0,0,0,0};
int pinState [NUM_INPUTS] = {0,0,0,0,0,0,0,0,0,0,0,0};

// This is the lowest note, you can change this note
//int note = 0x30; // This is C3 - 48
int note = 0x3C; // This is C4 - 60

void setup()
{

  Serial.begin(38400); // make sure your serial to midi converter reads at this speed
  for (int i=0; i<NUM_INPUTS; i++) //initializing inputs
  {
    pinMode(pinNumbers[i], INPUT);
    digitalWrite(pinNumbers[i], LOW);
  }

// LED stuff
  pinMode(inputLED_a, INPUT);
  pinMode(inputLED_b, INPUT);
  pinMode(inputLED_c, INPUT);
  digitalWrite(inputLED_a, LOW);
  digitalWrite(inputLED_b, LOW);
  digitalWrite(inputLED_c, LOW);

  pinMode(outputK, OUTPUT);
  pinMode(outputM, OUTPUT);
  digitalWrite(outputK, LOW);
  digitalWrite(outputM, LOW);

}
///////////////////////////
// MAIN LOOP
///////////////////////////

void loop() {

  // reading all input pins and sending out midi notes
  for (int i=0; i<NUM_INPUTS; i++) {

    (pinChange[i]) = (pinState[i]); // store previous pin states

    (pinState[i]) = (digitalRead(pinNumbers[i])); // get current pin states

    if (pinChange[i]!= (pinState[i]) ) {
     int msg = 0;
      if ( pinState[i] == 0 ) {
        msg = 0x90;
       } else {
        msg = 0x80;
      }
      sendNote(msg, note + i, 96); // if pin state is changed, send midi note.
    }
  }

  // this is LED stuff
  cycleLEDs();
  updateOutLEDs();
  addDelay();

}

///////////////////////////
// SENDING MIDI MESSAGE
///////////////////////////

void sendNote(int cmd, int pitch, int velocity) {

  // The midi message consists of three bytes: channel(in this case 1) , note (in this case 0x3C which is C3 plus a number between 0 and 18), velocity (which is max (0x7F) or zero, which turns the note off)

  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);

}


// THE REST OF THE CODE BELOW IS FOR TURNING THE LEDS ON THE MAKEY MAKEY ON AND OFF




///////////////////////////
// ADD DELAY
///////////////////////////
void addDelay() {

  loopTime = micros() - prevTime;
  if (loopTime < TARGET_LOOP_TIME) {
    int wait = TARGET_LOOP_TIME - loopTime;
    delayMicroseconds(wait);
  }

  prevTime = micros();



}

///////////////////////////
// CYCLE LEDS
///////////////////////////

// This is for the LEDs at the front

void cycleLEDs() {
  pinMode(inputLED_a, INPUT);
  pinMode(inputLED_b, INPUT);
  pinMode(inputLED_c, INPUT);
  digitalWrite(inputLED_a, LOW);
  digitalWrite(inputLED_b, LOW);
  digitalWrite(inputLED_c, LOW);

  ledCycleCounter++;
  ledCycleCounter %= 6;

  if ((ledCycleCounter == 0) && (!pinState[0])) {
    pinMode(inputLED_a, INPUT);
    digitalWrite(inputLED_a, HIGH);
    pinMode(inputLED_b, OUTPUT);
    digitalWrite(inputLED_b, HIGH);
    pinMode(inputLED_c, OUTPUT);
    digitalWrite(inputLED_c, LOW);
  }
  if ((ledCycleCounter == 1) && (!pinState[1])) {
    pinMode(inputLED_a, OUTPUT);
    digitalWrite(inputLED_a, HIGH);
    pinMode(inputLED_b, OUTPUT);
    digitalWrite(inputLED_b, LOW);
    pinMode(inputLED_c, INPUT);
    digitalWrite(inputLED_c, LOW);

  }
  if ((ledCycleCounter == 2) && (!pinState[2])) {
    pinMode(inputLED_a, OUTPUT);
    digitalWrite(inputLED_a, LOW);
    pinMode(inputLED_b, OUTPUT);
    digitalWrite(inputLED_b, HIGH);
    pinMode(inputLED_c, INPUT);
    digitalWrite(inputLED_c, LOW);
  }
  if ((ledCycleCounter == 3) && (!pinState[3])) {
    pinMode(inputLED_a, INPUT);
    digitalWrite(inputLED_a, LOW);
    pinMode(inputLED_b, OUTPUT);
    digitalWrite(inputLED_b, LOW);
    pinMode(inputLED_c, OUTPUT);
    digitalWrite(inputLED_c, HIGH);
  }
  if ((ledCycleCounter == 4) && (!pinState[4])) {
    pinMode(inputLED_a, OUTPUT);
    digitalWrite(inputLED_a, LOW);
    pinMode(inputLED_b, INPUT);
    digitalWrite(inputLED_b, LOW);
    pinMode(inputLED_c, OUTPUT);
    digitalWrite(inputLED_c, HIGH);
  }
  if ((ledCycleCounter == 5) && (!pinState[5])) {
    pinMode(inputLED_a, OUTPUT);
    digitalWrite(inputLED_a, HIGH);
    pinMode(inputLED_b, INPUT);
    digitalWrite(inputLED_b, LOW);
    pinMode(inputLED_c, OUTPUT);
    digitalWrite(inputLED_c, LOW);
  }

}

///////////////////////////
// OTHER LEDS
///////////////////////////

// This is for the LEDs at the back (they also light up when the front buttons are pressed)

void updateOutLEDs()
{
  boolean somethingPlayingLeft = 0;
  boolean somethingPlayingRight = 0;

  for (int i=0; i<NUM_INPUTS; i++)
  {
    if (!pinState[i] && i<12)
    {
      somethingPlayingLeft = 1;

      }
    if (!pinState[i] && (i>11 || i<6))
    {
      somethingPlayingRight = 1;

      }

  }

  if (somethingPlayingLeft)
  {
    TXLED1;
  }else{
    TXLED0;
   }

  if (somethingPlayingRight)
  {
    RXLED1;
  }else{
    RXLED0;
  }
}
