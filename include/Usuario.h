#ifndef USUARIO_H
#define USUARIO_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Usuario {
    private:

    static int contadorId;
    //Irá armazenar os ids dos usuários removidos
    static vector<unsigned int> idsLiberados;

    unsigned int id;
    string nome;
    string email;
    string senha;

    public:

    Usuario (string nome, string email, string senha);

    Usuario ();
    
    static void addIdLiberado (unsigned int id);

    void setId (unsigned int id);

    unsigned int getId ();

    void setNome (string nome);

    string getNome ();

    void setEmail (string email);

    string getEmail ();

    void setSenha (string senha);

    string getSenha ();


};

#endif
