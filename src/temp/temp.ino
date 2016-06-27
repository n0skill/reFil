const long interval           = 300;
unsigned long previousMillis  = 0;
bool decaFlag                 = LOW;
bool blinkk = HIGH;

float getResistor()
{
  float Vout = (4.2 / 1024.0) * analogRead(A0); // Reads value on analog port 0
  delay(2);
  float dummyLoad = 10000.0; // ohms
  return (Vout * dummyLoad / (4.2 - Vout));
}

float getTemperature(float mesuredOhms)
{
  float factA   = 3.9083e-3;
  float factB   = -5.775e-7;
  float nominal = 1000.0;

  float fltTemperature = (-nominal * factA + (sqrt(pow((nominal * factA), 2)
                          - 4 * nominal * factB * (nominal - mesuredOhms)))) /
                         float((2 * nominal * factB));
  Serial.print("Ohms: ");
  Serial.println(mesuredOhms);

  Serial.print("Temp: ");
  Serial.println(fltTemperature);
  Serial.print('\n');
  return fltTemperature;
}

void dispNull()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}
void disp(int number)
{
  byte BCD[11][4] =
  {
    {0, 0, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 1},
    {1, 0, 1, 0}
  };

  digitalWrite(2, BCD[number][3]);
  digitalWrite(3, BCD[number][2]);
  digitalWrite(4, BCD[number][1]);
  digitalWrite(5, BCD[number][0]);

  
}


void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(6, blinkk);
  digitalWrite(7, !blinkk);
  blinkk = !blinkk;
  unsigned long currentMillis = millis();
  int temp = getTemperature(getResistor());
//  Serial.println(unit);
  if(temp >= 100){
    disp((temp/100)%10);
    delay(250);
    dispNull();
    delay(100);
  }
  if(temp >= 10) {
    disp((temp/10)%10);
    delay(250);
    dispNull();
    delay(100);
  }
  
  if(temp >= 1) {
    disp(temp%10);
    delay(250);
    dispNull();
    delay(100);
  }
  dispNull();
  
  delay(3
  opio00);
}


