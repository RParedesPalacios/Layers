#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Dense"


#include "data.h"

using namespace Eigen;
using namespace std;

////////////////////////////////////
///// BASE DATA CLASS
////////////////////////////////////

Data::Data()
{
 
}
Data::Data(int n,int d,int o,int b,char *name)
{
  num=n;
  dim=d;
  out=o;
  strcpy(this->name,name);
  sprintf(fname,"newdata");

  M.resize(num,dim);
  T.resize(num,out);
  head=0;
  batch=b;
}

// Binary
Data::Data(int bin,char *fname,int b,char *name)
{
  FILE *fe;
  unsigned char u;
  int i,j,fsc;
  
  float *fptr;
  int *iptr;

  fprintf(stderr,"Reading bin file %s\n",fname);

  fe=fopen(fname,"rb");
  if (fe==NULL) {
    fprintf(stderr,"%s not found\n",fname);
    exit(1);
  }
  iptr=(int *)malloc(3*sizeof(int));

  int read=fread(iptr,sizeof(int),3,fe);
  num=iptr[0];
  dim=iptr[1];
  out=iptr[2];
  
  fprintf(stderr,"Reading %s %d %d %d\n",fname,num,dim,out);

  strcpy(this->name,name);
  strcpy(this->fname,fname);

  M.resize(num,dim);
  T.resize(num,out);
  head=0;
  batch=b;

  fptr=(float *)malloc((dim+out)*sizeof(float));

  for(i=0;i<num;i++) {
    if (feof(fe)) {fprintf(stderr,"Error reading line %d\n",i);exit(1);}
    int read=fread(fptr,sizeof(float),dim+out,fe);
    
    for(j=0;j<dim;j++) {
      M(i,j)=fptr[j];
    }

    for(j=0;j<out;j++)
      T(i,j)=fptr[dim+j];
  }

}

//Ascii
Data::Data(char *fname,int b,char *name)
{
  FILE *fe;
  int i,j,fsc;
  float fv;
 

    
  batch=b;
  head=0;
  strcpy(this->name,name);
  strcpy(this->fname,fname);

  fe=fopen(fname,"rt");
  if (fe==NULL) {
    fprintf(stderr,"%s not found\n",fname);
    exit(1);
  }
    
  fsc=fscanf(fe,"%d %d %d\n",&num,&dim,&out);
  fprintf(stderr,"Reading %s %d %d %d\n",this->name,num,dim,out);


  M.resize(num,dim);
  T.resize(num,out);
  
  for(i=0;i<num;i++) {
    for(j=0;j<dim;j++) {
      fsc=fscanf(fe,"%f ",&fv);
      M(i,j)=fv;
    }
    for(j=0;j<out;j++) {
      fsc=fscanf(fe,"%f ",&fv);
      T(i,j)=fv;
    }
    //cout<<T.row(i)<<endl;
    //getchar();
  }
 
  fclose(fe);
}

void Data::Save(char *fname)
{
  FILE *fs;
  int i,j;

  fs=fopen(fname,"wt");
  

  fprintf(fs,"%d %d %d\n",num,dim,out);

  for(i=0;i<num;i++) {
    for(j=0;j<dim;j++) 
      fprintf(fs,"%f ",M(i,j));

    for(j=0;j<out;j++) 
      fprintf(fs,"%f ",T(i,j));    
    fprintf(fs,"\n");
  }
 
  fclose(fs);
  
}

void Data::SaveBin(char *fname)

{
  FILE *fs;
  int i,j;
  float fv;

  fs=fopen(fname,"wb");
  
  fprintf(stderr,"writting bin file\n");

  fwrite(&num, sizeof(int),1,fs);
  fwrite(&dim, sizeof(int),1,fs);
  fwrite(&out, sizeof(int),1,fs);


  for(i=0;i<num;i++) {
    for(j=0;j<dim;j++) {
      fv=M(i,j);
      fwrite(&fv, sizeof(float),1,fs);
    }
    for(j=0;j<out;j++) {
      fv=T(i,j);
      fwrite(&fv, sizeof(float),1,fs);
    }
  }
 
  fclose(fs);
  fprintf(stderr,"end writting bin file\n");
  
}

