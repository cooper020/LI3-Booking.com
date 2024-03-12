#include "../include/queries.h"

char** query1 (GHashTable *hashU, GHashTable *hashF, GHashTable *hashR, GHashTable* hashP, char *ID, int flag){
    FLIGHTS f;
    RESERVATIONS r;
    char** str = malloc(sizeof(char*)*2);
    
    USERS u = g_hash_table_lookup(hashU, ID);

    if(u==NULL){
        f=g_hash_table_lookup(hashF, ID);

        if(f==NULL){
            r = g_hash_table_lookup(hashR, ID);

            if(r!=NULL){
                // encontrou a reserva
                char* tmp = reservationToStringQuery1(r, flag);
                strcat(tmp, "\n");
                str[0] = strdup(tmp);
                free(tmp);
            }
            else{
                str[0] = NULL;
            }
        }
        else{
            // encontrou o voo
            char* tmp = flightToStringQuery1(f, flag);
            strcat(tmp, "\n");
            str[0] = strdup(tmp);
            free(tmp);
        }
    }
    else{
        // encontrou o utilizador
        char *isActive = getAccount_statusU(u);
        if(strcmp(isActive, "inactive") != 0){
            int nrFlights = getNrFlights(u, hashP);

            int nrReservations;
            double totalSpent;
            getNrReservationsAndTotalSpent(u, hashR, &nrReservations, &totalSpent);

            char* tmp = userToStringQuery1(u, flag, nrFlights, nrReservations, totalSpent);
            strcat(tmp, "\n");
            str[0] = strdup(tmp);
            free(tmp);
        }
        else{
            str[0] = NULL;
        }
        free(isActive);
    }
    str[1] = NULL;

    return str;
}


int compareDateClockQuery2(gconstpointer a, gconstpointer b, gpointer hashT) {
    GHashTable* hash = (GHashTable*)hashT;
    DateClock* value_a = (DateClock*)g_hash_table_lookup(hash, a);
    DateClock* value_b = (DateClock*)g_hash_table_lookup(hash, b);
    int diff = compareDateClock(value_b, value_a);
    if (diff == 0) {
        return strcmp((char*)a, (char*)b);
    } else {
        return diff;
    }
}
char** query2 (GHashTable *hashU, GHashTable *hashR, GHashTable *hashP, GHashTable *hashF, char *userID, char *type, int flag){    
    GList* sorted_keys = NULL;
    GHashTable *infoHash = NULL;
    GList *listFlights = NULL;

    if (strlen(type) == 0 || strcmp(type, "reservations") == 0 || strcmp(type, "flights") == 0) {
        USERS user = g_hash_table_lookup(hashU, userID);
        if (user != NULL) {

            char* status = getAccount_statusU(user);
            if (strcmp(status, "inactive") != 0) {
            
                infoHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, freeDateTime_void);
                listFlights = NULL;

                GHashTableIter iter;
                gpointer key, value;
                if (strlen(type) == 0 || strcmp(type, "reservations") == 0) {
                    g_hash_table_iter_init (&iter, hashR);
                    while (g_hash_table_iter_next (&iter, &key, &value)) {
                        RESERVATIONS reservation = value;

                        char* current_user_id = getUser_idR(reservation);
                        if (strcmp(current_user_id, userID) == 0) {
                            char* reservation_id = getIdR(reservation);
                            DateClock* beginDate = getBegin_dateR(reservation);
                            setTimeToZero(beginDate);

                            g_hash_table_insert(infoHash, reservation_id, beginDate);
                        }
                        free(current_user_id);
                    }
                }

                if (strlen(type) == 0 || strcmp(type, "flights") == 0) {
                    g_hash_table_iter_init (&iter, hashP);
                    while (g_hash_table_iter_next (&iter, &key, &value)) {
                        PASSENGERS passenger = value;

                        char* current_user_id = getUser_idP(passenger);
                        if (strcmp(current_user_id, userID) == 0) {
                            char* current_flight_id = getFlight_idP(passenger);

                            FLIGHTS f = g_hash_table_lookup(hashF, current_flight_id);
                            DateClock* beginDate = getS_departure_dateF(f);
                            setTimeToZero(beginDate);

                            g_hash_table_insert(infoHash, current_flight_id, beginDate);
                            listFlights = g_list_append(listFlights, current_flight_id);
                        }
                        free(current_user_id);
                    }
                }

                sorted_keys = g_hash_table_get_keys(infoHash);
                sorted_keys = g_list_sort_with_data(sorted_keys, compareDateClockQuery2, infoHash);
            }
            free(status);
        }
    }


    int size = g_list_length(sorted_keys);
    char** str = malloc(sizeof(char*)*(size+1));
    
    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int writeType;
    if (strlen(type) > 0) {
        writeType = 0;
    } else{
        writeType = 1;
    }
    int i;
    for (i = 0; iter_keys != NULL; ++i) {
        char* key = (char*)iter_keys->data;
        DateClock* value = (DateClock*)g_hash_table_lookup(infoHash, key);
        char* current_type;
        if(writeType == 1){
            if (g_list_find(listFlights, key) != NULL) {
                current_type = "flight";
            } else {
                current_type = "reservation";
            }
        }

        char* date = DateClockToString(value);
        char* justDate = strndup(date, 10);
        free(date);

        char* line = malloc(sizeof(char)*STR_SIZE);
        if (flag == 0){
            if(i>0){
                sprintf(line, "\n--- %d ---\nid: %s\ndate: %s\n", i+1, key, justDate);
            }
            else{
                sprintf(line, "--- %d ---\nid: %s\ndate: %s\n", i+1, key, justDate);
            }
            if(writeType == 1){
                strcat(line, "type: ");
                strcat(line, current_type);
                strcat(line, "\n");
            }
        } else {
            sprintf(line, "%s;%s", key, justDate);
            if(writeType == 1){
                strcat(line, ";");
                strcat(line, current_type);
                strcat(line, "\n");
            }
            else{
                strcat(line, "\n");
            }
        }
        free(justDate);

        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;

    if(infoHash)
        g_hash_table_destroy(infoHash);
    if(sorted_keys)
        g_list_free(sorted_keys);
    if(listFlights)
        g_list_free(listFlights);

    return str;
}

