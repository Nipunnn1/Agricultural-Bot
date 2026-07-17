/*
Arduino UNO 2

CH5 -> Mode Switch
    LOW  = Vehicle Mode
    HIGH = Arm Mode

CH6 -> Arm Control
    1000-1400 = Down / Close
    1600-2000 = Up / Open
*/

#define CH5 2
#define CH6 3

// Arm 
#define ENA 5
#define IN1 6
#define IN2 7

// Gripper 
#define ENB 9
#define IN3 10
#define IN4 11

void setup()
{
  pinMode(CH5,INPUT);
  pinMode(CH6,INPUT);

  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}

void loop()
{
  int mode = pulseIn(CH5,HIGH,25000);

  if(mode<1530)
  {
    stopAll();
    return;
  }

  int value = pulseIn(CH6,HIGH,25000);

  if(value>1710)
  {
      extendArm();
  }

  else if(value<1320)
  {
      retractArm();
  }

  else
  {
      stopArm();
  }
}

void extendArm()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,200);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,200);
}

void retractArm()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,200);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENB,200);
}

void stopArm()
{
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}

void stopAll()
{
  stopArm();
}