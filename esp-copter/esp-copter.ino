#define BLYNK_PRINT Serial


#include <Servo.h>
//#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



#define GPIO12  12
#define GPIO3   3

#define MOTOR1_PIN  GPIO12
#define MOTOR2_PIN  GPIO3

#define MIN_SIGNAL  1000
#define MAX_SIGNAL  2000

#define MAX_THROTTLE    180
#define MIN_THROTTLE    0

#define THROTTLE_DELAY  100     // Increase thottle with 100 ms delay in steps
 
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

    // Check for throtle bounds
    if(throttle_a > MAX_THROTTLE)
        throttle_a = MAX_THROTTLE;
    if(throttle_a < MIN_THROTTLE)
        throttle_a = MIN_THROTTLE;
             
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

void l0_initialiseMotors(void)
{
    escMotor1.attach(GPIO12, MIN_SIGNAL, MAX_SIGNAL);
    escMotor2.attach(GPIO3, MIN_SIGNAL, MAX_SIGNAL);

    // Setting minimum throttle
    Serial.println("Initialising Motors, setting minimum throttle...");
    escMotor1.writeMicroseconds(MIN_SIGNAL);
    escMotor2.writeMicroseconds(MIN_SIGNAL);
    delay(1000); 
}

void l1_initialiaseCopter(void)
{
    l0_initialiseMotors();
}

void l1_flyUp(int throttle_a)
{
    int currentThrottleMotor1_ = l0_readThrottle(escMotor1);
    int currentThrottleMotor2_ = l0_readThrottle(escMotor1);

    while(currentThrottleMotor1_ != throttle_a)
    {
        l0_setThrottle(escMotor1, currentThrottleMotor1_++);
        l0_setThrottle(escMotor2, currentThrottleMotor2_++);
    }
}



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Z";
char pass[] = "########";
char auth[] = "63602e17cb7c46f38cbd64e3e751e322";

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    l1_initialiaseCopter();  

//    Blynk.begin(auth,ssid, pass);
    Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
}

void loop() {
  // put your main code here, to run repeatedly:
    
    Blynk.run();
}