char** query3(GHashTable *hashR, char *hotel_Id, int flag) {
    int rating = 0;
    int size = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashR);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        RESERVATIONS reservation = value;
        char* current_hotel_id = getHotel_idR(reservation);
        if (strcmp(current_hotel_id, hotel_Id) == 0) {
            size++;
            rating += getRatingR(reservation);
        }
        free(current_hotel_id);
    }

    double values;
    if(size>0)
        values = (double)rating/(double)size;
    else
        values = (double)0;

    char** str = malloc(sizeof(char*)*2);
    char* line = malloc(sizeof(char)*STR_SIZE);

    if(flag == 0){
        sprintf(line, "--- 1 ---\nrating: %.3f\n", values);
    } else{
        sprintf(line, "%.3f\n", values);
    }
    str[0] = strdup(line);
    free(line);
    str[1] = NULL;

    return str;
}

char** query4(GHashTable *hashR, char *hotel_Id, int flag) {
    GHashTable* auxHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashR);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        RESERVATIONS reservation = value;
        char* current_hotel_id = getHotel_idR(reservation);
        if (strcmp(current_hotel_id, hotel_Id) == 0) {
            char* id_res = getIdR(reservation);
            g_hash_table_insert(auxHash, id_res, reservation);
        }
        free(current_hotel_id);
    }

    GList* sorted_keys = g_hash_table_get_keys(auxHash);
    sorted_keys = g_list_sort_with_data(sorted_keys, compare_beginDate_Then_Id, auxHash);
    int size = g_list_length(sorted_keys);

    char** str = malloc(sizeof(char*)*(size+1));

    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int i;
    for (i = 0; iter_keys != NULL; ++i) {
        char* key = (char*)iter_keys->data;
        RESERVATIONS reservation = (RESERVATIONS)g_hash_table_lookup(auxHash, key);

        DateClock* beginDate = getBegin_dateR(reservation);
        DateClock* endDate = getEnd_dateR(reservation);
        double totalPrice = (double)getPrice_per_nightR(reservation) * (double)getNrNights(beginDate, endDate);
        totalPrice = totalPrice + (totalPrice/(double)100 * (double)getCity_taxR(reservation));

        free(beginDate);
        free(endDate);

        char* line = reservationToStringQuery4(reservation, flag, i, totalPrice);
        if (flag != 0 || i != size-1) {
            strcat(line, "\n");
        }
        
        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;
    
    g_list_free(sorted_keys);
    g_hash_table_destroy(auxHash);

    return str;
}

char** query5 (GHashTable *hashF, char *name, DateClock *begin, DateClock *end, int flag){
    GHashTable* auxHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashF);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        FLIGHTS flight = value;
        char* current_origin = getOriginF(flight);
        if (strcmp(current_origin, name) == 0) {
            DateClock* beginDate = getS_departure_dateF(flight);
            DateClock* endDate = getS_arrival_dateF(flight);

            if (compareDateClock(beginDate, begin) >= 0 && compareDateClock(endDate, end) <= 0) {
                char* id = getIdF(flight);
                g_hash_table_insert(auxHash, id, flight);
            }
            free(beginDate);
            free(endDate);
        }
        free(current_origin);
    }

    GList* sorted_keys = g_hash_table_get_keys(auxHash);
    sorted_keys = g_list_sort_with_data(sorted_keys, compare_departureDate_Then_Id, auxHash);
    int size = g_list_length(sorted_keys);

    char** str = malloc(sizeof(char*)*(size+1));

    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int i=0;
    for (i = 0; iter_keys != NULL; ++i) {
        char* key = (char*)iter_keys->data;
        FLIGHTS flight = (FLIGHTS)g_hash_table_lookup(auxHash, key);

        char* line = flightToStringQuery5(flight, flag, i);
        if (flag != 0 || i != size-1) {
            strcat(line, "\n");
        }
        
        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;
    
    g_list_free(sorted_keys);
    g_hash_table_destroy(auxHash);

    return str;
}


