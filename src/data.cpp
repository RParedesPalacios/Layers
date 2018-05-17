#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>

#include "Eigen/Dense"

#include "data.h"
#include "utils.h"
#include "layer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


using namespace Eigen;
using namespace std;


////////////////////////////////////
///// BASE DATA CLASS
////////////////////////////////////

Data::Data()
{
  dim=out=size=num=gen=0;

}


void Data::Mem() {

  idx=(int *)malloc(num*sizeof(int));
  for(int i=0;i<num;i++) idx[i]=i;

  M.resize(num,size);

  //float
  fmu=(float *)malloc(size*sizeof(int));
  fsd=(float *)malloc(size*sizeof(int));
  fmax=(float *)malloc(size*sizeof(int));
  fmin=(float *)malloc(size*sizeof(int));
  fbin=(int *)malloc(size*sizeof(int));
  freal=(int *)malloc(size*sizeof(int));
  fint=(int *)malloc(size*sizeof(int));

  for(int i=0;i<size;i++) {
    fbin[i]=0;
    freal[i]=1;
    fint[i]=0;
    fmu[i]=0.0;
    fsd[i]=1.0;
    fmax[i]=1.0;
    fmin[i]=0.0;
  }
}

Data::Data(int n,int d,int o,int b,char *name)
{
  num=n;
  dim=d;
  out=o;
  size=dim+out;
  gen=0;

  cp=0;
  strcpy(this->name,name);
  sprintf(fname,name);
  
  Mem();

  fprintf(stderr,"New Data %s %dx(%d+%d)\n",name,num,dim,out);

  head=0;
  batch=b;
  balance=0;
  init_balance=0;
}




// Binary
Data::Data(int bin,char *fname,int b,char *name)
{
  FILE *fe;
  unsigned char u;
  int i,j,fsc;

  float *fptr;
  int *iptr;
  cp=0;

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
  size=dim+out;
  gen=0;

  fprintf(stderr,"Reading %s %d %d %d\n",fname,num,dim,out);

  strcpy(this->name,name);
  strcpy(this->fname,fname);

  Mem();

  head=0;
  batch=b;
  balance=0;
  init_balance=0;
  fptr=(float *)malloc((dim+out)*sizeof(float ));

  for(i=0;i<num;i++) {
    if (feof(fe)) {fprintf(stderr,"Error reading line %d\n",i);exit(1);}
    int read=fread(fptr,sizeof(float),dim+out,fe);

    if (read!=(dim+out)) {
      fprintf(stderr,"Error reading file (%d!=%d)\nCheck format\n",read,dim+out);
      exit(1);
    }
    for(j=0;j<dim;j++) {
      M(i,j)=fptr[j];
    }

    for(j=0;j<out;j++) 
      M(i,j+dim)=fptr[dim+j];
    
  }
}

