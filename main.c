#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
typedef union{unsigned int z;unsigned char b[4]}bytes;
void memorie_externa(char *nume_fisier_ext,int* width,int* height,unsigned char** redsub,unsigned char** greensub,unsigned char** bluesub,unsigned char** header)
{  // printf("\n XORARE PIXEL0: RED0:%u GREEN0:%u BLUE0:%u \n",(*redsub)[0],(*greensub)[0],(*bluesub)[0]);

    FILE *f;
    f=fopen(nume_fisier_ext,"wb");
    unsigned char x;
    if (f==NULL)printf("Fisierul s-a deschis incorect\n");
    int i=0;
    for(i=0; i<=53; i++)
    {
        x=(*header)[i];

        fwrite(&x,sizeof(unsigned char),1,f)
        ;}
        unsigned char* vect;
        vect=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
       int padding=0;
       while ((*width * 3 + padding) % 4 != 0)
        padding++;
    printf("Padding= %d \n",padding);
        i=(*height)-1;
       int j=0;int contor=0,pad=0;
       int k=0;

    unsigned char** matrice;
    matrice=(unsigned char**)malloc((*height)*sizeof(unsigned char*));
    for(i=0;i<=(*height)-1;i++)matrice[i]=(unsigned char*)malloc((*width)*3*sizeof(unsigned char));
    for(i=(*height)-1;i>=0;i--)for(j=0;j<=(*width)*3-1;j=j+3){
        x=(*bluesub)[k];
        matrice[i][j]=x;

        x=(*greensub)[k];
        matrice[i][j+1]=x;

        x=(*redsub)[k];
        matrice[i][j+2]=x;k++;}
    k=0;
    for(i=0;i<=(*height)-1;i++)for(j=0;j<=(*width)*3-1;j=j+3){
        x=matrice[i][j];fwrite(&x,sizeof(unsigned char),1,f);
        //if(i==(*height)-1&&j==0)printf("PIXEL TRANSMIS= %u",x);
        x=matrice[i][j+1];fwrite(&x,sizeof(unsigned char),1,f);
        //if(i==(*height)-1&&j==0)printf("PIXEL TRANSMIS= %u",x);
        x=matrice[i][j+2];fwrite(&x,sizeof(unsigned char),1,f);
        //if(i==(*height)-1&&j==0)printf("PIXEL TRANSMIS= %u",x);

    if(j==(*width)*3-3){pad=0;while(pad<padding){x=0;fwrite(&x,sizeof(unsigned char),1,f);pad++;}pad=0;}}



  /*  for(i=0;i<=(*height)-1;i++)for(j=0;j<=(*width)*3-1;j=j+3){
        x=(*bluesub)[k];
        matrice[i][j]=x;

        x=(*greensub)[k];
        matrice[i][j+1]=x;

        x=(*redsub)[k];
        matrice[i][j+2]=x;k++;}
    k=0;
    for(i=(*height)-1;i>=0;i--)for(j=0;j<=(*width)*3-1;j=j+3){
        x=matrice[i][j];fwrite(&x,sizeof(unsigned char),1,f);
        if(i==(*height)-1&&j==0)printf("PIXEL TRANSMIS= %u",x);
        x=matrice[i][j+1];fwrite(&x,sizeof(unsigned char),1,f);
        if(i==(*height)-1&&j==0)printf("PIXEL TRANSMIS= %u",x);
        x=matrice[i][j+2];fwrite(&x,sizeof(unsigned char),1,f);
        if(i==(*height)-1&&j==0)printf("PIXEL TRANSMIS= %u",x);
    if(j==(*width)*3-3){pad=0;while(pad<padding){x=0;fwrite(&x,sizeof(unsigned char),1,f);pad++;}pad=0;}}
*/
    fclose(f);
}
void test_chi(int* width,int* height,unsigned char** red,unsigned char** green,unsigned char** blue,unsigned char** redsub,unsigned char** greensub,unsigned char** bluesub)
{
    double chi=0;
    double sumared=0,sumagreen=0,sumablue=0;
    double num=0;
    double redf[256],greenf[256],bluef[256];int i,j;

    for(i=0;i<=255;i++){redf[i]=0;greenf[i]=0;bluef[i]=0;}
    double fmediu=0;
    fmediu=((*width)*(*height))/256;
   // printf("\n fmediu = %f\n",fmediu);
    for(i=0;i<=255;i++){

        for(j=0;j<=(*width)*(*height)-1;j++){
            if(i==(*red)[j])redf[i]++;
            if(i==(*green)[j])greenf[i]++;
            if(i==(*blue)[j])bluef[i]++;
        }
        num=redf[i]-fmediu;
        num=num*num;
        num=num/fmediu;
        sumared=sumared+num;
        num=0;
        num=greenf[i]-fmediu;
        num=num*num;
        num=num/fmediu;
        sumagreen=sumagreen+num;
        num=0;
        num=bluef[i]-fmediu;
        num=num*num;
        num=num/fmediu;
        sumablue=sumablue+num;
        num=0;
    }
    printf("\n Testul Chi Patrat pentru imaginea originala: \n");
    printf("\nRED: %f  GREEN: %f  BLUE: %f\n",sumared,sumagreen,sumablue);

 for(i=0;i<=255;i++){redf[i]=0;greenf[i]=0;bluef[i]=0;}
    fmediu=((*width)*(*height))/256;
    printf("\n fmediu = %f\n",fmediu);
    sumared=0;
    sumablue=0;
    sumagreen=0;
    for(i=0;i<=255;i++){

        for(j=0;j<=(*width)*(*height)-1;j++){
            if(i==(*redsub)[j])redf[i]++;
            if(i==(*greensub)[j])greenf[i]++;
            if(i==(*bluesub)[j])bluef[i]++;
        }
        num=redf[i]-fmediu;
        num=num*num;
        num=num/fmediu;
        sumared=sumared+num;
        num=0;
        num=greenf[i]-fmediu;
        num=num*num;
        num=num/fmediu;
        sumagreen=sumagreen+num;
        num=0;
        num=bluef[i]-fmediu;
        num=num*num;
        num=num/fmediu;
        sumablue=sumablue+num;
        num=0;
    }
    printf("\n Testul Chi Patrat pentru imaginea criptata: \n");
    printf("\nRED: %f  GREEN: %f  BLUE: %f\n",sumared,sumagreen,sumablue);
}
uint32_t xorshift32(uint32_t state)
{

    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
}

