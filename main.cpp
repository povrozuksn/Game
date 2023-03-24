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
    bool visible;

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

    Spaceman spaceman = {100, 300,  txLoadImage ("Pictures/spaceman1Left.bmp"),
    txLoadImage ("Pictures/spaceman1Right.bmp"), spaceman.image_right, 150, 212};

    int count_bar = 5;
    Barrier bar[count_bar];
    bar[0] = { 50, 50, 50, 50, TX_WHITE, true};
    for(int i=1; i<=count_bar; i++)
    {
        bar[i] = {bar[i-1].x+150, 50, 50, 50, TX_WHITE, true};
    }

    int bull_count = 1;
    Bullet bul[bull_count];

    int n=0;

    int level = 1;

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        //txClear();

        //Рисование
        txBitBlt (txDC(), xFon, yFon, 3600, 2400, background);

        drawSpaceman(spaceman);

        txSetColor(TX_GREEN, 3);
        txSetFillColor(TX_WHITE);
        txRectangle(650, 5, 750, 35);
        txDrawText(650, 5, 750, 35, "старт");

        if( txMouseX() > 650 &&
            txMouseX() < 750 &&
            txMouseY() > 5   &&
            txMouseY() < 35  )
        {
            txSetColor(TX_WHITE, 3);
            txSetFillColor(TX_GREEN);
            txRectangle(650, 5, 750, 35);
            txDrawText(650, 5, 750, 35, "старт");
        }
        if( txMouseButtons() == 1 &&
            txMouseX() > 650 &&
            txMouseX() < 750 &&
            txMouseY() > 5   &&
            txMouseY() < 35  )
        {
            txSetColor(TX_WHITE, 3);
            txSetFillColor(TX_RED);
            txRectangle(650, 5, 750, 35);
            txDrawText(650, 5, 750, 35, "START");
            background = txLoadImage ("Pictures/fon2.bmp");
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

        for(int i=0; i<count_bar; i++)
        {
            if (bar[i].visible)    bar[i].draw();
        }

        if(GetAsyncKeyState (VK_CONTROL))
        {
            for(int i=0; i<bull_count; i++)
            {
                bul[i] = {spaceman.x+10, spaceman.y+70-(i*10), true, 0, 10};
            }
        }

        for(int i=0; i<bull_count; i++)
        {
            if(bul[i].visible)
            {
                bul[i].x = bul[i].x + bul[0].vx;
                bul[i].y = bul[i].y - bul[0].vy;
                bul[i].draw();
            }
        }

        for(int i=0; i<count_bar; i++)
        {
            if( bul[0].x >  bar[i].x &&
                bul[0].x <  bar[i].x + bar[i].w &&
                bul[0].y >  bar[i].y &&
                bul[0].y <  bar[i].y + 15)
            {
                bul[i].visible = false;
                bar[i].visible = false;
                count_bar--;
            }
        }

        //Условие гравитации
        spaceman.y +=10;
        //Условие "земли"
        if(spaceman.y > y0Spaceman - 212)
        {
            spaceman.y = y0Spaceman-212;
        }
        //Условие прышка
        if(GetAsyncKeyState (VK_SPACE))
        {
            spaceman.y -= 50;
        }


        char str[100];
        sprintf(str, "Уровень = %d Мишень - %d", level, count_bar);
        txSetColor(TX_WHITE);
        txTextOut(10,10,str);

        if(count_bar<1)
        {
            level = 2;
            background = txLoadImage ("Pictures/fon1.bmp");
            count_bar = 10;
            bar[0] = { 50, 50, 25, 25, TX_WHITE, true};
            for(int i=1; i<=count_bar; i++)
            {
                bar[i] = {bar[i-1].x+100, 50, 25, 25, TX_WHITE, true};
            }
        }

        txEnd();
        txSleep(10);
    }

    txDeleteDC (background);
    txDeleteDC (spaceman.image);


txTextCursor (false);
txDisableAutoPause ();
return 0;
}

