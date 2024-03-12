#ifndef Grupo62_Output_Module 
#define Grupo62_Output_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 1024
/**
 * @brief Função que dá print da string para um file
 * 
 * @param string
 * @param outputPatch
 */
void printStringToFile(char *string, char *outputPath);

/**
 * @brief Função que dá append da string para um file
 * 
 * @param string
 * @param outputPatch
 */
void apendStringToFile(char *string, char *outputPath);

/**
 * @brief Função que dá print do array para um file
 * 
 * @param array
 * @param outputPatch
 */
void printArrayToFile(char **array, char *outputPath);

/**
 * @brief Função que dá print de uma linha no terminal
 *
 * @param line
 */
void printLine(char* line);

#endif