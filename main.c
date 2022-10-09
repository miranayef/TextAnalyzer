#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000
#define WORD_MAX 100
#define IN  1
#define OUT 0

void RepeatedWords(char words[WORD_MAX][MAX], int length);
void BarChart(char words[WORD_MAX][MAX], int length);
void Data(char str[MAX], int length);

int main()
{
    char str[MAX], words[WORD_MAX][MAX];
    int i=0, k, j=0,m=0, characters=0,  length=0;
    int state = OUT;
    int nw = 0;


    //taking input from user
    printf("Enter text to analyze:\n");

    while((k = getchar()) != EOF)
    {
        str[m++]=k;
        if((isspace(k)!= 0)|| (ispunct(k)!= 0))
        {
            state = OUT;
            words[i][j] = '\0';
            i++;
            j = 0;
        }
        else
        {
            words[i][j++]= k;
            if(state == OUT)
            {
                state = IN;
                nw++;
            }
        }
    }

    //number of words
    length=nw;
    for(k=0; k<length;k++){
        printf("\n%s", words[k]);
    }

    //calling the functions
    Data(str, length);
    RepeatedWords(words, length);
    BarChart(words, length);


    return 0;
}

void Data(char str[MAX], int length){

    int letters=0, digits=0, symbols=0, spaces=0, characters=0;
    float percentage, percentage2, percentage3, percentage4;
    characters = strlen(str);


    //using for loop to determine data sizes
    for(int i=0 ; i < characters; i++)
    {
        if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z')){
            letters ++;
        }else if(str[i]>='1' && str[i]<='9'){
             digits ++;
        }else if(str[i] != ' ' && str[i]!= '\n'){
             symbols++;
        }else if (str[i] == ' ')
             spaces++;
    }

    //calculating percentage ratios
    percentage = ((float)letters/(characters))*100.0 ;
    percentage2 = ((float)spaces/(characters))*100.0 ;
    percentage3 = ((float)digits/(characters))*100.0 ;
    percentage4 = ((float)symbols/(characters))*100.0 ;

    printf("\nNumber of:\n");
    printf("words=      %d\n", length);
    printf("characters= %d\n", characters);
    printf("letters=    %d\n", letters);
    printf("spaces=     %d\n", spaces);
    printf("digits=     %d\n", digits);
    printf("symbols=    %d\n", symbols);

    printf("\nPercentage ratio of:\n");
    printf("letters to characters: %.2f%%\n", percentage);
    printf("spaces to characters:  %.2f%%\n", percentage2);
    printf("digits to characters:  %.2f%%\n", percentage3);
    printf("symbols to characters: %.2f%%\n", percentage4);

}



void BarChart(char words[WORD_MAX][MAX], int length){

    char large[MAX];
    int k=0, j=0, l, size[length], sizeofwords=0;
    float percentratio[length], percent[length];

    for(k=0;k<length;k++){
            size[k] = strlen(words[k]); //calculates size of each word
            sizeofwords += strlen(words[k]); //calculates total size
    }

    for(k=0;k<length;k++){
            percentratio[k]=(size[k]/(float)(sizeofwords))*100;//calculates percentage ratio
    }


    int maxsize = 0 ;

    //find the largest length so we can use it as limit in the bar chat
    for(k=0 ; k < length; k++){
         if(strlen(large) < strlen(words[k])){
            strcpy(large, words[k]);
         }
    }
    maxsize= strlen(large);

    for(l=0; l<length ;l++){
        for(k=l+1 ; k<length;k++){
            if(percentratio[k] == percentratio[l]){
                   percent[l] += percentratio[k];//summing the duplciates
                for(j=k; j<length; j++)
                {
                    percentratio[j] = percentratio[j + 1]; //Copy the next element to the current element of array
                    size[j] = size[j + 1];
                }
                length--; //decrement the size of array by one since we deleted an element
                k--;
        }
      }percentratio[l]+= percent[l];
    }

    //printing the bar chart
    for(l=maxsize ; l>0 ; l--)
    {  if(l<10)
       printf(" %d|  ", l);//prints vertically the percentages
       else printf("%d|  ", l);
        for(k=0 ; k<length; k++)
        {
            if( l<=(size[k]))
            printf("||   ");//prints the bars for each percentage ratio
            else
            printf("     ");
        }printf("\n");
    }

       printf("   ");

    for(l=0 ; l<length; l++){
        printf("_____");
    }

    printf("\n     ");

    for(l=0 ; l<length; l++){
        if (percentratio[l] > 0.00)
            printf("%.0f%%  ",percentratio[l]);
    }
    printf("\n\n  %%  --> percentage ratio of each word\n num --> world length\n");

}

void RepeatedWords(char words[WORD_MAX][MAX], int length){

    char repeated[MAX];
    int k, l, occurrence, maximum=0;


    //using nested for loop to compare words and find the repeated ones
    for(k=0;k<length;k++){
        occurrence=0;
      for(l=k ; l<length ;l++){
        if(strcmp(words[k], words[l]) == 0){
         occurrence++;
        }
      }
      //using if to find the most repeated word and then copying the value of that word
        if (occurrence>maximum){
            maximum = occurrence;
            strcpy(repeated ,words[k]);
      }
    }

    //using if to print whether or not there is a repeated word
    if (maximum > 1){
    printf("\nThe most repeated word is '%s' and it was repeated %d times\n\n", repeated, maximum);
    }else {
    printf("\nThere are no repeated words\n\n");
    }
}
