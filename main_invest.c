#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "funcoes_invest.h"

int main(void) {
    char cpf[12];
    int senha;
    int esc;

    const char *arquivo_investidores = "investidores.bin";
    Usuario usuarios[10];

    // Carregar usuários do arquivo
    int num_usuarios = carregarUsuarios(arquivo_investidores, usuarios);
    if (num_usuarios == 0) {
        printf("Arquivo de investidores não encontrado. Criando novos usuários...\n");
        criarUsuarios(arquivo_investidores);
        num_usuarios = carregarUsuarios(arquivo_investidores, usuarios);
    }

    printf("Seja bem-vindo, Investidor! Por favor, faça o login.\n");

    while (1) {
        printf("CPF: ");
        scanf("%s", cpf);
        printf("Senha: ");
        scanf("%d", &senha);
        printf("\n");

        int usuario_autenticado = -1;

        for (int i = 0; i < num_usuarios; i++) {
            printf("Comparando CPF: %s e senha: %d com %s e %d\n",
                   cpf, senha, usuarios[i].cpf, usuarios[i].senha);
            if (strcmp(usuarios[i].cpf, cpf) == 0 && usuarios[i].senha == senha) {
                usuario_autenticado = i;
                break;
            }
        }

        if (usuario_autenticado != -1) {
            printf("Acesso permitido! Bem-vindo(a), %s.\n", usuarios[usuario_autenticado].nome);

            // Menu principal após login
            while (1) {
                cripto criptos[3];
                menu();
                printf("Escolha uma opcao: ");
                scanf("%d", &esc);
                printf("\n");

                if (esc < 1 || esc > 8) {
                    printf("Escolha uma opcao valida!\n");
                } else {
                    if (esc == 1) {
                        consultar_saldo(usuarios[usuario_autenticado].nome, usuarios[usuario_autenticado].cpf);
                    } else if (esc == 2) {
                        consultar_extrato(num_strings, senha, usuarios[usuario_autenticado].nome, usuarios[usuario_autenticado].cpf);
                    } else if (esc == 3) {
                        depositar(&usuarios[usuario_autenticado].saldo, &num_strings, &bit, &eth, &rip);
                    } else if (esc == 4) {
                        sacar(senha, &usuarios[usuario_autenticado].saldo, &num_strings, &bit, &eth, &rip);
                    } else if (esc == 5) {
                        comprar_cripto(senha, &num_strings, &usuarios[usuario_autenticado].saldo, criptos);
                    } else if (esc == 6) {
                        vender_cripto(senha, &num_strings, &usuarios[usuario_autenticado].saldo, &bit, &eth, &rip, &cot_bit, &cot_eth, &cot_rip);
                    } else if (esc == 7) {
                        atualizar_cot(&cot_bit, &cot_eth, &cot_rip);
                    } else if (esc == 8) {
                        printf("Saindo...\n");
                        return 0;
                    }
                }
            }
        } else {
            printf("CPF ou senha incorretos. Tente novamente!\n");
        }
    }

    return 0;
}