#include <stdio.h>
#include "lecturas.h"

int leerEnteroPositivo(char* mensaje){
    int valor;
    do{
        printf("%s", mensaje);
        scanf("%d",&valor);
         if(valor <=0){
          printf("-------------------------------------------------------------------");
            printf("Error");
          printf("-------------------------------------------------------------------");
        }
    }while(valor <= 0);
    return valor;
}

int leerEntero(char*mensaje){
  int valor;
  printf("%s", mensaje);
  scanf("%d",&valor);
  return valor;
}

int leerEnteroEntre(char*mensaje, int limInferior,int limSuperior){
  int valor;
    do{
        printf("%s", mensaje);
        scanf("%d",&valor);
         if((valor < limInferior)||(valor > limSuperior)){
          printf("-------------------------------------------------------------------");
           printf("Error: El numero debe estar entre %d y %d.\n", limInferior, limSuperior);
          printf("-------------------------------------------------------------------");
    }
    }while((valor < limInferior)||(valor > limSuperior));
  return valor;
      
}

int leerEnteroMayor(char*mensaje, int mayor){
  int valor;
  do{
        printf("%s", mensaje);
        scanf("%d",&valor);
        if(valor <=mayor){
            printf("-------------------------------------------------------------------");
            printf("Error");
            printf("-------------------------------------------------------------------");
        }
    }while(valor <= mayor);
   return valor;
  
}

int leerEnteroMenor(char*mensaje, int menor){
  int valor;
    do{
        printf("%s", mensaje);
        scanf("%d",&valor);
         if(valor >= menor){
          printf("-------------------------------------------------------------------");
            printf("Error");
          printf("-------------------------------------------------------------------");
        }
    }while(valor >= menor);
   return valor;
}

float leerFlotante(char*mensaje){
  float valor;
  printf("%s", mensaje);
  scanf("%f",&valor);
  return valor;
}

float leerFlotanteEntre(char*mensaje, float limInferior, float limSuperior){
  float valor; 
    do{
        printf("%s", mensaje);
        scanf("%f",&valor);
        if((valor < limInferior)||(valor > limSuperior)){
          printf("-------------------------------------------------------------------");
            printf("Error: El numero debe estar entre %f y %f.\n", limInferior, limSuperior);
          printf("-------------------------------------------------------------------");
        }
    }while((valor < limInferior)||(valor > limSuperior));
   return valor;
}

float leerFlotantePositivo(char* mensaje){
    float valor;
    do{
        printf("%s",mensaje);
        scanf("%f",&valor);
         if(valor <= 0){
            printf("-------------------------------------------------------------------");
            printf("Error");
            printf("-------------------------------------------------------------------");
        }
    }while(valor <= 0);
   return valor;
}

