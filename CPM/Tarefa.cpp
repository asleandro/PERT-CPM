#include "Tarefa.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
using namespace std;

Tarefa::Tarefa() {
}

void Tarefa::inserirDados(int qtdTarefas) {
	cout << setw(31) << "Nome da Tarefa: ";
	getline(cin, nome);
	transform(nome.begin(), nome.end(), nome.begin(), toupper);

	cout << setw(31) << "Duração: ";
	cin >> duracao;

	do {
		cout << setw(31) << "Quantidade de dependencias: ";
		cin >> qtdDependencias;
		if (qtdDependencias > qtdTarefas - 1) {
			cout << "     Quantidade de dependencias deve ser menor que a quantidade de Tarefas";
			Sleep(1500);
			cout << '\r' << "                                                        " << '\r';
		}
	} while (qtdDependencias > qtdTarefas - 1);
	cin.ignore();

	Dependencias = new string[qtdDependencias];

	for (int i = 0; i < qtdDependencias; i++) {
		if (qtdDependencias == 1)
			cout << setw(31) << "Nome da dependencia: ";
		else if (i < 9)
			cout << setw(28) << "Nome da dependencia nº" << i + 1 << ": ";
		else if (i >= 9)
			cout << setw(28) << "Nome da dependencia nº" << i + 1 << ": ";

		getline(cin, Dependencias[i]);
		transform(Dependencias[i].begin(), Dependencias[i].end(), Dependencias[i].begin(), toupper);
	}
}

void Tarefa::calculaInicioETerminoCedo(int qtdTarefas, Tarefa * arrTarefas) {
	if (ES == -1) {
		if (qtdDependencias == 0) {
			ES = 0;
		}
		else {
			float maxES = 0;

			for (int numDep = 0; numDep < qtdDependencias; numDep++) {
				for (int numTarefa = 0; numTarefa < qtdTarefas; numTarefa++) {
					if (Dependencias[numDep] == arrTarefas[numTarefa].nome) {
						if (arrTarefas[numTarefa].EF == -1) {
							arrTarefas[numTarefa].calculaInicioETerminoCedo(qtdTarefas, arrTarefas);
						}
						if (maxES = arrTarefas[numTarefa].EF) {
							maxES = arrTarefas[numTarefa].EF;
						}
					}
				}
			}
			ES = maxES;
		}
		EF = ES + duracao;
	}
}

void Tarefa::iniciarTarefasTerminais(float maxEF, int qtdTarefas, Tarefa* arrTarefas) {
	bool encontrado = false;

	for (int numTarefa = 0; numTarefa < qtdTarefas; numTarefa++) {
		for (int numDep = 0; numDep < arrTarefas[numTarefa].qtdDependencias; numDep++) {
			if (nome == arrTarefas[numTarefa].Dependencias[numDep]) {
				encontrado = true;
			}
		}
	}

	if (!encontrado) {
		LF = maxEF;
		LS = maxEF - duracao;
	}
}

void Tarefa::calculaInicioETerminoTarde(float maxEF, int qtdTarefas, Tarefa* arrTarefas) {
	float minLS = maxEF;

	for (int numTarefa = 0; numTarefa < qtdTarefas; numTarefa++) {
		for (int numDep = 0; numDep < arrTarefas[numTarefa].qtdDependencias; numDep++) {
			if (nome == arrTarefas[numTarefa].Dependencias[numDep]) {
				if (arrTarefas[numTarefa].LS == -1) {
					arrTarefas[numTarefa].calculaInicioETerminoTarde(maxEF, qtdTarefas, arrTarefas);
				}
				if (minLS > arrTarefas[numTarefa].LS) {
					minLS = arrTarefas[numTarefa].LS;
				}
			}
		}
		LF = minLS;
	}
	LS = LF - duracao;
}

void Tarefa::imprimeInicioETermino() {
	cout << nome << ":\n";
	cout << "ES: " << setw(6) << left << ES << "EF: " << EF << endl
		<< "LS: " << setw(6) << left << LS << "LF: " << LF << endl << endl;
}

Tarefa::~Tarefa() {
	delete[]Dependencias;
}




