const unsigned int LED_PIN = 12;
const unsigned int BUTTON_PIN = 10;
const unsigned int BAUD_RATE = 9600;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(BAUD_RATE); // <label id="code.welcome.init_serial"/>
}

int lastButtonState = LOW;
int buttonState;
boolean buttonOn = false;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void loop() {
  checkButton();
  if (buttonOn) {
     digitalWrite(LED_PIN, HIGH);
  } else {
     digitalWrite(LED_PIN, LOW);
  }
}

void checkButton() {
  int reading = digitalRead(BUTTON_PIN);
  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the button if the new button state is HIGH
      if (buttonState == HIGH) {
        buttonOn = !buttonOn;
        Serial.print("button toggle: ");
        Serial.println(buttonOn ? "true" : "false");
      }
    }
  }
  lastButtonState = reading;
}
