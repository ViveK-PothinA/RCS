#include <Ultrasonic.h>
#define m1 12
#define m2 5
#define pwmval 64
Ultrasonic u(10,11);          //(Trig PIN,Echo PIN)
Ultrasonic l(3,4);
Ultrasonic r(2,7);
//Ultrasonic b(3,4);

int *ar; int top=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1,OUTPUT); pinMode(m1+1,OUTPUT);
  pinMode(m2,OUTPUT); pinMode(m2+1,OUTPUT); 
  analogWrite(A0,255);analogWrite(A1,0);analogWrite(A2,255);analogWrite(A3,0);analogWrite(A4,255);analogWrite(A5,0);
  ar = (int*) malloc(10*sizeof(int));
}
int str(){
  digitalWrite(m1,HIGH);  digitalWrite(m1+1,LOW);
  digitalWrite(m2,HIGH);  digitalWrite(m2+1,LOW);
  delay(20);
  *(ar + top) = 0;                                   //Forward is 0
  return 3;
}
int right(){
  analogWrite(m1,pwmval);  digitalWrite(m1+1,LOW);
  analogWrite(m2,pwmval);  digitalWrite(m2+1,LOW);
  delay(20);
  return 1;                                      
}
int sright(){
  digitalWrite(m1,HIGH);  digitalWrite(m1+1,LOW);
  digitalWrite(m2,LOW);  digitalWrite(m2+1,LOW);
  delay(20);
  *(ar + top) = 1;
  return -1;                                          //Sharp Right = 1
}
int left(){
  analogWrite(m1,LOW);  analogWrite(m1+1,pwmval);
  digitalWrite(m2,LOW); analogWrite(m2+1,pwmval);
  delay(20);
  return 2;
}
int sleft(){
  digitalWrite(m1,LOW);  digitalWrite(m1+1,LOW);
  digitalWrite(m2,HIGH); digitalWrite(m2+1,LOW);
  delay(20);
  *(ar + top) = 2;
  return -2;                                          //Sharp Left = 2
}
int check(int a, int b){
  if(a==b) return 1;
  else if(a>b) return 2;
  else return 3;
}
int ur,lr,rr;//,br;
void loop(){
  // put your main code here, to run repeatedly
  ur = u.Ranging(CM);
  lr = l.Ranging(CM);
  rr = r.Ranging(CM);delay(100);
  //br = b.Ranging(CM);delay(100);
  ar = realloc(ar,1); top++;        //allocating and increasing index
  Serial.print("\nL:"); Serial.print(lr); Serial.print(" cm" );
  Serial.print("\tR:"); Serial.print(rr); Serial.print(" cm" );
  Serial.print("\tU:"); Serial.print(ur); Serial.print(" cm" );
  //Serial.print("\tB:"); Serial.print(br); Serial.print(" cm" );
  if(ur>8){                            //All forward cases
    if(lr>20){                          //All forward left turn cases
      if(rr>20){                        //T-Junction case
      sleft();                          //Priority of taking left
      *(ar+top) = *(ar+top) + 4;      //To make a node of identifying junction cases
      }
      else sleft();                  //Sharp left case
    }
    else if(rr>20) sright();                   //sharp right case
    else{
      if(rr==0&&1==check(rr,lr)){         //Final case
        digitalWrite(m1,LOW);  digitalWrite(m1+1,LOW);
        digitalWrite(m2,LOW);  digitalWrite(m2+1,LOW);
      }      
      else{
        Serial.print("\tC:"); Serial.print(check(rr,lr));
        switch(check(rr,lr)){
          case 1: str(); break;
          case 2: left; break;
          case 3: right(); break;
        }
      }
    }
  }  
  else{                                  //Backward cases
    int prev;                            // temp value to store the previous direction
    while(*(ar+top)<4){                 //Looping till the junction is found
      while(lr!=0||rr!=0){                                 //To move backwards till back is found
        digitalWrite(m1,LOW);  digitalWrite(m1+1,HIGH);
        digitalWrite(m2,LOW);  digitalWrite(m2+1,LOW);
        delay(20);
        int *temp;temp=ar+top;free(temp);top--;            //clearing the forward values
      }
      if(lr>20){                       //Backwards left = rev left
         digitalWrite(m1,LOW);  digitalWrite(m1+1,LOW);
         digitalWrite(m2,LOW);  digitalWrite(m2+1,HIGH);
         int *temp;temp=ar+top;prev=*(temp);free(temp);top--;            //clearing the left value
      }
      else{                            //Backwards right = rev right
         digitalWrite(m1,LOW);  digitalWrite(m1+1,HIGH);
         digitalWrite(m2,LOW);  digitalWrite(m2+1,LOW);
           int *temp;temp=ar+top;prev=*(temp);free (temp);top--;            //clearing the right value
      }
    }
    ar = realloc(ar,1); top++;
    if(prev==2) sleft();                                              //Have to right if turning left was wrong
    else sright();
    }
    
  }
