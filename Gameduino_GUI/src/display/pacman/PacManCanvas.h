#include "../mainCanvas/MainCanvas.h"
#include "../Game.h"

class PACMAN_MENU_ENTRY : public MAIN_MENU_ENTRY
{
public:
    void drawPage(Adafruit_ILI9341 tft, long frame);
    void onSelect();
};

class PACMAN_WALL
{
public:
    PACMAN_WALL(int x, int y, int w, int h);
    int x;
    int y;
    int w;
    int h;
    bool checkforColllisions(int cx, int cy)
    {
        /*int maxX = x + w;
        int maxY = y + h;*/
        return false; // TODO Programm, currently just placeholder
    }
    void draw(Adafruit_ILI9341 tft);
};

class PACMAN_CANVAS : public GAME
{
public:
    int px = HALF_LCD_WIDTH;
    int py = HALF_LCD_HEIGHT;
    int vx = 0;
    int vy = 0;
    int grid_count_x = 20;
    int grid_x = LCD_WIDTH / grid_count_x;
    int grid_count_y = LCD_WIDTH / grid_x;
    int grid_y = LCD_WIDTH / grid_count_y;
    int pacman_radius = 5;
    void drawScreen(Adafruit_ILI9341 tft, long frame);
    void handleJoyStick(int x, int y);
    void handleBTN1();
    void handleBTN2();
    void drawBackground(Adafruit_ILI9341 tft, long frame);
    void drawPacMan(Adafruit_ILI9341 tft);
    void movePacMan();
    bool checkCollision();
};
