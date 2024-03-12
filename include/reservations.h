#ifndef Grupo62_Reservations_Module 
#define Grupo62_Reservations_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>

#include "date.h"
#include "validacao.h"
#include "output.h"

/**
 * @brief Struct que define pelo que é constituído uma reservation e armazenando os seus dados
 * 
 */
typedef struct reservations *RESERVATIONS;

/**
 * @brief Função que cria e retorna uma struct do tipo RESERVATIONS
 * 
 * @return RESERVATIONS
 */
RESERVATIONS newReservation ();

/**
 * @brief Função que associa os respetivos dados à informação que contém a linha, fazendo automaticamente a validação da mesma
 * 
 * @param line
 * @param notvalid
 * @return RESERVATIONS
 */
RESERVATIONS initReservationFromLine(char *line, GHashTable *hashU);

////////// MÉTODOS GET //////////
/**
 * @brief Função que retorna o id da reservation
 * 
 * @param r
 * @return char* 
 */
char *getIdR (RESERVATIONS r);

/**
 * @brief Função que retorna o id do user
 * 
 * @param r
 * @return char* 
 */
char *getUser_idR (RESERVATIONS r);

/**
 * @brief Função que retorna o id do hotel
 * 
 * @param r
 * @return char* 
 */
char *getHotel_idR (RESERVATIONS r);

/**
 * @brief Função que retorna o hotel name
 * 
 * @param r
 * @return char* 
 */
char *getHotel_nameR (RESERVATIONS r);

/**
 * @brief Função que retorna as estrelas de um hotel
 * 
 * @param r
 * @return int
 */
int getHotel_starsR (RESERVATIONS r);

/**
 * @brief Função que retorna a city tax
 * 
 * @param r
 * @return int
 */
int getCity_taxR (RESERVATIONS r);

/**
 * @brief Função que retorna o address da reservation
 * 
 * @param r
 * @return char* 
 */
char *getAddressR (RESERVATIONS r);

/**
 * @brief Função que retorna a data de inicio da reservation
 * 
 * @param r
 * @return DateClock* 
 */
DateClock* getBegin_dateR (RESERVATIONS r);

/**
 * @brief Função que retorna a data de fim da reservation
 * 
 * @param r
 * @return DateClock* 
 */
DateClock* getEnd_dateR (RESERVATIONS r);

/**
 * @brief Função que retorna o price per night da reservation
 * 
 * @param r
 * @return int 
 */
int getPrice_per_nightR (RESERVATIONS r);

/**
 * @brief Função que retorna includes breakfast da reservation
 * 
 * @param r
 * @return char* 
 */
char *getIncludeS_breakfastR (RESERVATIONS r);

/**
 * @brief Função que retorna os room details da reservation
 * 
 * @param r
 * @return char* 
 */
char *getRoom_detailsR (RESERVATIONS r);

/**
 * @brief Função que retorna a rating da reservation
 * 
 * @param r
 * @return int 
 */
int getRatingR (RESERVATIONS r);

/**
 * @brief Função que retorna o comment da reservation
 * 
 * @param r
 * @return char* 
 */
char *getCommentR (RESERVATIONS r);


////////// MÉTODOS FREE //////////
/**
 * @brief Função que dá free à struct reservations
 * 
 * @param reservations
 */
void freeReservation(RESERVATIONS reservations);

/**
 * @brief Função invólucro (wrapper) da freeReservation
 * 
 * @param reservations
 */
void free_reservation_void (gpointer reservations);

/**
 * @brief Função responsável por comparar as datas de início
 * 
 * @param a
 * @param b
 * @param hashT
 *
 * @return int
 */
int compare_beginDate_Then_Id(gconstpointer a, gconstpointer b, gpointer hashT);

/**
 * @brief Função que passa os dados da query 4 de uma resrvation para uma srting única
 * 
 * @param r
 * @param flag
 * @param i
 * @param totalPrice
 * @return char*
 */
char* reservationToStringQuery4(RESERVATIONS r, int flag, int i, double totalPrice);

/**
 * @brief Função que passa os dados da query 1 de uma reservation para uma srting única
 * 
 * @param f
 * @param flag
 * @return char*
 */
char* reservationToStringQuery1(RESERVATIONS r, int flag);

/**
 * @brief Função que passa os dados da query 2 numa GList
 * 
 * @param path
 * @param listReservations
 * @param size
 * @param ID
 * @param flag
 * @return char*
 */
void printGListRQuery2 (char *path, GList *listReservations, int size, char *ID, int flag);

#endif