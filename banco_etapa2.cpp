#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ===== Dados das contas =====
const int MAX_CONTAS = 100;

int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];      // 1 = Corrente, 2 = Poupanca
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];

int quantidadeContas = 0;

// ===== Historico de movimentacoes =====
const int MAX_MOVIMENTACOES = 500;

int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES];   // 'D' = deposito, 'S' = saque
double valorMovimentacao[MAX_MOVIMENTACOES];

int quantidadeMovimentacoes = 0;

// ===== Funcoes auxiliares =====

// Retorna o indice da conta no array, ou -1 se nao existir
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

// Grava uma movimentacao no historico (o espaco deve ser checado antes)
void registrarMovimentacao(int numero, char tipo, double valor) {
    contaMovimentacao[quantidadeMovimentacoes] = numero;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;
}

// ===== Funcionalidades =====

void cadastrarConta() {
    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Limite de contas atingido!" << endl;
        return;
    }

    int numero;
    cout << "Numero da conta: ";
    cin >> numero;

    if (buscarConta(numero) != -1) {
        cout << "Ja existe uma conta com esse numero!" << endl;
        return;
    }

    cin.ignore();
    string nome, cpfDigitado;
    cout << "Nome do cliente: ";
    getline(cin, nome);
    cout << "CPF: ";
    getline(cin, cpfDigitado);

    int tipo;
    cout << "Tipo da conta (1 - Corrente, 2 - Poupanca): ";
    cin >> tipo;
    if (tipo != 1 && tipo != 2) {
        cout << "Tipo invalido!" << endl;
        return;
    }

    double saldoInicial;
    cout << "Saldo inicial: R$ ";
    cin >> saldoInicial;
    if (saldoInicial < 0) {
        cout << "Saldo inicial nao pode ser negativo!" << endl;
        return;
    }

    int i = quantidadeContas;
    numeroConta[i] = numero;
    nomeCliente[i] = nome;
    cpf[i] = cpfDigitado;
    tipoConta[i] = tipo;
    saldo[i] = saldoInicial;
    contaAtiva[i] = true;
    quantidadeContas++;

    cout << "Conta cadastrada com sucesso!" << endl;
}

void listarContas() {
    if (quantidadeContas == 0) {
        cout << "Nenhuma conta cadastrada." << endl;
        return;
    }

    cout << "\n--- Contas cadastradas ---" << endl;
    for (int i = 0; i < quantidadeContas; i++) {
        cout << "Conta " << numeroConta[i]
             << " | " << nomeCliente[i]
             << " | CPF: " << cpf[i]
             << " | " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca")
             << " | Saldo: R$ " << saldo[i]
             << " | " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
    }
}

void consultarConta() {
    int numero;
    cout << "Numero da conta: ";
    cin >> numero;

    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }

    cout << "\n--- Dados da conta ---" << endl;
    cout << "Numero: " << numeroConta[i] << endl;
    cout << "Cliente: " << nomeCliente[i] << endl;
    cout << "CPF: " << cpf[i] << endl;
    cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
    cout << "Saldo: R$ " << saldo[i] << endl;
    cout << "Situacao: " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
}

void depositar() {
    int numero;
    double valor;
    cout << "Numero da conta: ";
    cin >> numero;

    int i = buscarConta(numero);
    if (i == -1 || !contaAtiva[i]) {
        cout << "Conta nao encontrada ou inativa!" << endl;
        return;
    }

    cout << "Valor do deposito: R$ ";
    cin >> valor;
    if (valor <= 0) {
        cout << "Valor invalido!" << endl;
        return;
    }
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
        cout << "Historico de movimentacoes cheio!" << endl;
        return;
    }

    saldo[i] = saldo[i] + valor;
    registrarMovimentacao(numeroConta[i], 'D', valor);

    cout << "Deposito realizado! Novo saldo: R$ " << saldo[i] << endl;
}