//Ascii
Data::Data(char *fname,int b,char *name)
{
FILE *fe;
  int i,j,k,fsc;
  float fv;

  cp=0;
  batch=b;
  head=0;
  balance=0;
  init_balance=0;
  strcpy(this->name,name);
  strcpy(this->fname,fname);

  fe=fopen(fname,"rt");
  if (fe==NULL) {
    fprintf(stderr,"%s not found\n",fname);
    exit(1);
  }

  fsc=fscanf(fe,"%d %d %d\n",&num,&dim,&out);
  fprintf(stderr,"Reading %s %d %d %d\n",this->name,num,dim,out);

  

 if (dim>0) {
   size=dim+out;
    Mem();

    for(i=0;i<num;i++) {
      for(j=0;j<dim;j++) {
	if (feof(fe)) {
	  fprintf(stderr,"Error reading file\nCheck format\n");
	  exit(1);
	}
	fsc=fscanf(fe,"%f ",&fv);
	M(i,j)=fv;
      }
      for(j=0;j<out;j++) {
	if (feof(fe)) {
	  fprintf(stderr,"Error reading file\nCheck format\n");
	  exit(1);
	}
	fsc=fscanf(fe,"%f ",&fv);
	M(i,j+dim)=fv;
      }
    }
    fclose(fe);
  }
  else {

    fprintf(stderr,"list mode\n");
    int res;
    int w=-1,h,n,w1,h1,n1;
    char fn[1024];
    
    fprintf(stderr,"checking image sizes...\n");
    for(i=0;i<num;i++) {
      fsc=fscanf(fe,"%s %f\n",fn,&fv);
      res = stbi_info(fn, &w1, &h1, &n1);
      
      if (w==-1) {
	w=w1;
	h=h1;
	n=n1;
      }
      else if ((w!=w1)||(h!=h1)||(n!=n1)){
	fprintf(stderr,"Error image sizes\n");
	exit(1);
      }
      fprintf(stderr,"%s\r",fn);
    }
    fclose(fe);
    
    fprintf(stderr,"\n%dx%d %d channels\n",w,h,n);
    
    dim=w*h*n;
    Mem();

    fe=fopen(fname,"rt");
    if (fe==NULL) {
      fprintf(stderr,"%s not found\n",fname);
      exit(1);
    }

    fsc=fscanf(fe,"%d %d %d\n",&num,&i,&out);
    fprintf(stderr,"Reading Images\n");

    unsigned char *data;
    int c;
    for(i=0;i<num;i++) {
      fsc=fscanf(fe,"%s %d\n",fn,&c);
      fprintf(stderr,"reading %s class=%d\r",fn,c);
      for(j=0;j<out; j++) M(i,j+dim)=0.0;
      M(i,dim+c)=1;

      data = stbi_load(fn, &w, &h, &n, 0);
      int p=0;
      for(k=0;k<n;k++)
	for(j=k;j<dim;j+=n,p++)
	  M(i,p)=data[j];
      
    }//for num
    fprintf(stderr,"\n");
  }//else list
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
      fprintf(fs,"%f ",M(i,j+dim));
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
      fv=M(i,j+dim);
      fwrite(&fv, sizeof(float),1,fs);
    }
  }

  fclose(fs);
  fprintf(stderr,"end writting bin file\n");

}

void Data::fillData(Data *D,int p)
{
  int i,j;

  for(i=0;i<batch;i++)
    for(j=0;j<dim;j++)
      D->M((p*batch)+i,j)=M(getpos(i),j);

}

//////////////////////////////////////////////
// DATA CREATORS
///////////////////////////////////////////////
void Data::limits(int &sini,int &sfin,int &dini,int &dfin)
{
  if (dini==-1) dini=1;
  if (dfin==-1) dfin=size;
  if (sini==-1) sini=1;
  if (sfin==-1) sfin=num;
  
  
  if (sini<1) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dini<1) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  if (sfin>num) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin>size) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
}


