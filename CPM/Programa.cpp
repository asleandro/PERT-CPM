#include "Tarefa.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

void buscaCPM(float maxEF, int qtdTarefas, Tarefa* arrTarefas);
int pegaProximaTarefa(float maxEF, int qtdTarefas, Tarefa* arrTarefas, Tarefa &x);

int main() {
	setlocale(LC_ALL, "portuguese");

	SetConsoleTitle(L"AV2 Estruturas Avançadas de Dados e Análises - CPM");
	cout << "\n Aplicação do método CPM\n";
	cout << "----------------------------------------\n\n";

	int qtdTarefas;

	do {
		cout << setw(33) << "Informe a quantidade de tarefas: ";
		cin >> qtdTarefas;
		if (qtdTarefas < 2) {
			cout << " Quantidade de tarefas deve ser maior que 2.";
			Sleep(1500);
			cout << '\r' << "                                                        " << '\r';
		}
	} while (qtdTarefas <= 2);
	cin.ignore();

	Tarefa* arrTarefas = new Tarefa[qtdTarefas]; 
	for (int i = 0; i < qtdTarefas; i++) {
		cout << "\n\n";
		cout << setw(31) << "Tarefa nº" << i + 1 << "\n\n";
		arrTarefas[i].inserirDados(qtdTarefas);
	}

	// Calcular início e fim cedo
	for (int i = 0; i < qtdTarefas; i++) {
		arrTarefas[i].calculaInicioETerminoCedo(qtdTarefas, arrTarefas);
	}

	// Pegar o máximo de ES para todas as tarefas
	float maxEF = 0;
	for (int i = 0; i < qtdTarefas; i++) {
		if (maxEF < arrTarefas[i].EF) {
			maxEF = arrTarefas[i].EF;
		}
	}

	// Definir ES máximo às tarefas LF e calcular o LS
	for (int i = 0; i < qtdTarefas; i++) {
		arrTarefas[i].iniciarTarefasTerminais(maxEF, qtdTarefas, arrTarefas);
	}

	// Calcular LS E LF	
	for (int i = 0; i < qtdTarefas; i++) {
		arrTarefas[i].calculaInicioETerminoTarde(maxEF, qtdTarefas, arrTarefas);
	}

	cout << "\n\n------------------------------------------------------------------\n\n";

	// output

	cout << "\nDuração total: " << maxEF << "\n";

	cout << "\n\n\nCaminho crítico:\n\n";
	buscaCPM(maxEF, qtdTarefas, arrTarefas);

	cout << "\n\nTarefas primeiros/últimos inícios e términos: \n\n";
	for (int i = 0; i < qtdTarefas; i++) {
		arrTarefas[i].imprimeInicioETermino();
	}

	cout << "\n\n\n";
	delete[]arrTarefas;
	system("pause");
	return 0;
}

void buscaCPM(float maxEF, int qtdTarefas, Tarefa* arrTarefas) {
	string CP = "- ";
	for (int i = 0; i < qtdTarefas; i++) {
		if (arrTarefas[i].ES == 0 && arrTarefas[i].LS - arrTarefas[i].ES == 0 && arrTarefas[i].LF - arrTarefas[i].EF == 0) {
			while (true) {
				CP += arrTarefas[i].nome + " "; // adiciona o primeiro caminho crítico

				int index = 0;
				index = pegaProximaTarefa(maxEF, qtdTarefas, arrTarefas, arrTarefas[i]); // pega o index do primeiro

				if (index != -1) {
					CP += arrTarefas[index].nome + " "; // adiciona o próximo do primeiro ao caminho crítico

					while (true) {
						index = pegaProximaTarefa(maxEF, qtdTarefas, arrTarefas, arrTarefas[index]); // pega o index do próximo

						if (index != -1)
							CP += arrTarefas[index].nome + " "; // adiciona o próximo ao caminho crítico
						else
							break;
					}

					cout << CP << endl;
					CP = "- ";
				}
				else
					break;
			}
		}
	}
}

int pegaProximaTarefa(float maxEF, int qtdTarefas, Tarefa* arrTarefas, Tarefa& x) {
	// retorna o index da próxima tarefa no array de tarefas caso seja encontrado ou retorna -1 se não for

	for (int i = 0; i < qtdTarefas; i++) {
		for (int numDep = 0; numDep < arrTarefas[i].qtdDependencias; numDep++) {
			if (arrTarefas[i].Dependencias[numDep] == x.nome) {
				if (arrTarefas[i].LS - arrTarefas[i].ES == 0 && arrTarefas[i].LF - arrTarefas[i].EF == 0) {
					if (arrTarefas[i].LF != maxEF)
						arrTarefas[i].Dependencias[numDep] = "";
					return i;
				}
			}
		}
	}
	return -1;		
}
