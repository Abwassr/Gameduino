#include "TetrisCanvas.h"

void TETRIS_MENU_ENTRY::drawPage(Adafruit_ILI9341 tft, long frame)
{
    Serial.println("TETRIS_MENU_ENTRY");
    tft.setTextSize(4);
    int *data = getBBoxOfText(tft, "Tetris");
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(data[2] + 5, data[3] + 5);
    tft.fillRect(0, data[3], LCD_WIDTH, data[1] + 5, tft.color565(21, 21, 21));
    tft.println("Tetris");

    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(data[2], data[3]);
    tft.println("Tetris");
}

void TETRIS_MENU_ENTRY::onSelect()
{
}

void TETRIS_CANVAS::drawScreen(Adafruit_ILI9341 tft, long frame)
{
    tft.fillScreen(tft.color565(255, 0, 0));
    tft.setCursor(10, 10);
}
void TETRIS_CANVAS::handleJoyStick(int x, int y, double angle)
{
}
void TETRIS_CANVAS::handleBTN1()
{
}
void TETRIS_CANVAS::handleBTN2()
{
}
/*
bool *TETRIS_TILES::getBitMask(TETRIS_TILE_TYPE type)
{
    switch (type)
    {
    case I_SHAPE:
        bool shape[1][4] = {{1, 1, 1, 1}};
        return *shape;

    case J_SHAPE:
        bool shape[2][3] = {{1, 1, 1}, {0, 0, 1}};
        return *shape;

    case L_SHAPE:
        bool shape[2][3] = {{1, 1, 1}, {1, 0, 0}};
        return *shape;

    case O_SHAPE:
        bool shape[2][2] = {{1, 1}, {1, 1}};
        return *shape;

    case S_SHAPE:
        bool shape[2][3] = {{1, 1, 0}, {0, 1, 1}};
        return *shape;

    case T_SHAPE:
        bool shape[2][3] = {{1, 1, 1}, {0, 1, 0}};
        return *shape;

    case Z_SHAPE:
        bool shape[2][3] = {{1, 1, 0}, {0, 1, 1}};
        return *shape;
    }
}*/