void Data::copyto(Data *D,int Dsini,int Dsfin,int Ddini,int Ddfin,int Dtype,int sini,int sfin,int dini,int dfin,int type) {
  int i,j,k;
  int *ind;

  //fprintf(stderr,"copyto (%d %d %d %d)-->(%d %d %d %d)\n",sini,sfin,dini,dfin,Dsini,Dsfin,Ddini,Ddfin);
  // Destination
  D->limits(Dsini,Dsfin,Ddini,Ddfin);

  if (Dsfin<Dsini) {fprintf(stderr,"copyto: Incorrect sizes\n");exit(1);}
  if (Ddfin<Ddini) {fprintf(stderr,"copyto: Incorrect sizes\n");exit(1);}

  // Source
  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"copyto: Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"copyto: Incorrect sizes\n");exit(1);}
  
  /*
    if (type==0) fprintf(stderr,"copy %s[%d:%d,%d:%d]->%s[%d:%d,%d:%d] only real\n",name,sini,sfin,dini,dfin,D->name,Dsini,Dsfin,Ddini,Ddfin);
    else if (type==1) fprintf(stderr,"copy %s[%d:%d,%d:%d]->%s[%d:%d,%d:%d] only bin\n",name,sini,sfin,dini,dfin,D->name,Dsini,Dsfin,Ddini,Ddfin);
    else if (type==2) fprintf(stderr,"copy %s[%d:%d,%d:%d]->%s[%d:%d,%d:%d] only int\n",name,sini,sfin,dini,dfin,D->name,Dsini,Dsfin,Ddini,Ddfin);
    else fprintf(stderr,"copy %s[%d:%d,%d:%d]->%s[%d:%d,%d:%d]\n",name,sini,sfin,dini,dfin,D->name,Dsini,Dsfin,Ddini,Ddfin);
  */

  dini--;sini--;
  dfin--;sfin--;
  
  Ddini--;Dsini--;
  Ddfin--;Dsfin--;
  
  
  // Check if sizes match
  // ROWS
  int n,Dn;
  n=(sfin-sini)+1;
  Dn=(Dsfin-Dsini)+1;
  if (n!=Dn) {fprintf(stderr,"Copy Incorrect row sizes %d!=%d\n",n,Dn);exit(1);}
  
  // COLS
  int ndim=0;
  for(j=dini;j<=dfin;j++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
      ndim++;

  int Dndim=0;
  for(j=Ddini;j<=Ddfin;j++) 
    if ((Dtype==-1)||((Dtype==0)&&(D->freal[j]))||((Dtype==1)&&(D->fbin[j]))||((Dtype==2)&&(D->fint[j])))
      Dndim++;

  if (ndim!=Dndim) {fprintf(stderr,"Copy Incorrect col sizes %d!=%d\n",ndim,Dndim);exit(1);}
  
  if (ndim==0) {fprintf(stderr,"void selection\n");exit(1);}

  /// CORRECT SIZES, go forward...
  //fprintf(stderr,"copy block %dx%d\n",(sfin-sini)+1,ndim);

  ind=(int *)malloc(ndim*sizeof(int));
  k=0;
  for(j=Ddini;j<=Ddfin;j++) 
    if ((Dtype==-1)||((Dtype==0)&&(D->freal[j]))||((Dtype==1)&&(D->fbin[j]))||((Dtype==2)&&(D->fint[j]))) {
      ind[k]=j;
      k++;
    }

  // Copy samples
  k=0;
  for(j=dini;j<=dfin;j++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j]))) {
      for(i=sini;i<=sfin;i++)
	D->M(D->idx[Dsini+(i-sini)],ind[k])=M(idx[i],j);
      k++;
    }

  // Copy stats if any
  k=0;
  for(j=dini;j<=dfin;j++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j]))) {
      D->fbin[ind[k]]=fbin[j];
      D->freal[ind[k]]=freal[j];
      D->fint[ind[k]]=fint[j];

      D->fmu[ind[k]]=fmu[j];
      D->fsd[ind[k]]=fsd[j];
      D->fmax[ind[k]]=fmax[j];
      D->fmin[ind[k]]=fmin[j];
      k++;
    }
  free(ind);
}
 

