#ifndef Grupo62_Catalog_p_Module 
#define Grupo62_Catalog_p_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "passengers.h"
#include "catalog_f.h"
#include "catalog_u.h"


/**
 * @brief Struct de um catálogo de passengers
 * 
 */
typedef struct hash3 CatalogoPassenger;

/**
 * @brief Função que retorna o catálogo
 * 
 * @param cat
 * @return GHashTable*
 */
GHashTable *getHashTableP(CatalogoPassenger* cat);

/**
 * @brief Função que insere a informação no catálogo dos passengers
 * 
 * @param line
 * @param hashP
 */
void insert_CatalogoPassenger(char *line, CatalogoPassenger *hashP, CatalogoFlight *cat_flight, CatalogoUser *cat_user);


/**
 * @brief Função que cria o catálogo dos passengers
 * 
 * @param pathP
 * @return CatalogoReservation*
 */
CatalogoPassenger *create_CatalogoPassenger(char *pathP, CatalogoFlight *cat_flight, CatalogoUser *cat_user);

/**
 * @brief Função que dá free ao catálogo dos passengers
 * 
 * @param hashP
 */
void free_CatalogoPassenger(CatalogoPassenger *hashP);

#endif