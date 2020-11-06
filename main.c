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
  int constante;
 
  if (argc != 4)
  {
    fprintf(stderr, "usage: %s in1.pgm constante out.pgm \n", argv[0]);
    exit(0);
  }
 
  image1 = readimage(argv[1]);
  if (image1 == NULL)
  {
    fprintf(stderr, "addconst: readimage failed\n");
    exit(0);
  }
  constante = atoi(argv[2]);
 
  if (! laddconst(image1, constante))
  {
    fprintf(stderr, "addconst: function laddconst failed\n");
    exit(0);
  }
 
  writeimage(image1, argv[3]);
  freeimage(image1);
 
} /* main */