Data *Data::create(char *newn,int sini,int sfin,int dini,int dfin,int type) {
  int i,j,k;
  int si,sf,di,df;

  fprintf(stderr,"Create %s\n",newn);

  si=sini;sf=sfin;
  di=dini;df=dfin;

  // Source
  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  dini--;sini--;
  dfin--;sfin--;

  int ndim=0;
  int nout=0;
  for(j=dini;j<=dfin;j++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
      if (j<dim) ndim++;
      else nout++;

  Data *n=new Data((sfin-sini)+1,ndim,nout,batch,newn);
    
  copyto(n, -1,-1,-1,-1,-1,  si,sf,di,df,type);

  return n;
}

void Data::copyL(LMatrix N,int sini,int sfin,int dini,int dfin,int type) {
  int i,j,k;
  int si,sf,di,df;

  si=sini;sf=sfin;
  di=dini;df=dfin;

  // Source
  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  //fprintf(stderr,"copylayer to %s[%d:%d,%d:%d]\n",name,sini,sfin,dini,dfin);

  dini--;sini--;
  dfin--;sfin--;

  int ndim=0;
  int nout=0;
  for(j=dini;j<=dfin;j++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
      if (j<dim) ndim++;
      else nout++;

  int b=((sfin-sini)+1);
  if (b!=N.rows()) {
    fprintf(stderr,"Incorrect number of rows %d!=%d\n",b,N.rows());
    exit(1);
  }
  int d=nout+ndim;
  if (d!=N.cols()) {
    fprintf(stderr,"Incorrect number of cols %d!=%d\n",d,N.cols());
    exit(1);
  }

  int p=0;
  for(j=dini;j<=dfin;j++,p++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
      for(i=0;i<b;i++) 
	M(idx[sini+i],j)=N(i,p);

  
  //fprintf(stderr,"Layer copy %dx%d done\n",b,d);
      
}

//////////////////////////////////////////
void Data::set(double val,int sini,int sfin,int dini,int dfin,int type) {
  int i,j,k;
  int si,sf,di,df;

  si=sini;sf=sfin;
  di=dini;df=dfin;

  // source
  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  dini--;sini--;
  dfin--;sfin--;

  for(j=dini;j<=dfin;j++) 
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
      for(i=sini;i<=sfin;i++)
	M(idx[i],j)=val;

  return;
}

double Data::get(int s,int d) {

  if ((s>num)||(s<1)) {
    fprintf(stderr,"Error accesing row %d [1-%d]\n",s,num);
    exit(1);
  }
  if ((d>size)||(d<1)) {
    fprintf(stderr,"Error accesing col %d [1-%d]\n",d,size);
    exit(1);
  }

  
  return M(idx[s-1],d-1);
}
void Data::set(int s,int d,double val){

  if ((s>num)||(s<1)) {
    fprintf(stderr,"Error accesing row %d [1-%d]\n",s,num);
    exit(1);
  }
  if ((d>size)||(d<1)) {
    fprintf(stderr,"Error accesing col %d [1-%d]\n",d,size);
    exit(1);
  }


  M(idx[s-1],d-1)=val;
}



//////////////////////////////////////////

void Data::cat(Data *D) 
{
  int s=num+D->num;

  Data *aux=create(name,-1,-1,-1,-1,-1);
  Data *aux2=new Data(s,dim,out,batch,name);

  aux->copyto(aux2,1,aux->num,-1,-1,-1,   -1,-1,-1,-1,-1);
  D->copyto(aux2,aux->num+1,s,-1,-1,-1,   -1,-1,-1,-1,-1);

  num=s;
  Mem();
  init_balance=0;

  aux2->copyto(this,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1);

  delete aux;
  delete aux2;
}

void Data::paste(Data *D) 
{
  int s=dim+D->dim;

  Data *aux=create(name,-1,-1,-1,-1,-1);
  Data *aux2=new Data(num,s,out,batch,name);

  aux->copyto(aux2,-1,-1,1,aux->dim,-1,   -1,-1,-1,-1,-1);

  D->copyto(aux2,-1,-1,aux->dim+1,-1,-1,   -1,-1,-1,-1,-1);

  dim=s;
  size=dim+out;
  Mem();
  init_balance=0;

  aux2->copyto(this,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1);

  delete aux;
  delete aux2;
}

/////////////////////////////////////////////
// DATA STATS
/////////////////////////////////////////////
int Data::isBin(int f)
{
  float v1,v2;
  int dif=1;

  v1=M(0,f);

  for(int i=1;i<num;i++) 
    if (dif==1) {
      if (M(i,f)!=v1) {
	v2=M(i,f);
	dif=2;
      }
    }
    else {
      if ((M(i,f)!=v1)&&(M(i,f)!=v2)) return 0;
    }

  return 1;
}

int Data::isReal(int f)
{
  float fv;
  int iv;

  for(int i=0;i<num;i++) {
    iv=floor(M(i,f));
    fv=M(i,f);
    if (iv!=fv) 
      return 1;
  }
  return 0;
}



void Data::detect()
{
  int i;
  int b=0,r=0,n=0;
  
  
  for(int i=0;i<dim;i++) {
    if (isBin(i)) {freal[i]=0;fbin[i]=1;b++;}
    else if (isReal(i)) {r++;}
    else {freal[i]=0;fint[i]=1;n++;}
  }
  
  fprintf(stderr,"\n======= %s ========\n",name);
  fprintf(stderr,"size= %dx(%d+%d)\n",num,dim,out);
  fprintf(stderr,"Samples:\n");
  fprintf(stderr,"%d Binary feat\n",b);
  fprintf(stderr,"%d Real feat\n",r);
  fprintf(stderr,"%d Int feat\n",n);

  b=0;r=0;n=0;
  for(int i=dim;i<size;i++) {
    if (isBin(i)) {freal[i]=0;fbin[i]=1;b++;}
    else if (isReal(i)) {r++;}
    else {freal[i]=0;fint[i]=1;n++;}
  }
  fprintf(stderr,"Targets:\n");
  fprintf(stderr,"%d Binary feat\n",b);
  fprintf(stderr,"%d Real feat\n",r);
  fprintf(stderr,"%d Int feat\n",n);
  fprintf(stderr,"==================\n\n");
}


void Data::copystats(Data *D)
{
  cp=1;
  
  //fprintf(stderr,"Copy stats from %s to %s\n",D->name,name);

  for(int i=0;i<size;i++) {
   fbin[i]=D->fbin[i];
    freal[i]=D->freal[i];
    fint[i]=D->fint[i];

    fmu[i]=D->fmu[i];
    fsd[i]=D->fsd[i];
    fmax[i]=D->fmax[i];
    fmin[i]=D->fmin[i];
  }
}



/////////////////////////////////////////////
// DATA MANIPULATION
/////////////////////////////////////////////
void Data::zscore(int sini,int sfin,int dini,int dfin,int type) {
  int i,j;

  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  double m,sd;

  /*
  fprintf(stderr,"Zscore of %s\n",name);


  if (type==0) fprintf(stderr,"Zscore [%d:%d,%d:%d] only real\n",sini,sfin,dini,dfin);
  else if (type==1) fprintf(stderr,"Zscore [%d:%d,%d:%d] only bin\n",sini,sfin,dini,dfin);
  else if (type==2) fprintf(stderr,"Zscore [%d:%d,%d:%d] only int\n",sini,sfin,dini,dfin);
  else fprintf(stderr,"Zscore [%d:%d,%d:%d]\n",sini,sfin,dini,dfin);
  */
  
  dini--;sini--;
  dfin--;sfin--;
  
  int n=(sfin-sini)+1;

  for(j=dini;j<=dfin;j++) {
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j]))){
      if (!cp) {
	m=0.0;
	for(i=sini;i<=sfin;i++)
	  m+=M(idx[i],j);
	m/=n;

	fmu[j]=m;

	sd=0.0;
	for(i=sini;i<=sfin;i++)
	  sd+=(M(idx[i],j)-m)*(M(idx[i],j)-m);
	sd/=n;
	sd=sqrt(sd);

	fsd[j]=sd;
      }
      if (fsd[j]!=0.0)
	for(i=sini;i<=sfin;i++)
	  M(idx[i],j)=(M(idx[i],j)-fmu[j])/fsd[j];
      else {
	for(i=sini;i<=sfin;i++)
	  M(idx[i],j)=0.0;
      }
    }
  }
}

