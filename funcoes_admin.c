#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes_admin.h" 


int salvar_moedas(const Criptomoeda *moeda) {
    FILE *arquivo = fopen("moedas.dat", "ab"); 
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    fwrite(moeda, sizeof(Criptomoeda), 1, arquivo); 

    fclose(arquivo);
    return 0;
}

int ler_moedas() {
    FILE *arquivo = fopen("moedas.dat", "rb"); 
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    Criptomoeda moeda;
    while (fread(&moeda, sizeof(Criptomoeda), 1, arquivo) > 0) {
        printf("Nome: %s\n", moeda.nome);
        printf("Cotacao: %.2lf\n", moeda.cota);
        printf("Taxa de Compra: %.2f\n", moeda.taxa_c);
        printf("Taxa de Venda: %.2f\n", moeda.taxa_v);
        printf("\n");
    }

    fclose(arquivo);
    return 0;
}

int excluir_moeda(const char *nome_moeda) {
    FILE *arquivo_original = fopen("moedas.dat", "rb");
    FILE *arquivo_temp = fopen("moedas_temp.dat", "wb");
    if (!arquivo_original || !arquivo_temp) {
        perror("Erro ao abrir arquivo");
        if (arquivo_original) fclose(arquivo_original);
        if (arquivo_temp) fclose(arquivo_temp);
        return 1;
    }

    Criptomoeda moeda;
    int excluido = 0;
    int encontrado = 0;

    while (fread(&moeda, sizeof(Criptomoeda), 1, arquivo_original) > 0) {
        if (strcmp(moeda.nome, nome_moeda) == 0) {
            encontrado = 1;
            printf("Nome: %s\n", moeda.nome);
            printf("Cotacao: %.2lf\n", moeda.cota);
            printf("Taxa de Compra: %.2f\n", moeda.taxa_c);
            printf("Taxa de Venda: %.2f\n", moeda.taxa_v);

            char confirmacao;
            printf("Deseja realmente excluir esta moeda? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S') {
                excluido = 1;
                continue;
            } else {
                printf("Exclusao da criptomoeda '%s' cancelada.\n", nome_moeda);
            }
        }
        fwrite(&moeda, sizeof(Criptomoeda), 1, arquivo_temp);
    }

    fclose(arquivo_original);
    fclose(arquivo_temp);

    if (excluido) {
        remove("moedas.dat");
        rename("moedas_temp.dat", "moedas.dat");
        printf("Criptomoeda '%s' excluida com sucesso.\n", nome_moeda);
    } else {
        remove("moedas_temp.dat");
        if (!encontrado) {
            printf("Criptomoeda '%s' não encontrada.\n", nome_moeda);
        }
    }

    return 0;
}



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
}

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
    FILE *arquivo = fopen(arquivo_investidores, "ab");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo para cadastro");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("CPF: ");
    scanf("%s", novo.cpf);
    printf("Senha: ");
    scanf("%s", novo.senha);

    novo.num_criptos = 0; 
    novo.saldo = 0.0; 

    if (fwrite(&novo, sizeof(Investidor), 1, arquivo) != 1) {
        perror("Erro ao escrever no arquivo");
    } else {
        printf("Investidor cadastrado com sucesso!\n");
    }

    fclose(arquivo);
}


