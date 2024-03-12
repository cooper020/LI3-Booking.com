#include "../include/view.h"

void menuInicial () {
    printLine("--------------------------------------------------------\n");
    printLine("                       Bem-vindo!!                      \n");
    printLine("                                                        \n");
    printLine("                    Sistema de gestão                   \n");
    printLine("                    e consulta de voos                  \n");
    printLine("                        e reservas                      \n");
    printLine("                                                        \n");
    printLine("                Grupo 62 - LI3 2023/2024                \n");
    printLine("                                                        \n");
    printLine("--------------------------------------------------------\n");
    printLine("                                                        \n");
    printLine("               Pressione n para continuar!              \n");
    printLine("                 Pressione e para sair!                 \n");
    printLine("                                                        \n");
    printLine("--------------------------------------------------------\n");
}


void menuQueries () {
    printLine("\n                             ");
    printLine("\n Que query quer executar?");
    printLine("\n                             ");
    printLine("\n 1  | Listar o resumo de um utilizador, voo, ou reserva (consoante o identicador recebido por argumento).");
    printLine("\n 2  | Listar os voos ou reservas de um utilizador, ordenados por data (da mais recente para a mais antiga).");
    printLine("\n 3  | Apresentar a classicação média de um hotel (a partir do seu identicador).");
    printLine("\n 4  | Listar as reservas de um hotel, ordenadas por data de início (da mais recente para a mais antiga).");
    printLine("\n 5  | Listar os voos com origem num dado aeroporto, entre duas datas, ordenados por data de partida estimada (da mais recente para a mais antiga).");
    printLine("\n 6  | Listar o top N aeroportos com mais passageiros, para um dado ano.");
    printLine("\n 7  | Listar o top N aeroportos com a maior mediana de atrasos.");
    printLine("\n 8  | Apresentar a receita total de um hotel entre duas datas inclusive (a partir do seu identicador).");
    printLine("\n 9  | Listar todos os utilizadores cujo nome começa com o prefixo passado por argumento, ordenados por nome (de forma crescente).");
    printLine("\n 10 | Apresentar várias métricas gerais da aplicação.");
    printLine("\n 0  | Voltar\n");
    printLine("\n");
}                      

void page_aux(){
    printLine("---------------------------------------------------------------------------------------------\n");
    printLine("      [n] Next Page | [p] Previous Page | [f] First Page | [l] Last Page | [q] Quit        \n");
    printLine("---------------------------------------------------------------------------------------------\n");
}