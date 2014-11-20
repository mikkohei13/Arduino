/* Tuikku
    Sytyttää ledejä rinnakkaisesti
 */

const int PIN_COUNT = 6;
int myPins[] = {3, 5, 6, 9, 10, 11};
int history[] = {0, 0, 0, 0, 0, 0};
int previousLed = 0;
int randomLed = 0;
int newPin = 0;

int x = 0;
int i = 0;
int y = 0;

int chancePercent = 0;

void setup() {
  for (int i=0; i <= (PIN_COUNT - 1); i++)
  {
    pinMode(myPins[i], OUTPUT);      
  }
  Serial.begin(9600);
}

void loop()
{
  // Set up new pin
  chancePercent = 20; // Chance of lighting a new led up
  if (random(1, 100) > (100 - chancePercent))
  {
    newPin = random(0, PIN_COUNT);
    if(history[newPin] == 0) // light up only non-lit pins
    {
      history[newPin] = 10;
    }
  }
  
  // Goe through pins and light up those that have been set up
  for(x = 0; x <= (PIN_COUNT - 1); x++)
  {
    analogWrite(myPins[x], 25 * history[x]); // fade out
    
    // substract from history
    if(history[x] > 0)
    {
      history[x] = history[x] - 1;
    }
  }
  
  delay(50);
  
  /*
  randomLed = random(0, 6);
  while(randomLed == previousLed)
  {
    randomLed = random(0, 6);
  }
  previousLed = randomLed;
  
  //--------------
  
  strobeRandomBrightness(randomLed);
  */
}

//----------------------------------------------------
// Strobe then delay

int strobe(int pinIndex)
{
  analogWrite(myPins[pinIndex], 255);
  delay(50);
  analogWrite(myPins[pinIndex], 0);
  delay(100);
}

//----------------------------------------------------
// Strobe then delay

int strobeRandomBrightness(int pinIndex)
{
  int brightness = random(1, 16);
  brightness = brightness*brightness;
//  Serial.println("pin");   Serial.println(pinIndex);  Serial.println(brightness); // DEBUG
  
  analogWrite(myPins[pinIndex], (brightness));
  delay(50);
  analogWrite(myPins[pinIndex], 0);
  delay(100);
}

//----------------------------------------------------
// Fades in and out

int fadeInOut(int pinIndex, int interval)
{
  // fade in
  for (i=0; i <= 255; i = i+1)
  {
    analogWrite(myPins[pinIndex], i);
    delay(interval);
  }
  // fade out
  for (y=255; y >= 0; y=y-1)
  {
    analogWrite(myPins[pinIndex], y);
    delay(interval);
  }

}
