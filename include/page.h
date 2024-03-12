#ifndef Grupo62_Page_Module
#define Grupo62_Page_Module

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "view.h"
#include "menus.h"
#include "output.h"

/**
 * @brief Função que dá print da página
 * 
 * @param arr
 * @param size
 * @param page
 * @param max
 */
void printPagina(char** arr, int size, int page, int max, int lastPage);

/**
 * @brief Função que dá print do array para um file
 * 
 * @param array
 * @param outputPatch
 */
void printArray (char** arr, int size, int max);

/**
 * @brief Função que dá print do array para um file
 * 
 * @param array
 * @param outputPatch
 */
void page (char** arr);

#endif