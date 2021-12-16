#include "EX3.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>

int getGematriaStr(char* word);
int getGematria(char c);
char* getAtbash(char* word);
char* getReverse(char* word);
void deleteCharByIndex(char* str, int i);
long int findPlace(char* str, char c);

char* getWord()
{
    char tempWord[WORD] = {'\0'};
    char c = '\0';
    int i = 0;

    // take the word until an empty char
    while(i < (WORD -1))
    {
        c = getchar();
        if (c == '\n' || c == '\r' || c == ' '){break;}
        tempWord[i++] = c;
    }

    // allocate space for word
    char* word = (char*)calloc(sizeof(char), strlen(tempWord) + 1); // +1 for \0
    if(word == NULL) {return NULL;}
    
    // move word from user from local to dynamic memory. 
    strcpy(word, tempWord);
    
    return word;
}

char* getText()
{
    char tempText[TXT] = {'\0'};
    char c = '\0';
    int i = 0;

    // take the text until a tilda '~'.
    while(i < (TXT -1))
    {
        c = getchar();
        if (c == '~'){break;}
        tempText[i++] = c;
    }

    // allocate space for word
    char* text = (char*)calloc(sizeof(char), strlen(tempText) + 1); // +1 for \0
    if(text == NULL) {return NULL;}
    
    // move text from user from local to dynamic memory. 
    strcpy(text, tempText);
    
    return text;
}

char** getGematriaSequences(char* word, char* text)
{
    long int textSize = strlen(text);

    // maximum sequenses is when every char at text is
    // the same, and accurence with it gematria to word.
    // for example: word is 'bee', text is: 'lllll...l'
    // ("l" * textSize)
    char** sequenses = (char**)malloc(textSize * sizeof(char*));
    int seqCount = 0;

    // get gematry of word.
    int gimatria = getGematriaStr(word);
    int i = 0;
    int j = 0;

    while(i < textSize)
    {
        char* seq = (char*)calloc(sizeof(char), WORD);
        int count = 0;

        // ignode unalphabet chars.
        while(!isalpha(text[i]) && i < textSize){i++;}

        j = i;
        while (j < textSize)
        {
            if(isalpha(text[j]))
            {
                if(count + getGematria(text[j]) < gimatria)
                {
                    seq[strlen(seq)] = text[j]; // add the char to string
                    count += getGematria(text[j]); // encrease the counter
                    j++;
                }
                else if(count + getGematria(text[j]) > gimatria)
                {
                    free(seq);
                    break;
                }
                else
                {
                    seq[strlen(seq)] = text[j]; // add the char to string
                    sequenses[seqCount++] = seq;
                    break;
                }
            }
            else
            {
                seq[strlen(seq)] = text[j]; // add the char to string
                j++; // go to next char 
            }
        }

        i++;
    }  
       
    return sequenses;
}

char** getAtbashOrReversedAtbashSeqIgnoreEmptyChars(char* word, char* text)
{
    long int textSize = strlen(text);
    long int wordSize = strlen(word);

    // maximum sequenses is when word is one char and text
    // contain textSize letter each one of them is like word
    // or like atbashWord. for example: word is: 'a' 
    // text is: 'aaazzzazazzazazaaaz....az'
    // ("a" or "z" * textSize...)
    char** sequenses = (char**)malloc(textSize * sizeof(char*));
    int seqCount = 0;

    // get atbash word.
    char* atbashWord = getAtbash(word);
    char* reverse = getReverse(atbashWord);
    
    int i = 0; // go around word
    int j = 0; // go around atbashWord
    int k = 0; // go over the text outside.
    int l = 0; // go over the text inside.
    int regularProcess = TRUE; // flag turn off when we need to k++
    int atbashProcess = TRUE; // flag turn off when we need to k++

    char* regularSeq = (char*)calloc(sizeof(char), WORD);
    char* atbashSeq = (char*)calloc(sizeof(char), WORD);
    while(k < textSize)
    {
        // ignode unalphabet chars.
        while(!isalpha(text[k]) && k < textSize){k++;}

        l = k;
        while(l < textSize)
        {
            if(isalpha(text[l]))
            {
                if(regularProcess)
                {
                    // add letter to regular, or not and free seq
                    if(reverse[i % wordSize] == text[l])
                    {
                        regularSeq[strlen(regularSeq)] = text[l];
                        i++;

                        // if we get cpmplete word above.
                        if(i % wordSize == 0)
                        {
                            sequenses[seqCount++] = regularSeq;
                            regularSeq = (char*)calloc(sizeof(char), WORD);
                            i = 0;
                            regularProcess = FALSE;
                        }
                    }
                    else
                    {
                        free(regularSeq);
                        regularSeq = (char*)calloc(sizeof(char), WORD);
                        i = 0;
                        regularProcess = FALSE;
                    }
                }

                if(atbashProcess)
                { 
                    if(atbashWord[j % wordSize] == text[l])
                    {
                        atbashSeq[strlen(atbashSeq)] = text[l];
                        j++;

                        // if we get cpmplete word above.
                        if(j % wordSize == 0)
                        {
                            sequenses[seqCount++] = atbashSeq;
                            atbashSeq = (char*)calloc(sizeof(char), WORD);
                            j = 0;
                            atbashProcess = FALSE;
                        }
                    }
                    else
                    {
                        //free(atbashSeq);
                        atbashSeq = (char*)calloc(sizeof(char), WORD);
                        j = 0;
                        atbashProcess = FALSE;
                    }
                }

            }
            else
            {
                if(regularProcess)
                {
                    regularSeq[strlen(regularSeq)] = text[l];
                }
                
                if(atbashProcess)
                {
                    atbashSeq[strlen(atbashSeq)] = text[l];
                }
            }
            
            // if reg and atbash end with curr word start with k, go next k.
            if(regularProcess == FALSE && atbashProcess == FALSE)
            {
                break;
            }

            l++;
        }

        k++;
        regularProcess = TRUE;
        atbashProcess = TRUE;
    }

    return sequenses;
}