int compareIntThenStr(gconstpointer a, gconstpointer b, gpointer hashT) {
    GHashTable* hash = (GHashTable*)hashT;
    int value_a = GPOINTER_TO_INT(g_hash_table_lookup(hash, a));
    int value_b = GPOINTER_TO_INT(g_hash_table_lookup(hash, b));
    int diff = value_b - value_a;

    if (diff == 0) {
        diff = strcmp((char*)a, (char*)b);
    }

    return diff;
}
char** query6 (GHashTable *hashF, int year, int topN, int flag){
    GHashTable* auxHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashF);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        FLIGHTS flight = value;
        DateClock* departure_date = getS_departure_dateF(flight);
        if(getDateClockAno(departure_date) == year){
            char* current_origin = getOriginF(flight);
            char* current_destination = getDestinationF(flight);
            int passengers = getOcupied_seatsF(flight);

            if (!g_hash_table_contains(auxHash, current_origin)) {
                g_hash_table_insert(auxHash, current_origin, GINT_TO_POINTER(passengers));
            } else {
                int old = GPOINTER_TO_INT(g_hash_table_lookup(auxHash, current_origin));
                g_hash_table_replace(auxHash, current_origin, GINT_TO_POINTER(old + passengers));
            }

            if (!g_hash_table_contains(auxHash, current_destination)) {
                g_hash_table_insert(auxHash, current_destination, GINT_TO_POINTER(passengers));
            } else {
                int old = GPOINTER_TO_INT(g_hash_table_lookup(auxHash, current_destination));
                g_hash_table_replace(auxHash, current_destination, GINT_TO_POINTER(old + passengers));
            }
        }
        free(departure_date);
    }
    
    GList* sorted_keys = g_hash_table_get_keys(auxHash);
    sorted_keys = g_list_sort_with_data(sorted_keys, compareIntThenStr, auxHash);
    int size = g_list_length(sorted_keys);

    char** str = malloc(sizeof(char*)*(size+1));

    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int i=0;
    for (i = 0; i < topN && iter_keys != NULL; ++i) {
        char* key = (char*)iter_keys->data;
        int value = GPOINTER_TO_INT(g_hash_table_lookup(auxHash, key));

        char* line = malloc(sizeof(char)*STR_SIZE);

        if(flag == 0){
            if(i!=0){
                sprintf(line, "\n--- %d ---\nname: %s\npassengers: %d\n", i+1, key, value);
            }
            else{
                sprintf(line, "--- %d ---\nname: %s\npassengers: %d\n", i+1, key, value);
            }
        }
        else{
            sprintf(line, "%s;%d\n", key, value);
        }

        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;

    g_list_free(sorted_keys);
    g_hash_table_destroy(auxHash);

    return str;
}

int compare_integers(gconstpointer a, gconstpointer b) {
    int value_a = GPOINTER_TO_INT(a);
    int value_b = GPOINTER_TO_INT(b);

    return value_a - value_b;
}
void free_GList(gpointer data) {
    //g_list_free_full(data, g_free);
    g_list_free(data);
}
char** query7 (GHashTable *hashF, int topN, int flag){
    GHashTable* auxHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL); 
    GHashTable* topHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashF);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        FLIGHTS flight = value;
        char* current_origin = getOriginF(flight);
        
        int delay = calculaAtrasoPartida(flight);

        if (!g_hash_table_contains(auxHash, current_origin)) {
            GList* delays = g_list_append(NULL, GINT_TO_POINTER(delay)); //MEM. LEAK
            g_hash_table_insert(auxHash, current_origin, delays);
        } else {
            GList* delays = g_hash_table_lookup(auxHash, current_origin);
            GList* delays_copy = g_list_copy(delays); //MEM. LEAK
            
            delays_copy = g_list_append(delays_copy, GINT_TO_POINTER(delay)); //MEM. LEAK
            g_hash_table_replace(auxHash, current_origin, delays_copy);

            g_list_free(delays);
        }
    }

    g_hash_table_iter_init (&iter, auxHash);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        GList* delays = value;
        int size = g_list_length(delays);
        GList* sorted_delays = g_list_sort(delays, compare_integers);

        int median_idx = size / 2;
        int median;
        if (size % 2 == 0) {
            int left = GPOINTER_TO_INT(g_list_nth_data(sorted_delays, median_idx - 1));
            int right = GPOINTER_TO_INT(g_list_nth_data(sorted_delays, median_idx));
            median = (left + right) / 2;
        } else {
            median = GPOINTER_TO_INT(g_list_nth_data(sorted_delays, median_idx));
        }

        g_hash_table_insert(topHash, strdup(key), GINT_TO_POINTER(median));

        g_list_free(sorted_delays);
    }
    
    GList* sorted_keys = g_hash_table_get_keys(topHash);
    sorted_keys = g_list_sort_with_data(sorted_keys, compareIntThenStr, topHash);

    char** str = malloc(sizeof(char*)*(topN+1));

    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int i=0;
    for (i = 0; i < topN && iter_keys != NULL; ++i) {
        char* key = (char*)iter_keys->data;
        int value = GPOINTER_TO_INT(g_hash_table_lookup(topHash, key));

        char* line = malloc(sizeof(char)*STR_SIZE);

        if(flag == 0){
            if(i!=0){
                sprintf(line, "\n--- %d ---\nname: %s\nmedian: %d\n", i+1, key, value);
            }
            else{
                sprintf(line, "--- %d ---\nname: %s\nmedian: %d\n", i+1, key, value);
            }
        }
        else{
            sprintf(line, "%s;%d\n", key, value);
        }

        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;

    g_list_free(sorted_keys);
    g_hash_table_destroy(auxHash);
    g_hash_table_destroy(topHash);

    return str;
}

