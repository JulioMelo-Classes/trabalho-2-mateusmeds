#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <vector>
#include <string>
#include <iostream>

#include "Usuario.h"

using namespace std;

class Mensagem {
    private:

    static int contadorId;

    unsigned int id;

    string dataHora;
    string conteudo;
    
    Usuario *enviadaPor;
    

    public:

    Mensagem (string dataHora, Usuario *enviadaPor, string conteudo);

    Mensagem ();

    void setId (unsigned int id);
    unsigned int getId ();

    void setEnviadaPor(Usuario *enviadaPor);
    Usuario * getEnviadaPor();

    void setEmail (string email);
    string getEmail ();

    void setConteudo (string conteudo);
    string getConteudo ();

    void setDataHora (string dataHora);
    string getDataHora ();


};

#endif
