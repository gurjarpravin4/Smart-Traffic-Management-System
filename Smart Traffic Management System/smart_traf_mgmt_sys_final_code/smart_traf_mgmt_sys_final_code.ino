//  Variable Declarations-
const float r2 = A1, g2 = A0;                                         //  LEDs
const int r1 = 5, g1 = 4;
const int echo1 = 3, trig1 = 2;                                       //  Sensors
const int echo2 = 7, trig2 = 6;                 
const float echo3 = A3, trig3 = A2;
const float echo4 = A5, trig4 = A4;
bool s1, s2, s3, s4;
bool readSensors(int echo, int trig);
void timer(int t);

void setup() {
  Serial.begin(115200);
  pinMode(echo1, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo4, INPUT);
  pinMode(trig4, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g2, OUTPUT);  
  Serial.println("Welcome to Smart Traffic Management System!");
  analogWrite(r1, 255);
  analogWrite(g2, 255);
  analogWrite(r2, 255);
  analogWrite(g1, 255);
  delay(3000);
  analogWrite(r1, 0);
  analogWrite(g2, 0);
  analogWrite(r2, 0);
  analogWrite(g1, 0);
}

void loop() {
//  For Lane 1-
  Serial.println("S3 and S4:");
  s3 = readSensors(echo3, trig3);   //  Read traffic for sig 2
  s4 = readSensors(echo4, trig4);
  analogWrite(r1, 255);             //  Toggle the signals
  analogWrite(g2, 255);  
  if(s3 == false && s4 == false){
//    min traffic condition (g2 for 10)
    Serial.println("MIN TRAFFIC");
    timer(10);
  }

  else if(s3 == true && s4 == true){
//    max traffic condition (g2 for 20)
    Serial.println("MAX TRAFFIC");
    timer(20);
  }

  else{
//    med traffic condition (g2 for 15)
    Serial.println("MED TRAFFIC");
    timer(15);
  }
  analogWrite(r1, 0);             //  Toggle the signals
  analogWrite(g2, 0);

//  For Lane 2-
  Serial.println("S1 and S2:  ");
  s1 = readSensors(echo1, trig1);   //  Read traffic for sig 2
  s2 = readSensors(echo2, trig2);
  analogWrite(r2, 255);             //  Toggle the signals
  analogWrite(g1, 255);
  if(s1 == false && s2 == false){
//    min traffic condition (g1 for 10)
    Serial.println("MIN TRAFFIC");
    timer(10);
  }

  else if(s1 == true && s2 == true){
//    max traffic condition (g1 for 20)
    Serial.println("MAX TRAFFIC");
    timer(20);
  }

  else{
//    med traffic condition (g1 for 15)
    Serial.println("MED TRAFFIC");
    timer(15);
  }
  analogWrite(r2, 0);             //  Toggle the signals
  analogWrite(g1, 0);
}


bool readSensors(int echo, int trig){
  double t, d;
  bool temp_sen;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  t = pulseIn(echo, HIGH);
  d = 0.034 * t / 2;  // in cm
  d = d / 100;  // in meters
  Serial.print("Distance = ");
  Serial.print(d);
  Serial.print("m");
  Serial.println();
  if (d >= 0.5)                 //  If distance measured is greater than width of the road, no traffic is present
    temp_sen = false;
  else                         //  If distance measured is less than width of the road, traffic is present
    temp_sen = true;
  return temp_sen;
}

void timer(int t){
  while(t >= 0){
    Serial.println(t);
    delay(1000);
    t--;
  }
}
