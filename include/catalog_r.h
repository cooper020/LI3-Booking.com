#ifndef Grupo62_Catalog_r_Module 
#define Grupo62_Catalog_r_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "reservations.h"
#include "catalog_u.h"

/**
 * @brief Struct de um catálogo de Reservations
 * 
 */
typedef struct hash4 CatalogoReservation;

/**
 * @brief Função que retorna o catálogo
 * 
 * @param cat
 * @return GHashTable*
 */
GHashTable *getHashTableR(CatalogoReservation *cat);

/**
 * @brief Função que insere a informação no catálogo das reservations
 * 
 * @param line
 * @param hashR
 */
void insert_CatalogoReservation( char *line, CatalogoReservation *hashR, CatalogoUser *cat_user);


/**
 * @brief Função que cria o catálogo das reservations
 * 
 * @param pathR
 * @return CatalogoReservation*
 */
CatalogoReservation *create_CatalogoReservation(char *pathR, CatalogoUser *cat_user);

/**
 * @brief Função que procura uma reservation no catálogo através da sua key
 * 
 * @param hashR
 * @param key
 * @return CatalogoReservation*
 */
RESERVATIONS FindByKey_CatalogoReservation(CatalogoReservation *hashR, char *key);

/**
 * @brief Função que dá free ao catálogo das reservations
 * 
 * @param hashR
 */
void free_CatalogoReservation (CatalogoReservation *hashR);

#endif