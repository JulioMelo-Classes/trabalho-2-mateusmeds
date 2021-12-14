#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void Sistema::imprimirUsuariosLogados () {
	for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i){
		cout << "[Usuario: " << i->first << ", Servidor: " << i->second.first << ", Canal: " << i->second.second << "]" <<endl;
	}
}

string Sistema::buscarNomeCanalPeloId (int id, Servidor servidor) {

	for (auto &canal : servidor.getCanaisTexto()) {
		if (canal.getId() == id) {
			return canal.getNome();
		}
	}

	return "";
}

bool Sistema::pesquisarSeCanalJaExiste (string nome, Servidor servidor) {
	for (auto &canal : servidor.getCanaisTexto()) {
		if (canal.getNome() == nome) {
			return true;
		}
	}

	return false;
}


bool Sistema::verificarSeJaEhParticipante (Usuario *usuario, Servidor servidor) {

	for (auto &participante : servidor.getParticipantes()) {
		if (participante->getId() == usuario->getId()) {
			return true;
		}
	}

	return false;
}


Usuario * Sistema::buscarUsuarioPeloId (int id) {

	for (auto usuario : this->usuarios) {
		if (usuario->getId() == id) {
			return usuario;
		}
	}

	return NULL;
}

void Sistema::addUsuario (Usuario *usuario) {
	this->usuarios.push_back(usuario);
}

bool Sistema::checarSeExisteEmail (string email) {

	for (auto usuario : this->usuarios) {
		if (usuario->getEmail() == email) {
			return true;
		}
	}

	return false;
}

void Sistema::removerUsuario (Usuario *usuario) {

}

vector<Usuario*> Sistema::getUsuarios () {
	return this->usuarios;
}

void Sistema::addServidor (Servidor servidor) {
}

void Sistema::removerServidor (Servidor servidor) {

}

vector<Servidor> Sistema::getServidores () {
	return this->servidores;
}

bool Sistema::verificarSeEstaLogado (int id) {
	return usuariosLogados.count(id) > 0;
}

/* COMANDOS */
string Sistema::quit() {
	//Removendo da memória todas os usuários cadastrados
	for (auto usuario : this->usuarios) {
		delete usuario;
	}
	return "Finalizando o Concordo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {

	if (Sistema::checarSeExisteEmail(email)) {
		return "Erro: Usuário " + email + " já existe!";
	}

	Usuario *usuario = new Usuario(nome, email, senha);
	Sistema::addUsuario(usuario);

	return  "Usuário " + email + " criado com sucesso!";
}

std::string Sistema::delete_user (const std::string email, const std::string senha){

	int index = 0;
	for (auto usuario : this->usuarios) {
		if (usuario->getEmail() == email && usuario->getSenha() == senha) {

			if (this->verificarSeEstaLogado(usuario->getId())) {
				return "Erro: O usuário " + email + " está logado no sistema!";
			}

			Usuario::addIdLiberado(usuario->getId());

			this->usuarios.erase(this->usuarios.begin() + index);

			//Removendo da memória a instância desse usuário deletado
			delete usuario;

			return "Usuário " + email + " removido com sucesso!";
		} 
		index++;
	}

	return "Erro: Os dados informados são inválidos!";
}

string Sistema::login(const string email, const string senha) {

	for (auto usuario : this->usuarios) {
		if (usuario->getEmail() == email && usuario->getSenha() == senha) {
			usuariosLogados.insert({usuario->getId(), {0,0}});
			return "Logado como " + email;
		}
	}

	return "Erro: Os dados informados são inválidos!";
}

string Sistema::disconnect(int id) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário não está logado!";
	}

	for (auto usuario : this->usuarios) {
		if (usuario->getId() == id) {
			usuariosLogados.erase(id);
			return "Desconectando usuário " + usuario->getEmail();
		}
	}

	return "Erro: O usuário não existe!";
}

string Sistema::create_server(int id, const string nome) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuario precisa estar logado!";
	}

	for (auto &srv : this->servidores) {

		if (srv.getNome() == nome) {
			return "Erro: Já existe um servidor com esse nome!";
		}
	}

	for (auto usr : this->usuarios) {
		if (usr->getId() == id) {
			Servidor srv(nome, usr);
			this->servidores.push_back(srv);
			return "Servidor " + nome + " criado por " + usr->getEmail();
		}
	}

	return "Erro: ao tentar criar o servidor " + nome;
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuario precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		if (srv.getNome() == nome && srv.getDono()->getId() == id) {
			srv.setDescricao(descricao);

			return "Descrição do servidor " + srv.getNome() + " alterada com sucesso!";
		} else if (srv.getNome() == nome && srv.getDono()->getId() != id) {
			return "Erro: Você não tem permissão para alterar a descrição de um servidor que não foi criado por você!";
		}
	}

	return "Erro: O servidor " + nome + " não existe!";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuario precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		if (srv.getNome() == nome && srv.getDono()->getId() == id) {
			srv.setCodigoConvite(codigo);

			if (codigo == "") {
				return "Código de convite do servidor " + srv.getNome() + " removido com sucesso!";
			}

			return "Código de convite do servidor " + srv.getNome() + " alterado com sucesso!";
		} else if (srv.getNome() == nome && srv.getDono()->getId() != id) {
			return "Erro: Você não tem permissão para alterar o código de convite de um servidor que não foi criado por você!";
		}
	}

	return "Erro: O servidor " + nome + " não existe!";
}

