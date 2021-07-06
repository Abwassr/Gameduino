#include "PacManCanvas.h"
#include "main.h"

uint8_t bgcolor[] = {201, 196, 0}; // Unsigned 8-bit Numbers
NESW_Direction lastPressedDirection = NESW_UNDEFINED;
Point *lastTileVisited = new Point(0, 0);

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
    if (frame == 0)
        drawBackground(tft, frame);
    if (frame == 0)
    {
        vy = 1;
    }
    int x = random(4);
    switch (x)
    {
    case 0:
        lastPressedDirection = NESW_NORTH;
        break;
    case 1:
        lastPressedDirection = NESW_EAST;
        break;
    case 2:
        lastPressedDirection = NESW_SOUTH;
        break;
    case 3:
        lastPressedDirection = NESW_WEST;
        break;
    }
    Serial.println(lastPressedDirection);
    movePacMan(tft);
    drawPacMan(tft);

    // ! TODO Center BoundingBox to match the fillCircle used in drawPacMan();
    BOUNDINGBOX *pac_bb = new BOUNDINGBOX(px - pacman_radius, py - pacman_radius, pacman_radius * 2, pacman_radius * 2);
    BOUNDINGBOX *box_bb = new BOUNDINGBOX(10, 10, 10, 10);
}
void PACMAN_CANVAS::handleJoyStick(int x, int y)
{
    // TODO Implement "lastPressedDirection"
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
            tft.drawLine(tile_x * grid_x + grid_x / 2, 0, tile_x * grid_x + grid_x / 2, LCD_HEIGHT, tft.color565(0, 0, 80));
        }
        for (int tile_y = 0; tile_y <= grid_count_y; tile_y++)
        {
            tft.drawLine(0, tile_y * grid_y + grid_y / 2, LCD_WIDTH, tile_y * grid_y + grid_y / 2, tft.color565(0, 0, 80));
        }
    }
}

void PACMAN_CANVAS::drawPacMan(Adafruit_ILI9341 tft)
{
    //* Parameters for PacMan
    int color = tft.color565(255, 255, 0);

    //* Erase old PacMan
    int old_x = px - vx;
    int old_y = py - vy;
    tft.fillCircle(old_x, old_y, pacman_radius, tft.color565(21, 21, 21));

    //* Draw new PacMan
    tft.fillCircle(px, py, pacman_radius, color);
}

void PACMAN_CANVAS::movePacMan(Adafruit_ILI9341 tft)
{
    //* Only accept / process keystrokes when on Tile intersection
    if (px % grid_x == 0 && py % grid_y == 0)
    {
        lastTileVisited = new Point(px, py);
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

    int old_x = px - vx;
    int old_y = py - vy;
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

    if (checkCollision())
    {
    }
}

bool PACMAN_CANVAS::checkCollision()
{
}
