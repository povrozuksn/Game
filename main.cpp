#include "TXLib.h"

struct Spaceman
{
   int x;
   int y;
   HDC image_left;
   HDC image_right;
   HDC image;
   int w_image;
   int h_image;
   int vx;
   int vy;
};

struct Barrier
{
    int x;
    int y;
    int w;
    int h;
    COLORREF color;

    void draw()
    {
        txSetColor(color);
        txSetFillColor(color);
        txRectangle(x, y, x+w, y+h);
    }
};

struct Bullet
{
    int x;
    int y;
    bool visible;
    int vx;
    int vy;

    void draw()
    {
       txSetColor (TX_WHITE);
       txSetFillColor (TX_BLACK);
       txCircle(x, y, 5);
    }
};

void drawSpaceman(Spaceman spaceman)
{
    txTransparentBlt (txDC(), spaceman.x,  spaceman.y,  spaceman.w_image, spaceman.h_image, spaceman.image, 0, 0, TX_BLACK);
}

int main()
{
txCreateWindow (800, 600);

    HDC background = txLoadImage ("Pictures/fon.bmp");
    int xFon = -1800;
    int yFon = -1200;
    int y0Spaceman = 550;

    Spaceman spaceman = {400, 300,  txLoadImage ("Pictures/spaceman1Left.bmp"),
    txLoadImage ("Pictures/spaceman1Right.bmp"), spaceman.image_right, 150, 212};

    Spaceman spaceman2 = {100, 100, txLoadImage ("Pictures/spacemanLeft.bmp"),
    txLoadImage ("Pictures/spacemanRight.bmp"), spaceman2.image_right, 147, 150, 10};

    Barrier bar1 = {200, 400, 100, 200, TX_WHITE};
    Barrier bar2 = {400, 50, 50, 50, TX_GREEN};

    Bullet bul = {0, 0, false, 0, 10};

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txClear();

        //���������
        txBitBlt (txDC(), xFon, yFon, 3600, 2400, background);

        drawSpaceman(spaceman);
        drawSpaceman(spaceman2);

        bar1.draw();
        bar2.draw();

        if(bul.visible)
        {
            bul.draw();
            bul.y -= bul.vy;
        }

        //������� ����������
        spaceman.y +=20;
        //������� "�����"
        if(spaceman.y > y0Spaceman - 212)
        {
            spaceman.y = y0Spaceman-212;
        }
        //������� ������
        if(GetAsyncKeyState (VK_SPACE))
        {
            spaceman.y -= 80;
        }

        if(GetAsyncKeyState (VK_RIGHT))
        {
            spaceman.x += 10;
            spaceman.image = spaceman.image_right;
        }
        if(GetAsyncKeyState (VK_LEFT))
        {
            spaceman.x -= 10;
            spaceman.image = spaceman.image_left;
        }


        if( spaceman.x       < bar1.x+bar1.w &&
            spaceman.x+150   > bar1.x &&
            spaceman.y       < bar1.y+bar1.h &&
            spaceman.y+212   > bar1.y
            )
        {
            if(spaceman.image == spaceman.image_left)
            {
                spaceman.x = bar1.x+bar1.w;
                spaceman.y   = bar1.y-212;
            }
            else if(spaceman.image == spaceman.image_right)
            {
                spaceman.x = bar1.x-150;
                spaceman.y   = bar1.y-212;
            }
        }


        if(GetAsyncKeyState (VK_CONTROL))
        {
            bul.x = spaceman.x+10;
            bul.y = spaceman.y+70;
            bul.visible = true;
        }


        spaceman2.x = spaceman2.x + spaceman2.vx;
        if(spaceman2.x > 800 - 147 || spaceman2.x < 0)
        {
            spaceman2.vx = - spaceman2.vx;
            if(spaceman2.vx > 0)
            {
                spaceman2.image = spaceman2.image_right;
            }
            else spaceman2.image = spaceman2.image_left;
        }


        txEnd();
        txSleep(10);

    }

    txDeleteDC (background);
    txDeleteDC (spaceman.image);
    txDeleteDC (spaceman2.image);

txTextCursor (false);
txDisableAutoPause ();
return 0;
}

