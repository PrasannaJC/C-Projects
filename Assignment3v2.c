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


int compile(struct virtualMachine vm)
{
    /*--------------------------------------------------------------------------------------------------------*/

    
    //printf("main starts\n");
    //int virtual[100];
    int lineNumber = 0;
    char line[50];
    
    //int accumulator = 0;
    int value = 0, haltCount = 0, valid = 0, unknownCount = 0, OOB = 0;

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
        temp = 0;
        
        token = strtok(NULL, space);
        if (strlen(token) > 5)
        {
            valid = 1;
            //printf("");
        }
        value = atoi(token);
        //printf("%d\n", value);
        if (strcmp(function,read) == 0)
        {
            vm.vMachine[lineNumber] = 1000 + value;
            //virtual[lineNumber] = 1000 + value;
        }
        // write function
        else if (strcmp(function,write) == 0)
        {
            vm.vMachine[lineNumber] = 1100 + value;
            //[lineNumber] = 1100 + value;
        }
        // print function
        else if (strcmp(function,print) == 0)
        {
            vm.vMachine[lineNumber] = 1200 + value;
            //[lineNumber] = 1200 + value;
        }
        // load function
        else if (strcmp(function,load) == 0)
        {
            vm.vMachine[lineNumber] = 2000 + value;
            //[lineNumber] = 2000 + value;
        }
        // store function
        else if (strcmp(function,stor) == 0)
        {
            vm.vMachine[lineNumber] = 2100 + value;
            //[lineNumber] = 2100 + value;
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
            //[lineNumber] = 3000 + value;
        }
        // subtract function
        else if (strcmp(function,subtract) == 0)
        {
            vm.vMachine[lineNumber] = 3100 + value;
            //[lineNumber] = 3100 + value;
        }
        // divide function
        else if (strcmp(function,divide) == 0)
        {
            vm.vMachine[lineNumber] = 3200 + value;
            //[lineNumber] = 3200 + value;
        }
        // multiply function
        else if (strcmp(function,multiply) == 0)
        {
            vm.vMachine[lineNumber] = 3300 + value;
            //[lineNumber] = 3300 + value;
        }
        // modulus function
        else if (strcmp(function,modulus) == 0)
        {
            vm.vMachine[lineNumber] = 3400 + value;
            //[lineNumber] = 3400 + value;
        }
        // bran function
        else if (strcmp(function,bran) == 0)
        {
            vm.vMachine[lineNumber] = 4000 + value;
            //[lineNumber] = 4000 + value;
        }
        // brng function
        else if (strcmp(function,brng) == 0)
        {
            vm.vMachine[lineNumber] = 4100 + value;
            //[lineNumber] = 4100 + value;
        }
        // brzr function
        else if (strcmp(function,brzr) == 0)
        {
            vm.vMachine[lineNumber] = 4200 + value;
            //[lineNumber] = 4200 + value;
        }
        // halt function
        else if (strcmp(function,halt) == 0)
        {
            vm.vMachine[lineNumber] = 9900 + value;
            haltCount++;
            //[lineNumber] = 9900;
        }
        else
        {
            //printf("UNRECOGNIZED COMMAND\n");
            vm.vMachine[lineNumber] = 10000;
            unknownCount++;
        }
        if (vm.vMachine[lineNumber] > 9999 || vm.vMachine[lineNumber] < -999)
        {
            OOB++;
        }
        printf("value --> %d\n",vm.vMachine[lineNumber]);
    }

    if (haltCount == 0)
    {
        valid = 4;
    }
    if (unknownCount > 0)
    {
        valid = 3;
    }
    if (OOB > 0)
    {
        valid = 1;
    }
    
    /*--------------------------------------------------------------------------------------------------------*/
/*
    for (int b = 0; b <= 99; b++)
    {
        printf("%d - %d\n",b ,vm.vMachine[b]);
    }*/

    printf("Compile started...\n");
    if (valid == 0)
    {
        printf("Compile was sucessful :)\n");
        return 1;
    }
    else if (valid == 1)
    {
        printf("Compile failed => Word overflow occurred :(\n");
        return 0;
    }
    else if (valid == 2)
    {
        printf("Compile failed => Wrong format :(\n");
        return 0;
    }
    else if (valid == 3)
    {
        printf("Compile failed => unknown word :(\n");
        return 0;
    }
    else if (valid == 4)
    {
        printf("Compile failed => No HALT was found :(\n");
        return 0;
    }

}

