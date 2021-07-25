#pragma once

#include "Pins.h"

#define PIN_BTN_1 0
#define PIN_BTN_2 1
#define PIN_BTN_3 2
#define PIN_DIP_1 3
#define PIN_DIP_2 4
#define PIN_DIP_3 5
#define PIN_DIP_4 6
#define PIN_SWI_1 15
#define PIN_SWI_2 18
#define PIN_SWI_3 19

// JOYSTICK CALIBRATION
#define JOYSTICK_CALI_SOUTH 130

#define LCD_WIDTH 320
#define LCD_HEIGHT 240
#define HALF_LCD_WIDTH (LCD_WIDTH / 2)
#define HALF_LCD_HEIGHT (LCD_HEIGHT / 2)
#define FPS 24      //* Framerate is capped to 24FPS to improve consitency, maybe integrade a "frame delta" time
#define DEBUG false // ? Toggles Debug mode (FPS counter, Game specific debugging)
#define VERBOSE true
#define MAX_FREE_HEAP 51432

#define CONSOLE_NAME "Gameduino"
#define DEV_NAME "Bodensee Fuechse 2021"
#define VERSION "IN DEV"

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NORTH_EAST,
    EAST_SOUTH,
    SOUTH_WEST,
    WEST_NORTH,
    TO_WEAK,
    UNDEFINED
};
enum NESW_Direction
{
    NESW_NORTH,
    NESW_EAST,
    NESW_SOUTH,
    NESW_WEST,
    NESW_UNDEFINED
};

int *getBBoxOfText(Adafruit_ILI9341 tft, String text);
int *getJoyStickPos();
Direction getJoyStickDirection();
double getJoyStickAngle();
double normalizeAngle(double angle);