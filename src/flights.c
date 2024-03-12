#include "../include/flights.h"


struct flights{
    char *id; //não pode ser vazio
    char *airline; //não pode ser vazio
    char *plane_model; //não pode ser vazio
    int total_seats; //não poderá ser inferior ao número de passageiros nesse voos
    char *origin; // constituídos por 3 letras
    char *destination; // constituídos por 3 letras
    DateClock* s_departure_date; //tem que vir antes de schedule_arrival_date
    DateClock* s_arrival_date;
    DateClock* r_departure_date; //tem que vir antes de real_arrival_date
    DateClock* r_arrival_date;
    char *pilot; //não pode ser vazio
    char *copilot; //não pode ser vazio
    char *notes; //pode ser vazio

    int free_seats;
};


FLIGHTS newFlight(){
    FLIGHTS f = malloc(sizeof(struct flights));
    if (f == NULL) {
        // Trate o erro de alocação de memória
        return NULL;
    }

    f -> id = NULL;
    f -> airline = NULL;
    f -> plane_model = NULL;
    f -> total_seats = 0;
    f -> origin = NULL;
    f -> destination = NULL;
    f -> s_departure_date = NULL;
    f -> s_arrival_date = NULL;
    f -> r_departure_date = NULL;
    f -> r_arrival_date = NULL;
    f -> pilot = NULL;
    f -> copilot = NULL;
    f -> notes = NULL;

    f -> free_seats = 0;

    return f;
}

char ** takeLineF(char * line) {
    char** tokens = malloc(sizeof(char *) * 13);
    int i = 0;
    char * token = NULL;
    while ((token = strsep(&line, ";")) && i < 13) {
        tokens[i++] = token;
    }
    return tokens;
}

FLIGHTS initFlightFromLine( char *line){
    if (line == NULL)
        return NULL;
    
    int valid = 1;
    char *line_dup = strdup(line);
    
    char ** tokens = takeLineF(line);

    FLIGHTS flights = newFlight();

    // Atribui os campos da estrutura flights com os tokens
    flights->id = strdup(tokens[0]);
    if (valida_notzero(flights->id) != 0) {
        valid = 0;
    }
    
    flights->airline = strdup(tokens[1]);
    if (valida_notzero(flights->airline) != 0) {
        valid = 0;
    }
    
    flights->plane_model = strdup(tokens[2]);
    if (valida_notzero(flights->plane_model) != 0) {
        valid = 0;
    }
    
    char* totSeats = tokens[3];
    if(isInt(totSeats) == 0){
        valid = 0;
    }
    else{
        flights->total_seats = atoi(totSeats);
        if (flights->total_seats <= 0) {
            valid = 0;
        }
    }
    
    
    flights->origin = strdup(tokens[4]);
    if(flights->origin==NULL || strlen(flights->origin) != 3){
        valid = 0;
    }
    else{
        for(int i=0; i<3; i++){
            if(!isLetter(flights->origin[i])){
                valid = 0;
            }
            else{
                flights->origin[i] = toUpper(flights->origin[i]);
            }
        }
    }

    flights->destination = strdup(tokens[5]);
    if(flights->destination==NULL || strlen(flights->destination) != 3){
        valid = 0;
    }
    else{
        for(int i=0; i<3; i++){
            if(!isLetter(flights->destination[i])){
                valid = 0;
            }
            else{
                flights->destination[i] = toUpper(flights->destination[i]);
            }
        }
    }

    flights->s_departure_date = preenche_data_hora(tokens[6]);
    // if (flights->s_departure_date == NULL) { // é validado em baixo, não é preciso aqui
    //     valid = 0;
    // }
    
    flights->s_arrival_date = preenche_data_hora(tokens[7]);
    if (flights->s_arrival_date == NULL || flights->s_departure_date == NULL || compareDateClock(flights->s_departure_date, flights->s_arrival_date) >= 0) {
        valid = 0;
    }
    
    flights->r_departure_date = preenche_data_hora(tokens[8]);
    // if (flights->r_departure_date == NULL) { // é validado em baixo, não é preciso aqui
    //     valid = 0;
    // }
    
    flights->r_arrival_date = preenche_data_hora(tokens[9]);
    if (flights->r_arrival_date == NULL || flights->r_departure_date == NULL || compareDateClock(flights->r_departure_date, flights->r_arrival_date) >= 0) {
        valid = 0;
    }

    flights->pilot = strdup(tokens[10]);
    if (valida_notzero(flights->pilot) != 0) {
        valid = 0;
    }

    flights->copilot = strdup(tokens[11]);
    if (valida_notzero(flights->copilot) != 0) {
        valid = 0;
    }

    flights->notes = strdup(tokens[12]);
    if (flights->notes == NULL) {
        valid = 0;
    }

    if (!valid) {
        char *aux = malloc(STR_SIZE*sizeof(char));
        strcpy(aux, line_dup);
        strcat(aux, "\n");
        apendStringToFile(aux, "Resultados/flights_errors.csv");
        free(aux);

        freeFlight(flights);
        flights = NULL;
    }
    else{
        flights->free_seats = flights->total_seats;
    }

    free(line_dup);
    free(tokens);
    return flights;
}