string Sistema::list_servers(int id) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuario precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		cout << srv.getNome() <<endl;
	}

	return "";
}

string Sistema::remove_server(int id, const string nome) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuario precisa estar logado!";
	}

	int index = 0;
	for (auto &srv : this->servidores) {
		if (srv.getNome() == nome && srv.getDono()->getId() == id) {

			for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i){
				if (i->second.first == srv.getId()) {
					i->second.first = 0;
					i->second.second = 0;
				}
			}

			this->servidores.erase(this->servidores.begin() + index);

			return "O servidor " + nome + " foi removido com sucesso!";
		} else if (srv.getNome() == nome && srv.getDono()->getId() != id) {
			return "Erro: Você não tem permissão para remover um servidor que não foi criado por você!";
		}
		index++;
	}
	
	return "Erro: O servidor " + nome + " não existe!";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuario precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		//Verifica se existe algum servidor com o nome informado
		if (srv.getNome() == nome) {
			//Verifica se o usuário é dono ou se o servidor não possui código de convite
			if (srv.getDono()->getId() == id || srv.getCodigoConvite() == "" || srv.getCodigoConvite() == codigo) {

				for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
					//Procurando o id do usuário na tabela de usuários logados
					if (i->first == id) {

						//Atribuindo o id do servidor para o usuário na tabela de usuários logados
						i->second.first = srv.getId();

						//Atribuindo o valor 0 para o campo do canal do respectivo usuário
						i->second.second = 0;

						//Verifica se o usuário já participa do respectivo servidor
						if (!this->verificarSeJaEhParticipante(this->buscarUsuarioPeloId(id), srv)) {
							//Adicionando usuário na lista de participantes desse servidor
							srv.addParticipante(this->buscarUsuarioPeloId(id));
						}
					}
				}

				//Apagar: esta linha abaixo
				this->imprimirUsuariosLogados();

				return this->buscarUsuarioPeloId(id)->getEmail() + " entrou no servidor '" + nome + "' com sucesso!";
			} 
			//Verifica se o usuário NÃO digitou o código de convite
			else if (codigo == "") {
				return "Erro: Servidor '" + nome + "' requer código de convite";
			}

			//Caso não entre em nenhuma das condições, significa que o usuário digitou o código de convite errado
			return "Erro: Código de convite inválido!";
		}
	}

	return "Erro: O servidor " + nome + " não existe!";
}

string Sistema::leave_server(int id, const string nome) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {

		//Verifica se existe algum servidor com o nome informado
		if (srv.getNome() == nome) {

			//Verifica se o usuário está visualizando o servidor
			for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
				//Procurando o id do usuário e se ele está visualizando o servidor atualmente
				if (i->first == id && i->second.first == srv.getId()) {

					Usuario *usuario = this->buscarUsuarioPeloId(id);

					//Atribuindo o valor 0 para o servidor e o canal do respectivo usuário
					i->second = {0, 0};

					//Removendo o usuário da lista de participantes do respectivo servidor
					srv.removerParticipante(usuario);

					return usuario->getEmail() + " saiu do servidor '" + srv.getNome() + "'";
				}
			}

			//Caso não entre em nenhuma das condições, significa que o usuário digitou o código de convite errado
			return "Erro: O usuário precisa estar conectado no servidor!";
		}
	}

	return "Erro: O servidor '" + nome + "' não existe!";
}

string Sistema::list_participants(int id) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {

				//Exbidindo os participantes do respectivo servidor
				for (auto &participante : srv.getParticipantes()) {
					cout << participante->getNome() << endl;
				}

				return "";
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor!";
}

string Sistema::list_channels(int id) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {
				//Exibindo os canais de texto do respectivo servidor
				cout << "#canais de texto" << endl;
				for (auto &canal : srv.getCanaisTexto()) {
					cout << "#" << canal.getId() << " " << canal.getNome() << endl;
				}

				return "";
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para listar os canais!";
}

