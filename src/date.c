#include "../include/date.h"

#define ANO 2023
#define MES 10
#define DIA 01

typedef struct datahora{
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
} DateClock;

int getDateClockDia (DateClock *dh){
    return dh->dia;
}

int getDateClockMes (DateClock *dh){
    return dh->mes;
}

int getDateClockAno (DateClock *dh){
    return dh->ano;
}

int getDateClockHora (DateClock *dh){
    return dh->hora;
}

int getDateClockMinuto (DateClock *dh){
    return dh->minuto;
}

int getDateClockSegundo (DateClock *dh){
    return dh->segundo;
}

void setTimeToZero(DateClock *dh){
    dh->hora = 0;
    dh->minuto = 0;
    dh->segundo = 0;
}

// função que faz um clone da datahora
DateClock *cloneDateClock (DateClock *dh){
    DateClock *clone = malloc(sizeof(struct datahora));
    clone->ano = dh->ano;
    clone->mes = dh->mes;
    clone->dia = dh->dia;
    clone->hora = dh->hora;
    clone->minuto = dh->minuto;
    clone->segundo = dh->segundo;
    return clone;
}

DateClock* preenche_data_hora(char *date) {
    // verificar se o tamanho da data está correto
    if (strlen(date) != 10 && strlen(date) != 19) 
        return NULL;
    
    // verificar se a sintaxe da data está no formato correto
    int year, month, day, hour, minute, second;
    // caso tenha não hora
    if (strlen(date) != 19 ){
        if (sscanf(date, "%d/%d/%d", &year, &month, &day) == 3 ){
            hour = 0;
            minute = 0;
            second = 0;
        }
        else
            return NULL;
    }
    else if (sscanf (date, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6)
        return NULL;

    // ...
    if ( year < 0 || month < 1 || month > 12 || day < 1 || day > 31 || 
            hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59 )
        return NULL;
    
    DateClock *new = malloc(sizeof(struct datahora)); 
    new->ano = year;
    new->mes = month;
    new->dia = day;
    new->hora = hour;
    new->minuto = minute;
    new->segundo = second;

    return new;
}

// função que passa do tipo DateClock para String
char *DateClockToString(DateClock *dh){
    char *str = malloc(sizeof(char) * 20); 
    sprintf(str, "%04d/%02d/%02d %02d:%02d:%02d", dh->ano, dh->mes, dh->dia, dh->hora, dh->minuto, dh->segundo);
    return str;
}

// dar free da data 
void free_date (DateClock *dh){
    free(dh);
}

void freeDateTime_void(gpointer data) {
    free_date((DateClock*)data);
}

// função que compara duas datas
// return 1 se d1 > d2, return -1 se d1 < d2, return 0 se d1 = d2
// Isto é a data maior é a data mais recente
int compareDateClock(DateClock *d1, DateClock *d2){
    if (d1 == NULL || d2 == NULL) {
        return 0;
    }

    int ano_data= getDateClockAno(d1);
    int ano_data2= getDateClockAno(d2);

    if (ano_data > ano_data2) 
        return 1;

    else if (ano_data < ano_data2) 
        return -1;

    else {
        int mes_data = getDateClockMes(d1);
        int mes_data2 = getDateClockMes(d2);
        if (mes_data > mes_data2) 
            return 1;
        else if (mes_data < mes_data2) 
            return -1;
        else {
            int dia_data = getDateClockDia(d1);
            int dia_data2 = getDateClockDia(d2);
            if (dia_data > dia_data2) 
                return 1;
            else if (dia_data < dia_data2) 
                return -1;
            else {
                int hora_data = getDateClockHora(d1);
                int hora_data2 = getDateClockHora(d2);
                if (hora_data > hora_data2) 
                    return 1;
                else if (hora_data < hora_data2) 
                    return -1;
                else {
                    int minuto_data = getDateClockMinuto(d1);
                    int minuto_data2 = getDateClockMinuto(d2);
                    if (minuto_data > minuto_data2) 
                        return 1;
                    else if (minuto_data < minuto_data2) 
                        return -1;
                    else {
                        int segundo_data = getDateClockSegundo(d1);
                        int segundo_data2 = getDateClockSegundo(d2);
                        if (segundo_data > segundo_data2) 
                            return 1;
                        else if (segundo_data < segundo_data2) 
                            return -1;
                        
                        else 
                            return 0;
                    }
                }
            }
        }
    }
}

// calcular tempo entre duas datas
int calculadif (DateClock *d1, DateClock *d2){
    // d1 < d2
    int r = compareDateClock(d1, d2);
    if (r == 0 ) // datas iguais
        return 0;
    if (r == 1) //d2 é mais antiga que d1
        return -1;
    
    int pre = 60 - getDateClockSegundo(d1);
    pre += (60 - (getDateClockMinuto(d1)+1)) * 60;
    pre += (24 - (getDateClockHora(d1)+1)) * 60 * 60;

    int dias = (getDateClockDia(d2)- getDateClockDia(d1)-1) * 24 * 60 * 60;
    
    int pos = getDateClockSegundo(d2);
    pos += getDateClockMinuto(d2) * 60;
    pos += getDateClockHora(d2) * 60 * 60;

    return pre + dias + pos;
}

DateClock* segToData (int seg){
    if(seg < 0)
        return NULL;

    DateClock *new = malloc(sizeof(struct datahora));
    int min = seg / 60;
    int hora = min / 60;
    int dia = hora / 24;
    //nao se ve o mes pelo o que o enunciado diz

    new -> ano = 0;
    new -> mes = 0;
    new -> dia = dia;
    new -> hora = hora - dia*24;
    new -> minuto = min - hora*60;  
    new -> segundo = seg - min*60;

    return new;
}

int getNrNights(DateClock *d1, DateClock *d2){
    // rever enuciao, ver se reservas podem ser em meses diferentes, subtrair só os dias um do outro ??
    d1 = cloneDateClock(d1);
    d2 = cloneDateClock(d2);
    d1->hora = d1->minuto = d1->segundo = 0;
    d2->hora = d2->minuto = d2->segundo = 0;

    DateClock* dif = segToData(calculadif(d1, d2));
    int nights = dif->dia;
    free_date(dif);
    free_date(d1);
    free_date(d2);

    return nights;
}

//função que recebe as datas de uma reserva e um periodo de tempo e devolve o numero de noites que a reserva tem dentro desse periodo
int contaNoites(DateClock *beginDateRes, DateClock *endDateRes, DateClock *begin, DateClock *end) {
    DateClock *aux = segToData(calculadif(beginDateRes, endDateRes));
    int diasTotal = aux->dia;
    free_date(aux);

    int noites = 0;
    DateClock *dataAtual = cloneDateClock(beginDateRes);

    for (int i = 0; i < diasTotal; i++) {
        if (compareDateClock(dataAtual, begin) >= 0 && compareDateClock(dataAtual, end) <= 0) {
            noites++;
        }

        dataAtual->dia++;
    }

    free_date(dataAtual);
    return noites;
}

int calculaIdade(DateClock *birth_date){
    DateClock *today = malloc(sizeof(struct datahora));
    today->ano = ANO;
    today->mes = MES;
    today->dia = DIA;
    today->hora = 0;
    today->minuto = 0;
    today->segundo = 0;

    int idade = ANO - getDateClockAno(birth_date);
    if (compareDateClock(today, birth_date) == -1)
        idade--;
    free_date(today);
    return idade;
}
