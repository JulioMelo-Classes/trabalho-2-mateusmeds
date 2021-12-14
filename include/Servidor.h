#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <vector>
#include <string>
#include <iostream>

#include "Usuario.h"
#include "CanalTexto.h"

using namespace std;

class Servidor {
    private:

        static int contadorId;

        static vector<int> idsLiberados;

        unsigned int id;

        string nome;
        string descricao;
        string codigoConvite;

        Usuario *dono;

        vector<CanalTexto> canaisTexto = vector<CanalTexto>();
        vector<Usuario*> participantes;


    public:

        Servidor (string nome, Usuario *dono);

        void setId (unsigned int id);
        unsigned int getId ();

        void setDono(Usuario *dono);
        Usuario * getDono();

        void setNome (string nome);
        string getNome ();

        void setDescricao (string descricao);
        string getDescricao ();

        void setCodigoConvite (string codigoConvite);
        string getCodigoConvite ();

        void addParticipante (Usuario *usuario);
        void removerParticipante (Usuario *usuario);
        vector<Usuario*> getParticipantes ();

        void addCanalTexto (CanalTexto canalTexto);
        void removerCanalTexto (CanalTexto canalTexto, int index);
        vector<CanalTexto> getCanaisTexto ();
};

#endif