void sacar() {
    int numero;
    double valor;
    cout << "Numero da conta: ";
    cin >> numero;

    int i = buscarConta(numero);
    if (i == -1 || !contaAtiva[i]) {
        cout << "Conta nao encontrada ou inativa!" << endl;
        return;
    }

    cout << "Valor do saque: R$ ";
    cin >> valor;
    if (valor <= 0) {
        cout << "Valor invalido!" << endl;
        return;
    }
    if (valor > saldo[i]) {
        cout << "Saldo insuficiente!" << endl;
        return;
    }
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
        cout << "Historico de movimentacoes cheio!" << endl;
        return;
    }

    saldo[i] = saldo[i] - valor;
    registrarMovimentacao(numeroConta[i], 'S', valor);

    cout << "Saque realizado! Novo saldo: R$ " << saldo[i] << endl;
}

void transferir() {
    int numOrigem, numDestino;
    double valor;

    cout << "Conta de origem: ";
    cin >> numOrigem;
    cout << "Conta de destino: ";
    cin >> numDestino;

    int iOrigem = buscarConta(numOrigem);
    int iDestino = buscarConta(numDestino);

    if (iOrigem == -1 || iDestino == -1) {
        cout << "Uma das contas nao foi encontrada!" << endl;
        return;
    }
    if (!contaAtiva[iOrigem] || !contaAtiva[iDestino]) {
        cout << "Ambas as contas precisam estar ativas!" << endl;
        return;
    }
    if (iOrigem == iDestino) {
        cout << "Origem e destino nao podem ser a mesma conta!" << endl;
        return;
    }

    cout << "Valor da transferencia: R$ ";
    cin >> valor;
    if (valor <= 0) {
        cout << "Valor invalido!" << endl;
        return;
    }
    if (valor > saldo[iOrigem]) {
        cout << "Saldo insuficiente na conta de origem!" << endl;
        return;
    }
    // Precisa de espaco para 2 registros (saida + entrada)
    if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
        cout << "Historico sem espaco para a transferencia!" << endl;
        return;
    }

    saldo[iOrigem] = saldo[iOrigem] - valor;
    saldo[iDestino] = saldo[iDestino] + valor;

    registrarMovimentacao(numeroConta[iOrigem], 'S', valor);
    registrarMovimentacao(numeroConta[iDestino], 'D', valor);

    cout << "Transferencia realizada com sucesso!" << endl;
}

void exibirExtrato() {
    int numero;
    cout << "Numero da conta: ";
    cin >> numero;

    int i = buscarConta(numero);
    if (i == -1) {
        cout << "Conta nao encontrada!" << endl;
        return;
    }

    cout << "\n--- Extrato da conta " << numero << " (" << nomeCliente[i] << ") ---" << endl;

    bool temMovimentacao = false;
    for (int j = 0; j < quantidadeMovimentacoes; j++) {
        if (contaMovimentacao[j] == numero) {
            if (tipoMovimentacao[j] == 'D') {
                cout << "Deposito: R$ " << valorMovimentacao[j] << endl;
            }
            else if (tipoMovimentacao[j] == 'S') {
                cout << "Saque: R$ " << valorMovimentacao[j] << endl;
            }
            temMovimentacao = true;
        }
    }

    if (!temMovimentacao) {
        cout << "Nenhuma movimentacao registrada." << endl;
    }
    cout << "Saldo atual: R$ " << saldo[i] << endl;
}

// ===== Programa principal =====
int main() {
    cout << fixed << setprecision(2);

    int opcao;
    do {
        cout << "\n===== BANCO INF101 =====" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Depositar" << endl;
        cout << "5 - Sacar" << endl;
        cout << "6 - Transferir" << endl;
        cout << "7 - Extrato" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: depositar(); break;
            case 5: sacar(); break;
            case 6: transferir(); break;
            case 7: exibirExtrato(); break;
            case 0: cout << "Encerrando..." << endl; break;
            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);

    return 0;
}
