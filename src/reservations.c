#include "../include/reservations.h"


struct reservations{
    char *id; //não pode ser vazio
    char *user_id; //não pode ser vazio
    char *hotel_id; //não pode ser vazio
    char *hotel_name; //não pode ser vazio
    int hotel_stars; //um valor inteiro entre 1 e 5
    int city_tax; //um valor inteiro maior ou igual a zero
    char *address; //não pode ser vazio
    DateClock* begin_date; //tem que vir antes do end_date
    DateClock* end_date;
    int price_per_night; //valor inteiro maior que 0
    char *includes_breakfast; //FASLSO: “f ”, “false”, “0”, e “” VERDADE: “t”, “true”, e “1”.
    char *room_details; //pode ser vazio
    int rating; //valor inteiro entre 1 e 5 ou vazio 
    char *comment; //pode ser vazio
};

RESERVATIONS newReservation(){
    RESERVATIONS r = malloc(sizeof(struct reservations));
    r -> id = NULL;
    r -> user_id = NULL; 
    r -> hotel_id = NULL;
    r -> hotel_name = NULL;
    r -> hotel_stars = 0;
    r -> city_tax = 0;
    r -> address = NULL;
    r -> begin_date = NULL;
    r -> end_date = NULL;
    r -> price_per_night = 0;
    r -> includes_breakfast = NULL;
    r -> room_details = NULL;
    r -> rating = 0;
    r -> comment = NULL;

    return r;
}

char* reservationToStringQuery4(RESERVATIONS r, int flag, int i, double totalPrice){
    if (r == NULL)
        return "NULL";

    char *str = malloc(sizeof(char) * STR_SIZE);
    if(flag == 0){
        sprintf(str, "--- %d ---\nid: %s\nbegin_date: %04d/%02d/%02d\nend_date: %04d/%02d/%02d\nuser_id: %s\nrating: %d\ntotal_price: %.3f\n", 
                    i+1, r->id, 
                    getDateClockAno(r->begin_date), getDateClockMes(r->begin_date),getDateClockDia(r->begin_date),
                    getDateClockAno(r->end_date), getDateClockMes(r->end_date),getDateClockDia(r->end_date),
                    r->user_id, r->rating, totalPrice);
    }
    else{
        sprintf(str, "%s;%04d/%02d/%02d;%04d/%02d/%02d;%s;%d;%.3f", 
                    r->id, 
                    getDateClockAno(r->begin_date), getDateClockMes(r->begin_date), getDateClockDia(r->begin_date), 
                    getDateClockAno(r->end_date), getDateClockMes(r->end_date), getDateClockDia(r->end_date), 
                    r->user_id, r->rating, totalPrice);
    }

    return str;
}

char ** takeLineR(char * line) {
    char** tokens = malloc(sizeof(char *) * 14);
    int i = 0;
    char * token = NULL;
    while ((token = strsep(&line, ";")) && i < 14) {
        tokens[i++] = token;
    }
    return tokens;
}

RESERVATIONS initReservationFromLine( char *line, GHashTable *hashU){
    if (line == NULL)
        return NULL;

    int valid = 1;
    char *line_dup = strdup(line);
    
    RESERVATIONS reservations = newReservation();

    char ** tokens = takeLineR(line);


    // Atribui os campos da estrutura reservations com os tokens
    reservations->id = strdup(tokens[0]);
    if (valida_notzero(reservations->id) != 0) {
        valid = 0;
    }

    reservations->user_id = strdup(tokens[1]);
    if (valida_notzero(reservations->user_id) != 0) {
        valid = 0;
    }

    reservations->hotel_id = strdup(tokens[2]);
    if (valida_notzero(reservations->hotel_id) != 0) {
        valid = 0;
    }

    reservations->hotel_name = strdup(tokens[3]);
    if (valida_notzero(reservations->hotel_name) != 0) {
        valid = 0;
    }

    char* hoSta = tokens[4];
    if(isInt(hoSta) == 0){
        valid = 0;
    }
    else{
        reservations->hotel_stars = atoi(hoSta);
        if (reservations->hotel_stars <= 0 || reservations->hotel_stars > 5 ){
            valid = 0;
        }
    }

    char* ciTax = tokens[5];
    if(isInt(ciTax) == 0){
        valid = 0;
    }
    else{
        reservations->city_tax = atoi(ciTax);
        if (reservations->city_tax <= 0){
            valid = 0;
        }
    }

    reservations->address = strdup(tokens[6]);
    if (valida_notzero(reservations->address) != 0) {
       valid = 0;
    }

    reservations->begin_date = preenche_data_hora(tokens[7]);
    // if (reservations->begin_date == NULL) { // é validado em baixo, não é preciso aqui
    //     valid = 0;
    // }

    reservations->end_date = preenche_data_hora(tokens[8]);
    if (reservations->end_date == NULL || reservations->begin_date == NULL || compareDateClock(reservations->begin_date, reservations->end_date) >= 0) {
        valid = 0;
    }

    char* priPNi = tokens[9];
    if(isInt(priPNi) == 0){
        valid = 0;
    }
    else{
        reservations->price_per_night = atoi(priPNi);
        if (reservations->price_per_night <= 0){
            valid = 0;
        }
    }

    reservations->includes_breakfast = strdup(tokens[10]);
    if (reservations->includes_breakfast == NULL) {
        valid = 0;
    }else{
        char *i_b = toLowerCase(reservations->includes_breakfast);
        if(strcmp(i_b, "f") == 0 || strcmp(i_b, "false") == 0 || strcmp(i_b, "0") == 0 || strcmp(i_b, "") == 0){
            free(i_b);
            reservations->includes_breakfast = strdup("False");
        }
        else if (strcmp(i_b, "t") == 0 || strcmp(i_b, "true") == 0 || strcmp(i_b, "1") == 0) {
            free(i_b);
            reservations->includes_breakfast = strdup("True");
        }
        else{
            valid = 0;
        }
    }

    reservations->room_details = strdup(tokens[11]);
    if (reservations->room_details == NULL) {
        valid = 0;
    }

    char* rat = tokens[12];
    if(isInt(rat) == 0){
        valid = 0;
    }
    else{
        reservations->rating = atoi(rat);
        if (reservations->rating <= 0 || reservations->rating > 5){ // NULL ou string vazia faz com que o atoi retorne 0 e daí o '< 0' em vez de '<=0'
            valid = 0;
        }
    }
    
    reservations->comment = strdup(tokens[13]);
    if (reservations->comment == NULL) {
        valid = 0;
    }

    if (!g_hash_table_contains(hashU, reservations->user_id)){
        valid = 0;
    }

    if (!valid) {
        char* aux = malloc(STR_SIZE * sizeof(char));
        strcpy(aux, line_dup);
        strcat(aux, "\n");
        apendStringToFile(aux, "Resultados/reservations_errors.csv");
        free(aux);
        freeReservation(reservations);
        reservations = NULL;
    }
    
    free(line_dup);
    free(tokens);
    return reservations;
    
}