void execute(struct virtualMachine vm)
{
    printf("EXECUTE STARTS\n");
    //printf("%d\n",lines);
    vm.accumulator = 0;
    vm.iCounter = 0;
    vm.operand = 0;
    vm.oCode = 0;
    
    for (int b = 0; b <= 99; b++)
    {
        printf("%d - %d\n",b ,vm.vMachine[b]);
    }

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
                    /*
                    if (first == 0 || last == 0 || first == 10 || last == 10 || first > 64 || last > 64)
                    */
                    f1 = first;
                    l1 = last;
                    printf("%c%c", f1,l1);
                    k++;
                }
                else
                {
                    //printf("Character unknown :(\n");
                    truth = 0;
                    break;
                }
                /*
                f1 = first;
                l1 = last;
                printf("%c%c", f1,l1);
                k++;
                */
            }while (l1 != '\0');
            if (truth == 0)
            {
                errorCode = 3;
                break;
            }
            //printf("print works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
            vm.iCounter++;
        }
        //load
        else if (vm.oCode == 20)
        {
            //printf("load starts\n");
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
            //printf("load works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
        }
        //store
        else if (vm.oCode == 21)
        {
            //printf("store starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 2100;
            vm.vMachine[vm.operand] = vm.accumulator;
            //printf("store works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
            vm.iCounter++;
        }
        /*//set
        else if (vm[i]/100 == 22)
        {
            printf("set starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 2200;
            vm[vm.operand - 1] = vm[vm.operand];
            
            printf("set works\n");
        }*/
        //add
        else if (vm.oCode == 30)
        {
            //printf("add starts\n");
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
            //printf("subtract starts\n");
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
            //printf("divide starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 3200;
            //printf("before if %d \n", vm.operand);
            if (vm.vMachine[vm.operand] == 0)
            {
                printf("ErrorCode 4 reached\n");
                fflush(stdout);
                errorCode = 2;
                break;
            }
            else
            {
                vm.accumulator = vm.accumulator / vm.vMachine[vm.operand];
                vm.iCounter++;
            }            
            //printf("divide works with - %d - at - %d - with accumulator equal to => %d\n", vm.vMachine[vm.operand],vm.iCounter, vm.accumulator);
        }
        //multiply
        else if (vm.oCode == 33)
        {
            //printf("multiply starts\n");
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
            //printf("modulus starts\n");
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
            //printf("bran starts\n");
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
            //printf("bran works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
        }
        //brng
        else if (vm.oCode == 41)
        {
            //printf("brng starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 4100;
            if (vm.accumulator < 0)
            {
                vm.iCounter = vm.operand;
            }
            else
            {
                //errorCode = 4; // does not apply for brng and brzr...
                //break;
                vm.iCounter++;
            }
            //printf("brng works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
        }
        //brzr
        else if (vm.oCode == 42)
        {
            //printf("brzr starts\n");
            vm.operand = vm.vMachine[vm.iCounter] % 4200;
            if (vm.accumulator == 0)
            {
                vm.iCounter = vm.operand;
            }
            else
            {
                vm.iCounter++;
            }
            //printf("brzr works at - %d - with accumulator equal to => %d\n", vm.iCounter, vm.accumulator);
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
        printf("Dividing by 0 was attempted at position %d :(", vm.iCounter);
    }
    else if (errorCode == 3)
    {
        printf("Printing unknown character was attempted at position %d :(", vm.iCounter);
    }
    else if (errorCode == 4)
    {
        printf("Segemntation fault with directory target out of bounds at position %d :(", vm.iCounter);
    }
    else if (errorCode == 5)
    {
        printf("Unrecognized Command Code at position %d :(", vm.iCounter);
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
    
    for (int w = 0; w < 100; w++)
    {
        vm.vMachine[w] = 0;
    }
    //printf("Main WHile Ends!!!\n");
    // the virtual array should be complete.

    for (int b = 0; b <= 99; b++)
    {
        printf("before compile >>> %d - %d\n",b ,vm.vMachine[b]);
    }

    compile(vm);
    if (compile(vm) == 1)
    {
        for (int b = 0; b <= 99; b++)
        {
            printf("before execute >>> %d - %d\n",b ,vm.vMachine[b]);
        }
        stdin = fopen("/dev/tty", "r");
        execute(vm);
    }
}
