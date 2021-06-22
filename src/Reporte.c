#include <stdio.h>
#include <stdlib.h>
#include "Reporte.h"
#include "auxiliar.h"
#include <string.h>

int reporte_setId(Reporte* this, int idArt)
{
	int retorno = 0;
	if(this != NULL && idArt >= 0)
	{
		this->idArt = idArt;
		retorno = 1;
	}
	return retorno;
}

int reporte_getId(Reporte* this, int* idArt)
{
	int retorno = 0;
	if(this != NULL && idArt != NULL)
	{
		*idArt = this->idArt;
		retorno = 1;
	}
	return retorno;
}

int reporte_setCodigo(Reporte* this, char* codigo)
{
	int retorno = 0;
	if(this != NULL && codigo != NULL)
	{
		strcpy(this->codigo, codigo);
		retorno = 1;
	}
	return retorno;
}

int reporte_getCodigo(Reporte* this, char* codigo)
{
	int retorno = 0;
	if(this != NULL && codigo != NULL)
	{
		strcpy(codigo, this->codigo);
		retorno = 1;
	}
		return retorno;
}

int reporte_setNombre(Reporte* this, char* nombre)
{
	int retorno = 0;
	if(this != NULL && nombre != NULL)
	{
		strcpy(this->nombre, nombre);
		retorno = 1;
	}
	return retorno;
}

int reporte_getNombre(Reporte* this, char* nombre)
{
	int retorno = 0;
	if(this != NULL && nombre != NULL)
	{
		strcpy(nombre, this->nombre);
		retorno = 1;
	}
	return retorno;
}

int reporte_setDescripcion(Reporte* this, char* descripcion)
{
	int retorno = 0;
	if(this != NULL && descripcion != NULL)
	{
		strcpy(this->descripcion, descripcion);
		retorno = 1;
	}
	return retorno;
}

int reporte_getDescripcion(Reporte* this, char* descripcion)
{
	int retorno = 0;
	if(this != NULL && descripcion != NULL)
	{
		strcpy(descripcion, this->descripcion);
		retorno = 1;
	}
	return retorno;
}

int reporte_setFob(Reporte* this, float fob)
{
	int retorno = 0;
	if(this != NULL && fob >= 0)
	{
		this->fob = fob;
		retorno = 1;
	}
	return retorno;
}

int reporte_getFob(Reporte* this, float* fob)
{
	int retorno = 0;
	if(this != NULL && fob != NULL)
	{
		*fob = this->fob;
		retorno = 1;
	}
	return retorno;
}

int reporte_setpArancelaria(Reporte* this, char* pArancelaria)
{
	int retorno = 0;
	if(this != NULL && pArancelaria != NULL)
	{
		strcpy(this->pArancelaria, pArancelaria );
		retorno = 1;
	}
	return retorno;
}

int reporte_getpArancelaria(Reporte* this, char* pArancelaria)
{
	int retorno = 0;
	if(this != NULL && pArancelaria != NULL)
	{
		strcpy(pArancelaria, this->pArancelaria);
		retorno = 1;
	}
	return retorno;
}

int reporte_setmCubicos(Reporte* this, float mCubicos)
{
	int retorno = 0;
	if(this != NULL && mCubicos >= 0)
	{
		this->mCubicos = mCubicos;
		retorno = 1;
	}
	return retorno;
}

int reporte_getmCubicos(Reporte* this, float* mCubicos)
{
	int retorno = 0;
	if(this != NULL && mCubicos != NULL)
	{
		*mCubicos = this->mCubicos;
		retorno = 1;
	}
	return retorno;
}

int reporte_setcmCubicos(Reporte* this, float cmCubicos)
{
	int retorno = 0;
	if(this != NULL && cmCubicos >= 0)
	{
		this->cmCubicos = cmCubicos;
		retorno = 1;
	}
	return retorno;
}

int reporte_getcmCubicos(Reporte* this, float* cmCubicos)
{
	int retorno = 0;
	if(this != NULL && cmCubicos != NULL)
	{
		*cmCubicos = this->cmCubicos;
		retorno = 1;
	}
	return retorno;
}

