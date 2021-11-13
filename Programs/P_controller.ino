//using only P of PID controller 

#include<PID_v1.h>
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

double Setpoint = 3500;

double Input, Output;

double Kp = 0.017;
double Kd = 0;
double Ki = 0;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

int motorPow = 0;

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

  digitalWrite(motorEnable, LOW);

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);
  myPID.SetSampleTime(5);
  //myPID.SetControllerDirection(REVERSE);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {
    3, 4, 19, 18, 17, 16, 15, 14
  }, SensorCount);

  //calibrate
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
  Input = qtr.readLineBlack(sensorValues);

  myPID.Compute();

  //straight
  if ((Output < 4) & (Output > -4))
  {
    motorPow = map(Output, -4, 4, 0, 4);
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
  else if (Output > 4)
  {
    digitalWrite(BmotorDir, LOW);
    analogWrite(BmotorPow, 195 + Output);
    digitalWrite(DmotorDir, LOW);
    analogWrite(DmotorPow, 195 + Output);
    digitalWrite(AmotorDir, HIGH);
    analogWrite(AmotorPow, 60 - Output);
    digitalWrite(CmotorDir, HIGH);
    analogWrite(CmotorPow, 60 - Output);
  }

  //turn left
  else if (Output < -4)
  {
    digitalWrite(BmotorDir, HIGH);
    analogWrite(BmotorPow, 60 - abs(Output));
    digitalWrite(DmotorDir, HIGH);
    analogWrite(DmotorPow, 60 - abs(Output));
    digitalWrite(AmotorDir, LOW);
    analogWrite(AmotorPow, 195 + abs(Output));
    digitalWrite(CmotorDir, LOW);
    analogWrite(CmotorPow, 195 + abs(Output));
  }
}
