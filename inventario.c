#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "inventario.h"

/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */

void menuIn(){
    printf("\n");
    printf("Inventario:\n");
    printf("[1] Agregar Producto\n");
    printf("[2] Imprimir Inventario\n");
    printf("[3] Consultar Producto\n");
    printf("[4] Eliminar Producto\n");
    printf("[5] Modificar Producto\n");
    printf("[6] Regresar a Menu Principal\n");
}

void controlInventario(char libros[][50], int cantidades[], float precios[], int i, int tamano, int noma,char buscar[], long posicion ) {
    int ivent;
    int cantidadLibros = 0;
    do {
        printf("//===================================//\n");
        menuIn();
        printf("//===================================//\n");
        scanf("%d", &ivent);
          
        switch (ivent) {
            case 1:
                printf("//-----------------/-----------------//\n");
                agregarLibro(libros, cantidades, precios, i, noma, tamano);
                printf("\n Inventario modificado:\n");
                printf("//-----------------/-----------------//\n");
                break;

            case 2:
                printf("//-----------------/-----------------//\n");
                 leerLibros(libros, cantidades, precios);
                printf("//-----------------/-----------------//\n");
                break;
                  
            case 3:
                printf("//-----------------/-----------------//\n");
                printf ("Ingrese producto que busca: ");
                scanf("%s",buscar);
                buscarPosicion(buscar,&posicion);
                 if(posicion != -1){
                    printf("\nEncontrado\n");
                    Infolibros(posicion);
                }else
                    printf("No se encontro\n");
                printf("//-----------------/-----------------//\n");
                break;
            case 4:
                printf("//-----------------/-----------------//\n");
                eliminarLibro();
                printf("//-----------------/-----------------//\n");
                break;
            case 5:
                printf("//-----------------/-----------------//\n");
                printf ("Ingrese producto que busca: ");
                scanf("%s",buscar);
                buscarPosicion(buscar,&posicion);
                 if(posicion != -1){
                    printf("\nEncontrado\n");
                    modificarInfolibros(posicion);
                }else
                    printf("No se encontro\n");
                printf("//-----------------/-----------------//\n");
                break;
            case 6:
                printf("------------------------------------\n");
                sleep(1);
                printf("Regresando");
                 sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".\n");
                break;
                
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opcion incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (ivent != 6);
}


void agregarLibro(char libros[][50], int cantidades[], float precios[], int i, int tamano, int noma){
    printf("-------------------------------------------------------------------\n");
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
        scanf("%s", libros[i]);
        
        // Validar que no se repita el nombre del libro
        char tempLibro[50];
        long tempPosicion;
        strcpy(tempLibro, libros[i]);
        buscarPosicion(tempLibro, &tempPosicion);
        while (tempPosicion != -1) {
            printf("\nEste libro ya fue ingresado. Ingrese otro título: ");
            scanf("%s", libros[i]);
            strcpy(tempLibro, libros[i]);
            buscarPosicion(tempLibro, &tempPosicion);
        }
        
        cantidades[i] = leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresado: ");
        precios[i] = leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
   
        tamano = noma;
        printf("-------------------------------------------------------------------\n");
        fprintf(archivo,"%s %d %.2f$\n", libros[i], cantidades[i], precios[i]);
    }
    fclose(archivo);
}


void leerLibros(char libros[][50], int cantidades[], float precios[]) {
    FILE *archivo = fopen("libros.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("*********************************************\n");
    printf("| Nombre                 | Cantidad | Precio |\n");
    printf("*********************************************\n");

    int i = 0;
    while (fscanf(archivo, "%s %d %f$", libros[i], &cantidades[i], &precios[i])== 3) {
        printf("| %-22s  | %d       | %.2f $\n", libros[i], cantidades[i], precios[i]);
        i++;
    }

    printf("---------------------------------------------\n");

    fclose(archivo);
}


void buscarPosicion(const char* buscado, long* pos) {
    FILE *archivo;
    archivo = fopen("libros.txt", "r");
    char libros[50];
    int cantidades;
    float precios;
    *pos = -1;
    if (archivo == NULL) {
        printf("No se abrio el archivo");
        return;
    }
    while (!feof(archivo)) {
        fscanf(archivo, "%s %d %f", libros, &cantidades, &precios);
        if (strcmp(libros, buscado) == 0) {
            *pos = ftell(archivo) - (strlen(libros) + sizeof(cantidades) + sizeof(precios));
            fclose(archivo);
            return;
        }
    }
    fclose(archivo);
}

void Infolibros(long pos) {
    FILE *archivo;
    archivo = fopen("libros.txt", "r");
    char libro[50];
    int cantidades;
    float precios;
    if (archivo == NULL) {
        printf("No se abrio el archivo");
        return;
    }
    
    fseek(archivo, pos, SEEK_SET);
    fscanf(archivo, "%s %d %f", libro, &cantidades, &precios);
    printf("\n%s %d %.2f\n", libro, cantidades, precios);
    fclose(archivo);
}

void modificarInfolibros(long pos) {
    FILE *archivo;
    archivo = fopen("libros.txt", "r+");
    char libro[50];
    int cantidades;
    float precios;
    
    char nuevolibro[50];
    int nuevocantidades;
    float nuevoprecios;

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    
    fseek(archivo, pos, SEEK_SET);
    fscanf(archivo, "%s %d %f", libro, &cantidades, &precios);
    printf("\nLibro actual: %s\nCantidad actual: %d\nPrecio actual: %.2f\n", libro, cantidades, precios);

    printf("Ingrese el nuevo libro: ");
    scanf("%s", nuevolibro);
    printf("Ingrese la nueva cantidad: ");
    scanf("%d", &nuevocantidades);
    printf("Ingrese el nuevo precio: ");
    scanf("%f", &nuevoprecios);

    // Regresar al inicio de la posición para sobrescribir los datos
    fseek(archivo, pos, SEEK_SET);
    fprintf(archivo, "%s %d %.2f$\n", nuevolibro, nuevocantidades, nuevoprecios);

    fclose(archivo);
    printf("Información modificada correctamente.\n");
}

void eliminarLibro() {
    char nombreLibro[50];
    printf("Ingrese el nombre del libro que desea eliminar: ");
    scanf("%s", nombreLibro);

    FILE *archivo = fopen("libros.txt", "r");
    FILE *tempArchivo = fopen("tempLibros.txt", "w");

    if (archivo == NULL || tempArchivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char libros[50];
    int cantidad;
    float precio;
    int econtrado = 0;

    while (fscanf(archivo, "%s %d %f$", libros, &cantidad, &precio) != EOF) { //El bucle se repite hasta que llegue al final del archivo por EOF(End Of File)
        if (strcmp(libros, nombreLibro) == 0) {
            econtrado == 1;
            continue; // Omitir la escritura de este libro al archivo temporal
        }
        fprintf(tempArchivo, "%s %d %.2f$\n", libros, cantidad, precio);
    }

    fclose(archivo);
    fclose(tempArchivo);

    // Eliminar el archivo original y renombrar el temporal
    remove("libros.txt");
    rename("tempLibros.txt", "libros.txt");

    if (econtrado==1){
        printf("Libro eliminado correctamente.\n");
    }else{
        printf("Libro no encontrado.\n");
    }
}