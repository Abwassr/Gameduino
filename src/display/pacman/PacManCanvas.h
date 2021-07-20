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
    uint16 x;
    uint16 y;
    uint16 w;
    uint16 h;
    BOUNDINGBOX bb;
    PACMAN_WALL(uint16 x1, uint16 y1, uint16 w1, uint16 h1)
    {
        x = x1;
        y = y1;
        w = w1;
        h = h1;

        int yBuffer = 0;
        int xBuffer = 0;
        if (w > h)
            yBuffer = 1;
        else if (h > w)
            xBuffer = 1;
        Serial.print("Wall_BB_X: ");
        Serial.println(x - xBuffer);
        Serial.print("Wall_BB_Y: ");
        Serial.println(y - yBuffer);
        Serial.print("Wall_BB_W: ");
        Serial.println(w + 2 * xBuffer);
        Serial.print("Wall_BB_H: ");
        Serial.println(h + 2 * yBuffer);
        Serial.println("-------");
        bb = BOUNDINGBOX(x - xBuffer, y - yBuffer, w + 2 * xBuffer, h + 2 * yBuffer);
    }
    void draw(Adafruit_ILI9341 tft)
    {
        tft.drawRect(bb.bbx, bb.bby, bb.bbw, bb.bbh, tft.color565(255, 255, 0));
    }
};

class PACMAN_CANVAS : public GAME
{
public:
    uint16 px = HALF_LCD_WIDTH;
    uint16 py = HALF_LCD_HEIGHT;
    uint16 vx = 0;
    uint16 vy = 0;
    uint16 grid_count_x = 20;
    uint16 grid_x = LCD_WIDTH / grid_count_x;
    uint16 grid_count_y = LCD_HEIGHT / grid_x;
    uint16 grid_y = LCD_WIDTH / grid_count_x;
    uint16 pacman_radius = 5;
    uint16 wall_count = 0;
    BOUNDINGBOX pac_bb = BOUNDINGBOX(px - pacman_radius, py - pacman_radius, pacman_radius * 2, pacman_radius * 2);
    void drawScreen(Adafruit_ILI9341 tft, long frame);
    void handleJoyStick(int x, int y, double angle);
    void handleBTN1();
    void handleBTN2();
    void drawBackground(Adafruit_ILI9341 tft, long frame);
    void drawPacMan(Adafruit_ILI9341 tft);
    void movePacMan(Adafruit_ILI9341 tft);
    bool checkCollision();
    PACMAN_WALL *getMap();
    PACMAN_WALL createWall(uint16 tileX, uint16 tileY, uint16 width, uint16 height);
};
