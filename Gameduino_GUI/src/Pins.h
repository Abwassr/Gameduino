#pragma once

// Blue LED
#define PIN_LED1 53
// Green LED
#define PIN_LED2 52
// Red LED
#define PIN_LED3 51

#define JOY_X 1000 // ? ANALOG PINS SIND EIN GERÜCHT.... zumindest auf ESP
#define JOY_Y 1000 // ? ANALOG PINS SIND EIN GERÜCHT.... zumindest auf ESP
#define JOY_SW 6

// NORMAL (OUR TFT)

#define TFT_CS 21
#define TFT_DC 57
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST -1
#define TFT_MISO 12
#define TFT_RT_CS 20

/*
// FLIPPED (ROBOTER AG TFT)
#define TFT_CS 21
#define TFT_DC 20
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST -1
#define TFT_MISO 12
#define TFT_RT_CS 57
*/
/*
// GAMEDUINO
#define TFT_CS 5
#define TFT_DC 3
#define TFT_MOSI 12
#define TFT_CLK 13
#define TFT_RST -1
#define TFT_MISO 11
#define TFT_RT_CS 6
*/
/*
// ESP8266
#define TFT_CS 10
#define TFT_DC 9
#define TFT_MOSI 13
#define TFT_CLK 14
#define TFT_RST -1
#define TFT_MISO 12
#define TFT_RT_CS 6
*/