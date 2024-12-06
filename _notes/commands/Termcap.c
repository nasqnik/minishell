
// ## Terminal Capabilities (Termcap) Functions:
// [tgetent] - <termcap.h>  
// [tgetflag] - <termcap.h>  
// [tgetnum] - <termcap.h>  
// [tgetstr] - <termcap.h>  
// [tgoto] - <termcap.h>  
// [tputs] - <termcap.h>  

// #include <termcap.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     char termbuf[2048];  // Buffer for terminal description
//     char buffer[1024];   // Buffer for termcap strings
//     char *area = buffer;

//     // Initialize termcap for the terminal type
//     if (tgetent(termbuf, getenv("TERM")) != 1) {
//         fprintf(stderr, "Error initializing termcap.\n");
//         return 1;
//     }

//     // Example terminal capabilities
//     printf("tgetflag (am): %d\n", tgetflag("am"));        // Automatic margins
//     printf("tgetnum (co): %d\n", tgetnum("co"));          // Number of columns
//     printf("tgetstr (cl): %s\n", tgetstr("cl", &area));   // Clear screen string

//     // Move the cursor (use with caution)
//     char *cm = tgetstr("cm", &area);
//     if (cm) {
//         printf("Cursor movement string: %s\n", cm);
//         printf("tgoto result: %s\n", tgoto(cm, 10, 5));  // Move cursor to column 10, row 5
//     }

//     return 0;
// }
