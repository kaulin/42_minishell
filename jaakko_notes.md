# Jaakko's Minishell Notes

## 21.8.
- TODO: If there are multiple outfiles, they are created in order and until one fails (no permissions) or the last one is reached.
- FIXED segfaults on empty input

## 20.8.
- FIXED echo "Hello' segfaults, gets into execute, should give syntax error

## 19.8.
- Basic functionality established!!!
- quit signaling works with shells within shells
- cd:ing into a deleted directory from a subdirectory segfaults (not all the time???)
- Redirection needs work
- Command arguments are parsed together without separating spaces, need to rebuild tokenizing anyway

## 13.8.
- Problem in tokenization: redirection tokens need to be handled even when not separated from other tokens by whitespace.

## 9.8.
- How to handle removal of the current working directory or the parent directory of current working directory. Bash:
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4$ rm -rf ~/42/minishell/local/1/2
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4$ pwd
/home/jajuntti/42/minishell/local/1/2/3/4
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4/.$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4/./.$ cd .
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4/././.$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4/./././..$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
jajuntti@c3r2p7:~/42/minishell/local/1/2/3/4/./././../..$ cd ..
jajuntti@c3r2p7:~/42/minishell/local/1$ echo $OLDPWD
/home/jajuntti/42/minishell/local/1/2/3/4/./././../..
Explained: moving to "current directory" . adds /. to $PWD and gives error message. This can be repeated indefinitely. Moving to "parent directory" .. adds /.. to the $PWD and gives error messages, but can be repeated n times, where n is the level of depth one was initially from the parent of the directory that was removed. In the above case, we started at lvl 4 and lvl 2 was removed. 4-2=2, so we are able to cd "up" .. twice, before we are returned to the actual existing directory. If lvl 1 is removed after removing lvl 2, .. can be repeated one more time, before we are returned to the still existing /local. Creating new versions of the original file structure after removing parts does not affect this. Only removing current directory (4-4=0) and using cd .. returns you to 3, as expected.

## 7.8.
- Bashing my head against bash continues:
<< EOF"" cat
> $NAME
> EOF
$NAME

## 6.8.
- Continuing on bash behavior depending on pipe character separation:
	1. cmd1 || cmd2 - executes cmd1, no error messages and exit code 0. cmd1 not piped. !!! || is interpreted as OR, needs not be addressed
	2. cmd1 | | cmd2 - gives bash: syntax error near unexpected token `|'
	3. cmd1 ||| cmd2 - gives bash: syntax error near unexpected token `|'
	4. cmd1 |||| cmd2 - gives bash: syntax error near unexpected token `||' (same with further | characters)
	5. cmd1 |""| cmd2 - executes cmd1 and cmd2 but cmd1 output is not piped to cmd2 and gives Command not found error (same with other non whitespace non command strigns)

## 5.8.
- Handling input error messages as opposed to program error messages
- Error messages for unclosed quotes, input starting or ending with a pipe character, or pipe chacters following one another
- Handling variable expansion in heredoc

## 5.6.
- If a running process in minishell is interrupted with ctrl + c to return the prompt to the user, ctrl + d signla does not work any more.
- Added macros for ERROR and SUCCESS to minishell.h, use these instead of EXIT_SUC/FAIL when just returning 1 or 0, not really exiting the program.
- Parser expander stuck in infinite loop, trying to hunt it down...

## 28.5.
- Using export in a pipe works as any pipe command: it's run in a different process, so the main process variables are not changed.

## 15.5.
- PWD stored in envp -> needs to be modified on directory changes