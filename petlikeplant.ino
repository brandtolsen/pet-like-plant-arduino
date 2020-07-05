#include <Servo.h>
const int buzzerPin = 12; // Buzzer is in pin 12

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading = 0;     // the analog reading from the sensor divider
int val = 0; // Holds a value for the last light range used
int valNew = 0; // Assigned when a new light range is present
String condition = "none";
int happyTones[] = {1520, 1136, 863, 2093, 234, 3951, 574, 4186};
int happyTonesEx[] = {2520, 1136, 863, 4093, 234, 5951, 174, 2186};
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int stepSpeed = 100; //ms



void setup()
{


  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.print("i am started");

  for (pos = pos; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    Serial.println("left");
  }
}


void loop()

{

  photocellReading = analogRead(photocellPin); //photocell values

  //Monitor stuff
  Serial.print("Photocell reading reading = ");
  Serial.println(photocellReading);     // the raw analog reading
  Serial.print("Val - ");
  Serial.println(val);


  if (photocellReading < 250) {
    //Dark
    tone(buzzerPin, 250);
    tone(buzzerPin, random(10, 200));
    delay(500);
    noTone(buzzerPin);
    delay(random(10, 1500));
    valNew = 1;


  } else {
    //Super shiny!
    noTone(buzzerPin);
    valNew = 3;

  }




  if (valNew == val) {
    // If light range is unchanged - do nothing
    Serial.print("It is still - ");
    Serial.println(condition);
    Serial.print("and the position is ");
    Serial.println(pos);
    delay(2500);
    myservo.detach();

  } else if (valNew == 1) {
    myservo.attach(9);
    condition = "dark";
    Serial.print("It is now DARK");
    for (pos = 0; pos <= 5; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(stepSpeed);                       // waits 15ms for the servo to reach the position
      Serial.println("dark");
    }
    val = valNew;

  } else if (valNew == 3) {
    myservo.attach(9);
    condition = "bright";
    for (int notePlay = 0; notePlay < 8; notePlay++) {
      int noteRandom = random(7);
      tone(buzzerPin, happyTonesEx[noteRandom], 150);
      delay(50);
      noTone(8);
    }

    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(stepSpeed);                       // waits 15ms for the servo to reach the position
      Serial.println("bright");
    }
    val = valNew;
  }
}
