#ifndef Grupo62_Passengers_Module 
#define Grupo62_Passengers_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "validacao.h"
#include "flights.h"

/**
 * @brief Struct que define pelo que é constituído um passenger e armazenando os seus dados
 * 
 */
typedef struct passengers *PASSENGERS;

/**
 * @brief Função que cria e retorna uma struct do tipo PASSENGERS
 * 
 * @return PASSENGERS
 */
PASSENGERS newPassengers ();

/**
 * @brief Função que cria e retorna uma struct do tipo PASSENGERS
 * 
 * @return Passengers
 */
PASSENGERS initPassengerFromLine(char *line, GHashTable* hashF, GHashTable* hashU);


////////// MÉTODOS GET ////////// 
/**
 * @brief Função que retorna o id do flight
 * 
 * @param p
 * @return char* 
 */
char *getFlight_idP (PASSENGERS p);

/**
 * @brief Função que retorna o id do user
 * 
 * @param p
 * @return char* 
 */
char *getUser_idP (PASSENGERS p);



////////// MÉTODOS FREE //////////
/**
 * @brief Função que dá free à struct passengers
 * 
 * @param passengers
 */
void freePassengers(PASSENGERS passengers);

/**
 * @brief Função invólucro (wrapper) da freePassengers
 * 
 * @param passengers
 */
void free_passenger_void (gpointer passengers);

#endif