char** getAngramSeqIgnoreEmptyChars(char* word, char* text)
{
    long int textSize = strlen(text);

    // maximum sequenses is when word is one char and text
    // contain textSize letter each one of them is like word
    // for example: word is: 'a' 
    // text is: 'aaaaaaaaaa....a'
    // ("a" * textSize...)
    char** sequenses = (char**)malloc(textSize * sizeof(char*));
    int seqCount = 0;

    int i = 0;
    int j = 0;

    while(i < textSize)
    {
        // make copy of word
        char* copyOfWord = (char*)calloc(sizeof(char), strlen(word)+1);
        strcpy(copyOfWord, word);

        // make new sequence
        char* seq = (char*)calloc(sizeof(char), TXT);

        // ignode unalphabet chars.
        while(!isalpha(text[i]) && i < textSize){i++;}

        j = i;
        while(j < textSize)
        {
            if(isalpha(text[j]))
            {
                long int pos = findPlace(copyOfWord, text[j]);
                if(pos != ERROR)
                {
                    seq[strlen(seq)] = text[j];
                    j++;

                    deleteCharByIndex(copyOfWord, pos);
                    if(strlen(copyOfWord) == 0)
                    {
                        sequenses[seqCount++] = seq;
                        break;
                    }
                }
                else
                {
                    free(seq);
                    seq = (char*)calloc(sizeof(char), TXT);
                    break;
                }
            }
            else
            {
                if(text[j] == ' ' || text[j] == '\t')
                {
                    seq[strlen(seq)] = text[j];
                    j++;
                }
                else
                {
                    break;
                }
            }
        }
        i++;
    }

    return sequenses;

}


//---HELPER_FUNCTIONS---//

/*
functon get some word and return the gematria value.
input: string of some word.
output: gemtaria value int.
*/
int getGematriaStr(char* word)
{
    long int len = strlen(word);
    int gematria = 0;
    
    for(int i = 0; i < len; i++)
    {
        if(isalpha(word[i]))
        {
            gematria += tolower(word[i]) - 'a' + 1;
        }
    }

    return gematria;
}

/*
functon return the gematria for single char.
input: singke.
output: gemtaria value int.
*/
int getGematria(char c)
{
    return tolower(c) - 'a' + 1;
}

/*
function return an atbash word.
input: word
output: the word in atbash 
*/
char* getAtbash(char* word)
{
    long int len = strlen(word);
    char* atbash = calloc(sizeof(char), len + 1);

    for(int i = 0; i < len; i++)
    {
        if(isupper(word[i]))
        {
            atbash[i] = 'A' + ('Z' - word[i]);
        }
        else if(islower(word[i]))
        {
            atbash[i] = 'a' + ('z' - word[i]);
        }
        else
        {
            atbash[i] = word[i];
        }
    }

    return atbash;
}

char* getReverse(char* word)
{
    long int len = strlen(word);
    char* reverse = (char*)calloc(sizeof(char), len + 1);
    for(int i = len - 1, j = 0; i >= 0; i--, j++)
    {
        reverse[j] = word[i];
    }

    return reverse;
}


long int findPlace(char* str, char c)
{
    long int position = strchr(str, c) - str;

    // if(position<=0)
    // {
    //     printf("str is: %s, c is %c\n", str, c);
    // }

    return position >= 0 ? position : ERROR;
}

void deleteCharByIndex(char* str, int i)
{
    memmove(str + i, str + (i + 1), strlen(str) - i);
}
