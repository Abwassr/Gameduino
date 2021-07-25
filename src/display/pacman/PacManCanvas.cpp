#include "PacManCanvas.h"
#include "main.h"

uint8_t bgcolor[] = {201, 196, 0}; // Unsigned 8-bit Numbers
NESW_Direction lastPressedDirection = NESW_UNDEFINED;
Point lastTileVisited = Point(0, 0);
uint16 score = 0;

PACMAN_WALL walls[] = {
    //? LOWER WALL
    PACMAN_WALL(0, 13, 18, 13),

    //? UPPER WALL
    PACMAN_WALL(0, 1, 18, 1),

    //? LEFT WALL
    PACMAN_WALL(0, 1, 0, 5),
    PACMAN_WALL(0, 5, 2, 5),
    PACMAN_WALL(2, 5, 2, 6),
    PACMAN_WALL(-1, 6, 2, 6),
    PACMAN_WALL(-1, 7, 2, 7),
    PACMAN_WALL(2, 7, 2, 8),
    PACMAN_WALL(0, 8, 2, 8),
    PACMAN_WALL(0, 8, 0, 13),

    //? RIGHT WALL
    PACMAN_WALL(18, 1, 18, 5),
    PACMAN_WALL(16, 5, 18, 5),
    PACMAN_WALL(16, 5, 16, 6),
    PACMAN_WALL(16, 6, 19, 6),
    PACMAN_WALL(16, 7, 19, 7),
    PACMAN_WALL(16, 7, 16, 8),
    PACMAN_WALL(16, 8, 18, 8),
    PACMAN_WALL(18, 8, 18, 13),

    // A
    PACMAN_WALL(1, 2, 3, 2),
    PACMAN_WALL(1, 3, 3, 3),
    PACMAN_WALL(1, 2, 1, 3),
    PACMAN_WALL(3, 2, 3, 3),

    // B
    PACMAN_WALL(1, 4, 2, 4),

    // C
    PACMAN_WALL(1, 9, 2, 9),

    // D
    PACMAN_WALL(1, 10, 3, 10),
    PACMAN_WALL(1, 12, 3, 12),
    PACMAN_WALL(1, 10, 1, 12),
    PACMAN_WALL(3, 10, 3, 12),
    PACMAN_WALL(3, 11, 4, 11),

    // E
    PACMAN_WALL(3, 4, 3, 6),
    PACMAN_WALL(3, 5, 5, 5),
    PACMAN_WALL(5, 4, 5, 5),

    // F
    PACMAN_WALL(3, 7, 3, 9),
    PACMAN_WALL(3, 8, 4, 8),

    // G
    PACMAN_WALL(4, 1, 4, 2),

    // H
    PACMAN_WALL(4, 3, 4, 4),
    PACMAN_WALL(4, 3, 5, 3),
    PACMAN_WALL(5, 2, 5, 3),
    PACMAN_WALL(5, 2, 7, 2),

    // I
    PACMAN_WALL(6, 3, 6, 5),
    PACMAN_WALL(6, 4, 8, 4),

    // J
    PACMAN_WALL(4, 6, 4, 7),

    // K
    PACMAN_WALL(5, 6, 6, 6),

    // L
    PACMAN_WALL(5, 7, 6, 7),

    // M
    PACMAN_WALL(5, 8, 5, 9),
    PACMAN_WALL(4, 9, 7, 9),
    PACMAN_WALL(4, 9, 4, 10),

    // N
    PACMAN_WALL(4, 12, 4, 13),

    // O
    PACMAN_WALL(5, 10, 5, 12),
    PACMAN_WALL(5, 11, 8, 11),
    PACMAN_WALL(5, 12, 6, 12),
    PACMAN_WALL(6, 11, 6, 12),
    PACMAN_WALL(8, 10, 8, 11),

    // P
    PACMAN_WALL(8, 1, 8, 2),

    // Q
    PACMAN_WALL(9, 2, 9, 3),

    // R
    PACMAN_WALL(7, 3, 8, 3),

    // S
    PACMAN_WALL(7, 5, 11, 5),
    PACMAN_WALL(9, 4, 9, 5),

    // T
    PACMAN_WALL(7, 6, 11, 6),
    PACMAN_WALL(7, 6, 7, 8),
    PACMAN_WALL(11, 6, 11, 8),
    PACMAN_WALL(6, 8, 12, 8),

    // U
    PACMAN_WALL(6, 10, 7, 10),

    // V
    PACMAN_WALL(7, 12, 7, 13),

    // W
    PACMAN_WALL(8, 9, 10, 9),
    PACMAN_WALL(9, 9, 9, 10),

    // X
    PACMAN_WALL(9, 11, 9, 12),
    PACMAN_WALL(8, 12, 10, 12),

    // P'
    PACMAN_WALL(10, 1, 10, 2),

    // R'
    PACMAN_WALL(10, 3, 11, 3),

    // I'
    PACMAN_WALL(10, 4, 12, 4),
    PACMAN_WALL(12, 3, 12, 5),

    // M'
    PACMAN_WALL(13, 8, 13, 9),
    PACMAN_WALL(11, 9, 14, 9),
    PACMAN_WALL(14, 9, 14, 10),

    // O'
    PACMAN_WALL(13, 10, 13, 12),
    PACMAN_WALL(10, 11, 13, 11),
    PACMAN_WALL(12, 12, 13, 12),
    PACMAN_WALL(12, 11, 12, 12),
    PACMAN_WALL(10, 10, 10, 11),

    // D'
    PACMAN_WALL(15, 10, 17, 10),
    PACMAN_WALL(15, 12, 17, 12),
    PACMAN_WALL(17, 10, 17, 12),
    PACMAN_WALL(15, 10, 15, 12),
    PACMAN_WALL(14, 11, 15, 11),

    // V'
    PACMAN_WALL(11, 12, 11, 13),

    // N'
    PACMAN_WALL(14, 12, 14, 13),

    // U'
    PACMAN_WALL(11, 10, 12, 10),

    // F'
    PACMAN_WALL(15, 7, 15, 9),
    PACMAN_WALL(14, 8, 15, 8),

    // J'
    PACMAN_WALL(14, 6, 14, 7),

    // K'
    PACMAN_WALL(12, 6, 13, 6),

    // L'
    PACMAN_WALL(12, 7, 13, 7),

    // C'
    PACMAN_WALL(16, 9, 17, 9),

    // E'
    PACMAN_WALL(15, 4, 15, 6),
    PACMAN_WALL(13, 5, 15, 5),
    PACMAN_WALL(13, 4, 13, 5),

    // H'
    PACMAN_WALL(14, 3, 14, 4),
    PACMAN_WALL(13, 3, 14, 3),
    PACMAN_WALL(13, 2, 13, 3),
    PACMAN_WALL(11, 2, 13, 2),

    // G'
    PACMAN_WALL(14, 1, 14, 2),

    // A'
    PACMAN_WALL(15, 2, 17, 2),
    PACMAN_WALL(15, 3, 17, 3),
    PACMAN_WALL(17, 2, 17, 3),
    PACMAN_WALL(15, 2, 15, 3),

    // B'
    PACMAN_WALL(16, 4, 17, 4),
};

