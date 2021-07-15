#include "basicas.cpp"

#define MAXdni 9
#define MAXsexo 2
#define MAXprofesion 7
#define MAXestado 2
struct Postulante
{
	char DNI[MAXdni];
   char nombre[LIM];
   int edad;
   int sexo;
   int profesion;
   int experiencia;
   int estado;
};

char Tsexo[MAXsexo][LIM]={"Masculino", "Femenino"};
char Tprofesion[MAXprofesion][LIM]={"Ing. Sistemas", "Ing. Electronica", "Ing. Civil", "Ing. Mecanica", "Contabilidad", "Economia", "Administracion"};
char Testado[MAXestado][LIM]={"Con trabajo", "Sin trabajo"};

void iniciaPostulante(Postulante &P)
{
 	P.DNI[0]=NULL;
 	P.nombre[0]=NULL;
 	P.edad=0;
 	P.sexo=0;
 	P.profesion=0;
   P.experiencia=0;
   P.estado=0;
}


void mostrarPostulante(Postulante &P)
{
 	printf("\n\n Numero de DNI: %s ",P.DNI);
 	printf("\n Nombre: %s ",P.nombre);
	printf("\n Edad: %d ",P.edad);
 	printf("\n Sexo: %s ",Tsexo[P.sexo-1]);
 	printf("\n Profesion: %s ",Tprofesion[P.profesion-1]);
   printf("\n A%cos de experiencia: %d",164,P.experiencia);
   printf("\n Estado laboral: %s",Testado[P.estado-1]);
}


struct listaPostulantes
{
  Postulante *pP;
  int N;
};

void iniciaListaPostulante(listaPostulantes &LP)
{
	LP.pP= new Postulante [MAX];
   LP.N=0;
}

void leePostulante(Postulante &P,listaPostulantes &LP)
{
	int flagdni;
   do
   {
 		do
      {
    		printf("\n   Ingrese numero de DNI (8 caracteres): ");
    		fflush(stdin);
      	gets(P.DNI);
 		}while(!(strlen(P.DNI)==MAXdni-1));
      flagdni=0;
   	for(int i=0;i<LP.N;i++)
   		if(strcmp(P.DNI, LP.pP[i].DNI) == 0)
         	flagdni=1;
      if(flagdni==1)
      	printf("\n     Error, el DNI se ha ingresado anteriormente\n");
   }while(!(flagdni==0));

	printf("\n   Ingrese nombre: ");
   gets(P.nombre);

 	P.edad=leeEntero("\n   Ingrese edad[20-70]: ",20,70);
 	P.sexo=validaTabla("\n    Ingrese sexo: ",Tsexo,MAXsexo);
 	P.profesion=validaTabla("\n    Ingrese profesion: ",Tprofesion,MAXprofesion);
   P.experiencia=leeEnterocon(0,50);
   P.estado=validaTabla("\n    Ingrese estado laboral: ",Testado,MAXestado);
}

void inserta(listaPostulantes &LP, Postulante &P)
{
  	if(LP.N<MAX)
  	{
     	LP.pP[LP.N]=P;
     	LP.N++;
  	}
  	else
      printf("\n No hay espacio...");
}

void leerListaPostulante(listaPostulantes &LP)
{
  	Postulante P;

  	do{
  		iniciaPostulante(P);
  		leePostulante(P,LP);
  		inserta(LP,P);
 	}while(continuar("\n Desea continuar (S/N): ")=='S');

}

void mostrarListaPostulante(listaPostulantes &LP)
{
	if(LP.N>0)
   {
   	for(int i=0;i<LP.N;i++)
      {
      	printf("\n\nPostulante Nro[%d]",i+1);
      	mostrarPostulante(LP.pP[i]);
      }
   }
   else
   	printf("\nNo hay Datos...");
   getch();
}

void liberarListaPostulante(listaPostulantes &LP)
{
 	delete [] LP.pP;
}

