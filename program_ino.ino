String comdata = "status: ";
const int lightA0 = A5;
const int lightD0 = 2;
const int TrigPin = 6;
const int EchoPin = 5;
const int lightone = 8;
const int lighttwo = 9;
const int lightthree = 10;


void setup()
{
    Serial.begin(9600);
    pinMode(lightD0, INPUT);
    pinMode(lightA0, INPUT);
    pinMode(lightone, OUTPUT);
    pinMode(lighttwo, OUTPUT);
    pinMode(lightthree, OUTPUT);
    pinMode(TrigPin,OUTPUT); 
    pinMode(EchoPin, INPUT);
}

void loop()
{
  float distance = 0;
  float tempdis[10] = {0};
  float tempdis1[10] = {0};
  int sum = 0;
  for(int y = 0; y < 10; y++)
  {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    tempdis[y] = pulseIn(EchoPin, HIGH)/58.0;
    sum += tempdis[y];
  }
  sum = sum/10;
  for(int y = 0; y < 10; y++)
    tempdis1[y] = abs(sum-tempdis[y]);
  for(int y = 0; y < 9; y++)
  {
    if(tempdis1[y] < tempdis1[y+1])
      distance = tempdis[y];
    else
      distance = tempdis[y+1];
  } 
  if(distance < 15 || distance > 450)
    return ;
  Serial.print("distance = ");
  Serial.print(distance);
  Serial.println("cm");
  int sumlightA = 0;
  for(int i = 0; i < 10; i++)
  {
    int temp = analogRead(lightA0);
    sumlightA += temp;
  }
  sumlightA = sumlightA/10;
  Serial.print("lightA0 = ");
  Serial.println(sumlightA);
  int lightD = digitalRead(lightD0);
  Serial.print(lightD);
  if(distance <= 120 && sumlightA >= 900)
    openlight();
  else
    closelight();
  delay(1000);
}

void openlight()
{
  digitalWrite(lightone, HIGH);
  digitalWrite(lighttwo, HIGH);
  digitalWrite(lightthree, HIGH);
}

void closelight()
{
  digitalWrite(lightone, LOW);
  digitalWrite(lighttwo, LOW);
  digitalWrite(lightthree, LOW);
}
