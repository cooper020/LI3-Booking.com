#include <stdio.h>
#include <stdlib.h>
#include "../include/executor.h"
#include "../include/output.h"

#include <locale.h>

int main(int argc, char *argv[]){
    setlocale(LC_COLLATE, "en_US.UTF-8");
    
    executor(argc, argv);
    printLine("Fim do programa\n");
    return 0;
} 