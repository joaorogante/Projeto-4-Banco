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
