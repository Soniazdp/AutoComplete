# Autocomplete Function

This project is a fast implementation of the autocomplete functionality. The task of the program is to quickly retrieve the top terms that match a query string, judging from the importance weight associated with each term.

For example, if the query string is "Eng", the matches might be "English", or "Engineering".


## Directory Structure

- `main.c`: uses the functions declared in h and c file to implement the complete autocomplete function, and it can be modified to test the c file.

- `autocomplete.c`:
    - `read_in_terms`: sorts the string in lexicographical orders
    - `highest_match`: returns the index in terms of the last term in lexicographic order that matches the query string
    - `lowest_match`: returns the index in terms of the first term in lexicographic order that matches the query string 

- `autocomplete.h`: declares C function and macro definitions to be shared between several source files
    - `term`: specifies the structure of 'term' for each string term

- `cities.txt` & `wiktionary.txt`: text files which contain a list of terms and their associated weights, which can be used to test the autocomplete function


## Compilation Intruction

Use the command to compile: `gcc -Wall autocomplete.c main.c`. Note that `autocomplete.h` must also be placed in the same folder as the C files. 


## Testing Example

The current `main.c` file uses `cities.txt` to test the autocomplete functions. In line 10 the `cities.txt` text file was read by the program and the list of city names and their weights are sorted. In line 17, the autocomplete function was called with a query string `'Tor', 'Toronto, Ontario, Canada'` should be returned if the program is running without error. 

Those lines can be modified to test different query strings or text files. The text file read by the program must be placed in the same folder as the C files. The text file must contain the list of terms in a format that is the same as that of `cities.txt`.


## Credit

The project was originally designed by Kevin Wayne, which was adapted and used as assignments in University of Toronto Engineering course ESC190 by Michael Guerzhoy, implemented by Bonnie Luo and Sonia Zeng in 2021 Winter.
