#include <iostream>
#include <string>

#include "CanalTexto.h"

using namespace std;

int CanalTexto::contadorId;

vector<int> CanalTexto::idsLiberados;

CanalTexto::CanalTexto (string nome, Usuario *dono) {
    
    if (this->idsLiberados.size()) {
        this->id = this->idsLiberados[0];
        this->idsLiberados.erase(this->idsLiberados.begin());
    } else {
        this->id = ++CanalTexto::contadorId;
    }
    
    this->nome = nome;
    this->dono = dono;
}

CanalTexto::CanalTexto () {

}

vector<Mensagem> CanalTexto::getMensagens () {
    return this->mensagens;
}



void CanalTexto::addMensagem (Mensagem mensagem) {
    this->mensagens.push_back(mensagem);
}

void CanalTexto::addIdLiberado (unsigned int id) {
    CanalTexto::idsLiberados.push_back(id);
}


string CanalTexto::getNome() {
    return this->nome;
}

unsigned int CanalTexto::getId () {
    return this->id;
}

Usuario * CanalTexto::getDono() {
    return this->dono;
}
