#include <stdio.h>

void cadastrar_passageiro() {
    printf("cadastrar_passageiro\n");
}

void cadastrar_tripulacao() {
    printf("cadastrar_tripulacao\n");
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