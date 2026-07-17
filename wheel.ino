/*

Arduino UNO 1

CH1 -> Steering
CH2 -> Throttle

Motor Driver:
IN1 IN2 -> Left Motors
IN3 IN4 -> Right Motors

ENA -> PWM Left
ENB -> PWM Right
*/

#define CH1 2
#define CH2 3

#define ENA 5
#define IN1 6
#define IN2 7

#define ENB 9
#define IN3 10
#define IN4 11

int throttle;
int steering;

void setup()
{
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  throttle = pulseIn(CH2, HIGH, 25000);
  steering = pulseIn(CH1, HIGH, 25000);

  if(throttle==0 || steering==0) //STop
  {
    stopMotors();
    return;
  }

  int speed = map(throttle,1000,2000,-255,255);
  int turn  = map(steering,1000,2000,-150,150);

  int leftSpeed = speed + turn;
  int rightSpeed = speed - turn;

  leftSpeed = constrain(leftSpeed,-255,255);
  rightSpeed = constrain(rightSpeed,-255,255);

  driveMotor(leftSpeed,rightSpeed);
}

void driveMotor(int left,int right)
{
  // Left 
  if(left>=0)
  {
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,left);
  }
  else
  {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,-left);
  }

  // Right 
  if(right>=0)
  {
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,right);
  }
  else
  {
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(ENB,-right);
  }
}

void stopMotors()
{
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}