#include "../include/catalog_r.h"
#include "../include/parser.h"

//Struct que define a hashtable
typedef struct hash4 {
    GHashTable *cat_reservations;
} CatalogoReservation;

GHashTable *getHashTableR(CatalogoReservation* cat){
    return cat->cat_reservations;
}

//Insere a estrutura USERS com as informações de uma linha na tabela hash, usando o ID da reservation como chave
void insert_CatalogoReservation(char *line, CatalogoReservation *hashR, CatalogoUser *cat_user) {
    RESERVATIONS r = initReservationFromLine(line, getHashTableU(cat_user));
    if (r == NULL) return;

    char *id = getIdR(r);
    if (id == NULL) {
        freeReservation(r);
        return;
    }

    if (g_hash_table_contains(hashR->cat_reservations, id))
        free(id);
    else
        g_hash_table_insert(hashR->cat_reservations, id, r);
}


//Criar uma tabela de hash a partir de um arquivo .csv
CatalogoReservation *create_CatalogoReservation(char *pathR, CatalogoUser *cat_user) {
    CatalogoReservation *new = malloc(sizeof(CatalogoReservation));
    if (new == NULL) {
        printLine("Erro na alocação de memória para CatalogoReservation.\n");
        return NULL;
    }

    new->cat_reservations = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_reservation_void);
    
    if (new->cat_reservations == NULL) {
        printLine("Erro na alocação de memória para a tabela hash.\n");
        free(new);
        return NULL;
    }

    parser_Reservations(pathR, new, cat_user);

    return new;
}

//Encontrar os dados de uma reservation na hashtable a partir da key 
RESERVATIONS FindByKey_CatalogoReservation(CatalogoReservation *hashR, char *key){
    if (hashR == NULL || key == NULL || hashR->cat_reservations == NULL || !g_hash_table_contains(hashR->cat_reservations, key))
        return NULL;
    return g_hash_table_lookup(hashR->cat_reservations, key);
}

//Dá free à hashtable para não ficar em memória
void free_CatalogoReservation(CatalogoReservation *hashR){
    if (hashR != NULL) {
        g_hash_table_destroy(hashR->cat_reservations);
        free(hashR);
    }
}