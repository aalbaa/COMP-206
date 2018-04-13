#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int isNumeric (const char * s);

int main(int argc, char *argv[]){

    //there must be 3 arguments, else exit
    if (argc!=4){
        printf("Error: Not enough arguments. input file.out <\"pathTo text File\"> <a> <b>\n");
        return -1;
    }
    
    
    char *filePath = argv[1];
    char *replicaPath = "replicaFile.txt"; //the intermediate file used to replica

    // This is to make sure the arguments for 'a' and 'b' are indeed numeric
    if (isNumeric(argv[2]) == 0 || isNumeric(argv[3]) == 0){
        printf("Error: Values enetered for 'a' or 'b' are not numbers\n");
        return -1;
    }
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    
    char tag1[3] = "#A#";
    char tag2[3] = "#B#";
    
    

    
    FILE * fileIn = fopen(filePath,"r");    //The file we're reading from
        if (fileIn == NULL){
        printf("Error: bad file\n");
        return -1;
    }

    
    char c;


    // Printing the numbers
    char temp[3];
    for (c = fgetc(fileIn); c!=EOF; c=fgetc(fileIn)){
        if(c == tag1[0]){
            // 'temp' is used to store temporary characters if the first condition is met.
            temp[0]=c;
            temp[1]=fgetc(fileIn);
            temp[2]=fgetc(fileIn);
            if (temp[1]==tag1[1] && temp[2]==tag1[2]){
                printf("%0.6f",a);
            }else{
                if (temp[1]==tag2[1] && temp[2]==tag2[2]){
                    printf("%0.6f",b);
                }else{
                    printf("%c%c%c",temp[0],temp[1],temp[2]);
                }
                
            }            
            continue;                    
        }
        printf("%c",c); 
    }



    fclose(fileIn);


    return 0;    
}



// Checks if a string is a number (returns 1 if it's a number, and 0 otherwise)
int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}