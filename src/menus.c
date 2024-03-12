#include "../include/menus.h"

void Querie_choose (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers) {
    char* read = malloc(STR_SIZE*sizeof(char));

    while(1){
        menuQueries();

        printLine("\nInsere a tua opção: ");
        scanf("%s", read);
        if(strlen(read)==0 || strlen(read)>2 || (strcmp(read, "0") && strcmp(read, "1") && strcmp(read, "2") && strcmp(read, "3") && strcmp(read, "4") && strcmp(read, "5") && strcmp(read, "6") && strcmp(read, "7") && strcmp(read, "8") && strcmp(read, "9") && strcmp(read, "10"))){
            printLine("\nInsere uma opção válida\n");
            continue;
        }
        int qryNum = atoi(read);
        if(qryNum == 0){
            break;
        }
        queries_iterative(users, flights, reservations, passengers, qryNum); 
    }
}

void menuInits(CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers) {
    char* read= malloc(STR_SIZE*sizeof(char));
    char r;
    while(1){
        menuInicial();
        scanf("%s", read);
        if(strlen(read)==1)
            r = read[0];
        else{
            printLine("\nInsere uma opção válida\n");
            continue;
        }
        int exit = 0;
        switch(r) {
            case 'n': 
            {
                Querie_choose(users, flights, reservations, passengers);
            }
            break;

            case 'e':{
                exit = 1;
            }
            break;
            
            default: {
                printLine("\nInsere uma opção válida\n");
            }
            break;
        }
        if(exit == 1)
            break;
    }
    free(read);
    return;
}
