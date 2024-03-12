#include "../include/parser.h"


void parser_Users(char *path_to_csv, CatalogoUser *hashU) {
    FILE *file = fopen(path_to_csv, "r");
    if (!file) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir o arquivo de users: %s\n", path_to_csv);
        printLine(aux);
        free(aux);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    if (read != -1) {
        apendStringToFile(line, "Resultados/users_errors.csv");
    }
    while ((read = getline(&line, &len, file)) != -1) {
        char* line_dup = strdup(line); //MEM. LEAK
        char* command = strsep(&line_dup, "\n");

        insert_CatalogoUser(command ,hashU);

        free(command);
    }

    free(line);
    fclose(file);
}

void parser_Reservations(char *path_to_csv, CatalogoReservation *hashR, CatalogoUser *cat_user) {
    FILE *file = fopen(path_to_csv, "r");
    if (!file) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir o arquivo de reservations: %s\n", path_to_csv);
        printLine(aux);
        free(aux);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    if (read != -1) {
        apendStringToFile(line, "Resultados/reservations_errors.csv");
    }
    while ((read = getline(&line, &len, file)) != -1) {
        char* line_dup = strdup(line); //MEM. LEAK
        char* command = strsep(&line_dup, "\n");

        insert_CatalogoReservation(command ,hashR, cat_user);

        free(command);
    }

    free(line);
    fclose(file);
}

void parser_Passengers(char *path_to_csv, CatalogoPassenger *hashP,CatalogoFlight *cat_flight, CatalogoUser *cat_user) {
    FILE *file = fopen(path_to_csv, "r");
    if (!file) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir o arquivo de passengers: %s\n", path_to_csv);
        printLine(aux);
        free(aux);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, file);
    if (read != -1) {
        apendStringToFile(line, "Resultados/passengers_errors.csv");
    }
    while ((read = getline(&line, &len, file)) != -1) {
        char* line_dup = strdup(line); //MEM. LEAK
        char* command = strsep(&line_dup, "\n");

        insert_CatalogoPassenger(command ,hashP, cat_flight, cat_user);
        
        free(command);
        
    }

    free(line);
    fclose(file);
}

void parser_Flights(char *path_to_csv, CatalogoFlight *hashF) {
    FILE *file = fopen(path_to_csv, "r");
    if (!file) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        sprintf(aux, "Erro ao abrir o arquivo de flights: %s\n", path_to_csv);
        printLine(aux);
        free(aux);
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    
    read = getline(&line, &len, file);
    if (read != -1) {
        apendStringToFile(line, "Resultados/flights_errors.csv");
    }
    while ((read = getline(&line, &len, file)) != -1) {

        size_t last_char = strlen(line) - 1;
        if (line[last_char] == '\n') {
            line[last_char] = '\0';
        }

       if (line[0] != '\0') {  // Verifica se a linha não está vazia
            char *line_dup = strdup(line);
            char *line_dup_start = line_dup;
            insert_CatalogoFlight(line, hashF);
            free(line_dup_start);
        }
    }
    free(line);
    fclose(file);
}