string Sistema::create_channel(int id, const string nome) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {
				//Verificando se o canal já existe
				if (this->pesquisarSeCanalJaExiste(nome, srv)) {
					return "O Canal de Texto '" + nome + "' já existe neste servidor!";
				}
				//Criando o canal
				CanalTexto canal(nome, this->buscarUsuarioPeloId(id));
				//Adicionando o canal no respectivo servidor
				srv.addCanalTexto(canal);

				return "Canal de Texto '" + nome + "' criado com sucesso!";
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para criar um canal!";
}

string Sistema::remove_channel(int id, const string nome) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {

			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {

				//Verificando se o canal existe
				if (!this->pesquisarSeCanalJaExiste(nome, srv)) {
					return "O Canal de Texto '" + nome + "' não existe neste servidor!";
				}
				
				int index = 0;
				for (auto &canal : srv.getCanaisTexto()) {

					//Pesquisando o canal pelo nome
					if (canal.getNome() == nome) {
						//Verificando se o usuário é dono do servidor ou do canal
						if (srv.getDono()->getId() == id || canal.getDono()->getId() == id) {
							
							//Loop responsável for atribuir na tabela de usuários logados o valor 0 no campo de canal dos usuários que estão visualizando o canal a ser removido 
							for (auto itr = usuariosLogados.begin(); itr != usuariosLogados.end(); ++itr) {
								//Verificando se o usuário está visualizando o canal atualmente, caso sim, atribui valor 0
								if (itr->second.second == canal.getId()) {
									itr->second.second = 0;
								}
							}

							srv.removerCanalTexto(canal, index);

							CanalTexto::addIdLiberado(canal.getId());

							return this->buscarUsuarioPeloId(id)->getEmail() +  " removeu o Canal de Texto '" + canal.getNome() + "'";
						}
					}
					index++;
				}
				return "Erro: O usuário não tem permissão para remover o canal '" + nome + "'";
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para remover um canal!";
}

string Sistema::enter_channel(int id, const string nome) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {
				//Pesquisando se o canal de texto existe no servidor
				for (auto &canal : srv.getCanaisTexto()) {
					if (canal.getNome() == nome) {
						//Alterando o id do canal na tabela de usuários logados do respectivo usuário
						i->second.second = canal.getId();

						return this->buscarUsuarioPeloId(id)->getEmail() + " entrou no canal de texto '" + nome + "'";
					}
				}

				return "Erro: O canal de tetxo '" + nome + "' não existe neste servidor!";
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para entrar em um canal de texto!";
}

string Sistema::leave_channel(int id) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {
				//Verifica se o usuário está visualizando algum canal no momento
				if (i->second.second == 0) {
					return "Erro: O usuário precisa estar visualizando algum canal para poder sair!";
				}

				//Pegando o id do canal
				int idCanal = i->second.second;

				//Atribuindo o valor 0 no campo de canal do respectivo usuário
				i->second.second = 0;
				
				return this->buscarUsuarioPeloId(id)->getEmail() + " saiu do canal de texto '" + this->buscarNomeCanalPeloId(idCanal, srv) + "'";
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para sair de um canal de texto!";
}

string Sistema::send_message(int id, const string mensagem) {

	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {

				if (i->second.second == 0) {
					return "Erro: O usuário não está visualizando nenhum canal!";
				}

				//Pesquisando se o canal de texto existe no servidor
				for (auto &canal : srv.getCanaisTexto()) {

					//Procurando canal pelo id
					if (canal.getId() == i->second.second) {

						Mensagem msg = Mensagem("13/12/2021 - 20:30", this->buscarUsuarioPeloId(id), mensagem);

						canal.addMensagem(msg);

						return "";
					}
				}
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para enviar mensagem em um canal de texto!";
}

string Sistema::list_messages(int id) {
	
	if (!this->verificarSeEstaLogado(id)) {
		return "Erro: O usuário precisa estar logado!";
	}

	for (auto &srv : this->servidores) {
		for (auto i = usuariosLogados.begin(); i != usuariosLogados.end(); ++i) {
			//Procurando o id do usuário na tabela de usuários logados e qual servidor ele está visualizando atualmente
			if (i->first == id && i->second.first == srv.getId()) {

				//Verificando se o usuário está visualizando algum canal
				if (i->second.second == 0) {
					return "Erro: O usuário não está visualizando nenhum canal!";
				}

				//Pesquisando se o canal de texto existe no servidor
				for (auto &canal : srv.getCanaisTexto()) {

					//Procurando canal pelo id
					if (canal.getId() == i->second.second) {

						for (auto &msg : canal.getMensagens()) {
							cout << msg.getEnviadaPor()->getNome() << "<" << msg.getDataHora() << ">: " << msg.getConteudo() << endl;
						}

						return "";
					}
				}
			}
		}
	}

	return "Erro: O usuário precisa estar conectado em algum servidor para listar as mensagens em um canal de texto!";
}

