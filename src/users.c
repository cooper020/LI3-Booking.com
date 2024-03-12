#include "../include/users.h"

struct users {
    char *id; //não pode ser vazio
    char *name; //não pode ser vazio
    char *email; //tem que ter o seguinte formato: “<username>@<domain>.<TLD>”.
    char *phone_number; //não pode ser vazio
    DateClock* birth_date; 
    char *sex; //não pode ser vazio
    char *passport; //não pode ser vazio
    char *country_code; //deverá ser formado por duas letras
    char *address; //não pode ser vazio
    DateClock* account_creation; // tem de ser depois de birth_date
    char *pay_method; //não pode ser vazio
    char *account_status; //“active” ou “inactive”, diferentes combinações de maiúsculas e minúsculas são válidas
};

USERS newUser() {
    USERS u = malloc(sizeof(struct users));
    if (u == NULL) {
        return NULL;
    }

    u->id = NULL;
    u->name = NULL;
    u->email = NULL;
    u->phone_number = NULL;
    u->birth_date = NULL;
    u->sex = NULL;
    u->passport = NULL;
    u->country_code = NULL;
    u->address = NULL;
    u->account_creation = NULL;
    u->pay_method = NULL;
    u->account_status = NULL;

    return u;
}

char ** takeLineU(char * line) {
    char **tokens = malloc(sizeof(char *) * 12);
    int i = 0;
    char * token = NULL;
    while ((token = strsep(&line, ";")) && i < 12) {
        tokens[i++] = token;
    }
    return tokens;
}

USERS initUserFromLine( char *line){
    if (line == NULL)
        return NULL;

    int valid = 1;
    char *line_dup = strdup(line);

    char ** tokens = takeLineU(line);
    
    USERS users = newUser();
    
    // Atribui os campos da estrutura users com os tokens
    users->id = strdup(tokens[0]);
    if (valida_notzero(users->id) != 0) {
        valid = 0;
    }
        
    users->name = strdup(tokens[1]);
    if (valida_notzero(users->name) != 0) {
        valid = 0; 
    }
    
    users->email = strdup(tokens[2]);
    if (valida_email(users->email) != 0) {
        valid = 0;
    }
    /*else{
        char* username = malloc(512);
        char* domain = malloc(512);
        char* tld = malloc(512);
        if (sscanf(users->email, "%s@%s.%s", username,domain,tld) != 3){
            valid = 0;
        }
        else if (strlen(username) < 1 || strlen(domain) < 1 || strlen(tld) < 2){
            valid = 0;
        }
        free(username);
        free(domain);
        free(tld);
    }*/
    
    users->phone_number = strdup(tokens[3]);
    if (valida_notzero(users->phone_number) != 0) {
        valid = 0; 
    }
    
    users->birth_date = preenche_data_hora(tokens[4]);
    // if (users->birth_date == NULL) { // é validado em baixo, não é preciso aqui
    //     valid = 0; 
    // }

    users->sex = strdup(tokens[5]); //MEM. LEAK
    if (strlen(users->sex) == 0) {
        valid = 0; 
    }
    
    users->passport = strdup(tokens[6]);
    if (valida_notzero(users->passport) != 0) {
        valid = 0; 
    }
    
    users->country_code = strdup(tokens[7]);
    if (users->country_code == NULL || strlen(users->country_code) != 2){
        valid = 0; 
    }else {
        for (int i = 0; i < 2; i++) {
            if (!isLetter(users->country_code[i])) {
                valid = 0; 
            }
        }
    }
    
    users->address = strdup(tokens[8]);
    if (valida_notzero(users->address) != 0) {
        valid = 0; 
    }
    
    users->account_creation = preenche_data_hora(tokens[9]);
    if (users->account_creation == NULL || users->birth_date == NULL || compareDateClock(users->birth_date, users->account_creation) >= 0) {
        valid = 0; 
    }
    
    users->pay_method = strdup(tokens[10]);
    if (valida_notzero(users->pay_method) != 0) {
        valid = 0; 
    }
    
    users->account_status = strdup(tokens[11]);
    if (users->account_status == NULL){
        valid = 0; 
    }
    else {
        char* a_s = toLowerCase(users->account_status);
        if (strcmp(a_s, "active") ==  0 ) {
            free(a_s);
            users->account_status = strdup("active");
        }
        else if (strcmp(a_s, "inactive") ==  0 ) {
            free(a_s);
            users->account_status = strdup("inactive");
        }
        else {
            valid = 0; 
        }
    }

    if (!valid) {
        char * aux = malloc(STR_SIZE*sizeof(char));
        strcpy(aux, line_dup);
        strcat(aux, "\n");
        apendStringToFile(aux, "Resultados/users_errors.csv");
        free(aux);
        freeUser(users);
        users = NULL;
    }

    free(line_dup);
    free(tokens); 
    return users;
}

