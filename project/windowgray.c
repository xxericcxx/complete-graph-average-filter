//
//  windowgray.c
//  
//
//  Created by Eric on 2020/11/4.
//


#include <stdint.h>
#include <stdio.h>
#include "src//lib//mcimage.h"
#include "src//lib//laddconst.h"
#include <math.h>
#include <string.h>


#define MIN2(a, b) ((a) < (b) ? (a) : (b))
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define CLIP3(x, a, b) MIN2(MAX2(a,x), b)
 



unsigned char* NLM(unsigned char* ptrimage1, int cs, int rs, int bloc, int win, float fFiltPar, int fSigma){
    
    int rx,ry,wx,wy;
    int px, py, cx, cy;
    float diffval2 = 0;
    int channel = 1;
    float omega = 0;
    float sum = 0;
    float max;
    float Cp;
    float h = fFiltPar * fSigma;
    int windowsum;
    float meanpixel;
    for(int y = 0;y < rs;y++)
    {
        for(int x = 0;x < cs;x++)
        {
        
            omega = 0;
            Cp = 0;
            sum = 0;
            for(ry = -bloc ; ry <= bloc ; ry++)
            {
                for(rx = -bloc; rx <= bloc;rx++)
                {
                    diffval2 = 0;
                    for(wy = -win; wy <= win;wy++)
                    {
                        for(wx = -win;wx <= win;wx++)
                        {
                            cx = CLIP3(x + rx + wx, 0, cs - 1);
                            cy = CLIP3(y + ry + wy, 0, rs - 1);
                            px = CLIP3(x + wx, 0, cs - 1);
                            py = CLIP3(y + wy, 0, rs - 1);
                            diffval2 += ((int)(ptrimage1[px + py * cs]) - (int)(ptrimage1[cx + cy * cs])) * ((int)(ptrimage1[px + py * cs]) - (int)(ptrimage1[cx + cy * cs]));
                            
                        }
                    }
                
                    diffval2 = diffval2 / (channel * (2 * win + 1) * (2 * win + 1));
                    if((diffval2 - 2 * fSigma * fSigma) > 0)
                        max = (diffval2 - 2 * fSigma * fSigma);
                    else
                        max = 0;
                    omega = exp( -max / (h * h));
                    Cp += omega;
                    int ox = CLIP3(x + rx , 0, cs - 1);
                    int oy = CLIP3(y + ry , 0, rs - 1);
                    sum += omega * (int)(ptrimage1[ox + oy * cs]);
                }
            }
        
            ptrimage1[x + y * cs] = Cp == 0 ? ptrimage1[x + y * cs] : CLIP3((unsigned char)(sum / Cp), 0, 255);

        }
    }
    
    
    
    for(int y = win;y < rs - win;y++)
    {
        for(int x = win;x < cs - win;x++)
        {
            windowsum = 0;
            for(wy = -win; wy <= win;wy++)
            {
                for(wx = -win;wx <= win;wx++)
                {
            
                    px = CLIP3(x + wx, 0, cs - 1);
                    py = CLIP3(y + wy, 0, rs - 1);
                    windowsum += (int)(ptrimage1[px + py * cs]);
                }
            
            }
            meanpixel = (windowsum / ((2 * win + 1) * (2 * win + 1)));
        ptrimage1[x + y * cs] = (unsigned char)(meanpixel);
        }
        
    }
    return ptrimage1;
}





/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
  
    struct xvimage * image1;

    unsigned char *ptrimage1;
    unsigned char *ptrimage2;

    int px, py, cx, cy;
    int rs, cs, N;
    float diffval2 = 0;
    int channel = 1;
    float omega = 0;
    float sum = 0;
    float Cp;
//判断输入完整
  
    if (argc != 4)
  
    {
    
        fprintf(stderr, "pixelise imagein.pgm sigma image_out.pgm\n", argv[0]);
    
        exit(0);
  
    }
 
    
    
    
 
    image1 = readimage(argv[1]);
    int fSigma;
    fSigma = atoi(argv[2]);//初始化sigma
    if (image1 == NULL)
  
    {
    
        fprintf(stderr, "addconst: readimage failed\n");
    
        exit(0);
  
    }
    
    
  
  
    rs = image1->row_size;
  
    cs = image1->col_size;
  
    N = rs * cs;
    
    
  
    ptrimage1 = UCHARDATA(image1);  //ptrimage1  --> image1 data
  
    
    
    int bloc, win;
    float fFiltPar;//define variable

 

        if (fSigma > 0.0f && fSigma <= 15.0f) {
            win = 1;
            bloc = 10;
            fFiltPar = 0.4f;

        } else if ( fSigma > 15.0f && fSigma <= 30.0f) {
            win = 2;
            bloc = 10;
            fFiltPar = 0.4f;

        } else if ( fSigma > 30.0f && fSigma <= 45.0f) {
            win = 3;
            bloc = 17;
            fFiltPar = 0.35f;

        } else if ( fSigma > 45.0f && fSigma <= 75.0f) {
            win = 4;
            bloc = 17;
            fFiltPar = 0.35f;

        } else if (fSigma <= 100.0f) {

            win = 5;
            bloc = 17;
            fFiltPar = 0.30f;

        } else {
            printf("error :: algorithm parametrized only for values of sigma less than 100.0\n");
            exit(-1);
        }

    
    
    



    NLM(ptrimage1,cs,rs,bloc,win,fFiltPar,fSigma);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
   
    
    
    writeimage(image1, argv[3]);
  
    freeimage(image1);

 
}
