#include "../mainCanvas/MainCanvas.h"
#include "../Game.h"

class PACMAN_MENU_ENTRY : public MAIN_MENU_ENTRY
{
public:
    void drawPage(Adafruit_ILI9341 tft, long frame);
    void onSelect();
};
class PACMAN_CANVAS : public GAME
{
public:
    uint16 grid_count_x = 18;
    uint16 grid_x = LCD_WIDTH / grid_count_x;
    uint16 grid_count_y = LCD_HEIGHT / grid_x;
    uint16 grid_y = LCD_WIDTH / grid_count_x;
    uint16 px = grid_x * 9;
    uint16 py = grid_x * 6;
    uint16 vx = 1;
    uint16 vy = 0;
    uint16 pacman_radius = 5;
    BOUNDINGBOX pac_bb = BOUNDINGBOX(px - pacman_radius, py - pacman_radius, pacman_radius * 2, pacman_radius * 2);
    void drawScreen(Adafruit_ILI9341 tft, long frame);
    void handleJoyStick(int x, int y, double angle);
    void handleBTN1();
    void handleBTN2();
    void drawBackground(Adafruit_ILI9341 tft, long frame);
    void drawPacMan(Adafruit_ILI9341 tft);
    void movePacMan(Adafruit_ILI9341 tft);
    int checkCollision();
};
class PACMAN_WALL
{
public:
    long wallX1;
    long wallY1;
    long wallX2;
    long wallY2;
    PACMAN_WALL(long wallX1, long wallY1, long wallX2, long wallY2)
    {
        uint16 grid = LCD_WIDTH / 18; // THE 20 is from the PACMAN_CANVAS class!
        long offset = grid / 2;
        long wx1 = wallX1 * grid + offset;
        long wy1 = wallY1 * grid + offset;
        long wx2 = wallX2 * grid + offset;
        long wy2 = wallY2 * grid + offset;
        long yBuffer = 0;
        long xBuffer = 0;
        if (wx2 - wx1 > wy2 - wy1)
        {
            yBuffer = 1;
        }
        if (wx2 - wx1 < wy2 - wy1)
        {
            xBuffer = 1;
        }
        this->wallX1 = wx1 - xBuffer;
        this->wallY1 = wy1 - yBuffer;
        this->wallX2 = wx2 + (2 * xBuffer);
        this->wallY2 = wy2 + (2 * yBuffer);
    }

    virtual ~PACMAN_WALL()
    {
    }
    void print()
    {
        /*Serial.print("WallX1: ");
        Serial.println(wallX1);
        Serial.print("WallY1: ");
        Serial.println(wallY1);
        Serial.print("WallX2: ");
        Serial.println(wallX2);
        Serial.print("WallY2: ");
        Serial.println(wallY2);
        Serial.println("###########");*/
    }
    void draw(Adafruit_ILI9341 tft)
    {
        tft.fillRect(wallX1, wallY1, wallX2 - wallX1, wallY2 - wallY1, tft.color565(0, 139, 115));
    }
    bool isPointInside(int px, int py)
    {
        return (wallX1 < px && wallX2 > px && wallY1 < py && wallY2 > py);
    }
    bool checkCollisions(int px, int py, int radius)
    {
        for (int j = 0; j < 4; j++)
        {
            int testX = (j % 2 == 0) ? px - radius : px + radius;
            int testY = (j < 2) ? py - radius : py + radius;
            /*Serial.print("testX");
            Serial.println(testX);
            Serial.print("testY");
            Serial.println(testY);
            Serial.print("Result: ");
            Serial.println(isPointInside(testX, testY));*/
            if (isPointInside(testX, testY))
                return true;
        }
        return false;
    }
};