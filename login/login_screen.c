#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to replicate `getch` functionality
/** 
* getch() - writes keyboard input characters to buffer
* Descritpion: Custom implementation of getch() from conio.h
* Return: character ch.
*/
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

char *pass_func(void)
    {
    // Loop to get character from keyboard input. Hides input by displaying asterisk character
        char ch;
        int i = 0;
        char *pass;

        pass = malloc(20 * sizeof(char));
        /*if (pass == NULL)
        {
            return EXIT_FAILURE;
        }
        */
        while (1)
        {
            i = 0;
            //memset(pass, 0, sizeof(pass));

            while (i < 19)
            {
                ch = getch();
                if (ch == '\n' || ch == '\r')
                {
                    pass[i] = '\0';
                    break;
                } 
                else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') )
                {
                    pass[i++] = ch;
                    printf("*");
                }
                else
                {
                    pass[i++] = ch;
                    printf("*");
                }
            }

            if (i > 0 && pass[i] == '\0')
            {
                break;
            }
        }
        return pass;
    }

/**
 * main - entry point of the program
 * Return: 0
*/
int main(void) {
    int l;
    int pass_input = 0;
    char saved_pass[20];

    printf("Enter a password containing only alphanumeric characters!\n");


    // Retrieves password from file and saves it in saved_pass buffer

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

    // Remove the new line character at the end of the file
    saved_pass[strcspn(saved_pass, "\n")] = '\0';
    fclose(ptr);

    while (pass_input == 0)
    {
    // Compares the input password and the saved password
    l = strcmp (pass_func(), saved_pass);
    if (l == 0)
    {
        printf("\nLogin successful\n");
        pass_input = 1;
       // return EXIT_SUCCESS;
    }
    else
    {
        printf("\nIncorrect password\n");
        sleep(1);
        printf("\033[H\033[J");
    }
    }
    return 0;
}