//Reportes
void profesionEstado(listaPostulantes &LP)
{
   int n,x,y;
	if(LP.N>0)
	{
   	n=validaTabla("\n    Ingrese profesion: ", Tprofesion, MAXprofesion);
      x=0;
      y=0;
      for(int i=0;i<LP.N;i++)
      	if(LP.pP[i].profesion==n)
         	if(LP.pP[i].estado==1)
            	x+=1;
            else
            	y+=1;
      printf("\n\nPostulantes con trabajo: %d",x);
      printf("\nPostulantes sin trabajo: %d",y);
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void experienciaLimite(listaPostulantes &LP)
{
   int num,flag=0;
	if(LP.N>0)
	{
      printf("\nIngrese a%cos de experiencia: ",164);
      scanf("%d",&num);
      for(int i=0;i<LP.N;i++)
      	if(LP.pP[i].experiencia<num)
         {
         	printf("\n\nPostulante Nro[%d]",i+1);
         	mostrarPostulante(LP.pP[i]);
            flag=1;
         }
      if(flag==0)
      	printf("\nNo hay postulantes...");
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void sexoRango(listaPostulantes &LP)
{
	int s,emin,emax,flag=0,sex=0,hom=0,muj=0;
	if(LP.N>0)
	{
   	s=validaTabla("\n    Ingrese sexo: ", Tsexo, MAXsexo);
      for(int i=0;i<LP.N;i++)
      {
      	if(LP.pP[i].sexo==1)
         	hom+=1;
         else
         	muj+=1;
      }
      if(s==1)
      	if(hom>0)
      		sex=hom;
      	else
      		sex=0;
      else
      	if(muj>0)
      		sex=muj;
      	else
      		sex=0;
      if(sex>0)
      {
      	emin=leeEntero("\n   Ingrese edad minima[20-70]: ", 20, 70);
      	do
      	{
      		emax=leeEntero("\n   Ingrese edad maxima[Edad minima-70]", emin, 70);
      	}while(!(emax>=emin));
      	for(int i=0;i<LP.N;i++)
      	{
      		if(LP.pP[i].sexo==s)
         	{
         		if(LP.pP[i].edad>=emin && LP.pP[i].edad<=emax)
            	{
            		printf("\n\nPostulante Nro[%d]",i+1);
         			mostrarPostulante(LP.pP[i]);
            		flag=1;
            	}
         	}
      	}
      	if(flag==0)
      		printf("\nNo hay postulantes con ese rango de edad...");
      }
      else
      {
      	printf("\nNo hay postulantes %s",Tsexo[s-1]);
      }
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

int hombremujer(listaPostulantes LP,int a)
{
   int num=0;

	for(int i=0;i<LP.N;i++)
   {
   	if(LP.pP[i].sexo==a)
      {
      	num++;
      }
   }
   return num;
}

void porcentajeHM(listaPostulantes &LP)
{
   int hombres,mujeres,suma;
   float porH,porM;

	if(LP.N>0)
   {
      hombres=hombremujer(LP,1);
      mujeres=hombremujer(LP,2);
      suma=hombres+mujeres;
      porH=(float)hombres*100/suma;
      porM=(float)mujeres*100/suma;
   	printf("\n Hombres: %.2f%",porH);
      printf("\n\n Mujeres: %.2f%",porM);
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void promedioEdad(listaPostulantes &LP)
{
 	int suma=0;
 	float prom;

 	if(LP.N>0)
 	{
  		for(int i=0; i<LP.N; i++)
  			suma+=LP.pP[i].edad;
  		prom=(float)suma/LP.N;
		printf("\n El promedio de edad es: %.2f", prom);
   }
 	else
 		printf("\nNo hay datos...");
 	getch();
}


void numprofesion(listaPostulantes LP)
{
   int num,mayor=0,aux=0,a;

   for(a=1;a<MAXprofesion+1;a++)
   {
      num=0;
   	for(int i=0;i<LP.N; i++)
      {
   	 	if(LP.pP[i].profesion==a)
      		num++;
      }
      if(num>mayor)
      {
      	mayor=num;
         aux=a;
      }
   }
   printf("\nProfesion con mas postulantes: %s",Tprofesion[aux-1]);
}
void profesionmaypos(listaPostulantes &LP)
{
	if(LP.N>0)
 	{
		numprofesion(LP);
   }
 	else
 		printf("\nNo hay datos...");
 	getch();
}


void menu(listaPostulantes &LP)
{
  int opc;
  do{
     printf("\n\n *** MENU PRINCIPAL ***\n");
     printf("\n  1. Lectura");
     printf("\n  2. Mostrar");
     printf("\n  3. Numero de postulantes por estado dada una profesion");
     printf("\n  4. Postulantes con a%cos de experiencia menores a un valor",164);
     printf("\n  5. Postulantes dado el sexo y un rango de edades	");
     printf("\n  6. Porcentaje de hombre y mujeres postulantes");
     printf("\n  7. Promedio de edad de los postulantes por cada estado");
     printf("\n  8. Profesion con mayor numero de postulantes");
     printf("\n  9. Salir");
     opc=leeEntero("\n Ingrese opcion: ", 1, 9);
     switch(opc)
     {
       case 1: leerListaPostulante(LP); break;
       case 2: mostrarListaPostulante(LP); break;
       case 3: profesionEstado(LP); break;
       case 4: experienciaLimite(LP); break;
       case 5: sexoRango(LP); break;
       case 6: porcentajeHM(LP); break;
       case 7: promedioEdad(LP); break;
       case 8: profesionmaypos(LP); break;
       case 9: liberarListaPostulante(LP); break;
     }
  }while(opc!=9);
}

int main()
{
	listaPostulantes LP;

   iniciaListaPostulante(LP);
   menu(LP);
   return 1;
}
