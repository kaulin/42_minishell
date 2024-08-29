TODO
- Redirections and file permissions or directories
- Expansion of env variables in heredoc (maybe not necessary, according to many)
- Redirection without command
- If there are multiple outfiles, they are created in order and until one fails (no permissions) or the last one is reached.
- Moves env to using linked list
- Free problem in clean array when command not found
- Extra free in cleanup
- Signals
- Error messages
- Fix memory leak in expander.c

FIXED
27.8. Tokenization should not separate linked and quoted arguments
27.8. rebuild parsing to handle connected arguments that should be placed in separate tokens
27.8. echo does not separate multiple agruments with a space
21.8. segfaults on empty input
20.8. echo "Hello' segfaults, gets into execute, should give syntax error
 