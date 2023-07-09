#include<SoftwareSerial.h>
#include "CytronMotorDriver.h"

CytronMD motor1(PWM_DIR, 5, 6);
CytronMD motor2(PWM_DIR, 9, 10);

int relayPin1 = 11; //motor relays
int relayPin2 = 12; //motor relays
int x = 0;
int y = 0;
int r1 = 4; //jack relay
int r2 = 7; //jack relay



void setup() {
  Serial1.begin(9600);
  Serial.begin(115200);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
}

void loop() {

  if (Serial1.available() > 0)
  {
    int a = Serial1.read();
    Serial.println(a);
    if (a == 49) {

      Forward();
      Serial.println("Forward");
    }
    else if (a == 50) {
      Backward();
      Serial.println("BAckward");

    }
    else if (a == 48) {
      Brake();
      Serial.println("Brake");

    }
    else if (a == 51) {
      Left();
      Serial.println("Left");

    }
    else if (a == 52) {
      Right();
      Serial.println("Right");

    }
    if (a == 54) {
      jackUp();
      Serial.println("Hoisting jack");
    }
    else if (a == 55) {
      jackDown();
      Serial.println("Lowering jack");
    }
    else if (a == 56) {
      jackStop();
      Serial.println("Freezing jack");
    }

    if (a==53){
      Demo();
    }
  }

}

void Forward() {
  int i = x;
  int j = y;
  for (; i <= 129 ; i += 1) {
    x = i;
    motor1.setSpeed(-i);
    motor2.setSpeed(-i);
    delay(25);
  }
  motor1.setSpeed(-129);
  motor2.setSpeed(-129);
  Serial.println("Forward");

  x = -129;
  y = -129;
}


void Backward() {
  int i = x;
  int j = y;
  for (; i <= 129; i += 1) {
    x = i;
    motor1.setSpeed(i);
    motor2.setSpeed(i);
    delay(25);
  }
  motor1.setSpeed(129);
  motor2.setSpeed(129);
  Serial.println("Backward");

  x = 129;
  y = 129;
}

void Brake() {

  int i = x;
  int j = y;
  if (i > 0 && j > 0) {
    for (; i >= 0; i = i - 1) {
      motor1.setSpeed(i);
      motor2.setSpeed(i);
      delay(25);
    }
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    x = 0;
    y = 0;
  }
  else if (i < 0 && j < 0) {
    for (; i <= 0; i = i + 1) {
      motor1.setSpeed(i);
      motor2.setSpeed(i);
      delay(25);
    }
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    x = 0;
    y = 0;
  }
  else if (i < 0 && j > 0) {
    for (; i <= 0; i = i + 1) {
      motor1.setSpeed(i);
      motor2.setSpeed(j--);
      delay(25);
    }
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    x = 0;
    y = 0;
  }
  else if (i > 0 && j < 0) {
    for (; i >= 0; i = i - 1) {
      motor1.setSpeed(i);
      motor2.setSpeed(j++);
      delay(25);
    }
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    x = 0;
    y = 0;
  }

}

void Left() {
  int i = x;
  int j = y;
  for (i = 0; i <= 66; i += 1) {
    motor1.setSpeed(i);
    motor2.setSpeed(-i);
    delay(25);
  }
  motor1.setSpeed(66);
  motor2.setSpeed(-66);
  x = 66;
  y = -66;

}

void Right() {
  int i = x;
  int j = y;
  for (; i <= 66; i += 1) {
    motor1.setSpeed(-i);
    motor2.setSpeed(i);
    delay(25);
  }
  motor1.setSpeed(-66);
  motor2.setSpeed(66);
  x = -66;
  y = 66;

}

void jackUp() {
  digitalWrite (r1, HIGH); //r1 4, r2 7
  digitalWrite(r2, LOW);
}

void jackDown() {
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
}

void jackStop() {
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
}

void Demo() {
  Serial.print("demo");
  Forward();
  delay(5000);
  Brake();
  
  Backward();
  delay(5000);
  Brake();
  
  Right();
  delay(5000);
  Brake();

  Left();
  delay(5000);
  Brake();

  jackUp();
  delay(5000);

  jackDown();
  delay(5000);

  jackStop();
  
}
