/*
 * vvargas_argtok.h
 *
 *  Created on: Feb 10, 2019
 *      Author: Vargas
 */

#ifndef VVARGAS_ARGTOK_H_
#define VVARGAS_ARGTOK_H_


/* Count the number of characters in the string argument. */
int string_length(char*);

/* Evaluate if the character c is an acceptable character for
   a token (e.g. '0' is acceptable but '\t' is not.
   Returns 0 if not, 1 if yes. */
char is_valid_character(char c);

/* Find the starting index for the next word.
   char* str - the string to search.
   int pos - the index to start searching. */
int find_word_start(char*, int);

/* Find the end index for the next word.
   char* str - the string to search.
   int pos - the index to start searching. */
int find_word_end(char*, int);

/* Count the number of words in the string argument. */
int count_words(char*);

/* Print all tokens. */
void print_tokens(char**);

/* Free all tokens and the array containing the tokens. */
void free_tokens(char**);

/* Tokenizes the string argument into an array of tokens.
   For example, "hello world string" would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" */
char** argtok(char*);





#endif /* VVARGAS_ARGTOK_H_ */
