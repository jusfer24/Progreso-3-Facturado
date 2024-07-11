
void menuIn();
void controlInventario(char[][50], int[], float[], int, int, int, char[], long);
void agregarLibro(char[][50], int[], float[], int, int, int);
void leerLibros(char libros[][50], int [], float []);
void buscarPosicion(const char* buscado, long* pos);
void Infolibros(long pos);
void eliminarLibro();
void modificarInfolibros(long);

int leerEnteroPositivo(char* mensaje);
int leerEnteroEntre(char* mensaje, int limInferior, int limSuperior);
float leerFlotantePositivo(char*);