#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "usuarios.h"
/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */

void menuUsu(){
    printf("\n");
    printf("Usuarios:\n");
    printf("[1] Ingresar Usuario\n");
    printf("[2] Imprimir Usuarios\n");
    printf("[3] Eliminar Usuario\n");
    printf("[4] Consultar Usuario\n");
    printf("[5] Modificar Usuario\n");
    printf("[6] Regresar a Menu Principal\n");
}

void controlUsuario(char usuarioN[][50], char usuarioAp[][50], int cedula[], char buscar[], long posicion) {
    int usuent;
    int cedulaBuscada;
    do {
        printf("//===================================//\n");
        menuUsu();
        printf("//===================================//\n");
        scanf("%d", &usuent);
        
        switch (usuent) {
            case 1:
                printf("//-----------------//-----------------//\n");
                ingresarUsuario();
                printf("//-----------------//-----------------//\n");
                break;
            case 2:
                printf("//-----------------//-----------------//\n");
                leerUsuarios(usuarioN,usuarioAp, cedula);
                printf("//-----------------//-----------------//\n");
                break;    
            case 3:
                printf("//-----------------//-----------------//\n");
                eliminarUsuario();
                printf("//-----------------//-----------------//\n");
                break;    
            case 4:
                printf("//-----------------//-----------------//\n");
                printf("Ingrese la cédula de la persona que busca: ");
                scanf("%d", &cedulaBuscada);
                buscarUsu(cedulaBuscada, &posicion);
                if (posicion != -1) {
                    printf("\nEncontrado\n");
                    mostrarInfoUsu(posicion);
                } else {
                    printf("\nUsuario no encontrado\n");
                }
                printf("//-----------------//-----------------//\n");
                break;
            case 5:
                printf("//-----------------//-----------------//\n");
                printf("Ingrese la cédula de la persona que desea modificar: ");
                scanf("%d", &cedulaBuscada);
                buscarUsu(cedulaBuscada,&posicion);
                if (posicion != -1) {
                    printf("\nUsuario encontrado\n");
                    modificarInfoUsu(posicion);
                } else {
                    printf("\n");
                }
                 printf("//-----------------//-----------------//\n");
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
    } while (usuent != 6);
}


int validarCedula(char cedula[]) {
    int n = strlen(cedula);
    if (n != 10) {
        return 0; // La cedula debe tener 10 dígitos
    }
    // Verificar que los dos primeros digitos estén en el rango valido
    int provincia = (cedula[0] - '0') * 10 + (cedula[1] - '0');
    if (provincia < 0 || provincia > 24) {
        return 0;
    }
    // Verificar que el tercer dígito sea menor a 6
    if (cedula[2] < '0' || cedula[2] > '5') {
        return 0;
    }
    // Coeficientes de verificación
    int coeficientes[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    int suma = 0;
    // Calcular la suma con los coeficientes
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        int producto = digito * coeficientes[i];
        if (producto > 9) {
            producto -= 9;
        }
        suma += producto;
    }
    // Obtener el siguiente múltiplo de 10
    int siguienteMultiplo10 = ((suma + 9) / 10) * 10;
    int digitoVerificador = siguienteMultiplo10 - suma;
    // Verificar que el último dígito sea igual al dígito verificador
    return (digitoVerificador == (cedula[9] - '0'));
}


void ingresarUsuario() {
    printf("-------------------------------------------------------------------\n");
    char usuarioAp[20][15];
    char usuarioN[20][15];
    int cedula[20];
    char cedula_str[20][11]; // Arreglo para almacenar las cédulas como cadena de caracteres
    int cant;
    
    printf("Ingrese cuantos Usuarios va a registrar: ");
    scanf("%d", &cant);
    
    FILE *archivo;
    archivo = fopen("Usuarios.txt", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    
    for (int i = 0; i < cant; i++) {
        printf("-------------------------------------------------------------------\n");
        
        // Ingreso de la cédula como entero
        printf("Ingrese la cedula: ");
        scanf("%d", &cedula[i]);
        
        // Convertir la cédula a cadena de caracteres (char[])
        sprintf(cedula_str[i], "%010d", cedula[i]);
        
        // Validar la cédula
        if (!validarCedula(cedula_str[i])) {
            printf("\nLa cedula ingresada no es valida. Ingrese otra cedula:\n");
            scanf("%d", &cedula[i]);
            sprintf(cedula_str[i], "%010d", cedula[i]); // Actualizar la cadena de caracteres
        }
        
        // Verificar si la cédula ya está registrada
        long tempPosicion = -1;
        buscarUsu(cedula[i], &tempPosicion);
        
        while (tempPosicion != -1) {
            printf("\nEste usuario ya fue ingresado:\n");
            printf("------------------------------------\n");
            mostrarInfoUsu(tempPosicion);
            printf("-------------------------------------\n");
            printf("-------------////-------------\n");
            printf("|1| Ingresar otro usuario\n");
            printf("|2| Salir\n");
            printf("-------------////-------------\n");
            printf("Ingrese su opcion: ");
            int quefuef;
            scanf("%d", &quefuef);
            
            if (quefuef == 1) {
                printf("*********************************\n");
                printf("Ingrese otra cedula: ");
                scanf("%d", &cedula[i]);
                buscarUsu(cedula[i], &tempPosicion);
                 printf("*********************************\n");
            } else if (quefuef == 2) {
                fclose(archivo);
                return;
            } else {
                printf("Opcion no valida. Ingrese 1 o 2.\n");
            }
        }
        
        printf("Ingrese el nombre: ");
        scanf("%s", usuarioN[i]);
        printf("Ingrese el apellido: ");
        scanf("%s", usuarioAp[i]);
        
        fprintf(archivo, " %s %s %d \n", usuarioN[i], usuarioAp[i], cedula[i]);
        printf("-------------------------------------------------------------------\n");
    }
    
    fclose(archivo);
}

void leerUsuarios(char usuarioN[][50], char usuarioAp[][50], int cedula[]) {
    FILE *archivo;
    archivo = fopen("Usuarios.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("*********************************************\n");
    printf("| Nombre      | Apellido       | Cedula |\n");
    printf("*********************************************\n");

    int i = 0;
    
    while (fscanf(archivo,"%99s %99s %99d", usuarioN[i], usuarioAp[i],&cedula[i])== 3){
        printf("| %-11s  | %-11s       | %-11d \n", usuarioN[i], usuarioAp[i],cedula[i] );
        i++;
    }

    printf("---------------------------------------------\n");

    fclose(archivo);
}


void buscarUsu(int buscado, long* pos) {
    FILE *archivo;
    archivo = fopen("Usuarios.txt", "r");
    char linea[200];
    char nombre[100];
    char apellido[100];
    int cedula;
    *pos = -1;
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    while (fgets(linea, 200, archivo) != NULL) {
        sscanf(linea, "%99s %99s %d", apellido, nombre, &cedula);
        if (cedula == buscado) {
            *pos = ftell(archivo) - strlen(linea);
            fclose(archivo);
            return;
        }
    }
    fclose(archivo);
}

void mostrarInfoUsu(long pos) {
    FILE *archivo;
    archivo = fopen("Usuarios.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    
    fseek(archivo, pos, SEEK_SET); // Moverse a la posición en el archivo
    
    char nombre[50];
    char apellido[50];
    int cedula;
    
    // %48s se usa para especificar que fscanf leerá hasta 49 caracteres o hasta encontrar un salto de línea 
    fscanf(archivo, "%49s %49s %d", nombre, apellido, &cedula);
    
    // Imprimir cada dato en líneas separadas
    printf("\nApellido: %s\n", apellido);
    printf("Nombre: %s\n", nombre);
    printf("Cédula: %d\n", cedula);
    
    fclose(archivo);
}


int leerEnteroEntre(char*mensaje, int limInferior,int limSuperior){
  int valor;
    do{
        printf("%s", mensaje);
        scanf("%d",&valor);
         if((valor < limInferior)||(valor > limSuperior)){
          printf("-------------------------------------------------------------------\n");
           printf("Error: El numero debe estar entre %d y %d.\n", limInferior, limSuperior);
          printf("-------------------------------------------------------------------\n");
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
          printf("-------------------------------------------------------------------\n");
            printf("Error");
          printf("-------------------------------------------------------------------\n");
        }
    }while(valor <= 0);
    return valor;
}

float leerFlotantePositivo(char* mensaje){
    float valor;
    do{
        printf("%s",mensaje);
        scanf("%f",&valor);
         if(valor <= 0){
            printf("-------------------------------------------------------------------\n");
            printf("Error");
            printf("-------------------------------------------------------------------\n");
        }
    }while(valor <= 0);
   return valor;
}

void eliminarUsuario() {
    char nombre[50], apellido[50];
    printf("Ingrese el nombre del usuario que desea eliminar: ");
    scanf("%s", nombre);
    printf("Ingrese el apellido del usuario que desea eliminar: ");
    scanf("%s", apellido);

    FILE *archivo = fopen("Usuarios.txt", "r");
    FILE *tempArchivo = fopen("tempUsuarios.txt", "w");

    if (archivo == NULL || tempArchivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char usuarioN[50], usuarioAp[50];
    int cedula;
    int encontrado = 0;

    while (fscanf(archivo, " %s %s %d", usuarioN, usuarioAp, &cedula) != EOF) { //El bucle se repite hasta que llegue al final del archivo por EOF(End Of File)
        if (strcmp(usuarioN, nombre) == 0 && strcmp(usuarioAp, apellido) == 0) {
            encontrado = 1;
            continue; // Omitir la escritura de este usuario al archivo temporal
        }
        fprintf(tempArchivo, " %s %s %d\n", usuarioN, usuarioAp, cedula);
    }

    fclose(archivo);
    fclose(tempArchivo);

    // Eliminar el archivo original y renombrar el temporal
    remove("Usuarios.txt");
    rename("tempUsuarios.txt", "Usuarios.txt");

    if (encontrado)
        printf("Usuario eliminado correctamente.\n");
    else
        printf("Usuario no encontrado.\n");
}


void modificarInfoUsu(long pos) {
    FILE *archivo;
    archivo = fopen("Usuarios.txt", "r+");
    char nombre[50];
    char apellido[50];
    int cedula;
    char nuevoNombre[50];
    char nuevoApellido[50];
    char nuevaCedula_str[11]; // Para almacenar la nueva cédula como cadena de caracteres

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    
    fseek(archivo, pos, SEEK_SET);
    fscanf(archivo, " %s %s %d", nombre, apellido, &cedula);
    printf("\nApellido actual: %s\nNombre actual: %s\nCédula actual: %d\n", apellido, nombre, cedula);

    // Ingreso del nuevo apellido y nombre
    printf("Ingrese el nuevo apellido: ");
    scanf("%s", nuevoApellido);
    printf("Ingrese el nuevo nombre: ");
    scanf("%s", nuevoNombre);

    // Validación y entrada de la nueva cédula
    int esCedulaValida = 0;
    while (!esCedulaValida) {
        printf("Ingrese la nueva cédula: ");
        scanf("%s", nuevaCedula_str);

        if (!validarCedula(nuevaCedula_str)) {
            printf("La cédula ingresada no es válida para Ecuador. Ingrese nuevamente.\n");
        } else {
            esCedulaValida = 1;
        }
    }

    // Convertir la cédula nueva de cadena a entero
    sscanf(nuevaCedula_str, "%d", &cedula);

    // Regresar al inicio de la posición para sobrescribir los datos
    fseek(archivo, pos, SEEK_SET);
    fprintf(archivo, "%s %s %d\n", nuevoNombre, nuevoApellido, cedula);

    fclose(archivo);
    printf("Información modificada correctamente.\n");
}


