#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    char puzzle[50][50];
    char answers[50][50];
    char word[50];
    
    //int i = 0;
    gets(word);
    int length = 0;
    int x = 1,y = 0, max = 0; // integers that represent the positions in the puzzle and the max size of the puzzle.
    char letter = 'a'; // the currently being read character.

    /* 
    find the length of one row.
    */
    int k = 0;
    while (letter != (char)0)
    {
        letter = word[k];
        if (isalpha(letter) > 0)
        {
            puzzle[0][y] = letter;
            y++;
        }
        k++;
    }
    max = y;
    y = 0;
    //printf("%d \n", max);
    //fflush(stdout);
    /* 
    finds the letters in the table and puts them into the puzzle array without spaces.
    */
    for (x = 1; x < max; x++)
    {
        gets(word);
        y = 0;
        for (k = 0; k < max * 2; k++)
        {
            if (isalpha(word[k]) > 0)
            {
                puzzle[x][y] = word[k];
                y++;
            }
        }
    }

    /*
what should i do about going diagonally?
shoudl i add +1 to row & column or -1 to row & column?

step 1: go thought the first line and count how many letters which is the # of rows.
step 2: if it is a letter, input it into the puzzle array. if it is a whitespace, ignore it!
step 3: read a word form the file, and find it, then go to the next.
    */

    // set up a while loop to read each word till EOF.
    
    for (int f = 0; f < max; f++)
    {
        for (int g = 0; g < max; g++)
        {
            answers[f][g] = ' ';
        }
    }

    while (gets(word) != NULL)
    {
        //gets(word);
        int temp = 0;
        int flag = 0;
        length = strlen(word) - 1;
        // PUT THE SEARCHING LOOP HERE!!!
        for (int row = 0; row < max; row++)
        {
            for (int column = 0; column < max; column++)
            {
                if (word[0] == puzzle[row][column])
                {
                    /* WORD IS FROM TOP TO BOTTOM */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (row + temp <= max && word[temp] == puzzle[row + temp][column] && row + temp >= 0)
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            //printf("\n");
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row + temp][column] = puzzle[row + temp][column];                            
                        }
                        break;
                    }

                    /* WORD IS FROM LEFT TO RIGHT */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (column + temp <= max && word[temp] == puzzle[row][column + temp] && column + temp >= 0)
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row][column + temp] = puzzle[row][column + temp];
                        }
                        break;
                    }

                    /* WORD IS FROM BOTTOM TO TOP */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (row - temp >= 0 && word[temp] == puzzle[row - temp][column])
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row - temp][column] = puzzle[row - temp][column];
                        }
                        break;
                    }

                    /* WORD IS FROM RIGHT TO LEFT */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (column - temp >= 0 && word[temp] == puzzle[row][column - temp])
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row][column - temp] = puzzle[row][column - temp];
                        }
                        break;
                    }

                    /* WORD IS DIAGONALLY RIGHT AND DOWN */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (row + temp <= max && column + temp <= max && word[temp] == puzzle[row + temp][column + temp])
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row + temp][column + temp] = puzzle[row + temp][column + temp];
                        }
                        break;
                    }

                    /* WORD IS DIAGONALLY RIGHT AND UP */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        
                        if (row - temp >= 0 && column + temp <= max && word[temp] == puzzle[row - temp][column + temp])
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row - temp][column + temp] = puzzle[row - temp][column + temp];
                        }
                        break;
                    }

                    /* WORD IS DIAGONALLY LEFT AND DOWN */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (column - temp >= 0 && row + temp <= max && word[temp] == puzzle[row + temp][column - temp])
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row + temp][column - temp] = puzzle[row + temp][column - temp];
                        }
                        break;
                    }

                    /* WORD IS DIAGONALLY LEFT AND UP */
                    flag = 1;
                    for (temp = 1; temp < length; temp++)
                    {
                        if (row - temp >= 0 && column - temp >= 0 && word[temp] == puzzle[row - temp][column - temp])
                        {
                            // leave blank
                        }
                        else
                        {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag == 1)
                    {
                        for (temp = 0; temp < length; temp++)
                        {
                            answers[row - temp][column - temp] = puzzle[row - temp][column - temp];
                        }
                        break;
                    }                    
                }
                if (flag == 1)
                {
                    break;
                }
            }
            if (flag == 1)
            {
                break;
            }          
        }
    }
    
    // printing out the answer array.
    for (int f = 0; f < max; f++)
    {
        for (int g = 0; g < max; g++)
        {
            printf("%c ", answers[f][g]);
        }
        printf("\n"); 
    }
}
