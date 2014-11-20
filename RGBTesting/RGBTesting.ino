/*
BASED ON:

Color Crossfader tutorial
http://arduino.cc/en/Tutorial/ColorCrossfader
April 2007, Clay Shirky <clay.shirky@nyu.edu> 
Creative Commons Attribution ShareAlike 3.0.
http://creativecommons.org/licenses/by-sa/3.0/

Adafruit Arduino - Lesson 3. RGB LED
Simon Monk
Last updated on 2012-11-30 
http://learn.adafruit.com/adafruit-arduino-lesson-3-rgb-leds/arduino-sketch

int ledSet1 = 2;
int ledSet2 = 5;
int ledSet3 = 8;
int ledSet4 = 11;

*/

int ledSet[] = {2, 5, 8, 11};

int DEBUG = 1;

int wait = 1;      // 10ms internal crossFade delay; increase for slower fades
int hold = 100;       // Optional hold when a color is complete, before the next crossFade

int arra[] = {0, 0, 0};

//--------------------------------------------------------------
 
void setup()
{
  for (int i=0; i < 4; i++)
  {
    pinMode(ledSet[i], OUTPUT);
    pinMode(ledSet[i]+1, OUTPUT);
    pinMode(ledSet[i]+2, OUTPUT);
  }
  
  if (DEBUG)
  {
    Serial.begin(9600);
  }
}
 
//--------------------------------------------------------------

void loop()
{
  rotateColors(50);  
  delay(2000);
  
//  setColor(2, 0, 0, 255);
//  delay(1000);
  
  /*
  int ledNumber = random(0, 4);
  oneFlash(ledNumber, 500);
  delay(0);
  */
}

//--------------------------------------------------------------

void oneFlash(int led, int delayTime)
{
  arraRandomBrightColor();
  setColor(ledSet[led], arra[0], arra[1], arra[2]);  
  delay(delayTime);
  turnOff(ledSet[led]);
}

void turnOff(int ledPrimer)
{
  analogWrite(ledPrimer, 0);
  analogWrite(ledPrimer+1, 0);
  analogWrite(ledPrimer+2, 0);  
}

void rotateColors(int delayTime)
{
  arraRandomBrightColor();
  setColor(ledSet[0], arra[0], arra[1], arra[2]);
  delay(delayTime);
  
  arraRandomBrightColor();
  setColor(ledSet[1], arra[0], arra[1], arra[2]);
  delay(delayTime);

  arraRandomBrightColor();
  setColor(ledSet[2], arra[0], arra[1], arra[2]);
  delay(delayTime);

  arraRandomBrightColor();
  setColor(ledSet[3], arra[0], arra[1], arra[2]);
  delay(delayTime);
}

//--------------------------------------------------------------

void setColor(int ledPrimer, int red, int green, int blue)
{
  analogWrite(ledPrimer, red);
  analogWrite(ledPrimer+1, green);
  analogWrite(ledPrimer+2, blue);  
}

//--------------------------------------------------------------
// Modifies color array: creates new random saturated color

void arraRandomBrightColor()
{
 int color1 = random(0, 256);
  int color2 = 256 - color1;
  
  int select = random(0, 3);
  

  if (select == 0)
  {
        Serial.println("h1");
      arra[0] = color1;
      arra[1] = color2;
      arra[2] = 0;
  }
  else
  {
    if (select == 1)
    {
        Serial.println("h2");
      arra[0] = 0;
      arra[1] = color1;
      arra[2] = color2;
    }
    else
    {
        Serial.println("h3");
      arra[0] = color1;
      arra[1] = 0;
      arra[2] = color2;
    }
  }

  
  Serial.print(select);
  Serial.print(" / ");
  Serial.print(arra[0]);
  Serial.print(", ");
  Serial.print(arra[1]);  
  Serial.print(", ");
  Serial.println(arra[2]);

}

