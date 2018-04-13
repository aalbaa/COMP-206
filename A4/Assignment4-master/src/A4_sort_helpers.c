#include "A4_sort_helpers.h"
#include <stdlib.h>
sem_t* sem[27]; // 27 semaphores
// Function: read_all() 
// Provided to read an entire file, line by line.
// No need to change this one.
void read_all( char *filename ){
    
    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
	
    while( curr_line < MAX_NUMBER_LINES && 
           fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) )
    {
        curr_line++;
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// Function: read_all() 
// Provided to read only the lines of a file staring with first_letter.
// No need to change this one.
void read_by_letter( char *filename, char first_letter ){

    FILE *fp = fopen( filename, "r" );
    int curr_line = 0;
    text_array[curr_line][0] = '\0';
	
    while( fgets( text_array[curr_line], MAX_LINE_LENGTH, fp ) ){
        if( text_array[curr_line][0] == first_letter ){
            curr_line++;
        }

        if( curr_line == MAX_NUMBER_LINES ){
            sprintf( buf, "ERROR: Attempted to read too many lines from file.\n" );
            write( 1, buf, strlen(buf) );
            break;
        }
    }
	
    text_array[curr_line][0] = '\0';
    fclose(fp);
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q1.
void sort_words( ){
    char temp[MAX_LINE_LENGTH]; // this is a temporary variable for 'swap'

    for (int i = 0; text_array[i][0] != '\0'; i++ ){
        for(int j=i; text_array[j][0] != '\0';j++){
            if(strcmp(text_array[j],text_array[i]) < 0){
                // swap
                strcpy(temp, text_array[i]);
                // char* temp =(char*)malloc(MAX_LINE_LENGTH*sizeof(char));
                strcpy(text_array[i], text_array[j]);
                strcpy(text_array[j], temp);
            }
        }
    }
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2.
int initialize( ){
    // Remove the current place-holder code, and write your own.
    // sprintf(buf, "Initializing.\n"  );
    // write(1, buf, strlen(buf));

    // array of alphabet (as strings)
    char alph[27][2];
    
    alph[0][0] = 'a';
    alph[0][1] = '\0';

    sem_unlink(alph[0]);
    sem[0] = sem_open(alph[0],O_CREAT, 0666,1);
        
    for (int i = 0; i < 26; i++){
        alph[i][0] = 'a'+i;
        alph[i][1] = '\0';

        sem_unlink(alph[i]);
        sem[i] = sem_open(alph[i],O_CREAT, 0666,0);
    }


    return 0;
}

// YOU MUST COMPLETE THIS FUNCTION FOR Q2 and Q3.   
int process_by_letter( char* input_filename, char first_letter ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "This process will sort..." lines
    // are printed in the right order (alphabetical).
    sem_wait(sem[first_letter-'a']);
    
    sprintf(buf, "This process will sort the letter %c.\n",  first_letter );
    write(1,buf,strlen(buf));

    sem_post(sem[first_letter-'a'+1]);

    // For Q3, uncomment the following 2 lines and integrate them with your overall solution.
    // read_by_letter( input_filename, first_letter );
    // sort_words( );

    return 0;
}

// YOU COMPLETE THIS ENTIRE FUNCTION FOR Q2 and Q3.
int finalize( ){
    // For Q2, keep the following 2 lines in your solution (maybe not at the start).
    // Add lines above or below to ensure the "Sorting complete!" line
    // is printed at the very end, after all letter lines.
    
    sem_post(sem[0]);
    sprintf( buf, "Sorting complete!\n" );
    write( 1, buf, strlen(buf) );
    sem_post(sem[26]);

    // For Q3, come up with a way to accumulate the sorted results from each
    // letter process and print the overal sorted values to standard out.
    // You are not allowed to read from the input file, or call sort_words
    // directly from this function.

    return 0;
}

