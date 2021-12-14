#include <iostream>
#include <string>

#include "Mensagem.h"

using namespace std;

int Mensagem::contadorId;

Mensagem::Mensagem (string dataHora, Usuario *enviadaPor, string conteudo) {
    this->id = ++Mensagem::contadorId;
    this->dataHora = dataHora;
    this->enviadaPor = enviadaPor;
    this->conteudo = conteudo;
}

Mensagem::Mensagem () {

}

string Mensagem::getDataHora() {
    return this->dataHora;
}

unsigned int Mensagem::getId () {
    return this->id;
}

string Mensagem::getConteudo () {
    return this->conteudo;
}

Usuario * Mensagem::getEnviadaPor() {
    return this->enviadaPor;
}