void decriptare(unsigned char** redsub,unsigned char** greensub,unsigned char** bluesub,unsigned int*SV,unsigned long int**R,int*width,int*height,unsigned int** inv,unsigned char**redcr,unsigned char **greencr,unsigned char**bluecr)
{
    int i;
        for(i=1; i<=2*(*width)*(*height)-1; i++)
        (*R)[i]=xorshift32((*R)[i-1]);
    unsigned char x0,x1,x2,x3,x4,x5;
    //   printf("SV= %u",(*SV));
    //   printf("R0= %u",(*R)[0]);

    bytes t;
    t.z=(*SV);
    x0=t.b[0];
    x1=t.b[1];
    x2=t.b[2];

    unsigned int wh=(*width)*(*height);

    t.z=(*R)[wh];
    x3=t.b[0];
    x4=t.b[1];
    x5=t.b[2];

   unsigned char *redp,*bluep,*greenp;
    redp=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    bluep=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    greenp=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));


     unsigned char y;
    y=(*redsub)[0]^x2;
    redp[0]=y;
    y=(*greensub)[0]^x1;
    greenp[0]=y;
    y=(*bluesub)[0]^x0;
    bluep[0]=y;
    redp[0]=redp[0]^x5;
    greenp[0]=greenp[0]^x4;
    bluep[0]=bluep[0]^x3;



    for(i=1; i<=(*width)*(*height)-1; i++)
    {
        redp[i]=(*redsub)[i-1]^(*redsub)[i];
        greenp[i]=(*greensub)[i-1]^(*greensub)[i];
        bluep[i]=(*bluesub)[i-1]^(*bluesub)[i];
    }

        for(i=1; i<=(*width)*(*height)-1; i++){
        x0=0;
        x1=0;
        x2=0;

        t.z=(*R)[wh+i];
        x0=t.b[0];
        x1=t.b[1];
        x2=t.b[2];

        redp[i]=x2^redp[i];
        greenp[i]=x1^greenp[i];
        bluep[i]=x0^bluep[i];

        }


    unsigned int* P1; int aux,indice;
     P1=(unsigned int*)malloc((*width)*(*height)*3*sizeof(unsigned int));
      for(i=(*width)*(*height)-1; i>=0; i--)P1[i]=i;
int     j=1;
     for(i=(*width)*(*height)-1; i>=0; i--)
    {
        indice = (*R)[j] % (i+1);
        aux=P1[i];
        P1[i]=P1[indice];            //generarea permutarii
        P1[indice]=aux;
        j++;
    }
    *inv=(unsigned int*)malloc((*width)*(*height)*sizeof(unsigned int));
     for(i=(*width)*(*height)-1; i>=0; i--)
        (*inv)[P1[i]]=i;

     *redcr=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    *bluecr=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    *greencr=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
        unsigned int k;
        for(i=(*width)*(*height)-1; i>=0; i--)
    {
        k=(*inv)[i];

        (*redcr)[k]=redp[i];
        (*greencr)[k]=greenp[i];
        (*bluecr)[k]=bluep[i];
}

}
void xorare(unsigned int *SV,unsigned char**redsub,unsigned char**greensub,unsigned char**bluesub,unsigned long int** R,int *width,int* height,unsigned char** header)
{
    printf("\nSV= %d \n R0= %d \n",*SV,(*R)[0]);
    unsigned long int res=0;
    int i;
    unsigned int x0=0,x1=0,x2=0,x3=0,x4=0,x5=0;

    bytes t;
    t.z=(*SV);
    x0=t.b[0];
    x1=t.b[1];
    x2=t.b[2];

    unsigned int wh=(*width)*(*height);
    printf("\n \n \nR DE W*H ESTE %u\n \n \n",(*R)[wh]);
    t.z=(*R)[wh];
    x3=t.b[0];
    x4=t.b[1];
    x5=t.b[2];

    (*redsub)[0]=  (*redsub)[0]^x2;
    (*greensub)[0]=(*greensub)[0]^x1;            /// XOREZ PIXEL0
    (*bluesub)[0]= (*bluesub)[0]^x0;
    (*redsub)[0]=  (*redsub)[0]^x5;
    (*greensub)[0]=(*greensub)[0]^x4;
    (*bluesub)[0]= (*bluesub)[0]^x3;


    for(i=1; i<=(*width)*(*height)-1; i++)
    {
        (*redsub)[i]=(*redsub)[i-1]^(*redsub)[i];
        (*greensub)[i]=(*greensub)[i-1]^(*greensub)[i];
        (*bluesub)[i]=(*bluesub)[i-1]^(*bluesub)[i];

        x0=0;
        x1=0;
        x2=0;
        t.z=(*R)[wh+i];
        x0=t.b[0];
        x1=t.b[1];
        x2=t.b[2];

        (*redsub)[i]=x2^(*redsub)[i];
        (*greensub)[i]=x1^(*greensub)[i];             ///XOREZ CEILALTI PIXELI
        (*bluesub)[i]=x0^(*bluesub)[i];

        }

}


