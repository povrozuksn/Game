#include "TXLib.h"

int main()
{
txCreateWindow (800, 600);

    //��������� ����
    HDC background = txLoadImage ("Pictures/fon.bmp");
    int xFon = -1800;
    int yFon = -1200;
/*
    HDC manRight = txLoadImage ("Pictures/manRight.bmp");
    HDC manLeft = txLoadImage ("Pictures/manLeft.bmp");
    HDC man = manRight;
    int n_kadr = 0;
*/

    //������������� ������� "����������� �������"
    HDC spaceshipeUp = txLoadImage ("Pictures/spaceshipe_Up.bmp");
    HDC spaceshipeDown = txLoadImage ("Pictures/spaceshipe_Down.bmp");
    HDC spaceshipeLeft = txLoadImage ("Pictures/spaceshipe_Left.bmp");
    HDC spaceshipeRight = txLoadImage ("Pictures/spaceshipe_Right.bmp");
    HDC spaceshipe = spaceshipeUp;
    int xSpaceShip = 600;
    int ySpaceShip = 300;

    //������������� ������� "���������"
    HDC spaceman1Left = txLoadImage ("Pictures/spaceman1Left.bmp");
    HDC spaceman1Right = txLoadImage ("Pictures/spaceman1Right.bmp");
    HDC spaceman = spaceman1Left;
    int xSpaceman = 400;
    int ySpaceman = 300;
    int y0Spaceman = 550;

    //������������� ������� "���������2"
    HDC spaceman2Left = txLoadImage ("Pictures/spacemanLeft.bmp");
    HDC spaceman2Right = txLoadImage ("Pictures/spacemanRight.bmp");
    HDC spaceman2 = spaceman2Right;
    int xSpaceman2 = 100;
    int ySpaceman2 = 100;
    int vxSpaceman2 = 10;

    //������������� �������
    int xBullet;
    int yBullet;
    int vx = 5;
    bool Bullet_visible = false;

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_WHITE);
        txClear();

        //��������� ����
        txBitBlt (txDC(), xFon, yFon, 3600, 2400, background);

/*
        txTransparentBlt (txDC(), 0, 0, 150, 200, man, 0, 0, TX_WHITE);

        if(GetAsyncKeyState ('E'))
        {
            txTransparentBlt (txDC(), 0, 0, 150, 200, manRight, 150*n_kadr, 0, TX_WHITE);
            n_kadr++;
            if (n_kadr>=8) n_kadr = 0;
        }

        if(GetAsyncKeyState ('Q'))
        {
            txTransparentBlt (txDC(), 0, 0, 150, 200, manLeft, 150*n_kadr, 0, TX_WHITE);
            n_kadr++;
            if (n_kadr>=8) n_kadr = 0;
        }
*/

        //��������� ������������ �������
        if(spaceshipe == spaceshipeUp || spaceshipe == spaceshipeDown)
            txTransparentBlt (txDC(), xSpaceShip, ySpaceShip, 131, 200, spaceshipe, 0, 0, TX_BLACK);
        else if(spaceshipe == spaceshipeLeft || spaceshipe == spaceshipeRight)
            txTransparentBlt (txDC(), xSpaceShip, ySpaceShip, 200, 131, spaceshipe, 0, 0, TX_BLACK);

        //���������� ����������� �������
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


        txTransparentBlt (txDC(), xSpaceman, ySpaceman, 150, 212, spaceman, 0, 0, TX_BLACK);
        //������� ����������
        ySpaceman +=20;
        //������� "�����"
        if(ySpaceman > y0Spaceman - 212)
        {
            ySpaceman = y0Spaceman-212;
        }
        //������� ������
        if(GetAsyncKeyState (VK_SPACE))
        {
            ySpaceman -= 80;
        }

        if(GetAsyncKeyState (VK_RIGHT))
        {
            xSpaceman += 10;
            spaceman = spaceman1Right;
        }
        if(GetAsyncKeyState (VK_LEFT))
        {
            xSpaceman -= 10;
            spaceman = spaceman1Left;
        }
        if(Bullet_visible)
        {
            txCircle(xBullet, yBullet, 10);
            xBullet += vx;
        }
        if(GetAsyncKeyState (VK_CONTROL))
        {
            xBullet = xSpaceman+10;
            yBullet = ySpaceman+70;
            if(spaceman == spaceman1Right)
            {
                vx=vx;
            }

            if(spaceman == spaceman1Left)
            {
                vx=-vx;
            }

            Bullet_visible = true;
        }


        txTransparentBlt (txDC(), xSpaceman2, ySpaceman2, 147, 150, spaceman2,  0, 0, TX_BLACK);
        xSpaceman2 = xSpaceman2 + vxSpaceman2;
        if(xSpaceman2 > 800 - 147 || xSpaceman2 < 0)
        {
            vxSpaceman2 = - vxSpaceman2;
            if(vxSpaceman2 > 0)
            {
                spaceman2 = spaceman2Right;
            }
            else spaceman2 = spaceman2Left;
        }


        txEnd();
        txSleep(10);

    }

    txDeleteDC (background);
    txDeleteDC (spaceman);

txTextCursor (false);
txDisableAutoPause ();
return 0;
}

