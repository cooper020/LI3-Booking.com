#include "../include/catalog_f.h"
#include "../include/parser.h"

//Struct que define a hashtable
typedef struct hash2 {
    GHashTable *cat_flight;
} CatalogoFlight;

GHashTable *getHashTableF(CatalogoFlight* cat){
    return cat->cat_flight;
}

//Insere a estrutura FLIGHTS com as informações de uma linha na tabela hash, usando o ID do flight como chave
void insert_CatalogoFlight( char *line, CatalogoFlight *hashF) {
    FLIGHTS f = initFlightFromLine(line);
        if (f == NULL) return;

    char *id = getIdF(f);
    if (id == NULL) {
        freeFlight(f);
        return;
    }

    if (g_hash_table_contains(hashF->cat_flight, id))
        free(id);
    else
        g_hash_table_insert(hashF->cat_flight, id, f);
} 


//Criar uma tabela de hash a partir de um arquivo .csv
CatalogoFlight *create_CatalogoFlight(char *pathF) {
    CatalogoFlight *new = malloc(sizeof(CatalogoFlight));
    if (new == NULL) {
        printLine("Erro na alocação de memória para CatalogoFlight.\n");
        return NULL;
    }
    
    new->cat_flight = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_flight_void);
    
    if (new->cat_flight == NULL) {
        printLine("Erro na alocação de memória para a tabela hash.\n");
        free(new);
        return NULL;
    }
    
    parser_Flights(pathF, new);
    return new;
}

//Encontrar os dados de um flight na hashtable a partir da key 
FLIGHTS FindByKey_CatalogoFlight(CatalogoFlight *hashF, char *key){
    if (hashF == NULL || key == NULL || hashF->cat_flight == NULL || !g_hash_table_contains(hashF->cat_flight, key))
        return NULL;
    return g_hash_table_lookup(hashF->cat_flight, key);
}

void free_CatalogoFlight(CatalogoFlight *hashF){
    if (hashF != NULL) {
        if (hashF->cat_flight != NULL) {
            g_hash_table_destroy(hashF->cat_flight);
        }
        free(hashF);
    }
}

