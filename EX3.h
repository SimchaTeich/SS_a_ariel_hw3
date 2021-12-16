#ifndef _EX3_H_
#define _EX3_H_

#define WORD 30
#define TXT 1024

#define TRUE 1
#define FALSE 0
#define ERROR -1

/*
function gets from user a "word".
word - is an sequence of chars that stop
read from user when he press empty char.
empty char - ' ', '\n', '\t'.
output - the word.
*/
char* getWord();

/*
function gets from user a "text".
text - is an sequence of chars that stop
read from user when he press tilda.
tilda - '~'.
output - the text.
*/
char* getText();

/*
function find all the minimal sequens
in the text, with the same gimatria of word.
input - a word and some text.
output - array of thes sequences.
*/
char** getGematriaSequences(char* word, char* text);


/*
function find all the minimal sequens
in the text, with its hes the same atbash,
or reverse atbash.
input - a word and some text.
output - array of thes sequences.
*/
char** getAtbashOrReversedAtbashSeqIgnoreEmptyChars(char* word, char* text);

/*
function find all the anagram sequences
of a word in some text.
input - a word and some text
output - array of thes sequences.
*/
char** getAngramSeqIgnoreEmptyChars(char* word, char* text);


#endif