#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "funcoes_admin.h"

int main(void) {
    char cpf[12];
    int senha;
    int esc;

    Adm adms[3];
    criarAdmin(adms);

    // Nome do arquivo único para investidores
    const char *arquivo_investidores = "investidores.bin";

    printf("Seja bem vindo! Insira seu CPF e sua senha para realizar o login.\n");

    while (1) {
        printf("CPF: ");
        scanf("%s", cpf);
        printf("Senha: ");
        scanf("%d", &senha);  
        printf("\n");

        int adm_autenticado = -1;

        // Verifica login nos 3 administradores cadastrados
        for (int i = 0; i < 3; i++) {  // Corrigido de 10 para 3
            if (strcmp(adms[i].cpf, cpf) == 0 && adms[i].senha == senha) {
                adm_autenticado = i;
                break;
            }
        }

        if (adm_autenticado != -1) {
            printf("Acesso permitido!\n");

            while (1) {
                menu1_admin();  // Corrigido para o nome correto
                printf("Escolha uma opcao: ");
                scanf("%d", &esc);
                printf("\n");

                if (esc < 1 || esc > 8) {
                    printf("Escolha uma opcao valida!\n");
                } else {
                    if (esc == 1) { 
                        cadastrar_investidor(arquivo_investidores); 
                    } else if (esc == 2) { 
                        excluir_investidor(arquivo_investidores); 
                    } else if (esc == 3) { 
                        printf("Cadastrar Cripto\n");
                    } else if (esc == 4) { 
                        printf("Excluir Cripto\n");
                    } else if (esc == 5) { 
                        consultar_investidores(arquivo_investidores); 
                    } else if (esc == 6) { 
                        printf("Consultar Extrato.\n");
                    } else if (esc == 7) { 
                        printf("Atualizar Cotacao\n");
                    } else if (esc == 8) { 
                        printf("Encerrando...\n");
                        return 0; 
                    }
                }
            }

        } else {
            printf("CPF ou senha incorretos, tente novamente ou pressione CTRL + C para sair!\n");
        }
    }

    return 0;
}
