#include <stdio.h>
#include "lecturas.h"
#include "operacionesVec.h"

void ingresarLibros(char nombres[][50], int cantidades[], float precios[], int tamano) {
    printf("Ingrese los datos en el siguiente orden: \n");
    printf("*********************************************\n");
    printf("|Nombre | Cantidad | Precio|\n");
    printf("*********************************************\n");
    for (int i = 0; i < tamano; i++) {
        printf(" -----------------------------------------\n"); 
        printf("Ingrese el nombre del libro %d: ", i + 1);
        scanf("%s", nombres[i]);
        cantidades[i]=leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresdo: ");
        precios[i]=leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
    }
}

void imprimirLibros(char nombres[][50],int cantidades[], float precios[], int tamano) {
    printf("Inventario-Libreria Andina\n");
    printf("|Nombre     | Cantidad   | Precio|\n");
    for (int i = 0; i < tamano; i++) {
        printf(" %i | %s | %i unidades | %.2f $\n", i + 1, nombres[i], cantidades[i], precios[i]);
    }
}

void mostrarmenu(){
    printf("\n");
    printf("********************\n");
    printf("Menu de opciones:\n");
    printf("1. Editar un dato\n");
    printf("2. Agregar al inventario\n");
    printf("3. Borrar dato\n");
    printf("4. Cerrar\n");
    printf("********************\n");
}
void agregarLibro(char nombres[][50], int cantidades[], float precios[], int tamano){
    printf("Ingrese el nombre del nuevo libro %d: ", tamano);
    scanf("%s", nombres[tamano - 1]);
    cantidades[tamano - 1]=leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresdo: ");
    precios[tamano - 1]=leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
}

void borrarLibro(char nombres[][50], int cantidades[], float precios[], int tamano){
    int eliminar=0;
    eliminar = leerEnteroEntre("Ingrese el numero de libro que desea eliminar: ", 1, tamano);
    nombres[eliminar-1]=="null";
    cantidades[eliminar-1]=0;
    precios[eliminar-1]=0;
    printf(" -----------------------------------------\n");
    for (int i = 0; i < tamano; i++) {
        if(i!=eliminar-1){
            printf(" %i | %s | %i unidades | %.2f $\n", i + 1, nombres[i], cantidades[i], precios[i]);
        }
    }   
}

void editarLibro(char nombres[][50], int cantidades[], float precios[], int tamano) {
    int edit;
    edit = leerEnteroEntre("Ingrese el numero de libro que desea editar: ", 1, tamano);
    printf("Ingrese el nuevo nombre  %d: ", edit);
    scanf("%s", nombres[edit - 1]);
    cantidades[edit - 1]=leerEnteroPositivo("Ingrese la nueva cantidad de libros: ");
    precios[edit - 1]=leerFlotantePositivo("Ingrese el nuevo precio del libro: ");
    printf("Editado con exito.\n");
}
