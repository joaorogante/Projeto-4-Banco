#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

double deposito_global = 0.0;
double transferencia_global = 0.0;
double debito_global = 0.0;

void salvar_dados(Cliente *clientes, int num_clientes) {
    FILE *fp = fopen("clientes.txt", "w"); // Altere a extensão do arquivo para .txt
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    // Escrever cada cliente no arquivo de forma organizada
    for (int i = 0; i < num_clientes; i++) {
        fprintf(fp, "Cliente %d:\n", i + 1);
        fprintf(fp, "Nome: %s\n", clientes[i].nome);
        fprintf(fp, "CPF: %s\n", clientes[i].cpf);
        fprintf(fp, "Tipo de conta: %s\n", clientes[i].tipo_conta == 1 ? "Comum" : "Plus");
        fprintf(fp, "Saldo: %.2lf\n", clientes[i].saldo);
        fprintf(fp, "Senha: %s\n", clientes[i].senha);
        fprintf(fp, "-----------------\n");
    }
    fclose(fp);
}
void carregar_dados(Cliente *clientes, int *num_clientes) {
    FILE *fp = fopen("clientes.txt", "r"); // Altere a extensão do arquivo para .txt
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }
    char buffer[100];
    int i = 0;
    while (fscanf(fp, "Cliente %d:\n", &i) != EOF) {
        fscanf(fp, "Nome: %s\n", clientes[i-1].nome);
        fscanf(fp, "CPF: %s\n", clientes[i-1].cpf);
        char tipo_conta[10];
        fscanf(fp, "Tipo de conta: %s\n", tipo_conta);
        clientes[i-1].tipo_conta = strcmp(tipo_conta, "Comum") == 0 ? 1 : 2;
        fscanf(fp, "Saldo: %lf\n", &clientes[i-1].saldo);
        fscanf(fp, "Senha: %s\n", clientes[i-1].senha);
        fgets(buffer, sizeof(buffer), fp); // Ler a linha "-----------------\n"
    }
    *num_clientes = i;
    fclose(fp);
}
void novo_cliente(Cliente *clientes, int *num_clientes) {
    Cliente novo_cliente;
    printf("Digite o nome do cliente: ");
    scanf("%s", novo_cliente.nome);
    printf("Digite o CPF do cliente: ");
    scanf("%s", novo_cliente.cpf);
    printf("Digite o tipo de conta (1 para comum, 2 para plus): ");
    scanf("%d", &novo_cliente.tipo_conta);
    printf("Digite o saldo inicial da conta: ");
    scanf("%lf", &novo_cliente.saldo);
    printf("Digite a senha do cliente: ");
    scanf("%s", novo_cliente.senha);
    clientes[(*num_clientes)++] = novo_cliente;
    salvar_dados(clientes, *num_clientes);
}
void apaga_cliente(Cliente *clientes, int *num_clientes) {
    char cpf[11];
    int i, j;
    printf("Digite o CPF do cliente a ser apagado: ");
    scanf("%s", cpf);
    for (i = 0; i < *num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            for (j = i; j < *num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            (*num_clientes)--;
            printf("Cliente apagado com sucesso!\n");
            salvar_dados(clientes, *num_clientes);
            return;
        }
    }
    printf("Cliente não encontrado!\n");
}
void listar_clientes(Cliente *clientes, int num_clientes) {
    printf("\n==== Lista de Clientes ====\n");
    for (int i = 0; i < num_clientes; i++) {
        printf("\nCliente %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Tipo de Conta: %s\n", clientes[i].tipo_conta == 1 ? "Comum" : "Plus");
        printf("Saldo: R$ %.2lf\n", clientes[i].saldo);
        printf("---------------------------\n");
    }
    printf("\n");
}
void debito(Cliente *clientes, int num_clientes) {
    char cpf[11], senha[20];
    double valor, taxa;
    int i;
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    printf("Digite a senha do cliente: ");
    scanf("%s", senha);
    printf("Digite o valor a ser debitado: ");
    scanf("%lf", &valor);
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            taxa = clientes[i].tipo_conta == 1 ? 0.05 : 0.03;
            if (clientes[i].saldo - valor * (1 + taxa) >= (clientes[i].tipo_conta == 1 ? -1000.0 : -5000.0)) {
                clientes[i].saldo -= valor * (1 + taxa);
                debito_global += valor* (1 + taxa);
                printf("Débito realizado com sucesso!\n");
                return;
            } else {
                printf("Saldo insuficiente!\n");
            }
            return;
        }
    }
    printf("Cliente não encontrado ou senha incorreta!\n");
}    
void deposito(Cliente *clientes, int num_clientes) {
    char cpf[11];
    double valor;
    int i;
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    printf("Digite o valor a ser depositado: ");
    scanf("%lf", &valor);
    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clientes[i].saldo += valor;
            deposito_global += valor;
            printf("Depósito realizado com sucesso!\n");
         
            return;
        }
    }
    printf("Cliente não encontrado!\n");
}
void extrato(Cliente *clientes, int num_clientes) {
    char cpf[11], senha[20];
    int i;
    double debito_local = 0.0; 

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    printf("Digite a senha do cliente: ");
    scanf("%s", senha);

    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            printf("Saldo: %.2lf\n", clientes[i].saldo);

            FILE *fp = fopen("extrato.txt", "a");
            if (fp == NULL) {
                printf("Erro ao abrir o arquivo de extrato!\n");
                return;
            }

            fprintf(fp, "Cliente: %s\n", clientes[i].nome);
            fprintf(fp, "CPF: %s\n", clientes[i].cpf);
            fprintf(fp, "Saldo: %.2lf\n", clientes[i].saldo);
            fprintf(fp, "Operações:\n");

            if (debito_global > 0.0) {
                double taxa = clientes[i].tipo_conta == 1 ? 0.05 : 0.03;
                fprintf(fp, "Débito: %.2lf (Taxa: %.2lf)\n", debito_global, debito_global * taxa);
                debito_global = 0.0; 
            }
            if (deposito_global > 0.0) {
                fprintf(fp, "Depósito: %.2lf\n", deposito_global);
                deposito_global = 0.0; 
            }
            if (transferencia_global > 0.0) {
                fprintf(fp, "Transferência: %.2lf\n", transferencia_global);
                transferencia_global = 0.0; 
            }

            fprintf(fp, "-----------------\n");
            fclose(fp);

            return;
        }
    }

    printf("Cliente não encontrado ou senha incorreta!\n");
}
void transferencia(Cliente *clientes, int num_clientes) {
    char cpf_origem[12], senha[21], cpf_destino[12]; 
    double valor;
    int i, j;

    printf("Digite o CPF da conta de origem: ");
    scanf("%11s", cpf_origem); 
    printf("Digite a senha da conta de origem: ");
    scanf("%20s", senha); 
    printf("Digite o CPF da conta de destino: ");
    scanf("%11s", cpf_destino); 
    printf("Digite o valor a ser transferido: ");
    scanf("%lf", &valor);

    if(valor <= 0){
        printf("Valor inválido!\n");
        return; 
    }

    int conta_origem_encontrada = 0;

    for (i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf_origem) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            conta_origem_encontrada = 1;
            if(clientes[i].saldo - valor < 0){
                printf("Saldo insuficiente!\n");
                return;
            }

            for (j = 0; j < num_clientes; j++) {
                if (strcmp(clientes[j].cpf, cpf_destino) == 0) {
                    clientes[i].saldo -= valor;
                    clientes[j].saldo += valor;
                    printf("Transferência realizada com sucesso!\n");
                    transferencia_global = valor; 
                    return;
                }
            }

            if(j == num_clientes){
                printf("Conta de destino não encontrada!\n");
                return;
            }
        }
    }

    if(i == num_clientes && !conta_origem_encontrada){
        printf("Conta de origem não encontrada ou senha incorreta!\n");
        return;
    }  
}