void criptare(char *fisier_text,int *width,int *height,unsigned char** redsub,unsigned char** bluesub,unsigned char** greensub,unsigned char** header,unsigned char** red,unsigned char** blue,unsigned char** green,unsigned long int **R,unsigned int*SV)
{

    int i,j;
    unsigned int *P1;
    unsigned int indice,aux;
    char* cheie;
    char* cheie2;
    P1=(unsigned int*)malloc((*width)*(*height)*3*sizeof(unsigned int));
    FILE *f;
    f=fopen(fisier_text,"r");
    if (f==NULL)printf("Fisierul s-a deschis incorect \n");
    fseek (f, 0, SEEK_END);
    int length = ftell (f);
    fseek (f, 0, SEEK_SET);
    cheie = malloc (length/2);
    cheie2= malloc(length/2);
    if (cheie)fread (cheie, 1, length/2, f);
    if (cheie2)fread (cheie2, length/2, length/2, f);
    ///for(i=0;i<length/2;i++)printf("%c",cheie[i]);
    int key=strtol(cheie,NULL,10);
    int key2=strtol(cheie2,NULL,10);

    ///printf("\n%d",key);
    ///printf("\n%d",key2);

    (*R)[0]=key;
   // printf("key=%d\n",key);
    (*SV)=key2;
   // printf("SV=%u",*SV);
    fclose(f);
    for(i=1; i<=2*(*width)*(*height)-1; i++)
        (*R)[i]=xorshift32((*R)[i-1]);

    j=1;
    for(i=(*width)*(*height)-1; i>=0; i--)P1[i]=i;
    for(i=(*width)*(*height)-1; i>=0; i--)
    {
        indice = (*R)[j] % (i+1);
        aux=P1[i];
        P1[i]=P1[indice];
        P1[indice]=aux;
        j++;
    }


    *redsub=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    *bluesub=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    *greensub=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));

    unsigned char x;
    for(i=(*width)*(*height)-1; i>=0; i--)
    {
        (*redsub)[P1[i]]=(*red)[i];
        (*greensub)[P1[i]]=(*green)[i];
        (*bluesub)[P1[i]]=(*blue)[i];

    }

}


