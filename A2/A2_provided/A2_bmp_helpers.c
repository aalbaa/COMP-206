/* FILE: A2_bmp_helpers.c is where you will code your answers for Assignment 2.
 * 
 * Each of the functions below can be considered a start for you. 
 *
 * You should leave all of the code as is, except for what's surrounded
 * in comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A2_bmp_headers.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#ifdef DEBUG
  #define debug(x,y) printf(x,y)
  // #define debug(x) printf(x)
#else
  #define debug(x,y)
  // #define debug(x) printf(x)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int bmp_open( char* bmp_filename,        unsigned int *width, 
              unsigned int *height,      unsigned int *bits_per_pixel, 
              unsigned int *padding,     unsigned int *data_size, 
              unsigned int *data_offset, unsigned char** img_data ){

              
  // // YOUR CODE FOR Q1 SHOULD REPLACE EVERYTHING FROM HERE
  // printf( "BMP_OPEN is not yet implemented. Please help complete this code!\n" );
  // *width=0;
  // *height=0;
  // *bits_per_pixel=0;
  // *padding=0;
  // *data_size=0;
  // *data_offset=0;
  // *img_data=NULL;
  // // TO HERE


  // Opening file:
  FILE *bmpfile = fopen(bmp_filename,"rb");
  if(bmpfile == NULL){
    printf("Error reading the file\n");
    return -1;
  }


  // Reading first two characters
  char b,m;
  fread(&b,1,1,bmpfile);
  fread(&m,1,1,bmpfile);

  // If first two chars are not BM, then don't read the rest of the file (our code is based on BM files)
  if(b!='B'||m!='M'){
    printf("Error: file is NOT bitmap (BM)\n");
    return -1;
  }

  // Reading size of file
  fread(data_size, 1, sizeof(unsigned int), bmpfile);

  debug("First two bytes: %c",b);debug("%c\n",m);
  debug("File size: %u bytes == ",*data_size);debug("%u KB\n",*data_size/1024);
  

  // closing and reopening file to read from beginning:
  fclose(bmpfile);
  bmpfile = fopen(bmp_filename,"rb");
  if(bmpfile == NULL){
    printf("Error reading the file\n");
    return -1;
  }

  


  // image data pointer (malloc)
  unsigned char *img_data_ptr = (unsigned char*) malloc(*data_size);
  fread(img_data_ptr, 1, *data_size, bmpfile);
  
  *img_data = img_data_ptr;

  //NOTE: "*img_data" can be replaced for "img_data_ptr" in the following code. 
  // I chose img_data_ptr for the neateness of the code


  //testing (since we already know filesize)
  unsigned int* sizeTestPtr = (unsigned int*) (img_data_ptr+2);
  unsigned int sizeTest = *sizeTestPtr;

  

  unsigned int* width_ptr =  (unsigned int*)(img_data_ptr+18);
  *width = *width_ptr;

  unsigned int *height_ptr = (unsigned int*)(img_data_ptr+22);
  *height = *height_ptr;
  
  unsigned int *bits_per_pixel_ptr = (unsigned int*)(img_data_ptr+28);
  *bits_per_pixel = *bits_per_pixel_ptr;

  // unsigned int *padding_ptr = (unsigned int*)(img_data_ptr+22);,
  // unsigned int *data_size, 
  unsigned int *data_offset_ptr = (unsigned int*)(img_data_ptr+10);
  *data_offset = *data_offset_ptr;
  
  

  // Calculating and storing "padding":
  *padding = *width%4;



  debug("File size (test) in bytes: %u bytes\n", sizeTest);

  // closing file:
  fclose(bmpfile);
  
  return 0;  
}


/********************************************************************/
/********************************************************************/
/********************************************************************/

// We've implemented bmp_close for you. No need to modify this function
void bmp_close( unsigned char **img_data ){

  if( *img_data != NULL ){
    free( *img_data );
    *img_data = NULL;
  }
}


/********************************************************************/
/********************************************************************/
/********************************************************************/
//           Q2


int bmp_mask( char* input_bmp_filename, char* output_bmp_filename, 
              unsigned int x_min, unsigned int y_min, unsigned int x_max, unsigned int y_max,
              unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned int img_width;
  unsigned int img_height;
  unsigned int bits_per_pixel;
  unsigned int data_size;
  unsigned int padding;
  unsigned int data_offset;
  unsigned char* img_data    = NULL;
  
  int open_return_code = bmp_open( input_bmp_filename, &img_width, &img_height, &bits_per_pixel, &padding, &data_size, &data_offset, &img_data ); 
  
  if( open_return_code ){ printf( "bmp_open failed. Returning from bmp_mask without attempting changes.\n" ); return -1; }
 
  // // YOUR CODE FOR Q2 SHOULD REPLACE EVERYTHING FROM HERE
  // printf( "BMP_MASK is not yet implemented. Please help complete this code!\n" );
  // // TO HERE!

  


  unsigned char* new_img_data = (unsigned char*)malloc(data_size);
  memcpy(new_img_data, img_data, data_size);
  
  
  debug("Reading: %u \n",*(unsigned int*)(new_img_data+2));
  

  unsigned int num_colors = bits_per_pixel/8;
  unsigned char *pixel_data = new_img_data + data_offset;

  
  // Setting the values
  for(int row = y_min; row <= y_max; row++){
    for(int col = x_min; col <= x_max; col++){     
      new_img_data[ row*(img_width*num_colors+padding) + col*num_colors + 2 + data_offset] = red;      
      new_img_data[ row*(img_width*num_colors+padding) + col*num_colors + 1 + data_offset] = green;
      new_img_data[ row*(img_width*num_colors+padding) + col*num_colors + 0 + data_offset] = blue;      
    }    
  }
  
  debug("coutner k = %i\n",k);
    
  // opening output file (or creating it)
  FILE *bmpfile_new = fopen(output_bmp_filename,"wb");
  if(bmpfile_new == NULL){
    printf("Error reading the file\n");
    return -1;
  }
  // writing to output file
  fwrite(new_img_data, 1, data_size, bmpfile_new);

  // closing output file (we're done using it)
  fclose(bmpfile_new);
  
  bmp_close( &img_data );
  
  return 0;
}         



/********************************************************************/
/********************************************************************/
/********************************************************************/


int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){

  unsigned int img_width1;
  unsigned int img_height1;
  unsigned int bits_per_pixel1;
  unsigned int data_size1;
  unsigned int padding1;
  unsigned int data_offset1;
  unsigned char* img_data1    = NULL;
  
  int open_return_code = bmp_open( bmp_input1, &img_width1, &img_height1, &bits_per_pixel1, &padding1, &data_size1, &data_offset1, &img_data1 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input1 ); return -1; }
  
  unsigned int img_width2;
  unsigned int img_height2;
  unsigned int bits_per_pixel2;
  unsigned int data_size2;
  unsigned int padding2;
  unsigned int data_offset2;
  unsigned char* img_data2    = NULL;
  
  open_return_code = bmp_open( bmp_input2, &img_width2, &img_height2, &bits_per_pixel2, &padding2, &data_size2, &data_offset2, &img_data2 ); 
  
  if( open_return_code ){ printf( "bmp_open failed for %s. Returning from bmp_collage without attempting changes.\n", bmp_input2 ); return -1; }
  
  // YOUR CODE FOR Q3 SHOULD REPLACE EVERYTHING FROM HERE
  printf( "BMP_COLLAGE is not yet implemented. Please help complete this code!\n" );
  // TO HERE!
      
  bmp_close( &img_data1 );
  bmp_close( &img_data2 );
  
  return 0;
}                  
