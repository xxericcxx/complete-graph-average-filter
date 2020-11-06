//
//  diffrgb.c
//  
//
//  Created by Eric on 2020/11/6.
//

//
//  main.c
//  iamge analyses
//
//  Created by Eric on 2020/10/28.
//  Copyright © 2020 Eric. All rights reserved.
//

/* Call to laddconst */
#include <stdint.h>
#include <stdio.h>
#include "src//lib//mcimage.h"
#include "src//lib//laddconst.h"
 
/* =============================================================== */
int main(int argc, char **argv)
/* =============================================================== */
{
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
  int indexpixel;
  unsigned long newval;
//判断输入完整
  if (argc != 4)
  {
    fprintf(stderr, "diffimage image1 image2 imageresult \n", argv[0]);
    exit(0);
  }
 
    
    
    
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

  for (indexpixel = 0; indexpixel < N; indexpixel++)
  {
    newval = (int)(ptrimage1[indexpixel]) - (int)(ptrimage4[indexpixel]);
    if (newval < NDG_MIN) newval = NDG_MIN;
    if (newval > NDG_MAX) newval = NDG_MAX;
    ptrimage1[indexpixel] = (unsigned char)newval;
  }

    for (indexpixel = 0; indexpixel < N; indexpixel++)
    {
      newval = (int)(ptrimage2[indexpixel]) - (int)(ptrimage5[indexpixel]);
      if (newval < NDG_MIN) newval = NDG_MIN;
      if (newval > NDG_MAX) newval = NDG_MAX;
      ptrimage2[indexpixel] = (unsigned char)newval;
    }
    for (indexpixel = 0; indexpixel < N; indexpixel++)
    {
      newval = (int)(ptrimage3[indexpixel]) - (int)(ptrimage6[indexpixel]);
      if (newval < NDG_MIN) newval = NDG_MIN;
      if (newval > NDG_MAX) newval = NDG_MAX;
      ptrimage3[indexpixel] = (unsigned char)newval;
    }

  

 writergbimage(g1,g2,g3, argv[3]);
  freeimage(g1);
  freeimage(g2);
  freeimage(g3);

} /* main */



