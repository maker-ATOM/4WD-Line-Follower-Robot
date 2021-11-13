#define motorEnable 2

#define AmotorPow 11
#define AmotorDir 12
#define BmotorPow 10
#define BmotorDir 5
#define CmotorPow 9
#define CmotorDir 8
#define DmotorPow 6
#define DmotorDir 7


void setup()
{

  pinMode(motorEnable, OUTPUT);

  pinMode(AmotorPow, OUTPUT);
  pinMode(AmotorDir, OUTPUT);
  pinMode(BmotorPow, OUTPUT);
  pinMode(BmotorDir, OUTPUT);
  pinMode(CmotorPow, OUTPUT);
  pinMode(CmotorDir, OUTPUT);
  pinMode(DmotorPow, OUTPUT);
  pinMode(DmotorDir, OUTPUT);

  digitalWrite(motorEnable, HIGH);

  delay(2000);

}

void loop()
{
  //move forward
  digitalWrite(AmotorDir, HIGH);
  analogWrite(AmotorPow, 0);
  digitalWrite(CmotorDir, HIGH);
  analogWrite(CmotorPow, 0);
  digitalWrite(BmotorDir, HIGH);
  analogWrite(BmotorPow, 0);
  digitalWrite(DmotorDir, HIGH);
  analogWrite(DmotorPow, 0);
  delay(1300);

  //stop
  digitalWrite(AmotorDir, LOW);
  analogWrite(AmotorPow, 0);
  digitalWrite(CmotorDir, LOW);
  analogWrite(CmotorPow, 0);
  digitalWrite(BmotorDir, LOW);
  analogWrite(BmotorPow, 0);
  digitalWrite(DmotorDir, LOW);
  analogWrite(DmotorPow, 0);
  delay(400);

  //rotate clockwise
  digitalWrite(AmotorDir, HIGH);
  analogWrite(AmotorPow, 0);
  digitalWrite(CmotorDir, HIGH);
  analogWrite(CmotorPow, 0);
  digitalWrite(BmotorDir, LOW);
  analogWrite(BmotorPow, 255);
  digitalWrite(DmotorDir, LOW);
  analogWrite(DmotorPow, 255);
  delay(500);

  //stop
  digitalWrite(AmotorDir, LOW);
  analogWrite(AmotorPow, 0);
  digitalWrite(CmotorDir, LOW);
  analogWrite(CmotorPow, 0);
  digitalWrite(BmotorDir, LOW);
  analogWrite(BmotorPow, 0);
  digitalWrite(DmotorDir, LOW);
  analogWrite(DmotorPow, 0);
  delay(400);
}
