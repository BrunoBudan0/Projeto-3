#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "funcoes_admin.h"

#define MAX_USUARIOS 100

int main(void) {
    char cpf[12];
    int senha;
    int esc;

    Adm adms[3];
    criarAdmin(adms);
    

    Usuario usuarios[MAX_USUARIOS];
    const char *arquivo_investidores = "investidores.bin";

    FILE *teste_arquivo = fopen(arquivo_investidores, "rb");
    if (!teste_arquivo) {
        inicializarUsuarios(arquivo_investidores);
        printf("Arquivo de investidores inicializado.\n");
    } else {
        fclose(teste_arquivo);
    }

    
    // Carregar usuários do arquivo
    int num_usuarios = carregarUsuarios(arquivo_investidores, usuarios);

    printf("Seja bem-vindo! Insira seu CPF e sua senha para realizar o login.\n");

    while (1) {
        printf("CPF: ");
        scanf("%s", cpf);
        printf("Senha: ");
        scanf("%d", &senha);
        printf("\n");

        int adm_autenticado = -1;

        // Verifica login dos administradores
        for (int i = 0; i < 3; i++) {
            if (strcmp(adms[i].cpf, cpf) == 0 && adms[i].senha == senha) {
                adm_autenticado = i;
                break;
            }
        }

        if (adm_autenticado != -1) {
            printf("Acesso permitido, %s!\n", adms[adm_autenticado].nome);

            while (1) {
                menu1_admin();
                printf("Escolha uma opcao: ");
                scanf("%d", &esc);
                printf("\n");

                if (esc < 1 || esc > 8) {
                    printf("Escolha uma opcao valida!\n");
                } else if (esc == 1) {
                    cadastrar_investidor(arquivo_investidores);
                    num_usuarios = carregarUsuarios(arquivo_investidores, usuarios); // Atualiza usuários
                } else if (esc == 2) {
                    excluir_investidor(arquivo_investidores);
                    num_usuarios = carregarUsuarios(arquivo_investidores, usuarios); // Atualiza usuários
                } else if (esc == 3) {
                    printf("Funcionalidade: Cadastrar Cripto.\n");
                } else if (esc == 4) {
                    printf("Funcionalidade: Excluir Cripto.\n");
                } else if (esc == 5) {
                    consultarSaldoInvestidores(arquivo_investidores); // Mostra saldo de todos os investidores
                } else if (esc == 6) {
                    printf("Digite o CPF do investidor para consultar o extrato: ");
                    scanf("%s", cpf);

                    int investidor_encontrado = -1;
                    for (int i = 0; i < num_usuarios; i++) {
                        if (strcmp(usuarios[i].cpf, cpf) == 0) {
                            investidor_encontrado = i;
                            break;
                        }
                    }

                    if (investidor_encontrado != -1) {
                        consultarExtratoInvestidor(&usuarios[investidor_encontrado]);
                    } else {
                        printf("Investidor com CPF %s não encontrado.\n", cpf);
                    }
                } else if (esc == 7) {
                    printf("Funcionalidade: Atualizar Cotacao.\n");
                } else if (esc == 8) {
                    printf("Encerrando...\n");
                    return 0;
                }
            }
        } else {
            printf("CPF ou senha incorretos, tente novamente ou pressione CTRL + C para sair!\n");
        }
    }

    return 0;
}