////////// MÉTODOS GET //////////


char *getIdU (USERS u) {
    return strdup(u->id);
}

char *getNameU (USERS u) {
    return strdup(u->name);
}

char *getEmailU (USERS u) {
    return strdup(u->email);
}

char *getPhone_numberU (USERS u) {
    return strdup(u->phone_number);
}

DateClock *getBirth_dateU (USERS u) {
    return cloneDateClock(u->birth_date);
}

char *getSexU (USERS u) {
    return strdup(u->sex);
}

char *getPassportU (USERS u) {
    return strdup(u->passport);
}

char *getCountry_codeU (USERS u) {
    return strdup(u->country_code);
}

char *getAddressU (USERS u) {
    return strdup(u->address);
}

DateClock *getAccoutnt_creationU (USERS u) {
    return cloneDateClock(u->account_creation);
}

char *getPay_methodU (USERS u) {
    return strdup(u->pay_method);
}

char *getAccount_statusU (USERS u) {
    return strdup(u->account_status);
}


void freeUser(USERS users) {
    if (users) { //verifica se o pointer não é nulo
        if (users->id) free(users->id);
        if (users->name) free(users->name);
        if (users->email) free(users->email);
        if (users->phone_number) free(users->phone_number);
        if (users->sex) free(users->sex);
        if (users->birth_date) free_date(users->birth_date);
        if (users->passport) free(users->passport);
        if (users->country_code) free(users->country_code);
        if (users->address) free(users->address);
        if (users->account_creation) free_date(users->account_creation);
        if (users->pay_method) free(users->pay_method);
        if (users->account_status) free(users->account_status);
        free(users); // Liberta a strut inteira
    }
}

void free_user_void (gpointer users){
    freeUser(users);
}

int valida_email(char *email) {
    if (email == NULL) {
        return 1;
    }
    const char *arroba = strchr(email, '@');
    const char *ponto = strrchr(email, '.');

    // Verifica se '@' e '.' estão presentes e se há pelo menos um caractere entre eles
    if (arroba == NULL || ponto == NULL || arroba == email || arroba + 1 == ponto || ponto == email) {
        return 1; 
    }
    return 0; 
}

char* userToStringQuery1(USERS u, int flag, int nrFlights, int nrReservations, double totalSpent){
    if (u == NULL)
        return "NULL";

    char *str = malloc(sizeof(char) * STR_SIZE);
    int idade = calculaIdade(u->birth_date);
    if(flag == 0){
        sprintf(str, "--- 1 ---\nname: %s\nsex: %s\nage: %d\ncountry_code: %s\npassport: %s\nnumber_of_flights: %d\nnumber_of_reservations: %d\ntotal_spent: %.3f",
                    u->name, u->sex, idade, u->country_code, u->passport, nrFlights, nrReservations, totalSpent);
    }
    else{
        sprintf(str, "%s;%s;%d;%s;%s;%d;%d;%.3f", 
                    u->name, u->sex, idade, u->country_code, u->passport, nrFlights, nrReservations, totalSpent);
    }

    return str;
}

// tempo de execucao esta a ficar muito alto, tentativa com hash table iterator
int getNrFlights(USERS u, GHashTable *hashP){
    int nrFlights = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashP);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        PASSENGERS p = value;
        char *id = getUser_idP(p);
        if (strcmp(id, u->id) == 0) {
            nrFlights++;
        }
        free(id);
    }

    return nrFlights;
}

void getNrReservationsAndTotalSpent(USERS u, GHashTable *hashR, int *nR, double *tS){
    int nrReservations = 0;
    double totalSpent = 0;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, hashR);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        RESERVATIONS r = value;
        char *id = getUser_idR(r);
        if (strcmp(id, u->id) == 0) {
            nrReservations++;

            DateClock* beginDate = getBegin_dateR(r);
            DateClock* endDate = getEnd_dateR(r);
            double totalPrice = (double)getPrice_per_nightR(r) * (double)getNrNights(beginDate, endDate);
            totalPrice = totalPrice + (totalPrice/(double)100 * (double)getCity_taxR(r));

            totalSpent += totalPrice;

            free_date(beginDate);
            free_date(endDate);
        }
        free(id);
    }

    *nR = nrReservations;
    *tS = totalSpent;
}
