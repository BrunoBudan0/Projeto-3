#define FUNCOES_H  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// INVEST

extern float bit;
extern float eth;
extern float rip;
extern float real;

#define MAX 100
#define LEN 200
extern char extrato[MAX][LEN];
extern int num_strings;

// atualização projeto 3
typedef struct {
    char nome[50]; //nome da moeda 
    float moeda; // valor
    float cota; // cotação
    double taxaV; // É possivel deixar os três em um só double?
    double taxaC;
} cripto;

// É interessante criar um 'struct' para as moedas? Aparentemente sim.
extern double cot_bit;
extern double cot_eth;
extern double cot_rip;

// funcoes_invest.h
typedef struct {
    char cpf[12];
    int senha;
    char nome[50];
    float saldo;
    float bitcoin;
    float ethereum;
    float ripple;
    char extrato[100][200]; // Ajuste conforme necessário
    int num_strings;
    cripto criptos[3]; // Array para armazenar as criptomoedas
} Usuario;




void criarMoedas(cripto criptos[]); 

int ler_arquivo(char nome_arquivo[],float *bit,float *eth, float *rip, float *real, double *cot_bit, double *cot_eth,double *cot_rip, char extrato[][LEN], int *num_strings);

int salvar_arquivo(char nome_arquivo[],float *bit,float *eth, float *rip, float *real, double *cot_bit, double *cot_eth,double *cot_rip, char extrato[][LEN], int *num_strings);

int carregarUsuarios(const char *arquivo_investidores, Usuario usuarios[]);

void inicializarUsuarios(const char *arquivo_investidores);

void salvarUsuarios(const char *arquivo_investidores, Usuario usuarios[], int num_usuarios);

int menu();

int menu2();

void consultar_saldo(char nome[], char cpf[], float saldo, float bitcoin, float ethereum, float ripple);

int consultar_extrato(int num_strings, int senha, char nome[], char cpf[]);

int depositar(float *real, int *num_strings, float *bit, float *eth, float *rip);

int sacar(int senha,float *real,int *num_strings, float *bit, float *eth, float *rip);

int comprar_cripto(int senha, int *num_strings, float *real, cripto criptos[]);

int vender_cripto(int senha,int *num_strings, float *real ,float *bit, float *eth, float *rip, double *cot_bit, double *cot_eth, double *cot_rip);

int atualizar_cot(double *cot_bit, double *cot_eth, double *cot_rip);