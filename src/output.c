#include "../include/output.h"

void printStringToFile(char *string, char *outputPath){
    FILE *fp = fopen(outputPath, "w");
    if (!fp) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir ficheiro de output para escrever: %s\n", outputPath);
        printLine(aux);
        free(aux);
        return;
    }
    fprintf(fp, "%s", string);
    fclose(fp);
}

void apendStringToFile(char *string, char *outputPath){
    FILE *fp = fopen(outputPath, "a");
    if (!fp) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir ficheiro de output para append: %s\n", outputPath);
        printLine(aux);
        free(aux);
        return;
    }
    fprintf(fp, "%s", string);
    fclose(fp);
}

void printArrayToFile(char **array, char *outputPath){
    FILE *fp = fopen(outputPath, "w");
    if(!fp){
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir o arquivo: %s para escrita.\n", outputPath);
        printLine(aux);
        free(aux);
        return;
    }
    if(array!=NULL){
        for (int i = 0; array[i]!=NULL; ++i) {
            fprintf(fp, "%s", array[i]);
        }
    }
    fclose(fp);
}

void printLine(char* line){
    printf("%s", line);
}