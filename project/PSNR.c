//
//  PSNR.c
//  
//
//  Created by Eric on 2020/11/5.
//

#include <stdint.h>
#include <stdio.h>
#include "src//lib//mcimage.h"
#include "src//lib//laddconst.h"
#include <math.h>
#include <string.h>
int main(int argc, char **argv)

{
    
    if (argc != 3)
    
    {
      
        fprintf(stderr, "PSNR denoised.pgm noise.pgm\n", argv[0]);
      
        exit(0);
    
    }
    
    struct xvimage * image1;
    struct xvimage * image2;
    unsigned char *ptrimage1;
    unsigned char *ptrimage2;
    int rs1, cs1, N1;
    int rs2, cs2, N2;
    int MSE = 0;
    float PSNR = 0;
    image1 = readimage(argv[1]);
    image2 = readimage(argv[2]);
    
    rs1 = image1->row_size;
    
    cs1 = image1->col_size;
    
    N1 = rs1 * cs1;
      
      
    
    ptrimage1 = UCHARDATA(image1);
    
    rs2 = image2->row_size;
    
    cs2 = image2->col_size;
    
    N2 = rs2 * cs2;
      
    ptrimage2 = UCHARDATA(image2);
    
    for(int y = 0; y < rs1; y++)
    {
        for(int x=0; x< cs1; x++)
        {
            MSE += ((int)(ptrimage2[x + y * cs1]) - (int)(ptrimage1[x + y * cs1])) * ((int)(ptrimage2[x + y * cs1]) - (int)(ptrimage1[x + y * cs1]));
        }
    }
    MSE = MSE / N1;
    PSNR = 10 * (log10(255 * 255 / (MSE)));
    printf("PSNR is %f db\n",PSNR);
}
