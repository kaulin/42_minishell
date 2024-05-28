# Jaakko's Minishell Notes

## 28.5.
- Using export in a pipe works as any pipe command: it's run in a different process, so the main process variables are not changed.

## 15.5.
- PWD stored in envp -> needs to be modified on directory changes