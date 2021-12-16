#include "EX3.h"
#include <stdio.h>

int main()
{
    // get word and text from user.
    char* word = getWord();
    char* text = getText();

    printf("Gematria Sequences: ");
    char** n = getGematriaSequences(word, text);
    for(int i = 0; i < TXT; i++)
    {
        if(n[i] == NULL){break;}
        printf("%s", n[i]);
        if(i+1 >= TXT || n[i+1]!=NULL)
        {
            printf("~");
        }
    }

    printf("\n");

    printf("Atbash Sequences: ");
    char** n2 = getAtbashOrReversedAtbashSeqIgnoreEmptyChars(word, text);
    for(int i = 0; i < TXT; i++)
    {
        if(n2[i] == NULL){break;}
        printf("%s", n2[i]);
        if(i+1 >= TXT || n2[i+1]!=NULL)
        {
            printf("~");
        }
    }

    printf("\n");

    printf("Anagram Sequences: ");
    char** n3 = getAngramSeqIgnoreEmptyChars(word, text);
    for(int i = 0; i < TXT; i++)
    {
        if(n3[i] == NULL){break;}
        printf("%s", n3[i]);
        if(i+1 >= TXT || n3[i+1]!=NULL)
        {
            printf("~");
        }
    }
 
    return 0;
}