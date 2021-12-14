#include <iostream>
#include <string>

#include "Servidor.h"

using namespace std;

int Servidor::contadorId;

vector<int> Servidor::idsLiberados;

Servidor::Servidor (string nome, Usuario *dono) {

    if (this->idsLiberados.size()) {
        this->id = this->idsLiberados[0];
        this->idsLiberados.erase(this->idsLiberados.begin());
    } else {
        this->id = ++Servidor::contadorId;
    }

    this->nome = nome;
    this->dono = dono;
}

unsigned int Servidor::getId () {
    return this->id;
}

string Servidor::getNome() {
    return this->nome;
}

string Servidor::getDescricao () {
    return this->descricao;
}

string Servidor::getCodigoConvite () {
    return this->codigoConvite;
}

Usuario * Servidor::getDono() {
    return this->dono;
}

void Servidor::setDescricao (string descricao) {
    this->descricao = descricao;
}

void Servidor::setCodigoConvite (string codigoConvite) {
    this->codigoConvite = codigoConvite;
}


void Servidor::addParticipante (Usuario *usuario) {
    this->participantes.push_back(usuario);
}

void Servidor::removerParticipante (Usuario *usuario) {
    this->participantes.erase(this->participantes.begin());
}

vector<Usuario*> Servidor::getParticipantes () {
    return this->participantes;
}


void Servidor::addCanalTexto (CanalTexto canalTexto) {
    this->canaisTexto.push_back(canalTexto);
}

void Servidor::removerCanalTexto (CanalTexto canalTexto, int index) {
    this->canaisTexto.erase(this->canaisTexto.begin() + index);
}
vector<CanalTexto> Servidor::getCanaisTexto () {
    return this->canaisTexto;
}  

