#define mA1 12   // Defining pins for  A motor
#define mA2 11
#define mB1 10   // Defining pins for B motor
#define mB2 9
#define trigPin 8 // Defining pins for Ulstrasonic Sensor    
#define echoPin 7 
#define IR1 6  // Defining pins for IR sensor
#define IR2 5

int dist; // Distance measured usig Ultrasonic sensor
long duration; // Pulse duration from Ultrasonic sensor
bool IRs1,IRs2; // IR sensor state

void setup()
{// Setup codes
  pinMode(IR1, INPUT);
  pinMode(IR2,INPUT);
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin (9600); // inatialize the serial connection for 9600 baud rate
} 

void sensor_check()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  dist = (duration/2)/29.1;
  
  // Read IR state
  IRs1=digitalRead(IR1);
  IRs2=digitalRead(IR2); 
}

void print_data()
{ // Print the sensor data to serival monitor
  Serial.print(dist);
  Serial.print(" cm IR state: ");
  Serial.print(IRs1);
  Serial.print(",");
  Serial.println(IRs2);
  delay(200);
}

void forward()
{// Make the bot go forward
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void backward()
{// Make the bot go backward
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void left()
{// Make the bot go left
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void right()
{// Make the bot go right
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void wait()
{// Make the bot stop
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}

void loop()
{
  sensor_check(); // Get the sensors data
  print_data(); // Print the sensors data to serial monitor

  if(IRs1||IRs2)
  { // move back and turn right if one of the two or both IR are high 
    // when the bot is in contact with surface the sensors data is low 
    backward();
    delay(1000);
    right();
    delay(1000);
  }
  else
  {
    if(dist<=7)
    {// move back if there is obstacle in 7 cm range
      backward();
    }
    else if(dist>=10 && dist<=12)
    {// turn right if the obstacle is between 10 to 12 cm range
      right();
    }
    else
    {// If there is no obstacle move forward
      forward();
    }
  } 
}