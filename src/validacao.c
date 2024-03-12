#include "../include/validacao.h"


int valida_notzero( char *str) {
    // Adapte a lógica de validação conforme necessário
    return (str == NULL || strcmp(str, "") == 0);
}

int isLetter(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int isInt(char *str){
    if(str == NULL)
        return 0;
    int size = strlen(str);
    for(int i=0; i<size; i++){
        if(!isdigit(str[i]))
            return 0;
    }
    return 1;
}

char toLower(char c){
    if(c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

char toUpper(char c){
    if(c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

char* toLowerCase(char *str){
    int size = strlen(str);
    for(int i=0; i<size; i++){
        str[i] = toLower(str[i]);
    }
    return str;
}
