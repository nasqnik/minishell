// [isatty] - <unistd.h>  
// [ttyname] - <unistd.h>  
// [ttyslot] - <unistd.h>  
// [ioctl] - <sys/ioctl.h>  
// [tcsetattr] - <termios.h>  
// [tcgetattr] - <termios.h>  

// TTY historically refers to Teletypewriter. In modern computing,
// a TTY generally refers to a terminal or console used for interactive input/output.

// [isatty]  "Is a TTY"  
//  Checks if a given file descriptor refers to a terminal 
// [ttyname] "TTY Name"
// Retrieves the name of the terminal device associated with a file descriptor
// [ttyslot] "TTY Slot"
//Gets the slot number of the terminal in the /etc/ttys file.
//A terminal slot of 0 means the current terminal is not listed
// in /etc/ttys, which is typical for pseudoterminals (like /dev/pts devices).
// [ioctl] "Input/Output Control"
// Performs low-level control operations on devices (including terminals).
// [tcsetattr] "Terminal Control Set Attributes".
//  Sets the attributes (settings) of a terminal, such as enabling/disabling echo or changing input modes.
// [tcgetattr] "Terminal Control Get Attributes".
// Retrieves the current attributes (settings) of a terminal.

#include <unistd.h> 
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <fcntl.h>

// [isatty]
// [ttyname]
// [ttyslot]

// int main(void)
// {
//     int fd1 = open("text.txt", O_RDONLY);
//     int fd2 = STDIN_FILENO;
//     if (isatty(fd2))
//         printf("it is a terminal.\n");
//     else 
//         printf("it_is_not\n");
//     printf("the name of the terminal is: %s\n", ttyname(fd2));
//     printf("the terminal slot is %d\n", ttyslot());
// }

// [ioctl]
// int main() {
//     struct winsize ws; // Structure to store window size

//     // Use ioctl to get the window size
//     // TIOCGWINSZ: A macro (defined in <sys/ioctl.h>) that requests the terminal's window size.
//     if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
//         perror("ioctl failed");
//         return 1;
//     }

//     // Print the number of rows and columns
//     printf("Rows: %d\n", ws.ws_row);
//     printf("Columns: %d\n", ws.ws_col);

//     return 0;
// }

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

// [tcsetattr] 

int main() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);      // Get current attributes
    term.c_lflag &= ~ECHO;              // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply changes

    printf("Enter a password: ");
    char password[100];
    fgets(password, sizeof(password), stdin);
    printf("\nPassword entered: %s\n", password);

    term.c_lflag |= ECHO;               // Re-enable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    return 0;
}
// [tcgetattr] 

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

// int main() {
//     struct termios term;
//     if (tcgetattr(STDIN_FILENO, &term) == 0) {
//         printf("Input flags: %x\n", term.c_iflag);
//         printf("Output flags: %x\n", term.c_oflag);
//         printf("Control flags: %x\n", term.c_cflag);
//         printf("Local flags: %x\n", term.c_lflag);
//     } else {
//         perror("tcgetattr failed");
//     }
//     return 0;
// }
