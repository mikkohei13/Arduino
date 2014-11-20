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


*/

int redPin = 2;
int grnPin = 3;
int bluPin = 4;

// Set initial color
int redVal = 0;
int grnVal = 0; 
int bluVal = 0;

int wait = 1;      // 10ms internal crossFade delay; increase for slower fades
int hold = 100;       // Optional hold when a color is complete, before the next crossFade
int DEBUG = 1;      // DEBUG counter; if set to 1, will write values back via serial
int loopCount = 60; // How often should DEBUG report?
/*int repeat = 0;     // How many times should we loop before stopping? (0 for no stop)
int j = 0;          // Loop counter for repeat
*/

// Initialize color variables
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

int arra[] = {0, 0, 0};


//--------------------------------------------------------------
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  
  if (DEBUG)
  {
    Serial.begin(9600);
  }
}
 
//--------------------------------------------------------------

void loop()
{
  // randomise times
  wait = random(1, 4);
  hold = random(50, 150);
  
  // randomize color
  returnRandomColor();
  
  // fade
  crossFade(arra);
  
}

//--------------------------------------------------------------
// Modifies color array: creates new random saturated color

void returnRandomBrightColor()
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

//--------------------------------------------------------------

void setRandomBrightColor()
{
  int color1 = random(0, 256);
  int color2 = 256 - color1;
  
  int select = random(0, 3);
  if (select == 0)
  {
    setColor(color1, color2, 0);
  }
  else
  {
    if (select == 1)
    {
      setColor(0, color1, color2);
    }
    else
    {
      setColor(color1, 0, color2);
    }
  }
  
  // Debug
  Serial.print(color1);
  Serial.print(" / ");
  Serial.print(color2);
  Serial.print(" // ");
  Serial.println(select);
}

//--------------------------------------------------------------
 
void returnRandomColor()
{
  int colors[] = {0, 0, 0};
  int off = random(0, 3);
  
  colors[0] = random(1, 256);
  colors[1] = random(1, 256);
  colors[2] = random(1, 256);

  colors[off] = 0;
  
  arra[0] = colors[0];
  arra[1] = colors[1];
  arra[2] = colors[2];
}

//--------------------------------------------------------------
void setRandomColor()
{
  int colors[] = {0, 0, 0};
  int off = random(0, 3);
  
  colors[0] = random(1, 255);
  colors[1] = random(1, 255);
  colors[2] = random(1, 255);

  colors[off] = 0;
  
  setColor(colors[0], colors[1], colors[2]);
}

//--------------------------------------------------------------

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(grnPin, green);
  analogWrite(bluPin, blue);  
}


//--------------------------------------------------------------
//--------------------------------------------------------------
// TEMP

/*
  setColor(0xDD, 0xDD, 0x00);
  for (int i = 0; i <= 255; i++)
  {
    setColor(0, 255, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--)
  {
    setColor(0, 255, i);
    delay(10);
  }
  */


/* BELOW THIS LINE IS THE MATH -- YOU SHOULDN'T NEED TO CHANGE THIS FOR THE BASICS
* 
* The program works like this:
* Imagine a crossfade that moves the red LED from 0-10, 
*   the green from 0-5, and the blue from 10 to 7, in
*   ten steps.
*   We'd want to count the 10 steps and increase or 
*   decrease color values in evenly stepped increments.
*   Imagine a + indicates raising a value by 1, and a -
*   equals lowering it. Our 10 step fade would look like:
* 
*   1 2 3 4 5 6 7 8 9 10
* R + + + + + + + + + +
* G   +   +   +   +   +
* B     -     -     -
* 
* The red rises from 0 to 10 in ten steps, the green from 
* 0-5 in 5 steps, and the blue falls from 10 to 7 in three steps.
* 
* In the real program, the color percentages are converted to 
* 0-255 values, and there are 1020 steps (255*4).
* 
* To figure out how big a step there should be between one up- or
* down-tick of one of the LED values, we call calculateStep(), 
* which calculates the absolute gap between the start and end values, 
* and then divides that gap by 1020 to determine the size of the step  
* between adjustments in the value.
*/

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1. 
*  (R, G, and B are each calculated separately.)
*/

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

/* crossFade() converts the percentage colors to a 
*  0-255 range, then loops 1020 times, checking to see if  
*  the value needs to be updated each time, then writing
*  the color values to the correct pins.
*/

void crossFade(int color[3]) {
  // Convert to 0-255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(redPin, redVal);   // Write current values to LED pins
    analogWrite(grnPin, grnVal);      
    analogWrite(bluPin, bluVal); 

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop

    if (DEBUG) { // If we want serial output, print it at the 
      if (i == 0 or i % loopCount == 0) { // beginning, and every loopCount times
/*        Serial.print("Loop/RGB: #");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(redVal);
        Serial.print(" / ");
        Serial.print(grnVal);
        Serial.print(" / ");  
        Serial.println(bluVal); */
      } 
      DEBUG += 1;
    }
  }
  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}
