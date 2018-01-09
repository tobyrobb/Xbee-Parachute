// T robb
// for the arduino nano
#include <Servo.h> 

#define servoPin 9
#define speakerPin 4
#define ledHeartbeatPin 5
#define ledActivationPin 6
#define buttonPin 7


Servo myservo;  // create servo object to control a servo 
 
int openPos = 0;    // variable to store the servo position 
int closePos = 180;    // variable to store the servo position 
 
String commandString = ""; //somewhere to put the command received

// these are the valid command strings we should recieve 

String OPEN = "open";

String HEARTBEAT = "+";


void setup() {
  Serial.begin(4800);
  
//Setup the pins

  pinMode(servoPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
  myservo.write(closePos);     // tell servo to go to position in variable 'pos' 

//Lets beep on successful BOOT
 
  tone(speakerPin, 500);
  delay(1000);
  noTone(speakerPin);

//all done
  Serial.println("Parachute release receiver - April 2016");
  Serial.println("");
  Serial.println("            Setup Complete");

}

void loop() {
  
  //send a heartbeat
delay(10);
Serial.println(HEARTBEAT);  //send heartbeat
//Serial.println("Heartbeat sent");
//Serial.print("Waiting for the OPEN command...Last message received was:  ");    
//Serial.println(commandString);      
checkSerial();
delay(300);
}

void checkSerial(void){
   
  String content = "";
  char character;
  
  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
   
    if (content != "") {

  //begin your command choices here
    commandString = content; //copy the serial string into serialString
  
   if (commandString == OPEN) 
        { 
          myservo.write(openPos);              // tell servo to go to position in variable 'pos' 
          Serial.println("Opening Servo");
          tone(speakerPin, 1500, 1000);
          commandString == "";
          delay(500);
        }   
   if (commandString == HEARTBEAT) 
        { 
          //Serial.println("Connected");
          tone(speakerPin, 50);
          analogWrite(ledHeartbeatPin, 255);
          commandString = "";
          delay(100);
        }   
      }
    }
  
}

