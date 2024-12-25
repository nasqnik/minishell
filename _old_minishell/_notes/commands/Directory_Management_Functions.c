// ## Directory Management Functions:

// [getcwd]* - <unistd.h>  // Gets the current working directory.
// char *getcwd(char *buf, size_t size);
// [chdir]* - <unistd.h>  // Changes the current working directory
// int chdir(const char *path);
// [opendir] - <dirent.h>  // Opens a directory stream for reading
// DIR *opendir(const char *name);
// [readdir] - <dirent.h>  // Reads the next entry in a directory stream
// struct dirent *readdir(DIR *dirp);
// [closedir] - <dirent.h>  // Closes an open directory stream
// int closedir(DIR *dirp);

// Think of a directory as a list of files stored on your device:
// opendir: Opens the list and prepares a "bookmark" (directory stream) at the beginning of the list.
// readdir: Moves the bookmark to the next entry and retrieves the file's name.
// closedir: Closes the list and discards the bookmark.
// In this analogy:

// The DIR * is the bookmark or iterator.
// The list of files is stored on the disk.

#include <unistd.h>
#include <dirent.h> // directory entries
#include <stdio.h>

int main(void)
{
    printf("\nUnderstanding <<Directory Management Functions>>\n\n");
    printf("first function get the current working directory [getcwd] \nlike that: \n");
    char buf[1024];
    getcwd(buf, sizeof(buf));
    printf("buffer from getcwd is : %s\n", buf);
    printf("now we will change the directory with [chdir] then print it with [getcwd]\n");
    if (chdir("/tmp") == 0) {
        printf("Directory changed to /tmp\n");
    }
    getcwd(buf, sizeof(buf));
    printf("buffer from getcwd is : %s\n", buf);
    DIR *dir = opendir("/tmp");
    if (dir != NULL) {
        printf("Directory opened successfully.\n");
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Entry: %s\n", entry->d_name);
        // printf("lol : %c\n", entry->d_name[0]);
    }
    closedir(dir);
}