#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
    /*
    questions => number of questions on the quiz.
    score => the user's score on the quiz.
    level => the difficulty of the quiz.
    upper => the upper limit for the range of random integers generated.
    lower => the lower limit for the range of random integers generated.
    operation => an integer that is used to store what arithmetic operation is being used for a question.
    first => the first random integer of a question.
    second => the second random integer of a question.
    answerInput => the answer inputted by the user in response to a question.
    answerKey => the correct answer to a question.
    */
    int questions = 0, score = 0, level = 0, upper, lower, operation, first, second = 0, answerInput = 0, answerKey;
    int valid = 1;
    
    char levelIn[20];
    char questionIn[20];
    char answerArray[20];

    while (questions <= 0 || questions > 20)
    {
        valid = 1;
        printf("How many questions are on this test? (1-20) ");
        scanf("%s", questionIn);

        for (int k = 0; k < 20; k++)
        {
            if (valid == 1)
            {
                if (isdigit(questionIn[k]) != 0)
                {
                    valid = 1;
                    //printf("validation working  ");
                }
                else if (questionIn[k] == '\0')
                {
                    break;
                }
                else
                {
                    valid = 0;
                    //printf("validation quit  ");
                }
            }
        }
        //printf("for loop working  ");
        if (valid == 1)
        {
            questions = atoi(questionIn);
            //printf("%d", questions);
        }
        else
        {
            questions = 0;
        }
        
    }
    
    while (level <= 0 || level > 4)
    {
        valid = 1;
        printf("Select difficulty for the test(1 - 4): ");
        scanf("%s", levelIn);

        for (int k = 0; k < 20; k++)
        {
            if (valid == 1)
            {
                if (isdigit(levelIn[k]) != 0)
                {
                    valid = 1;
                    //printf("validation working  ");
                }
                else if (levelIn[k] == '\0')
                {
                    break;
                }
                else
                {
                    valid = 0;
                    //printf("validation quit  ");
                }
            }
        }
        //printf("for loop working  ");
        if (valid == 1)
        {
            level = atoi(levelIn);
            //printf("%d", level);
        }
        else
        {
            level = 0;
        }
        //scanf("%d", & level);
    }
    
    if (level == 1)
    {
        upper = 10;
        lower = 1;
    }
    else if (level == 2)
    {
        upper = 50;
        lower = 1;
    }
    else if (level == 3)
    {
        upper = 100;
        lower = 1;
    }
    else
    {
        upper = 100;
        lower = -100;
    }

    /*
    operations=>
    Addition: 1
    Subtraction: 2
    Multiplication: 3
    Division: 4
    */

    for (int i = 1; i <= questions; i++)
    {
        operation = ((rand() % 4) + 1);
        if (operation == 4 && level == 4)
        {
            while (second == 0)
            {
                second = ((rand() % (200)) + 1 + lower);
            }
        }
        else
        {
            second = ((rand() % (upper)) + lower);
        }
        
        first = ((rand() % (upper)) + lower);
        printf("\nQuestion %d: ", i);

        switch(operation)
        {
            case 1:
                printf("%d + %d", first, second);
                answerKey = first + second;
                break;
            case 2:
                printf("%d - %d", first, second);
                answerKey = first - second;
                break;
            case 3:
                printf("%d * %d", first, second);
                answerKey = first * second;
                break;
            default:
                printf("%d / %d", first, second);
                answerKey = first / second;
                break;
        }
/*
        printf("\nEnter your answer: ");
        scanf("%d", & answerInput);
        */
        
        valid = 1;

        printf("\nEnter your answer: ");
        scanf("%s", answerArray);

        for (int l = 0; l < 20; l++)
        {
            //printf("%c\n", answerArray[l]);
            if (valid == 1)
            {
                if (isdigit(answerArray[l]) != 0)
                {
                    valid = 1;
                    //printf("validation working  ");
                }
                else if (answerArray[l] == '-' && l == 0)
                {
                    valid = 1;
                }
                else if (answerArray[l] == '\0')
                {
                    break;
                }
                else
                {
                    valid = 0;
                    //printf("validation quit  ");
                }
            }
        }
        //printf("for loop working  ");
        if (valid == 1)
        {
            answerInput = atoi(answerArray);
            if (answerInput == answerKey)
            {
                printf("\nCorrect!!!");
                score++;
            }
            else
            {
                printf("\nWrong!!!");
                printf("\nThe correct answer is %d", answerKey);
            }
            //printf("%d", level);
        }
        else
        {
            printf("\nWrong!!!");
            printf("\nThe correct answer is %d", answerKey);
        }
    }

    printf("\nYour score is: %d / %d", score, questions);

    //return 0;
}