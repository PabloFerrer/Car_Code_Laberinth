/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Smart Car Tutorial Lesson 1
 * Tutorial URL http://osoyoo.com/2017/04/23/arduinosmartcarlesson1/
 * CopyRight www.osoyoo.com

 * After running the code, smart car will go forward 5 seconds, then go backward 5
 * seconds, then left turn for 5 seconds then right turn for 5 seconds then stop. 
 * 
 */
 
#include "configuration.h"
#include <Ultrasonic.h>

Ultrasonic sensorDelantero(10,9,30000); //(Trig PIN,Echo PIN, microsegundos max "distancia máxima")
Ultrasonic sensorDerecho(12,13,30000);
Ultrasonic sensorIzquierdo(11,3,30000);

//Distancias que miden los ultrasonidos
int disR = 0;
int disD = 0;
int disI =0;
int v1= 80;
int v2= 80;




/*motor control*/
void go_Advance(void)  //Forward  //3HIGH 1LOW Giran hacia adelante las de la izquierda 
                                  //HIGH LOW HIGH LOW marcha alante  
{                                 //LOW HIGH LOW HIGH marcha atras   
                                  //LOW 2HIGH LOW Giro sobre su propio eje (2segundos 180º/1segundo 90º)
                                  //
  digitalWrite(dir1PinL,HIGH);     
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);      
}
void go_Left(void)  //Turn left
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void go_Right(void)  //Turn right
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Back(void)  //Reverse
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

//Pins initialize
void init_GPIO()
{
	pinMode(dir1PinL, OUTPUT); 
	pinMode(dir2PinL, OUTPUT); 
	pinMode(speedPinL, OUTPUT);  
 
	pinMode(dir1PinR, OUTPUT);
  pinMode(dir2PinR, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
	stop_Stop();
}

void advance(int disR){
  if(disR > distA){
    go_Advance();
    Serial.println("Puedo ir hacia adelante");
    
  }else{
    stop_Stop();
  }
}

void canTurn(int disD,int disI){

  if(disD > distD){
    delay(500);
    //stop_Stop();
    Serial.println("Me paro");
    //go_Right();
    Serial.println("Giro derecha");
    delay(1100);
    //stop_Stop();
    Serial.println("Me paro");
    delay(500);
    //go_Advance();
    Serial.println("Avanzo un poco");
    delay(1000);
  
  }else if(disI > distI){
    delay(500);
    //stop_Stop();
    Serial.println("Me paro");
    //go_Left();
    Serial.println("Giro izquierda");
    delay(1100);
    //stop_Stop();
    Serial.println("Me paro");
    delay(500);
    //go_Advance();
    Serial.println("Avanzo un poco");
    delay(1000);
  }
  
}
 
void setup()
{
	init_GPIO();
  Serial.begin(9600);
  set_Motorspeed(v1,v2);
}



void loop()
{
  disR = sensorDelantero.Ranging(CM);
  disD = sensorDerecho.Ranging(CM);
  disI = sensorIzquierdo.Ranging(CM);
  Serial.println(disI);
  
  advance(disR);
  canTurn(disD,disI);

  
  
}

