#ifndef CANAL_TEXTO_H
#define CANAL_TEXTO_H

#include <vector>
#include <string>
#include <iostream>

#include "Usuario.h"
#include "Mensagem.h"

using namespace std;

class CanalTexto {
    private:

        static int contadorId;

        static vector<int> idsLiberados;
        
        unsigned int id;
        string nome;
        Usuario *dono;

        vector<Mensagem> mensagens;

    public:

        CanalTexto ();

        CanalTexto (string nome, Usuario *dono);


        void addMensagem (Mensagem mensagem);

        void setId (unsigned int id);
        unsigned int getId ();

        void setDono(Usuario *dono);
        Usuario * getDono();

        void setNome (string nome);
        string getNome ();

        static void addIdLiberado (unsigned int id);

        vector<Mensagem> getMensagens ();

};

#endif
