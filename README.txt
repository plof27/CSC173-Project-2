Group: Andrew Peck, Will Cunningham, Saralinda Schell

TO BUILD and TO RUN:

A. The folder CSC173-Project-2 contains a make file (Makefile). Build and run the program by:
>Navigating to the CSC173-Project-2 directory
>Running the command (assuming that the computer has make) >make
>Running the command >runMainLAW.exe

This code will first run and execute the expressions from test_expressions.txt and then accept expressions from the standard input until the EOF symbol is given.
The functions in main
    read_strings_from_cli(int),
    read_strings_from_file(filename,int),
    read_strings_from_file_for_table(filename, int),
    read_strings_from_cli_for_table(int),

can be flagged to allow evaluation of the parse tree. 0 prints the tree only, 1 prints and executes it.


NOTES:
More input strings can be added to the expression file if desired. Must be line delineated and have an empty line at the end
otherwise the last expression in the file will truncate by one character.
Depending on the console and length of the expression, the text can wrap around
and distort the printout.
