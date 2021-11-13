//using conditional statements

#include<QTRSensors.h>

#define motorEnable 2
#define AmotorPow 11
#define AmotorDir 12
#define BmotorPow 10
#define BmotorDir 5
#define CmotorPow 9
#define CmotorDir 8
#define DmotorPow 6
#define DmotorDir 7

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

int Input;

int motorPow = 0;
int neededmotorPow = 0;
int turnDirec = 0;

unsigned long currentTime = 0;
unsigned long prevTime = 0;
unsigned long elapsedTime = 0;

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

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {
    3, 4, 19, 18, 17, 16, 15, 14
  }, SensorCount);

  digitalWrite(motorEnable, LOW);

  //calibration
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);

  digitalWrite(motorEnable, HIGH);

}

void loop()
{
  currentTime = millis();
  elapsedTime = currentTime - prevTime;

  Input = qtr.readLineBlack(sensorValues);

  //case 1 extreme left
  if ((Input > 0) & (Input < 250))
  {
    neededmotorPow = 0;
    turnDirec = 0;
  }

  //case 2 left
  else if ((Input > 250) & (Input < 750))
  {
    neededmotorPow = 7;
    turnDirec = 0;
  }

  //case 3 left
  else if ((Input > 750) & (Input < 1250))
  {
    neededmotorPow = 14;
    turnDirec = 0;
  }

  //case 4 left
  else if ((Input > 1250) & (Input < 1750))
  {
    neededmotorPow = 21;
    turnDirec = 0;
  }

  //case 5 left
  else if ((Input > 1750) & (Input < 2250))
  {
    neededmotorPow = 28;

    turnDirec = 0;
  }

  //case 6 left
  else if ((Input > 2250) & (Input < 2750))
  {
    neededmotorPow = 35;
    turnDirec = 0;
  }

  //case 7 left
  else if ((Input > 2750) & (Input < 3250))
  {
    neededmotorPow = 42;
    turnDirec = 0;
  }

  //case 8 go straight
  else if ((Input > 3250) & (Input < 3750))
  {
    neededmotorPow = 47;
    turnDirec = 1;
  }

  //case 9 right
  else if ((Input > 3750) & (Input < 4250))
  {
    neededmotorPow = 42;
    turnDirec = 2;
  }

  //case 10 right
  else if ((Input > 4250) & (Input < 4750))
  {
    neededmotorPow = 35;
    turnDirec = 2;
  }

  //case 11 right
  else if ((Input > 4750) & (Input < 5250))
  {
    neededmotorPow = 28;
    turnDirec = 2;
  }

  //case 12 right
  else if ((Input > 5250) & (Input < 5750))
  {
    neededmotorPow = 21;
    turnDirec = 2;
  }

  //case 13 right
  else if ((Input > 5750) & (Input < 6250))
  {
    neededmotorPow = 14;
    turnDirec = 2;
  }

  //case 14 right
  else if ((Input > 6250) & (Input < 6750))
  {
    neededmotorPow = 7;
    turnDirec = 2;
  }

  //case 15 exterme right
  else if ((Input > 6750) & (Input < 7250))
  {
    neededmotorPow = 0;
    turnDirec = 2;
  }

  //stop
  else
  {
    neededmotorPow = 255;
    turnDirec = 1;
  }


  if (elapsedTime > 100)
  {
    if (motorPow > neededmotorPow)
    {
      motorPow--;
    }
    else if (motorPow < neededmotorPow)
    {
      motorPow++;
    }
    prevTime = currentTime;
  }

  //left
  if (turnDirec == 0)
  {
    digitalWrite(AmotorDir, HIGH);
    analogWrite(AmotorPow, motorPow);
    digitalWrite(CmotorDir, HIGH);
    analogWrite(CmotorPow, motorPow);
    digitalWrite(BmotorDir, LOW);
    analogWrite(BmotorPow, 255 - motorPow);
    digitalWrite(DmotorDir, LOW);
    analogWrite(DmotorPow, 255 - motorPow);
  }

  //straight
  if (turnDirec == 1)
  {
    digitalWrite(AmotorDir, HIGH);
    analogWrite(AmotorPow, motorPow);
    digitalWrite(CmotorDir, HIGH);
    analogWrite(CmotorPow, motorPow);
    digitalWrite(BmotorDir, HIGH);
    analogWrite(BmotorPow, motorPow);
    digitalWrite(DmotorDir, HIGH);
    analogWrite(DmotorPow, motorPow);
  }

  //right
  if (turnDirec == 2)
  {
    digitalWrite(AmotorDir, LOW);
    analogWrite(AmotorPow, 255 - motorPow);
    digitalWrite(CmotorDir, LOW);
    analogWrite(CmotorPow, 255 - motorPow);
    digitalWrite(BmotorDir, HIGH);
    analogWrite(BmotorPow, motorPow);
    digitalWrite(DmotorDir, HIGH);
    analogWrite(DmotorPow, motorPow);
  }
}
