#ifndef Grupo62_Validacao_Module 
#define Grupo62_Validacao_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Função que valida se o parametro não é nulo
 * 
 * @param str
 * @return int 
 */
int valida_notzero(char *str);

/**
 * @brief Função que valida se a letra corresponde
 * 
 * @param c
 * @return int 
 */
int isLetter(char c);

/**
 * @brief Função responsável por verificar se a string corresponde a um inteiro
 * 
 * @param str
 *
 * @return int
 */
int isInt(char *str);

/**
 * @brief Função que valida se palavra é valida em minúsculo
 * 
 * @param str
 * @return char*
 */
char* toLowerCase(char *str);

/**
 * @brief Função que valida se palavra é valida em maiúsculo
 * 
 * @param c
 * @return char*
 */
char toUpper(char c);

#endif