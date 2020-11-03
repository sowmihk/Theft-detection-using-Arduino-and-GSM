/*
A laser pointer is needed to make a light beam that will be detected by the ldr
Make Sure you line up the beam and the ldr properly
*/
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
const int sensivity = 400;  // 0-1023 a lower value means a more powerful laser
//int count=0;
//int time1=1;
#define ldr A0
/*#define redLed 7
#define blueLed 8
#define buzzer 9
#define buttonPin A2
*/

//int buttonState;
int state = 0;


void setup() {

//Serial.begin(9600);
 mySerial.begin(9600);   // Setting the baud rate of GSM Module  
 Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
//  socket();


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
//  SendMessage();
socket();
  //count=0;

  }
  if (state == 1) {
socket();
//SendMessage1();
//count=0;
}


}


void SendMessage()
{
  //if(count<time1){
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\""); // Replace x with mobile number
  delay(1000);
  mySerial.println("opened");// The SMS text you want to send
  delay(100);
 mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
//count++;
//}

}
void SendMessage1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds orj 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\""); // Replace x with mobile number
  delay(1000);
  mySerial.println("closed");// The SMS text you want to send
  delay(100);
 mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void socket()
{
 mySerial.begin(9600);  
 Serial.begin(9600);  
 delay(500);

mySerial.println("AT+CIPSHUT");
 delay(1000);
 printSerialData();

 mySerial.println("AT+CIPMUX=1");
 delay(2000);
 printSerialData();
 
 mySerial.println("AT+CGATT=1");
 delay(1000);
 printSerialData();
 
 
 mySerial.println("AT+CSTT=\"airtelgprs\",\"\",\"\"");//setting the APN,2nd parameter empty works for all networks
 delay(5000);
 printSerialData();
 
 mySerial.println();
 mySerial.println("AT+CIICR");
 delay(6000);
 printSerialData();
 
 mySerial.println("AT+CIFSR"); //init the HTTP request
 delay(2000);
 printSerialData();
 mySerial.println("AT+CIPSTART=\"TCP\",\"tcp://0.tcp.ngrok.io\",\"18116\"");
 delay(5000);
 printSerialData();
 delay(5000);
 
mySerial.println("AT+CIPSEND");
 delay(2000);
 printSerialData();
 if(state==1)
 {
  sendclose();
 }
 else
{
sendopen();
}
delay(3000);
mySerial.println("AT+CIPCLOSE");
printSerialData();

mySerial.println("AT+CIPSHUT");
delay(1000);
printSerialData();
}
void printSerialData()
{
while(mySerial.available()!=0)
Serial.write(mySerial.read());
}




void sendopen()
{
//temp = analogRead(tempPin);
//temp = temp * 0.48828125;
//Serial.print(“TEMPERATURE = “);
//Serial.print(temp);
//Serial.print(“*C”);
//Serial.print("Hello world");
delay(5000);
mySerial.println("AT+CLTS=1;&W");
mySerial.println("AT+CFUN=1,1");
mySerial.println("AT+CLTS?");
mySerial.println("AT+CCLK?");
mySerial.println("Opened");
mySerial.println((char)26);
delay(3000);
printSerialData();
mySerial.write(0x1A);
delay(3000);
printSerialData();

}


void sendclose()
{

 delay(5000);
mySerial.println("Closed");
mySerial.println((char)26);
delay(3000);
printSerialData();
mySerial.write(0x1A);
delay(3000);
printSerialData();
}
