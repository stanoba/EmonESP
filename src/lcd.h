#ifndef _EMONESP_LCD_H
#define _EMONESP_LCD_H

#include <Arduino.h>
#include <ArduinoJson.h>

void lcd_setup();
void lcd_display(JsonDocument &json);

#endif