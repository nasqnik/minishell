#include <stdio.h>

// Segmentation fault: 11
int main(void)
{
	// printf("lol\n");
	int *ptr = NULL;
	*ptr = 42;
	return (0);
}

// #include <signal.h>

// // Quit : 4
// int main(void)
// {
//     raise(SIGQUIT); // Send SIGQUIT to the process itself
//     return (0);
// }
