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
    int x;
    int y;
    int w;
    int h;
    PACMAN_WALL(int x1, int y1, int w1, int h1)
    {
        x = x1;
        y = y1;
        w = w1;
        h = h1;
    }
    bool checkforColllisions(int cx, int cy)
    {
        /*int maxX = x + w;
        int maxY = y + h;*/
        return false; // TODO Programm, currently just placeholder
    }
    void draw(Adafruit_ILI9341 tft)
    {
        BOUNDINGBOX *bb = getBB();
        tft.drawRect(bb->bbx, bb->bby, bb->bbw, bb->bbh, tft.color565(255, 255, 0));
    }
    BOUNDINGBOX *getBB()
    {
        int yBuffer = 0;
        int xBuffer = 0;
        if (w > h)
            yBuffer = 1;
        else if (h > w)
            xBuffer = 1;
        BOUNDINGBOX *bb = new BOUNDINGBOX(x - xBuffer, y - yBuffer, w + 2 * xBuffer, h + 2 * yBuffer);
        return bb;
    }
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
    int wall_count = 0;
    PACMAN_WALL *walls;
    void drawScreen(Adafruit_ILI9341 tft, long frame);
    void handleJoyStick(int x, int y);
    void handleBTN1();
    void handleBTN2();
    void drawBackground(Adafruit_ILI9341 tft, long frame);
    void drawPacMan(Adafruit_ILI9341 tft);
    void movePacMan(Adafruit_ILI9341 tft);
    bool checkCollision();
    void initializeMap();
    PACMAN_WALL *createWall(int tileX, int tileY, int width, int height);
};
