
int leerEnteroPositivo(char* mensaje);
int leerEnteroEntre(char* mensaje, int limInferior, int limSuperior);
float leerFlotantePositivo(char*);

void menuUsu();
void controlUsuario(char[][50] ,char[][50], int[],char[],long);
void ingresarUsuario();
void buscarUsu(int buscado, long* pos);
void mostrarInfoUsu(long pos);
void eliminarUsuario();
void modificarInfoUsu(long);
void leerUsuarios(char usuarioN[][50], char usuarioAp[][50], int cedula[]);

int validarCedula(char cedula[]);