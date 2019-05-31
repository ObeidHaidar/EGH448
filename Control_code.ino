/* 
This code is the property of Haidar Obeid. 
*/


#include <PID_v1.h>

int motor_pin = 13; // pin D7 in NodeMCU
int frequency_input_pin = 12; // pin D6 in NodeMCU

double desired_motor_speed = 400; //Hz multiply by 30 to get speed in rpm 
double motor_speed = 0; // it's a pwm signal that ranges between 0 and 1023 on NodeMCU
double frequency_input = 0;

unsigned long pulse_duration;

int Kp = 3; //Proportional Controller Constant
int Ki = 4; //Integral Controller Constant
int Kd = 0; //Derivative Controller Constant


PID myPID(&frequency_input, &motor_speed, &desired_motor_speed, Kp, Ki, Kd, DIRECT);

void setup()
{

  Serial.begin(9600);
  
  pinMode(motor_pin, OUTPUT);
  pinMode(frequency_input_pin, INPUT);
  
  // Set output limit.
  myPID.SetOutputLimits(0,1023);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{

  pulse_duration = pulseIn(frequency_input_pin, HIGH);
    
  if(pulse_duration>1000){

      
  frequency_input = 1000000/(2*pulse_duration);
  myPID.Compute();
  analogWrite(motor_pin,motor_speed);

  Serial.println(frequency_input);
      }
}