void PACMAN_MENU_ENTRY::drawPage(Adafruit_ILI9341 tft, long frame)
{
    Serial.println("PACMAN_MENU_ENTRY");
    tft.setTextSize(4);
    int *data = getBBoxOfText(tft, "PacMan");
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(data[2] + 5, data[3] + 5);
    tft.fillRect(0, data[3], LCD_WIDTH, data[1] + 5, tft.color565(21, 21, 21));
    tft.println("PacMan");

    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(data[2], data[3]);
    tft.println("PacMan");
}

void PACMAN_MENU_ENTRY::onSelect()
{
    Serial.println("STARTING PACMAN");
    PACMAN_CANVAS *canvas = new PACMAN_CANVAS();
    setCurrentlyDisplayedCanvas(canvas);
}

void PACMAN_CANVAS::drawScreen(Adafruit_ILI9341 tft, long frame)
{

    //* All fixed with simple frame==0 check!😀
    // // TODO  Optimize redraw (dont redraw if nothing changed)
    // // ?     Zones?, dont draw black?
    // // * Only draw background on the first frame (Performance Optimization)
    /*Serial.print(grid_count_x);
    Serial.print("@");
    Serial.print(grid_x);
    Serial.print("px");
    Serial.print("\t");
    Serial.print(grid_count_y);
    Serial.print("@");
    Serial.print(grid_y);
    Serial.println("px");*/
    if (frame == 0)
    {
        lastTileVisited = Point(px, py);
        drawBackground(tft, frame);
        for (int i = 0; i < sizeof(walls) / sizeof(walls[0]); i++)
            walls[i].draw(tft);
        tft.setCursor(10, 2);
        tft.setTextSize(2);
        tft.print("Score: ");
        tft.setCursor(185, 2);
        tft.print("PacMan");
        tft.setTextSize(1);
        tft.setCursor(260, 1);
        tft.print("Bodensee");
        tft.setCursor(260, 10);
        tft.print("Fuechse");
    }
    movePacMan(tft); //! HEAP LEAK: 24hpc
    drawPacMan(tft); //* NO HEAP LEAK
    tft.fillRect(90, 2, 60, 18, tft.color565(26, 26, 26));
    tft.setCursor(90, 2);
    tft.setTextSize(2);
    tft.print(score);
}
void PACMAN_CANVAS::handleJoyStick(int x, int y, double angle)
{
    if (angle > -22.5 && angle < 22.5)
    {
        lastPressedDirection = NESW_NORTH;
    }
    if (angle > -157.5 && angle < -22.5)
    {
        lastPressedDirection = NESW_WEST;
    }
    if (angle < -157.5 || angle > 157.5)
    {
        lastPressedDirection = NESW_SOUTH;
    }
    if (angle < 157.5 && angle > 22.5)
    {
        lastPressedDirection = NESW_EAST;
    }
    //int absFromSouth = 2;
}
void PACMAN_CANVAS::handleBTN1()
{
    // ? Braucht man überhaupt Buttons für Pacman?
}
void PACMAN_CANVAS::handleBTN2()
{
    // ? Braucht man überhaupt Buttons für Pacman?
}
void PACMAN_CANVAS::drawBackground(Adafruit_ILI9341 tft, long frame)
{
    tft.fillScreen(tft.color565(21, 21, 21));
    tft.setTextSize(1);
    if (DEBUG)
    {
        for (int tile_x = 0; tile_x <= grid_count_x; tile_x++)
        {
            tft.drawLine(tile_x * grid_x, 0, tile_x * grid_x, LCD_HEIGHT, tft.color565(50, 0, 0));
        }
        for (int tile_y = 0; tile_y <= grid_count_y; tile_y++)
        {
            tft.drawLine(0, tile_y * grid_y, LCD_WIDTH, tile_y * grid_y, tft.color565(50, 0, 0));
        }
        for (int tile_x = 0; tile_x <= grid_count_x; tile_x++)
        {
            tft.setCursor(tile_x * grid_x, 10);
            tft.print(tile_x);
            tft.drawLine(tile_x * grid_x + grid_x / 2, 0, tile_x * grid_x + grid_x / 2, LCD_HEIGHT, tft.color565(0, 0, 80));
        }
        for (int tile_y = 0; tile_y <= grid_count_y; tile_y++)
        {
            tft.setCursor(10, tile_y * grid_y);
            tft.print(tile_y);
            tft.drawLine(0, tile_y * grid_y + grid_y / 2, LCD_WIDTH, tile_y * grid_y + grid_y / 2, tft.color565(0, 0, 80));
        }
    }
    /*for (int index = 0; index != wall_count; index++)
    {
        Serial.print("Drawing wall ");
        Serial.print(index);
        Serial.println("!");
        walls[index].draw(tft);
    }*/
}

