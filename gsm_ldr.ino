/*
A laser pointer is needed to make a light beam that will be detected by the ldr
Make Sure you line up the beam and the ldr properly
*/
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
const int sensivity = 400;  // 0-1023 a lower value means a more powerful laser
int count=1;
int time1=0;
#define ldr A0
/*#define redLed 7
#define blueLed 8
#define buzzer 9
#define buttonPin A2
*/

//int buttonState;
int state = 0;


void setup() {

Serial.begin(9600);
 mySerial.begin(9600);   // Setting the baud rate of GSM Module  
 // Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

//pinMode(redLed, OUTPUT);
//pinMode(blueLed, OUTPUT);
//pinMode(buzzer, OUTPUT);
}

void loop() {
  
int light = analogRead(ldr);
//int button = analogRead(buttonPin);
//Serial.print("button = ");
//Serial.print(button);
//Serial.print("\n");  
Serial.print("light = ");
Serial.print(light);
Serial.print("\n");  
Serial.print("state = ");
Serial.print(state);
Serial.print("\n"); 
Serial.print("\n");  
//  if (button >= 1020) {
    state = 0;
  //}
  if (light >sensivity) {
    state = 1;
  }
  if ((light <= sensivity) && (state == 0)) {
  SendMessage();

  }
  if (state == 1) {

SendMessage1();
time1=1;
}
}


void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\""); // Replace x with mobile number
  delay(1000);
  mySerial.println("opened");// The SMS text you want to send
  delay(100);
 mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void SendMessage1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\""); // Replace x with mobile number
  delay(1000);
  mySerial.println("closed");// The SMS text you want to send
  delay(100);
 mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
