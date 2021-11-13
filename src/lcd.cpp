
#include <Arduino.h>
#include <ArduinoJson.h>
#include "app_config.h"
#include <U8g2lib.h>
#include "emonesp.h"
#include <ESP8266WiFi.h>

static U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void lcd_setup()
{
  String nodename = node_name.c_str();
  String cfw = ESCAPEQUOTE(BUILD_TAG);
  u8g2.begin();
  u8g2.setContrast(5); // 0..255
  u8g2.setFont(u8g2_font_t0_11_mr);
  u8g2.clearBuffer();
  u8g2.setCursor(5, 15);
  u8g2.print("EmonESP Starting...");
  u8g2.setCursor(5, 30);
  u8g2.print("Node: " + nodename);
  u8g2.setCursor(5, 45);
  u8g2.print("Version: " + cfw);
  u8g2.sendBuffer();
  delay(1000);
}

void lcd_display(JsonDocument &json)
{
  IPAddress myAddress = WiFi.localIP();
  char tmpStr[40];
  sprintf_P(tmpStr, PSTR("%d.%d.%d.%d"), myAddress[0], myAddress[1], myAddress[2], myAddress[3]);
  String ipaddress = tmpStr;

  JsonObject jsonobj = json.as<JsonObject>();
  int linehight = 12;
  int shift = 0;
  String vrms = jsonobj["vrms"];
  int L1 = jsonobj["ct1"];
  int L2 = jsonobj["ct2"];
  int L3 = jsonobj["ct3"];
  float temp = jsonobj["t0"];
  int power = L1 + L2 + L3;

  u8g2.clearBuffer();
  shift = shift + linehight; u8g2.setCursor(0, shift);
  u8g2.print("Vrms: " + vrms + "V");

  if (temp!=300 and temp!=0) {
    char str[4];
    dtostrf(temp, 3, 1, str);

    u8g2.setCursor(70, shift);
    u8g2.print("T:" + String(str) + "C");
  }

  shift = shift + linehight; u8g2.setCursor(0, shift);
  u8g2.print("Total Power: " + String(power) + "W");
  shift = shift + linehight; u8g2.setCursor(0, shift);
  u8g2.print("L1:");
  u8g2.setCursor(40, shift);
  u8g2.print("L2:");
  u8g2.setCursor(80, shift);
  u8g2.print("L3:");
  shift = shift + linehight; u8g2.setCursor(0, shift);
  u8g2.print(String(L1)+"W");
  u8g2.setCursor(40, shift);
  u8g2.print(String(L2)+"W");
  u8g2.setCursor(80, shift);
  u8g2.print(String(L3)+"W");

  shift = shift + linehight; u8g2.setCursor(0, shift);
  u8g2.print("IP: " + ipaddress);
  u8g2.sendBuffer();
}

