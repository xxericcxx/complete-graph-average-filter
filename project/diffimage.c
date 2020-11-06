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
  struct xvimage * image1;
  struct xvimage * image2;

  int constante;
  unsigned char *ptrimage1;
  unsigned char *ptrimage2;

  int rs, cs, N;
  int indexpixel;
  unsigned long newval;
//判断输入完整
  if (argc != 4)
  {
    fprintf(stderr, "diffimage image1 image2 imageresult \n", argv[0]);
    exit(0);
  }
 
    
    
    
  image1 = readimage(argv[1]);
  if (image1 == NULL)
  {
    fprintf(stderr, "addconst: readimage failed\n");
    exit(0);
  }
    
  
    
  image2 = readimage(argv[2]);
  if (image2 == NULL)
  {
    fprintf(stderr, "addconst: readimage failed\n");
    exit(0);
  }
 
  
  rs = image1->row_size;
  cs = image1->col_size;
  N = rs * cs;
    
    
  ptrimage1 = UCHARDATA(image1);  //ptrimage1  --> image1 data
  ptrimage2 = UCHARDATA(image2);
  for (indexpixel = 0; indexpixel < N; indexpixel++)
  {
    newval = (int)(ptrimage1[indexpixel]) - (int)(ptrimage2[indexpixel]);
    if (newval < NDG_MIN) newval = NDG_MIN;
    if (newval > NDG_MAX) newval = NDG_MAX;
    ptrimage1[indexpixel] = (unsigned char)newval;
  }


  

  writeimage(image1, argv[3]);
  freeimage(image1);
    freeimage(image2);

 
} /* main */


