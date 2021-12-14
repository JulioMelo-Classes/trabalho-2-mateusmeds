#include <iostream>
#include <string>

#include "Usuario.h"

using namespace std;

int Usuario::contadorId;

vector<unsigned int> Usuario::idsLiberados;

Usuario::Usuario (string nome, string email, string senha) {

    if (this->idsLiberados.size()) {
        this->id = this->idsLiberados[0];
        this->idsLiberados.erase(this->idsLiberados.begin());
    } else {
        this->id = ++Usuario::contadorId;
    }

    this->nome = nome;
    this->email = email;
    this->senha = senha;
}

Usuario::Usuario () {
    
}

void Usuario::addIdLiberado (unsigned int id) {
    Usuario::idsLiberados.push_back(id);
}

string Usuario::getNome() {
    return this->nome;
}

unsigned int Usuario::getId () {
    return this->id;
}

string Usuario::getEmail () {
    return this->email;
}

string Usuario::getSenha () {
    return this->senha;
}
