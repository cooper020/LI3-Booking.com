#ifndef Grupo62_Catalog_u_Module 
#define Grupo62_Catalog_u_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "users.h"
#include "output.h"

/**
 * @brief Struct de um catálogo de Users
 * 
 */
typedef struct hash1 CatalogoUser;

/**
 * @brief Função que retorna o catálogo
 * 
 * @param cat
 * @return GHashTable*
 */
GHashTable *getHashTableU(CatalogoUser* cat);

/**
 * @brief Função que insere a informação no catálogo dos users
 * 
 * @param line
 * @param hashU  
 */
void insert_CatalogoUser ( char *line, CatalogoUser *hashU);


/**
 * @brief Função que cria o catálogo dos users
 * 
 * @param pathU
 * @return CatalogoUser*
 */
CatalogoUser *create_CatalogoUser(char *pathU);

/**
 * @brief Função que dá free ao catálogo dos users
 * 
 * @param hashU
 */
void free_CatalogoUser(CatalogoUser *hashU);

#endif