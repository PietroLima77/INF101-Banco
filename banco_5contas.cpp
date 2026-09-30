#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX_CONTAS = 5;

// Arrays: a posição i representa a mesma conta em todos eles
int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];
int qtdContas = 0;

// Lê um inteiro com validação básica
int lerInt(const string& msg) {
    int valor;
    cout << msg;
    cin >> valor;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida! " << msg;
        cin >> valor;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

// Retorna o índice da conta ou -1 se não encontrar
int buscarConta(int numero) {
    for (int i = 0; i < qtdContas; i++) {
        if (numeroConta[i] == numero) return i;
    }
    return -1;
}

// Pede o número e devolve o índice (-1 se não existir)
int selecionarConta() {
    if (qtdContas == 0) {
        cout << "\nNenhuma conta cadastrada.\n";
        return -1;
    }
    int num = lerInt("Numero da conta: ");
    int idx = buscarConta(num);
    if (idx == -1) cout << "\nConta nao encontrada.\n";
    return idx;
}

int main() {
    int opcao = 0;

    do {
        cout << "\n********************************\n";
        cout << "**        BANCO INF101        **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        opcao = lerInt("Opcao: ");

        switch (opcao) {
            case 1: {
                if (qtdContas >= MAX_CONTAS) {
                    cout << "\nLimite de " << MAX_CONTAS << " contas atingido!\n";
                    break;
                }
                cout << "\n--- Cadastro de conta ---\n";

                int num = lerInt("Numero da conta: ");
                while (num <= 0 || buscarConta(num) != -1) {
                    if (num <= 0) cout << "O numero deve ser maior que zero.\n";
                    else cout << "Ja existe uma conta com esse numero.\n";
                    num = lerInt("Numero da conta: ");
                }

                int i = qtdContas; // próxima posição livre
                numeroConta[i] = num;

                cout << "Nome do titular: ";
                getline(cin, nomeCliente[i]);

                cout << "CPF do titular: ";
                getline(cin, cpf[i]);

                int tipo = lerInt("Tipo da conta (1 = Corrente; 2 = Poupanca): ");
                while (tipo != 1 && tipo != 2) {
                    cout << "Tipo invalido!\n";
                    tipo = lerInt("Tipo da conta (1 = Corrente; 2 = Poupanca): ");
                }
                tipoConta[i] = tipo;

                double s;
                cout << "Saldo inicial: ";
                cin >> s;
                while (cin.fail() || s < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalido! O saldo nao pode ser negativo: ";
                    cin >> s;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                saldo[i] = s;

                contaAtiva[i] = true;
                qtdContas++;
                cout << "\nConta cadastrada com sucesso! (" << qtdContas << "/" << MAX_CONTAS << ")\n";
                break;
            }

            case 2: {
                int i = selecionarConta();
                if (i == -1) break;
                cout << "\n--- Dados da conta ---\n";
                cout << "Numero: " << numeroConta[i] << endl;
                cout << "Titular: " << nomeCliente[i] << endl;
                cout << "CPF: " << cpf[i] << endl;
                cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << endl;
                cout << fixed << setprecision(2);
                cout << "Saldo: R$ " << saldo[i] << endl;
                cout << "Status: " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
                break;
            }

            case 3: {
                int i = selecionarConta();
                if (i == -1) break;
                if (!contaAtiva[i]) {
                    cout << "\nConta inativa! Ative a conta para verificar o saldo.\n";
                } else {
                    cout << fixed << setprecision(2);
                    cout << "\nSaldo atual: R$ " << saldo[i] << endl;
                }
                break;
            }

            case 4: {
                int i = selecionarConta();
                if (i == -1) break;
                if (!contaAtiva[i]) {
                    cout << "\nConta inativa! Ative a conta para alterar o tipo.\n";
                    break;
                }
                int novo = lerInt("Novo tipo (1 = Corrente; 2 = Poupanca): ");
                while (novo != 1 && novo != 2) {
                    cout << "Tipo invalido!\n";
                    novo = lerInt("Novo tipo (1 = Corrente; 2 = Poupanca): ");
                }
                tipoConta[i] = novo;
                cout << "Tipo alterado com sucesso!\n";
                break;
            }

            case 5: {
                int i = selecionarConta();
                if (i == -1) break;
                contaAtiva[i] = !contaAtiva[i];
                cout << "\nConta " << (contaAtiva[i] ? "ATIVADA" : "DESATIVADA") << " com sucesso!\n";
                break;
            }

            case 6:
                cout << "\nEncerrando o sistema. Ate logo!\n";
                break;

            default:
                cout << "\nOpcao invalida! Tente novamente.\n";
        }
    } while (opcao != 6);

    return 0;
}
