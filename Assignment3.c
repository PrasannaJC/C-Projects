#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct virtualMachine
{
    int vMachine[100];
    int accumulator;
    int iCounter;
    int iRegister;
    int oCode;
    int operand;
};

int compile(struct virtualMachine vm, int problem)
{
    int primary = 0;
    printf("Compile started...\n");
    
    if (problem == 0)
    {
        printf("Compile was sucessful :)\n");
        primary = 1;
    }
    else if (problem == 1)
    {
        printf("Compile failed => Word overflow :(\n");
        primary = 0;
    }
    else if (problem == 3)
    {
        printf("Compile failed => Wrong format (Undefined command) :(\n");
        primary = 0;
    }
    else if (problem == 2)
    {
        printf("Compile failed => Unknown command :(\n");
        primary = 0;
    }
    else if (problem == 4)
    {
        printf("Compile failed => No HALT was found :(\n");
        primary = 0;
    }
    return primary;
}

void execute(struct virtualMachine vm, int lines)
{
    //printf("EXECUTE STARTS\n");
    //printf("%d\n",lines);
    vm.accumulator = 0;
    vm.iCounter = 0;
    vm.operand = 0;
    vm.oCode = 0;
    /*
    for (int b = 0; b <= lines; b++)
    {
        printf("%d - %d\n",b ,vm.vMachine[b]);
    }*/
    int errorCode = 0;
    while (1)
    {
        if (vm.iCounter > 99 || vm.iCounter < 0)
        {
            errorCode = 4;
            break;
        }
        vm.iRegister = vm.vMachine[vm.iCounter];
        vm.oCode = vm.iRegister/100;

        //vm.operand = vm.vMachine[vm.iCounter]%100;
        //printf("-->%d\n",vm.iCounter);
        //printf("While starts here\n");
        //read
        if (vm.oCode == 10)
        {
            //printf("read starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 1000;
            int temp = 0;
            //printf("before scanf\n");
            //scanf("%d", temp);
            scanf("%d", &temp);
            //printf("after scanf\n");
            fflush(stdout);
            vm.vMachine[vm.operand] = temp;
            
            //printf("Read works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
            vm.iCounter++;
        }
        //write
        else if (vm.oCode == 11)
        {
            //printf("write starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 1100;
            printf("%d\n", vm.vMachine[vm.operand]); //should format it...
            
            //printf("write works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
            vm.iCounter++;
        }
        //print
        else if (vm.oCode == 12)
        {
            //printf("print starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 1200;
            int k = vm.operand;
            char f1;
            char l1;
            int truth = 1;
            do
            {
                int first = vm.vMachine[k]/100;
                int last = vm.vMachine[k]%100;
                if (first < 91 && last < 91 && (first == 0 || last == 0 || first == 10 || last == 10 || first > 64 || last > 64))
                {
                    f1 = first;
                    l1 = last;
                    printf("%c%c", f1,l1);
                    k++;
                }
                else
                {
                    truth = 0;
                    break;
                }
                
            }while (l1 != '\0');

            if (truth == 0)
            {
                errorCode = 3;
                break;
            }
            vm.iCounter++;
        }
        //load
        else if (vm.oCode == 20)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 2000;
            if (vm.vMachine[vm.operand] > 9999 || vm.vMachine[vm.operand] < -999)
            {
                errorCode = 1;
                break;
            }
            else
            {
                vm.accumulator = vm.vMachine[vm.operand];
                vm.iCounter++;
            }
        }
        //store
        else if (vm.oCode == 21)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 2100;
            vm.vMachine[vm.operand] = vm.accumulator;
            vm.iCounter++;
        }
        
        //SET is already done in compile...

        //add
        else if (vm.oCode == 30)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 3000;
            vm.accumulator += vm.vMachine[vm.operand];
            if (vm.accumulator > 9999 || vm.accumulator < -999)
            {
                errorCode = 1;
                break;
            }            
            else
            {
                vm.iCounter++;
            }
        }
        //subtract
        else if (vm.oCode == 31)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 3100;
            vm.accumulator = vm.accumulator - vm.vMachine[vm.operand];
            if (vm.accumulator > 9999 || vm.accumulator < -999)
            {
                errorCode = 1;
                break;
            }            
            else
            {
                vm.iCounter++;
            }
        }
        //divide
        else if (vm.oCode == 32)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 3200;
            if (vm.vMachine[vm.operand] == 0)
            {
                //printf("ErrorCode 4 reached\n");
                //fflush(stdout);
                errorCode = 2;
                break;
            }
            else
            {
                vm.accumulator = vm.accumulator / vm.vMachine[vm.operand];
                vm.iCounter++;
            }            
        }
        //multiply
        else if (vm.oCode == 33)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 3300;
            vm.accumulator = vm.accumulator * vm.vMachine[vm.operand];
            if (vm.accumulator > 9999 || vm.accumulator < -999)
            {
                errorCode = 1;
                break;
            }
            else 
            {
                vm.iCounter++;    
            }
        }
        //modulus
        else if (vm.oCode == 34)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 3400;
            vm.accumulator = vm.accumulator % vm.vMachine[vm.operand];
            if (vm.accumulator > 9999 || vm.accumulator < -999)
            {
                errorCode = 1;
                break;
            }            
            else
            {
                vm.iCounter++;
            }
        }
        //bran
        else if (vm.oCode == 40)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 4000;
            if (vm.operand >=0 && vm.operand < 100)
            {
                vm.iCounter = vm.operand;
            }
            else
            {
                errorCode = 4;
                break;
            }
        }
        //brng
        else if (vm.oCode == 41)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 4100;
            if (vm.accumulator < 0)
            {
                vm.iCounter = vm.operand;
            }
            else
            {
                vm.iCounter++;
            }
        }
        //brzr
        else if (vm.oCode == 42)
        {
            vm.operand = vm.vMachine[vm.iCounter] % 4200;
            if (vm.accumulator == 0)
            {
                vm.iCounter = vm.operand;
            }
            else
            {
                vm.iCounter++;
            }
        }
        
        //halt
        else if (vm.oCode == 99)
        {
            break; // HALT IS OUTSIDE OF THE WHILE LOOP...
        }
        
        else
        {
            errorCode = 5;
            break;
        }         
    }

    // ALL POSSIBLE ERROR CODES LISTED BEFORE THE HALT FUNCTION.
    if (errorCode == 1)
    {
        printf("Word overflow for item inputted in accumulator at position %d :(\n", vm.iCounter);
    }
    else if (errorCode == 2)
    {
        printf("Dividing by 0 was attempted at position %d :(\n", vm.iCounter);
    }
    else if (errorCode == 3)
    {
        printf("Printing unknown character was attempted at position %d :(\n", vm.iCounter);
    }
    else if (errorCode == 4)
    {
        printf("Segemntation fault with directory target out of bounds at position %d :(\n", vm.iCounter);
    }
    else if (errorCode == 5)
    {
        printf("Unrecognized Command Code at position %d :(\n", vm.iCounter);
    }
    else // not necessary...
    {
        printf("YOUR PROGRAM IS PERFECT WITH NO ERRORS!!!\n");
    }

    //HALT done here...
    printf("\nREGISTERS:");
    printf("\nAccumulator:             %04d", vm.accumulator);
    printf("\nInstructionCounter:        %02d", vm.iCounter);
    printf("\nInstructionRegister:     %04d", vm.iRegister); // not sure about this one...
    printf("\nOperationCode:             %02d", vm.oCode);
    printf("\nOperand:                   %02d", vm.operand);
    printf("\nMEMORY:\n");
    int z = 0;
    printf("  ");
    while (z < 10)
    {
        printf("%6d", z);
        z++;
    }
    for (int x = 0; x < 10; x++)
    {
        printf("\n%2d", x*10);
        for (int y = 0; y < 10; y++)
        {
            if (vm.vMachine[(x * 10) + y] < 0)
            {
                printf(" %05d", vm.vMachine[(x * 10) + y]);
            }
            else
            {
                printf(" %+05d", vm.vMachine[(x * 10) + y]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    struct virtualMachine vm;
    //printf("main starts\n");
    //int virtual[100];
    int value = 0, lineNumber = 0, problem = 0, haltCount = 0, dummy = 0;
    char line[50];
    for (int w = 0; w < 100; w++)
    {
        vm.vMachine[w] = 0;
    }

    // Below are all the different commands as chacter arrays.---------------------------------------------------------
    // Use strcmp to check for each command.
    //INPUT/OUTPUT
    char read[5] = "READ";
    char write[5] = "WRIT";
    char print[5] = "PRNT";
    //LOAD/STORE
    char load[5] = "LOAD";
    char stor[5] = "STOR";
    char set[4] = "SET"; // SET has been replaced with SETT for it to work!!!
    //ARITHMETIC
    char add[4] = "ADD";
    char subtract[4] = "SUB";
    char divide[4] = "DIV";
    char multiply[5] = "MULT";
    char modulus[4] = "MOD";
    //CONTROL
    char bran[5] = "BRAN";
    char brng[5] = "BRNG";
    char brzr[5] = "BRZR";
    char halt[5] = "HALT";

    while (gets(line) != NULL)
    {
        const char *space = " ";
        char *token = strtok(line, space);
        lineNumber = ((token[0] - '0') * 10) + (token[1] - '0');
        token = strtok(NULL, space);
        char function[5] = {' '};
        int temp = 0;        
        while(temp < strlen(token))
        {
            function[temp] = token[temp];
            temp++;  
        }
        //printf("------>>>>%d\n", strlen(function));
        if (strlen(function) < 3 || strlen(function) > 4 || !isalpha(function[0]))
        {
            dummy = 3;
            problem = 3;
        }
        temp = 0;
        token = strtok(NULL, space);
        if (strlen(token) > 5)
        {
            problem = 1;
        }
        value = atoi(token);

        if (strcmp(function,read) == 0)
        {
            vm.vMachine[lineNumber] = 1000 + value;
        }
        // write function
        else if (strcmp(function,write) == 0)
        {
            vm.vMachine[lineNumber] = 1100 + value;
        }
        // print function
        else if (strcmp(function,print) == 0)
        {
            vm.vMachine[lineNumber] = 1200 + value;
        }
        // load function
        else if (strcmp(function,load) == 0)
        {
            vm.vMachine[lineNumber] = 2000 + value;
        }
        // store function
        else if (strcmp(function,stor) == 0)
        {
            vm.vMachine[lineNumber] = 2100 + value;
        }
        // set function
        else if (strcmp(function,set) == 0)
        {
            vm.vMachine[lineNumber] = value;
        }
        // add function
        else if (strcmp(function,add) == 0)
        {
            vm.vMachine[lineNumber] = 3000 + value;
        }
        // subtract function
        else if (strcmp(function,subtract) == 0)
        {
            vm.vMachine[lineNumber] = 3100 + value;
        }
        // divide function
        else if (strcmp(function,divide) == 0)
        {
            vm.vMachine[lineNumber] = 3200 + value;
        }
        // multiply function
        else if (strcmp(function,multiply) == 0)
        {
            vm.vMachine[lineNumber] = 3300 + value;
        }
        // modulus function
        else if (strcmp(function,modulus) == 0)
        {
            vm.vMachine[lineNumber] = 3400 + value;
        }
        // bran function
        else if (strcmp(function,bran) == 0)
        {
            vm.vMachine[lineNumber] = 4000 + value;
        }
        // brng function
        else if (strcmp(function,brng) == 0)
        {
            vm.vMachine[lineNumber] = 4100 + value;
        }
        // brzr function
        else if (strcmp(function,brzr) == 0)
        {
            vm.vMachine[lineNumber] = 4200 + value;
        }
        // halt function
        else if (strcmp(function,halt) == 0)
        {
            vm.vMachine[lineNumber] = 9900 + value;
            haltCount++;
        }
        else
        {
            vm.vMachine[lineNumber] = 10000;
            problem = 2;
        }
        //printf("%d - %s - %d\n",lineNumber ,function, vm.vMachine[lineNumber]);
    }
    if (haltCount == 0)
    {
        problem = 4;
    }
    if (dummy == 3)
    {
        problem = 3;
    }
    
    if (compile(vm, problem) == 1)
    {
        stdin = fopen("/dev/tty", "r");
        execute(vm, lineNumber);
    }
}
