#ifndef Grupo62_Users_Module 
#define Grupo62_Users_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "date.h"
#include "validacao.h"
#include "passengers.h"
#include "reservations.h"
#include "output.h"

/**
 * @brief Struct que define pelo que é constituído um user e armazenando os seus dados
 * 
 */
typedef struct users *USERS;

/**
 * @brief Função que cria e retorna uma struct do tipo USERS
 * 
 * @return USERS
 */
USERS newUser ();

/**
 * @brief Função que associa os respetivos dados à informação que contém a linha, fazendo automaticamente a validação da mesma
 * 
 * @param line
 * @param notvalid
 * @return USERS
 */
USERS initUserFromLine( char *line);

////////// MÉTODOS GET //////////

/**
 * @brief Função que retorna o id do user
 * 
 * @param u
 * @return char* 
 */
char *getIdU (USERS u);

/**
 * @brief Função que retorna o name do user
 * 
 * @param u
 * @return char* 
 */
char *getNameU (USERS u);

/**
 * @brief Função que retorna o email do user
 * 
 * @param u
 * @return char* 
 */
char *getEmailU (USERS u);

/**
 * @brief Função que retorna o phone number do user
 * 
 * @param u
 * @return char* 
 */
char *getPhone_numberU (USERS u);

/**
 * @brief Função que retorna o birthdate do user
 * 
 * @param u
 * @return DateClock* 
 */
DateClock *getBirth_dateU (USERS u);

/**
 * @brief Função que retorna o sex do user
 * 
 * @param u
 * @return char* 
 */
char *getSexU (USERS u);

/**
 * @brief Função que retorna o passport do user
 * 
 * @param u
 * @return char* 
 */
char *getPassportU (USERS u);

/**
 * @brief Função que retorna o country code do user
 * 
 * @param u
 * @return char* 
 */
char *getCountry_codeU (USERS u);

/**
 * @brief Função que retorna o id do user
 * 
 * @param u
 * @return char* 
 */
char *getAddressU (USERS u);

/**
 * @brief Função que retorna a hora de account creation do user
 * 
 * @param u
 * @return DateClock* 
 */
DateClock *getAccoutnt_creationU (USERS u);

/**
 * @brief Função que retorna o pay method do user
 * 
 * @param u
 * @return char* 
 */
char *getPay_methodU (USERS u);

/**
 * @brief Função que retorna o account status do user
 * 
 * @param u
 * @return char* 
 */
char *getAccount_statusU (USERS u);


////////// MÉTODOS FREE //////////
/**
 * @brief Função que dá free à struct user
 * 
 * @param users
 */
void freeUser(USERS users);

/**
 * @brief Função invólucro (wrapper) da freeUser
 * 
 * @param users
 */
void free_user_void (gpointer users);

/**
 * @brief Função de validação do emial
 * 
 * @param email
 * @return int 
 */
int valida_email( char *email);

/**
 * @brief Função que passa os dados da query 1 de um user para uma srting única
 * 
 * @param u
 * @param flag
 * @param nrFlights
 * @param nrReservations
 * @param totalSpent
 * @return char*
 */
char* userToStringQuery1(USERS u, int flag, int nrFlights, int nrReservations, double totalSpent);

/**
 * @brief Função que retorna o número de flights
 * 
 * @param u
 * @param listFlights
 * @return int 
 */
int getNrFlights(USERS u, GHashTable *hashP);

/**
 * @brief Função que obtem as reservas e o total gasto
 * 
 * @param u
 * @param listReservations
 * @param nR
 * @param tS
 */
void getNrReservationsAndTotalSpent(USERS u, GHashTable *hashR, int *nR, double *tS);

#endif