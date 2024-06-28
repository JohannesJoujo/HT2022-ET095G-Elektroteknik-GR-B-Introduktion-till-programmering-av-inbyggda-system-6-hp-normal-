
/*
 * Johannes Joujo 4.2 Sub-task 2: Display bitmaps *
 */
#include "C12832.h"
#include "ST7565R.h"
#include "mbed.h"

/*
 * I used a tabell and wrote one or zero to draw the face
 * i later put the value into an online calculator to go
 * from binary -> hexadecimal.
 * This are the values i got for each row:
 */
static char jagj[] = {
    0xFF,
    0x81,
    0xB7,
    0xB7,
    0x9D,
    0xC3,
    0xFF,
    0x81,
    0xFF,
};
// The bitmap is 8X9
Bitmap jag = {8, 9, 1, jagj};
AnalogOut port(p18);
C12832 lcd(p5, p7, p6, p8, p11);
DigitalIn d(p12);
DigitalIn l(p13);
DigitalIn c(p14);
DigitalIn up(p15);
DigitalIn r(p16);
int x = 0;
int y = 0;
int main()
{

    while (1)
    {
        // In the begining x and y =0 and it will start at position (0,0).
        lcd.locate(x, y);
        lcd.cls();
        lcd.print_bm(jag, x, y);
        lcd.copy_to_lcd();

        /*The if statments are for if the joy stick has been pressed
         * up, down,left or right then the figure should move in that
         * direction. I have a 0,1 wait because it moves too fast either.
         */
        if (r == 1 && x <= 118)
        {
            x++;
            lcd.cls();
            lcd.locate(x, y);
            lcd.print_bm(jag, x, y);
            lcd.copy_to_lcd();
            wait(0.01);
        }

        if (up == 1 && y >= 1)
        {
            y--;
            x = x;
            lcd.cls();
            lcd.locate(x, y);
            lcd.print_bm(jag, x, y);
            lcd.copy_to_lcd();
            wait(0.01);
        }

        if (d == 1 && y <= 22)
        {
            y++;
            x = x;
            lcd.cls();
            lcd.locate(x, y);
            lcd.print_bm(jag, x, y);
            lcd.copy_to_lcd();
            wait(0.01);
        }

        if (l == 1 && x >= 1)
        {
            x--;
            lcd.cls();
            lcd.locate(x, y);
            lcd.print_bm(jag, x, y);
            lcd.copy_to_lcd();
            wait(0.01);
        }
    }
}
