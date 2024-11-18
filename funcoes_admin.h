#define FUNCOES_H  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ADMIN

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
    float saldo; // Adicionando saldo diretamente aqui
} Usuario;

typedef struct {
    char nome[50];
    char cpf[12];
    char email[50];
    float saldo;
} Investidor;

void menu1_admin();

void criarAdmin(Adm adms[]);

void cadastrar_investidor(const char *arquivo_investidores);

void excluir_investidor(const char *arquivo_investidores);

void consultar_investidores(const char *arquivo_investidores);

int cadastrar_cripto(); 

int exc_cripto();

int carregarUsuarios(const char *arquivo_investidores, Usuario usuarios[]);
