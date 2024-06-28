/*
 * Johannes joujo Exercise 6: File Management
 */

#include "mbed.h"
#include "LM75B.h"

LM75B tmp(p28, p27);
LocalFileSystem local("local");

DigitalIn c(p14);

int main()
{
    // used in the for loop to make a new line every fifth loop
    int count = 0;
    while (1)
    {

        if (c == 1)
        {
            /* opening the file in append mode so that the information stored
             *  in the file wont dissapear every time a new value is written to the file
             */
            FILE *File1 = fopen("/local/datafile.txt", "a");
            // putting in the temperature values into the file
            for (int i = 0; i < 5; i++)
            {
                count++;
                if (count == 5)
                {
                    fprintf(File1, "%0.1f,\n", tmp.read());
                    // resetting the count
                    count = 0;
                    // waiting 0.5s to get a new temperatur reading
                    wait(0.5);
                }
                else
                {
                    fprintf(File1, "%0.1f, ", tmp.read());
                    wait(0.5);
                }
            }
            fclose(File1);
            int value = 0;
            // Printing last 5 values from datafile.txt
            FILE *File = fopen("/local/datafile.txt", "r");
            fseek(File, -30, SEEK_END);
            // from where the pointer is to the end of file print
            while (!feof(File))
            {
                value = fgetc(File);
                printf("%c", value);
            }
            fclose(File);
        }
    }
}
