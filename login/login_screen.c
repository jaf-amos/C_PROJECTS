#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to replicate `getch` functionality
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);          // Save current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set new attributes
    ch = getchar();                          // Read a single character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old attributes
    return ch;
}


int main(void) {
    char ch;
    char pass[20];
    char saved_pass[20];
    int i = 0;
    int l;

    printf("Enter a password containing only alphanumeric characters!\n");
    start:
    while (i < 20)
    {
        ch = getch();
        if (ch == '\n' || ch == '\r')
        {
            pass[i] = '\0';
            break;
        } 
        else if ((ch > 64 && ch < 91) || (ch > 96 && ch < 123) || (ch > 47 && ch < 58) )
        {
            pass[i++] = ch;
            printf("*");
        }
        else
        {
            printf("You have entered an invalid character.\n");
            sleep(2);
            system("clear");
            goto start;
        }
    }

    //printf("Your entered %s\n", pass);

    FILE *ptr;
    ptr = fopen("password.txt", "r");

    if (ptr == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    if (fgets(saved_pass, sizeof(saved_pass), ptr) == NULL)
    {
        perror("Error reading file");
        fclose(ptr);
        return EXIT_FAILURE;
    }

    saved_pass[strcspn(saved_pass, "\n")] = '\0';

    fclose(ptr);

    l = strcmp (pass, saved_pass);
    if (l == 0)
    {
        printf("Login successful\n");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Incorrect password\n");
        sleep(1);
        system("clear");
    }
        
    return 0;
}