void Data::center(int sini,int sfin,int dini,int dfin,int type) {
  int i,j;
  double m;

  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  fprintf(stderr,"Center of %s\n",name);

  if (type==0)   fprintf(stderr,"Center [%d:%d,%d:%d] only real\n",sini,sfin,dini,dfin);
  else if (type==1)   fprintf(stderr,"Center [%d:%d,%d:%d] only bin\n",sini,sfin,dini,dfin);
  else if (type==2)   fprintf(stderr,"Center [%d:%d,%d:%d] only int\n",sini,sfin,dini,dfin);
  else fprintf(stderr,"Center [%d:%d,%d:%d]\n",sini,sfin,dini,dfin);

  dini--;sini--;
  dfin--;sfin--;

  int n=(sfin-sini)+1;
  for(j=dini;j<=dfin;j++) {
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j]))){
      if (!cp) {
	m=0.0;
	for(i=sini;i<=sfin;i++)
	  m+=M(idx[i],j);
	m/=n;

	fmu[j]=m;
      }
      for(i=sini;i<=sfin;i++)
	M(idx[i],j)=M(idx[i],j)-fmu[j];
    }
  }
}


void Data::maxmin(int sini,int sfin,int dini,int dfin,int type) {
  int i,j;
  double max,min;

  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  /*fprintf(stderr,"Maxmin of %s\n",name);

  if (type==0)   fprintf(stderr,"Maxmin [%d:%d,%d:%d] only real\n",sini,sfin,dini,dfin);
  else if (type==1)   fprintf(stderr,"Maxmin [%d:%d,%d:%d] only bin\n",sini,sfin,dini,dfin);
  else if (type==2)   fprintf(stderr,"Maxmin [%d:%d,%d:%d] only int\n",sini,sfin,dini,dfin);
  else fprintf(stderr,"Maxmin [%d:%d,%d:%d]\n",sini,sfin,dini,dfin);
  */
  
  dini--;sini--;
  dfin--;sfin--;

  int n=(sfin-sini)+1;
  for(j=dini;j<=dfin;j++) {
    if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j]))){
      if (!cp) {
	max=M(idx[sini],j);
	min=M(idx[sini],j);
	for(i=sini;i<=sfin;i++) {
	  if (M(idx[i],j)>max) max=M(idx[i],j);
	  if (M(idx[i],j)<min) min=M(idx[i],j);
	}

	fmax[j]=max;
	fmin[j]=min;
      }
      if (fmax[j]!=fmin[j]) 
	for(i=sini;i<=sfin;i++)
	  M(idx[i],j)=(M(idx[i],j)-fmin[j])/(fmax[j]-fmin[j]);
      else
	for(i=sini;i<=sfin;i++)
	  M(idx[i],j)=0.0;
    }
    
  }
}

