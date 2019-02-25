/*
 * vvargas_argtok.c
 *
 *  Created on: Feb 10, 2019
 *      Author: Vargas
 */


#include <stdio.h>
#include <stdlib.h>
#include "vvargas_argtok.h"



/*Function that will read a string from the char* variable passed to it (maybe from console)
It will then traverse the string as it adds to a counter that will return in the end.
*/
int string_length(char* str){
  int counter = 0;
  while(*str++){
    ++counter;
  }

  return counter;
}

/*Function that will take in a character and check if it is a valid one*/
char is_valid_character(char c){
  switch(c){
    case '\n':
    case '\t':
    case '\b':
    case '\a':
    case '\f':
    case '\r':
    case '\v':
    case '\\':
    case '\'':
    case '\"':
    case ' ':
    case '\0':
      return 0;
    default:
      return 1;
  }
}

/*Function that will search for the beginnning of next word, beginning the search at provided index*/
int find_word_start(char* line, int index){
  if(!is_valid_character(line[index])){ //first we check if we are in a valid character, if not we look for one
    while(!is_valid_character(line[index])){
      index++;
    }
  }else{//we are in a valid character, so we are the word beginning
    return index;
  }
  return index;
}

/*To search the end of the next word we can apply a search to the beginnning of it, then we just traverse it
until we reach the end
*/
int find_word_end(char* line, int index){
  int beg_of_word = find_word_start(line, index);
  //Now having the beginning we can get to the end
  while(is_valid_character(line[beg_of_word])){
    beg_of_word++;//when the loop is done this will be the end of the word
  }
  //here we went one over the end so we just return
  beg_of_word--;
  return beg_of_word;

}

/*Now we must count the words found in the line, we are assuming a relatively well built line. What we do is from the beginnning get the beginnning of each word, with our function, and just keep traversing with find word end and beg.*/
  int count_words(char* line){
    int counter = 0;//counts words
    int index = 0;
    short end = 0;
    short length = string_length(line);
    while(1){
      index = find_word_start(line, index);
      if(index>=length) break;
      counter ++;
      end = find_word_end(line, index);
      index = end+1;
    }
    return counter;
  }

/*Now we will define the function that tokenizes a string*/

char** argtok(char* line){
  short num_words = count_words(line);
  short word_leng =0;
  int index = 0;
  char** tokens = (char**) malloc((num_words+1)*sizeof(char*));//we allocate memory for the number of pointers needed

  for(short i=0;i<num_words;i++){ //we will calculate length of each string and allocate memory for each
    word_leng = (find_word_end(line, index) - find_word_start(line, index)) + 1;
    tokens[i] =(char *) malloc((word_leng + 1)*sizeof(char));//we allocate one extra for the NULL character
    index = find_word_start(line, index);
    for(short j = 0;j<word_leng;j++){
      tokens[i][j] = line[index+j];
    }
    index = (find_word_end(line, index) +1);
    tokens[i][index] = '\0';
  }
  tokens[num_words] = (char*) malloc(sizeof(char));
  tokens[num_words] = '\0';
  return tokens;
}


/*Now a function that takes a pointer pointer of chars (array of strings) and prints each string*/
void print_tokens(char** tokens){
  while(*tokens){
    printf("%s \n", *tokens);
    tokens++;
  }
}


void free_tokens(char** tokens){
  char** temp = tokens;
  while(*tokens){
    free(*tokens);
    tokens++;
  }
  free(temp);
}

