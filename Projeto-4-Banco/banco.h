#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    char tipo_operacao[20]; // Depósito, Saque ou Transferência
    double valor;
    char data[11]; // dd/mm/aaaa
} Operacao;

typedef struct {
    char nome[50];
    char cpf[11]; 
    int tipo_conta;
    double saldo;
    char senha[20];
    Operacao operacoes[100]; // Array para armazenar as últimas 100 operações
    int indice_operacao; // Índice da próxima operação a ser inserida
} Cliente;

void salvar_dados(Cliente *clientes, int num_clientes);
void carregar_dados(Cliente *clientes, int *num_clientes);
void novo_cliente(Cliente *clientes, int *num_clientes);
void apaga_cliente(Cliente *clientes, int *num_clientes);
void listar_clientes(Cliente *clientes, int num_clientes);
void debito(Cliente *clientes, int num_clientes);
void deposito(Cliente *clientes, int num_clientes);
void extrato(Cliente *clientes, int num_clientes);
void transferencia(Cliente *clientes, int num_clientes);

#endif
