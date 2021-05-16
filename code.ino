// including libraries
#include <Servo.h>

//declaring variables

Servo servoMotor;

int dist = 0;	
int pir;
int ldr;
int temp;
int gas;

// ultrasonic sensor function
long getDist(int pin)
{
  pinMode(pin, OUTPUT);  // Clear the trigger
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(pin, HIGH);
}


void setup()
{
  // servo motor
  servoMotor.attach(7);
  
  // PIR sensor
  pinMode(8, INPUT);
  
  
  pinMode(13, OUTPUT); //DC motor
  pinMode(A4, INPUT);	//temperature sensor
  
  pinMode(A5, INPUT);	//Photoresisitor
  pinMode(5, OUTPUT);	//Light Bulb
  
  pinMode(A0, INPUT);	//Gas sensor
  pinMode(9, OUTPUT);	//Buzzer
  
  Serial.begin(9600);
  
}

void loop()
{
  
  //For Door
  
  dist = 0.01723 * getDist(6);  // used get distance function and multiplied
  
  if(dist <100)
  {
    servoMotor.write(90);
    Serial.print(" 	  || Door Open!  and  Distance = ");
    Serial.print(dist);
    Serial.print("\n");
  }
  else
  {
    servoMotor.write(0);
    Serial.print(" 	  || Door Closed!  and  Distance = ");
    Serial.print(dist);
    Serial.print("\n");
  }
  
   //Gas Sensor
  
  gas = analogRead(A0); 	// takes input and store in gas variable
  
  if (gas < 200 )
  	{
    digitalWrite (9, LOW);	 // 9 is output to buzzer
  	}
  else 
  {
    digitalWrite(9, HIGH);
  }
  
  
  // For DC motor and light bulb
  
  pir=digitalRead(8);		
  ldr=analogRead(A5);		
  
  temp=analogRead(A4);
  temp=(temp*5)/1.024;	//temperature conversion formula
  temp=temp/10;
  
  
 if (pir<1)
  {
    digitalWrite(5,LOW);		// no motion detected
    digitalWrite(13,LOW);
    
  }
  else
  {
    if ((ldr<550) && (temp>32))
    {
      {digitalWrite(5,HIGH);		// temp high & ldr low
       digitalWrite(13,HIGH);}
      delay(1000);
      
    }
    
    else
    {
     	 if ((ldr>550) && (temp>32))
    	{
           {digitalWrite(5,LOW);		//temp high & ldr high
            digitalWrite(13,HIGH);}
           delay(1000);
           
    	}
    	
      	else
    	{
      		if ((ldr<550) && (temp<32))
    		{
               {digitalWrite(5,HIGH);		//temp low & ldr low
                digitalWrite(13,LOW);}
                delay(4000);  
    		}
    				
        		else
        		{
                  {digitalWrite(5,LOW);		//temp low & ldr high
                   digitalWrite(13,LOW);}
                   delay(1000);
        		}
         }
      }
   
 } 
  
  
  
  
  
  Serial.print("Temperature:  ");
  Serial.println(temp);
  Serial.print("Human detected (1:yes, 0:no):  ");
  Serial.println(pir);
  Serial.print("milivolt through LDR:  ");
  Serial.println(ldr);
  Serial.println("Gas value:  ");
  Serial.println(gas);
  Serial.println("\n");
  
  delay(5000);
  
} 
    
