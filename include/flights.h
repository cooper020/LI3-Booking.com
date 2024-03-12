#ifndef Grupo62_Flights_Module 
#define Grupo62_Flights_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "date.h"
#include "validacao.h"
#include "users.h"

/**
 * @brief Struct que define pelo que é constituído um flight e armazenando os seus dados
 * 
 */
typedef struct flights *FLIGHTS;

/**
 * @brief Função que cria e retorna uma struct do tipo FLIGHTS
 * 
 * @return FLIGHTS
 */
FLIGHTS newFlight ();

/**
 * @brief Função que associa os respetivos dados à informação que contém a linha, fazendo automaticamente a validação da mesma
 * 
 * @param line
 * @param notvalid
 * @return FLIGHTS
 */
FLIGHTS initFlightFromLine(char *line);

////////// MÉTODOS GET //////////

/**
 * @brief Função que retorna o id do flight
 * 
 * @param f
 * @return char* 
 */
char *getIdF (FLIGHTS f);

/**
 * @brief Função que retorna a airline do flight
 * 
 * @param f
 * @return char* 
 */
char *getAirlineF (FLIGHTS f);

/**
 * @brief Função que retorna o plane model do flight
 * 
 * @param f
 * @return char* 
 */
char *getPlane_modelF (FLIGHTS f);

/**
 * @brief Função que retorna os total seats do flight
 * 
 * @param f
 * @return int 
 */
int getTotal_seatsF (FLIGHTS f);

/**
 * @brief Função que retorna a origin do flight
 * 
 * @param f
 * @return char* 
 */
char *getOriginF (FLIGHTS f);

/**
 * @brief Função que retorna a destinations do flight
 * 
 * @param f
 * @return char* 
 */
char *getDestinationF (FLIGHTS f);

/**
 * @brief Função que retorna a hora estimada de partida do flight
 * 
 * @param f
 * @return DateClock* 
 */
DateClock* getS_departure_dateF (FLIGHTS f);

/**
 * @brief Função que retorna a hora estimada de chegada do flight
 * 
 * @param f
 * @return DateClock* 
 */
DateClock* getS_arrival_dateF (FLIGHTS f);

/**
 * @brief Função que retorna a hora real de partida do flight
 * 
 * @param f
 * @return DateClock* 
 */
DateClock* getR_departure_dateF (FLIGHTS f);

/**
 * @brief Função que retorna a hora real de chegada do flight
 * 
 * @param f
 * @return DateClock* 
 */
DateClock* getR_arrival_dateF (FLIGHTS f);

/**
 * @brief Função que retorna o pilot do flight
 * 
 * @param f
 * @return char* 
 */
char *getPilotF (FLIGHTS f);

/**
 * @brief Função que retorna o copilot do flight
 * 
 * @param f
 * @return char* 
 */
char *getCopilotF (FLIGHTS f);

/**
 * @brief Função que retorna as notes do flight
 * 
 * @param f
 * @return char* 
 */
char *getNotesF (FLIGHTS f);

/**
 * @brief Função que devolve o número de lugares ocupados
 * 
 * @param f
 * @return int
 */
int getOcupied_seatsF (FLIGHTS f);

/**
 * @brief Função que devolve o consumo de lugares
 * 
 * @param f
 * @return int
 */
int consumeSeat (FLIGHTS f);

////////// MÉTODO FREE //////////
/**
 * @brief Função que dá free à struct flight
 * 
 * @param flights
 */
void freeFlight(FLIGHTS flights);

/**
 * @brief Função invólucro (wrapper) da freeFlight
 * 
 * @param flights
 */
void free_flight_void (gpointer flights);

////////// FUNÇÕES AUXILIARES //////////

/**
 * @brief Função que compara as duas datas de partida
 * 
 * @param a
 * @param b
 * @param hashT
 * @return int
 */
int compare_departureDate_Then_Id(gconstpointer a, gconstpointer b, gpointer hashT);

/**
 * @brief Função que devolve o atreaso da partida do voo
 * 
 * @param f
 * @return int
 */
int calculaAtrasoPartida(FLIGHTS f);

/**
 * @brief Função que passa os dados da query 5 de um flight para uma srting única
 * 
 * @param f
 * @param flag
 * @param i
 * @return char*
 */
char* flightToStringQuery5(FLIGHTS f, int flag, int i);

/**
 * @brief Função que ordena os voos por data de partida
 * 
 * @param flights
 * @param size
 */
void sortFlightsByDepartureDate(FLIGHTS* flights, int size);

/**
 * @brief Função que passa os dados da query 1 de um flight para uma srting única
 * 
 * @param f
 * @param flag
 * @return char*
 */
char* flightToStringQuery1(FLIGHTS f, int flag);

#endif