**Builtins**
- At what point do we check if we are dealing with a builtin and if there is a right amount of arguments for them?
- Can we use printf or would e.g. ft_putstring_fd() be better?


**TO DO**
- Check builtin arguments, if there are possible commands or expansions inside them and if we need to handle them somehow.Echo!
- Correct EXIT_SUCCESS/FAILURE
- Check malloc and function call protection
- Check the forms of valid identifiers with export. Variables can only start with alphabets or '_'?
- Handle several redirections/files inside sigle command
- Change check_builtin function call placement. In parent ff we have only one command and it is a builtin we do not need to fork.