int reporte_setvalorAereo(Reporte* this, float valorAereo)
{
	int retorno = 0;
	if(this != NULL && valorAereo >= 0)
	{
		this->valorAereo = valorAereo;
		retorno = 1;
	}
	return retorno;
}

int reporte_getvalorAereo(Reporte* this, float* valorAereo)
{
	int retorno = 0;
	if(this != NULL && valorAereo != NULL)
	{
		*valorAereo = this->valorAereo;
		retorno = 1;
	}
	return retorno;
}

int reporte_setvalorMaritimo(Reporte* this, float valorMaritimo)
{
	int retorno = 0;
	if(this != NULL && valorMaritimo >= 0)
	{
		this->valorMaritimo = valorMaritimo;
		retorno = 1;
	}
	return retorno;
}

int reporte_getvalorMaritimo(Reporte* this, float* valorMaritimo)
{
	int retorno = 0;
	if(this != NULL && valorMaritimo != NULL)
	{
		*valorMaritimo = this->valorMaritimo;
		retorno = 1;
	}
	return retorno;
}

/**
 * \brief Reserva un espacio en memoria para guardar un Articulo
 * \param Void (No recibe nada en los parametros)
 * \return Retorna un puntero al espacio de memoria donde guardará el Articulo
 */
Reporte* reporte_new(void)
{
	Reporte* aux = NULL;
	aux = malloc(sizeof(Reporte));
	return aux;
}


Reporte* reporte_newParametros(char* idStr, char* codigo, char* nombre, char* descripcion, char* fobStr, char* pArancelariaStr,
										char* mCubicosStr, char* cmCubicosStr, char* valorAereoStr, char* valorMaritimoStr)
{
	Reporte* aux = NULL;
	aux = reporte_new();
	char nArancelaria[48];
	if(aux != NULL && idStr != NULL && codigo != NULL && nombre != NULL && descripcion != NULL && fobStr != NULL && pArancelariaStr != NULL && mCubicosStr != NULL &&
			cmCubicosStr != NULL && valorAereoStr != NULL && valorMaritimoStr != NULL )
	{
		if(aux_verificarNumerica(idStr, 10) == 0 && aux_verificarFlotante(fobStr) == 0 && aux_verificarFlotante(mCubicosStr) == 0 && aux_verificarFlotante(cmCubicosStr) == 0 &&
				aux_verificarFlotante(valorAereoStr) == 0 && aux_verificarFlotante(valorMaritimoStr) == 0)
		{
			strcpy(nArancelaria,pArancelariaStr);
			if(reporte_setId(aux, atoi(idStr)) == 1 && reporte_setCodigo(aux, codigo) == 1 &&
				reporte_setNombre(aux, nombre) == 1 && reporte_setDescripcion(aux, descripcion) == 1 && reporte_setFob(aux, atof(fobStr)) == 1 &&
				reporte_setpArancelaria(aux, nArancelaria) == 1 && reporte_setmCubicos(aux, atof(mCubicosStr)) == 1 &&
				reporte_setcmCubicos(aux, atof(cmCubicosStr)) == 1 && reporte_setvalorAereo(aux, atof(valorAereoStr)) == 1 &&
				reporte_setvalorMaritimo(aux, atof(valorMaritimoStr)) == 1)
			{
				return aux;
			}
			else
			{
				reporte_delete(aux);
			}
		}
	}
	return NULL;
}

