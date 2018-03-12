#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    //there must be 3 arguments, else exit
    if (argc!=4){
        printf("Error: Not enough arguments. input file.out <\"pathTo text File\"> <a> <b>\n");
        return -1;
    }
    
    
    char *filePath = argv[1];
    char *replicaPath = "replicaFile.txt"; //the intermediate file used to replica
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    
    char tag1[3] = "#A#";
    char tag2[3] = "#B#";
    
    

    
    FILE * fileIn = fopen(filePath,"r");    //The file we're reading from
    FILE * fileOut = fopen(replicaPath,"w");                         //The file we're replicaing to
    // Error reading (or opening) either files
    if (fileIn == NULL ||fileOut == NULL){
        printf("Error: bad file\n");
        return -1;
    }

    
    char c;

    //This is just plain replicaing files

    char temp[3];
    for (c = fgetc(fileIn); c!=EOF; c=fgetc(fileIn)){
        if(c == tag1[0]){
            temp[0]=c;
            temp[1]=fgetc(fileIn);
            temp[2]=fgetc(fileIn);
            if (temp[1]==tag1[1] && temp[2]==tag1[2]){
                fprintf(fileOut,"%0.6f",a);                
            }else{
                if (temp[1]==tag2[1] && temp[2]==tag2[2]){
                    fprintf(fileOut,"%0.6f",b); 
                }else{
                    fprintf(fileOut,"%c%c%c",temp[0],temp[1],temp[2]);
                }
                
            }            
            continue;                    
        }

        fprintf(fileOut,"%c",c);     
    }



    fclose(fileIn);
    fclose(fileOut);


    //copying files from replica to original. Thus requiring the "w" mode 
    fileIn = fopen(replicaPath,"r");
    fileOut = fopen(filePath,"w");


    if (fileIn == NULL ||fileOut == NULL){
        printf("Error: bad file\n");
        return -1;
    }


    //copying files to original file
    for (c = fgetc(fileIn); c!=EOF; c=fgetc(fileIn)){
            // fprintf(fileOut,"%c",c);
            printf("%c",c);
	
    }


    fclose(fileIn);
    fclose(fileOut);

    remove(replicaPath);
    

    return 0;    
}
