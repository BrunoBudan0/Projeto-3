#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_admin.h" 

// arquivo moedas

int salvar_moedas(const Criptomoeda *moeda) {
    FILE *arquivo = fopen("moedas.dat", "ab"); 
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    fwrite(moeda, sizeof(Criptomoeda), 1, arquivo); // Escreve a estrutura completa

    fclose(arquivo);
    return 0;
}

int ler_moedas() {
    FILE *arquivo = fopen("moedas.dat", "rb"); // Arquivo binário, modo leitura
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    Criptomoeda moeda;
    while (fread(&moeda, sizeof(Criptomoeda), 1, arquivo) > 0) {
        // printf("Nome: %s\n", moeda.nome);
        // printf("Cotacao: %.2lf\n", moeda.cota);
        // printf("Taxa de Compra: %.2f\n", moeda.taxa_c);
        // printf("Taxa de Venda: %.2f\n", moeda.taxa_v);
        // printf("\n");
    }

    fclose(arquivo);
    return 0;
}



// arquivo moedas

void criarAdmin(Admin admins[]) {
    strcpy(admins[0].cpf, "12345678901");
    admins[0].senha = 111;
    strcpy(admins[0].nome, "Gabriel");

    strcpy(admins[1].cpf, "12345678902");
    admins[1].senha = 222;
    strcpy(admins[1].nome, "Bruno");

    strcpy(admins[2].cpf, "12345678903");
    admins[2].senha = 333;
    strcpy(admins[2].nome, "Daniel");

}

int menu_admin(){
    printf("\n");
    printf("1. Cadastrar Investidor\n");
    printf("2. Excluir Investidor\n");
    printf("3. Cadastrar Criptomoeda\n");
    printf("4. Excluir Criptomoeda\n");
    printf("5. Atualizar Cotacao\n");
    printf("6. Sair\n");
    printf("\n");

    return 0;
}

int cadastrar_invest() {
    printf("cadastrar investidor\n");
    return 0;
}

int exc_invest() {
    printf("excluir investidor\n");
    return 0;
}


int cadastrar_cripto() {
    Criptomoeda moeda;

    printf("Cadastrar Cripto:\n");

    printf("Digite o nome da moeda: ");
    scanf("%s", moeda.nome);

    printf("Digite a cotacao da moeda: ");
    scanf("%lf", &moeda.cota);

    printf("Digite a taxa de compra da moeda: ");
    scanf("%f", &moeda.taxa_c); 

    printf("Digite a taxa de venda da moeda: ");
    scanf("%f", &moeda.taxa_v); 

    salvar_moedas(&moeda);
    return 0;
}



int exc_cripto() {
    printf("\nExcluir Cripto:\n");
    // char moeda_exc[255];
    // Criptomoeda moeda;
    // printf("Digite o nome da moeda que deseja excluir:");
    // scanf("%s", moeda_exc);
    
    // while (strcmp(moeda_exc) == moeda.nome){
    //     printf("Nome: %s\n", moeda.nome);
    //     printf("Cotacao: %.2lf\n", moeda.cota);
    //     printf("Taxa de Compra: %.2f\n", moeda.taxa_c);
    //     printf("Taxa de Venda: %.2f\n", moeda.taxa_v);
    //     printf("\n");
    // }

    // return 0;
}

int atualizar_cota() {
    printf("atualizar cotacao\n");
    ler_moedas();
    return 0;
}