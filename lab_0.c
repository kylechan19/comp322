/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *filename = NULL;

void readFile(){
    printf("Enter file name: ");
    scanf("%d", &filename);
    filename = (char *)malloc(sizeof(char));
}

void convertValue(){

}

void inputData(){

}

int main(void) {
    int choice;
    choice = 0;

    while(choice != 3){
        printf("\n");
        printf("MENU OPTIONS: \n ");
        printf("Option 1: Read data from file \n ");
        printf("Option 2: Enter data to be processed \n ");
        printf("Option 3: Quit \n ");
        printf("\n INPUT: ");
      
        scanf("%d", &choice);
        printf("\n");

        switch(choice){
        
        case 1: 
        break;

        case 2:
        break;
      
        case 3: printf("End of lab_0.c");
        break;

        default: printf("Enter a valid option. \n \n");
    }
  }