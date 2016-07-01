bool decaFlag       = LOW;
const int maxTemp   = 25;
const int margin    = 3;
const int targTemp  = 220;

void dispMode() {
  dispNum(targTemp, 200);
}

void heatingControl()
{
  float temp = getTemperature(getResistor());
  
  if(temp < maxTemp - margin) {
    digitalWrite(6, HIGH);
  }
  else if(temp > maxTemp + margin) {
    digitalWrite(6, LOW);
  }
}

float getResistor() {
  float Vout = (4.2 / 1024.0) * analogRead(A0); // Reads value on analog port 0
  delay(2);
  float dummyLoad = 10000.0; // ohms
  return (Vout * dummyLoad / (4.2 - Vout));
}

float getTemperature(float mesuredOhms) {
  float factA   = 3.9083e-3;
  float factB   = -5.775e-7;
  float nominal = 1000.0;

  float fltTemperature =  (-nominal * factA +
                          (sqrt(pow((nominal * factA), 2)
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
void dispNum(int num, int del)
{
  if(num >= 100)
  {
      disp((num/100)%10);
      delay(del);
      dispNull();
      delay(del/2);
  }
  if(num >= 10)
  {
      disp((num/10)%10);
      delay(del);
      dispNull();
      delay(del/2);
  }
  if(num >= 1) {
      disp(num%10);
      delay(del);
      dispNull();
      delay(del);
  }
    delay(del);
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

bool readState()
{
  bool s = digitalRead(9);  return s;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, INPUT);
  Serial.begin(9600);

  dispNull();
}

void loop() {
  if(readState())
  {
    digitalWrite(13, HIGH);
    dispMode();
    delay(200);
  }
  else 
  {
    digitalWrite(13, LOW);
    unsigned long currentMillis = millis();
    int temp = getTemperature(getResistor());
    dispNum(temp, 400);
    heatingControl();
  }
  delay(300);
}




