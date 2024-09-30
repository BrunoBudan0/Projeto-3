#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h" 

float bit = 0;
float eth = 0;
float rip = 0;
float real = 0;

#define MAX 100
#define LEN 200
char extrato[MAX][LEN];
int num_strings = 1;

int cot_bit = 5000;
int cot_eth = 2000;
int cot_rip = 500;

int menu(){
    printf("\n");
    printf("1. Consultar saldo\n");
    printf("2. Consultar extrato\n");
    printf("3. Depositar\n");
    printf("4. Sacar\n");
    printf("5. Comprar Criptomoedas\n");
    printf("6. Vender Criptomoedas\n");
    printf("7. Atualizar cotacao\n");
    printf("8. Sair\n");
    printf("\n");

    return 0;
}

int menu2(){
    puts("\n");
    printf("1.Bitcoin\n");
    printf("2.Ethereum\n");
    printf("3.Ripple\n");
    puts("\n");

    return 0;
}

// Função que cria os usuários e retorna o array de usuários
void criarUsuarios(Usuario usuarios[]) {
    strcpy(usuarios[0].cpf, "12345678901");
    usuarios[0].senha = 111;
    strcpy(usuarios[0].nome, "Gabriel");

    strcpy(usuarios[1].cpf, "12345678902");
    usuarios[1].senha = 222;
    strcpy(usuarios[1].nome, "Bruno");

    strcpy(usuarios[2].cpf, "12345678903");
    usuarios[2].senha = 333;
    strcpy(usuarios[2].nome, "Daniel");

    strcpy(usuarios[3].cpf, "12345678904");
    usuarios[3].senha = 444;
    strcpy(usuarios[3].nome, "Livia");

    strcpy(usuarios[4].cpf, "12345678905");
    usuarios[4].senha = 555;
    strcpy(usuarios[4].nome, "Julia");

    strcpy(usuarios[5].cpf, "12345678906");
    usuarios[5].senha = 666;
    strcpy(usuarios[5].nome, "Ana");

    strcpy(usuarios[6].cpf, "12345678907");
    usuarios[6].senha = 777;
    strcpy(usuarios[6].nome, "Ravi");

    strcpy(usuarios[7].cpf, "12345678908");
    usuarios[7].senha = 888;
    strcpy(usuarios[7].nome, "Sergio");

    strcpy(usuarios[8].cpf, "12345678909");
    usuarios[8].senha = 999;
    strcpy(usuarios[8].nome, "Catarina");

    strcpy(usuarios[9].cpf, "12345678910");
    usuarios[9].senha = 000;
    strcpy(usuarios[9].nome, "Mario");

}

int verificarUsuario(Usuario usuarios[], int quantidade, char cpf[], int senha) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && usuarios[i].senha == senha) {
            return 1; // Usuário encontrado e senha correta
        }
    }
    return 0; // Usuário não encontrado ou senha incorreta
}

void formatar_cpf(char cpf[], char cpf_formatado[]) {
    snprintf(cpf_formatado, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c",
             cpf[0], cpf[1], cpf[2], 
             cpf[3], cpf[4], cpf[5], 
             cpf[6], cpf[7], cpf[8], 
             cpf[9], cpf[10]);       
}

void formatar_hora(char* buffer, int len) {
    time_t tempoAtual;
    time(&tempoAtual);
    struct tm *tempoLocal = localtime(&tempoAtual);
    snprintf(buffer, len, "%02d/%02d/%04d %02d:%02d:%02d", 
             tempoLocal->tm_mday,
             tempoLocal->tm_mon + 1,
             tempoLocal->tm_year + 1900,
             tempoLocal->tm_hour,
             tempoLocal->tm_min,
             tempoLocal->tm_sec);
}

int extrato_fun(int *num_strings,char tipo, float valor, char moeda, double cota, float tx, float *real, float *bit, float *eth, float *rip) {
    int comp = *num_strings;
    if (comp < MAX) {
        char now[25];
        formatar_hora(now, sizeof(now));
        sprintf(extrato[comp], "%s %c %.2f %c CT: %.2f TX: %.2f REAL: %.2f BTC: %.2f ETH: %.2f XRP: %.2f", 
             now ,tipo, valor, moeda, cota, tx, *real, *bit, *eth, *rip);
        (*num_strings)++;
        return 0;
    } else {
        printf("Array cheio\n");
        return 0;
    }
}