char** query8(GHashTable *hashR, char *hotel_Id, DateClock *begin, DateClock *end, int flag) {
    int revenue = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashR);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        RESERVATIONS reservation = value;
        char* current_hotel_id = getHotel_idR(reservation);
        if (strcmp(current_hotel_id, hotel_Id) == 0){
            DateClock* beginDate = getBegin_dateR(reservation);
            DateClock* endDate = getEnd_dateR(reservation);
            
            int dias = contaNoites(beginDate, endDate, begin, end);
            if (dias > 0) {
                revenue += getPrice_per_nightR(reservation) * dias;
            }

            free(beginDate);
            free(endDate);
        }
        free(current_hotel_id);
    }

    char** str = malloc(sizeof(char*)*2);
    char* line = malloc(sizeof(char)*STR_SIZE);

    if (flag == 0) {
        sprintf(line, "--- 1 ---\nrevenue: %d\n", revenue);
    } else {
        sprintf(line, "%d\n", revenue);
    }

    str[0] = strdup(line);
    free(line);
    str[1] = NULL;

    return str;
}

int compare_query9(gconstpointer a, gconstpointer b, gpointer hashT) {
    char* strA = (char*)a;
    char* strB = (char*)b;
    GHashTable* hash = (GHashTable*)hashT;

    char* nameA = g_hash_table_lookup(hash, strA);
    char* nameB = g_hash_table_lookup(hash, strB);

    int diff = strcoll(nameA, nameB);

    if (diff == 0) {
        diff =  strcoll(strA, strB);
    }
    
    return diff;
}
char** query9 (GHashTable *hashU, char *prefix, int flag){
    GHashTable* auxHash = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashU);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        USERS user = value;

        char* account_status = getAccount_statusU(user);
        int diff = strcmp(account_status, "inactive");
        free(account_status);
        if (diff == 0) {
            continue;
        }

        char* user_name = getNameU(user);
        char* name_resized = strndup(user_name, strlen(prefix));
        diff = strcoll(name_resized, prefix);
        free(name_resized);

        if (diff == 0) {
            char* user_id = getIdU(user);
            g_hash_table_insert(auxHash, user_id, user_name);
        }
        else{
            free(user_name);
        }
    }

    GList* sorted_keys = g_hash_table_get_keys(auxHash);
    sorted_keys = g_list_sort_with_data(sorted_keys, compare_query9, auxHash);
    int size = g_list_length(sorted_keys);

    char** str = malloc(sizeof(char*)*(size+1));

    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int i=0;
    for (i = 0; iter_keys != NULL; ++i) {
        char* key = (char*)iter_keys->data;
        char* value = (char*)g_hash_table_lookup(auxHash, key);

        char* line = malloc(sizeof(char)*STR_SIZE);

        if(flag == 0){
            if(i!=0){
                sprintf(line, "\n--- %d ---\nid: %s\nname: %s\n", i+1, key, value);
            }
            else{
                sprintf(line, "--- %d ---\nid: %s\nname: %s\n", i+1, key, value);
            }
        }
        else{
            sprintf(line, "%s;%s\n", key, value);
        }

        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;
    
    g_list_free(sorted_keys);
    g_hash_table_destroy(auxHash);

    return str;
}

typedef struct query10Struct{
    int users;
    int flights;
    int passengers;
    GList* analysed_passengers;
    int unique_passengers;
    int reservations;
} *QUERY10STRUCT;

void freeQuery10Struct(gpointer data) {
    QUERY10STRUCT q10s = (QUERY10STRUCT)data;
    if(q10s->analysed_passengers)
        g_list_free_full(q10s->analysed_passengers, free);
    if(q10s)
        free(q10s);
}

