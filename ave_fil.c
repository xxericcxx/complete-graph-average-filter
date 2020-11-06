//
//  ave_fil.c
//  
//
//  Created by Eric on 2020/11/1.
//

#include <stdint.h>
#include <stdio.h>
#include "src//lib//mcimage.h"
#include "src//lib//laddconst.h"
 
/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
  
    struct xvimage * image1;

    unsigned char *ptrimage1;
    unsigned char *ptrimage2;

  
    int rs, cs, N;
  

//判断输入完整
  
    if (argc != 3)
  
    {
    
        fprintf(stderr, "ave_fil inputimage.pgm outputimage.pgm\n", argv[0]);
    
        exit(0);
  
    }
 
    
    
    
 
    image1 = readimage(argv[1]);
  
    if (image1 == NULL)
  
    {
    
        fprintf(stderr, "addconst: readimage failed\n");
    
        exit(0);
  
    }
    
    
  
  
    rs = image1->row_size;
  
    cs = image1->col_size;
  
    N = rs * cs;
    
    
  
    ptrimage1 = UCHARDATA(image1);  //ptrimage1  --> image1 data
  
    
    
    
    for(int i = 1;i < rs - 1;i++)
    {
        for(int j = 1;j < cs - 1;j++)
        {
            ptrimage1[i * rs + j] = (int) (ptrimage1[ (i - 1) * rs + (j - 1)]+
                                       ptrimage1[ (i - 1) * rs + j]+
                                       ptrimage1[ (i - 1) * rs + (j + 1)]+
                                       ptrimage1[ i * rs + (j - 1)]+
                                       ptrimage1[ i * rs + j]+
                                       ptrimage1[ i * rs + (j + 1)]+
                                       ptrimage1[ (i + 1) * rs + (j - 1)]+
                                       ptrimage1[ (i + 1) * rs + j]+
                                       ptrimage1[ (i + 1) * rs + (j + 1)]) / 9;
        
        }
    }
    
    
    
    

    
    


  

  
    writeimage(image1, argv[2]);
  
    freeimage(image1);

 
}
