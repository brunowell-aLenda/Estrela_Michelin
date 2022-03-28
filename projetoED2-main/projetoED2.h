#ifndef PROJETOED2_H_INCLUDED
#define PROJETOED2_H_INCLUDED

#define STRTAM 50

////Início das funções utilizadas para a implementação do menu.
//Descrição: Funções utilizadas para desenvolver o menu.
//Implementadas por: Natália
void criarMenuLinhaSuperior();
void criarMenuLinhaHorizontal(int tamX);
void criarMenuLinhaRodape(int tamX);
void criarMenuItem(int tamX, char str[]);
////Início das funções utilizadas para a implementação do menu.


////Início das estruturas base do sistema
//Descrição: Estruturas que servem de entidades para o sistema.
//Implementadas por: Natália
typedef struct hash_cliente HashCliente;
typedef struct hash_empresa HashEmpresa;

typedef struct hash_almoco HashAlmoco;
typedef struct hash_lanche HashLanche;
typedef struct hash_jantar HashJantar;
typedef struct hash_sobremesa HashSobremesa;

typedef struct hash_pedido HashPedido;

typedef struct cliente Cliente;
typedef struct empresa Empresa;

typedef struct almoco Almoco;
typedef struct lanche Lanche;
typedef struct jantar Jantar;
typedef struct sobremesa Sobremesa;

typedef struct pedido Pedido;
////Fim das estruturas base do sistema.


////Início das funções para criação de tabelas.
//Descrição: Cria uma tabela de determinado tipo e preenche ela com posições vazias.
//Implementadas por: Natália
HashCliente* hash_cria_cliente();
HashEmpresa* hash_cria_empresa();

HashAlmoco* hash_cria_almoco();
HashLanche* hash_cria_lanche();
HashJantar* hash_cria_jantar();
HashSobremesa* hash_cria_sobremesa();

HashPedido* hash_cria_pedido();
////Fim das funções para criação de tabelas.


////Início das funções para inserção nas tabelas.
//Descrição: Recebem uma tabela de determinado tipo e as informações daquela estrutura que será inserida,
//           fazendo um tratamento para que não haja repetição de IDs e, em algumas delas, atualizamos o arquivo de texto daquela estrutura.
//Implementadas por: Vinicius
Cliente* hash_insere_cliente(HashCliente* tab, char* nome, long long int cpf);
Empresa* hash_insere_empresa(HashEmpresa* tab, char* nome, long long int cnpj);

Almoco* hash_insere_almoco(HashAlmoco* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa); //Se utiliza da função estática hash_verifica_almoco
Lanche* hash_insere_lanche(HashLanche* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa); //Se utiliza da função estática hash_verifica_lanche
Jantar* hash_insere_jantar(HashJantar* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa); //Se utiliza da função estática hash_verifica_jantar
Sobremesa* hash_insere_sobremesa(HashSobremesa* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa); //Se utiliza da função estática hash_verifica_sobremesa

Pedido* hash_insere_pedido(HashPedido* tab, int id_pedido, char* nome_prato, float preco, char* nome_empresa, long long int cpf_cliente); //Se utiliza da função estática hash_verifica_pedido
Pedido* hash_insere_pedido_almoco(HashPedido* tab, Almoco* almoco, long long int cpf_cliente); //Se utiliza da função estática hash_verifica_pedido e atualiza_arquivo_pedido_almoco
Pedido* hash_insere_pedido_lanche(HashPedido* tab, Lanche* lanche, long long int cpf_cliente); //Se utiliza da função estática hash_verifica_pedido e atualiza_arquivo_pedido_lanche
Pedido* hash_insere_pedido_jantar(HashPedido* tab, Jantar* jantar, long long int cpf_cliente); //Se utiliza da função estática hash_verifica_pedido e atualiza_arquivo_pedido_jantar
Pedido* hash_insere_pedido_sobremesa(HashPedido* tab, Sobremesa* sobremesa, long long int cpf_cliente); //Se utiliza da função estática hash_verifica_pedido e atualiza_arquivo_pedido_sobremesa
////Fim das funções para inserção nas tabelas.


