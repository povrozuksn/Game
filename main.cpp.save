#include "TXLib.h"

struct Spaceman
{
   int x;
   int y;
   HDC image_left;
   HDC image_right;
   HDC image;
   int vx;
   int vy;
};


int main()
{
txCreateWindow (800, 600);

    //Параметры Фона
    HDC background = txLoadImage ("Pictures/fon.bmp");
    int xFon = -1800;
    int yFon = -1200;


    //Инициализация объекта "Космический кораблю"
    HDC spaceshipeUp = txLoadImage ("Pictures/spaceshipe_Up.bmp");
    HDC spaceshipeDown = txLoadImage ("Pictures/spaceshipe_Down.bmp");
    HDC spaceshipeLeft = txLoadImage ("Pictures/spaceshipe_Left.bmp");
    HDC spaceshipeRight = txLoadImage ("Pictures/spaceshipe_Right.bmp");
    HDC spaceshipe = spaceshipeUp;
    int xSpaceShip = 600;
    int ySpaceShip = 300;

    //Инициализация объекта "Космонавт"
    Spaceman spaceman = {400, 300,  txLoadImage ("Pictures/spaceman1Left.bmp"), txLoadImage ("Pictures/spaceman1Right.bmp"), spaceman.image_right};

    int y0Spaceman = 550;

    //Инициализация объекта "Космонавт2"
    Spaceman spaceman2 = {100, 100, txLoadImage ("Pictures/spacemanLeft.bmp"), txLoadImage ("Pictures/spacemanRight.bmp"), spaceman2.image_right, 10};

    //Инициализация снаряда
    int xBullet;
    int yBullet;
    int vx = 5;
    bool Bullet_visible = false;

    int x1 = 200;
    int x2 = 300;
    int y1 = 400;
    int y2 = 600;

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txClear();

        //Рисование Фона
        txBitBlt (txDC(), xFon, yFon, 3600, 2400, background);


        //Пропорции космического корабля
        if(spaceshipe == spaceshipeUp || spaceshipe == spaceshipeDown)
            txTransparentBlt (txDC(), xSpaceShip, ySpaceShip, 131, 200, spaceshipe, 0, 0, TX_BLACK);
        else if(spaceshipe == spaceshipeLeft || spaceshipe == spaceshipeRight)
            txTransparentBlt (txDC(), xSpaceShip, ySpaceShip, 200, 131, spaceshipe, 0, 0, TX_BLACK);

        //Управление космическим кораблём
        if(GetAsyncKeyState ('S'))
        {
            yFon -= 10;
            spaceshipe = spaceshipeDown;
        }
        if(GetAsyncKeyState ('W'))
        {
            yFon += 10;
            spaceshipe = spaceshipeUp;
        }
        if(GetAsyncKeyState ('D'))
        {
            xFon -= 10;
            spaceshipe = spaceshipeRight;
        }
        if(GetAsyncKeyState ('A'))
        {
            xFon += 10;
            spaceshipe = spaceshipeLeft;
        }


        txTransparentBlt (txDC(), spaceman.x, spaceman.y, 150, 212, spaceman.image, 0, 0, TX_BLACK);
        //Условие гравитации
        spaceman.y +=20;
        //Условие "земли"
        if(spaceman.y > y0Spaceman - 212)
        {
            spaceman.y = y0Spaceman-212;
        }
        //Условие прышка
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


        txSetColor(TX_WHITE);
        txSetFillColor(TX_WHITE);
        txRectangle(x1, y1, x2, y2);

        if( spaceman.x       < x2 &&
            spaceman.x+150   > x1 &&
            spaceman.y       < y2 &&
            spaceman.y+212   > y1
            )
        {
            if(spaceman.image == spaceman.image_left)
            {
                spaceman.x = x2;
                spaceman.y   = y1-212;
            }
            else if(spaceman.image == spaceman.image_right)
            {
                spaceman.x = x1-150;
                spaceman.y   = y1-212;
            }
        }

        if(Bullet_visible)
        {
            txCircle(xBullet, yBullet, 10);
            xBullet += vx;
        }
        if(GetAsyncKeyState (VK_CONTROL))
        {
            xBullet = spaceman.x+10;
            yBullet = spaceman.y+70;
            if(spaceman.image == spaceman.image_right)
            {
                vx=vx;
            }

            if(spaceman.image == spaceman.image_left)
            {
                vx=-vx;
            }

            Bullet_visible = true;
        }


        txTransparentBlt (txDC(), spaceman2.x, spaceman2.y, 147, 150, spaceman2.image,  0, 0, TX_BLACK);
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

