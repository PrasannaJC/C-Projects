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
    printf("word a -> %s\n", c->word);
    printf("word b -> %s\n", d->word);
    printf("compare is %d\n", strcmp(c->word, d->word));
    printf("----------------------------------\n");
    */
    if (strcasecmp(c->word, d->word) == 0 && strcmp(c->word, d->word) < 0)
    {
        return -1;
    }
    else if (strcasecmp(c->word, d->word) == 0 && strcmp(c->word, d->word) > 0)
    {
        return 1;
    }
    else if (strcmp(c->word, d->word) != 0)
    {
        return strcasecmp(c->word, d->word);
    }
}

void wordProcessor(int size, FILE *fp, FILE *fwOne)
{
    size++;
    const char *space = " ";
    char *outputLine = malloc(size);
    char line[101];
    int lineSize = 0;
    while (fscanf(fp, "%s\n", line) == 1)
    {
        char *wordToken = strtok(line, space);
        while (wordToken != NULL)
        {
            if (strlen(wordToken) + lineSize + 1 < size)
            {
                strcat(outputLine, wordToken);
                lineSize += strlen(wordToken);
                if (lineSize < size)
                {
                    strcat(outputLine, " ");
                }
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
    fseek(fp, 0, SEEK_SET);
    char line[100];
    int count = 0, temp = 1;
    fscanf(fp, "%s", line);
    wordlist[count].word = malloc(strlen(line) + 1);
    strcpy(wordlist[count].word,line);
    wordlist[count].counter = 1;
    count++;

    while (fscanf(fp, "%s", line) == 1)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(wordlist[i].word,line) == 0)
            {
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
            wordlist = realloc(wordlist, ((count + 1) * sizeof(Sorting)));
            wordlist[count].word = malloc(strlen(line) + 1);
            strcpy(wordlist[count].word,line);
            wordlist[count].counter = 1;
            
            count++;
        }       
    }
    
    qsort(wordlist, count, sizeof(Sorting), compare);
    
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
    
    wordProcessor(size, fp, fwOne);
    fclose(fwOne);
    wordCounter(fp, fwTwo);
    fclose(fp);
    fclose(fwTwo);
}