void bmp_lin(char *nume_fisier,unsigned char **red,unsigned char **green,unsigned char **blue,int *width,int*height,unsigned char **header)
{
    int i,j;
    unsigned int y;
    unsigned char x;
    FILE *f;

    f=fopen(nume_fisier,"rb");
    if (f == NULL)printf("Error: fopen failed\n");
    *header=(unsigned char*)malloc(55*sizeof(unsigned char));

// Citesc header
//fread(*header, sizeof(unsigned char), 54, f);
    for(i=0; i<=53; i++)
    {
        fread(&x,sizeof(unsigned char),1,f);
        (*header)[i]=x;
    }
// Din header iauec inaltimea si latimea

    fseek(f,18,SEEK_SET);
    fread(&y,sizeof(unsigned int),1,f);
    *width=(int*)y;
    fseek(f,22,SEEK_SET);
    fread(&y,sizeof(unsigned int),1,f);
    *height=(int*)y;
    printf("Dimensiunea imaginii in pixeli este %d * %d \n",*width,*height);
    for(i=0; i<=53; i++)printf("Header %d = %u \n",i,(*header)[i]);
    fseek(f,54,SEEK_SET);

    int padding = 0;
// Padding
    while ((*width * 3 + padding) % 4 != 0)
        padding++;
    printf("Padding= %d \n",padding);
// Noua latime
   unsigned int widthnew = *width * 3 + padding;

    *red=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    *blue=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
    *green=(unsigned char*)malloc((*width)*(*height)*3*sizeof(unsigned char));
     int nrpix=(*width)*(*height)-1;
    int  n=nrpix;
    int pad;
      i=1;int contor=0;
      printf("\nNRPIXELI INITIAL= %d\n",nrpix);
      while(nrpix>=0){
       j=0;n=nrpix;i=1;

    while(j<=(*width)-1){

        fread(&x,sizeof(unsigned char),1,f);
        (*blue)[n-(*height)+i]=x;
contor++;

        fread(&x,sizeof(unsigned char),1,f);

        (*green)[n-(*height)+i]=x;
contor++;
        fread(&x,sizeof(unsigned char),1,f);
        (*red)[n-(*height)+i]=x;
contor++;
        if(j==(*width)-1){pad=0;while(pad<padding){fread(&x,sizeof(unsigned char),1,f);pad++;}}


        i++;j++;nrpix--;}
    }

    printf("\nNRPIXELI FINAL= %d\n", n);
    printf("\nContor octeti = %d\n",contor);




    //for(i=0;i<n;i++)printf("Pixel %d RGB: %u %u %u \n",i,(*red)[i],(*green)[i],(*blue)[i]);  //AFISARE PIXELI

    fclose(f);
}
void grayscale_image(char* nume_fisier_sursa,char* nume_fisier_destinatie,unsigned char** header)
{
   FILE *fin, *fout;
   unsigned int dim_img, latime_img, inaltime_img;
   unsigned char pRGB[3], aux;

   printf("nume_fisier_sursa = %s \n",nume_fisier_sursa);

   fin = fopen(nume_fisier_sursa, "rb");
   if(fin == NULL)
   	{
   		printf("nu am gasit imaginea sursa din care citesc");
   		return;
   	}
   int i,j;unsigned char x;
   (*header)=(unsigned char*)malloc(54*sizeof(unsigned char));
   for(i=0;i<=53;i++){fread(&x,sizeof(unsigned char),1,fin);(*header)[i]=x;printf("\n %d = %u \n",i,x);}
   fout = fopen(nume_fisier_destinatie, "wb+");

   fseek(fin, 2, SEEK_SET);
   fread(&dim_img, sizeof(unsigned int), 1, fin);
   printf("Dimensiunea imaginii in octeti: %u\n", dim_img);

   fseek(fin, 18, SEEK_SET);
   fread(&latime_img, sizeof(unsigned int), 1, fin);
   fread(&inaltime_img, sizeof(unsigned int), 1, fin);
   printf("Dimensiunea imaginii in pixeli (latime x inaltime): %u x %u\n",latime_img, inaltime_img);

   //copiaza octet cu octet imaginea initiala in cea noua
	fseek(fin,0,SEEK_SET);
	unsigned char c;
	while(fread(&c,1,1,fin)==1)
	{
		fwrite(&c,1,1,fout);
		fflush(fout);
	}
	fclose(fin);

	//calculam padding-ul pentru o linie
	int padding;
    if(latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;

    printf("padding = %d \n",padding);

	fseek(fout, 54, SEEK_SET);

	for(i = 0; i < inaltime_img; i++)
	{
		for(j = 0; j < latime_img; j++)
		{
			//citesc culorile pixelului
			fread(pRGB, 3, 1, fout);
			//fac conversia in pixel gri
			aux = 0.299*pRGB[2] + 0.587*pRGB[1] + 0.114*pRGB[0];
			pRGB[0] = pRGB[1] = pRGB[2] = aux;
        	fseek(fout, -3, SEEK_CUR);
        	fwrite(pRGB, 3, 1, fout);
        	fflush(fout);
		}
		fseek(fout,padding,SEEK_CUR);
	}
	fclose(fout);
}
void afisare(char* nume,unsigned char*** imgcol,int* widthimg,int*heightimg,unsigned char** header)
{
    FILE *f;
    unsigned char x,aux;
    f=fopen(nume,"wb");
    if (f==NULL)printf("Fisierul a fost deschis incorect");
    int i,j,padding=0;int pad=0;
    while (((*widthimg) * 3 + padding) % 4 != 0)
    padding++;

    printf("Padding= %d \n",padding);

    printf("\n Width= %u \n Height= %u \n",(*widthimg),(*heightimg));

    for(i=0; i<=53; i++)

    {x=(*header)[i];

        fwrite(&x,sizeof(unsigned char),1,f);}

    unsigned char galben=201,verde=202,cyan=203,magenta=204,albastru=205,argintiu=206,albastru2=207,magenta2=208,albastru3=209;
        for(i=0;i<=(*heightimg)-1;i++)for(j=0;j<=(*widthimg)*3-1;j=j+3){
                if((*imgcol)[i][j]==galben){(*imgcol)[i][j]=0;(*imgcol)[i][j+1]=255;(*imgcol)[i][j+2]=255;}
            else if((*imgcol)[i][j]==verde){(*imgcol)[i][j]=0;(*imgcol)[i][j+1]=255;(*imgcol)[i][j+2]=0;}
            else if((*imgcol)[i][j]==cyan){(*imgcol)[i][j]=255;(*imgcol)[i][j+1]=255;(*imgcol)[i][j+2]=0;}
            else if((*imgcol)[i][j]==magenta){(*imgcol)[i][j]=255;(*imgcol)[i][j+1]=0;(*imgcol)[i][j+2]=255;}
            else if((*imgcol)[i][j]==albastru){(*imgcol)[i][j]=255;(*imgcol)[i][j+1]=0;(*imgcol)[i][j+2]=0;}
            else if((*imgcol)[i][j]==argintiu){(*imgcol)[i][j]=192;(*imgcol)[i][j+1]=192;(*imgcol)[i][j+2]=192;}
            else if((*imgcol)[i][j]==albastru2){(*imgcol)[i][j]=0;(*imgcol)[i][j+1]=140;(*imgcol)[i][j+2]=255;}
            else if((*imgcol)[i][j]==magenta2){(*imgcol)[i][j]=128;(*imgcol)[i][j+1]=0;(*imgcol)[i][j+2]=128;}
            else if((*imgcol)[i][j]==albastru3){(*imgcol)[i][j]=0;(*imgcol)[i][j+1]=0;(*imgcol)[i][j+2]=128;}
                else{x=(*imgcol)[i][j];(*imgcol)[i][j]=(*imgcol)[i][j+2];(*imgcol)[i][j+2]=x;}}
    for(i=0;i<=(*heightimg)-1;i++)for(j=0;j<=(*widthimg)*3-1;j++){;x=(*imgcol)[i][j];fwrite(&x,sizeof(unsigned char),1,f);
    if(j==(*widthimg)*3-1&&padding!=0){pad=0;while(pad<padding){x=0;fwrite(&x,sizeof(unsigned char),1,f);pad++;}}

            }
}
void nonmax(double** sort_max,double*** cor_matrix0,double*** cor_matrix1,double*** cor_matrix2,double*** cor_matrix3,
            double*** cor_matrix4,double*** cor_matrix5,double*** cor_matrix6,double*** cor_matrix7,double*** cor_matrix8,double*** cor_matrix9,int* widthimg,int*heightimg,
            int *widthsab,int* heightsab,int* k,double* ps)
{
    int nr=0,i,j,coli=-1,colj=-1,p,q=0;
    int mat=-1;
    double aux;
   while(q!=3){ for(nr=0;nr<=(*k)-1;nr++){
         mat=-1;coli=-1;colj=-1;
       if((*sort_max)[nr]>0){
        for(i=0;i<=(*heightimg)-(*heightsab)-1;i++)
        for(j=0;j<=(*widthimg)-(*widthsab)-1;j++)
        {        if(coli==-1&&colj==-1)
               { if((*cor_matrix0)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=0;}
            else if((*cor_matrix1)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=1;}
            else if((*cor_matrix2)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=2;}
            else if((*cor_matrix3)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=3;}
            else if((*cor_matrix4)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=4;}
            else if((*cor_matrix5)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=5;}
            else if((*cor_matrix6)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=6;}
            else if((*cor_matrix7)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=7;}
            else if((*cor_matrix8)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=8;}
            else if((*cor_matrix9)[i][j]==(*sort_max)[nr]){coli=i;colj=j;mat=9;}
            }
        }


        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix0)[i][j]>=(*ps)){aux=(*cor_matrix0)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix0)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix0)[i][j]=0;}}}
            }}




     }



        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix1)[i][j]>=(*ps)){aux=(*cor_matrix1)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix1)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix1)[i][j]=0;}}}
            }}




     }


        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix2)[i][j]>=(*ps)){aux=(*cor_matrix2)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix2)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix2)[i][j]=0;}}}
            }}

     }




        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix3)[i][j]>=(*ps)){aux=(*cor_matrix3)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix3)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix3)[i][j]=0;}}}
            }}




     }




        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix4)[i][j]>=(*ps)){aux=(*cor_matrix4)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix4)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix4)[i][j]=0;}}}
            }}




     }





        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix5)[i][j]>=(*ps)){aux=(*cor_matrix5)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix5)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix5)[i][j]=0;}}}
            }}




     }





        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix6)[i][j]>=(*ps)){aux=(*cor_matrix6)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix6)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix6)[i][j]=0;}}}
            }}




     }




        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix7)[i][j]>=(*ps)){aux=(*cor_matrix7)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix7)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix7)[i][j]=0;}}}
            }

            }}


        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix8)[i][j]>=(*ps)){aux=(*cor_matrix8)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix8)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix8)[i][j]=0;}}}
            }}




     }




        for(i=coli-(*heightsab);i<=coli+(*heightsab)-1;i++)
            for(j=colj-(*widthsab);j<=colj+(*widthsab)-1;j++){
            if(i<0||j<0);
            else {if((*cor_matrix9)[i][j]>=0.5){aux=(*cor_matrix9)[i][j];
            for(p=0;p<=(*k)-1;p++){if(aux==(*sort_max)[p]){if(aux>(*sort_max)[nr]){(*sort_max)[nr]=0;(*cor_matrix9)[coli][colj]=0;}
            else if(aux<(*sort_max)[nr]){(*sort_max)[p]=0;(*cor_matrix9)[i][j]=0;}}}
            }}



     }

     }}
  q++;  }
}
int cmpfunc (const void * a, const void * b) {
    double va,vb;
    va=*(double*)a;
    vb=*(double*)b;
    if(va>vb)return -1;
    if(va<vb)return 1;
        return 0;}
