valgrind --trace-children=yes -s --suppressions=_notes/ignore_readline_leaks.txt  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

valgrind --trace-children=yes -s --suppressions=_notes/ignore_readline_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell 2> out

lsof -p <PID>

pgrep sminishell

echo "Hello, Minishell!" | grep Minishell [done] [done]
echo "This is a test" > output.txt        [done] [done]
echo "Appending line" >> output.txt       [done] [done]
grep test < output.txt                    [done] [done]
cat << EOF                                [done] [done]
This is a heredoc example.
EOF
ls -l | grep minishell                    [done] [done]
echo $PATH                                [done] [done]
echo "Error logging" | tee error.log > output.log [done]
echo "The current date is: $(date)"        [done] [done]
echo "The current date is: " $(date)       [so_that_will_not_work_because_the_bracket_is_a_different_thing_now]
ls *.c                                     [we_need_to_make_wildcard_**_or_split_and_save_it_as_**]
ls -l | wc -l                              [done] [done]
mkdir test_dir && cd test_dir              [we_need_to_make_the_logic_for_&&]
ls nonexistentfile 2> error.txt            [not_required]
sleep 5 | echo hi                          [done]

cat << EOF > file3.txt
This is a heredoc example with multiple lines.
Minishell testing!
EOF
# Creates 'file3.txt' with the content of the heredoc.

cat file3.txt | tee file4.txt >> file5.txt
# Duplicates the content of 'file3.txt' into 'file4.txt' and appends it to 'file5.txt'.

ls -l > dirlist.txt 2> error.log
# Writes directory listing to 'dirlist.txt' and errors (if any) to 'error.log'.

cat dirlist.txt error.log > combined.txt
# Combines the content of 'dirlist.txt' and 'error.log' into 'combined.txt'.

grep Minishell < file3.txt | tee result.txt >> final_result.txt
# Searches for "Minishell" in 'file3.txt', saves the result in 'result.txt', and appends it to 'final_result.txt'.

echo "Appending this to multiple files" | tee -a file1.txt file2.txt file4.txt
# Appends "Appending this to multiple files" to 'file1.txt', 'file2.txt', and 'file4.txt'.

cat file3.txt | grep example | tee output1.txt > output2.txt
# Searches for "example" in 'file3.txt', saves it to 'output1.txt', and overwrites 'output2.txt' with the same content.

ls nonexistentfile > /dev/null 2>> errors.log
# Discards standard output and appends the error "file not found" to 'errors.log'.

echo "Final command test" > final.txt && cat final.txt >> all_results.txt
# Creates 'final.txt' with "Final command test" and appends its content to 'all_results.txt'.



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

          echo hello > file1 | cat file1 && echo done

# echo > out -n "Hello World" << ls | meow > sleep.txt // fix this one itv should strat from the bgining if it found a pipe


# VALID COMMANDS:

# 1. Runs `echo` and `ls` in a subshell, pipes the output to `grep`, and saves it to `output.txt`.
(echo "Hello" && ls) | grep "H" > output.txt

# 2. Tries to create `mydir`. If it fails, outputs "Failed". Then appends "Retry" to `log.txt`.
mkdir mydir || echo "Failed" && echo "Retry" >> log.txt

# 3. Reads from `input.txt`, pipes "Data" through `cat`, and appends it to `output.txt`.
echo "Data" | cat < input.txt >> output.txt

# 4. Uses a here document as input and pipes its output to `grep`.
cat << EOF | grep "example"
This is an example
line of text
EOF

# 5. Writes "Start" to `file.txt`, lists a nonexistent file, and falls back to echo "Fallback".
echo "Start" > file.txt && (ls nonexistent || echo "Fallback")

# INVALID COMMANDS:

# 6. Error: Parentheses are not used this way; they must wrap commands as a subshell.
echo "Hi" (ls)

# 7. Error: Missing the `EOF` terminator for the here document.
cat << EOF | grep "missing"
This line is incomplete

# 8. Error: A pipe cannot start a command; it must connect commands.
| echo "Pipe first"

# 9. Error: `>|` is not valid in standard Bash syntax; it's a typo or unsupported syntax.
ls >| file.txt

# 10. Error: `&&` and `||` cannot be used together without a command in between.
echo "test" && || echo "error"

((echo "This is the outer subshell") && (echo "This is the inner subshell"))


# Command 1: Simple logical grouping with priorities
(echo "Outer" && (echo "Inner success" || echo "Inner failure")) && echo "Final success"

# Command 2: Nested failure case with priorities
(echo "Outer success" || (echo "Inner success" && echo "This won't run")) || echo "Final failure"

# Command 3: Combining priorities for mixed cases
(echo "Start" && (false || echo "Inner condition met")) && echo "End reached"

# Command 4: A failing outer subshell that skips the inner
(false && (echo "Inner success" || echo "Inner fallback")) || echo "Outer failure"

# Command 5: Complex chaining with multiple priorities
((echo "First" && echo "Second") || echo "Skipped") && (echo "Final success" || echo "Final failure")

cat << 1 > 2 | cat 2
> $PWD
> "PWD"
> "$PWD"
> '$PWD'