////////// MÉTODOS GET //////////

char *getIdF (FLIGHTS f) {
    return strdup(f->id);
}

char *getAirlineF (FLIGHTS f) {
    return strdup(f->airline);
}

char *getPlane_modelF (FLIGHTS f) {
    return strdup(f->plane_model);
}

int getTotal_seatsF (FLIGHTS f) {
    return f -> total_seats;
}

char *getOriginF (FLIGHTS f) {
    return strdup(f->origin);
}

char *getDestinationF (FLIGHTS f) {
    return strdup(f->destination);
}

DateClock *getS_departure_dateF (FLIGHTS f) {
    return cloneDateClock(f->s_departure_date);
}

DateClock *getS_arrival_dateF (FLIGHTS f) {
    return cloneDateClock(f->s_arrival_date);
}

DateClock *getR_departure_dateF (FLIGHTS f) {
    return cloneDateClock(f->r_departure_date);
}

DateClock *getR_arrival_dateF (FLIGHTS f) {
    return cloneDateClock(f->r_arrival_date);
}

char *getPilotF (FLIGHTS f) {
    return strdup(f->pilot);
}

char *getCopilotF (FLIGHTS f) {
    return strdup(f->copilot);
}

char *getNotesF (FLIGHTS f) {
    return strdup(f->notes);
}

int getOcupied_seatsF (FLIGHTS f) {
    return f->total_seats - f->free_seats;
}

int consumeSeat (FLIGHTS f) {
    if (f->free_seats > 0) {
        f->free_seats--;
        return 1;
    }
    return 0;
}


////////// MÉTODO FREE //////////

void freeFlight(FLIGHTS flights) {
    if (flights) { //verifica se o pointer não é nulo
        if (flights->id) free(flights->id);
        if (flights->airline) free(flights->airline);
        if (flights->plane_model) free(flights->plane_model);
        if (flights->origin) free(flights->origin);
        if (flights->destination) free(flights->destination);
        if (flights->s_departure_date) free_date(flights->s_departure_date);
        if (flights->s_arrival_date) free_date(flights->s_arrival_date);
        if (flights->r_departure_date) free_date(flights->r_departure_date);
        if (flights->r_arrival_date) free_date(flights->r_arrival_date);
        if (flights->pilot) free(flights->pilot);
        if (flights->copilot) free(flights->copilot);
        if (flights->notes) free(flights->notes);
        free(flights); // Liberta a strut inteira
    }
}

void free_flight_void (gpointer flights){
    freeFlight(flights);
}

////////// FUNÇÕES AUXILIARES //////////

int compare_departureDate_Then_Id(gconstpointer a, gconstpointer b, gpointer hashT){
    GHashTable *hash = (GHashTable*) hashT;
    FLIGHTS flightA = g_hash_table_lookup(hash, (char*)a);
    FLIGHTS flightB = g_hash_table_lookup(hash, (char*)b);

    int diff = compareDateClock(flightB->s_departure_date, flightA->s_departure_date);

    if(diff == 0){
        diff = strcmp(flightA->id, flightB->id);
    }
    
    return diff;
}

int calculaAtrasoPartida(FLIGHTS f){
    int atraso = 0;
    if(f->r_departure_date != NULL && f->s_departure_date != NULL){
        atraso = calculadif(f->s_departure_date, f->r_departure_date);
    }
    return atraso;
}

char* flightToStringQuery5(FLIGHTS f, int flag, int i){
    char *str = malloc(sizeof(char) * STR_SIZE);
    char* d1 = DateClockToString(f->s_departure_date);

    if(flag==0){
        sprintf(str, "--- %d ---\nid: %s\nschedule_departure_date: %s\ndestination: %s\nairline: %s\nplane_model: %s\n", 
                    i+1, f->id, d1, f->destination, f->airline, f->plane_model);
    }else{
        sprintf(str, "%s;%s;%s;%s;%s", 
                    f->id, d1, f->destination, f->airline, f->plane_model);
    }
    free(d1);

    return str;
}

char* flightToStringQuery1(FLIGHTS f, int flag){
    char *str = malloc(sizeof(char) * STR_SIZE);
    //companhia;avião;origem;destino;partida_est;chegada_est;número_passageiros;tempo_atraso

    int tempo_atraso = calculaAtrasoPartida(f);//em segundos
    int num_passageiros = f->total_seats - f->free_seats;

    char* departureString = DateClockToString(f->s_departure_date);
    char* arrivalString = DateClockToString(f->s_arrival_date);

    if(flag==0)
        sprintf(str, "--- 1 ---\nairline: %s\nplane_model: %s\norigin: %s\ndestination: %s\nschedule_departure_date: %s\nschedule_arrival_date: %s\npassengers: %d\ndelay: %d",
                    f->airline, f->plane_model, f->origin, f->destination, departureString, arrivalString, num_passageiros, tempo_atraso
        );
        
    else
        sprintf(str, "%s;%s;%s;%s;%s;%s;%d;%d", 
                    f->airline, f->plane_model, f->origin, f->destination, departureString, arrivalString, num_passageiros, tempo_atraso
        );

    free(departureString);
    free(arrivalString);    
    
    return str;
}