// ONLY FOR IMAGES
void Data::YUV()
{
  int i,j;
  int s;
  double r,g,b;
  double y,u,v;

  // it assumes that there are three channels R-G-B
  if ((dim%3)!=0) {
    fprintf(stderr,"%s does not seem to be RGB data\n",name);
    exit(1);
  }

  fprintf(stderr,"%s YUV\n",name);
  s=dim/3;
  for(i=0;i<num;i++) {
    for(j=0;j<s;j++) {

      r=M(idx[i],j);
      g=M(idx[i],j+s);
      b=M(idx[i],j+2*s);

      y=0.299*r+0.587*g+0.114*b;
      u=-0.147*r-0.289*g+0.436*b;
      v=0.615*r-0.515*g-0.100*b;

      M(idx[i],j)=y;
      M(idx[i],j+s)=u;
      M(idx[i],j+2*s)=v;
    }

  }

}


/////////////////////////////////////////////
// BASIC OPERATIONS
/////////////////////////////////////////////
void Data::add(double val,int sini,int sfin,int dini,int dfin,int type) {
  int i,j;

  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}


  fprintf(stderr,"Add over %s %f\n",name,val);
  if (type==0)   fprintf(stderr,"Add [%d:%d,%d:%d] only real\n",sini,sfin,dini,dfin);
  else if (type==1)   fprintf(stderr,"Add [%d:%d,%d:%d] only bin\n",sini,sfin,dini,dfin);
  else if (type==2)   fprintf(stderr,"Add [%d:%d,%d:%d] only int\n",sini,sfin,dini,dfin);
  else fprintf(stderr,"Add [%d:%d,%d:%d]\n",sini,sfin,dini,dfin);

  dini--;sini--;
  dfin--;sfin--;

  if (val!=0.0)
    for(i=sini;i<=sfin;i++)
      for(j=dini;j<=dfin;j++) {
	if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
	  M(idx[i],j)+=val;
      }
}