void colorare(char* nume_fisier,unsigned char*** piximg,int *widthimg,int* heightimg,double*** cor_matrix,unsigned char*** imgcol,unsigned char* CR,unsigned char* CG,unsigned char* CB,int* widthsab,int* heightsab)
{

 int i,j,cor_i,cor_j;
 int kont=0;

    for(i=0;i<=(*heightimg)-1;i++)for(j=0;j<=(*widthimg)-1;j++){
        if((*cor_matrix)[i][j]!=0){//printf("\n %f \n ",(*cor_matrix)[i][j]);
            for(cor_i=i;cor_i<=i+(*heightsab)-1;cor_i++)for(cor_j=j;cor_j<=j+(*widthsab)-1;cor_j++)
            {
                if(cor_i>i&&cor_i<i+(*heightsab)-1&&cor_j!=j&&cor_j<j+(*widthsab)-1);
                else (*imgcol)[cor_i][cor_j*3]=(*CR);
            }
        }
    }
}

void corellation(unsigned char*** pixsab,int*widthsab, int* heightsab,unsigned char*** piximg,int *widthimg,int *heightimg,double*** cor_matrix,double* ps)
{   double corelatie=0;
    double x=0;
    double n=(*widthsab)*(*heightsab);
    int i,j;    double smediu=0;
    for(i=0;i<=(*heightsab)-1;i++)for(j=0;j<=(*widthsab)-1;j++)smediu=smediu+(*pixsab)[i][j];
    smediu=smediu/((*widthsab)*(*heightsab));
   // printf(" %f ",smediu);
      double sigmas=0;
      for(i=0;i<=(*heightsab)-1;i++)for(j=0;j<=(*widthsab)-1;j++){x=(*pixsab)[i][j]-smediu;x=x*x;sigmas=sigmas+x;}
      sigmas=sigmas/(n-1);
      sigmas=sqrt(sigmas);
     // printf("Am ajuns aici1");
      (*cor_matrix)=(double**)malloc((*widthimg)*(*heightimg)*sizeof(double*));
      for(i=0;i<(*heightimg);i++)(*cor_matrix)[i]=(double*)malloc((*widthimg)*sizeof(double));
      for(i=0;i<=(*heightimg)-1;i++)for(j=0;j<=(*widthimg)-1;j++)(*cor_matrix)[i][j]=0;

      unsigned char** fereastra;
      fereastra=(unsigned char**)malloc((*widthsab)*(*heightsab)*sizeof(unsigned char));
      double fmediu=0;
      double sigmaf=0;
      for(i=0;i<(*heightsab);i++)fereastra[i]=(unsigned char*)malloc((*widthsab)*sizeof(unsigned char));
      int fer_i=0;
      int fer_j=0; // liinia si coloana unde se afla coltul stang al ferestrei
      double f=0,s=0,sig=0;int ak=0;
      int p,q;
      //printf("Am ajuns aici2");
      while(fer_i<=(*heightimg)-(*heightsab))
      {i=0;j=0;
      fmediu=0;sigmaf=0;f=0;s=0;sig=0;corelatie=0;
          for(p=fer_i,i=0;p<=fer_i+(*heightsab)-1;p++,i++)
             for(q=fer_j,j=0;q<=fer_j+(*widthsab)-1;q++,j++)
              fereastra[i][j]=(*piximg)[p][q];
              for(i=0;i<=(*heightsab)-1;i++)for(j=0;j<=(*widthsab)-1;j++)fmediu=fmediu+fereastra[i][j];
    fmediu=fmediu/((*widthsab)*(*heightsab));
    for(i=0;i<=(*heightsab)-1;i++)for(j=0;j<=(*widthsab)-1;j++){x=fereastra[i][j]-fmediu;x=x*x;sigmaf=sigmaf+x;}
      sigmaf=sigmaf/(n-1);
      sigmaf=sqrt(sigmaf);
      for(i=0;i<=(*heightsab)-1;i++)for(j=0;j<=(*widthsab)-1;j++){f=fereastra[i][j]-fmediu;s=(*pixsab)[i][j]-smediu;
       sig=1/(sigmaf*sigmas);
       corelatie=corelatie+sig*f*s; }
     // if(fer_i==0&&fer_j==0)printf("corelatia primei ferestre = %f",corelatie/n);
      if((corelatie/n)>=(*ps))(*cor_matrix)[fer_i][fer_j]=corelatie/n;
      else (*cor_matrix)[fer_i][fer_j]=0;

       if(fer_j==(*widthimg)-(*widthsab)){fer_j=0;fer_i++;}
       else fer_j++;

}


}


