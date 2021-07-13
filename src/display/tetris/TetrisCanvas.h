#include "../mainCanvas/MainCanvas.h"
#include "../Game.h"

class TETRIS_MENU_ENTRY : public MAIN_MENU_ENTRY
{
public:
    void drawPage(Adafruit_ILI9341 tft, long frame);
    void onSelect();
};

class TETRIS_CANVAS : public GAME
{
public:
    void drawScreen(Adafruit_ILI9341 tft, long frame);
    void handleJoyStick(int x, int y);
    void handleBTN1();
    void handleBTN2();
};

enum TETRIS_TILE_TYPE
{
    I_SHAPE,
    J_SHAPE,
    L_SHAPE,
    O_SHAPE,
    S_SHAPE,
    T_SHAPE,
    Z_SHAPE
};

class TETRIS_TILES
{
    bool *getBitMask(TETRIS_TILE_TYPE type);
};