void Data::sub(double val,int sini,int sfin,int dini,int dfin,int type)
{
  int i,j;

  add(-val,sini,sfin,dini,dfin,type);
}

void Data::div(double val,int sini,int sfin,int dini,int dfin,int type) {
  int i,j;

  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}


  fprintf(stderr,"Div over %s %f\n",name,val);
  if (type==0)   fprintf(stderr,"Div [%d:%d,%d:%d] only real\n",sini,sfin,dini,dfin);
  else if (type==1)   fprintf(stderr,"Div [%d:%d,%d:%d] only bin\n",sini,sfin,dini,dfin);
  else if (type==2)   fprintf(stderr,"Div [%d:%d,%d:%d] only int\n",sini,sfin,dini,dfin);
  else fprintf(stderr,"Div [%d:%d,%d:%d]\n",sini,sfin,dini,dfin);

  dini--;sini--;
  dfin--;sfin--;

  if (val!=0.0)
    for(i=sini;i<=sfin;i++)
      for(j=dini;j<=dfin;j++) {
	if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
	  M(idx[i],j)/=val;
      }
}

void Data::mul(double val,int sini,int sfin,int dini,int dfin,int type) {
  int i,j;

  limits(sini,sfin,dini,dfin);

  if (sfin<sini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}
  if (dfin<dini) {fprintf(stderr,"Incorrect sizes\n");exit(1);}

  /*
  fprintf(stderr,"Mul over %s %f\n",name,val);
  if (type==0)   fprintf(stderr,"Mul [%d:%d,%d:%d] only real\n",sini,sfin,dini,dfin);
  else if (type==1)   fprintf(stderr,"Mul [%d:%d,%d:%d] only bin\n",sini,sfin,dini,dfin);
  else if (type==2)   fprintf(stderr,"Mul [%d:%d,%d:%d] only int\n",sini,sfin,dini,dfin);
  else fprintf(stderr,"Mul [%d:%d,%d:%d]\n",sini,sfin,dini,dfin);
  */
  
  dini--;sini--;
  dfin--;sfin--;

  for(i=sini;i<=sfin;i++)   
    for(j=dini;j<=dfin;j++) 
      if ((type==-1)||((type==0)&&(freal[j]))||((type==1)&&(fbin[j]))||((type==2)&&(fint[j])))
	M(idx[i],j)*=val;
          
}

////////////////////////////
// CONTROLING POSITION
// AND SHUFFLING
////////////////////////////
int Data::getpos(int p)
{
  return idx[(head+p)%num];
}

void Data::shuffle()
{
  int *ind;
  int i,j,s,k,l;


  //fprintf(stderr,"Shuffle %s\n",name);

  if (!balance) {
    for(i=0;i<num;i++)
      idx[i]=i;

    //shuffle idx
    for(i=0;i<num;i++) {
      int temp=idx[i];
      int r=rand()%num;

      idx[i]=idx[r];
      idx[r]=temp;
    }
  }
  else {
    fprintf(stderr,"Balancing classes\n");

    if (!init_balance) {
      init_balance=1;

      bci=(int **)malloc(out*sizeof(int*));
      bcc=(int *)malloc(out*sizeof(int));
      for(j=0;j<out;j++) bcc[j]=0;

      for(i=0;i<num;i++)
	for(j=0;j<out;j++) {
	  if (M(i,j+dim)==1) bcc[j]++;
	}

      for(j=0;j<out;j++) {
	fprintf(stderr,"Class %d : %d\n",j,bcc[j]);

	bci[j]=(int *)malloc(bcc[j]*sizeof(int));

	int c=0;
	for(i=0;i<num;i++)
	  if (M(i,j+dim)==1) {
	    bci[j][c]=i;
	    c++;
	  }
      }
    }


    // Fill idx whith class-balanced indexes
    s=num/out;
    for(k=0;k<out-1;k++) {
      for(i=k*s;i<(k+1)*s;i++) {
	j=rand()%bcc[k];
	idx[i]=bci[k][j];
      }
    }
    // last class because num%out couldn't be 0
    for(i=k*s;i<num;i++) {
      j=rand()%bcc[k];
      idx[i]=bci[k][j];
    }


    //shuffle idx
    for(i=0;i<num;i++) {
      int temp=idx[i];
      int r=rand()%num;

      idx[i]=idx[r];
      idx[r]=temp;
    }

    int *v=(int *)malloc(out*sizeof(int));
    for(i=0;i<out;i++)
      v[i]=0;
    for(i=0;i<num;i++) {
      for(j=0;j<out;j++)
	if (M(idx[i],j+dim)==1) v[j]++;
    }
    //for(j=0;j<out;j++)
    //  fprintf(stderr,"Class %d ---> %d\n",j,v[j]);

    free(v);
  }
  head=0;
}