void liniarizare(char *nume_fisier,unsigned char*** piximg,int* width,int* height)
{unsigned char x;
unsigned int y;
FILE *f;
f=fopen(nume_fisier,"rb");
if(f==NULL)printf("Fisier deschis incorect");
int i,j;
fseek(f,18,SEEK_SET);
    fread(&y,sizeof(unsigned int),1,f);
    *width=(int*)y;printf("width= %d\n",(*width));
    fseek(f,22,SEEK_SET);
    fread(&y,sizeof(unsigned int),1,f);
    *height=(int*)y;printf("height= %d\n",(*height));
int padding=0;
*piximg=(unsigned char**)malloc((*height)*sizeof(unsigned char*));

for(i=0;i<(*height);i++)(*piximg)[i]=(unsigned char*)malloc((*width)*sizeof(unsigned char));

while (((*width) * 3 + padding) % 4 != 0)
        padding++;

    printf("Padding= %d \n",padding);


    int pad=0;
fseek(f,54,SEEK_SET);
for(i=0;i<=(*height)-1;i++){
for(j=0;j<=(*width)-1;j++){fread(&x,sizeof(unsigned char),1,f);
fread(&x,sizeof(unsigned char),1,f);
fread(&x,sizeof(unsigned char),1,f);
(*piximg)[i][j]=x;
if(j==(*width)-1&&padding!=0){pad=0;while(pad<padding){fread(&x,sizeof(unsigned char),1,f);pad++;}}
;}}

}

