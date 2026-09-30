#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

int main() {
    // Variáveis obrigatórias (Etapa 1: apenas variáveis individuais)
    int numeroConta = 0;
    string nomeCliente = "";
    string cpf = "";
    int tipoConta = 0;      // 1 = Corrente; 2 = Poupança
    double saldo = 0.0;
    bool contaAtiva = false;

    bool contaCadastrada = false; // controla se já existe conta
    int opcao = 0;

    do {
        // Menu com o nome do sistema
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Opcao: ";

        // Se digitar letra, limpa o erro e cai no "default"
        if (!(cin >> opcao)) {
            cin.clear();
            opcao = 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1: {
                cout << "\n--- Cadastro de conta ---\n";

                // Número da conta > 0
                cout << "Numero da conta: ";
                cin >> numeroConta;
                while (cin.fail() || numeroConta <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalido! Digite um numero maior que zero: ";
                    cin >> numeroConta;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Nome do titular: ";
                getline(cin, nomeCliente);

                cout << "CPF do titular: ";
                getline(cin, cpf);

                // Tipo da conta: 1 ou 2
                cout << "Tipo da conta (1 = Corrente; 2 = Poupanca): ";
                cin >> tipoConta;
                while (cin.fail() || (tipoConta != 1 && tipoConta != 2)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalido! Digite 1 ou 2: ";
                    cin >> tipoConta;
                }

                // Saldo inicial >= 0
                cout << "Saldo inicial: ";
                cin >> saldo;
                while (cin.fail() || saldo < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalido! O saldo nao pode ser negativo: ";
                    cin >> saldo;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                contaAtiva = true;       // conta nasce ativa
                contaCadastrada = true;
                cout << "\nConta cadastrada com sucesso!\n";
                break;
            }

            case 2:
                if (!contaCadastrada) {
                    cout << "\nNenhuma conta cadastrada.\n";
                } else {
                    cout << "\n--- Dados da conta ---\n";
                    cout << "Numero: " << numeroConta << endl;
                    cout << "Titular: " << nomeCliente << endl;
                    cout << "CPF: " << cpf << endl;
                    cout << "Tipo: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << endl;
                    cout << fixed << setprecision(2);
                    cout << "Saldo: R$ " << saldo << endl;
                    cout << "Status: " << (contaAtiva ? "Ativa" : "Inativa") << endl;
                }
                break;

            case 3:
                if (!contaCadastrada) {
                    cout << "\nNenhuma conta cadastrada.\n";
                } else if (!contaAtiva) {
                    cout << "\nConta inativa! Ative a conta para verificar o saldo.\n";
                } else {
                    cout << fixed << setprecision(2);
                    cout << "\nSaldo atual: R$ " << saldo << endl;
                }
                break;

            case 4:
                if (!contaCadastrada) {
                    cout << "\nNenhuma conta cadastrada.\n";
                } else if (!contaAtiva) {
                    cout << "\nConta inativa! Ative a conta para alterar o tipo.\n";
                } else {
                    cout << "\nTipo atual: " << (tipoConta == 1 ? "Corrente" : "Poupanca") << endl;
                    cout << "Novo tipo (1 = Corrente; 2 = Poupanca): ";
                    int novoTipo;
                    cin >> novoTipo;
                    while (cin.fail() || (novoTipo != 1 && novoTipo != 2)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalido! Digite 1 ou 2: ";
                        cin >> novoTipo;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    tipoConta = novoTipo;
                    cout << "Tipo alterado com sucesso!\n";
                }
                break;

            case 5:
                if (!contaCadastrada) {
                    cout << "\nNenhuma conta cadastrada.\n";
                } else {
                    contaAtiva = !contaAtiva; // inverte o estado
                    cout << "\nConta " << (contaAtiva ? "ATIVADA" : "DESATIVADA") << " com sucesso!\n";
                }
                break;

            case 6:
                cout << "\nEncerrando o sistema. Ate logo!\n";
                break;

            default:
                cout << "\nOpcao invalida! Tente novamente.\n";
        }
    } while (opcao != 6);

    return 0;
}
