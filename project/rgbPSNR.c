//
//  rgbPSNR.c
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



int MSE(unsigned char* ptrimage1,unsigned char* ptrimage2,int cs, int rs)
{
    int MSE = 0;
    for(int y = 0; y < rs; y++)
    {
        for(int x=0; x< cs; x++)
        {
            MSE += ((int)(ptrimage1[x + y * cs]) - (int)(ptrimage2[x + y * cs])) * ((int)(ptrimage1[x + y * cs]) - (int)(ptrimage2[x + y * cs]));
        }
    }
    return MSE;
}




int main(int argc, char **argv)

{
    
    if (argc != 3)
    
    {
      
        fprintf(stderr, "PSNR denoised.pgm noise.pgm\n", argv[0]);
      
        exit(0);
    
    }
    
    struct xvimage * g1;
    struct xvimage * g2;
    struct xvimage * g3;

    struct xvimage * g4;
    struct xvimage * g5;
    struct xvimage * g6;
    
    unsigned char *ptrimage1;
    unsigned char *ptrimage2;
    unsigned char *ptrimage3;
    
    unsigned char *ptrimage4;
    unsigned char *ptrimage5;
    unsigned char *ptrimage6;
    int rs, cs, N;

    int MSE_r = 0;
    int MSE_g = 0;
    int MSE_b = 0;
    int MSE_sum = 0;
    float PSNR = 0;

    readrgbimage(argv[1], &g1, &g2, &g3);
    readrgbimage(argv[2], &g4, &g5, &g6);
    
    rs = g1->row_size;
    
    cs = g1->col_size;
    
    N = rs * cs;
      
      
    
    ptrimage1 = UCHARDATA(g1);

    ptrimage2 = UCHARDATA(g2);
    
    ptrimage3 = UCHARDATA(g3);
    
    ptrimage4 = UCHARDATA(g4);

    ptrimage5 = UCHARDATA(g5);
    
    ptrimage6 = UCHARDATA(g6);
    
    MSE_r = MSE(ptrimage1,ptrimage4,cs,rs);
    MSE_g = MSE(ptrimage2,ptrimage5,cs,rs);
    MSE_b = MSE(ptrimage3,ptrimage6,cs,rs);
    MSE_sum = ((MSE_r + MSE_g + MSE_b) / (3 * N));
    PSNR = 10 * (log10(255 *255 / MSE_sum));
    printf("PSNR_rgb is %f db\n",PSNR);
}