////Início das funções para busca nas tabelas do sistema.
//Descrição: Fazemos um laço de repetição verificando a partir do documento (CPF ou CNPJ), caso achemos o usuário desejado retornamos ele,
//           se não, retornamos NULL.
//Implementadas por: Natália
Cliente* hash_busca_cliente(HashCliente* tab, long long int cpf);
Empresa* hash_busca_empresa(HashEmpresa* tab, long long int cnpj);
////Fim das funções para busca nas tabelas do sistema.


//Descrição: Recebemos uma empresa e retornamos o nome da mesma.
//Implementada por: Natália
char* retorna_nome_empresa(Empresa* empresa);


////Início das funções para impressão do cliente e da empresa.
//Descrição: Fazemos um laço de repetição na estrutura e caso aquela posição não seja vazia nós imprimimos os campos.
//Implementadas por: Flávio
void imprime_cliente(Cliente* cliente);
void imprime_empresa(Empresa* empresa);
////Fim das funções para impressão do cliente e da empresa.


////Início das funções para impressão dos pratos e pedidos de uma determinada empresa.
//Descrição: Fazemos um laço de repetição na estrutura e caso aquela posição não seja vazia nós imprimimos os campos.
//Implementadas por: Vinicius
void hash_imprime_almocos_empresa(HashAlmoco* tabela_almoco);
void hash_imprime_lanches_empresa(HashLanche* tabela_lanche);
void hash_imprime_jantares_empresa(HashJantar* tabela_jantar);
void hash_imprime_sobremesas_empresa(HashSobremesa* tabela_sobremesa);

void hash_imprime_pedidos_empresa(HashPedido* tabela_pedido);
////Fim das funções para impressão dos pratos e pedidos de uma determinada empresa.


////Início das funções para impressão de todos os pratos cadastrados no sistema.
//Descrição: Abrimos o arquivo que guarda as informações daquela estrutura, guardamos todos os dados em uma tabela auxiliar e, logo
//           em seguida, printamos na tela a tabela auxiliar.
//Implementadas por: Natália
void hash_imprime_todos_almocos(); //Se utiliza da função hash_insere_almoco
void hash_imprime_todos_lanches(); //Se utiliza da função hash_insere_lanches
void hash_imprime_todos_jantares(); //Se utiliza da função hash_insere_jantares
void hash_imprime_todas_sobremesas(); //Se utiliza da função hash_insere_sobremesas
////Fim das funções para impressão de todos os pratos cadastrados no sistema.


////Início das funções para atualização dos arquivos de texto.
//Descrição: Abrimos o arquivo daquela determinada estrutura e fazemos um for naquela tabela para irmos inserindo de posição em posição no arquivo.
//Implementadas por: Flávio
void atualiza_arquivo_clientes(HashCliente* tabela_cliente);
void atualiza_arquivo_empresas(HashEmpresa* tabela_empresa);


//Descrição: Recebemos todos os campos de um prato, fazemos um tratamento para não repetir IDs e depois inserimos no arquivo.
//Implementadas por: Vinicius
int atualiza_arquivo_almocos(int id_almoco, char* nome_prato, float preco, char* nome_empresa_logada); //Se utliza da função estática hash_verifica_almoco
int atualiza_arquivo_lanches(int id_lanche, char* nome_prato, float preco, char* nome_empresa_logada); //Se utliza da função estática hash_verifica_lanche
int atualiza_arquivo_jantares(int id_jantar, char* nome_prato, float preco, char* nome_empresa_logada); //Se utliza da função estática hash_verifica_jantar
int atualiza_arquivo_sobremesas(int id_sobremesa, char* nome_prato, float preco, char* nome_empresa_logada); //Se utliza da função estática hash_verifica_sobremesa
////Fim das funções para atualização dos arquivos de texto.


////Início das funções para verificação dos IDs antes de cadastrarmos alguma nova estrutura no sistema.
//Descrição: Abrimos o arquivo daquela determinada estrutura, fazemos uma tabela auxiliar com todos os dados daquela estrutura,
//           depois verificamos se há um ID repetido, se não, retornamos NULL, se sim, retornamos ele.
//Implementadas por: Vinicius
Almoco* hash_verifica_almoco(int id); //Se utiliza da função hash_insere_almoco
Lanche* hash_verifica_lanche(int id); //Se utiliza da função hash_insere_lanche
Jantar* hash_verifica_jantar(int id); //Se utiliza da função hash_insere_jantar
Sobremesa* hash_verifica_sobremesa(int id); //Se utiliza da função hash_insere_sobremesa
////Fim das funções para verificação dos IDs antes de cadastrarmos alguma nova estrutura no sistema.


