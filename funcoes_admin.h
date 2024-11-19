#define FUNCOESADMIN_H  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ADMIN

int menu_admin();

typedef struct {
    char cpf[10];
    int senha;
    char nome[50];
} Admin;

void criarAdmin(Admin admins[]);

int cadastrar_invest();

int exc_invest(); 

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