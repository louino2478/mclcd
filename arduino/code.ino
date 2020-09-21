//code by louino
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
String incomingByte = "";
String ip = "";
String online = "0";
String players = "0";
String maxplayers = "0";
String tps = "0";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(15);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("demarage systeme...");
  bootsleep();
  Serial.println("ready");
}

void loop() {
  SerialRead();
  if(incomingByte.startsWith("ip:") == true){
    incomingByte.replace("ip: ", "");
    incomingByte.replace("ip:", "");
    ip = incomingByte;
  }
  if(incomingByte.startsWith("online:") == true){
    incomingByte.replace("online: ", "");
    incomingByte.replace("online:", "");
    online = incomingByte;
  }
  if(incomingByte.startsWith("players:") == true){
    incomingByte.replace("players: ", "");
    incomingByte.replace("players:", "");
    players = incomingByte;
  }
  if(incomingByte.startsWith("maxplayers:") == true){
    incomingByte.replace("maxplayers: ", "");
    incomingByte.replace("maxplayers:", "");
    maxplayers = incomingByte;
  }
  if(incomingByte.startsWith("tps:") == true){
    incomingByte.replace("tps: ", "");
    incomingByte.replace("tps:", "");
    tps = incomingByte;
  }
  
  
  lcd.setCursor(0,2);
  if(online == "0"){
    lcd.print("SERVEUR HORS LIGNE");
  } else if(online == "1"){
    lcd.print("SERVEUR EN LIGNE  ");
  }
  
  if(online == "1"){
    lcd.setCursor(0,3);
    lcd.print("J: " + players + "/" + maxplayers + "   ");
    lcd.setCursor(10,3);
    lcd.print("TPS: " + tps);
  } else {
    lcd.setCursor(0,3);
    lcd.print("                    ");
  }
  lcd.setCursor(0,0);
  lcd.print("ip: " + ip + "   ");
  /*
  Serial.println("ip --> " + ip);
  Serial.println("online --> " + online);
  Serial.println("players --> " + players);
  Serial.println("maxplayers --> " + maxplayers);
  Serial.println("tps --> " + tps);
  */
  delay(15);
}

void SerialRead () {
  while(Serial.available() == 0){
    delay(15);
  }
  if (Serial.available() > 0) {
    incomingByte = Serial.readString();
  }
}

void bootsleep () {
  SerialRead();
  if(incomingByte == "ready"){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("systeme pret");
  }else{
    bootsleep();
  }
}
