valgrind --trace-children=yes -s --suppressions=_notes/ignore_readline_leaks.txt  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

valgrind --trace-children=yes -s --suppressions=_notes/ignore_readline_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell 2> out


//  hi i "-am" -me -lol"$PWD"$USER'hi'<1>2>>ko || duhvsui
|| ((char *)(cursor->next->data))[0] == '-')

|| ((cursor->next->type >= D_QUOTES && cursor->next->type <= WORD) ((char *)(cursor->next->data))[0] == '-'))

export VAR1="hello" VAR2="world" && echo "This is a test for $VAR1 and $VAR2" | grep "test" > output.txt

export VAR1="hello" VAR2="world" && echo "This is a test for $VAR1 and $VAR2" | grep "test"'-l' > output.txt
        # if (cursor && !((cursor->type >= REDIRECT_IN && cursor->type <= REDIRECT_APPEND)))
cat<<EOF

tar -czvf archive.tar.gz file1 file2&&echo"Done" ||archive, file, file?


work fine
mini shell is fun'-l'|skasfk <<ko>>$PWD psoaf

minishell$ mini shell is fun'-l'|skasfk <<ko>>$PWD "ps"o'af' ((((((essgsd))))))

AFTER EXPANSIONS
string :   #mini#  
          type: :COMMAND
string :   # #  
          type: :SPACE
string :   #shell is fun#  
          type: :ARGUMENT
string :   #-l#  
          type: :FLAG
string :   #|#  
          type: :PIPE
string :   #skasfk#  
          type: :COMMAND
string :   # #  
          type: :SPACE
string :   #<<#  
          type: :HEREDOC (<<)
string :   #ko#  
          type: :DELIMITER
string :   #>>#  
          type: :REDIRECT_APPEND (>>)
string :   #/home/vscode/src#  
          type: :ENV_VAR
string :   # #  
          type: :SPACE
string :   #psoaf essgsd#  
          type: :ARGUMENT