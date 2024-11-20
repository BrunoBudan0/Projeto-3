#define FUNCOESADMIN_H  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ADMIN

#define MAX_CRIPTOS 10

typedef struct {
    char nome[50];
    char cpf[12];
    char senha[20];
    float saldo; // Saldo em reais
    int num_criptos; // Número de criptomoedas possuídas
    struct {
        char nome[20];    // Nome da criptomoeda
        float quantidade; // Quantidade possuída
    } criptos[10];
} Investidor;


typedef struct {
    char cpf[10];
    int senha;
    char nome[50];
    char nome_arquivo[12];
} Adm;

typedef struct {
    char cpf[12];
    int senha;
    char nome[50];
    float saldo; 
} Usuario;

void menu1_admin();

void criarAdmin(Adm adms[]);

void criarAdmin(Adm adms[]);

void cadastrar_investidor(const char *arquivo_investidores);

void excluir_investidor(const char *arquivo_investidores);

void consultar_saldo(const char *arquivo_investidores);

void consultar_extrato(const char *arquivo_investidores);

void listar_investidores(const char *arquivo_investidores);

int carregarUsuarios(const char *arquivo_investidores, Usuario usuarios[]);

int cadastrar_cripto(); 

int exc_cripto();

int atualizar_cota();


// arquivo moedas

typedef struct {
    char nome[255];
    double cota;
    float taxa_c;
    float taxa_v;
} Criptomoeda;

int salvar_moedas(const Criptomoeda *moeda);
int ler_moedas();

// arquivo moedas
