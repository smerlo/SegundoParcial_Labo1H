#ifndef POSICION_ARANCELARIA_H_
#define POSICION_ARANCELARIA_H_
typedef struct
{
    int id;
    char nomenclatura_arancelaria[48];
    float porcentaje_seguro;
    float porcentaje_importacion;
    float pocentaje_tasaEstadistica;
    int tipo_licencia;
}pArancelaria;

int pArancelaria_setId(pArancelaria* this, int id);
int pArancelaria_getId(pArancelaria* this, int* id);
int pArancelaria_setNomenclaturaArancelaria(pArancelaria* this, char* nArancelaria);
int pArancelaria_getNomenclaturaArancelaria(pArancelaria* this, char* nArancelaria);
int pArancelaria_setSeguro(pArancelaria* this, float seguro);
int pArancelaria_getSeguro(pArancelaria* this, float* seguro);
int pArancelaria_setImportacion(pArancelaria* this, float pImportacion);
int pArancelaria_getImportacion(pArancelaria* this, float* pImportacion);
int pArancelaria_setTasa(pArancelaria* this, float tasa);
int pArancelaria_getTasa(pArancelaria* this, float* tasa);
int pArancelaria_setTipoLicencia(pArancelaria* this, int tLicencia);
int pArancelaria_getTipoLicencia(pArancelaria* this, int* tLicencia);
pArancelaria* pArancelaria_new(void);
pArancelaria* pArancelaria_newParametros(char* idStr, char* nArancelaria, char* pSeguroStr, char* pImportacionStr, char* pTasaStr, char* tipoLicenciaStr);
void pArancelaria_delete(pArancelaria* this);
int pArancelaria_imprimir(pArancelaria* this);
float pArancelaria_CalcularCostoArgentino(pArancelaria* this, float baseImponible);
#endif /* POSICION_ARANCELARIA_H_ */
