#pragma once
#include <string>
using namespace std;

class Tarefa {
public:
	string nome;
	float duracao;
	int qtdDependencias = 0;
	string* Dependencias;
	float ES = -1, EF = -1, LS = -1, LF = -1;

	/*
	* LEGENDA
	* ES = Early Start = início mais cedo
	* EF = Early Finish = término mais cedo
	* LS = Late Start = início mais tarde
	* LF = Late Finish = término mais tarde
	*/

public:
	Tarefa();
	void inserirDados(int qtdTarefas);
	void calculaInicioETerminoCedo(int qtdTarefas, Tarefa* arrTarefas);
	void iniciarTarefasTerminais(float maxEF, int qtdTarefas, Tarefa* arrTarefas);
	void calculaInicioETerminoTarde(float maxEF, int qtdTarefas, Tarefa* arrTarefas);
	void imprimeInicioETermino();
	~Tarefa();

};

