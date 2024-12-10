#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h> 
// int main(void) {
//     char *input = readline("Enter your name: ");
//     if (input && *input) {
//         add_history(input);
//         printf("Hello, %s!\n", input);
//     } else {
//         printf("No input provided.\n");
//     }
//     free(input);
//     return 0;
// }

void interactive_session() {
    char *input;
    
    // Example of a loop to continuously read inputs
    while (1) {
        // Use readline to get input from the user
        input = readline("Enter a command (type 'exit' to quit): ");

        if (!input) {
            // Handle EOF (Ctrl+D)
            printf("\nExiting...\n");
            break;
        }

        if (*input) {
            add_history(input);  // Add the input to the history
        }

        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Simulate replacing the line in the input (using rl_replace_line)
        rl_replace_line("Processing your command...", 1);
        rl_on_new_line();  // Tell readline we're on a new line
        rl_redisplay();    // Redisplay the updated line

        printf("\nYou entered: %s\n", input);  // Print the input

        free(input);  // Free the input string memory
    }

    rl_clear_history();  // Clear all stored history
}

int main(void) {
    printf("Interactive Session Started!\n");
    interactive_session();
    printf("Session Ended.\n");
    return 0;
}
