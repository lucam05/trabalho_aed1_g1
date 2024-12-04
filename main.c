#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas de Dados
typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int fidelidade; // 0 = Não, 1 = Sim
    int pontos;
} Passageiro;

typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
    char cargo[20]; // Piloto, Copiloto, Comissário
} Tripulante;

typedef struct {
    int codigo;
    char data[11];
    char hora[6];
    char origem[50];
    char destino[50];
    char aviao[20];
    int piloto;
    int copiloto;
    int status; // 0 = Inativo, 1 = Ativo
    float tarifa;
} Voo;

typedef struct {
    int numero;
    int codigo_voo;
    int status; // 0 = Livre, 1 = Ocupado
} Assento;

typedef struct {
    int codigo_voo;
    int numero_assento;
    int codigo_passageiro;
} Reserva;

// Funções de Utilidade
void menu();
void cadastrarPassageiro();
void cadastrarTripulacao();
void cadastrarVoo();
void cadastrarAssento();
void realizarReserva();
void baixaReserva();
void pesquisar();
void programaFidelidade();
int gerarCodigo(const char *arquivo);

// Funções de Arquivo
void salvarArquivo(const char *nomeArquivo, void *registro, size_t tamanho);
int verificarCodigo(const char *nomeArquivo, int codigo, size_t tamanho);