void excluir_investidor(const char *arquivo_investidores) {
    char cpf[12];
    printf("Digite o CPF do investidor que deseja excluir: ");
    scanf("%s", cpf);

    FILE *arquivo = fopen(arquivo_investidores, "rb");
    FILE *temp = fopen("temp.bin", "wb"); 
    if (!arquivo || !temp) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Investidor investidor;
    bool encontrado = false;

    while (fread(&investidor, sizeof(Investidor), 1, arquivo)) {
        if (strcmp(investidor.cpf, cpf) != 0) {
            fwrite(&investidor, sizeof(Investidor), 1, temp);
        } else {
            encontrado = true;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(arquivo_investidores); 
    rename("temp.bin", arquivo_investidores); 

    if (encontrado) {
        printf("Investidor excluído com sucesso!\n");
    } else {
        printf("CPF não encontrado!\n");
    }
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



void listar_investidores(const char *arquivo_investidores) {
    FILE *arquivo = fopen(arquivo_investidores, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s!\n", arquivo_investidores);
        return;
    }

    Investidor investidor;
    printf("\n--- Lista de Investidores ---\n");
    while (fread(&investidor, sizeof(Investidor), 1, arquivo)) {
        printf("Nome: %s | CPF: %s | Criptomoedas:\n", investidor.nome, investidor.cpf);
        if (investidor.num_criptos > 0) {
            for (int i = 0; i < investidor.num_criptos; i++) {
                printf("- %s: %.2f\n", 
                    investidor.criptos[i].nome, 
                    investidor.criptos[i].quantidade);
            }
        } else {
            printf("Nenhuma criptomoeda cadastrada.\n");
        }
        printf("\n");
    }
    printf("------------------------------\n");

    fclose(arquivo);
}

void consultar_saldo(const char *arquivo_investidores) {
    FILE *arquivo = fopen(arquivo_investidores, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s!\n", arquivo_investidores);
        return;
    }

    Investidor investidor;
    bool algum_registro = false;

    printf("\n--- Saldos de Todos os Investidores ---\n");
    while (fread(&investidor, sizeof(Investidor), 1, arquivo)) {
        printf("Nome: %s\n", investidor.nome);
        printf("Saldo em Reais: R$ %.2f\n", investidor.saldo);
        printf("Criptomoedas:\n");
        if (investidor.num_criptos > 0) {
            for (int i = 0; i < investidor.num_criptos; i++) {
                printf("- %s: %.2f\n", 
                    investidor.criptos[i].nome, 
                    investidor.criptos[i].quantidade);
            }
        } else {
            printf("Nenhuma criptomoeda cadastrada.\n");
        }
        printf("\n");
        algum_registro = true;
    }

    fclose(arquivo);

    if (!algum_registro) {
        printf("Nenhum investidor cadastrado no sistema.\n");
    }
    printf("---------------------------------------\n");
}

void consultar_extrato(const char *arquivo_investidores) {
    char cpf[12];
    printf("Digite o CPF do investidor que deseja consultar o extrato: ");
    scanf("%s", cpf);

    FILE *arquivo = fopen(arquivo_investidores, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s!\n", arquivo_investidores);
        return;
    }

    Investidor investidor;
    bool encontrado = false;

    while (fread(&investidor, sizeof(Investidor), 1, arquivo)) {
        if (strcmp(investidor.cpf, cpf) == 0) {
            encontrado = true;
            printf("\n--- Extrato do Investidor ---\n");
            printf("Nome: %s\n", investidor.nome);
            printf("CPF: %s\n", investidor.cpf);
            printf("Saldo em Reais: R$ %.2f\n", investidor.saldo);
            printf("Criptomoedas:\n");
            if (investidor.num_criptos > 0) {
                for (int i = 0; i < investidor.num_criptos; i++) {
                    printf("- %s: %.2f\n", 
                        investidor.criptos[i].nome, 
                        investidor.criptos[i].quantidade);
                }
            } else {
                printf("Nenhuma criptomoeda cadastrada.\n");
            }
            printf("------------------------------\n");
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Investidor com CPF %s não encontrado.\n", cpf);
    }
}

int carregarUsuarios(const char *arquivo_investidores, Usuario usuarios[]) {
    FILE *arquivo = fopen(arquivo_investidores, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s!\n", arquivo_investidores);
        return 0;
    }

    int count = 0;
    while (fread(&usuarios[count], sizeof(Usuario), 1, arquivo)) {
        count++;
    }

    fclose(arquivo);
    return count; 
}

int exc_cripto() {
    printf("\nExcluir Cripto:\n");

    char nome_moeda[255];
    printf("Digite o nome da moeda que deseja excluir: ");
    scanf("%s", nome_moeda);

    excluir_moeda(nome_moeda);

    ler_moedas();
    system("pause");

    return 0;
}

int atualizar_cota() {
    printf("Atualizando cotações das criptomoedas\n");

    FILE *arquivo = fopen("moedas.dat", "rb");
    FILE *arquivo_temp = fopen("moedas_temp.dat", "wb");

    if (!arquivo || !arquivo_temp) {
        perror("Erro ao abrir o arquivo");
        if (arquivo) fclose(arquivo);
        if (arquivo_temp) fclose(arquivo_temp);
        return 1;
    }

    Criptomoeda moeda;
    srand(time(NULL)); 

    while (fread(&moeda, sizeof(Criptomoeda), 1, arquivo) > 0) {
        double fator_aleatorio = 0.5 + ((rand() / (double)RAND_MAX) * 1.0);
        moeda.cota *= fator_aleatorio;

        printf("Nome: %s\n", moeda.nome);
        printf("Nova Cotação: %.2lf\n", moeda.cota);

        fwrite(&moeda, sizeof(Criptomoeda), 1, arquivo_temp);
    }

    fclose(arquivo);
    fclose(arquivo_temp);

    remove("moedas.dat"); 
    rename("moedas_temp.dat", "moedas.dat"); 

    printf("Cotações atualizadas com sucesso!\n");

    return 0;
}
