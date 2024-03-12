#include "../include/page.h"

void printPagina(char** arr, int size, int page, int max, int lastPage) {
    int i, j;
    printLine("---------------------------------------------------------------------------------------------\n");
    char* aux = malloc(STR_SIZE*sizeof(char));
    sprintf(aux, "                                       Page %d/%d\n", page + 1, lastPage + 1);
    printLine(aux);
    free(aux);
    printLine("---------------------------------------------------------------------------------------------\n");
    for (i = max * page; i < max * (page + 1) && i < size; i += max) {
        for (j = i; (j < i + max) && (j < size); j++) {
            if (arr[j] == NULL) {
                return;  // Retorna se o elemento do array for null
            }
            char* aux = malloc(STR_SIZE*sizeof(char));
            sprintf(aux, "%s\n", arr[j]);
            printLine(aux);
            free(aux);
        }
    }
    page_aux(); 
     
}


void printArray(char** arr, int size, int max) {
    if(arr == NULL || size == 0) {
        return;
    }

    int page = 0;
    // calcula o numero de paginas
    int resto = size % max;
    int lastPage = size/max + (resto == 0 ? -1 : 0);// se o resto for 0, entao nao tem ultima pagina, -1 por começar em 0
    char* read = malloc(STR_SIZE*sizeof(char));
    system("clear");
    printPagina(arr, size, page, max, lastPage);
    while (1) {
        scanf("%s", read);
        if(((strcmp(read, "N") == 0 || strcmp(read, "n") == 0)) && page<lastPage)
            page+=1;
        else if(((strcmp(read, "P") == 0 || strcmp(read, "p") == 0)) && page>0)
            page-=1;
        else if((strcmp(read, "F") == 0 || strcmp(read, "f") == 0))
            page = 0;
        else if((strcmp(read, "L") == 0 || strcmp(read, "l") == 0))
            page = lastPage;
        else if((strcmp(read, "Q") == 0 || strcmp(read, "q") == 0))
            break;
        system("clear");
        printPagina(arr, size, page, max, lastPage);
    }
    free(read);
    system("clear");
}

void page(char** arr) {
    if(arr == NULL) {
        return;
    }

    int max = 4;

    int size;
    for(size = 0; arr[size] != NULL; size++);
    
    printArray(arr, size, max);
}