void consultar_saldo(char nome[], char cpf[]){
    char cpf_formatado[15];  
    formatar_cpf(cpf, cpf_formatado);

    printf("Saldo de %s (CPF: %s):\n", nome, cpf_formatado); 
    printf("Bitcoin: %.2f\n", bit);
    printf("Ethereum: %.2f\n", eth);
    printf("Ripple: %.2f\n", rip);
    printf("Reais: %.2f\n", real);
}

int consultar_extrato(int num_strings){
    if (num_strings != 0){
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", extrato[i]);
        }
    }
    else{
        printf("Não há extrato");
    }

    return 0;
}

int depositar(float *real, int *num_strings, float *bit, float *eth, float *rip) {
    printf("Digite a quantidade a ser depositada(R$):");
    float valor;
    scanf("%f", &valor);
    
    if (valor > 0) {
        *real += valor;  // Adiciona o valor depositado ao real
        printf("Novo saldo: %.2f\n", *real);
        char tipo = '+';
        char moeda[5] = "REAL";
        int cota = 0.0;
        float tx = 0.0;
        puts("Transacao realizada com sucesso!");
        extrato_fun(num_strings, tipo,valor,*moeda,cota,tx, real, bit, eth, rip);
    } else {
        puts("Houve um erro! Digite um valor valido...");
    }
    // Implementar extrato... 
    return 0;
}

int sacar(int senha, float *real, int *num_strings, float *bit, float *eth, float *rip){

    printf("Digite sua senha: ");
    int senh;
    scanf("%d", &senh);
    if (senh == senha){
        printf("Digite a quantidade a sacar(R$):");

        float valor;
        scanf("%f", &valor);
        float veri = *real; // copia do real (valor para verificação)
        if (valor > 0 && veri - valor >= 0) {
            *real -= valor;  // subtrai o valor do real
            printf("Novo saldo: %.2f\n", *real);
            puts("Transacao realizada com sucesso!");
            char tipo = '-';
            char moeda[5] = "REAL";
            int cota = 0.0;
            float tx = 0.0;
            extrato_fun(num_strings, tipo,valor,*moeda,cota,tx, real, bit, eth, rip);
        } else {
            puts("Houve um erro!!!");
        }
        // Implementar extrato... 
    }
    else{
            puts("Senha incorreta!");
    }
}

int comprar_cripto(int senha, int *num_strings, float *real, float *bit, float *eth, float *rip, int *cot_bit, int *cot_eth, int *cot_rip){
    printf("Digite sua senha: ");

    int senh;
    scanf("%d", &senh);
    if (senh == senha){
        while(1){

            printf("Escolha uma opcao: ");
            menu2();
            int esc;
            scanf("%d", &esc);
            if (esc < 0 && esc > 4)
                puts("Opcao invalida...");
            else {
                // Colocar a quantidade da moeda ou a quantidade em reais?
                printf("Digite a quantidade:");

                float valor;
                scanf("%f", &valor);
                float veri = *real; // copia do real (valor para verificação)
                if (esc == 1){
                    if (valor > 0 && (veri - (valor * *cot_bit * 1.02)) >=0) {
                        *real -= (valor * *cot_bit * 1.02);
                        *bit += valor;  // Adiciona o valor depositado ao real
                        printf("Saldo Bitcoin: %.2f\n", *bit);
                        puts("Transacao realizada com sucesso!");
                        char tipo = '+';
                        char moeda[5] = "BTC";
                        float tx = 0.02;
                        extrato_fun(num_strings, tipo,valor,*moeda,*cot_bit,tx, real, bit, eth, rip);
                    } else {
                        puts("Houve um erro!!!");
                    }
                    // Implementar extrato... 
                    return 0;
                }
                else if (esc == 2) {
                        if (valor > 0 && (veri - (valor * *cot_eth * 1.01)) >=0) {
                        *real -= (valor * *cot_eth * 1.01);
                        *eth += valor;  // Adiciona o valor depositado ao real
                        printf("Saldo Ethereum: %.2f\n", *eth);
                        puts("Transacao realizada com sucesso!");
                        char tipo = '+';
                        char moeda[5] = "ETH";
                        float tx = 0.01;
                        extrato_fun(num_strings, tipo,valor,*moeda,*cot_eth,tx, real, bit, eth, rip);
                    } else {
                        puts("Houve um erro!!!");
                    }
                    // Implementar extrato... 
                    return 0;
                }
                else{
                    if (valor > 0 && (veri - (valor * *cot_rip * 1.01)) >=0) {
                        *real -= (valor * *cot_rip * 1.01);
                        *rip += valor;  // Adiciona o valor depositado ao real
                        printf("Saldo Ripple: %.2f\n", *rip);
                        puts("Transacao realizada com sucesso!");
                        char tipo = '+';
                        char moeda[5] = "RIP";
                        float tx = 0.01;
                        extrato_fun(num_strings, tipo,valor,*moeda,*cot_rip,tx, real, bit, eth, rip);
                    } else{
                        puts("Houve um erro!!!");
                    }
                    // Implementar extrato... 
                    return 0;
                }
            }
        }
    }
    else{
            puts("Senha incorreta!");
        }
}

