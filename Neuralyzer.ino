/*
  Neuralyzer
 */

const int buttonPin = 2;
const int GreenPin = 5;
const int OrangePin = 7;
const int RedPin = 9;
const int BackPin = 13;
const int FlashPin = 12;

//const long interval = 200;  // interval at which to blink 
unsigned long interval = 100;  // interval at which to blink 
const long flashval = 50;   // How long the flash is for

// Variables will change:
int GreenState = LOW;
int OrangeState = LOW;
int RedState = LOW;
int BackState = LOW;
int FlashState = LOW;

int buttonState;
int lastButtonState = LOW; 

long lastDebounceTime = 0;
long debounceDelay = 50;
unsigned long previousMillis = 0;


#define UP true
#define DOWN false


// Array with Arduino pins containing LEDs in sequence
byte LEDpins[] = {OrangePin,RedPin,OrangePin,GreenPin};
 
// Variable to track which LED to turn on, start at 000001
int LEDstate=0x01;
 
// State variable to know which direction to shift
boolean direction=UP;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(OrangePin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(BackPin, OUTPUT);
  pinMode(FlashPin, OUTPUT);

  // set initial LED state
  digitalWrite(GreenPin, GreenState);
  digitalWrite(OrangePin, OrangeState);
  digitalWrite(RedPin, RedState);
  digitalWrite(BackPin, RedState);

   Serial.begin(9600);
  Serial.println("Hello world");
  delay(2000);// Give reader a chance to see the output.
  
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
            digitalWrite(RedPin, HIGH);
            digitalWrite(GreenPin, HIGH);
            digitalWrite(FlashPin, HIGH);
            delay(flashval); 
            digitalWrite(RedPin, LOW);
            digitalWrite(FlashPin, LOW);
            
      }
    }
  }

//  unsigned long currentMillis = millis();


  for (int x=0; x < 4; x++)
    digitalWrite(LEDpins[x], bitRead(LEDstate,x));


 // for (int x=0; x < 3; x++)
 // Serial.println(bitRead(LEDstate,x));


 Serial.println("---------------");
  // Test Funciton to turn on all LEDs with pushbutton
  //  turnOnAll();
    
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    // We've waited "interval" amount of time, so let's do some stuff!

    if (BackState == LOW) {
      BackState = HIGH;
    } else {
      BackState = LOW;
    }
    
 digitalWrite(BackPin, BackState);

 
    // "Reset" our clock
    previousMillis = currentMillis;
 
    if (direction==UP) {
      // Use "<<" to "bit-shift" everything to the left once
      LEDstate = LEDstate << 1;
      // 0x20 is the "last" LED, another shift makes the value 0x40
      if (LEDstate == 0x40) {
        // turn on the one before "0x20" and reverse direction
        LEDstate = 0x10;
        direction = DOWN;
      }
    }
    else {
      // use "&gt;&gt;" to "bit-shift" all bits in LEDstate once to the right
      LEDstate = LEDstate << 1;
      // This means we ran out of bits!
      if (LEDstate == 0x00) {
        // set one ahead so no extra delay
        LEDstate = 0x02;
        direction = UP;
      }
    }
  }
    
 // }
  
  //digitalWrite(RedPin, RedState);
  //digitalWrite(GreenPin, GreenState);

  lastButtonState = reading;
}


void turnOnAll() {
    for (int x=0; x< 3; x++)
      digitalWrite(LEDpins[x], HIGH);
}
