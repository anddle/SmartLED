int LED_PIN = 45;
int BUTTON_PIN = 44;
int oldButtonState = HIGH;
int powerOnOff = false;

void setup() {

 pinMode(LED_PIN, OUTPUT);
 pinMode(BUTTON_PIN, INPUT);
 Serial.begin(9600);
 Serial.println("init start");
 Serial2.begin(9600);
}

char buffer [1];
int keyPressCount = 0;

void loop() {

  int buttonState = digitalRead(BUTTON_PIN);
  bool powerChange = false;

  if(buttonState == LOW && oldButtonState == HIGH)
  {
    Serial.println("power press down");
    keyPressCount++;
    powerChange = true;
    oldButtonState = buttonState;
  }

  if(buttonState == HIGH && oldButtonState == LOW)
  {
    Serial.println("power press up");
    keyPressCount++;
    powerChange = true;
    oldButtonState = buttonState;
  }

  if(powerChange && keyPressCount % 2 == 0)
  {
    if(powerOnOff) 
    {
      Serial.println("power off");
      analogWrite(LED_PIN, 0);
      powerOnOff = false;
    }
    else
    {
      Serial.println("power on");
      analogWrite(LED_PIN, 255);
      powerOnOff = true;
    }

    return;
  }
  
  if (Serial2.available())
  {   
      int nReadSize = Serial2.readBytes(buffer, 1);
      if(nReadSize > 0)
      {
          Serial.println("Receive command");
          powerOnOff = true; 
          analogWrite(LED_PIN, buffer[0]);
      }
  }
}
