#include <stdio.h>
#include <stdlib.h>

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

typedef struct {
  int codigo;
  char data[11];
  char hora[6];
  char origem[100];
  char destino[100];
  int codigo_aviao;
  int codigo_piloto;
  int codigo_copiloto;
  int codigo_comissario;
  int status;
  float tarifa;
} Voo;

typedef struct {
  int numero;
  int codigo_voo;
  int status;
} Assento;

typedef struct {
  int codigo_voo;
  int numero_assento;
  int codigo_passageiro;
} Reserva;

int validar_tripulacao(int codigo_piloto, int codigo_copiloto) {
  FILE *arquivo = fopen("tripulacao.dat", "rb");
  if (arquivo == NULL) {
    return 0;
  }

  int piloto_encontrado = 0, copiloto_encontrado = 0;
  Tripulacao tripulacao;

  while (fread(&tripulacao, sizeof(Tripulacao), 1, arquivo)) {
    if (tripulacao.codigo == codigo_piloto &&
        strcmp(tripulacao.cargo, "Piloto") == 0) {
      piloto_encontrado = 1;
    }
    if (tripulacao.codigo == codigo_copiloto &&
        strcmp(tripulacao.cargo, "Copiloto") == 0) {
      copiloto_encontrado = 1;
    }
  }

  fclose(arquivo);
  return piloto_encontrado && copiloto_encontrado;
}

