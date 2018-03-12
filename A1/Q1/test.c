#include <stdio.h>
#include <stdlib.h>

void addStr(char* a, char* b, char c[]){
    int sizeA = sizeof(a)/sizeof(a[0]);
    int sizeB = sizeof(b)/sizeof(b[0]);
    int i = 0;
    while(i<sizeA){
        c[i] = a[i];
        i++;
    }
    while(i<sizeB+sizeA){
        c[i] = b[i-sizeA];
        i++;
    }

       
}

int main(int argc, char *argv[]){


    // FILE* fileIn = fopen("test.txt","r");
    // FILE* fileOut = fopen("testOut.txt","w");

    // if (fileIn == NULL || fileOut==NULL){
    //     printf("Error: bad file\n");
    //     exit(-1);   
    // }
    // char c;

    // c = fgetc(fileIn);
    // while(c!=EOF){
    //     fprintf(fileOut,"%c",c);
    //     c = fgetc(fileIn);
    // }

    // fclose(fileIn);
    // fclose(fileOut);

    // remove("testOut.txt");

    

    char a[3];
    a[0]='a';
    a[1]='b';
    a[2]='\0';
    // b[1]='b';
    // b[2]='c';
    // printf("%c%c\n",a[0],a[1]);
    puts(a);
    // char* c = a+b;
    // printf("%s\n",c);

    







    // char userIn[100];
    // fgets(userIn,100,file);
    // printf("%s",userIn);
    

    // fprintf(file,"This is a test\nlet's see how it goes\n");
    // fprintf(file,"Hello world3\n");
    // char string[100]; 
    // char c;
    // fgetc(string, 100,file);
    // while ()
    // c = fgetc(file);
    // while(c!=' '){
    //     printf("%c",c);
    //     c = fgetc(file);
    // }
    // // file++;
    // fprintf(file,"%s","ZB");

    
    // rename("test4.txt","test5.txt");

    // fgets(string,100,file);
    // printf("%s\n",string);
    // while(string !="test"){
    //     printf("%s",string);
    //     fgets(string,100,file);
    // }

    // while(c!=' '){
    //     printf("%c",c);
    //     c = fgetc(file);
    // }
    // // file++;
    // fprintf(file,"%s","ZB");


    // fscanf(file,"%s",string);
    // printf("%s\n",string);
    // fscanf(file,"%s",string);
    // printf("%s\n",string);


    return 0;
}


/*
questions:
Is the filename always the same?
Is the path TO the file? Or includes the file itself?? (Desktop/test.txt) or Deskop/ ?

*/