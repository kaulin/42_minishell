# Jaakko's Minishell Notes

## 6.8.
- Continuing on bash behavior depending on pipe character separation:
	1. cmd1 || cmd2 - executes cmd1 and cmd2 and redirects successfully, ie || = |
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