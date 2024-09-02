TODO
- Check builtin functionality thoroughly after migration, especially cd and unset.
- Wrong error message for trying to cd into non-existing dir
- Redirections and file permissions or directories
- Redirection without command
- If there are multiple outfiles, they are created in order and until one fails (no permissions) or the last one is reached.
- Error messages
- Fix single memory leak in trim_n of expander_utils.c

FIXED
30.8. Moves env to using linked list
27.8. Tokenization should not separate linked and quoted arguments
27.8. rebuild parsing to handle connected arguments that should be placed in separate tokens
27.8. echo does not separate multiple agruments with a space
21.8. segfaults on empty input
20.8. echo "Hello' segfaults, gets into execute, should give syntax error
  