int main()
{  ///Proiect: Tema1.

    char nume_fisier1[100];
    char fisier_text1[100];

    int width;
    int height;
    int i,j;
    unsigned char *header1;
    printf("\n\n Tema1- Criptografie \n\n");
    printf("\n Introduceti calea completa a fisierului bmp: \n");
    scanf("%s",nume_fisier1);
    unsigned char *red,*blue,*green;

    bmp_lin(nume_fisier1,&red,&green,&blue,&width,&height,&header1);

    printf("Width= %d\n",width);
    printf("Height= %d\n",height);
    for(i=0; i<=53; i++)printf("Header %d = %d \n",i,header1[i]);



    char nume_fisier_ext[100];
    printf("\n Introduceti calea completa a fisierului bmp incarcata in memoria externa ce va fi criptat: \n");
    scanf("%s",nume_fisier_ext);

    printf("\n Introduceti calea completa a fisierului text ce contine cheia secreta: \n");
    scanf("%s",fisier_text1);


    unsigned int SV;
    unsigned long int *R;
    R=(unsigned long int*)malloc((2*width*height-1)*sizeof(unsigned long int));


    unsigned int *inv;
    unsigned char *redsub,*bluesub,*greensub;
    unsigned char *redcr,*bluecr,*greencr;
    char nume_decript[100];

      criptare(fisier_text1,&width,&height,&redsub,&bluesub,&greensub,&header1,&red,&blue,&green,&R,&SV);
      xorare(&SV,&redsub,&greensub,&bluesub,&R,&width,&height,&header1);
      test_chi(&width,&height,&red,&green,&blue,&redsub,&greensub,&bluesub);
      memorie_externa(nume_fisier_ext,&width,&height,&redsub,&greensub,&bluesub,&header1);
      printf("\n Introduceti calea completa a fisierului text ce va contine imaginea decriptata:\n");
      scanf("%s",nume_decript);
      decriptare(&redsub,&greensub,&bluesub,&SV,&R,&width,&height,&inv,&redcr,&greencr,&bluecr);
      memorie_externa(nume_decript,&width,&height,&redcr,&greencr,&bluecr,&header1);



    ///Proiect: Tema2.

    int widthimg,heightimg;
    unsigned char* header;
	char nume_img_sursa[] = "test.bmp";
	char nume_img_grayscale[] = "test_grayscale.bmp";
	char numefisier[100];
    grayscale_image(nume_img_sursa, nume_img_grayscale,&header);
    printf("\n Introduceti calea completa a fisierului bmp grayscale: \n");
    scanf("%s",numefisier);
    unsigned char x;
	unsigned char **piximg;
	liniarizare(numefisier,&piximg,&widthimg,&heightimg);
    unsigned char** imgcol;
    imgcol=(unsigned char**)malloc(widthimg*heightimg*3*sizeof(unsigned char*));
    for(i=0;i<heightimg;i++)imgcol[i]=(unsigned char*)malloc(widthimg*3*sizeof(unsigned char));
	int p=0,q=0;
	for(i=0;i<heightimg;i++)for(j=0;j<widthimg;j++)
        {
            imgcol[p][q]=piximg[i][j];
           q++;
	     imgcol[p][q]=piximg[i][j];
	       q++;
         imgcol[p][q]=piximg[i][j];
           q++;
           if(j==widthimg-1){p++;q=0;}
        }
    char numef[100];
    int widthsab,heightsab;
    char nume_cifra0[]="cifra0.bmp";
    char nume_cifra0g[]="cifra0_grayscale.bmp";
    unsigned char **pixsab0;
    unsigned char * fakeheader;
    grayscale_image(nume_cifra0,nume_cifra0g,&fakeheader);
    liniarizare(nume_cifra0g,&pixsab0,&widthsab,&heightsab);

    char nume_cifra1[]="cifra1.bmp";
    char nume_cifra1g[]="cifra1_grayscale.bmp";
    unsigned char **pixsab1;
    grayscale_image(nume_cifra1,nume_cifra1g,&fakeheader);
    liniarizare(nume_cifra1g,&pixsab1,&widthsab,&heightsab);

    char nume_cifra2[]="cifra2.bmp";
    char nume_cifra2g[]="cifra2_grayscale.bmp";
    unsigned char **pixsab2;
    grayscale_image(nume_cifra2,nume_cifra2g,&fakeheader);
    liniarizare(nume_cifra2g,&pixsab2,&widthsab,&heightsab);

    char nume_cifra3[]="cifra3.bmp";
    char nume_cifra3g[]="cifra3_grayscale.bmp";
    unsigned char **pixsab3;
    grayscale_image(nume_cifra3,nume_cifra3g,&fakeheader);
    liniarizare(nume_cifra3g,&pixsab3,&widthsab,&heightsab);

    char nume_cifra4[]="cifra4.bmp";
    char nume_cifra4g[]="cifra4_grayscale.bmp";
    unsigned char **pixsab4;
    grayscale_image(nume_cifra4,nume_cifra4g,&fakeheader);
    liniarizare(nume_cifra4g,&pixsab4,&widthsab,&heightsab);

    char nume_cifra5[]="cifra5.bmp";
    char nume_cifra5g[]="cifra5_grayscale.bmp";
    unsigned char **pixsab5;
    grayscale_image(nume_cifra5,nume_cifra5g,&fakeheader);
    liniarizare(nume_cifra5g,&pixsab5,&widthsab,&heightsab);

    char nume_cifra6[]="cifra6.bmp";
    char nume_cifra6g[]="cifra6_grayscale.bmp";
    unsigned char **pixsab6;
    grayscale_image(nume_cifra6,nume_cifra6g,&fakeheader);
    liniarizare(nume_cifra6g,&pixsab6,&widthsab,&heightsab);

    char nume_cifra7[]="cifra7.bmp";
    char nume_cifra7g[]="cifra7_grayscale.bmp";
    unsigned char **pixsab7;
    grayscale_image(nume_cifra7,nume_cifra7g,&fakeheader);
    liniarizare(nume_cifra7g,&pixsab7,&widthsab,&heightsab);

    char nume_cifra8[]="cifra8.bmp";
    char nume_cifra8g[]="cifra8_grayscale.bmp";
    unsigned char **pixsab8;
    grayscale_image(nume_cifra8,nume_cifra8g,&fakeheader);
    liniarizare(nume_cifra8g,&pixsab8,&widthsab,&heightsab);

    char nume_cifra9[]="cifra9.bmp";
    char nume_cifra9g[]="cifra9_grayscale.bmp";
    unsigned char **pixsab9;
    grayscale_image(nume_cifra9,nume_cifra9g,&fakeheader);
    liniarizare(nume_cifra9g,&pixsab9,&widthsab,&heightsab);

    printf("\nWsab= %d Hsab= %d",widthsab,heightsab);
    double ps=0.5;printf("\nps= %f \n",ps);
    double** cor_matrix0;
    corellation(&pixsab0,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix0,&ps);
   // for(i=0;i<=heightimg-1;i++)for(j=0;j<=widthimg;j++)if(i<=100&&j<=100&&cor_matrix0[i][j]>=ps)printf("\n i= %d j= %d valoare= %f",i,j,cor_matrix0[i][j]);
    int k=0;
	unsigned char CR,CG,CB;
    CR=255;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix0,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix1;
    corellation(&pixsab1,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix1,&ps);
    CR=201;
    CG=10;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix1,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix2;
    corellation(&pixsab2,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix2,&ps);
    CR=202;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix2,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix3;
    corellation(&pixsab3,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix3,&ps);
    CR=203;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix3,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix4;
    corellation(&pixsab4,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix4,&ps);
    CR=204;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix4,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix5;
    corellation(&pixsab5,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix5,&ps);
    CR=205;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix5,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix6;
    corellation(&pixsab6,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix6,&ps);
    CR=206;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix6,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix7;
    corellation(&pixsab7,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix7,&ps);
    CR=207;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix7,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix8;
    corellation(&pixsab8,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix8,&ps);
    CR=208;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix8,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);

    double** cor_matrix9;
    corellation(&pixsab9,&widthsab,&heightsab,&piximg,&widthimg,&heightimg,&cor_matrix9,&ps);
    CR=209;
    CG=0;
    CB=0;
    colorare(numefisier,&piximg,&widthimg,&heightimg,&cor_matrix9,&imgcol,&CR,&CG,&CB,&widthsab,&heightsab);
    char nume[100];
    printf("\n Introduceti calea completa a fisierului bmp pt colorare ferestre: \n");
    scanf("%s",nume);
    afisare(nume,&imgcol,&widthimg,&heightimg,&header);

    double * sort_max;
    sort_max=(double*)malloc(widthimg*heightimg*3*sizeof(double));

    for(i=0;i<=widthimg*heightimg*3-1;i++)sort_max[i]=0;
    i=0;j=0;int ok=1; k=0;
    while(ok){if(cor_matrix0[i][j]>0){sort_max[k]=cor_matrix0[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix1[i][j]>0){sort_max[k]=cor_matrix1[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix2[i][j]>0){sort_max[k]=cor_matrix2[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix3[i][j]>0){sort_max[k]=cor_matrix3[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix4[i][j]>0){sort_max[k]=cor_matrix4[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix5[i][j]>0){sort_max[k]=cor_matrix5[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix6[i][j]>0){sort_max[k]=cor_matrix6[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix7[i][j]>0){sort_max[k]=cor_matrix7[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix8[i][j]>0){sort_max[k]=cor_matrix8[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;

    while(ok){if(cor_matrix9[i][j]>0){sort_max[k]=cor_matrix9[i][j];k++;}if(j==widthimg-widthsab){j=0;i++;} else j++;
              if(i==heightimg-heightsab&&j==widthimg-widthsab)ok=0;}
    ok=1;i=0;j=0;


qsort(sort_max,k,sizeof(double),cmpfunc);
//for(i=0;i<k;i++)printf("\n %d = %f \n",i,sort_max[i]);



   nonmax(&sort_max,&cor_matrix0,&cor_matrix1,&cor_matrix2,&cor_matrix3,&cor_matrix4,&cor_matrix5,&cor_matrix6,&cor_matrix7,&cor_matrix8,&cor_matrix9,&widthimg,
         &heightimg,&widthsab,&heightsab,&k,&ps);


    unsigned char** imgcol2;
    imgcol2=(unsigned char**)malloc(widthimg*heightimg*3*sizeof(unsigned char*));
    for(i=0;i<heightimg;i++)imgcol2[i]=(unsigned char*)malloc(widthimg*3*sizeof(unsigned char));
    p=0,q=0;
	for(i=0;i<heightimg;i++)for(j=0;j<widthimg;j++)
        {
            imgcol2[p][q]=piximg[i][j];
           q++;
	     imgcol2[p][q]=piximg[i][j];
	       q++;
         imgcol2[p][q]=piximg[i][j];
           q++;
           if(j==widthimg-1){p++;q=0;}
        }
printf("\n Introduceti calea completa a fisierului bmp pt scoatere ferestre in plus: \n");
    scanf("%s",numef);
    CR=255;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix0,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=201;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix1,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=202;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix2,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=203;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix3,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=204;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix4,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=205;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix5,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=206;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix6,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=207;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix7,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=208;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix8,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);
    CR=209;
colorare(numef,&piximg,&widthimg,&heightimg,&cor_matrix9,&imgcol2,&CR,&CG,&CB,&widthsab,&heightsab);

    afisare(numef,&imgcol2,&widthimg,&heightimg,&header);
    return 0;
}

