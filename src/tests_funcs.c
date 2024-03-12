#include "../include/tests_funcs.h"

void compare_testes_aux(char *file1, char *file2, int number) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printLine("Erro ao abrir os arquivos.\n");
        return;
    }

    char line1[1024], line2[1024];
    int line_num = 1;

    while (fgets(line1, sizeof(line1), f1) != NULL && fgets(line2, sizeof(line2), f2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            char *aux = malloc(STR_SIZE*sizeof(char));
            sprintf(aux, "A primeira diferença foi encontrada na linha %d do file command%d_output.txt\n", line_num, number);
            printLine(aux);
            free(aux);

            break;
        }
        line_num++;
    }

    fclose(f1);
    fclose(f2);


}

void compare_testes(char* directory) {
    for (int i = 1; i < 101; i++) {
        char file1[1024], file2[1024];
        sprintf(file1, "%s/command%d_output.txt", directory, i);
        sprintf(file2, "Resultados/command%d_output.txt", i);

        compare_testes_aux(file1, file2, i);

    }
}

double media(double *array, int tamanho) {
    double soma = 0.0;
    for(int i = 0; i < tamanho; i++) {
        soma += array[i];
    }
    return soma / tamanho;
}

void verificaArray(double *array, int tamanho, int f) {
    if(tamanho == 0) {
        printLine("A query não teve execuções\n");
        return;
    } else {
        double media_val = media(array, tamanho);
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "A query %d executou em %.4f segundos (em média)\n", f, media_val);
        printLine(aux);
        free(aux);
        
    }
}

