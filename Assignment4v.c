#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct sorting{
    char *word;
    int counter;
}Sorting;

int compare(const void * a, const void * b)
{
    Sorting * c = (Sorting*)a;
    Sorting * d = (Sorting*)b;
    /*
    if (strcasecmp(c->word, d->word) == 0)
    {

    }*/
    return strcmp(c->word, d->word);
}

void wordProcessor(int size, FILE *fp, FILE *fwOne)
{
    printf("WORD-PROCESSOR STARTED\n");
    size++;
    const char *space = " ";
    char *outputLine = malloc(size);
    char line[101];
    //printf("SIZE -> %d\n", size);
    int lineSize = 0;
    while (fscanf(fp, "%s\n", line) == 1)
    {
        char *wordToken = strtok(line, space);
        while (wordToken != NULL)
        {
            if (strlen(wordToken) + lineSize + 1 <= size)
            {
                strcat(outputLine, wordToken);
                strcat(outputLine, " ");
                lineSize += strlen(wordToken);
                //printf("%s\n", outputLine);
                lineSize++;
            }
            else
            {
                strcat(outputLine, "\n");
                fputs(outputLine, fwOne);
                memset(outputLine, '\0', size);
                lineSize = 0;
                strcat(outputLine, wordToken);
                strcat(outputLine, " ");
                lineSize += strlen(wordToken);
                lineSize++;
            }
            wordToken = strtok(NULL, space);
        }
    }
    strcat(outputLine, "\n");
    fputs(outputLine, fwOne);
}

void wordCounter(FILE *fp, FILE *fw)
{
    Sorting *wordlist = malloc(sizeof(Sorting));
    //printf("set up 1\n");
    fseek(fp, 0, SEEK_SET);
    char line[100];
    //const char *space = " ";
    int count = 0, temp = 1;
    fscanf(fp, "%s", line);
    wordlist[count].word = malloc(strlen(line) + 1);
    strcpy(wordlist[count].word,line);
    wordlist[count].counter = 1;
    //printf("wordlist at %d is %s\n", count, wordlist[count].word);
    count++;

    //printf("line is -> %s\n", line);
    while (fscanf(fp, "%s", line) == 1)
    {
        //printf("line is -> %s\n", line);
        for (int i = 0; i < count; i++)
        {
            //printf("i is --> %d\n", i);
            //printf("wordlist at 0 is ->%s\n", wordlist[0].word);
            if (strcmp(wordlist[i].word,line) == 0)
            {
                //printf("If 1 reached...\n");
                temp = 0;
                wordlist[i].counter++;
                break;
            }
            else
            {
                temp = 1;
            }
        }
        if (temp == 1)
        {
            //printf("temp equal to 1 \n");
            wordlist = realloc(wordlist, ((count + 1) * sizeof(Sorting)));
            wordlist[count].word = malloc(strlen(line) + 1);
            strcpy(wordlist[count].word,line);
            wordlist[count].counter = 1;
            //printf("wordlist at %d is %s\n", count, wordlist[count].word);
            count++;
        }       
    }
    //qSort will be done later...
    qsort(wordlist, count, sizeof(Sorting), compare);
    printf("qsort done with count --> %d\n", count);
    char test[50];
    for (int k = 0; k < count; k++)
    {
        sprintf(test, "%s - %d\n", wordlist[k].word, wordlist[k].counter);
        fputs(test, fw);
    }
    free(wordlist);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    FILE *fwOne;
    FILE *fwTwo;
    char fileName[50];
    strcpy(fileName, argv[2]);
   
    char fileOut[50];
    strcpy(fileOut, fileName);
    strcat(fileOut, ".out");
    char fileWord[50];
    strcpy(fileWord, fileName);
    strcat(fileWord, ".word");
    fp = fopen(fileName, "r");
    fwOne = fopen(fileOut, "w");
    fwTwo = fopen(fileWord, "w");
    int size = atoi(argv[1]);
    //printf("SIZE -> %d\n", size);
    
    wordProcessor(size, fp, fwOne);
    fclose(fwOne);
    wordCounter(fp, fwTwo);
    fclose(fp);
    fclose(fwTwo);
}