////////// MÉTODOS GET //////////


char *getIdR (RESERVATIONS r) {
    return strdup(r->id);
}

char *getUser_idR (RESERVATIONS r) {
    return strdup(r->user_id);
}

char *getHotel_idR (RESERVATIONS r) {
    return strdup(r->hotel_id);
}

char *getHotel_nameR (RESERVATIONS r) {
    return strdup(r->hotel_name);
}

int getHotel_starsR (RESERVATIONS r) {
    return r -> hotel_stars;
}

int getCity_taxR (RESERVATIONS r) {
    return r -> city_tax;
}

char *getAddressR (RESERVATIONS r) {
    return strdup(r->address);
}

DateClock *getBegin_dateR (RESERVATIONS r) {
    return cloneDateClock(r->begin_date);
}

DateClock *getEnd_dateR (RESERVATIONS r) {
    return cloneDateClock(r->end_date);
}

int getPrice_per_nightR (RESERVATIONS r) {
    return r -> price_per_night;
}

char *getIncludeS_breakfastR (RESERVATIONS r) {
    return strdup(r->hotel_name);
}

char *getRoom_detailstR (RESERVATIONS r) {
    return strdup(r->room_details);
}

int getRatingR (RESERVATIONS r) {
    return r->rating;
}

char *getCommentR (RESERVATIONS r) {
    return strdup(r->comment);
}


void freeReservation(RESERVATIONS reservations) {
    if (reservations) { //verifica se o pointer não é nulo
        if (reservations->id) free(reservations->id);
        if (reservations->user_id) free(reservations->user_id);
        if (reservations->hotel_id) free(reservations->hotel_id);
        if (reservations->hotel_name) free(reservations->hotel_name);
        if (reservations->address) free(reservations->address);
        if (reservations->begin_date) free_date(reservations->begin_date);
        if (reservations->end_date) free_date(reservations->end_date);
        if (reservations->includes_breakfast) free(reservations->includes_breakfast);
        if (reservations->room_details) free(reservations->room_details);
        if (reservations->comment) free(reservations->comment);
        free(reservations); // Liberta a strut inteira
    }
}

void free_reservation_void (gpointer reservations){
    freeReservation(reservations);
}

int compare_beginDate_Then_Id(gconstpointer a, gconstpointer b, gpointer hashT) {
    GHashTable* hash = (GHashTable*)hashT;
    RESERVATIONS r1 = g_hash_table_lookup(hash, (char*)a);
    RESERVATIONS r2 = g_hash_table_lookup(hash, (char*)b);

    int diff = compareDateClock(r2->begin_date, r1->begin_date);

    if (diff == 0) {
        diff = strcmp(r1->id, r2->id);
    }

    return diff;
}

char* reservationToStringQuery1(RESERVATIONS r, int flag){
    if (r == NULL)
        return "NULL";
    // id_hotel;nome_hotel;estrelas_hotel;data_início;data_fim;pequeno_almoço;número_de_noites;preço_total
    
    char *str = malloc(sizeof(char) * STR_SIZE);

    int nrNoites = getNrNights(r->begin_date, r->end_date);
    double totalPrice = (double)r->price_per_night * (double)nrNoites;
    totalPrice = totalPrice + (totalPrice/(double)100 * (double)r->city_tax);

    if(flag == 0){
        sprintf(str, "--- 1 ---\nhotel_id: %s\nhotel_name: %s\nhotel_stars: %d\nbegin_date: %04d/%02d/%02d\nend_date: %04d/%02d/%02d\nincludes_breakfast: %s\nnights: %d\ntotal_price: %.3f",
                    r->hotel_id, r->hotel_name, r->hotel_stars, 
                    getDateClockAno(r->begin_date), getDateClockMes(r->begin_date), getDateClockDia(r->begin_date), 
                    getDateClockAno(r->end_date), getDateClockMes(r->end_date), getDateClockDia(r->end_date), 
                    r->includes_breakfast, nrNoites, totalPrice);
    }
    else{
        sprintf(str, "%s;%s;%d;%04d/%02d/%02d;%04d/%02d/%02d;%s;%d;%.3f", 
                    r->hotel_id, r->hotel_name, r->hotel_stars, 
                    getDateClockAno(r->begin_date), getDateClockMes(r->begin_date), getDateClockDia(r->begin_date), 
                    getDateClockAno(r->end_date), getDateClockMes(r->end_date), getDateClockDia(r->end_date), 
                    r->includes_breakfast, nrNoites, totalPrice);
    }

    return str;
}
