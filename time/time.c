/**
* Description: Program displays a running 24 hour clock in the terminal.
* Date - 07/12/2024
* Author - Amos Araunah
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Clear screen using preprocessor directive
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

/**
 * main - program entry point
 * Return: 0
 */

int main(void)
{
    int seconds, minutes, hours;
    hours = minutes = seconds = 0;

    while (1)
    {
        system(CLEAR_SCREEN);

        //print time in HH : MM : SS
        printf("%02d : %02d : %02d", hours, minutes, seconds);

        fflush(stdout);
        seconds++;

        //increment the time
        if (seconds == 60)
        {
            minutes += 1;
            seconds = 0;
        }

        if (minutes == 60)
        {
            hours += 1;
            minutes = 0;
        }

        if (hours == 24)
        {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }

        sleep(1);
    }
    return (0);
}