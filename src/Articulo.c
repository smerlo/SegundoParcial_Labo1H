#include <stdio.h>
#include <stdlib.h>
#include "Articulo.h"
#include "auxiliar.h"
#include <string.h>



int articulo_setId(Articulo* this, int id)
{
	int retorno = 0;
	if(this != NULL && id >= 0)
	{
		this->id = id;
		retorno = 1;
	}
	return retorno;
}

int articulo_getId(Articulo* this, int* id)
{
	int retorno = 0;
	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 1;
	}
	return retorno;
}

int articulo_setCodigo(Articulo* this, char* codigo)
{
	int retorno = 0;
	if(this != NULL && codigo != NULL)
	{
		strcpy(this->codigo, codigo);
		retorno = 1;
	}
	return retorno;
}

int articulo_getCodigo(Articulo* this, char* codigo)
{
	int retorno = 0;
	if(this != NULL && codigo != NULL)
	{
		strcpy(codigo, this->codigo);
		retorno = 1;
	}
		return retorno;
}

int articulo_setNombre(Articulo* this, char* nombre)
{
	int retorno = 0;
	if(this != NULL && nombre != NULL)
	{
		strcpy(this->nombre, nombre);
		retorno = 1;
	}
	return retorno;
}

int articulo_getNombre(Articulo* this, char* nombre)
{
	int retorno = 0;
	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		retorno = 1;
	}
	return retorno;
}

/*int articulo_setDescripcion(Articulo* this, char* descripcion)
{
	int retorno = 0;
	if(this != NULL && descripcion != NULL)
	{
		strcpy(this->descripcion, descripcion);
		retorno = 1;
	}
	return retorno;
}

int articulo_getDescripcion(Articulo* this, char* descripcion)
{
	int retorno = 0;
	if(this != NULL && descripcion != NULL)
	{
		strcpy(descripcion, this->descripcion);
		retorno = 1;
	}
	return retorno;
}*/

int articulo_setFob(Articulo* this, float fob)
{
	int retorno = 0;
	if(this != NULL && fob >= 0)
	{
		this->fob = fob;
		retorno = 1;
	}
	return retorno;
}

int articulo_getFob(Articulo* this, float* fob)
{
	int retorno = 0;
	if(this != NULL && fob != NULL)
	{
		*fob = this->fob;
		retorno = 1;
	}
	return retorno;
}

int articulo_setpArancelaria(Articulo* this, int pArancelaria)
{
	int retorno = 0;
	if(this != NULL && pArancelaria >= 0)
	{
		this->pArancelaria = pArancelaria;
		retorno = 1;
	}
	return retorno;
}

int articulo_getpArancelaria(Articulo* this, int* pArancelaria)
{
	int retorno = 0;
	if(this != NULL && pArancelaria != NULL)
	{
		*pArancelaria = this->pArancelaria;
		retorno = 1;
	}
	return retorno;
}

int articulo_setAncho(Articulo* this, float ancho)
{
	int retorno = 0;
	if(this != NULL && ancho >= 0)
	{
		this->ancho = ancho;
		retorno = 1;
	}
	return retorno;
}

int articulo_getAncho(Articulo* this, float* ancho)
{
	int retorno = 0;
	if(this != NULL && ancho != NULL)
	{
		*ancho = this->ancho;
		retorno = 1;
	}
	return retorno;
}

int articulo_setAlto(Articulo* this, float alto)
{
	int retorno = 0;
	if(this != NULL && alto >= 0)
	{
		this->alto = alto;
		retorno = 1;
	}
	return retorno;
}

int articulo_getAlto(Articulo* this, float* alto)
{
	int retorno = 0;
	if(this != NULL && alto != NULL)
	{
		*alto = this->alto;
		retorno = 1;
	}
	return retorno;
}

int articulo_setProfundidad(Articulo* this, float profundidad)
{
	int retorno = 0;
	if(this != NULL && profundidad >= 0)
	{
		this->profundidad = profundidad;
		retorno = 1;
	}
	return retorno;
}

int articulo_getProfundidad(Articulo* this, float* profundidad)
{
	int retorno = 0;
	if(this != NULL && profundidad != NULL)
	{
		*profundidad = this->profundidad;
		retorno = 1;
	}
	return retorno;
}

int articulo_setPeso(Articulo* this, float peso)
{
	int retorno = 0;
	if(this != NULL && peso >= 0)
	{
		this->peso = peso;
		retorno = 1;
	}
	return retorno;
}

int articulo_getPeso(Articulo* this, float* peso)
{
	int retorno = 0;
	if(this != NULL && peso != NULL)
	{
		*peso = this->peso;
		retorno = 1;
	}
	return retorno;
}

