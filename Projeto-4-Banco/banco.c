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
            strcpy(clientes[i].operacoes[clientes[i].indice_operacao].tipo_operacao, "Depósito");
            clientes[i].operacoes[clientes[i].indice_operacao].valor = valor;
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            sprintf(clientes[i].operacoes[clientes[i].indice_operacao].data, "%02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
            clientes[i].indice_operacao = (clientes[i].indice_operacao + 1) % 100;

            printf("Depósito realizado com sucesso!\n");
         
            return;
        }
    }
    printf("Cliente não encontrado!\n");
}
