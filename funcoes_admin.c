#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_admin.h" 

void criarAdmin(Adm adms[]){
    strcpy(adms[0].cpf, "12345678901");
    adms[0].senha = 111;
    strcpy(adms[0].nome, "Gabriel");
    strcpy(adms[0].nome_arquivo, "01_G.bin");

    strcpy(adms[1].cpf, "12345678902");
    adms[1].senha = 222;
    strcpy(adms[1].nome, "Bruno");
    strcpy(adms[1].nome_arquivo, "02_B.bin");


    strcpy(adms[2].cpf, "12345678903");
    adms[2].senha = 333;
    strcpy(adms[2].nome, "Daniel");
    strcpy(adms[2].nome_arquivo, "03_D.bin");
};

void menu1_admin() { 
    printf("\n");
    printf("1. Cadastrar Novo Investidor\n");
    printf("2. Excluir Investidor\n");
    printf("3. Cadastrar Criptomoeda\n");
    printf("4. Excluir Criptomoeda\n");
    printf("5. Consultar Saldo de Investidor\n");
    printf("6. Consultar Extrato de Investidor\n");
    printf("7. Atualizar cotacao\n");
    printf("8. Sair\n");
    printf("\n");
}

void cadastrar_investidor(const char *arquivo_investidores) {
    Investidor novo;
    FILE *arquivo = fopen(arquivo_investidores, "ab"); // Abre o arquivo para adicionar
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome); // Lê o nome do investidor
    printf("CPF: ");
    scanf("%s", novo.cpf);
    printf("Saldo inicial: ");
    scanf("%f", &novo.saldo);

    fwrite(&novo, sizeof(Investidor), 1, arquivo); // Escreve o investidor no arquivo
    fclose(arquivo);

    printf("Investidor cadastrado com sucesso!\n");
}

void excluir_investidor(const char *arquivo_investidores) {
    char cpf[12];
    printf("Digite o CPF do investidor que deseja excluir: ");
    scanf("%s", cpf);

    FILE *arquivo = fopen(arquivo_investidores, "rb");
    FILE *temp = fopen("temp.bin", "wb"); // Arquivo temporário
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Investidor investidor;
    bool encontrado = false;

    // Lê todos os registros e copia os que não correspondem ao CPF
    while (fread(&investidor, sizeof(Investidor), 1, arquivo)) {
        if (strcmp(investidor.cpf, cpf) != 0) {
            fwrite(&investidor, sizeof(Investidor), 1, temp);
        } else {
            encontrado = true;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(arquivo_investidores); // Remove o arquivo original
    rename("temp.bin", arquivo_investidores); // Renomeia o temporário

    if (encontrado) {
        printf("Investidor excluído com sucesso!\n");
    } else {
        printf("CPF não encontrado!\n");
    }
}

void consultarSaldoInvestidores(const char *arquivo_investidores) {
    FILE *arquivo = fopen(arquivo_investidores, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s!\n", arquivo_investidores);
        return;
    }

    Usuario investidor;
    printf("Saldo de todos os investidores:\n");
    printf("----------------------------------------------------\n");

    while (fread(&investidor, sizeof(Usuario), 1, arquivo)) {
        printf("Nome: %s\n", investidor.nome);
        printf("CPF: %s\n", investidor.cpf);
        printf("Saldo em Reais: %.2f\n", investidor.saldo);
        printf("Bitcoin: %.2f\n", investidor.bitcoin);
        printf("Ethereum: %.2f\n", investidor.ethereum);
        printf("Ripple: %.2f\n", investidor.ripple);
        printf("----------------------------------------------------\n");
    }

    fclose(arquivo);
}


void consultarExtratoInvestidor(const Usuario *investidor) {
    printf("Extrato do investidor %s (CPF: %s):\n", investidor->nome, investidor->cpf);
    for (int i = 0; i < investidor->num_strings; i++) {
        printf("%s\n", investidor->extrato[i]);
    }
}