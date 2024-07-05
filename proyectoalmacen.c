#include <stdio.h>
#define LONGITUD 10

int leerEnteroEntre(char*,int,int);
int leerEnteroPositivo(char*);
float leerFlotantePositivo(char*);

void editarLibro(char[][50], int[], float[], int);
void agregarLibro(char[][50], int[], float[], int, int, int, int);
void borrarLibro(char[][50], int[], float[], int);
void mostrarmenu();
void ingresarUsuario();

int main(int argc, char const *argv[]) {
    int tamano, opcion, grade;
     int noma;
    printf("--> * Bienvenido a la Libreria Andina* <--\n");
    char usuarioAp[50][50];
    char usuarioN[50][50];
    int cedula[LONGITUD];
    char nombres[50][50];  
    int cantidades[50];
    float precios[50];  
    int i=0;
    do {
        mostrarmenu();
        opcion = leerEnteroEntre("Ingrese su opcion: ", 1, 4);
        switch (opcion) {
             case 1:
                agregarLibro(nombres, cantidades, precios, i+1, grade, noma, tamano);
                printf("\n Inventario modificado:\n");
                break;
            case 2:
               ingresarUsuario();
               break;
             case 3:
                editarLibro(nombres, cantidades, precios, noma);
                break;
            case 4:
                printf("Cerrando el programa...\n");
                break;
            default:
                printf("Opción inexistente.\n");
        }
        
    } while (opcion != 4);
    printf("Programa finalizado\n");
    return 0;
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


void mostrarmenu(){
    printf("\n");
    printf("********************\n");
    printf("Menu de opciones:\n");
    printf("1. Agregar al Inventario\n");
    printf("2. Agregar Usuario\n");
    printf("3. Borrar Dato\n");
    printf("4. Cerrar\n");
    printf("********************\n");
}
void agregarLibro(char nombres[][50], int cantidades[], float precios[], int i, int tamano, int grade, int noma){
    printf("-------------------------------------------------------------------");
    noma = leerEnteroPositivo("\nIngrese la nueva cantidad de libros a almacenar: ");
    FILE *archivo;
    archivo = fopen("libros.txt","a");
    
    if(archivo == NULL){
        printf("No se abrio el archivo");
        return;
    }
    for (int i = 0; i < noma; i++) {
        printf(" -----------------------------------------\n"); 
        printf("Ingrese el nombre del libro %d: ", i + 1);
        scanf("%s", nombres[i]);
        cantidades[i]=leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresdo: ");
        precios[i]=leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
   
    tamano=noma;
    printf("-------------------------------------------------------------------");
     fprintf(archivo,"%s %d  %d$\n", nombres[i],cantidades[i], precios[i]);
    }
    fclose(archivo);
    }

void editarLibro(char nombres[][50], int cantidades[], float precios[], int tamano) {
    printf("-------------------------------------------------------------------");
    int edit;
    edit = leerEnteroEntre("Ingrese el numero de libro que desea editar: ", 1, tamano);
    printf("Ingrese el nuevo nombre  %d: ", edit);
    scanf("%s", nombres[edit - 1]);
    cantidades[edit - 1]=leerEnteroPositivo("Ingrese la nueva cantidad de libros: ");
    precios[edit - 1]=leerFlotantePositivo("Ingrese el nuevo precio del libro: ");
    printf("Editado con exito.\n");
    printf("-------------------------------------------------------------------");
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

void ingresarUsuario(){
    char usuarioAp[20][15];
    char usuarioN[20][15];
    int cedula[20];
    int cant;
    printf("Ingrese cuantos Usuarios va a registrar: ");
    scanf("%d",&cant);
    FILE *archivo;
    archivo = fopen("Usuarios.txt","a");
    if(archivo == NULL){
        printf("No se abrio el archivo");
        return;
    }
    for (int i = 0; i < cant; i++)
    {
         printf("-------------------------------------------------------------------");
        printf("Ingrese el nombre: ");
        scanf("%s",usuarioN[i]);
         printf("Ingrese el apellido: ");
        scanf("%s",usuarioAp[i]);
        printf("Ingrese la cedula: ");
        scanf("%d",&cedula[i]);
        fprintf(archivo,"%s %s %d\n",usuarioN[i],usuarioAp[i],cedula[i]);
         printf("-------------------------------------------------------------------");
    }
    fclose(archivo);
    }