int extractKEY(DateClock *date, int YEAR, int MONTH, int tipo){
    if(tipo == 1){
        return getDateClockAno(date);
    }
    else if(tipo == 2){
        int aux = getDateClockAno(date);
        if(aux == YEAR){
            return getDateClockMes(date);
        }
        else{
            return -1;
        }
    }
    else if(tipo == 3){
        int aux = getDateClockAno(date);
        if(aux == YEAR){
            aux = getDateClockMes(date);
            if(aux == MONTH){
                return getDateClockDia(date);
            }
            else{
                return -1;
            }
        }
        else{
            return -1;
        }
    }

    return 0;
}
int compare_strings(gconstpointer a, gconstpointer b) {
    return strcmp((char*)a, (char*)b);
}
char** query10(GHashTable *hashU, GHashTable* hashF, GHashTable *hashP, GHashTable *hashR, char* year, char* month, int flag){
    int tipo, YEAR, MONTH;
    if(strlen(year)==0 && strlen(month)==0){
        tipo = 1;// getAno
    }
    else if(strlen(year)>0 && strlen(month)==0){
        YEAR = atoi(year);
        if(YEAR<=0){
            char **str = malloc(sizeof(char*)*1);
            str[0] = NULL;
            return str;
        }
        tipo = 2;// getAno(YEAR) -> getMes
    }
    else if(strlen(year)>0 && strlen(month)>0){
        YEAR = atoi(year);
        MONTH = atoi(month);
        if(YEAR<=0 || MONTH<=0 || MONTH>12){
            char **str = malloc(sizeof(char*)*1);
            str[0] = NULL;
            return str;
        }
        tipo = 3;// getAno(YEAR) -> getMes(MONTH) -> getDia
    }
    else{
        char **str = malloc(sizeof(char*)*1);
        str[0] = NULL;
        return str;
    }

    GHashTable* agregatorHash = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, freeQuery10Struct);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashU);
    while(g_hash_table_iter_next (&iter, &key, &value)){
        USERS user = value;

        DateClock *acountCreationDate = getAccoutnt_creationU(user);
        int KEY = extractKEY(acountCreationDate, YEAR, MONTH, tipo);
        if(KEY>0){
            if(!g_hash_table_contains(agregatorHash, GINT_TO_POINTER(KEY))){
                QUERY10STRUCT q10s = malloc(sizeof(struct query10Struct));
                q10s->users = 1;
                q10s->flights = 0;
                q10s->passengers = 0;
                q10s->analysed_passengers = NULL;
                q10s->unique_passengers = 0;
                q10s->reservations = 0;

                g_hash_table_insert(agregatorHash, GINT_TO_POINTER(KEY), q10s);
            }
            else{
                QUERY10STRUCT q10s = g_hash_table_lookup(agregatorHash, GINT_TO_POINTER(KEY));
                q10s->users++;
            }
        }
        free(acountCreationDate);
    }

    g_hash_table_iter_init (&iter, hashF);
    while(g_hash_table_iter_next (&iter, &key, &value)){
        FLIGHTS flight = value;

        DateClock *sDepartureDate = getS_departure_dateF(flight);
        int KEY = extractKEY(sDepartureDate, YEAR, MONTH, tipo);

        if(KEY>0){
            if(!g_hash_table_contains(agregatorHash, GINT_TO_POINTER(KEY))){
                QUERY10STRUCT q10s = malloc(sizeof(struct query10Struct));
                q10s->users = 0;
                q10s->flights = 1;
                q10s->passengers = 0;
                q10s->analysed_passengers = NULL;
                q10s->unique_passengers = 0;
                q10s->reservations = 0;

                g_hash_table_insert(agregatorHash, GINT_TO_POINTER(KEY), q10s);
            }
            else{
                QUERY10STRUCT q10s = g_hash_table_lookup(agregatorHash, GINT_TO_POINTER(KEY));
                q10s->flights++;
            }
        }
        free(sDepartureDate);
    }

    g_hash_table_iter_init (&iter, hashP);
    while(g_hash_table_iter_next (&iter, &key, &value)){
        PASSENGERS passenger = value;

        char* flightID = getFlight_idP(passenger);
        FLIGHTS flight = g_hash_table_lookup(hashF, flightID);
        DateClock *sDepartureDate = getS_departure_dateF(flight);
        int KEY = extractKEY(sDepartureDate, YEAR, MONTH, tipo);

        if(KEY>0){
            char *userID = getUser_idP(passenger);
            if(!g_hash_table_contains(agregatorHash, GINT_TO_POINTER(KEY))){
                QUERY10STRUCT q10s = malloc(sizeof(struct query10Struct));
                q10s->users = 0;
                q10s->flights = 0;
                q10s->passengers = 1;
                
                q10s->unique_passengers = 1;
                q10s->reservations = 0;

                q10s->analysed_passengers = g_list_append(NULL, userID);

                g_hash_table_insert(agregatorHash, GINT_TO_POINTER(KEY), q10s);
            }
            else{
                QUERY10STRUCT q10s = g_hash_table_lookup(agregatorHash, GINT_TO_POINTER(KEY));
                q10s->passengers++;

                if(!g_list_find_custom(q10s->analysed_passengers, userID, compare_strings)){
                    q10s->unique_passengers++;
                    
                    q10s->analysed_passengers = g_list_append(q10s->analysed_passengers, userID);
                }
                else{
                    free(userID);
                }
            }
        }
        free(sDepartureDate);
        free(flightID);
    }

    g_hash_table_iter_init (&iter, hashR);
    while(g_hash_table_iter_next (&iter, &key, &value)){
        RESERVATIONS reservation = value;

        DateClock *sBeginDate = getBegin_dateR(reservation);
        int KEY = extractKEY(sBeginDate, YEAR, MONTH, tipo);

        if(KEY>0){
            if(!g_hash_table_contains(agregatorHash, GINT_TO_POINTER(KEY))){
                QUERY10STRUCT q10s = malloc(sizeof(struct query10Struct));
                q10s->users = 0;
                q10s->flights = 0;
                q10s->passengers = 0;
                q10s->analysed_passengers = NULL;
                q10s->unique_passengers = 0;
                q10s->reservations = 1;

                g_hash_table_insert(agregatorHash, GINT_TO_POINTER(KEY), q10s);
            }
            else{
                QUERY10STRUCT q10s = g_hash_table_lookup(agregatorHash, GINT_TO_POINTER(KEY));
                q10s->reservations++;
            }
        }
        free(sBeginDate);
    }
    
    GList* sorted_keys = g_hash_table_get_keys(agregatorHash);
    sorted_keys = g_list_sort(sorted_keys, compare_integers);
    int size = g_list_length(sorted_keys);

    char** str = malloc(sizeof(char*)*(size+1));

    char* intro;
    if(tipo == 1){
        intro = "year";
    }
    else if(tipo == 2){
        intro = "month";
    }
    else if(tipo == 3){
        intro = "day";
    }
    GList* iter_keys = g_list_nth(sorted_keys, 0);
    int i;
    for (i = 0; iter_keys != NULL; ++i) {
        int key = GPOINTER_TO_INT(iter_keys->data);
        QUERY10STRUCT q10s = g_hash_table_lookup(agregatorHash, GINT_TO_POINTER(key));

        char* line = malloc(sizeof(char)*STR_SIZE);

        if(flag == 0){
            if(i!=0){
                sprintf(line, "\n--- %d ---\n%s: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n", i+1, intro, key, q10s->users, q10s->flights, q10s->passengers, q10s->unique_passengers, q10s->reservations);
            }
            else{
                sprintf(line, "--- %d ---\n%s: %d\nusers: %d\nflights: %d\npassengers: %d\nunique_passengers: %d\nreservations: %d\n", i+1, intro, key, q10s->users, q10s->flights, q10s->passengers, q10s->unique_passengers, q10s->reservations);
            }
        }
        else{
            sprintf(line, "%d;%d;%d;%d;%d;%d\n", key, q10s->users, q10s->flights, q10s->passengers, q10s->unique_passengers, q10s->reservations);
        }

        str[i] = strdup(line);
        free(line);

        iter_keys = g_list_next(iter_keys);
    }
    str[i] = NULL;

    g_list_free(sorted_keys);
    g_hash_table_destroy(agregatorHash);

    return str;
}

