#include "../include/catalog_u.h"
#include "../include/parser.h"


//Struct que define a hashtable
typedef struct hash1 {
    GHashTable *cat_user;
} CatalogoUser;


GHashTable *getHashTableU(CatalogoUser* cat){
    return cat->cat_user;
}

void insert_CatalogoUser( char *line, CatalogoUser *hashU) {
    USERS u = initUserFromLine(line);
        if (u == NULL) return;

    char *id = getIdU(u);
    if (id == NULL) {
        freeUser(u);
        return;
    }

    if (g_hash_table_contains(hashU->cat_user, id))
        free(id);
    else
        g_hash_table_insert(hashU->cat_user, id, u);
    
}

CatalogoUser *create_CatalogoUser(char *pathU) {
    CatalogoUser *new = malloc(sizeof(CatalogoUser));
    if (new == NULL) {
        printLine("Erro na alocação de memória para CatalogoUser.\n");
        return NULL;
    }
    

    new->cat_user = g_hash_table_new_full(g_str_hash,g_str_equal,g_free,free_user_void);
    
    if (new->cat_user == NULL) {
        printLine("Erro na alocação de memória para a tabela hash.\n");
        free(new);
        return NULL;
    }

    parser_Users(pathU, new);
    
    return new;
}

//Dá free à hashtable para não ficar em memória
void free_CatalogoUser(CatalogoUser *hashU){
    if (hashU != NULL) {
        g_hash_table_destroy(hashU->cat_user);
        free(hashU);
    }
}