void Data::div(float val) 
{
  int i,j;

  if (val!=0.0) 
    for(i=0;i<num;i++) 
      for(j=0;j<dim;j++) 
	M(i,j)/=val;
}

void Data::zscore() 
{
  int i,j;
  float m,sd;
  
  fprintf(stderr,"Zscore of %s\n",name);

  inmu.resize(1,dim);
  insd.resize(1,dim);

  for(j=0;j<dim;j++) {
    m=0.0;
    for(i=0;i<num;i++) 
      m+=M(i,j);
    m/=num;

    inmu(0,j)=m;

    sd=0.0;
    for(i=0;i<num;i++) 
      sd+=(M(i,j)-m)*(M(i,j)-m);
    sd/=num;
    sd=sqrt(sd);
    
    insd(0,j)=sd;

    if (sd!=0.0)
      for(i=0;i<num;i++) 
	M(i,j)=(M(i,j)-m)/sd;
    else {
      for(i=0;i<num;i++) 
	M(i,j)=0.0;
    }
  }
}

void Data::center() 
{
  int i,j;
  float m;
  
  fprintf(stderr,"Center of %s\n",name);

  inmu.resize(1,dim);


  for(j=0;j<dim;j++) {
    m=0.0;
    for(i=0;i<num;i++) 
      m+=M(i,j);
    m/=num;

    inmu(0,j)=m;

    for(i=0;i<num;i++) 
      M(i,j)=M(i,j)-inmu(0,j);

    }

}

void Data::zscore(Data *D) 
{
  int i,j;


  fprintf(stderr,"Zscore of %s from Data...\n",name);

  inmu.resize(1,dim);
  insd.resize(1,dim);

  inmu=D->inmu;
  insd=D->insd;

  for(j=0;j<dim;j++) 
    for(i=0;i<num;i++) 
      if (insd(0,j)!=0.0)
	M(i,j)=(M(i,j)-inmu(0,j))/insd(0,j);
      else 
	M(i,j)=0.0;
   
}


void Data::YUV() 
{
  int i,j;
  int s;
  float r,g,b;
  float y,u,v;

  // it assumes that there are three channels R-G-B
  if ((dim%3)!=0) {
    fprintf(stderr,"%s does not seem to be RGB data\n",name);
    exit(1);
  }

  fprintf(stderr,"RGB->YUV\n");
  s=dim/3;
  for(i=0;i<num;i++) {
    for(j=0;j<s;j++) {

      r=M(i,j);
      g=M(i,j+s);
      b=M(i,j+2*s);

      y=0.299*r+0.587*g+0.114*b;
      u=-0.147*r-0.289*g+0.436*b;
      v=0.615*r-0.515*g-0.100*b;
      
      M(i,j)=y;
      M(i,j+s)=u;
      M(i,j+2*s)=v;
    }
      
  }
    
}


void Data::center(Data *D) 
{
  int i,j;


  fprintf(stderr,"Center of %s from Data...\n",name);

  inmu.resize(1,dim);

  inmu=D->inmu;

  for(j=0;j<dim;j++) 
    for(i=0;i<num;i++) 
      M(i,j)=M(i,j)-inmu(0,j);
    
}


void Data::shuffle()
{
  
  MatrixXf M2(num,dim);
  MatrixXf T2(num,out);
  int *ind;
  int i,j;
  
  fprintf(stderr,"Shuffle %s\n",name);

  ind=(int *)malloc(num*sizeof(int));
  for(i=0;i<num;i++)
    ind[i]=-1;

  for(i=0;i<num;i++) {
    j=rand()%num;
    for(;ind[j]!=-1;j=rand()%num);
    ind[j]=i;
  }
   
  for(i=0;i<num;i++) {
    M2.row(i)=M.row(ind[i]);
    T2.row(i)=T.row(ind[i]);
  }

  M=M2;
  T=T2;
  //fprintf(stderr,"done\n");

}

void Data::preparebatch(int code)
{
  head=0;

  if (code==1) shuffle();

}
void Data::next()
{
  int c;

  if (head>=num-batch) {
    head=0;
  }
  else head+=batch;
}

int Data::gethead()
{
  return head;
}