void reporte_delete(Reporte* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

int reporte_imprimir(Reporte* this)
{
	int retorno=0;
	int id;
	char nombre[48];
	char codigo[48];
	char descripcion[256];
	float fob;
	char nArancelaria[20];
	float costoAereo;
	float costoMaritimo;


	if(this != NULL)
	{
		retorno = 1;
		reporte_getId(this,&id);
		reporte_getCodigo(this,codigo);
		reporte_getNombre(this,nombre);
		reporte_getDescripcion(this,descripcion);
		reporte_getFob(this,&fob);
		reporte_getpArancelaria(this, nArancelaria);
		reporte_getvalorMaritimo(this,&costoMaritimo);
		reporte_getvalorAereo(this,&costoAereo);

		printf("%d%20s%20s%20s%20f%20s%20f%20f\n",id,nombre,codigo,descripcion,fob,nArancelaria,costoAereo,costoMaritimo);
	}
	return retorno;
}

int reporte_CompararId(void* compareOne,void* compareTwo)
{
	int retorno = 0;
	Reporte* auxOne;
	Reporte* auxTwo;
	auxOne = (Reporte*) compareOne;
	auxTwo = (Reporte*) compareTwo;
	if(auxOne->idArt>auxTwo->idArt)
	{
		retorno = 1;
	}
	else if(auxOne->idArt<auxTwo->idArt)
	{
		retorno = -1;
	}
	return retorno;
}

int reporte_CompararNombre(void* compareOne,void* compareTwo)
{
	int retorno = 0;
		Reporte* auxOne;
		Reporte* auxTwo;
		auxOne = (Reporte*)compareOne;
		auxTwo = (Reporte*)compareTwo;
		if(auxOne != NULL && auxTwo != NULL)
		{
			if(strncmp(auxOne->nombre,auxTwo->nombre,128)>0)
			{
				retorno = -1;
			}
			else if(strncmp(auxOne->nombre,auxTwo->nombre,128) < 0)
			{
				retorno = 1;
			}
		}
		return retorno;
}

int reporte_CompararCodigo(void* compareOne,void* compareTwo)
{
	int retorno = 0;
		Reporte* auxOne;
		Reporte* auxTwo;
		auxOne = (Reporte*)compareOne;
		auxTwo = (Reporte*)compareTwo;
		if(auxOne != NULL && auxTwo != NULL)
		{
			if(strncmp(auxOne->codigo,auxTwo->codigo,128)>0)
			{
				retorno = -1;
			}
			else if(strncmp(auxOne->codigo,auxTwo->codigo,128) < 0)
			{
				retorno = 1;
			}
		}
		return retorno;
}

int reporte_CompararNArancelaria(void* compareOne,void* compareTwo)
{
	int retorno = 0;
		Reporte* auxOne;
		Reporte* auxTwo;
		auxOne = (Reporte*)compareOne;
		auxTwo = (Reporte*)compareTwo;
		if(auxOne != NULL && auxTwo != NULL)
		{
			if(strncmp(auxOne->pArancelaria,auxTwo->pArancelaria,48)>0)
			{
				retorno = -1;
			}
			else if(strncmp(auxOne->pArancelaria,auxTwo->pArancelaria,48) < 0)
			{
				retorno = 1;
			}
		}
		return retorno;
}

int reporte_CompararFob(void* compareOne,void* compareTwo)
{
	int retorno = 0;
	Reporte* auxOne;
	Reporte* auxTwo;
	auxOne = (Reporte*) compareOne;
	auxTwo = (Reporte*) compareTwo;
	if(auxOne->fob>auxTwo->fob)
	{
		retorno = 1;
	}
	else if(auxOne->fob<auxTwo->fob)
	{
		retorno = -1;
	}
	return retorno;
}

int reporte_CompararValorAereo(void* compareOne,void* compareTwo)
{
	int retorno = 0;
	Reporte* auxOne;
	Reporte* auxTwo;
	auxOne = (Reporte*) compareOne;
	auxTwo = (Reporte*) compareTwo;
	if(auxOne->valorAereo>auxTwo->valorAereo)
	{
		retorno = 1;
	}
	else if(auxOne->valorAereo<auxTwo->valorAereo)
	{
		retorno = -1;
	}
	return retorno;
}

int reporte_CompararValorMaritimo(void* compareOne,void* compareTwo)
{
	int retorno = 0;
	Reporte* auxOne;
	Reporte* auxTwo;
	auxOne = (Reporte*) compareOne;
	auxTwo = (Reporte*) compareTwo;
	if(auxOne->valorMaritimo>auxTwo->valorMaritimo)
	{
		retorno = 1;
	}
	else if(auxOne->valorMaritimo<auxTwo->valorMaritimo)
	{
		retorno = -1;
	}
	return retorno;
}