int validar_passageiro(int codigo_passageiro) {
  FILE *arquivo = fopen("passageiros.dat", "rb");
  if (arquivo == NULL) {
    return 0;
  }

  Passageiro passageiro;
  while (fread(&passageiro, sizeof(Passageiro), 1, arquivo)) {
    if (passageiro.codigo == codigo_passageiro) {
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

int assento_existe(int codigo_voo, int numero_assento) {
  FILE *arquivo = fopen("assentos.dat", "rb");
  if (arquivo == NULL) {
    return 0;
  }

  Assento assento;
  while (fread(&assento, sizeof(Assento), 1, arquivo)) {
    if (assento.codigo_voo == codigo_voo && assento.numero == numero_assento) {
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

Assento *buscar_assento(int codigo_voo, int numero_assento) {
  FILE *arquivo = fopen("assentos.dat", "rb");
  if (arquivo == NULL) {
    return NULL;
  }

  Assento assento;
  while (fread(&assento, sizeof(Assento), 1, arquivo)) {
    if (assento.codigo_voo == codigo_voo && assento.numero == numero_assento) {
      fclose(arquivo);
      Assento *found_assento = malloc(sizeof(Assento));
      *found_assento = assento;
      return found_assento;
    }
  }

  fclose(arquivo);
  return NULL;
}

Voo *buscar_voo(int codigo_voo) {
  FILE *arquivo = fopen("assentos.dat", "rb");
  if (arquivo == NULL) {
    return NULL;
  }

  Voo voo;
  while (fread(&voo, sizeof(Assento), 1, arquivo)) {
    if (voo.codigo == codigo_voo) {
      fclose(arquivo);
      Voo *found_voo = malloc(sizeof(Voo));
      *found_voo = voo;
      return found_voo;
    }
  }

  fclose(arquivo);
  return NULL;
}

Tripulacao *buscar_tripulacao_por_codigo(int codigo_tripulacao) {
  FILE *arquivo = fopen("tripulacao.dat", "rb");
  if (arquivo == NULL) {
    return NULL;
  }
  Tripulacao tripulacao;
  while (fread(&tripulacao, sizeof(Tripulacao), 1, arquivo)) {
    if (tripulacao.codigo == codigo_tripulacao) {
      fclose(arquivo);
      Tripulacao *found_tripulacao = malloc(sizeof(Tripulacao));
      *found_tripulacao = tripulacao;
      return found_tripulacao;
    }
  }

  fclose(arquivo);
  return NULL;
}

Tripulacao *buscar_tripulacao_por_nome(char *nome) {
  FILE *arquivo = fopen("tripulacao.dat", "rb");

  if (arquivo == NULL) {
    return NULL;
  }

  Tripulacao tripulacao;
  while (fread(&tripulacao, sizeof(Tripulacao), 1, arquivo)) {
    if (strcmp(tripulacao.nome, nome) == 0) {
      fclose(arquivo);
      Tripulacao *found_tripulacao = malloc(sizeof(Tripulacao));
      *found_tripulacao = tripulacao;
      return found_tripulacao;
    }
  }

  fclose(arquivo);
  return NULL;
}

Passageiro *buscar_passageiro_por_codigo(int codigo_passageiro) {
  FILE *arquivo = fopen("passageiros.dat", "rb");
  if (arquivo == NULL) {
    return NULL;
  }
  Passageiro passageiro;
  while (fread(&passageiro, sizeof(Passageiro), 1, arquivo)) {
    if (passageiro.codigo == codigo_passageiro) {
      fclose(arquivo);
      Passageiro *found_passageiro = malloc(sizeof(Passageiro));
      *found_passageiro = passageiro;
      return found_passageiro;
    }
  }

  fclose(arquivo);
  return NULL;
}

Passageiro *buscar_passageiro_por_nome(char *nome) {
  FILE *arquivo = fopen("passageiros.dat", "rb");

  if (arquivo == NULL) {
    return NULL;
  }

  Passageiro passageiro;
  while (fread(&passageiro, sizeof(Passageiro), 1, arquivo)) {
    if (strcmp(passageiro.nome, nome) == 0) {
      fclose(arquivo);
      Passageiro *found_passageiro = malloc(sizeof(Passageiro));
      *found_passageiro = passageiro;
      return found_passageiro;
    }
  }

  fclose(arquivo);
  return NULL;
}

int reserva_existe(int codigo_voo, int numero_assento, int codigo_passageiro) {
  FILE *arquivo = fopen("reservas.dat", "rb");
  if (arquivo == NULL) {
    return 0;
  }

  Reserva reserva;

  while (fread(&reserva, sizeof(Reserva), 1, arquivo)) {
    if (reserva.codigo_voo == codigo_voo &&
        reserva.numero_assento == numero_assento &&
        reserva.codigo_passageiro == codigo_passageiro) {
      fclose(arquivo);
      return 1;
    }
  }
  return 0;
}

int voo_existe(int codigo_voo) {
  FILE *arquivo = fopen("voos.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de voos para validação.\n");
    return 0;
  }

  Voo voo;
  while (fread(&voo, sizeof(Voo), 1, arquivo)) {
    if (voo.codigo == codigo_voo) {
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

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

void salvar_voo(Voo *voo) {
  FILE *arquivo = fopen("voos.dat", "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de voos.\n");
    return;
  }
  fwrite(voo, sizeof(Voo), 1, arquivo);
  fclose(arquivo);
  printf("Voo salvo com sucesso!\n");
}

void salvar_assento(Assento *assento) {
  FILE *arquivo = fopen("assentos.dat", "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de assentos.\n");
    return;
  }
  fwrite(assento, sizeof(Assento), 1, arquivo);
  fclose(arquivo);
  printf("Assento salvo com sucesso!\n");
}

void salvar_reserva(Reserva *reserva) {
  FILE *arquivo = fopen("reservas.dat", "ab");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de reservas.\n");
    return;
  }
  fwrite(reserva, sizeof(Reserva), 1, arquivo);
  fclose(arquivo);
  printf("Reserva salva com sucesso!\n");
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
  Voo voo;

  printf("Digite o código do voo: ");
  scanf("%d", &voo.codigo);
  getchar();

  printf("Digite a data do voo (DD/MM/AAAA): ");
  fgets(voo.data, sizeof(voo.data), stdin);
  voo.data[strcspn(voo.data, "\n")] = 0;

  printf("Digite a hora do voo (HH:MM): ");
  fgets(voo.hora, sizeof(voo.hora), stdin);
  voo.hora[strcspn(voo.hora, "\n")] = 0;

  printf("Digite a origem do voo: ");
  fgets(voo.origem, sizeof(voo.origem), stdin);
  voo.origem[strcspn(voo.origem, "\n")] = 0;

  printf("Digite o destino do voo: ");
  fgets(voo.destino, sizeof(voo.destino), stdin);
  voo.destino[strcspn(voo.destino, "\n")] = 0;

  printf("Digite o código do avião: ");
  scanf("%d", &voo.codigo_aviao);

  printf("Digite o código do piloto: ");
  scanf("%d", &voo.codigo_piloto);

  printf("Digite o código do copiloto: ");
  scanf("%d", &voo.codigo_copiloto);

  printf("Digite o código do comissário: ");
  scanf("%d", &voo.codigo_comissario);

  printf("Digite a tarifa do voo: ");
  scanf("%f", &voo.tarifa);

  if (validar_tripulacao(voo.codigo_piloto, voo.codigo_copiloto)) {
    voo.status = 1;
    printf("Voo marcado como ativo.\n");
  } else {
    voo.status = 0;
    printf("Erro: Piloto ou copiloto inválidos. Voo marcado como inativo.\n");
  }

  salvar_voo(&voo);
}

void cadastrar_assento() {
  Assento assento;
  printf("Digite o código do voo para os assentos: ");
  scanf("%d", &assento.codigo_voo);

  printf("Digite o número do assento: ");
  scanf("%d", &assento.numero);

  printf("Digite o status do assento Ocupado - 1 / Livre - 0:");
  scanf("%d", &assento.status);

  assento.status = 0;

  salvar_assento(&assento);
}

void reservar_assento() {
  Reserva reserva;
  Assento assento;
  Voo voo;

  printf("Digite o código do passageiro: ");
  scanf("%d", &reserva.codigo_passageiro);

  if (!validar_passageiro(reserva.codigo_passageiro)) {
    printf("Erro: Passageiro não encontrado.\n");
    return;
  }

  printf("Digite o código do voo: ");
  scanf("%d", &reserva.codigo_voo);

  if (!voo_existe(reserva.codigo_voo)) {
    printf("Erro: Voo não encontrado.\n");
    return;
  }

  printf("Digite o número do assento: ");
  scanf("%d", &reserva.numero_assento);

  if (!assento_existe(reserva.codigo_voo, reserva.numero_assento)) {
    printf("Erro: Assento não encontrado.\n");
    return;
  }

  FILE *arquivo_assentos = fopen("assentos.dat", "r+b");
  if (arquivo_assentos == NULL) {
    printf("Erro ao abrir o arquivo de assentos.\n");
    return;
  }

  int encontrado = 0;
  while (fread(&assento, sizeof(Assento), 1, arquivo_assentos)) {
    if (assento.codigo_voo == reserva.codigo_voo &&
        assento.numero == reserva.numero_assento) {
      if (assento.status == 1) {
        printf("Erro: Assento já ocupado.\n");
        fclose(arquivo_assentos);
        return;
      }
      assento.status = 1;
      fseek(arquivo_assentos, -sizeof(Assento), SEEK_CUR);
      fwrite(&assento, sizeof(Assento), 1, arquivo_assentos);
      encontrado = 1;
      break;
    }
  }

  fclose(arquivo_assentos);

  if (!encontrado) {
    printf("Erro ao reservar assento.\n");
    return;
  }

  salvar_reserva(&reserva);
}

void baixar_reserva() {
  int codigo_passageiro, codigo_voo, numero_assento;

  printf("Digite o código do passageiro: ");
  scanf("%d", &codigo_passageiro);

  if (!validar_passageiro(codigo_passageiro)) {
    printf("Erro: Passageiro não encontrado.\n");
    return;
  }

  printf("Digite o código do voo: ");
  scanf("%d", &codigo_voo);

  if (!voo_existe(codigo_voo)) {
    printf("Erro: Voo não encontrado.\n");
    return;
  }

  printf("Digite o número do assento: ");
  scanf("%d", &numero_assento);

  if (!assento_existe(codigo_voo, numero_assento)) {
    printf("Erro: Assento não encontrado.\n");
    return;
  }

  if (!reserva_existe(codigo_voo, numero_assento, codigo_passageiro)) {
    printf("Erro: Reserva não encontrada.\n");
    return;
  }

  Assento *assento = buscar_assento(codigo_voo, numero_assento);
  assento->status = 0;

  Voo *voo = buscar_voo(codigo_voo);

  Passageiro *passageiro = buscar_passageiro_por_codigo(codigo_passageiro);
  if (passageiro != NULL)
    passageiro->pontos_fidelidade += 10;
  free(passageiro);

  printf("Sucesso: Reserva baixada!\nValor: R$%d", voo->tarifa);
}

void pesquisa_tripulacao() {
  int tipo_busca = 0; // 0 nome - 1 codigo

  printf("Digite o tipo da busca -> 0 Por Nome - 1 Por codigo: ");
  scanf("%d", &tipo_busca);

  Tripulacao *tripulacao = NULL;

  if (tipo_busca == 1) {
    // por codigo
    int codigo_tripulacao;
    printf("Digite o codigo da tripulacao: ");
    scanf("%d", &codigo_tripulacao);
    tripulacao = buscar_tripulacao_por_codigo(codigo_tripulacao);
  } else {
    // por nome
    char nome_tripulacao[100];
    printf("Digite o nome da tripulação: ");
    scanf(" %[^\n]s", nome_tripulacao);
    tripulacao = buscar_tripulacao_por_nome(&nome_tripulacao);
  }
  if (tripulacao == NULL) {
    printf("Erro: Tripulacao nao encontrada.\n");
  } else {
    printf("Tripulacao encontrada: \n");
    printf("Codigo: %d\n", tripulacao->codigo);
    printf("Nome: %s\n", tripulacao->nome);
    printf("Telefone %s\n", tripulacao->telefone);
    printf("Cargo: %s\n", tripulacao->cargo);
    printf("Experiencia: %d\n", tripulacao->experiencia);
  }
}

void pesquisar_reservas_passageiro(int codigo_passageiro) {
  FILE *arquivo_reservas = fopen("reservas.dat", "rb");
  if (arquivo_reservas == NULL) {
    printf("Erro ao abrir o arquivo de reservas.\n");
    return;
  }

  Reserva reserva;
  int reservas_encontradas = 0;

  while (fread(&reserva, sizeof(Reserva), 1, arquivo_reservas)) {
    if (reserva.codigo_passageiro == codigo_passageiro) {
      Voo *voo = buscar_voo(reserva.codigo_voo);
      if (voo != NULL) {
        printf("Reserva encontrada:\n");
        printf("  Código do Voo: %d\n", reserva.codigo_voo);
        printf("  Número do Assento: %d\n", reserva.numero_assento);
        printf("  Data do Voo: %s\n", voo->data);
        printf("  Hora do Voo: %s\n", voo->hora);
        printf("  Origem: %s\n", voo->origem);
        printf("  Destino: %s\n", voo->destino);
        printf("  Tarifa: R$%.2f\n", voo->tarifa);
        free(voo);
        reservas_encontradas++;
      }
    }
  }

  fclose(arquivo_reservas);

  if (reservas_encontradas == 0) {
    printf("Nenhuma reserva encontrada para este passageiro.\n");
  }
}

void pesquisa_passageiro() {
  int tipo_busca = 0; // 0 nome - 1 codigo

  printf("Digite o tipo da busca -> 0 Por Nome - 1 Por codigo: ");
  scanf("%d", &tipo_busca);

  Passageiro *passageiro = NULL;

  if (tipo_busca == 1) {
    // por codigo
    int codigo_passageiro;
    printf("Digite o codigo do passageiro: ");
    scanf("%d", &codigo_passageiro);
    passageiro = buscar_passageiro_por_codigo(codigo_passageiro);
  } else {
    // por nome
    char nome_passageiro[100];
    printf("Digite o nome do passageiro: ");
    scanf(" %[^\n]s", nome_passageiro);
    passageiro = buscar_passageiro_por_nome(&nome_passageiro);
  }
  if (passageiro == NULL) {
    printf("Erro: Passageiro nao encontrado.\n");
  } else {
    printf("Passageiro encontrada: \n");
    printf("Codigo: %d\n", passageiro->codigo);
    printf("Nome: %s\n", passageiro->nome);
    printf("Telefone %s\n", passageiro->telefone);
    printf("Endereco: %s\n", passageiro->endereco);
    printf("Pontos fidelidade: %d\n", passageiro->pontos_fidelidade);
  }

  pesquisar_reservas_passageiro(passageiro->codigo);
}

void pesquisa() {
  int tipo_busca = 0; // 0 passageiro - 1 tripulacao

  printf("Digite o tipo da busca -> 0 Passageiro - 1 Tripulacao: ");
  scanf("%d", &tipo_busca);

  if (tipo_busca == 1) {
    // busca tripulacao
    pesquisa_tripulacao();
  } else {
    pesquisa_passageiro();
  }
}

void consultar_fidelidade() {
  int codigo_passageiro;

  printf("Digite o código do passageiro: ");
  scanf("%d", &codigo_passageiro);

  Passageiro *passageiro = buscar_passageiro_por_codigo(codigo_passageiro);
  if (passageiro != NULL) {
    printf("O passageiro %s possui %d pontos de fidelidade.\n",
           passageiro->nome, passageiro->pontos_fidelidade);
    free(passageiro);
  } else {
    printf("Erro: Passageiro não encontrado.\n");
  }
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
