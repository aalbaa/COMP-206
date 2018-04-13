#include <stdio.h>
#include <stdlib.h>



void printMonth(int month, char months[][9], int textWidth);
void printWeek(char [][9] , int);
void printDays(int, int);
void printMultipleChar(char,int numberOfChars);
void printDashLine(int textWidth);

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Error: there should be two arguments: DAYSIZE >= 2, and FIRSTDAY [1,7]");
        return -1;
    }
    
    // input paramaters
    int daysize = atoi(argv[1]);
    int firstday = atoi(argv[2]);

    if (daysize <2 || firstday < 1 || firstday >7){
        printf("Error: DAYSIZE should be >=2 and FIRSTDAY be in [1,7]");
        return -1;
    }

    // To avoid excessive memory usage
    if(daysize > 9) daysize = 9;

    // initializing week days
    char week[7][9]={"Sunday   ","Monday   ","Tuesday  ","Wednesday","Thursday ","Friday   ","Saturday "};
    
    char months[12][9]={"Jaunary  ","February ","March    ", "April    ", "May      ", "June     ", "July",
                        "August   ", "September","October  ","November ","December "};
    
    int textWidth = 7*(daysize+3)+1;

    printDashLine(textWidth);
    printMonth(0,months,textWidth);

    printDashLine(textWidth);
    printWeek(week,daysize);
    
    printDashLine(textWidth);
    printDays(firstday,daysize);


    

    return 0;
}














// month is the month to be printed: 0 for January, and 11 for December
void printMonth(int month, char months[][9], int textWidth){
    printf("|");
    printMultipleChar(' ',textWidth/2+textWidth%2-5);
    for(int i = 0; i< 9; i++){
        printf("%c",months[month][i]);
    }
    printMultipleChar(' ',textWidth/2-6);
    printf("|");
    printf("\n");
}


// Funciton to print week days
void printWeek(char week[][9] , int daysize){
    printf("| ");
    for (int i=0; i< 7; i++){
        for(int j=0; j<daysize; j++){
            printf("%c",week[i][j]);        
        }        
        printMultipleChar(' ',1);
        printf("|");
        printMultipleChar(' ',1);
    }
    printf("\n");
}





// Print the days
void printDays(int firstday, int daysize){
    // Print blanks for the days we don't need
    for (int j = 1; j<firstday; j++){
                printf("|");
                printMultipleChar(' ',2);
                printMultipleChar(' ',daysize);                
            }
    
        for ( int i =1 ; i< 31; i++){

            if (i<10){                
                printf("|");
                printMultipleChar(' ',1);
                printf("%i",i);
                printMultipleChar(' ',daysize);                
            }else{                
                printf("|");
                printMultipleChar(' ',1);
                printf("%i",i);
                printMultipleChar(' ',daysize-1); 
            }        
            if((i+firstday-1)%7 == 0){printf("|\n");}
        }
        
        if ((30+firstday-1)%7!=0){
            for (int j = 0; j<7-(30+firstday-1)%7; j++){
                if((30+j+firstday-1)%7 == 0){printf("|\n");}
                printf("|");
                printMultipleChar(' ',2);
                printMultipleChar(' ',daysize);                
            }
            printf("|\n");
        }
}

void printMultipleChar(char c, int n){
    for(int i=0; i<n; i++){
        printf("%c",c);
    }
}


// Printing a dash of lines with the width of the weekdays
void printDashLine(int textWidth){    
    printf("|");
    printMultipleChar('-',textWidth-2); //the -2 is because we're using the char '|' twice
    printf("|");
    printf("\n");
}
