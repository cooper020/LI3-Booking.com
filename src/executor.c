#include "../include/executor.h"

// corre as queries
void batch(char *input, CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers, int numargs){
    
    if(input){
        FILE* fp = NULL;
        fp = fopen(input, "r");
        if (!fp) {
            char *aux = malloc(STR_SIZE*sizeof(char));
            sprintf(aux, "Erro ao abrir o arquivo de input %s\n", input);
            printLine(aux);
            free(aux);
            return;
        }
        char* line = NULL;
        ssize_t read;
        size_t len=0;
        
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0, q5 = 0, q6 = 0, q7 = 0, q8 = 0, q9 = 0, q10 = 0;
        double *arrQ1 = NULL;
        double *arrQ2 = NULL;
        double *arrQ3 = NULL;
        double *arrQ4 = NULL;
        double *arrQ5 = NULL;
        double *arrQ6 = NULL;
        double *arrQ7 = NULL;
        double *arrQ8 = NULL;
        double *arrQ9 = NULL;
        double *arrQ10 = NULL;

        
        int commandNr = 1;
        while ((read = getline(&line, &len, fp)) != -1){
            if (!line[0] || line[0] == '\n')
                continue;

            char* line_copy = strdup(line);
            char* line_copy_start = line_copy;
            char* query = strsep(&line_copy, "\n");
            char* originalCommand = strdup(query); //MEM. LEAK
            query = strsep(&query, " ");
            
            int nquery = atoi(query);
            if(nquery <= 0 || nquery > 10){
                char* aux = malloc(STR_SIZE*sizeof(char));
                sprintf(aux, "Comando inválido: %s\n", originalCommand);
                printLine(aux);
                free(aux);
                free(line_copy_start);
                free(originalCommand);
                continue;
            }

            int flag;
            if (strstr(query, "F") != NULL) {
                flag = 0;
            }
            else{
                flag = 1;
            }
        
            char *args;
            if(strlen(query) == strlen(originalCommand)){
                args=strdup("");
            } else{
                args = strdup(originalCommand+strlen(query)+1);
            }

            char *outputPath = malloc(64*sizeof(char));
            sprintf(outputPath, "Resultados/command%d_output.txt", commandNr++);
            if(numargs == 3){
                queries(users, flights, reservations, passengers, nquery, outputPath, args, flag);
            } else {
                
                double timezzz = q_tests(users, flights, reservations, passengers, nquery, outputPath, args, flag);
                if(nquery == 1) {
                    q1++;
                    arrQ1 = realloc(arrQ1, (q1 + 1) * sizeof(double));
                    if(arrQ1 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ1[q1] = timezzz;
                }
                if(nquery == 2) {
                    q2++;
                    arrQ2 = realloc(arrQ2, (q2 + 1) * sizeof(double));
                    if(arrQ2 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ2[q2] = timezzz;
                }
                if(nquery == 3) {
                    q3++;
                    arrQ3 = realloc(arrQ3, (q3 + 1) * sizeof(double));
                    if(arrQ3 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ3[q3] = timezzz;
                }
                if(nquery == 4) {
                    q4++;
                    arrQ4 = realloc(arrQ4, (q4 + 1) * sizeof(double));
                    if(arrQ4 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ4[q4] = timezzz;
                }
                if(nquery == 5) {
                    q5++;
                    arrQ5 = realloc(arrQ5, (q5 + 1) * sizeof(double));
                    if(arrQ5 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ5[q5] = timezzz;
                }
                if(nquery == 6) {
                    q6++;
                    arrQ6 = realloc(arrQ6, (q6 + 1) * sizeof(double));
                    if(arrQ6 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ6[q6] = timezzz;
                }
                if(nquery == 7) {
                    q7++;
                    arrQ7 = realloc(arrQ7, (q7 + 1) * sizeof(double));
                    if(arrQ7 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ7[q7] = timezzz;
                }
                if(nquery == 8) {
                    q8++;
                    arrQ8 = realloc(arrQ8, (q8 + 1) * sizeof(double));
                    if(arrQ8 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ8[q8] = timezzz;
                }
                if(nquery == 9) {
                    q9++;
                    arrQ9 = realloc(arrQ9, (q9 + 1) * sizeof(double));
                    if(arrQ9 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ9[q9] = timezzz;
                }
                if(nquery == 10) {
                    q10++;
                    arrQ10 = realloc(arrQ10, (q10 + 1) * sizeof(double));
                    if(arrQ10 == NULL) {
                        printLine("Erro na alocação de memória\n");
                        return;
                    }
                    arrQ10[q10] = timezzz;
                }
            }
        
            

            free(line_copy_start);
            free(originalCommand);
            free(args);
            free(outputPath);
        }
        free(line);

            verificaArray(arrQ1, q1, 1); free(arrQ1);
            verificaArray(arrQ2, q2, 2); free(arrQ2);
            verificaArray(arrQ3, q3, 3); free(arrQ3);
            verificaArray(arrQ4, q4, 4); free(arrQ4);
            verificaArray(arrQ5, q5, 5); free(arrQ5);
            verificaArray(arrQ6, q6, 6); free(arrQ6);
            verificaArray(arrQ7, q7, 7); free(arrQ7);
            verificaArray(arrQ8, q8, 8); free(arrQ8);
            verificaArray(arrQ9, q9, 9); free(arrQ9);
            verificaArray(arrQ10, q10, 10); free(arrQ10);
    }
    else{
        printLine("Arquivo de input inexistente \n"); 
    }
}

char* path_input(char *argv[]){
    return argv[2];
}

char* folderFile(char* folder, char* file){
    char* path = malloc(strlen(folder) + strlen(file) + 2);// 1 do '/' e 1 do '\0'
    strcpy(path, folder);
    if (path[strlen(path) - 1] != '/') {
        strcat(path, "/");
    }
    strcat(path, file);

    return path;
}

void interative(CatalogoUser *users, CatalogoFlight *flights, CatalogoReservation *reservations, CatalogoPassenger *passengers){
    menuInits(users, flights, reservations, passengers);
}


void executor(int argc, char *argv[]){
    if (argc != 1 && argc != 3 && argc != 4) {
        printLine("Número de argumentos inválido.\n");
        return;
    }

    char* path_U = NULL;
    char* path_F = NULL;
    char* path_R = NULL;
    char* path_P = NULL;

    if(argc == 1){
        char* read = malloc(STR_SIZE*sizeof(char));
        printLine("Insere o caminho para a pasta com os ficheiros: ");
        scanf("%s", read);

        path_U = folderFile(read, "users.csv");
        path_F = folderFile(read, "flights.csv");
        path_R = folderFile(read, "reservations.csv");
        path_P = folderFile(read, "passengers.csv");

        free(read);
    }
    else{
        path_U = folderFile((char*)argv[1], "users.csv");
        path_F = folderFile((char*)argv[1], "flights.csv");
        path_R = folderFile((char*)argv[1], "reservations.csv");
        path_P = folderFile((char*)argv[1], "passengers.csv");
    }
    
    if(access(path_U, F_OK)==-1 || access(path_F, F_OK)==-1 || access(path_R, F_OK)==-1 || access(path_P, F_OK)==-1){
        printLine("Pelo menos um dos ficheiros necessários à execução do programa não existe.\n");
        return;
    }

    CatalogoUser *users = create_CatalogoUser(path_U);
    CatalogoFlight *flights = create_CatalogoFlight(path_F);
    CatalogoReservation *reservations = create_CatalogoReservation(path_R, users);
    CatalogoPassenger *passengers = create_CatalogoPassenger(path_P, flights, users);
    


    if(argc == 1){
        interative(users, flights, reservations, passengers);
    } else{

        char* inputFile = path_input(argv);
        batch(inputFile, users, flights, reservations, passengers, argc);
    }
    
    free_CatalogoUser(users);
    free_CatalogoFlight(flights);
    free_CatalogoReservation(reservations);
    free_CatalogoPassenger(passengers);
    
    free(path_U);
    free(path_F);
    free(path_R);
    free(path_P);

}

