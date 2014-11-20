/*


*/

int redPin = 2;
int grnPin = 3;
int bluPin = 4;

int DEBUG = 0;

int hold = 70;
int wait = 30;

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

  flash(redPin);
  delay(wait);  
  flash(grnPin);
  delay(wait);  
  flash(bluPin);
  delay(wait);
  
  delay (1000);
  
}

//--------------------------------------------------------------

void flash(int pin)
{
  analogWrite(pin, 255);
  delay(hold);
  analogWrite(pin, 0); 
}

//--------------------------------------------------------------

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(grnPin, green);
  analogWrite(bluPin, blue);  
}

