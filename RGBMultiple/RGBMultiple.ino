/*
Flashing RGB leds

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

*/

// Array of first pins of led's
int ledSet[] = {2, 5, 8, 11};

// Debug: 1 = on, 0 = off
int DEBUG = 1;

int wait = 1;      // 10ms internal crossFade delay; increase for slower fades
int hold = 100;       // Optional hold when a color is complete, before the next crossFade

// Array that holds RGB values. This can be seen and modified by all functions, so it doesn't have to be passed on to them.
int globalRGBarray[] = {0, 0, 0};

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
//  rotateColors(50);  
//  delay(2000);
  
  int ledNumber = random(0, 4);
  int timeOn = random(900, 1201);
//  oneFlash(ledNumber, timeOn);
  allFlash(timeOn);
  delay(1);
}

//--------------------------------------------------------------

void oneFlash(int ledNumber, int delayTime)
{
  setGlobalRGBarray2randomBrightColor();
  setLedColorOn(ledSet[ledNumber]);  
  delay(delayTime);
  turnLedOff(ledSet[ledNumber]);
}

void allFlash(int delayTime)
{
  setGlobalRGBarray2randomBrightColor();
  
  setLedColorOn(ledSet[0]);
  setLedColorOn(ledSet[1]);
  setLedColorOn(ledSet[2]);
  setLedColorOn(ledSet[3]);
  
  delay(delayTime);
  
  turnLedOff(ledSet[0]);
  turnLedOff(ledSet[1]);
  turnLedOff(ledSet[2]);
  turnLedOff(ledSet[3]);
}

void turnLedOff(int ledNumber)
{
  analogWrite(ledNumber, 0);
  analogWrite(ledNumber+1, 0);
  analogWrite(ledNumber+2, 0);  
}

void rotateColors(int delayTime)
{
  setGlobalRGBarray2randomBrightColor();
  setLedColorOn(ledSet[0]);
  delay(delayTime);
  
  setGlobalRGBarray2randomBrightColor();
  setLedColorOn(ledSet[1]);
  delay(delayTime);

  setGlobalRGBarray2randomBrightColor();
  setLedColorOn(ledSet[2]);
  delay(delayTime);

  setGlobalRGBarray2randomBrightColor();
  setLedColorOn(ledSet[3]);
  delay(delayTime);
}

//--------------------------------------------------------------

void setLedColorOn(int ledPrimer)
{
  analogWrite(ledPrimer, globalRGBarray[0]);
  analogWrite(ledPrimer+1, globalRGBarray[1]);
  analogWrite(ledPrimer+2, globalRGBarray[2]);  
}

//--------------------------------------------------------------
// Modifies color array: creates new random saturated color

void setGlobalRGBarray2randomBrightColor()
{
  int color1 = random(0, 256);
  int color2 = 256 - color1;
  
  int select = random(0, 3);
  

  if (select == 0)
  {
        Serial.println("h1");
      globalRGBarray[0] = color1;
      globalRGBarray[1] = color2;
      globalRGBarray[2] = 0;
  }
  else
  {
    if (select == 1)
    {
        Serial.println("h2");
      globalRGBarray[0] = 0;
      globalRGBarray[1] = color1;
      globalRGBarray[2] = color2;
    }
    else
    {
        Serial.println("h3");
      globalRGBarray[0] = color1;
      globalRGBarray[1] = 0;
      globalRGBarray[2] = color2;
    }
  }

  
  Serial.print(select);
  Serial.print(" / ");
  Serial.print(globalRGBarray[0]);
  Serial.print(", ");
  Serial.print(globalRGBarray[1]);  
  Serial.print(", ");
  Serial.println(globalRGBarray[2]);

}

