readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
printf, malloc, free, write, access, open, read, close
fork, wait, waitpid, wait3, wait4
signal, sigaction, sigemptyset, sigaddset, kill, exit
getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe
opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot
ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## Readline Functions:  [new_understanding_but_need_more]
[Use the -lreadline flag to compile any program using those functions, as the compiler needs to link with the readline library.]

.[readline] - <readline/readline.h>  
[rl_clear_history] - <readline/readline.h>  
[rl_on_new_line] - <readline/readline.h>  
[rl_replace_line] - <readline/readline.h>  
[rl_redisplay] - <readline/readline.h>  
.[add_history] - <readline/readline.h>  

## Standard I/O Functions: 
~~done~~.[printf] - <stdio.h>  
~~done~~.[write]* - <unistd.h>  

## Memory Management Functions:
~~done~~.[malloc]* - <stdlib.h>  
~~done~~.[free]* - <stdlib.h>  

## File Operations:  [new_understanding]
~~done~~.[access]* - <unistd.h>  
~~done~~.[open] - <fcntl.h>  
~~done~~.[read]* - <unistd.h>  
~~done~~.[close] - <unistd.h>  
~~done~~[unlink] - <unistd.h>  
[stat] - <sys/stat.h>  
[lstat]* - <sys/stat.h>  
[fstat] - <sys/stat.h>  

## Process Control Functions:
~~done~~.[fork]* - <unistd.h>  
~~done~~.[wait]* - <sys/wait.h>  
~~done~~[waitpid] - <sys/wait.h>  
[wait3] - <sys/wait.h>  
[wait4] - <sys/wait.h>  

## Signal Handling Functions: [new_understanding_but_need_more]
[signal]* - <signal.h>  
[sigaction] - <signal.h>  
[sigemptyset] - <signal.h>  
[sigaddset] - <signal.h>  
[kill] - <signal.h>  

## Program Termination Functions:
~~done~~.[exit]* - <stdlib.h>  

## Directory Management Functions:  [new_understanding]
[getcwd]* - <unistd.h>  
[chdir]* - <unistd.h>  
[opendir] - <dirent.h>  
[readdir] - <dirent.h>  
[closedir] - <dirent.h>  

## Terminal Handling Functions: [new_understanding_but_need_more]
[isatty] - <unistd.h>  
[ttyname] - <unistd.h>  
[ttyslot] - <unistd.h>  
[ioctl] - <sys/ioctl.h>  
[tcsetattr] - <termios.h>  important for the password
[tcgetattr] - <termios.h>  

## Error Handling Functions:
~~done~~[strerror] - <string.h>  
~~done~~[perror] - <stdio.h>  

## Environment and Path Functions:
[getenv] - <stdlib.h>  

## Terminal Capabilities (Termcap) Functions:  [I_did_not_know_how_to_make_it_work]
[tgetent] - <termcap.h>  
[tgetflag] - <termcap.h>  
[tgetnum] - <termcap.h>  
[tgetstr] - <termcap.h>  
[tgoto] - <termcap.h>  
[tputs] - <termcap.h>  

## File Descriptor Duplication Functions:
~~done~~[dup] - <unistd.h>  
~~done~~.[dup2] - <unistd.h>  

## Piping Functions:
~~done~~.[pipe] - <unistd.h>  

## Execution Functions:
~~done~~.[execve]* - <unistd.h>  