void Data::preparebatch(int code)
{
  head=0;

  if (code==1) shuffle();
  else for(int i=0;i<num;i++) idx[i]=i;

}
void Data::next()
{
  int c;

  if (head>=num-batch) {
    head=0;
  }
  else head+=batch;
}


void Data::setbalance(int b)
{
  balance=b;
}










////////////////////////////////////////////////
/// GENERATIVE 
////////////////////////////////////////////////
////////////////////////////////////////////////
/*class GData : public Data {
  public:
  GData();
  GData(int n,int d,int o,int b,char *name);
  
  void next();
  
  };
*/

GData::GData()
{
  num=dim=type=0;
  gen=1;
  size=dim+out;
  head=0;
  param=-1;

}
GData::GData(int n,int d,int t,int p,char *name)
{
  num=n;//should be batch size
  dim=d;
  out=0; // By defaulta Generative data is Source Data
  gen=1;
  param=p;
  size=dim+out;
  type=t;
  head=0;
  strcpy(this->name,name);

  if (type==0) { /// zeros
    fprintf(stderr,"Creating generative zeros data %s %dx%d\n",name,num,dim);
  }
  else if (type==1) { /// ones
    fprintf(stderr,"Creating generative ones data %s %dx%d\n",name,num,dim);
  }
  else if (type==2) { /// gauss
    fprintf(stderr,"Creating generative gauss data %s %dx%d\n",name,num,dim);
  }
  else if (type==3) { /// uniform
    fprintf(stderr,"Creating generative uniform data %s %dx%d\n",name,num,dim);
  }
  else if (type==4) { /// suniform
    fprintf(stderr,"Creating generative suniform data %s %dx%d\n",name,num,dim);
  }
  else if (type==5) { /// one_hot
    fprintf(stderr,"Creating generative one-hot data %s,%d %dx%d\n",name,param,num,dim);
  }

  Mem();
}


void GData::next() 
{
  int i,j,k;

  if (type==0) { /// zeros
    for(i=0;i<num;i++)
      for(j=0;j<size;j++)
	M(i,j)=0.0;
  }
  if (type==1) { /// ones
    for(i=0;i<num;i++)
      for(j=0;j<size;j++)
	M(i,j)=1.0;
  }
  if (type==2) { /// gauss
    for(i=0;i<num;i++)
      for(j=0;j<size;j++)
	M(i,j)=gaussgen();
  }
  if (type==3) { /// uniform
    for(i=0;i<num;i++)
      for(j=0;j<size;j++) 
	M(i,j)=uniform();
  }

  if (type==4) { /// suniform
    for(i=0;i<num;i++)
      for(j=0;j<size;j++)
	M(i,j)=suniform();
  }
  if (type==5) { /// onehot
    fprintf(stderr,"generating one-hot %d\n",param);
    for(i=0;i<num;i++) {
      for(j=0;j<size;j++)
	M(i,j)=0.0;
      if (param==-1) j=rand()%size;
      else j=param-1;
      M(i,j)=1.0;
    }
  }
}
