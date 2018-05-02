#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>


#include "data.h"

int main(int argc, char **argv) {

  char cad[1000];
  char name[1000];

  strcpy(name,"tmp");
  
  if (argc<2) {
    fprintf(stderr,"ascii2bin datafile\n");
    exit(1);
  }

  Data *d=new Data(argv[1],1,name);

  sprintf(cad,"%s.bin",argv[1]);

  d->SaveBin(cad);

  Data *d2=new Data(1,cad,1,name);


}
