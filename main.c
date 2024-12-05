#include <stdio.h>

typedef struct {
  int codigo;
  char nome[100];
  char endereco[200];
  char telefone[20];
  int fidelidade;
  int pontos_fidelidade;
} Passageiro;

typedef struct {
  int codigo;
  char nome[100];
  char telefone[20];
  char cargo[50];
  int experiencia;
} Tripulacao;

void salvar_passageiro(Passageiro *passageiro) {
  FILE *arquivo = fopen("passageiros.dat", "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de passageiros.\n");
    return;
  }
  fwrite(passageiro, sizeof(Passageiro), 1, arquivo);
  fclose(arquivo);
  printf("Passageiro salvo com sucesso!\n");
}

void salvar_tripulacao(Tripulacao *tripulacao) {
  FILE *arquivo = fopen("tripulacao.dat", "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de tripulação.\n");
    return;
  }
  fwrite(tripulacao, sizeof(Tripulacao), 1, arquivo);
  fclose(arquivo);
  printf("Tripulação salva com sucesso!\n");
}

void cadastrar_passageiro() {
  Passageiro passageiro;

  printf("Digite o código do passageiro: ");
  scanf("%d", &passageiro.codigo);
  getchar();

  printf("Digite o nome do passageiro: ");
  fgets(passageiro.nome, sizeof(passageiro.nome), stdin);
  passageiro.nome[strcspn(passageiro.nome, "\n")] = 0;

  printf("Digite o endereço do passageiro: ");
  fgets(passageiro.endereco, sizeof(passageiro.endereco), stdin);
  passageiro.endereco[strcspn(passageiro.endereco, "\n")] = 0;

  printf("Digite o telefone do passageiro: ");
  fgets(passageiro.telefone, sizeof(passageiro.telefone), stdin);
  passageiro.telefone[strcspn(passageiro.telefone, "\n")] = 0;

  printf("Passageiro é fidelidade? (1 para sim, 0 para não): ");
  scanf("%d", &passageiro.fidelidade);
  passageiro.pontos_fidelidade = 0;

  salvar_passageiro(&passageiro);
}

void cadastrar_tripulacao() {
  Tripulacao tripulacao;

  printf("Digite o código da tripulação: ");
  scanf("%d", &tripulacao.codigo);
  getchar();

  printf("Digite o nome da tripulação: ");
  fgets(tripulacao.nome, sizeof(tripulacao.nome), stdin);
  tripulacao.nome[strcspn(tripulacao.nome, "\n")] = 0;

  printf("Digite o telefone da tripulação: ");
  fgets(tripulacao.telefone, sizeof(tripulacao.telefone), stdin);
  tripulacao.telefone[strcspn(tripulacao.telefone, "\n")] = 0;

  printf("Digite o cargo da tripulação (ex: Piloto, Copiloto, Comissário, "
         "etc.): ");
  fgets(tripulacao.cargo, sizeof(tripulacao.cargo), stdin);
  tripulacao.cargo[strcspn(tripulacao.cargo, "\n")] = 0;

  printf("Digite a experiência da tripulação (em anos): ");
  scanf("%d", &tripulacao.experiencia);

  salvar_tripulacao(&tripulacao);
}

void cadastrar_voo() {
    printf("cadastrar_voo\n");
}

void cadastrar_assento() {
    printf("cadastrar_assento\n");
}

void reservar_assento() {
    printf("reservar_assento\n");
}

void baixar_reserva() {
    printf("baixar_reserva\n");
}

void pesquisa() {
    printf("pesquisa\n");
}

void consultar_fidelidade() {
    printf("consultar_fidelidade\n");
}

int main() {
    int opcao;

    do {
        printf("\nMenu de Opções:\n");
        printf("1. Cadastrar Passageiro\n");
        printf("2. Cadastrar Tripulação\n");
        printf("3. Cadastrar Voo\n");
        printf("4. Cadastrar Assento\n");
        printf("5. Reservar Assento\n");
        printf("6. Baixar Reserva\n");
        printf("7. Pesquisa\n");
        printf("8. Consultar Fidelidade\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            cadastrar_passageiro();
            break;
        case 2:
            cadastrar_tripulacao();
            break;
        case 3:
            cadastrar_voo();
            break;
        case 4:
            cadastrar_assento();
            break;
        case 5:
            reservar_assento();
            break;
        case 6:
            baixar_reserva();
            break;
        case 7:
            pesquisa();
            break;
        case 8:
            consultar_fidelidade();
            break;
        case 9:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 9);

    return 0;
}