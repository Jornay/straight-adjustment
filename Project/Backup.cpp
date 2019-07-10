#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>

void Calculo(float Xi[],float Yi[],int N,float* fx) 
{
	void Fx(int N,float a,float b,float Xi[],float* F);
//Determinando os coeficientes A e B da reta: f(x)=a+bx
float X=0,Y=0,A=0,B=0,C=0;
float a,b;
float fc[N];
int I;
for(I=0;I<N;I++)
{
	A=A+Xi[I]*Xi[I];     //Calculando as constantes.                
	B=B+Xi[I]*Yi[I];
	C=C+Yi[I]*Yi[I];
	X=X+Xi[I];
	Y=Y+Yi[I];
	
}
b=(B*N-Y*X)/(N*A-X*X);     //determinando o coeficiente de b
a= (Y-b*X)/N;              //determinando o coeficiente de a
system ("cls");
printf("\n\n====Valor de a = %.4f e valor de b = %.4f====",a,b);
Fx(N, a, b, Xi,fc);
for(I=0;I<N;I++)
   {
    
    fx[I]=fc[I];
   }
}

void Fx(int N,float a,float b,float Xi[],float* F)
{
int i;
	for(i=0;i<N;i++)
	{
		F[i]= a+b*Xi[i];
	}
}

void AGen(float C1[],float C2[],float C3[],int Nlin)
{
  	int i;
  	FILE * Fg;
	Fg = fopen ("Resultado.fit" , "w");
      printf("\n\n====Colunas recebidas e Coluna ajustada====\n");
  	      
	 printf("    Coluna 1	Coluna 2    Coluna 3(ajustada)\n");  
  	for (i=0;i<Nlin;i++)
     {
  		
    	fprintf(Fg, "%.2f %.2f %.2f\n",C1[i],C2[i],C3[i]);
		printf("    %.2f\t%.2f\t    %.2f\n",C1[i],C2[i],C3[i]);
  	}
  	  printf("\nPRESSIONE DUAS VEZES O ESPA�O PARA FECHAR\n");
   
  	fclose(Fg);
  
  	
}

void plotGnu()
{
	FILE * fgnu;
	fgnu = fopen ("temp.tmp" , "w");	
	fprintf(fgnu ,"set decimalsign locale\n");
	fprintf(fgnu ,"set xlabel 'X'\n");
    fprintf(fgnu ,"set ylabel 'Y'\n");
	fprintf(fgnu ,"plot 'Resultado.fit' using 1:2 pointtype 6 lc rgb 'black' ps 1.2 title 'Dados experimentais', 'Resultado.fit' using 1:3 w l lt rgb 'red' title 'Curva de Ajuste'\n");
    fprintf(fgnu, "pause -1");
    fclose(fgnu);


}
void sistema()
{
	//system ("cls");
	system ("gnuplot temp.tmp");
}
void delfile()
{
	system("del temp.tmp") ;
}

float ChiQ(float Y[],float fx[],int N )
{
	float Cq=0;
	int i;
	for(i=0;i<N;i++)
	{
		Cq =Cq+pow((fx[i]-Y[i]),2);
	}
	Cq=Cq/N;
	return Cq;
}

//=================================Main========================================//

int main()
{
	int i,l,N;
    char arq[25];
	float X[100],Y[100];
	float Cq;
	
//===========================Vari�veis===================================================//
setlocale(LC_ALL, "Portuguese");


    printf("\n\nSoftware de calculo intermedi�rio\n");
    printf("\nPara que tudo ocorra como o planejado, voc� dever� seguir as instru��es a seguir >>>>>>>>>\n\n");
    system("PAUSE");
    system("cls");
	
	printf("\n\n[1]-Primeiro voc� precisar� instalar o programa 'gnuplot' em sua m�quina.\n");
	printf("Ap�s isso voc� ter� que ir na sua barra de pesquisa do sistema operacional e digitar 'vari�veis de ambiente'\n");
    printf("Clickar em 'Path' e ir em editar\n");
    printf("Agora voc� ter� q procurar o diret�rio de onde o seu gnuplot foi intalado e copia-lo\n");
    printf("Na aba de edi��o, v� em 'novo' e coloque o diret�rio l� dentro, ap�s isso d� ok em tudo e feche\n");
	printf("\n\n[2]-Agora crie um arquivo txt onde se encontrar� o inicializador do programa Dev-C++ .\n");
    printf("\n[3]-Digite os valores de X na primeira coluna e de Y na segunda coluna separadas por tabula��o\n");
    printf("em um arquivo de texto (Apenas n�meros).\n");
    printf("\n\nExemplo:\n1	   2\n3	   8\n9	   50\n\n");
    printf("\nE assim se iniciar� o programa.\n\nN�O PROSSIGA A MENOS QUE TENHA SEGUIDO TODOS OS PASSOS ACIMA!\n\n");
    system("PAUSE");
    system("cls");
    
    printf("\n====INICIALIZANDO PROGRAMA====\n");
    printf("\n\nInforme o nome de seu arquivo incluindo a sua extens�o : ");
    gets(arq);
    
    printf("\nInforme quantas linhas haver� em sua matriz : ");
	scanf("%d",&l);
    
    FILE * fp;
	fp = fopen (arq , "r");
	if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
    for(i=0;i<l;i++)
		{
			fscanf(fp, "%f %f",&X[i],&Y[i]);
           

            
		}
    fclose(fp);
    
    float fx[l];
    Calculo(X,Y,l,fx);
     Cq=ChiQ(Y,fx,l);
    printf("Valor do Chi� = %.5f",Cq);
    AGen(X,Y,fx,l);
    plotGnu();
    sistema();
    system ("PAUSE");
    delfile();
    

	return 0;
}

