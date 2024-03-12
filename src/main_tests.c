#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "../include/executor.h"
#include "../include/tests_funcs.h"


int main(int argc, char *argv[]){
    if(argc != 4){
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Usage: %s <datset_folder> <input_file> <output_folder>\n", argv[0]);
        printLine(aux);
        free(aux);
        return 1;
    }

    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    
    executor(argc, argv);
    
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    char *aux = malloc(STR_SIZE*sizeof(char));
    sprintf(aux, "\nTempo total do programa: %.4f segundos\n", elapsed);
    printLine(aux);
    free(aux);

    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    char *aux2 = malloc(STR_SIZE*sizeof(char));
    sprintf(aux2, "Memória utilizada: %ld kB \n\n",  r_usage.ru_maxrss);
    printLine(aux2);
    free(aux2);
    

    compare_testes(argv[3]);

    printLine("\nFim do programa\n");
    return 0;
} 