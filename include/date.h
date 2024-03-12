#ifndef Grupo62_Date_Module 
#define Grupo62_Date_Module

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

/**
 * @brief Struct que define pelo que é constituído uma datahora e armazenando os seus dados
 * 
 */
typedef struct datahora DateClock;

/**
 * @brief Função que retorna o dia
 * 
 * @param dh
 * @return int
 */
int getDateClockDia (DateClock *dh);

/**
 * @brief Função que retorna o mes
 * 
 * @param dh
 * @return int
 */
int getDateClockMes (DateClock *dh);

/**
 * @brief Função que retorna o ano
 * 
 * @param dh
 * @return int
 */
int getDateClockAno (DateClock *dh);

/**
 * @brief Função que retorna a hora
 * 
 * @param dh
 * @return int
 */
int getDateClockHora (DateClock *dh);

/**
 * @brief Função que retorna o minuto
 * 
 * @param dh
 * @return int
 */
int getDateClockMinuto (DateClock *dh);

/**
 * @brief Função que retorna o segundo
 * 
 * @param dh
 * @return int
 */
int getDateClockSegundo (DateClock *dh);

/**
 * @brief Função que retorna põe o tempo a O
 * 
 * @param dh
 */
void setTimeToZero(DateClock *dh);

/**
 * @brief Função que dá clone da struct
 * 
 * @param dh
 * @return DateClock*
 */
DateClock *cloneDateClock (DateClock *dh);

/**
 * @brief Função que preenche a struct da datahora
 * 
 * @param command
 * @return DateClock*
 */
DateClock* preenche_data_hora(char *command);

/**
 * @brief Função que converte uma data numa string
 * 
 * @param dh
 * @return char*
 */
char *DateClockToString(DateClock *dh);

/**
 * @brief Função que dá free da date
 * 
 * @param dh
 */
void free_date (DateClock *dh);

/**
 * @brief Função que dá free da dateTime
 * 
 * @param data
 */
void freeDateTime_void(gpointer data);


/**
 * @brief Função que compara duas datas
 * 
 * @param d1
 * @param d2
 * @return int
 */
int compareDateClock(DateClock *d1, DateClock *d2);

/**
 * @brief Função que calcula a diferença entre duas datas
 * 
 * @param d1
 * @param d2
 * @return int
 */
int calculadif (DateClock *d1, DateClock *d2);

/**
 * @brief Função que retorna os segundos
 * 
 * @param seg
 * @return DateClock*
 */
DateClock* segToData (int seg);

/**
 * @brief Função que retorna o número de noites
 * 
 * @param d1
 * @param d2 
 * @return int
 */
int getNrNights(DateClock *d1, DateClock *d2);

/**
 * @brief Função que conta o número de noites
 * 
 * @param beginDateRes
 * @param endDateRes
 * @param begin
 * @param end
 * @return int
 */
int contaNoites(DateClock *beginDateRes,DateClock *endDateRes, DateClock *begin, DateClock *end);

/**
 * @brief Função que calcula idade
 * 
 * @param birth_date 
 * @return int
 */
int calculaIdade(DateClock *birth_date);

#endif