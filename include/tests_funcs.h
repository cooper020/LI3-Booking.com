#ifndef Grupo62_Tests_funcs_Module 
#define Grupo62_Tests_funcs_Module

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"

/**
 * @brief Função auxiliar da compare_tests
 * 
 * @param file1
 * @param file2  
 * @param number 
 */
void compare_testes_aux(char *file1, char *file2, int number);

/**
 * @brief Função auxiliar que compara os outputs gerados com os esperados
 * 
 * @param directory
 */
void compare_testes(char* directory);

/**
 * @brief Função que calcula a média dos tempos de execução das queries
 * 
 * @param array
 * @param tamanho 
 * @return double  
 */
double media(double *array, int tamanho);

/**
 * @brief Função para verificar o tempo de execução das queries
 * 
 * @param array
 * @param tamanho
 * @param f   
 */
void verificaArray(double *array, int tamanho, int f);

#endif