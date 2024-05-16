#include "banco.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    Cliente clientes[1000];
    int num_clientes = 0;
    int opcao;

    carregar_dados(clientes, &num_clientes);

    while (1) {
        printf("1. Novo cliente\n2. Apaga cliente\n3. Listar clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência Entre Contas\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novo_cliente(clientes, &num_clientes);
                break;
            case 2:
                apaga_cliente(clientes, &num_clientes);
                break;
            case 3:
                listar_clientes(clientes, num_clientes);
                break;
            case 4:
                debito(clientes, num_clientes);
                break;
            case 5:
                deposito(clientes, num_clientes);
                break;
            case 6:
                extrato(clientes, num_clientes);
                break;
            case 7:
                transferencia(clientes, num_clientes);
                break;
            case 0:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}
