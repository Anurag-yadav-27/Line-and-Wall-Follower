int IR_1=A5;
int IR_2=A4;
int IR_3=A3;
int LM_F=8;
int LM_R=9;
int RM_F=3;
int RM_R=4;
int EN_R=5;
int EN_L=6;
int c=0;
int d=0;
const int trig_pin1=7;
const int echo_pin1=2;
const int trig_pin0=10;
const int echo_pin0=11;
float dist0;
float dist1;
void setup() {
  // put your setup code here, to run once:
      pinMode(IR_1,INPUT);
      pinMode(IR_2,INPUT);
      pinMode(IR_3,INPUT);
      pinMode(LM_F,OUTPUT);
      pinMode(LM_R,OUTPUT);
      pinMode(RM_F,OUTPUT);
      pinMode(RM_R,OUTPUT);
      pinMode(EN_R,OUTPUT);
      pinMode(EN_L,OUTPUT);
      pinMode(trig_pin0,OUTPUT);
      pinMode(echo_pin0,INPUT);
      pinMode(trig_pin1,OUTPUT);
      pinMode(echo_pin1,INPUT);

      Serial.begin(9600);
      
}
void stope()
 {
  digitalWrite(LM_F,LOW);
  digitalWrite(LM_R,LOW);
  digitalWrite(RM_F,LOW);
  digitalWrite(RM_R,LOW);
  Serial.println("stop");
 }
void forward()
{
  digitalWrite(LM_F,HIGH);
  digitalWrite(RM_F,HIGH);
  digitalWrite(LM_R,LOW);
  digitalWrite(RM_R,LOW);
  Serial.println("forward");
}
void left()
{
  digitalWrite(LM_F,LOW);
  digitalWrite(LM_R,HIGH);
  digitalWrite(RM_F,HIGH);
  digitalWrite(RM_R,LOW);
  Serial.println("left");
}
void right()
{
   digitalWrite(LM_F,HIGH);
  digitalWrite(LM_R,LOW);
  digitalWrite(RM_F,LOW);
  digitalWrite(RM_R,HIGH);
  Serial.println("right");
}
float front_uv(){
  digitalWrite(trig_pin0,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin0,HIGH);
  delayMicroseconds(8);
  digitalWrite(trig_pin0,LOW);

  float duration0,distance0;
  duration0=pulseIn(echo_pin0,HIGH);
  distance0=(duration0*0.0343)/2;
  Serial.print("distance0: ");
  Serial.println(distance0);
  delay(50);
  return distance0;
}
float first_uv(){
  digitalWrite(trig_pin1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin1,HIGH);
  delayMicroseconds(8);
  digitalWrite(trig_pin1,LOW);

  float duration1,distance1;
  duration1=pulseIn(echo_pin1,HIGH);
  distance1=(duration1*0.0343)/2;
  Serial.print("distance1: ");
  Serial.println(distance1);
  delay(50);
  return distance1;
}
void wall()
{
  c=c+1;
  if(d==0)
         { 
            while(dist0 > 12)
              {
                Serial.print("case1");
                Serial.println();
                forward();
                dist0=front_uv();
              }

               stope();
               delay(500);
               Serial.print("case2");
               Serial.println();
            while(dist0 < 30)
            {
            dist0=front_uv();
            left();
            }
            delay(500);
            stope();
            delay(1000);
            d=1;
          }
        else if(d==1) 
          {
            Serial.print("c==1");
            Serial.print(dist0);
            Serial.println("  ");
            Serial.print(dist1);
            Serial.println("  ");
            if((dist1 < 10)&&(dist1 > 7))
           {
             forward();
             Serial.print("case3");
             Serial.println();
            }
            else if(dist1 < 7)
            {
              left();
              Serial.print("case4");
              Serial.println();
            }
            else if(dist1 > 10)
            {
               right();
                Serial.print("case5");
                Serial.println();
            }
        }
}
void loop(){
    dist0 = front_uv();
    dist1 = first_uv();
    if((dist0 > 20)&&(c==0))
    {
      //FORWAARD ONLY
     while((digitalRead(IR_1)==0)&&(digitalRead(IR_2)==1)&&(digitalRead(IR_3)==0))
     forward();
     // right caliberation
     if((digitalRead(IR_1)==0)&&(digitalRead(IR_2)==0)&&(digitalRead(IR_3)==1))
     {
      right();
     }
     //left caliberation
     else if((digitalRead(IR_1)==1)&&(digitalRead(IR_2)==0)&&(digitalRead(IR_3)==0))
     {
      left();
     }
     // right turn only
     if((digitalRead(IR_1)==0)&&(digitalRead(IR_2)==1)&&(digitalRead(IR_3)==1))
     {
      right();
      delay(100);
     }
     //left turn only
     else if((digitalRead(IR_1)==1)&&(digitalRead(IR_2)==1)&&(digitalRead(IR_3)==0))
     {
      left();
      delay(100);
     }
     // t point or plus point
     else if((digitalRead(IR_1)==1)&&(digitalRead(IR_2)==1)&&(digitalRead(IR_3)==1))
     {
      right();
      delay(100);
     }
     //path end
     else
     {
      right();
      delay(20);
     }
    }
    else if(c==1)
    {
      wall();
    }
    else
    stope();
}