// Main
int main() {
    int opcao;
    do {
        menu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer de entrada
        switch (opcao) {
            case 1: cadastrarPassageiro(); break;
            case 2: cadastrarTripulacao(); break;
            case 3: cadastrarVoo(); break;
            case 4: cadastrarAssento(); break;
            case 5: realizarReserva(); break;
            case 6: baixaReserva(); break;
            case 7: pesquisar(); break;
            case 8: programaFidelidade(); break;
            case 9: printf("\nSaindo do sistema...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 9);
    return 0;
}

// Implementação de Funções
void menu() {
    printf("\n========== MENU ==========");
    printf("\n1. Cadastrar Passageiro");
    printf("\n2. Cadastrar Tripulacao");
    printf("\n3. Cadastrar Voo");
    printf("\n4. Cadastrar Assento");
    printf("\n5. Realizar Reserva");
    printf("\n6. Baixa em Reserva");
    printf("\n7. Pesquisar");
    printf("\n8. Programa de Fidelidade");
    printf("\n9. Sair");
    printf("\n==========================\n");
}

void cadastrarPassageiro() {
    Passageiro p;
    p.codigo = gerarCodigo("passageiros.txt");
    printf("\nCadastro de Passageiro");
    printf("\nNome: ");
    fgets(p.nome, 50, stdin);
    strtok(p.nome, "\n");
    printf("Endereco: ");
    fgets(p.endereco, 100, stdin);
    strtok(p.endereco, "\n");
    printf("Telefone: ");
    fgets(p.telefone, 15, stdin);
    strtok(p.telefone, "\n");
    printf("Fidelidade (0 = Não, 1 = Sim): ");
    scanf("%d", &p.fidelidade);
    p.pontos = 0;

    salvarArquivo("passageiros.txt", &p, sizeof(Passageiro));
    printf("\nPassageiro cadastrado com sucesso!\n");
}

void cadastrarTripulacao() {
    Tripulante t;
    t.codigo = gerarCodigo("tripulacao.txt");
    printf("\nCadastro de Tripulação");
    printf("\nNome: ");
    fgets(t.nome, 50, stdin);
    strtok(t.nome, "\n");
    printf("Telefone: ");
    fgets(t.telefone, 15, stdin);
    strtok(t.telefone, "\n");
    printf("Cargo (Piloto, Copiloto, Comissario): ");
    fgets(t.cargo, 20, stdin);
    strtok(t.cargo, "\n");

    salvarArquivo("tripulacao.txt", &t, sizeof(Tripulante));
    printf("\nTripulação cadastrada com sucesso!\n");
}

void cadastrarVoo() {
    Voo v;
    v.codigo = gerarCodigo("voos.txt");
    printf("\nCadastro de Voo");
    printf("\nData (dd/mm/aaaa): ");
    fgets(v.data, 11, stdin);
    strtok(v.data, "\n");
    printf("Hora (hh:mm): ");
    fgets(v.hora, 6, stdin);
    strtok(v.hora, "\n");
    printf("Origem: ");
    fgets(v.origem, 50, stdin);
    strtok(v.origem, "\n");
    printf("Destino: ");
    fgets(v.destino, 50, stdin);
    strtok(v.destino, "\n");
    printf("Codigo do Piloto: ");
    scanf("%d", &v.piloto);
    printf("Codigo do Copiloto: ");
    scanf("%d", &v.copiloto);
    printf("Tarifa: ");
    scanf("%f", &v.tarifa);

    v.status = (v.piloto > 0 && v.copiloto > 0) ? 1 : 0;

    salvarArquivo("voos.txt", &v, sizeof(Voo));
    printf("\nVoo cadastrado com sucesso!\n");
}

void cadastrarAssento() {
    Assento a;
    printf("\nCadastro de Assento");
    printf("\nCodigo do Voo: ");
    scanf("%d", &a.codigo_voo);
    printf("Numero do Assento: ");
    scanf("%d", &a.numero);
    a.status = 0; // Livre

    salvarArquivo("assentos.txt", &a, sizeof(Assento));
    printf("\nAssento cadastrado com sucesso!\n");
}

void realizarReserva() {
    Reserva r;
    printf("\nRealizar Reserva");
    printf("\nCodigo do Voo: ");
    scanf("%d", &r.codigo_voo);
    printf("Numero do Assento: ");
    scanf("%d", &r.numero_assento);
    printf("Codigo do Passageiro: ");
    scanf("%d", &r.codigo_passageiro);

    // Validar se o assento está disponível
    FILE *file = fopen("assentos.txt", "rb+");
    Assento a;
    int encontrado = 0;
    while (fread(&a, sizeof(Assento), 1, file)) {
        if (a.codigo_voo == r.codigo_voo && a.numero == r.numero_assento) {
            if (a.status == 1) {
                printf("\nErro: Assento já reservado!\n");
                fclose(file);
                return;
            }
            a.status = 1; // Marcar como ocupado
            fseek(file, -sizeof(Assento), SEEK_CUR);
            fwrite(&a, sizeof(Assento), 1, file);
            encontrado = 1;
            break;
        }
    }
    fclose(file);

    if (!encontrado) {
        printf("\nErro: Assento não encontrado!\n");
        return;
    }

    salvarArquivo("reservas.txt", &r, sizeof(Reserva));
    printf("\nReserva realizada com sucesso!\n");
}

void baixaReserva() {
    // Similar à realização de reservas, mas liberando o assento
    printf("\nFuncionalidade não implementada completamente.\n");
}

void salvarArquivo(const char *nomeArquivo, void *registro, size_t tamanho) {
    FILE *file = fopen(nomeArquivo, "ab");
    if (!file) {
        printf("\nErro ao abrir arquivo!\n");
        return;
    }
    fwrite(registro, tamanho, 1, file);
    fclose(file);
}

int gerarCodigo(const char *arquivo) {
    FILE *file = fopen(arquivo, "rb");
    int ultimoCodigo = 0;
    if (file) {
        fseek(file, -sizeof(int), SEEK_END);
        fread(&ultimoCodigo, sizeof(int), 1, file);
        fclose(file);
    }
    return ultimoCodigo + 1;
}

void programaFidelidade() {
    FILE *file = fopen("passageiros.txt", "rb");
    if (!file) {
        printf("\nErro ao abrir arquivo de passageiros!\n");
        return;
    }

    Passageiro p;
    printf("\nPrograma de Fidelidade:");
    while (fread(&p, sizeof(Passageiro), 1, file)) {
        printf("\nCodigo: %d, Nome: %s, Pontos de Fidelidade: %d",
               p.codigo, p.nome, p.pontos);
    }
    fclose(file);
}
void pesquisar() {
    int opcao;
    printf("\nPesquisa:");
    printf("\n1. Passageiro");
    printf("\n2. Tripulante");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);
    getchar(); // Limpar buffer de entrada

    if (opcao == 1) {
        int codigo;
        char nome[50];
        printf("\nDigite o codigo do passageiro (ou -1 para ignorar): ");
        scanf("%d", &codigo);
        getchar();
        printf("Digite o nome do passageiro (ou deixe vazio para ignorar): ");
        fgets(nome, 50, stdin);
        strtok(nome, "\n");

        FILE *file = fopen("passageiros.txt", "rb");
        if (!file) {
            printf("\nErro ao abrir arquivo de passageiros!\n");
            return;
        }

        Passageiro p;
        int encontrado = 0;
        while (fread(&p, sizeof(Passageiro), 1, file)) {
            if ((codigo == -1 || p.codigo == codigo) &&
                (strlen(nome) == 0 || strstr(p.nome, nome) != NULL)) {
                printf("\nPassageiro encontrado:");
                printf("\nCodigo: %d, Nome: %s, Endereco: %s, Telefone: %s, Fidelidade: %d, Pontos: %d",
                       p.codigo, p.nome, p.endereco, p.telefone, p.fidelidade, p.pontos);
                encontrado = 1;
            }
        }
        fclose(file);
        if (!encontrado) {
            printf("\nNenhum passageiro encontrado.\n");
        }
    } else if (opcao == 2) {
        int codigo;
        char nome[50];
        printf("\nDigite o codigo do tripulante (ou -1 para ignorar): ");
        scanf("%d", &codigo);
        getchar();
        printf("Digite o nome do tripulante (ou deixe vazio para ignorar): ");
        fgets(nome, 50, stdin);
        strtok(nome, "\n");

        FILE *file = fopen("tripulacao.txt", "rb");
        if (!file) {
            printf("\nErro ao abrir arquivo de tripulantes!\n");
            return;
        }

        Tripulante t;
        int encontrado = 0;
        while (fread(&t, sizeof(Tripulante), 1, file)) {
            if ((codigo == -1 || t.codigo == codigo) &&
                (strlen(nome) == 0 || strstr(t.nome, nome) != NULL)) {
                printf("\nTripulante encontrado:");
                printf("\nCodigo: %d, Nome: %s, Telefone: %s, Cargo: %s",
                       t.codigo, t.nome, t.telefone, t.cargo);
                encontrado = 1;
            }
        }
        fclose(file);
        if (!encontrado) {
            printf("\nNenhum tripulante encontrado.\n");
        }
    } else {
        printf("\nOpcao invalida!\n");
    }
}
