#ifndef Grupo62_Parser_Module 
#define Grupo62_Parser_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "catalog_u.h"
#include "catalog_f.h"
#include "catalog_p.h"
#include "catalog_r.h"

/**
 * @brief Função responsável por fazer parse dos csv
 * 
 * @param path_to_csv 
 * @param hashF 
 */
void parser_Flights(char *path_to_csv, CatalogoFlight *hashF);

/**
 * @brief Função responsável por fazer parse dos csv
 * 
 * @param path_to_csv 
 * @param hashP 
 */
 void parser_Passengers(char *path_to_csv, CatalogoPassenger *hashP,CatalogoFlight *cat_flight, CatalogoUser *cat_user);

/**
 * @brief Função responsável por fazer parse dos csv
 * 
 * @param path_to_csv 
 * @param hashP
 */
void parser_Reservations(char *path_to_csv, CatalogoReservation *hashR, CatalogoUser *cat_user);

/**
 * @brief Função responsável por fazer parse dos csv
 * 
 * @param path_to_csv 
 * @param hashU
 */
void parser_Users(char *path_to_csv, CatalogoUser *hashU);

#endif