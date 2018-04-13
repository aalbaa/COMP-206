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

              
/***************** CODE FROM HERE  ************/

  // Opening file:
  FILE *bmpfile = fopen(bmp_filename,"rb");
  if(bmpfile == NULL){
    printf("(48) Error reading the file\n");
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
    printf("(75) Error reading the file  \n");
    return -1;
  }

  


  // image data pointer (malloc)
    *img_data = (unsigned char*) malloc(*data_size);
  
  fread(*img_data, 1, *data_size, bmpfile);
  
    
  *width =  *(unsigned int*)(*img_data+18);  
  
  *height = *(unsigned int*)(*img_data+22);
    
  *bits_per_pixel = *(unsigned int*)(*img_data+28);
  


  // unsigned int *data_size, 
  *data_offset = *(unsigned int*)(*img_data+10);
  
  // Calculating and storing "padding":
  *padding = *width%4;
  

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
  

    
  // opening output file (or creating it)
  FILE *bmpfile_new = fopen(output_bmp_filename,"wb");
  if(bmpfile_new == NULL){
    printf("(196) Error reading the file\n");
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
/*                          Q3                */

int bmp_collage( char* bmp_input1, char* bmp_input2, char* bmp_result, int x_offset, int y_offset ){
  // int temp = x_offset;
  // x_offset = y_offset;
  // y_offset = temp;

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
  
  // BEGINNGING OF SOLUTION
  unsigned int img_width_result;
  unsigned int img_height_result;
  unsigned int bits_per_pixel_result;
  unsigned int data_size_result;
  unsigned int padding_result;
  unsigned int data_offset_result;
  unsigned char* img_data_result    = NULL;
  
  
  int additional_width;
  int additional_height;


  int x_max, x_min, y_max, y_min;   //to determine height and width

if(x_offset >=0){
  if(img_width1 >= img_width2+x_offset){
    x_max = img_width1;
  }else{
    x_max = img_width2 + x_offset;
  }
}else{
  // if(img_width1 >= img_width2-x_offset){
    x_max = img_width1-x_offset;
  // }else{
  //   x_max = img_width2 - x_offset;
  // }
}
  

  if( x_offset < 0){
    x_min = x_offset;
  }else{
    x_min = 0;
  }

if(y_offset >=0 ){
  if(img_height1 >= img_height2 + y_offset){
    y_max = img_height1;
  }else{
    y_max = img_height2 + y_offset;
  }
}else{
  y_max = img_height1-y_offset;
}
  

  if( y_offset < 0){
    y_min = y_offset;
  }else{
    y_min = 0;
  }

  img_width_result = x_max-x_min;
  img_height_result = y_max-y_min;



  // img_width_result = img_width1 + additional_width;
  // img_height_result = img_height1 + additional_height;

  padding_result = img_width_result%4;

  
  // choosing the header file to be identical to that of input 1;
  data_offset_result = data_offset1;
  bits_per_pixel_result = bits_per_pixel1;

  // data_size_result = ((img_width_result*img_height_result)-(img_width2*img_height2))*bits_per_pixel_result/8
  //                     +(img_width2*img_height2*bits_per_pixel2/8);

  data_size_result = ((img_width_result*img_height_result)*bits_per_pixel2/8);
  // adding offset:
  data_size_result += data_offset_result + padding_result*img_height_result;

  debug("data_size_result:  %u\n",data_size_result);

  debug("new image data_size :  %u\n",data_size_result);

  // new img
  img_data_result = (unsigned char*)malloc(data_size_result);
  memcpy(img_data_result, img_data1, data_offset1);
  
  // editing data:  
  unsigned int* data_int_ptr_result = (unsigned int*) (img_data2);  
  *(data_int_ptr_result+ 2) = data_size_result;
  *(data_int_ptr_result+10) = data_offset_result;
  *(data_int_ptr_result+18) = img_width_result;
  *(data_int_ptr_result+22) = img_height_result;
  *(data_int_ptr_result+28) = bits_per_pixel_result;

  int x = 2;
  *(img_data_result+x) = *(data_int_ptr_result+x);
  x = 10;
  *(img_data_result+x) = *(data_int_ptr_result+x);
  x = 18;
  *(img_data_result+x) = *(data_int_ptr_result+x);
  x = 22;
  *(img_data_result+x) = *(data_int_ptr_result+x);
  x = 28;
  *(img_data_result+x) = *(data_int_ptr_result+x);


  // debugging
  unsigned int sizeTest = *(data_int_ptr_result+2);
  debug("new image size (from malloc): %u\n",sizeTest);
  x = 10;
  sizeTest = *(data_int_ptr_result+x);
  debug("new image data_offset: %u\n",sizeTest);
  x = 18;
  sizeTest = *(data_int_ptr_result+x);
  debug("new image width: %u\n",sizeTest);
  x = 22;
  sizeTest = *(data_int_ptr_result+x);
  debug("new image height: %u\n",img_height_result);

  

  unsigned int num_colors = bits_per_pixel_result/8;
  

  // negative x_offset (0 if x_offset >0)
  int x_offset_ve = 0;
  int y_offset_ve = 0;

  

  
  

  for(int row = 0; row <= img_height_result; row++){
    for(int col = 0; col <= img_width_result; col++){
      // writing top image
      if(( (row-y_offset+y_min) >= 0 && (row-y_offset+y_min) <= img_height2) && ((col-x_offset+x_min) >= 0 && (col-x_offset+x_min) <= img_width2)){           

        memcpy(img_data_result + row*(img_width_result*num_colors+padding_result) + col*num_colors + data_offset_result,
              img_data2+ (row-y_offset+y_min)*(img_width2*num_colors+padding2) + (col-x_offset+x_min)*num_colors + data_offset2,
              num_colors);
      }else{
        
        // bottom image
        if(row <= img_height1-y_min && row >= -y_min && col <= img_width1-x_min && col >= -x_min){              
          memcpy(img_data_result + row*(img_width_result*num_colors+padding_result) + col*num_colors + data_offset_result,
              img_data1 + (row+y_min)*(img_width1*num_colors+padding1) + (col+x_min)*num_colors + data_offset1,
              num_colors);    

          
        }else{
          // black or white
          img_data_result[ row*(img_width_result*num_colors+padding_result) + col*num_colors + 2 + data_offset_result] = 0;      
          img_data_result[ row*(img_width_result*num_colors+padding_result) + col*num_colors + 1 + data_offset_result] = 0;
          img_data_result[ row*(img_width_result*num_colors+padding_result) + col*num_colors + 0 + data_offset_result] = 0;     
        }
      }
    }    
  }  

  
 

  FILE *bmp_result_ptr = fopen(bmp_result,"wb");
  if(bmp_result == NULL){
    printf("Error opening the file\n");
    return -1;
  }
  fwrite(img_data_result, 1, data_size_result, bmp_result_ptr);
  
  debug("pointer: img_data1:  %p\n",img_data1);
  fclose(bmp_result_ptr);
  // bmp_close( &img_data1 );
  bmp_close( &img_data2 );

   
  return 0;
}               
