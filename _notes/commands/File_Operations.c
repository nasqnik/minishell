// ## File Operations:
// ~~done~~.[access]* - <unistd.h>  
// ~~done~~.[open] - <fcntl.h>  
// ~~done~~.[read]* - <unistd.h>  
// ~~done~~.[close] - <unistd.h>  
// ~~done~~[unlink] - <unistd.h>  
// [stat] - <sys/stat.h>  
// [lstat]* - <sys/stat.h>  
// [fstat] - <sys/stat.h> 

// [stat] - <sys/stat.h>
// Purpose: Retrieves information about a file (e.g., size, permissions, timestamps).
// int stat(const char *pathname, struct stat *buf);

// [lstat]* - <sys/stat.h> 
// Purpose: Similar to stat, but if the path is a symbolic link,
//  it retrieves information about the link itself, not the target.
// int lstat(const char *pathname, struct stat *buf);

// [fstat] - <sys/stat.h> 
// Purpose: Retrieves information about an open file descriptor, not a pathname.
// int fstat(int fd, struct stat *buf);

// struct stat {
//     dev_t     st_dev;     // ID of the device containing the file
//     ino_t     st_ino;     // Inode number
//     mode_t    st_mode;    // File type and permissions
//     nlink_t   st_nlink;   // Number of hard links
//     uid_t     st_uid;     // User ID of the file owner
//     gid_t     st_gid;     // Group ID of the file owner
//     dev_t     st_rdev;    // Device ID (if the file is a device)
//     off_t     st_size;    // Size of the file in bytes
//     time_t    st_atime;   // Time of last access
//     time_t    st_mtime;   // Time of last modification
//     time_t    st_ctime;   // Time of last status change
//     blksize_t st_blksize; // Preferred block size for I/O
//     blkcnt_t  st_blocks;  // Number of 512-byte blocks allocated
// };


#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// int main(void)
// {
//     int fd = open("text.txt", O_RDONLY);
//     if (fd <= 2)
//         return (1);
//     struct stat fileStat;
//     if (fstat(fd, &fileStat) == 0) {
//         printf("File size: %lld bytes\n", fileStat.st_size);
//         printf("File type and permissions %o \n", fileStat.st_mode & 0777);
//     }
    
// }

// int main(void)
// {
//     struct stat fileStat;
//     if (stat("/Users/meid/Desktop/mini_shell/text.txt", &fileStat) == 0) {
//         printf("File size: %lld bytes\n", fileStat.st_size);
//         printf("File type and permissions %o \n", fileStat.st_mode & 0777);
//     }
    
// }