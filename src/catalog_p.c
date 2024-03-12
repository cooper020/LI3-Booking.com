#include "../include/catalog_p.h"
#include "../include/parser.h"

//Struct que define a hashtable
typedef struct hash3 {
    GHashTable *cat_passernger;
} CatalogoPassenger;

GHashTable *getHashTableP(CatalogoPassenger* cat){
    return cat->cat_passernger;
}

//Insere a estrutura USERS com as informações de uma linha na tabela hash, usando o ID do passenger como chave
void insert_CatalogoPassenger(char *line, CatalogoPassenger *hashP, CatalogoFlight *cat_flight, CatalogoUser *cat_user) {
    char* line_dup = strdup(line);
    PASSENGERS p = initPassengerFromLine(line, getHashTableF(cat_flight), getHashTableU(cat_user));
    if (p == NULL) {
        free(line_dup); 
        return;
    }

    if (!g_hash_table_contains(hashP->cat_passernger, line_dup)) {
        g_hash_table_insert(hashP->cat_passernger, line_dup, p);
    } else {
        free(line_dup); 
    }
}

//Criar uma tabela de hash a partir de um arquivo .csv
CatalogoPassenger *create_CatalogoPassenger(char *pathP, CatalogoFlight *cat_flight, CatalogoUser *cat_user) {
    CatalogoPassenger *new = malloc(sizeof(CatalogoPassenger));
    if (new == NULL) {
        printLine("Erro na alocação de memória para CatalogoPassenger.\n");
        return NULL;
    }

    new->cat_passernger = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_passenger_void);
    
    if (new->cat_passernger == NULL) {
        printLine("Erro na alocação de memória para a tabela hash.\n");
        free(new);
        return NULL;
    }

    parser_Passengers(pathP, new, cat_flight, cat_user);

    return new;
}

//Dá free à hashtable para não ficar em memória
void free_CatalogoPassenger(CatalogoPassenger *hashP){
    if (hashP != NULL) {
        g_hash_table_destroy(hashP->cat_passernger);
        free(hashP);
    }
}
