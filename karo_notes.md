**TO DO**
- Check builtin arguments, if there are possible commands or expansions inside them and if we need to handle them somehow.Echo!
- Check malloc and function call protection
- Check the forms of valid identifiers with export. Variables can only start with alphabets or '_'?
- Handle several redirections/files inside sigle command
- Correct error handling and make it uniform.
- Echo: is there a space after the last word to be shown

Notes
- leaks in parsing when echo has ""
- We get syntax error near unexpected newline token if we use >out instead of > out
- Segfault if using >out in the beginning eg. >out cat