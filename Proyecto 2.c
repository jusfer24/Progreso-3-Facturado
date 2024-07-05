#include <stdio.h>

void controlInventario(char[][50], int[], float [], int);
int leerEnteroPositivo(char* mensaje);
int leerEnteroEntre(char* mensaje, int limInferior, int limSuperior);
float leerFlotantePositivo(char*);

void ingresarLibros(char[][50], int[], float [], int);
void imprimirLibros(char[][50], int [], float [], int);
void editarLibro(char [][50], int [], float [], int);
void agregarLibro(char[][50], int[], float[], int);
void borrarLibro(char[][50], int[], float[], int);

int main() {
    int menu;
    int filas;
    char nombres[50][50];  
    int cantidades[50];
    float precios[50];     
    printf("      --> * Bienvenido * <--    \n");
    do {
        printf("=====================================\n");
        printf("[1] Control de inventario\n");
        printf("[2] Control de usuarios\n");
        printf("[3] Factura \n");
        printf("[4] Cerrar Programa \n");
        printf("=====================================\n");
        scanf("%d", &menu);
        
        switch (menu) {
            case 1:
                printf("------------------------------------\n");
                controlInventario(nombres, cantidades, precios, filas);
                printf("------------------------------------\n");
                break;
            case 2:
                printf("------------------------------------\n");
                printf("[2] Control de usuarios\n");
                printf("------------------------------------\n");
                break;
            case 3:
                printf("------------------------------------\n"); 
                printf("[3] Factura \n");
                printf("------------------------------------\n");
                break;
            case 4:
                printf("------------------------------------\n");
                printf("Cerrando el programa...\n");
                printf("------------------------------------\n");
                break;
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opción incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (menu != 4);
    
    return 0;
}

void controlInventario(char nombres[][50], int cantidades[], float precios[], int filas) {
    int ivent;
    do {
        printf("//===================================//\n");
        printf("[1] Ingresar inventario\n");
        printf("[2] Imprimir inventario\n");
        printf("[3] Editar inventario\n");
        printf("[4] Agregar Nuevo Libro\n");
        printf("[5] Borrar Libro\n");
        printf("[6] Regresar al menu principal \n");
        printf("//===================================//\n");
        scanf("%d", &ivent);
        
        switch (ivent) {
            case 1:
                printf("//-----------------/-----------------//\n");
                filas = leerEnteroPositivo("\nIngrese cantidad de libros: ");
                printf("Ingrese los datos: \n");
                printf("*********************************************\n");
                printf("[nombre | cantidad | precio]\n");
                printf("*********************************************\n");
                ingresarLibros(nombres, cantidades, precios, filas);
                printf("//-----------------/-----------------//\n");
                break;
                
            case 2:
                printf("//-----------------/-----------------//\n");
                printf("+++++++++++++++++++++++++++++++\n");
                printf("\n");
                printf("\n");
                printf("Los libros ingresados son:\n");
                printf("[ | nombre     | cantidad   | precio   ]\n");
                imprimirLibros(nombres, cantidades, precios, filas);
                printf("\n");
                printf("\n");
                printf("//-----------------/-----------------//\n");
                break;
            case 3:
                printf("//-----------------/-----------------//\n");
                editarLibro(nombres, cantidades, precios, filas);
                printf("//-----------------/-----------------//\n");
                break;
            case 4:
                printf("//-----------------/-----------------//\n");
                agregarLibro(nombres, cantidades, precios, filas);
                printf("//-----------------/-----------------//\n");
                break;
            case 5:
                printf("//-----------------/-----------------//\n");
                borrarLibro(nombres, cantidades, precios, filas);
                printf("//-----------------/-----------------//\n");
                break;
            case 6:
                printf("------------------------------------\n");
                printf("Regresando a menu principal...\n");
                break;
                
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opción incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (ivent != 6);
}

int leerEnteroPositivo(char* mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor <= 0) {
            printf("\n-------------------------------------------------------------------\n");
            printf("Error: El valor debe ser un número entero positivo.\n");
            printf("-------------------------------------------------------------------\n");
        }
    } while (valor <= 0);
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

int leerEnteroEntre(char* mensaje, int limInferior, int limSuperior) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor < limInferior || valor > limSuperior) {
            printf("-------------------------------------------------------------------\n");
            printf("Error: El número debe estar entre %d y %d.\n", limInferior, limSuperior);
            printf("-------------------------------------------------------------------\n");
        }
    } while (valor < limInferior || valor > limSuperior);
    return valor;
}

void ingresarLibros(char nombres[][50], int cantidades[], float precios[], int filas) {
    for (int i = 0; i < filas; i++) {
        printf(" -----------------------------------------\n"); 
        printf("Ingrese el nombre del libro %d: ", i + 1);
        scanf("%s", nombres[i]);
        printf("Ingrese la cantidad de libros del ejemplar %d: ", i + 1);
        scanf("%d", &cantidades[i]);  
        printf("Ingrese el precio del libro por unidad: ");
        scanf("%f", &precios[i]);
    }
}

void imprimirLibros(char nombres[][50], int cantidades[], float precios[], int filas) {
    for (int i = 0; i < filas; i++) {
        printf(" %d | %s | %d unidades | %.2f $\n", i + 1, nombres[i], cantidades[i], precios[i]);
    }
}

void editarLibro(char nombres[][50], int cantidades[], float precios[], int filas) {
    int pop;
    printf("Ingrese el numero de libro que desea editar: ");
    pop = leerEnteroEntre("", 1, filas);
    printf("Ingrese el nuevo nombre  %d: ", pop);
    scanf("%s", nombres[pop - 1]);
    printf("Ingrese la nueva cantidad de libros %d: ", pop);
    scanf("%d", &cantidades[pop - 1]);  
    printf("Ingrese el nuevo precio del libro : ");
    scanf("%f", &precios[pop - 1]);
    printf("Editado con exito.\n");
}

void agregarLibro(char nombres[][50], int cantidades[], float precios[], int filas){
    printf("Ingrese el nombre del nuevo libro %d: ", filas+1);
    scanf("%s", nombres[filas - 1]);
    cantidades[filas - 1]=leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresdo: ");
    precios[filas - 1]=leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
}

void borrarLibro(char nombres[][50], int cantidades[], float precios[], int filas){
    int eliminar=0;
    eliminar = leerEnteroEntre("Ingrese el numero de libro que desea eliminar: ", 1, filas);
    nombres[eliminar-1]=="null";
    cantidades[eliminar-1]=0;
    precios[eliminar-1]=0;
    printf(" -----------------------------------------\n");
    for (int i = 0; i < filas; i++) {
        if(i!=eliminar-1){
            printf(" %i | %s | %i unidades | %.2f $\n", i + 1, nombres[i], cantidades[i], precios[i]);
        }
    }   
}
