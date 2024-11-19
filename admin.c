#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "funcoes_admin.h"


int main(void) {
    char cpf[12];
    int senha;
    int esc;

    Admin admins[3]; // Array para armazenar os usuários
    criarAdmin(admins); // Populando o array com os usuários

    printf("Seja bem vindo, insira seu CPF e sua senha!\n");
    while(1) {    
        printf("CPF: ");
        scanf("%s", cpf);
        printf("Senha: ");
        scanf("%d", &senha);  

        printf("\n");
        int admin_autenticado = -1;
        for (int i = 0; i < 10; i++) {
            if (strcmp(admins[i].cpf, cpf) == 0 && admins[i].senha == senha) {
                admin_autenticado = i;
                break;
            }
        }
        if (admin_autenticado != -1) {
        printf("Acesso permitido!\n");
        // Loop para o menu após login bem-sucedido
        }
        while (1) {
            menu_admin();
            printf("Escolha uma opcao: ");
            scanf("%d", &esc);
            printf("\n");

            if (esc < 1 || esc > 7) {
                    printf("Escolha uma opcao valida!\n");
            } else {
                if (esc == 1) {cadastrar_invest();}
                else if (esc == 2) {exc_invest(); }
                else if (esc == 3) { cadastrar_cripto(); }
                else if (esc == 4) { exc_cripto();}
                else if (esc == 5) { atualizar_cota(); }
                else if (esc == 6) { return 0;}
            }
        }    
    }
    return 0;
}