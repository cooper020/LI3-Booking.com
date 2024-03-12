#ifndef Grupo62_Catalog_f_Module 
#define Grupo62_Catalog_f_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "flights.h"


/**
 * @brief Struct de um catálogo de Users
 * 
 */
typedef struct hash2 CatalogoFlight;

/**
 * @brief Função que retorna o catálogo
 * 
 * @param cat
 * @return GHashTable*
 */
GHashTable *getHashTableF(CatalogoFlight* cat);

/**
 * @brief Função que insere a informação no catálogo dos flights
 * 
 * @param line
 * @param hashF   
 */
void insert_CatalogoFlight ( char *line, CatalogoFlight *hashF);


/**
 * @brief Função que cria o catálogo dos Flights
 * 
 * @param pathF
 * @return CatalogoFlight*
 */
CatalogoFlight *create_CatalogoFlight(char *pathF);

/**
 * @brief Função que procura um Flight no catálogo através da sua key
 * 
 * @param hashF
 * @param key
 * @return CatalogoFlight*
 */
FLIGHTS FindByKey_CatalogoFlight(CatalogoFlight *hashF, char *key);

/**
 * @brief Função que dá free ao catálogo dos flights
 * 
 * @param hashF
 */
void free_CatalogoFlight(CatalogoFlight *hashF);

#endif