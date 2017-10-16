#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>


#include "data.h"

int main(int argc, char **argv) {

  char cad[1000];

  if (argc<2) {
    fprintf(stderr,"bin2ascii datafile\n");
    exit(1);
  }

  Data *d=new Data(1,argv[1],1,"tmp");

  sprintf(cad,"%s.ascii",argv[1]);

  d->Save(cad);

}
