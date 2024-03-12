#ifndef Grupo62_Executor_Module 
#define Grupo62_Executor_Module

#include "catalog_u.h"
#include "catalog_f.h"
#include "catalog_r.h"
#include "catalog_p.h"
#include "queries.h"
#include "tests_funcs.h"
#include "menus.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>

/**
 * @brief Função que faz a conexão entre os módulos para poder executar as tarefas
 * 
 * @param argc 
 * @param argv 
 */
void executor(int argc, char *argv[]);

/**
 * @brief Função responsável por devolver a cainho para o dataset dos users
 * 
 * @param argv
 * @return char   
 */
char* init_user(char *argv[]);

/**
 * @brief Função responsável por devolver a cainho para o dataset dos flights
 * 
 * @param argv 
 * @return char   
 */
char* init_flight(char *argv[]);

/**
 * @brief Função responsável por devolver a cainho para o dataset das reservations
 * 
 * @param argv
 * @return char    
 */
char* init_reservation(char *argv[]);

/**
 * @brief Função responsável por devolver a cainho para o dataset dos passengers
 * 
 * @param argv 
 * @return char   
 */
char* init_passengers(char *argv[]);

/**
 * @brief Função responsável por devolver a cainho para o input utilizado na aplicação
 * 
 * @param argv 
 * @return char   
 */
char* path_input(char *argv[]);

/**
 * @brief Função que lê os comandos de input e dá início à realização das queries
 * 
 * @param input
 * @param users
 * @param flights
 * @param reservations
 * @param passengers
 */
void batch(char *input, CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int numargs);

/**
 * @brief Função que lê os comandos de input e dá inicio ao modo interativo
 * 
 * @param input
 * @param users
 * @param flights
 * @param reservations
 * @param passengers
 */
void interative(CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers);

#endif