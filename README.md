## Para compilar

```console
No diretório raiz
make
```

## Para executar
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
cd build
./concordo
```

```console
cd build
./concordo < ../data/script_comandos.txt
./concordo < ../data/script_servidores.txt
./concordo < ../data/script_testes.txt
```

## Dificuldades e Limitações
O projeto possui muitas funcionalidades, mas a que não conseguir fazer foi a de listar as mensagens. Até consigo imprimir nos métodos da classe CanalTexto, mas na list-messages não está funcionando por algum motivo. Certamente é uma besteirinha, mas não consegui.

# Avaliação
## Funcionalidades
- A1.2 ok
- A1.3 25%
Aqui você precisava levar em consideração as mensagens/canais/servidores do usuário também
- A1.4 ok
- A2.1 ok
- A2.2 ok
- A2.3 ok
- A2.4 ok
- A2.5 ok
- A2.6 ok
- A2.7 ok
- A2.8 ok
- A2.9 10%
Neste caso, vou penalizar pois você violou a restrição do trabalho
- B1.1 10%
Neste caso, vou penalizar pois você violou a restrição do trabalho
- B1.2 ok
- B1.3 ok
- B1.4 ok
- B1.5 10%
Neste caso, vou penalizar pois você violou a restrição do trabalho
- B2.1 10%
Neste caso, vou penalizar pois você violou a restrição do trabalho
- B2.2 10%
Neste caso, vou penalizar pois você violou a restrição do trabalho. Embora não funcione pelos motivos que conversamos na entrevista

## Classes
- Servidor 80%
Penalizei pois você violou a restrição relativa ao retorno de containers
- Canal 80%
Penalizei pois você violou a restrição relativa ao retorno de containers
- Mensagem ok

## Boas Práticas
- Documentação nok
- Testes ok
- Organização 60%
Uso de namespace std no .h

## Observações
Como conversamos o problema aqui é o retorno de containers e o uso deles na classe sistema quando eles deveriam ser usados por sua própria classe. No geral a implementação está ok. Outro ponto é que a indentação está estranha nos .h das classes, veja que quando definimos os membros privados é comum ter mais um nível de tab como se a _label_ `private:` representasse um if. Eu arrumei sua classe Mensagem.h veja como ficou para futuras implementações.