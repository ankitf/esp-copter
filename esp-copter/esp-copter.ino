#include <Servo.h>


#define GPIO12  12
#define GPIO3   3


#define MIN_SIGNAL  1000
#define MAX_SIGNAL  2000

#define THROTTLE_DELAY  100


#define MOTOR1_PIN  GPIO12
#define MOTOR2_PIN  GPIO3

Servo escMotor1;
Servo escMotor2;


int l0_readThrottle(Servo escMotor_a)
{
    int throttle_ = escMotor_a.read();

    return throttle_;
}

void l0_setThrottle(Servo escMotor_a, int throttle_a)
{
    // read the current throttle 
    
    int currentThrottle_ = l0_readThrottle(escMotor_a);

    // Check if we are goin up or down
    int step_ = 1;
    if(throttle_a < currentThrottle_)
      step_ = -1;

    while(currentThrottle_ != throttle_a)
    {
      escMotor_a.write(currentThrottle_ + step_);
      currentThrottle_ =  l0_readThrottle(escMotor_a); 
      delay(THROTTLE_DELAY);   
    }
}

void l0_initialiseMotors()
{
    escMotor1.attach(GPIO12, MIN_SIGNAL, MAX_SIGNAL);
    escMotor2.attach(GPIO3, MIN_SIGNAL, MAX_SIGNAL);

    // Setting minimum throttle
    Serial.println("Initialising Motors, setting minimum throttle...");
    escMotor1.writeMicroseconds(MIN_SIGNAL);
    escMotor2.writeMicroseconds(MIN_SIGNAL);
    delay(1000); 
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  l0_initialiseMotors();  
}

void loop() {
  // put your main code here, to run repeatedly:
    
    l0_setThrottle(escMotor1, 90);
}


