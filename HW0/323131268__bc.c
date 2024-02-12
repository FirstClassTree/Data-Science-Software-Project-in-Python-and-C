#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {
    int sourceBase, targetBase, inputNumber;
    char temp;
    int returnNumber = 0;

    while(1){
        printf("enter the source base: \n");
        scanf("%d",&sourceBase);
        if(sourceBase<2 || sourceBase>16){
            printf("invalid target base!\n");
        }
        else{
            break;
        }
    }
    while(1){
        printf("enter the target base:\n");
        scanf("%d",&targetBase);
        if(targetBase<2 || targetBase>16){
            printf("invalid target base!\n");
        }
        else{
            break;
        }
    }
    printf("enter a number in base %d: \n",sourceBase);

    while(1){
        temp = getch();
        int tempAscci = (int)temp;
        if(tempAscci == 10 && returnNumber > 0){
            printf("enter a number in base %d: \n",sourceBase);
            break;
        }
        
        else if(48 <= tempAscci && tempAscci <= 47 + sourceBase || 97 <= tempAscci && tempAscci <= 96 + (sourceBase - 10 ) ){

            if(48 <= tempAscci && tempAscci <= 57){
                inputNumber =   tempAscci - 48;
            }
            else{
                inputNumber = tempAscci - 87;
            }

            while (inputNumber>0){
                returnNumber = inputNumber % targetBase;
                inputNumber = inputNumber / targetBase;
                if(returnNumber > 9){
                    printf("%c",returnNumber + 87);
                }
                else{
                    printf("%d",returnNumber);
                }
            }
        }
       
        else if (tempAscci !=10) {
            printf("invalid input number!\n");
        }
        
        
    }



}