int articulo_setPaisFabricacion(Articulo* this, char* paisFabricacion)
{
	int retorno = 0;
	if(this != NULL && paisFabricacion != NULL)
	{
		strcpy(this->paisFabricacion, paisFabricacion);
		retorno = 1;
	}
	return retorno;
}

int articulo_getPaisFabricacion(Articulo* this, char* paisFabricacion)
{
	int retorno = 0;
	if(this != NULL && paisFabricacion != NULL)
	{
		strcpy(paisFabricacion, this->paisFabricacion);
		retorno = 1;
	}
	return retorno;
}

/**
 * \brief Reserva un espacio en memoria para guardar un Articulo
 * \param Void (No recibe nada en los parametros)
 * \return Retorna un puntero al espacio de memoria donde guardará el Articulo
 */
Articulo* articulo_new(void)
{
	Articulo* aux = NULL;
	aux = malloc(sizeof(Articulo));
	return aux;
}


Articulo* articulo_newParametros(char* idStr, char* codigo, char* nombre, char* fobStr, char* pArancelariaStr,
										char* anchoStr, char* altoStr, char* profundidadStr, char* pesoStr, char* paisFabricacion)
{
	Articulo* aux = NULL;
	aux = articulo_new();
	if(aux != NULL && idStr != NULL && codigo != NULL && nombre != NULL && fobStr != NULL && pArancelariaStr != NULL && anchoStr != NULL &&
			altoStr != NULL && profundidadStr != NULL && pesoStr != NULL && paisFabricacion != NULL)
	{
		if(aux_verificarNumerica(idStr, 10) == 0 && aux_verificarFlotante(fobStr) == 0 && aux_verificarFlotante(anchoStr) == 0 && aux_verificarFlotante(altoStr) == 0 &&
				aux_verificarFlotante(profundidadStr) == 0 && aux_verificarFlotante(pesoStr) == 0 && aux_verificarNumerica(pArancelariaStr, 10) == 0)
		{
			if(articulo_setId(aux, atoi(idStr)) == 1 && articulo_setCodigo(aux, codigo) == 1 &&
				articulo_setNombre(aux, nombre) == 1 && articulo_setFob(aux, atof(fobStr)) == 1 &&
				articulo_setpArancelaria(aux, atoi(pArancelariaStr)) == 1 && articulo_setAncho(aux, atof(anchoStr)) == 1 &&
				articulo_setAlto(aux, atof(altoStr)) == 1 && articulo_setProfundidad(aux, atof(profundidadStr)) == 1 &&
				articulo_setPeso(aux, atof(pesoStr)) == 1 && articulo_setPaisFabricacion(aux, paisFabricacion) == 1)

			{
				return aux;
			}
			else
			{
				articulo_delete(aux);
			}
		}
	}
	return NULL;
}

void articulo_delete(Articulo* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int articulo_imprimir(Articulo* this)
{
	int retorno=0;
	int id;
	char codigo[24];
	char nombre[128];
	float fob;
	int pArancelaria;
	float ancho;
	float alto;
	float profundidad;
	float peso;
	char paisFabricacion[48];

	if(this != NULL)
	{
		retorno = 1;
		articulo_getId(this,&id);
		articulo_getCodigo(this,codigo);
		articulo_getNombre(this,nombre);
		articulo_getFob(this,&fob);
		articulo_getpArancelaria(this, &pArancelaria);
		articulo_getAncho(this,&ancho);
		articulo_getAlto(this,&alto);
		articulo_getProfundidad(this, &profundidad);
		articulo_getPeso(this,&peso);
		articulo_getPaisFabricacion(this,paisFabricacion);
		printf("%d%15s%15s%15f%15d%15f%15f%15f%15f%15s\n",id,codigo,nombre,fob,pArancelaria,ancho,alto,profundidad,peso,paisFabricacion);
	}
	return retorno;
}

float articulo_calcularMetrosCubicos(Articulo* this)
{
	float retorno = -1;
	float ancho;
	float alto;
	float profundidad;

	if(this != NULL)
	{
		articulo_getAncho(this,&ancho);
		articulo_getAlto(this,&alto);
		articulo_getProfundidad(this, &profundidad);
		retorno = (alto/100)*(ancho/100)*(profundidad/100);
	}
	return retorno;
}

float articulo_calcularCmCubicos(Articulo* this)
{
	float retorno = -1;
	float ancho;
	float alto;
	float profundidad;

	if(this != NULL)
	{
		articulo_getAncho(this,&ancho);
		articulo_getAlto(this,&alto);
		articulo_getProfundidad(this, &profundidad);
		retorno = ancho*alto*profundidad;
	}
	return retorno;
}

