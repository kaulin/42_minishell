**Builtins**
- Redirection in builtins
- Can we use printf or would e.g. ft_putstring_fd() be better?
- 


**TO DO**
- Check builtin arguments, if there are possible commands or expansions inside them and if we need to handle them somehow.Echo!
- Correct EXIT_SUCCESS/FAILURE
- Check malloc and function call protection
- Check the forms of valid identifiers with export. Variables can only start with alphabets or '_'?
- Handle several redirections/files inside sigle command
- Handle heredoc by making another pipe where the input is written and where it can be read from
- Check if PATH_MAX still works in linux as it should
- Make error handling uniform using fail() everywhere