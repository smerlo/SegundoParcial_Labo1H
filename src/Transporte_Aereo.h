#ifndef TRANSPORTE_AEREO_H_
#define TRANSPORTE_AEREO_H_
typedef struct
{
    float constante_volumetrica;
    float precio_kg;
}tAereo;

int tAereo_setConstanteVolumetrica(tAereo* this, float cVolumetrica);
int tAereo_getConstanteVolumetrica(tAereo* this, float* cVolumetrica);
int tAereo_setPrecioKg(tAereo* this, float precioKg);
int tAereo_getPrecioKg(tAereo* this, float* precioKg);
tAereo* tAereo_new(void);
tAereo* tAereo_newParametros(char* cVolumetrica, char* precioKg);
void tAereo_delete(tAereo* this);
int tAereo_imprimir(tAereo* this);
float tAereo_CalcularFlete(tAereo* this, float cmCubicos, float peso);
#endif /* TRANSPORTE_AEREO_H_ */
