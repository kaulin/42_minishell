TODO
- ctrl + c in heredoc should just cancel and return prompt (not running command)
- ctrl + c while process is running (sleep, for example) returns error code 130 if that was the last command in pipeline
- If started with no environment, problems with cd, as $PWD and $OLDPWD dont exist. same if these are unset. Unsetting $OLDPWD results in really big issues at the moment. Running getcwd before any commands are run could be a solution.
- removing dir above current dir results in getcwd failure when trying to move up (can be argued that this is good enough, cd with full path works)

FIXED
- check var_list alphabetic pointers, sometimes list gets broken
- order of operations: > a < a < b should give error for b not exisiting, since it creates a before trying to read from it
- ls | << A cat = pipe output is read into heredoc  (reuse of pipes?)
- heredoc without command still gives invalid read (goes into do_cmd)
- unset PATH does not really unset the paths, though the env is removed
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
- echo "Hello' segfaults, gets into execute, should give syntax e-z 