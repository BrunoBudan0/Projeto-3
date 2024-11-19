#ifndef FUNCOES_ADMIN_H
#define FUNCOES_H 
#include "funcoes_invest.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ADMIN

typedef struct {
    char cpf[10];
    int senha;
    char nome[50];
    char nome_arquivo[12];
} Adm;

void consultarSaldoInvestidores(const char *arquivo_investidores);
void consultarExtratoInvestidor(const Usuario *investidor);

typedef struct {
    char nome[50];
    char cpf[12];
    char email[50];
    float saldo;
} Investidor;

void menu1_admin();

void criarAdmin(Adm adms[]);

void cadastrar_investidor(const char *arquivo_investidores);

void excluir_investidor(const char *arquivo_investidores);

int cadastrar_cripto(); 

int exc_cripto();

#endif // FUNCOES_ADMIN_H
