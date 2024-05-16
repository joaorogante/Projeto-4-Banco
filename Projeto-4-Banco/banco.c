#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"
#include <time.h>

double deposito_global = 0.0;
double transferencia_global = 0.0;
double debito_global = 0.0;

void salvar_dados(Cliente *clientes, int num_clientes) {
    FILE *fp = fopen("clientes.bin", "w"); // Altere a extensão do arquivo para .txt
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
