#ifndef Grupo62_Queries_Module 
#define Grupo62_Queries_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>

#include "users.h"
#include "flights.h"
#include "reservations.h"
#include "passengers.h"
#include "catalog_u.h"
#include "catalog_f.h"
#include "catalog_r.h"
#include "catalog_p.h"
#include "date.h"
#include "page.h"

/**
 * @brief Função responsável por chamar as diversas queries
 * 
 * @param users
 * @param flights
 * @param reservations
 * @param passengers
 * @param num_qry
 * @param outputPath
 * @param args
 * @param flag
 */
void queries (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int num_qry, char *outputPath, char* args, int flag);

/**
 * @brief Função responsável por chamar as diversas queries no modo interativo
 * 
 * @param users
 * @param flights
 * @param reservations
 * @param passengers
 * @param num_qry
 */
void queries_iterative (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int num_qrys);

/**
 * @brief Função responsável por chamar as diversas queries
 * 
 * @param users
 * @param flights
 * @param reservations
 * @param passengers
 * @param num_qry
 * @param outputPath
 * @param args
 * @param flag
 */
double q_tests (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int num_qry, char *outputPath, char* args, int flag);

#endif