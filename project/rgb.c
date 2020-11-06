//
//  rgb.c
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
                
                    diffval2 = diffval2 / ((2 * win + 1) * (2 * win + 1));
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
    
    
    
  /*  for(int y = win;y < rs - win;y++)
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
                    //printf("%d\n",(int)(ptrimage1[px + py * cs]));
                }
            
            }
            meanpixel = (windowsum / ((2 * win + 1) * (2 * win + 1)));
            //printf("%f\n",meanpixel);
        ptrimage1[x + y * cs] = (unsigned char)(meanpixel);
        }
        
    }*/
    return ptrimage1;
}





/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
  
    struct xvimage * g1;
    struct xvimage * g2;
    struct xvimage * g3;

    unsigned char *ptrimage1;
    unsigned char *ptrimage2;
    unsigned char *ptrimage3;
    int px, py, cx, cy;
    int rs1, cs1, N1,rs2 ,cs2 ,N2, rs3, cs3, N3;
    float diffval2 = 0;
    float omega = 0;
    float sum = 0;
    float Cp;
//判断输入完整
  
    if (argc != 4)
  
    {
    
        fprintf(stderr, "pixelise imagein.ppm sigma image_out.pppm\n", argv[0]);
    
        exit(0);
  
    }
 
    
    
    if (readrgbimage(argv[1], &g1, &g2, &g3) == 0)
    {
      fprintf(stderr, "rgb2bw: readrgbimage failed\n");
      exit(1);
    }
 

    rs1 = g1->row_size;
    
    cs1 = g1->col_size;
    
    N1 = rs1 * cs1;
      
    ptrimage1 = UCHARDATA(g1);  //ptrimage1  --> image1 data
    
    rs2 = g2->row_size;
    
    cs2 = g2->col_size;
    
    N2 = rs2 * cs2;
      
    ptrimage2 = UCHARDATA(g2);  //ptrimage1  --> image1 data
    
    rs3 = g3->row_size;
    
    cs3 = g3->col_size;
    
    N3 = rs3 * cs3;
      
    ptrimage3 = UCHARDATA(g3);  //ptrimage1  --> image1 data
    
    
    int fSigma;
    fSigma = atoi(argv[2]);//初始化sigma

    
    
  
  
   
  
    
    
    int bloc, win;
    float fFiltPar;//define variable
         if (fSigma > 0.0f && fSigma <= 25.0f)
         {
                   win = 1;
                   bloc = 10;
                   fFiltPar = 0.55f;

               
         }
         else if (fSigma > 25.0f && fSigma <= 55.0f)
         {
                   win = 2;
                   bloc = 17;
                   fFiltPar = 0.4f;

               
         }
         else if (fSigma <= 100.0f)
         {
                   win = 3;
                   bloc = 17;
                   fFiltPar = 0.35f;
         }
         else
         {
                   printf("error :: algorithm parametrized only for values of sigma less than 100.0\n");
                   exit(-1);
            
         }
    
    
    



    NLM(ptrimage1,cs1,rs1,bloc,win,fFiltPar,fSigma);
    NLM(ptrimage2,cs2,rs2,bloc,win,fFiltPar,fSigma);
    NLM(ptrimage3,cs3,rs3,bloc,win,fFiltPar,fSigma);
    
    
    
    
    writergbimage(g1,g2,g3, argv[3]);
  
    freeimage(g1);
    freeimage(g2);
    freeimage(g3);

 
}
