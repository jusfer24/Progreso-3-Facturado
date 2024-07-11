#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "usuarios.h"
#include "inventario.h"


#define LONGITUD 10
#define LON 20
#define cont 0
#define MAX_LIBROS 50

void ingresarfactura();
    char libros[MAX_LIBROS][50];
    int cantidades[MAX_LIBROS];
    float precios[MAX_LIBROS];
    int cantidadLibros = 0;

int main(int argc, char const *argv[]) {
    int tamano, opcion, grade;
    int noma;
    int menu; 
    int i=0;
    long posicion;
    printf("--> * Bienvenido a la Libreria Andina* <--\n");
    char usuarioAp[50][50];
    char usuarioN[50][50];
    int cedula[LONGITUD];
    char libros[50][50];  
    int cantidades[50];
    float precios[50];  
   
    char buscar[LON];
    
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
                controlInventario(libros, cantidades, precios, i, noma, tamano, buscar, posicion);
                printf("------------------------------------\n");
                break;
            case 2:
                printf("------------------------------------\n");
                controlUsuario(usuarioN, usuarioAp, cedula, buscar, posicion);
                printf("------------------------------------\n");
                break;
            case 3:
                printf("------------------------------------\n"); 
                ingresarfactura(libros, cantidades, precios, &cantidadLibros);
                printf("------------------------------------\n");
                break;
            case 4:
                printf("------------------------------------\n");
                sleep(1);
                printf("Cerrando ");
                sleep(1);
                printf("el ");
                sleep(1);
                printf("programa");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".\n");
                printf("------------------------------------\n");
                break;
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opcion incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (menu != 4);
    
    return 0;
}

/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */

void ingresarfactura(){
    time_t t = time(NULL); //Obténiene el tiempo actual
     // Convierte el tiempo a una estructura de tiempo local
    struct tm tm = *localtime(&t);
    char usuarioAp[15];
    char usuarioN[15];
    int cedula;
    char libronom[15];
    int cantidad;
    float precio;
    char des[4];
    char nombre[50];
    float pagado;
    int *newcont;
    printf("\nIngrese los datos a la factura: ");
    FILE *archivof = fopen("Facturas.txt", "w");
    FILE *archivo = fopen("libros.txt", "r");
    FILE *archivotemp = fopen("librostem.txt", "w");
    if (archivo == NULL || archivof == NULL || archivotemp == NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }
    do {
        printf("\n-------------------------------------------------------------------\n");
        printf("\nIngrese el nombre: ");
        scanf("%s", usuarioN);
        printf("\nIngrese el apellido: ");
        scanf("%s", usuarioAp);
        printf("\nIngrese la RUC/cedula: ");
        scanf("%i", &cedula);
        do{
            printf("\nIngrese el libro comprado: ");
            scanf("%s", libronom);
            printf("\nIngrese la cantidad de libros comprados: ");
            scanf("%d", &cantidad);
            printf("\nIngrese el precio del libro: ");
            scanf("%f", &precio);
            //Para bajar el stock en el inventario
            while (fscanf(archivo, "%s %d %f", nombre, &cantidad, &precio) != EOF) {
                if (strcmp(nombre, libronom) == 0) {
                    fprintf(archivotemp, "%s %d %.2f\n", nombre, cantidad-1, precio);
                    continue; // Omitir la escritura de este libro al archivo temporal
                }
            fprintf(archivotemp, "%s %d %.2f\n", nombre, cantidad, precio);
            }
            fclose(archivo);
            fclose(archivotemp);
            remove("libros.txt");
            rename("librostem.txt", "libros.txt");
        }while(cantidad != 0);
        do{
            printf("Ingrese el dinero pagado: ");
            scanf("%f", &pagado);
        } while (pagado >= precio);
        printf("\n Los datos ingresados estan bien?");
        scanf("%s", des);
        printf("\n-------------------------------------------------------------------\n");
    } while (des == "si");
    *newcont=cont+1;
    fprintf(archivof, "\n      --> la Libreria Andina <--\n");
    fprintf(archivof, "Establecimiento: Quito Norte\n");
    fprintf(archivof, "Ref Factura No: 0%d", *newcont);
    fprintf(archivof, "Fecha actual: %02d-%02d-%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);//Imprime la fecha actual en formato dd-mm-yyyy
    fprintf(archivof, "Usuario: %s %s\n", usuarioN, usuarioAp);
    fprintf(archivof, "RUC/Cedula: %d", cedula);
    fprintf(archivof, "Descripcion CANT PREC TOTAL\n");
    fprintf(archivof, "%s %d %.2f %.2f\n", libronom, cantidad, precio, cantidad*precio);
    fprintf(archivof, "EFECTIVO              %.2f\n", pagado);
    fprintf(archivof, "CAMBIO                %.2f\n", pagado-precio);
    fprintf(archivof,"-------------------------------------------------------------------\n");
    fclose(archivof);
}