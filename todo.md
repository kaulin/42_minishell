TODO
- heredoc no cmd = segfault (might be something to do with dups, as there is some bubble gum)
- unset PATH does not really unset the paths, though the env is removed
- some multiple unsets result in segfault due to remove from alpha function
- removing dir above current dir results in getcwd failure when trying to move up

FIXED
- If there are multiple outfiles, they are created in order and until one fails (no permissions) or the last one is reached.
- Redirection without command
- Redirections and file permissions or directories
- Wrong error message for trying to cd into non-existing dir
- File checker gives error for outfile that doesnt exist
- move fail functionality into error handler (fixing some error messages)
5.9. Make error handler work
4.9. Fix single memory leak in trim_n of expander_utils.c
4.9. No space between tokens = failure
30.8. Moves env to using linked list
27.8. Tokenization should not separate linked and quoted arguments
27.8. Rebuild parsing to handle connected arguments that should be placed in separate tokens
27.8. echo does not separate multiple agruments with a space
21.8. segfaults on empty input
20.8. echo "Hello' segfaults, gets into execute, should give syntax error