void PACMAN_CANVAS::drawPacMan(Adafruit_ILI9341 tft)
{
    //* Parameters for PacMan
    int color = tft.color565(255, 255, 0);

    //* Erase old PacMan
    uint16 old_x = px - vx;
    uint16 old_y = py - vy;
    tft.fillCircle(old_x, old_y, pacman_radius, tft.color565(21, 21, 21));

    //* Draw new PacMan
    tft.fillCircle(px, py, pacman_radius, color);
}

void PACMAN_CANVAS::movePacMan(Adafruit_ILI9341 tft)
{
    //* Only accept / process keystrokes when on Tile intersection
    if (px % grid_x == 0 && py % grid_y == 0)
    {
        if (vx != 0 || vy != 0)
            score++;
        lastTileVisited = Point(px, py);
        switch (lastPressedDirection)
        {
        case NORTH:
            vx = 0;
            vy = -1;
            break;
        case EAST:
            vx = -1;
            vy = 0;
            break;
        case SOUTH:
            vx = 0;
            vy = 1;
            break;
        case WEST:
            vx = 1;
            vy = 0;
            break;
        default:
            break;
        }
    }
    px += vx;
    py += vy;

    uint16 old_x = px - vx;
    uint16 old_y = py - vy;
    //* Fix out of Bounds with loop-around
    if (px < 0)
    {
        tft.fillCircle(old_x, old_y, pacman_radius, tft.color565(21, 21, 21));
        px = LCD_WIDTH;
    }
    if (px > LCD_WIDTH)
    {
        tft.fillCircle(old_x, old_y, pacman_radius, tft.color565(21, 21, 21));
        px = 0;
    }
    if (py < 0)
    {
        tft.fillCircle(old_x, old_y, pacman_radius, tft.color565(21, 21, 21));
        py = LCD_HEIGHT;
    }
    if (py > LCD_HEIGHT)
    {
        tft.fillCircle(old_x, old_y, pacman_radius, tft.color565(21, 21, 21));
        py = 0;
    }
    // TODO Center BoundingBox to match the fillCircle used in drawPacMan();

    pac_bb = BOUNDINGBOX(px - pacman_radius, py - pacman_radius, pacman_radius * 2, pacman_radius * 2);
    if (checkCollision() >= 0)
    {
        uint16 wallIndex = checkCollision();
        Serial.println("Collision!!!!!");
        lastPressedDirection = NESW_UNDEFINED;
        tft.fillCircle(px, py, pacman_radius, tft.color565(21, 21, 21));
        vx = 0;
        vy = 0;
        //! WARNING THIS IS UNTESTED CODE, IF CRASHED ACCOUR, PLEASE REMOVE!!!
        walls[wallIndex].draw(getPageManager().getTFT());
        //! END OF UNTESTED CODE
        px = lastTileVisited.gx;
        py = lastTileVisited.gy;
    }
}
bool once = true;
// TODO REWRITE WHOLE WALL SYSTEM
//* REWROTE ENTIRE WALL SYSTEM
//! MUST BE SIGNED INT
int PACMAN_CANVAS::checkCollision()
{
    for (int i = 0; i < sizeof(walls) / sizeof(walls[0]); i++)
    {
        walls[i].print();
        if (walls[i].checkCollisions(px, py, pacman_radius))
        {
            Serial.print("Collision on: ");
            Serial.println(i);
            return i;
        }
    }

    return -1;
}