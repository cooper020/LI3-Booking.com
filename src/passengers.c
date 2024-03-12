#include "../include/passengers.h"

struct passengers{
    char *flight_id;//não pode ser vazio
    char *user_id;//não pode ser vazio
};

PASSENGERS newPassenger(){
    PASSENGERS p = malloc(sizeof(struct passengers));
    p -> flight_id = NULL;
    p -> user_id = NULL;

    return p;
}

char ** takeLineP(char * line) {
    char** tokens = malloc(sizeof(char *) * 2);
    int i = 0;
    char * token = NULL;
    while ((token = strsep(&line, ";")) && i < 2) {
        tokens[i++] = token;
    }
    return tokens;
}

PASSENGERS initPassengerFromLine(char *line, GHashTable* hashF, GHashTable* hashU){
    if (line == NULL)
        return NULL;

    int valid = 1;
    char *line_dup = strdup(line);

    char ** tokens = takeLineP(line);
    
    PASSENGERS passengers = newPassenger();

    // Atribui os campos da estrutura passsengers com os tokens
    passengers->flight_id = strdup(tokens[0]);
    if (valida_notzero(passengers->flight_id) != 0) {
        valid = 0;
    }
 
    passengers->user_id = strdup(tokens[1]);
    if (valida_notzero(passengers->user_id) != 0) {
        valid = 0;
    }

    if (!g_hash_table_contains(hashU, passengers->user_id) || !g_hash_table_contains(hashF, passengers->flight_id)){
        valid = 0;
    }

    if(valid==1){
        // Verifica se o flight tem lugares disponiveis
        FLIGHTS f = g_hash_table_lookup(hashF, passengers->flight_id);
        if (consumeSeat(f) == 0){
            valid = 0;
        }
    }
    
    if(!valid){
        char* aux = malloc(STR_SIZE * sizeof(char));
        strcpy(aux, line_dup);
        strcat(aux, "\n");
        apendStringToFile(aux, "Resultados/passengers_errors.csv");
        free(aux);
        freePassengers(passengers);
        passengers = NULL;
    }

    free(line_dup);
    free(tokens);
    return passengers;
}

////////// MÉTODOS GET //////////


char *getFlight_idP (PASSENGERS p) {
    return strdup(p->flight_id); //MEM. LEAK
}

char *getUser_idP (PASSENGERS p) {
    return strdup(p->user_id);
}

////////// MÉTODOS FREE //////////

void freePassengers(PASSENGERS passengers) {
    if (passengers) { //verifica se o pointer não é nulo
        if (passengers->flight_id) free(passengers->flight_id);
        if (passengers->user_id) free(passengers->user_id);
   
        free(passengers); // Liberta a strut inteira
    }
}

void free_passenger_void (gpointer passengers){
    freePassengers(passengers);
}