int vender_cripto(int senha, int *num_strings ,float *real, float *bit, float *eth, float *rip, int *cot_bit, int *cot_eth, int *cot_rip){
    printf("Digite sua senha: ");
    int senh;
    scanf("%d", &senh);
    if (senh == senha){
        while(1){
            printf("Escolha uma opcao: ");
            menu2();
            int esc;
            scanf("%d", &esc);
            if (esc < 0 && esc > 4)
                puts("Opcao invalida...");
            else {
                // Colocar a quantidade da moeda ou a quantidade em reais?
                printf("Digite a quantidade:");
                float valor;
                scanf("%f", &valor);
                if (esc == 1){
                    float veri = *bit; // copia do bit (valor para verificação)
                    if (valor > 0 && (veri - valor) >=0) {
                        *real += (valor * *cot_bit * 0.97);
                        *bit -= valor; 
                        printf("Saldo Bitcoin: %.2f\n", *bit);
                        puts("Transacao realizada com sucesso!");
                        char tipo = '-';
                        char moeda[5] = "BTC";
                        double cota = *cot_bit;
                        float tx = 0.03;
                        extrato_fun(num_strings, tipo,valor,*moeda,*cot_bit,tx, real, bit, eth, rip);
                    } else {
                        puts("Houve um erro!!!");
                    }
                    // Implementar extrato... 
                    return 0;
                }
                else if (esc == 2) {
                    float veri = *eth; // copia do eth (valor para verificação)
                    if (valor > 0 && (veri - valor) >=0) {
                    *real += (valor * *cot_eth * 0.98);
                    *eth -= valor; 
                    printf("Saldo Ethereum: %.2f\n", *eth);
                    puts("Transacao realizada com sucesso!");
                    char tipo = '-';
                    char moeda[5] = "ETH";
                    double cota = *cot_eth;
                    float tx = 0.02;
                    extrato_fun(num_strings, tipo,valor,*moeda,*cot_eth,tx, real, bit, eth, rip);
                    } else {
                        puts("Houve um erro!!!");
                    }
                    // Implementar extrato... 
                    return 0;
                }
                else{
                    float veri = *rip; // copia do real (valor para verificação)
                    if (valor > 0 && (veri - valor) >=0) {
                        *real += (valor * *cot_rip * 0.99);
                        *rip -= valor;  
                        printf("Saldo Ripple: %.2f\n", *rip);
                        puts("Transacao realizada com sucesso!");
                        char tipo = '-';
                        char moeda[5] = "RIP";
                        double cota = *cot_rip;
                        float tx = 0.01;
                        extrato_fun(num_strings, tipo,valor,*moeda,*cot_rip,tx, real, bit, eth, rip);
                    } else{
                        puts("Houve um erro!!!");
                    }
                    // Implementar extrato... 
                    return 0;
                }
            }
        }
    }
    else{
            puts("Senha incorreta!");
        }
}

int atualizar_cot(int *cot_bit, int *cot_eth, int *cot_rip){

    srand(time(NULL));

    double cincobtc = *cot_bit * 0.05;
    double cincoeth = *cot_eth * 0.05;
    double cincorip = *cot_rip * 0.05;

    double limiteinfbtc = *cot_bit - cincobtc;
    double limitesupbtc = *cot_bit + cincobtc;

    double limiteinfeth = *cot_eth - cincoeth;
    double limitesupeth = *cot_eth + cincoeth;

    double limiteinfrip = *cot_rip - cincorip;
    double limitesuprip = *cot_rip + cincorip;

    double numAleatorioBTC = limitesupbtc - (rand()/(double)RAND_MAX)* (limitesupbtc - limiteinfbtc);
    printf("Cotação Bitcoin: %.2f\n", numAleatorioBTC);

    double numAleatorioETH = limitesupeth - (rand()/(double)RAND_MAX)* (limitesupeth - limiteinfeth);
    printf("Cotação Ethereum: %.2f\n", numAleatorioETH);

    double numAleatorioRIP = limitesuprip - (rand()/(double)RAND_MAX)* (limitesuprip - limiteinfrip);
    printf("Cotação Ripple:%.2f\n", numAleatorioRIP);

}