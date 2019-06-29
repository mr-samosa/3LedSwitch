int switchPin = 10;
int led1 = 2;
int led2 = 3;
int led3 = 4;
boolean currentButton = false;
boolean lastButton = false;

boolean led1On = false;
boolean led2On = false;
boolean led3On = false;
boolean led4On = false;

int ledCount = 0;

long lastTime = 0;
long currentTime = 0;
long elapsed = 0;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  if (buttonPressed() && elapsed < 1000) {
    ledCount ++;
  }

  else if (elapsed > 5000) {
    reset();
  }
  checkLights();
  lastButton = currentButton;
}


void reset() {
  turnOff(led1); turnOff(led2); turnOff(led3);
  ledCount = 0;
}

void checkLights() {
  if (ledCount > 3 || elapsed >= 1000) {
    reset();
    return;

  }
  switch (ledCount) {
    case 1:
      turnOn(led1);
      turnOff(led2); turnOff(led3);
      
      Serial.println(true);
    case 2:
      turnOn(led2);
      turnOff(led3);
    case 3:
      turnOn(led3);
  }


}

void checkElapsed() {

  currentTime = millis();
  elapsed = currentTime - lastTime;

}

boolean buttonPressed() {
  //retrieves proper value for button press
  currentButton = debounce(lastButton);

  //if there is a change and button is currently pressed

  if (currentButton != lastButton && currentButton) {
    checkElapsed();
    lastTime = currentTime;
    return true;
  }
  else {
    return false;
  }


}

void turnOff(int n) {
  digitalWrite(n, LOW);
}
void turnOn(int n) {
  digitalWrite(n, HIGH);
}


boolean debounce(boolean last) {
  boolean current = digitalRead(switchPin);
  if (current != last) {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;

}
