//Parachute trigger
//T Robb April 2016

#define speakerPin 4
#define ledHeartbeatPin 5
#define ledActivationPin 6
#define buttonPin 7
 

String commandString = ""; //somewhere to put the command received

// these are the valid command strings we should recieve 

String TXHEARTBEAT = "*";

String RXHEARTBEAT = "+";


void setup() {

//Start the serial ports
Serial.begin(4800);

//Setup the pins
 
pinMode(ledHeartbeatPin, OUTPUT);
 
pinMode(ledActivationPin, OUTPUT);
 
pinMode(buttonPin, INPUT_PULLUP);


//Lets flash and beep on successful BOOT
digitalWrite(ledActivationPin, HIGH);
digitalWrite(ledHeartbeatPin, HIGH);

tone(speakerPin, 500);
delay(1000);
noTone(speakerPin);

digitalWrite(ledActivationPin, LOW);
digitalWrite(ledHeartbeatPin, LOW);

//all done
Serial.println("Parachute release transmitter - April 2016");
Serial.println("");
Serial.println("            Setup Complete");
}

void loop() {
delay(1200);
//Turn off the Leds and speaker
delay(10);
digitalWrite(ledActivationPin, LOW);
delay(10);
//digitalWrite(ledHeartbeatPin, LOW);
analogWrite(ledHeartbeatPin, 127);

delay(10);
noTone(speakerPin);

//send a heartbeat
delay(10);
Serial.println(TXHEARTBEAT);  //send heartbeat
//Serial.println("Heartbeat sent");

//Look for a button press
delay(10);
 
if(digitalRead(buttonPin)== LOW){
      digitalWrite(ledActivationPin, HIGH);
      tone(speakerPin, 50);
      for(int i = 0;i<=5;i++){
      Serial.println("open");
      delay(300);
      }
      // Serial.println("Sent open command");  
   }
   
delay(10);
noTone(speakerPin);

//check the RF Serial
delay(10);
checkSerial();


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
  
   if (commandString == RXHEARTBEAT) 
        { 
         //Serial.println("Connected");
          tone(speakerPin, 1000, 100);
          analogWrite(ledHeartbeatPin, 255);
          commandString = "";
          delay(10);
        }   
      }
    }
}