char** extractArgs(char* args, int nrArgs){
    char* args_dup = NULL;
    if(args)
        args_dup = strdup(args);
    char* args_dup_start = args_dup;

    char** str = malloc(sizeof(char*)*nrArgs);

    for(int i=0; i<nrArgs; i++){
        if(args_dup && strlen(args_dup)>0){
            if(args_dup[0] == '"'){
                args_dup++;
                char* aux = strsep(&args_dup, "\"");
                if (aux)
                    str[i] = strdup(aux);
                else
                    str[i] = strdup("");
                aux = strsep(&args_dup, " ");
            }
            else{
                char* aux = strsep(&args_dup, " ");
                if (aux)
                    str[i] = strdup(aux);
                else
                    str[i] = strdup("");
            }
        }
        else{
            str[i] = strdup("");
        }
    }

    if(args_dup_start)
        free(args_dup_start);

    return str;
}
void freeArgs(char** args, int nrArgs){
    for(int i=0; i<nrArgs; i++){
        if(args[i])
            free(args[i]);
    }
    free(args);
}

void queries (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int num_qry, char *outputPath, char* args, int flag){
    GHashTable *hashU = getHashTableU(users);
    GHashTable *hashR = getHashTableR(reservations);
    GHashTable *hashP = getHashTableP(passengers);
    GHashTable *hashF = getHashTableF(flights);

    char** str = NULL;
    switch(num_qry){
        case 1:
        {
            char** argsArray = extractArgs(args, 1);
            char* ID = argsArray[0];

            if(strlen(ID)>0){
                str = query1 (hashU, hashF, hashR, hashP, ID, flag);
            }
        
            freeArgs(argsArray, 1);
        }
        break;

        case 2:
        {
            char **argsArray = extractArgs(args, 2);
            char* ID = argsArray[0];
            char* type = argsArray[1];

            if(strlen(ID)>0){
                str = query2(hashU, hashR, hashP, hashF, ID, type, flag);
            }

            freeArgs(argsArray, 2);
        }   
        break;

        case 3:
        {
            char** argsArray = extractArgs(args, 1);
            char *ID = argsArray[0];
            
            if(strlen(ID)>0){
                str = query3(hashR, ID, flag);
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 4:
        {
            char** argsArray = extractArgs(args, 1);
            char *ID = argsArray[0];
            
            if(strlen(ID)>0){
                str = query4(hashR, ID, flag);
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 5:
        {
            char** argsArray = extractArgs(args, 3);
            char *origin = argsArray[0];
            char *arg1 = argsArray[1];
            char *arg2 = argsArray[2];

            DateClock* begin = preenche_data_hora(arg1);
            DateClock* end = preenche_data_hora(arg2);

            if(strlen(origin)>0 && begin && end){
                str = query5(hashF, origin , begin, end, flag);
            }
            
            if(begin)
                free(begin);
            if(end)
                free(end);
            freeArgs(argsArray, 3);
        }
        break;

        case 6:
        {
            char** argsArray = extractArgs(args, 2);
            char *yearStr = argsArray[0];
            char *topNStr = argsArray[1];

            int year = atoi(yearStr);
            int topN = atoi(topNStr);

            if(year>0 && topN>0){
                str = query6(hashF, year, topN, flag);
            }

            freeArgs(argsArray, 2);
        }
        break;

        case 7:
        {
            char** argsArray = extractArgs(args, 1);
            char *topNStr = argsArray[0];

            int topN = atoi(topNStr);

            if(topN>0){
                str = query7 (hashF, topN, flag);
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 8:
        {
            char** argsArray = extractArgs(args, 3);
            char *hotel_id = argsArray[0];
            char *arg1 = argsArray[1];
            char *arg2 = argsArray[2];

            DateClock* begin = preenche_data_hora(arg1);
            DateClock* end = preenche_data_hora(arg2);

            if(strlen(hotel_id)>0 && begin && end){
                str = query8(hashR, hotel_id, begin, end, flag);
            }

            if (begin)
                free(begin);
            if (end)
                free(end);
            freeArgs(argsArray, 3);
        }
        break;

        case 9:
        {
            char** argsArray = extractArgs(args, 1);
            char *prefix = argsArray[0];
            
            if(strlen(prefix)>0){
                str = query9(hashU, prefix, flag);
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 10:
        {
            char** argsArray = extractArgs(args, 2);
            char *YEAR = argsArray[0];
            char *MONTH = argsArray[1];

            str = query10(hashU, hashF, hashP, hashR, YEAR, MONTH, flag);

            freeArgs(argsArray, 2);
        }
        break;
    }
    
    printArrayToFile(str, outputPath);

    if(str){
        for(int i=0; str[i]!=NULL; i++){
            free(str[i]);
        }

        free(str);
    }
}

void queries_iterative (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int num_qry){
    char* r = malloc(sizeof(char)*STR_SIZE);
    printLine("Insere o modo de output pretendido (0 - modo normal, 1 - modo field[F]): ");
    scanf("%s", r);
    if(strlen(r)!=1){
        printLine("Modo inválido\n");
        free(r);
        return;
    }

    int flag;
    if(r[0]=='0')
        flag = 1;
    else if(r[0]=='1')
        flag = 0;
    else{
        printLine("Modo inválido\n");
        free(r);
        return;
    }
    free(r);
    
    GHashTable *hashU = getHashTableU(users);
    GHashTable *hashR = getHashTableR(reservations);
    GHashTable *hashP = getHashTableP(passengers);
    GHashTable *hashF = getHashTableF(flights);

    char** str = NULL;

    switch(num_qry){
        case 1:
        {
            char* read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o ID pretendido: ");
            scanf("%s", read);
            char* ID = strdup(read);
            free(read);
           
            if(strlen(ID)>0 && strcmp(ID, "\"\"")!=0){
                str = query1 (hashU, hashF, hashR, hashP, ID, flag);
            }
            else{
                printLine("Invalid ID\n");
            }

            free(ID);
        }
        break;

        case 2:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o ID pretendido: ");
            scanf("%s", read);
            char* ID = strdup(read);  

            printLine("[Caso pretendas não inserir nada abre e fecha aspas -> ""]\nInsere o tipo pretendido: ");
            scanf("%s", read);
            char* type;
            if(strcmp(read, "\"\"")==0){
                type = strdup("");
            }
            else{
                type = strdup(read);
            }
            free(read);

            if(strlen(ID)>0 && strcmp(ID, "\"\"")!=0){
                str = query2(hashU, hashR, hashP, hashF, ID, type, flag);
            }
            else{
                printLine("Invalid ID\n");
            }

            free(ID);
            free(type);
        }   
        break;

        case 3:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o ID pretendido: ");
            scanf("%s", read);
            char* ID = strdup(read);
            free(read);
            
            if(strlen(ID)>0 && strcmp(ID, "\"\"") != 0 ){
                str = query3(hashR, ID, flag);
            }
            else{
                printLine("Invalid ID\n");
            }

            free(ID);
        }
        break;

        case 4:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o ID pretendido: ");
            scanf("%s", read);
            char* ID = strdup(read);
            free(read);
            
            if(strlen(ID)>0 && strcmp(ID, "\"\"") != 0 ){
                str = query4(hashR, ID, flag);
            }
            else{
                printLine("Invalid ID\n");
            }

            free(ID);
        }
        break;

        case 5:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o nome do aeroporto pretendido: ");
            scanf("%s", read);
            char *origin = strdup(read);

            printLine("Insere a data inicial pretendida: ");
            scanf("%s", read);
            char *arg1 = strdup(read);

            printLine("Insere a data final pretendida: ");
            scanf("%s", read);
            char *arg2 = strdup(read);

            DateClock* begin = preenche_data_hora(arg1);
            DateClock* end = preenche_data_hora(arg2);

            free(read);
            free(arg1);
            free(arg2);

            if(strlen(origin)>0 && strcmp(origin, "\"\"")!=0){
                if(begin){
                    if(end){
                        str = query5(hashF, origin , begin, end, flag);
                    }
                    else{
                        printLine("Data final inválida\n");
                    }
                }
                else{
                    printLine("Data inicial inválida\n");
                }
            }
            else{
                printLine("Nome do aeroporto inválido\n");
            }
            
            if(begin)
                free(begin);
            if(end)
                free(end);
            free(origin);
        }
        break;

        case 6:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o ano pretendido: ");
            scanf("%s", read);
            char *yearStr = strdup(read);

            printLine("Insere o tamanho do top pretendido: ");
            scanf("%s", read);
            char *topNStr = strdup(read);
            free(read);
            
            int year = atoi(yearStr);
            int topN = atoi(topNStr);
            free(yearStr);
            free(topNStr);

            if(year>0){
                if(topN>0){
                    str = query6(hashF, year, topN, flag);
                }
                else{
                    printLine("Tamanhi do top inválido\n");
                }
            }
            else{
                printLine("Ano inválido\n");
            }
        }
        break;

        case 7:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o tamanho do top pretendido: ");
            scanf("%s", read);
            char *topNStr = strdup(read);
            free(read);

            int topN = atoi(topNStr);
            free(topNStr);

            if(topN>0){
                str = query7 (hashF, topN, flag);
            }
            else{
                printLine("Tamanho do top inválido\n");
            }
        }
        break;

        case 8:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o ID do hotel pretendido: ");
            scanf("%s", read);
            char *hotel_id = strdup(read);

            printLine("Insere a data inicial pretendida: ");
            scanf("%s", read);
            char *arg1 = strdup(read);

            printLine("Insere a data final pretendida: ");
            scanf("%s", read);
            char *arg2 = strdup(read);
           
            DateClock* begin = preenche_data_hora(arg1);
            DateClock* end = preenche_data_hora(arg2);
            free(read);
            free(arg1);
            free(arg2);

            if(strlen(hotel_id)>0 && strcmp(hotel_id, "\"\"")!=0){
                if(begin){
                    if(end){
                        str = query8(hashR, hotel_id, begin, end, flag);
                    }
                    else{
                        printLine("Data final inválida\n");
                    }
                }
                else{
                    printLine("Data inicial inválida\n");
                }
            }
            else{
                printLine("ID do hotel inválido\n");
            }

            free(hotel_id);
            if (begin)
                free(begin);
            if (end)
                free(end);
        }
        break;

        case 9:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("Insere o prefixo pretendido: ");
            scanf("%s", read);
            char *prefix = strdup(read);
            free(read);
            
            if(strlen(prefix)>0 && strcmp(prefix, "\"\"")!=0){
                str = query9(hashU, prefix, flag);
            }
            else{
                printLine("Prefixo inválido\n");
            }

            free(prefix);
        }
        break;

        case 10:
        {
            char*read = malloc(sizeof(char)*STR_SIZE);

            printLine("[Caso pretendas não inserir nada abre e fecha aspas -> ""]\nInsere o ano pretendido: ");
            scanf("%s", read);
            char *YEAR;
            if(strcmp(read, "\"\"")==0){
                YEAR = strdup("");
            }
            else{
                YEAR = strdup(read);
            }

            printLine("[Caso pretendas não inserir nada abre e fecha aspas -> ""]\nInsere o mes pretendido: ");
            scanf("%s", read);
            char *MONTH;
            if(strcmp(read, "\"\"")==0){
                MONTH = strdup("");
            }
            else{
                MONTH = strdup(read);
            }
            free(read);

            str = query10(hashU, hashF, hashP, hashR, YEAR, MONTH, flag);

            free(YEAR);
            free(MONTH);
        }
        break;
    }

    page(str);
    if(str){
        for(int i=0; str[i]!=NULL; i++){
            printLine(str[i]);
            free(str[i]);
        }

        free(str);
    }
}

