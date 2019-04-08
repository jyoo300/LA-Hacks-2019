#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D4
#define ECHOPIN    D3

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f421fc3df21746a5aa9d2dfe9e6b70a5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SMARTCOLLECTOR";
char pass[] = "smartcollector2019";

WidgetLCD lcd(V1);

void setup()
{
  // Debug console
  Serial.begin(9600);
pinMode(TRIGGERPIN, OUTPUT);
pinMode(ECHOPIN, INPUT);
Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
}

void loop()
{
  lcd.clear();
  long capacity = 80;
  long duration, distance, freeSpace;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;

  
  freeSpace = (distance*100/capacity); 

  if(distance <= 5){
    lcd.print(0, 0, "Trash can full");

  }
  else {
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" Cm");
  lcd.print(7, 1, distance);
  Serial.print("Free space: ");
  Serial.println(freeSpace);

//HTTP Post request http.begin
  }
  delay(2500);

Blynk.run();

}
