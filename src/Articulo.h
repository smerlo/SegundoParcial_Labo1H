#ifndef articulo_H_INCLUDED
#define articulo_H_INCLUDED
typedef struct
{
    int id;
    char codigo[24];
    char nombre[128];
    //char descripcion[256];
    float fob;
    int pArancelaria;
    float ancho;
    float alto;
    float profundidad;
    float peso;
    char paisFabricacion[48];
}Articulo;

int articulo_setId(Articulo* this, int id);
int articulo_getId(Articulo* this, int* id);
int articulo_setCodigo(Articulo* this, char* codigo);
int articulo_getCodigo(Articulo* this, char* codigo);
int articulo_setNombre(Articulo* this, char* nombre);
int articulo_getNombre(Articulo* this, char* nombre);
//int articulo_setDescripcion(Articulo* this, char* descripcion);
//int articulo_getDescripcion(Articulo* this, char* descripcion);
int articulo_setFob(Articulo* this, float fob);
int articulo_getFob(Articulo* this, float* fob);
int articulo_setpArancelaria(Articulo* this, int pArancelaria);
int articulo_getpArancelaria(Articulo* this, int* pArancelaria);
int articulo_setAncho(Articulo* this, float ancho);
int articulo_getAncho(Articulo* this, float* ancho);
int articulo_setAlto(Articulo* this, float alto);
int articulo_getAlto(Articulo* this, float* alto);
int articulo_setProfundidad(Articulo* this, float profundidad);
int articulo_getProfundidad(Articulo* this, float* profundidad);
int articulo_setPeso(Articulo* this, float peso);
int articulo_getPeso(Articulo* this, float* peso);
int articulo_setPaisFabricacion(Articulo* this, char* paisFabricacion);
int articulo_getPaisFabricacion(Articulo* this, char* paisFabricacion);
Articulo* articulo_new(void);
Articulo* articulo_newParametros(char* idStr, char* codigo, char* nombre, char* fobStr, char* pArancelariaStr, char* anchoStr, char* altoStr, char* profundidadStr, char* pesoStr, char* paisFabricacion);
void articulo_delete(Articulo* this);
int articulo_imprimir(Articulo* this);
float articulo_calcularMetrosCubicos(Articulo* this);
float articulo_calcularCmCubicos(Articulo* this);
#endif // articulo_H_INCLUDED