double q_tests (CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int num_qry, char *outputPath, char* args, int flag){
    GHashTable *hashU = getHashTableU(users);
    GHashTable *hashR = getHashTableR(reservations);
    GHashTable *hashP = getHashTableP(passengers);
    GHashTable *hashF = getHashTableF(flights);

    clock_t start, fim;
    double time_used;


    char** str = NULL;
    switch(num_qry){
        
        case 1:
        {
            char** argsArray = extractArgs(args, 1);
            char* ID = argsArray[0];

            if(strlen(ID)>0){
                start = clock();
                str = query1 (hashU, hashF, hashR, hashP, ID, flag);
                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;

            }

        
            freeArgs(argsArray, 1);
            
        }
        break;

        case 2:
        {
            char **argsArray = extractArgs(args, 2);
            char* ID = argsArray[0];
            char* type = argsArray[1];

            if(strlen(ID)>0){
                start = clock();
                str = query2(hashU, hashR, hashP, hashF, ID, type, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            freeArgs(argsArray, 2);
        }   
        break;

        case 3:
        {
            char** argsArray = extractArgs(args, 1);
            char *ID = argsArray[0];
            
            if(strlen(ID)>0){
                start = clock();
                str = query3(hashR, ID, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 4:
        {
            char** argsArray = extractArgs(args, 1);
            char *ID = argsArray[0];
            
            if(strlen(ID)>0){
                start = clock();
                str = query4(hashR, ID, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 5:
        {
            char** argsArray = extractArgs(args, 3);
            char *origin = argsArray[0];
            char *arg1 = argsArray[1];
            char *arg2 = argsArray[2];

            DateClock* begin = preenche_data_hora(arg1);
            DateClock* end = preenche_data_hora(arg2);

            if(strlen(origin)>0 && begin && end){
                start = clock();
                str = query5(hashF, origin , begin, end, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }
            
            if(begin)
                free(begin);
            if(end)
                free(end);
            freeArgs(argsArray, 3);
        }
        break;

        case 6:
        {
            char** argsArray = extractArgs(args, 2);
            char *yearStr = argsArray[0];
            char *topNStr = argsArray[1];

            int year = atoi(yearStr);
            int topN = atoi(topNStr);

            if(year>0 && topN>0){
                start = clock();
                str = query6(hashF, year, topN, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            freeArgs(argsArray, 2);
        }
        break;

        case 7:
        {
            char** argsArray = extractArgs(args, 1);
            char *topNStr = argsArray[0];

            int topN = atoi(topNStr);

            if(topN>0){
                start = clock();
                str = query7 (hashF, topN, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 8:
        {
            char** argsArray = extractArgs(args, 3);
            char *hotel_id = argsArray[0];
            char *arg1 = argsArray[1];
            char *arg2 = argsArray[2];

            DateClock* begin = preenche_data_hora(arg1);
            DateClock* end = preenche_data_hora(arg2);

            if(strlen(hotel_id)>0 && begin && end){
                start = clock();
                str = query8(hashR, hotel_id, begin, end, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            if (begin)
                free(begin);
            if (end)
                free(end);
            freeArgs(argsArray, 3);
        }
        break;

        case 9:
        {
            char** argsArray = extractArgs(args, 1);
            char *prefix = argsArray[0];
            
            if(strlen(prefix)>0){
                start = clock();
                str = query9(hashU, prefix, flag);

                fim = clock();
                time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;
            }

            freeArgs(argsArray, 1);
        }
        break;

        case 10:
        {
            char** argsArray = extractArgs(args, 2);
            char *YEAR = argsArray[0];
            char *MONTH = argsArray[1];

            start = clock();

            str = query10(hashU, hashF, hashP, hashR, YEAR, MONTH, flag);

            fim = clock();
            time_used = ((double) (fim - start)) / CLOCKS_PER_SEC;

            freeArgs(argsArray, 2);
        }
        break;
    }
    
    printArrayToFile(str, outputPath);

    for(int i=0; str[i]!=NULL; i++){
        free(str[i]);
    }
    if(str)
        free(str);

    return time_used;
}