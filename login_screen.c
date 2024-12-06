#include <stdio.h>

#include <termios.h>
#include <unistd.h>

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
    char save_pass[20];

    ch = getch();

    int i = 0;
    while (true)
    {
    if (ch == 13)
    {
        pass[i] = '\0';
        break;
    } 
    else
    {
        pass[i++] = ch;
        printf("*");
    }
    }

    printf("Your entered %s", pass);

    FILE * ptr;
    ptr = fopen("password.txt", "r");
    scanf(ptr, "%s", save_pass)
    return 0;
}


