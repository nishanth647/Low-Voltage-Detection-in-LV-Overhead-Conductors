#include <SPI.h>
#include <LoRa.h>
#define VR_PIN 34
#define VY_PIN 35
#define VB_PIN 32


#define CURRENT_PIN 33

#define BATTERY_PIN 36


#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26


String poleID = "LV_POLE_23";

float LOW_VOLTAGE = 180;
float PHASE_IMBALANCE_LIMIT = 40;
float BREAK_CURRENT_THRESHOLD = 0.1;



float readVoltage(int pin)
{
  long sum = 0;

  for(int i = 0; i < 200; i++)
  {
    sum += analogRead(pin);
  }

  float avg = sum / 200.0;

  float voltage = (avg / 4095.0) * 3.3;

  voltage = voltage * 100;

  return voltage;
}


float readCurrent()
{
  long sum = 0;

  for(int i = 0; i < 200; i++)
  {
    sum += analogRead(CURRENT_PIN);
  }

  float avg = sum / 200.0;

  float voltage = (avg / 4095.0) * 3.3;

  float current = (voltage - 2.5) / 0.185;

  return abs(current);
}


float readBattery()
{
  int value = analogRead(BATTERY_PIN);

  float voltage = (value / 4095.0) * 3.3;

  voltage = voltage * 2;

  return voltage;
}


void sendLoRa(String msg)
{
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();
}


void setup()
{
  Serial.begin(115200);

  SPI.begin(18, 19, 23, 5);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if(!LoRa.begin(433E6))
  {
    Serial.println("LoRa initialization failed");
    while(1);
  }

  Serial.println("System Started");
}


void loop()
{
  float VR = readVoltage(VR_PIN);
  float VY = readVoltage(VY_PIN);
  float VB = readVoltage(VB_PIN);

  float current = readCurrent();
  float battery = readBattery();

  Serial.println("------------ SYSTEM DATA ------------");

  Serial.print("R Phase Voltage: ");
  Serial.println(VR);

  Serial.print("Y Phase Voltage: ");
  Serial.println(VY);

  Serial.print("B Phase Voltage: ");
  Serial.println(VB);

  Serial.print("Line Current: ");
  Serial.println(current);

  Serial.print("Battery Voltage: ");
  Serial.println(battery);


  String fault = "NORMAL";


  if(VR < 50 && VY < 50 && VB < 50)
  {
    fault = "POWER_OUTAGE";
  }


  else if((VR > 200 || VY > 200 || VB > 200) && current < BREAK_CURRENT_THRESHOLD)
  {
    fault = "CONDUCTOR_BREAK";
  }


  else if(VR < LOW_VOLTAGE || VY < LOW_VOLTAGE || VB < LOW_VOLTAGE)
  {
    fault = "LOW_VOLTAGE";
  }


  float avg = (VR + VY + VB) / 3;

  if(abs(VR - avg) > PHASE_IMBALANCE_LIMIT ||
     abs(VY - avg) > PHASE_IMBALANCE_LIMIT ||
     abs(VB - avg) > PHASE_IMBALANCE_LIMIT)
  {
    fault = "PHASE_IMBALANCE";
  }


  if(fault != "NORMAL")
  {
    String alert = "";

    alert += "ALERT|";
    alert += poleID;
    alert += "|";
    alert += fault;

    alert += "|VR:";
    alert += VR;

    alert += "|VY:";
    alert += VY;

    alert += "|VB:";
    alert += VB;

    alert += "|I:";
    alert += current;

    alert += "|BAT:";
    alert += battery;


    Serial.println("FAULT DETECTED");
    Serial.println(alert);

    sendLoRa(alert);
  }

  else
  {
    String status = "";

    status += "STATUS|";
    status += poleID;

    status += "|VR:";
    status += VR;

    status += "|VY:";
    status += VY;

    status += "|VB:";
    status += VB;

    status += "|I:";
    status += current;

    status += "|BAT:";
    status += battery;

    Serial.println("System Normal");

    sendLoRa(status);
  }


  delay(10000);
}
