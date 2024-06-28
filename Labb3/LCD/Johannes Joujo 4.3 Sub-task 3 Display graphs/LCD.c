/*
 * Johannes Joujo 4.3 Sub-task 3: Display graphs *
 */
#include "C12832.h"
#include "mbed.h"
#include "LM75B.h"

C12832 lcd(p5, p7, p6, p8, p11);
LM75B tmp(p28, p27);

int main()
{
    float board_temp;
    float x;

    while (1)
    {
        // Vertical-axis.
        lcd.line(20, 0, 20, 31, 1);
        // Horisontal-axis.
        lcd.line(112, 0, 112, 31, 1);

        // prints 40 C and adds few black pixels next to the left vertical line.
        lcd.locate(0, 0);
        lcd.printf("40C");
        lcd.pixel(19, 0, 1);
        lcd.pixel(18, 0, 1);
        lcd.pixel(21, 0, 1);
        lcd.pixel(22, 0, 1);

        // prints 8 C and adds few black pixels next to the left vertical line.
        lcd.locate(3, 22);
        lcd.printf("8C");
        lcd.pixel(19, 31, 1);
        lcd.pixel(18, 31, 1);
        lcd.pixel(21, 31, 1);
        lcd.pixel(22, 31, 1);

        // prints 24 C and adds few black pixels next to the left vertical line.
        lcd.locate(0, 10);
        lcd.printf("24C");
        lcd.pixel(19, 15, 1);
        lcd.pixel(18, 15, 1);
        lcd.pixel(21, 15, 1);
        lcd.pixel(22, 15, 1);

        // calculate the time in seconds.
        double clk = 0;

        for (int i = 21; i < 111; i++)
        {
            // prints the current temperature to the board.
            lcd.locate(64, 0);
            lcd.printf("%0.2f", board_temp);
            board_temp = tmp.read();
            // calculate the temperature.
            x = 32 - (board_temp - 8);
            // printing the temperature as a pixel to the screen.
            lcd.pixel(i, x, 1);
            lcd.copy_to_lcd();
            clk += 0.1;
            // prints the total time.
            lcd.locate(113, 10);
            lcd.printf("9.1");
            lcd.locate(113, 20);
            lcd.printf("s");
            lcd.locate(64, 23);
            lcd.printf("%0.1f s", clk);
            // lcd.printf("s");
            wait(0.1);
        }
        lcd.cls();
    }
}
