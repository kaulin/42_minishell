TODO
- unset PATH does not really unset the paths, though the env is removed
- removing dir above current dir results in getcwd failure when trying to move up

FIXED
- var_list still small leak (didnt free key if var existed and input had no new value)
- some multiple unsets result in segfault due to remove from alpha function
- heredoc no cmd = segfault (check_builtin had no check for no cmds)
- If there are multiple outfiles, they are created in order and until one fails (no permissions) or the last one is reached.
- Redirection without command
- Redirections and file permissions or directories
- Wrong error message for trying to cd into non-existing dir
- File checker gives error for outfile that doesnt exist
- move fail functionality into error handler (fixing some error messages)
- Make error handler work
- Fix single memory leak in trim_n of expander_utils.c
- No space between tokens = failure
- Moves env to using linked list
- Tokenization should not separate linked and quoted arguments
- Rebuild parsing to handle connected arguments that should be placed in separate tokens
- echo does not separate multiple agruments with a space
- segfaults on empty input
- echo "Hello' segfaults, gets into execute, should give syntax e-