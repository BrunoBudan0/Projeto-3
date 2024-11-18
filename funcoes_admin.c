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

void consultar_investidores(const char *arquivo_investidores) {
    FILE *arquivo = fopen(arquivo_investidores, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Investidor investidor;
    printf("Dados dos investidores:\n\n");
    while (fread(&investidor, sizeof(Investidor), 1, arquivo)) {
        printf("Nome: %s\n", investidor.nome);
        printf("CPF: %s\n", investidor.cpf);
        printf("Email: %s\n", investidor.email);
        printf("Saldo: %.2f\n", investidor.saldo);
        printf("----------------------------------\n");
    }

    fclose(arquivo);
}