////Início das funções para remoção de empresas e clientes das tabelas.
//Descrição: Abrimos o arquivo daquela determinada estrutura, fazemos uma tabela auxiliar sem a estrutura escolhida, depois atualizamos
//           o arquivo txt com a nova tabela.
//Implementadas por: Vinicius
int hash_remove_cliente(long long int cpf); //Se utiliza das funções hash_insere_cliente e atualiza_arquivo_clientes
int hash_remove_empresa(long long int cnpj); //Se utiliza das funções hash_insere_empresa e atualiza_arquivo_empresas
////Fim das funções para remoção de empresas e clientes das tabelas.


//Descrição: Abrimos o arquivo de pedidos, pegamos os pedidos daquela determinada empresa e fazemos a soma de todos os pedidos dela.
//Implementada por: Vinícius
float financeiro(char* nome_empresa_logada);


////Início das funções para remoção dos pratos do sistema.
//Descrição: Verificamos se a estrutura escolhida está de fato na tabela daquela empresa, depois abrimos o arquivo daquela estrutura,
//           fazemos uma tabela auxiliar com todos os dados daquela estrutura e atualizamos o arquivo txt dela.
//Implementadas por: Flávio
int hash_remove_almoco(HashAlmoco* tabela_almoco, int id_almoco, char* nome_empresa_logada); //Se utiliza da função estática hash_verifica_almoco_empresa_logada e hash_insere_almoco
int hash_remove_lanche(HashLanche* tabela_lanche, int id_lanche, char* nome_empresa_logada); //Se utiliza da função estática hash_verifica_lanche_empresa_logada e hash_insere_lanche
int hash_remove_jantar(HashJantar* tabela_jantar, int id_jantar, char* nome_empresa_logada); //Se utiliza da função estática hash_verifica_jantar_empresa_logada e hash_insere_jantar
int hash_remove_sobremesa(HashSobremesa* tabela_sobremesa, int id_sobremesa, char* nome_empresa_logada); //Se utiliza da função estática hash_verifica_sobremesa_empresa_logada e hash_sobremesa_almoco
////Fim das funções para remoção dos pratos do sistema.


////Início das funções para atualizarmos as tabelas dos pratos do sistema.
//Descrição: Abrimos o arquivo daquela determinada estrutura, colocamos os dados daquela empresa em uma tabela auxiliar e
//           atualizamos a tabela principal.
//Implementadas por: Flávio
HashAlmoco* hash_atualiza_tabela_almoco(char* nome_empresa_logada); //Se utiliza da função hash_insere_almoco
HashLanche* hash_atualiza_tabela_lanche(char* nome_empresa_logada); //Se utiliza da função hash_insere_lanche
HashJantar* hash_atualiza_tabela_jantar(char* nome_empresa_logada); //Se utiliza da função hash_insere_lanche
HashSobremesa* hash_atualiza_tabela_sobremesa(char* nome_empresa_logada); //Se utiliza da função hash_insere_lanche
////Fim das funções para atualizarmos as tabelas dos pratos do sistema.


////Início das funções para verificarmos se as tabelas do sistema estão vazias.
//Descrição: Fazemos um laço de repetição dentro da tabela, se alguma posição for válida, retornamos 0, se nenhuma for válida, 1.
//Implementadas por: Flávio
int hash_almoco_vazia(HashAlmoco* tabela_almoco);
int hash_lanche_vazia(HashLanche* tabela_lanche);
int hash_jantar_vazia(HashJantar* tabela_jantar);
int hash_sobremesa_vazia(HashSobremesa* tabela_sobremesa);

int todos_pratos_vazios(HashAlmoco* tabela_almoco, HashLanche* tabela_lanche, HashJantar* tabela_jantar, HashSobremesa* tabela_sobremesa); //Se utiliza das 4 funções anteriores
////Fim das funções para verificarmos se as tabelas do sistema estão vazias.

#endif // PROJETOED2_H_INCLUDED
