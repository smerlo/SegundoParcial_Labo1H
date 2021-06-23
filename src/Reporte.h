#ifndef REPORTE_H_
#define REPORTE_H_
typedef struct
{
    int idArt;
    char codigo[24];
    char nombre[128];
    //char descripcion[256];
    float fob;
    char pArancelaria[48];
    float mCubicos;
    float cmCubicos;
    float valorAereo;
    float valorMaritimo;
}Reporte;
int reporte_setId(Reporte* this, int idArt);
int reporte_getId(Reporte* this, int* idArt);
int reporte_setCodigo(Reporte* this, char* codigo);
int reporte_getCodigo(Reporte* this, char* codigo);
int reporte_setCodigo(Reporte* this, char* nombre);
int reporte_getNombre(Reporte* this, char* nombre);
//int reporte_setDescripcion(Reporte* this, char* descripcion);
//int reporte_getDescripcion(Reporte* this, char* descripcion);
int reporte_setFob(Reporte* this, float fob);
int reporte_getFob(Reporte* this, float* fob);
int reporte_setpArancelaria(Reporte* this, char* pArancelaria);
int reporte_getpArancelaria(Reporte* this, char* pArancelaria);
int reporte_setmCubicos(Reporte* this, float mCubicos);
int reporte_getmCubicos(Reporte* this, float* mCubicos);
int reporte_setcmCubicos(Reporte* this, float cmCubicos);
int reporte_getcmCubicos(Reporte* this, float* cmCubicos);
int reporte_setvalorAereo(Reporte* this, float valorAereo);
int reporte_getvalorAereo(Reporte* this, float* valorAereo);
int reporte_setvalorMaritimo(Reporte* this, float valorMaritimo);
int reporte_getvalorMaritimo(Reporte* this, float* valorMaritimo);
Reporte* reporte_new(void);
Reporte* reporte_newParametros(char* idStr, char* codigo, char* nombre, char* fobStr, char* pArancelariaStr,	char* mCubicosStr, char* cmCubicosStr, char* valorAereoStr, char* valorMaritimoStr);
void reporte_delete(Reporte* this);
int reporte_imprimir(Reporte* this);
int reporte_CompararId(void* compareOne,void* compareTwo);
int reporte_CompararNombre(void* compareOne,void* compareTwo);
int reporte_CompararCodigo(void* compareOne,void* compareTwo);
int reporte_CompararNArancelaria(void* compareOne,void* compareTwo);
int reporte_CompararFob(void* compareOne,void* compareTwo);
int reporte_CompararValorAereo(void* compareOne,void* compareTwo);
int reporte_CompararValorMaritimo(void* compareOne,void* compareTwo);
int reporte_imprimirParancelariaMayor(Reporte* this);
#endif /* REPORTE_H_ */
