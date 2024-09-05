TODO

- Make error handler work
- File checker gives error for outfile that doesnt exist
- Check builtin functionality thoroughly after migration, especially cd and unset.
- Wrong error message for trying to cd into non-existing dir
- Redirections and file permissions or directories
- Redirection without command
- If there are multiple outfiles, they are created in order and until one fails (no permissions) or the last one is reached.
- Error messages
- Fix single memory leak in trim_n of expander_utils.c

FIXED
4.9. No space between tokens = failure
30.8. Moves env to using linked list
27.8. Tokenization should not separate linked and quoted arguments
rebuild parsing to handle connected arguments that should be placed in separate tokens
echo does not separate multiple agruments with a space
21.8. segfaults on empty input
20.8. echo "Hello' segfaults, gets into execute, should give syntax error
