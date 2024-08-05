# Jaakko's Minishell Notes

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