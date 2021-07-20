#include "PacManCanvas.h"
#include "main.h"

uint8_t bgcolor[] = {201, 196, 0}; // Unsigned 8-bit Numbers
NESW_Direction lastPressedDirection = NESW_UNDEFINED;
Point *lastTileVisited = new Point(0, 0);

PACMAN_WALL *walls;

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
        walls = getMap();
        drawBackground(tft, frame);
    }
    movePacMan(tft); //! HEAP LEAK: 24hpc
    drawPacMan(tft); //* NO HEAP LEAK
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
    pac_bb.show(getPageManager().getTFT(), 0, 128, 128);
    if (checkCollision())
    {
        Serial.println("Collision!!!!!");
        vx = 0;
        vy = 0;
        px = lastTileVisited->gx;
        py = lastTileVisited->gy;
    }
}
bool once = true;
// TODO REWRITE WHOLE WALL SYSTEM
bool PACMAN_CANVAS::checkCollision()
{
    if (once)
        for (unsigned int a = 0; a < 2; a = a + 1)
        {
            Serial.print("wall_x: ");
            Serial.println(walls[a].x);
            Serial.print("wall_y: ");
            Serial.println(walls[a].y);
            Serial.print("wall_w: ");
            Serial.println(walls[a].w);
            Serial.print("wall_h: ");
            Serial.println(walls[a].h);
            Serial.println("------");
            Serial.print("wall_bb_x: ");
            Serial.println(walls[a].bb.bbx);
            Serial.print("wall_bb_y: ");
            Serial.println(walls[a].bb.bby);
            Serial.print("wall_bb_w: ");
            Serial.println(walls[a].bb.bbw);
            Serial.print("wall_bb_h: ");
            Serial.println(walls[a].bb.bbh);
            Serial.println("------");
            once = false;
        }
    return false;
}

PACMAN_WALL *PACMAN_CANVAS::getMap()
{
    PACMAN_WALL walls2[] = {
        // Walls of the map!
        createWall(0, 0, grid_count_x, 0),
        createWall(0, 0, 0, grid_count_y)};
    return &*walls2;
}

PACMAN_WALL PACMAN_CANVAS::createWall(uint16 tileX, uint16 tileY, uint16 tileX2, uint16 tileY2)
{
    wall_count++;
    Serial.print("tileX: ");
    Serial.println((uint16)tileX);
    Serial.print("tileY: ");
    Serial.println((uint16)tileY);
    Serial.print("tileX2: ");
    Serial.println((uint16)tileX2);
    Serial.print("tileY2: ");
    Serial.println((uint16)tileY2);
    Serial.println("-------");
    Serial.print("Wall_X: ");
    Serial.println((uint16)tileX * grid_x + grid_x / 2);
    Serial.print("Wall_Y: ");
    Serial.println((uint16)tileY * grid_y + grid_y / 2);
    Serial.print("Wall_W: ");
    Serial.println((uint16)(tileX2 - tileX) * grid_x);
    Serial.print("Wall_H: ");
    Serial.println((uint16)(tileY2 - tileY) * grid_y);
    Serial.println("-------");

    return PACMAN_WALL(tileX * grid_x + grid_x / 2, tileY * grid_y + grid_y / 2, (tileX2 - tileX) * grid_x, (tileY2 - tileY) * grid_y);
}