#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "projetoED2.h"

#define N 101

void criarMenuLinhaSuperior(){
    int i;
    printf("%c", 201);
    for(i = 0; i < STRTAM; i++)
        printf("%c", 205);
    printf("%c\n", 187);
}

void criarMenuLinhaHorizontal(int tamX){
    int i;
    printf("%c", 204);
    for(i = 0; i < STRTAM; i++)
        printf("%c", 205);
    printf("%c\n", 185);
}

void criarMenuLinhaRodape(int tamX){
    int i;
    printf("%c", 200);
    for(i = 0; i < STRTAM; i++)
        printf("%c", 205);
    printf("%c\n", 188);
}

void criarMenuItem(int tamX, char str[]){
    printf("%c", 186);
    printf("%-*s", tamX, str);
    printf("%c\n", 186);
}

struct cliente {
    char nome[101];
    long long int cpf;
};

struct empresa {
    char nome[101];
    long long int cnpj;
};

struct almoco {
    int id;
    char nome_almoco[101];
    float preco;
    char nome_empresa[101];
};

struct lanche {
    int id;
    char nome_lanche[101];
    float preco;
    char nome_empresa[101];
};

struct jantar {
    int id;
    char nome_jantar[101];
    float preco;
    char nome_empresa[101];
};

struct sobremesa {
    int id;
    char nome_sobremesa[101];
    float preco;
    char nome_empresa[101];
};

struct pedido {
    int id_pedido;
    char nome_prato[101];
    float preco;
    char nome_empresa[101];
    long long int cpf_cliente;
};

struct hash_cliente {
    Cliente* v[N];
};

struct hash_empresa {
    Empresa* v[N];
};

struct hash_almoco {
    Almoco* v[N];
};

struct hash_lanche {
    Lanche* v[N];
};

struct hash_jantar {
    Jantar* v[N];
};

struct hash_sobremesa {
    Sobremesa* v[N];
};

struct hash_pedido {
    Pedido* v[N];
};

HashCliente* hash_cria_cliente() {
    HashCliente* tab = (HashCliente*) malloc(sizeof(HashCliente));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

HashEmpresa* hash_cria_empresa() {
    HashEmpresa* tab = (HashEmpresa*) malloc(sizeof(HashEmpresa));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

HashAlmoco* hash_cria_almoco() {
    HashAlmoco* tab = (HashAlmoco*) malloc(sizeof(HashAlmoco));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

HashLanche* hash_cria_lanche() {
    HashLanche* tab = (HashLanche*) malloc(sizeof(HashLanche));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

HashJantar* hash_cria_jantar() {
    HashJantar* tab = (HashJantar*) malloc(sizeof(HashJantar));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

HashSobremesa* hash_cria_sobremesa() {
    HashSobremesa* tab = (HashSobremesa*) malloc(sizeof(HashSobremesa));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

HashPedido* hash_cria_pedido() {
    HashPedido* tab = (HashPedido*) malloc(sizeof(HashPedido));
    if(tab == NULL) {
        printf("Memoria insuficiente.\n");
        exit(1);
    }
    int i;
    for(i = 0; i < N; i++)
        tab->v[i] = NULL;
    return tab;
}

static int hash(long long int documento) {
    return documento % N;
}

void imprime_cliente(Cliente* cliente) {
    printf("Nome: %s\n", cliente->nome);
    printf("CPF: %lld\n", cliente->cpf);
}

void imprime_empresa(Empresa* empresa) {
    printf("Nome: %s\n", empresa->nome);
    printf("CNPJ: %lld\n", empresa->cnpj);
}

Cliente* hash_insere_cliente(HashCliente* tab, char* nome, long long int cpf) {
    int h = hash(cpf);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;
    Cliente* a = (Cliente*) malloc(sizeof(Cliente));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }
    a->cpf = cpf;
    strcpy(a->nome, nome);
    tab->v[h] = a;
    return a;
}

Empresa* hash_insere_empresa(HashEmpresa* tab, char* nome, long long int cnpj) {
    int h = hash(cnpj);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;
    Empresa* a = (Empresa*) malloc(sizeof(Empresa));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }
    a->cnpj = cnpj;
    strcpy(a->nome, nome);
    tab->v[h] = a;
    return a;
}

Almoco* hash_verifica_almoco(int id) {
    HashAlmoco* tabela_aux = hash_cria_almoco();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato;

    FILE* arq_aux = fopen("almocos.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de almocos.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_almoco(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    int h = hash(id);
    while(tabela_aux->v[h] != NULL) {
        if(tabela_aux->v[h]->id == id)
            return tabela_aux->v[h];
        h = (h + 1) % N;
    }
    return NULL;
}

Lanche* hash_verifica_lanche(int id) {
    HashLanche* tabela_aux = hash_cria_lanche();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato;

    FILE* arq_aux = fopen("lanches.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de lanches.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_lanche(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    int h = hash(id);
    while(tabela_aux->v[h] != NULL) {
        if(tabela_aux->v[h]->id == id)
            return tabela_aux->v[h];
        h = (h + 1) % N;
    }
    return NULL;
}

Jantar*  hash_verifica_jantar(int id) {
    HashJantar* tabela_aux = hash_cria_jantar();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato;

    FILE* arq_aux = fopen("jantares.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de jantares.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_jantar(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    int h = hash(id);
    while(tabela_aux->v[h] != NULL) {
        if(tabela_aux->v[h]->id == id)
            return tabela_aux->v[h];
        h = (h + 1) % N;
    }
    return NULL;
}

Sobremesa* hash_verifica_sobremesa(int id) {
    HashSobremesa* tabela_aux = hash_cria_sobremesa();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato;

    FILE* arq_aux = fopen("sobremesas.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de sobremesas.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_sobremesa(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    int h = hash(id);
    while(tabela_aux->v[h] != NULL) {
        if(tabela_aux->v[h]->id == id)
            return tabela_aux->v[h];
        h = (h + 1) % N;
    }
    return NULL;
}

static int hash_verifica_pedido(int id) {
    HashPedido* tabela_aux = hash_cria_pedido();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_pedido;
    long long int cpf_cliente;

    FILE* arq_aux = fopen("pedidos.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de pedidos.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\t] %lld", &id_pedido, nome_prato, &preco, nome_empresa, &cpf_cliente);
        hash_insere_pedido(tabela_aux, id_pedido, nome_prato, preco, nome_empresa, cpf_cliente);
    }
    fclose(arq_aux);

    int h = hash(id);
    while(tabela_aux->v[h] != NULL) {
        if(tabela_aux->v[h]->id_pedido == id)
            return 1;
        h = (h + 1) % N;
    }
    return 0;
}

Almoco* hash_insere_almoco(HashAlmoco* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa) {
    Almoco* a = (Almoco*) malloc(sizeof(Almoco));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    if(id_prato != NULL) {
        a->id = id_prato;
    }
    else {
        a->id = rand() % 1000;
        while(hash_verifica_almoco(a->id) != NULL) {
            a->id = rand() % 1000;
        }
    }

    int h = hash(a->id);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_almoco, nome_prato);
    a->preco = preco;
    strcpy(a->nome_empresa, nome_empresa);
    tab->v[h] = a;
    return a;
}

Lanche* hash_insere_lanche(HashLanche* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa) {
    Lanche* a = (Lanche*) malloc(sizeof(Lanche));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    if(id_prato != NULL) {
        a->id = id_prato;
    }
    else {
        a->id = rand() % 1000;
        while(hash_verifica_lanche(a->id) != NULL) {
            a->id = rand() % 1000;
        }
    }

    int h = hash(a->id);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_lanche, nome_prato);
    a->preco = preco;
    strcpy(a->nome_empresa, nome_empresa);
    tab->v[h] = a;

    return a;
}

Jantar* hash_insere_jantar(HashJantar* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa) {
    Jantar* a = (Jantar*) malloc(sizeof(Jantar));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    if(id_prato != NULL) {
        a->id = id_prato;
    }
    else {
        a->id = rand() % 1000;
        while(hash_verifica_jantar(a->id) != NULL) {
            a->id = rand() % 1000;
        }
    }

    int h = hash(a->id);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_jantar, nome_prato);
    a->preco = preco;
    strcpy(a->nome_empresa, nome_empresa);
    tab->v[h] = a;

    return a;
}

Sobremesa* hash_insere_sobremesa(HashSobremesa* tab, int id_prato, char* nome_prato, float preco, char* nome_empresa) {
    Sobremesa* a = (Sobremesa*) malloc(sizeof(Sobremesa));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    if(id_prato != NULL) {
        a->id = id_prato;
    }
    else {
        a->id = rand() % 1000;
        while(hash_verifica_sobremesa(a->id) != NULL) {
            a->id = rand() % 1000;
        }
    }

    int h = hash(a->id);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_sobremesa, nome_prato);
    a->preco = preco;
    strcpy(a->nome_empresa, nome_empresa);
    tab->v[h] = a;

    return a;
}

static void atualiza_arquivo_pedido_almoco(int id_pedido, char* nome_almoco, float preco, char* nome_empresa, long long int cpf_cliente) {
    FILE* arq = fopen("pedidos.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    fprintf(arq, "%d\t%s\t%f\t%s\t%lld\n", id_pedido, nome_almoco, preco, nome_empresa, cpf_cliente);
    fclose(arq);
}

Pedido* hash_insere_pedido_almoco(HashPedido* tab, Almoco* almoco, long long int cpf_cliente) {
    Pedido* a = (Pedido*) malloc(sizeof(Pedido));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    a->id_pedido = rand() % 1000;
    while(hash_verifica_pedido(a->id_pedido) != 0) {
        a->id_pedido = rand() % 1000;
    }

    int h = hash(a->id_pedido);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_prato, almoco->nome_almoco);
    a->preco = almoco->preco;
    strcpy(a->nome_empresa, almoco->nome_empresa);
    a->cpf_cliente = cpf_cliente;
    tab->v[h] = a;

    atualiza_arquivo_pedido_almoco(a->id_pedido, almoco->nome_almoco, almoco->preco, almoco->nome_empresa, cpf_cliente);
    return a;
}

static void atualiza_arquivo_pedido_lanche(int id_pedido, char* nome_lanche, float preco, char* nome_empresa, long long int cpf_cliente) {
    FILE* arq = fopen("pedidos.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    fprintf(arq, "%d\t%s\t%f\t%s\t%lld\n", id_pedido, nome_lanche, preco, nome_empresa, cpf_cliente);
    fclose(arq);
}

Pedido* hash_insere_pedido_lanche(HashPedido* tab, Lanche* lanche, long long int cpf_cliente) {
    Pedido* a = (Pedido*) malloc(sizeof(Pedido));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    a->id_pedido = rand() % 1000;
    while(hash_verifica_pedido(a->id_pedido) != 0) {
        a->id_pedido = rand() % 1000;
    }

    int h = hash(a->id_pedido);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_prato, lanche->nome_lanche);
    a->preco = lanche->preco;
    strcpy(a->nome_empresa, lanche->nome_empresa);
    a->cpf_cliente = cpf_cliente;
    tab->v[h] = a;

    atualiza_arquivo_pedido_lanche(a->id_pedido, lanche->nome_lanche, lanche->preco, lanche->nome_empresa, cpf_cliente);
    return a;
}

static void atualiza_arquivo_pedido_jantar(int id_pedido, char* nome_jantar, float preco, char* nome_empresa, long long int cpf_cliente) {
    FILE* arq = fopen("pedidos.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    fprintf(arq, "%d\t%s\t%f\t%s\t%lld\n", id_pedido, nome_jantar, preco, nome_empresa, cpf_cliente);
    fclose(arq);
}

Pedido* hash_insere_pedido_jantar(HashPedido* tab, Jantar* jantar, long long int cpf_cliente) {
    Pedido* a = (Pedido*) malloc(sizeof(Pedido));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    a->id_pedido = rand() % 1000;
    while(hash_verifica_pedido(a->id_pedido) != 0) {
        a->id_pedido = rand() % 1000;
    }

    int h = hash(a->id_pedido);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_prato, jantar->nome_jantar);
    a->preco = jantar->preco;
    strcpy(a->nome_empresa, jantar->nome_empresa);
    a->cpf_cliente = cpf_cliente;
    tab->v[h] = a;

    atualiza_arquivo_pedido_jantar(a->id_pedido, jantar->nome_jantar, jantar->preco, jantar->nome_empresa, cpf_cliente);
    return a;
}

static void atualiza_arquivo_pedido_sobremesa(int id_pedido, char* nome_sobremesa, float preco, char* nome_empresa, long long int cpf_cliente) {
    FILE* arq = fopen("pedidos.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    fprintf(arq, "%d\t%s\t%f\t%s\t%lld\n", id_pedido, nome_sobremesa, preco, nome_empresa, cpf_cliente);
    fclose(arq);
}

Pedido* hash_insere_pedido_sobremesa(HashPedido* tab, Sobremesa* sobremesa, long long int cpf_cliente) {
    Pedido* a = (Pedido*) malloc(sizeof(Pedido));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    a->id_pedido = rand() % 1000;
    while(hash_verifica_pedido(a->id_pedido) != 0) {
        a->id_pedido = rand() % 1000;
    }

    int h = hash(a->id_pedido);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;


    strcpy(a->nome_prato, sobremesa->nome_sobremesa);
    a->preco = sobremesa->preco;
    strcpy(a->nome_empresa, sobremesa->nome_empresa);
    a->cpf_cliente = cpf_cliente;
    tab->v[h] = a;

    atualiza_arquivo_pedido_sobremesa(a->id_pedido, sobremesa->nome_sobremesa, sobremesa->preco, sobremesa->nome_empresa, cpf_cliente);
    return a;
}

Pedido* hash_insere_pedido(HashPedido* tab, int id_pedido, char* nome_prato, float preco, char* nome_empresa, long long int cpf_cliente) {
    Pedido* a = (Pedido*) malloc(sizeof(Pedido));
    if(a == NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    if(id_pedido != NULL) {
        a->id_pedido = id_pedido;
    }
    else {
        a->id_pedido = rand() % 1000;
        while(hash_verifica_pedido(a->id_pedido) != 0) {
            a->id_pedido = rand() % 1000;
        }
    }

    int h = hash(a->id_pedido);
    while(tab->v[h] != NULL)
        h = (h + 1) % N;

    strcpy(a->nome_prato, nome_prato);
    a->preco = preco;
    strcpy(a->nome_empresa, nome_empresa);
    a->cpf_cliente = cpf_cliente;
    tab->v[h] = a;

    return a;
}

Cliente* hash_busca_cliente(HashCliente* tab, long long int cpf) {
    int h = hash(cpf);
    while(tab->v[h] != NULL) {
        if(tab->v[h]->cpf == cpf)
            return tab->v[h];
        h = (h + 1) % N;
    }
    return NULL;
}

Empresa* hash_busca_empresa(HashEmpresa* tab, long long int cnpj) {
    int h = hash(cnpj);
    while(tab->v[h] != NULL) {
        if(tab->v[h]->cnpj == cnpj)
            return tab->v[h];
        h = (h + 1) % N;
    }
    return NULL;
}

char* retorna_nome_empresa(Empresa* empresa) {
    return empresa->nome;
}

void atualiza_arquivo_clientes(HashCliente* tabela_cliente) {
    FILE* arq = fopen("clientes.txt", "wt");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    int i;
    for (i = 0; i<N; i++) {
        if(tabela_cliente->v[i]) {
            fprintf(arq, "%s\t%lld\n", tabela_cliente->v[i]->nome, tabela_cliente->v[i]->cpf);
        }
    }
    fclose(arq);
}

void atualiza_arquivo_empresas(HashEmpresa* tabela_empresa) {
    FILE* arq = fopen("empresas.txt", "wt");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }
    int i;
    for (i = 0; i<N; i++) {
        if(tabela_empresa->v[i]) {
            fprintf(arq, "%s\t%lld\n", tabela_empresa->v[i]->nome, tabela_empresa->v[i]->cnpj);
        }
    }
    fclose(arq);
}

int atualiza_arquivo_almocos(int id_almoco, char* nome_prato, float preco, char* nome_empresa_logada) {
    FILE* arq = fopen("almocos.txt", "a+");
      if(arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    if(id_almoco == NULL) {
        id_almoco = rand() % 1000;
        while(hash_verifica_almoco(id_almoco) != 0) {
            id_almoco = rand() % 1000;
        }
    }

    fprintf(arq, "%d\t%s\t%f\t%s\n", id_almoco, nome_prato, preco, nome_empresa_logada);
    fclose(arq);
    return id_almoco;
}

int atualiza_arquivo_lanches(int id_lanche, char* nome_prato, float preco, char* nome_empresa_logada) {
    FILE* arq = fopen("lanches.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    if(id_lanche == NULL) {
        id_lanche = rand() % 1000;
        while(hash_verifica_lanche(id_lanche) != 0) {
            id_lanche = rand() % 1000;
        }
    }

    fprintf(arq, "%d\t%s\t%f\t%s\n", id_lanche, nome_prato, preco, nome_empresa_logada);
    fclose(arq);
    return id_lanche;
}

int atualiza_arquivo_jantares(int id_jantar, char* nome_prato, float preco, char* nome_empresa_logada) {
    FILE* arq = fopen("jantares.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    if(id_jantar == NULL) {
        id_jantar = rand() % 1000;
        while(hash_verifica_jantar(id_jantar) != 0) {
            id_jantar = rand() % 1000;
        }
    }

    fprintf(arq, "%d\t%s\t%f\t%s\n", id_jantar, nome_prato, preco, nome_empresa_logada);
    fclose(arq);
    return id_jantar;
}

int atualiza_arquivo_sobremesas(int id_sobremesa, char* nome_prato, float preco, char* nome_empresa_logada) {
    FILE* arq = fopen("sobremesas.txt", "a+");
      if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    if(id_sobremesa == NULL) {
        id_sobremesa = rand() % 1000;
        while(hash_verifica_sobremesa(id_sobremesa) != 0) {
            id_sobremesa = rand() % 1000;
        }
    }

    fprintf(arq, "%d\t%s\t%f\t%s\n", id_sobremesa, nome_prato, preco, nome_empresa_logada);
    fclose(arq);
    return id_sobremesa;
}

void hash_imprime_almocos_empresa(HashAlmoco* tabela_almoco) {
    int i;
    for (i=0; i<N; i++) {
        if(tabela_almoco->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-", tabela_almoco->v[i]->id);
            printf("%s\n", tabela_almoco->v[i]->nome_almoco);
            printf("Preco: R$ %.2f\n\n", tabela_almoco->v[i]->preco);
        }
    }
}

void hash_imprime_lanches_empresa(HashLanche* tabela_lanche) {
    int i;
    for (i=0; i<N; i++) {
        if(tabela_lanche->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-", tabela_lanche->v[i]->id);
            printf("%s\n", tabela_lanche->v[i]->nome_lanche);
            printf("Preco: R$ %.2f\n\n", tabela_lanche->v[i]->preco);
        }
    }
}

void hash_imprime_jantares_empresa(HashJantar* tabela_jantar) {
    int i;
    for (i=0; i<N; i++) {
        if(tabela_jantar->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-", tabela_jantar->v[i]->id);
            printf("%s\n", tabela_jantar->v[i]->nome_jantar);
            printf("Preco: R$ %.2f\n\n", tabela_jantar->v[i]->preco);
        }
    }
}

void hash_imprime_sobremesas_empresa(HashSobremesa* tabela_sobremesa) {
    int i;
    for (i=0; i<N; i++) {
        if(tabela_sobremesa->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-", tabela_sobremesa->v[i]->id);
            printf("%s\n", tabela_sobremesa->v[i]->nome_sobremesa);
            printf("Preco: R$ %.2f\n\n", tabela_sobremesa->v[i]->preco);
        }
    }
}

void hash_imprime_pedidos_empresa(HashPedido* tabela_pedido) {
    int i;
    for (i=0; i<N; i++) {
        if(tabela_pedido->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-", tabela_pedido->v[i]->id_pedido);
            printf("%s\n", tabela_pedido->v[i]->nome_prato);
            printf("Preco: R$ %.2f\n\n", tabela_pedido->v[i]->preco);
        }
    }
}

void hash_imprime_todos_almocos() {
    HashAlmoco* tabela_aux = hash_cria_almoco();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato, i;

    FILE* arq_aux = fopen("almocos.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de almocos.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_almoco(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    for (i=0; i<N; i++) {
        if(tabela_aux->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_almoco);
            printf("R$ %.2f\n", tabela_aux->v[i]->preco);
            printf("Empresa: %s\n", tabela_aux->v[i]->nome_empresa);
            printf("\n");
        }
    }
}

void hash_imprime_todos_lanches() {
    HashLanche* tabela_aux = hash_cria_lanche();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato, i;

    FILE* arq_aux = fopen("lanches.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de lanches.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_lanche(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    for (i=0; i<N; i++) {
        if(tabela_aux->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_lanche);
            printf("R$ %.2f\n", tabela_aux->v[i]->preco);
            printf("Empresa: %s\n", tabela_aux->v[i]->nome_empresa);
            printf("\n");
        }
    }
}

void hash_imprime_todos_jantares() {
    HashJantar* tabela_aux = hash_cria_jantar();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato, i;

    FILE* arq_aux = fopen("jantares.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de jantares.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_jantar(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    for (i=0; i<N; i++) {
        if(tabela_aux->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_jantar);
            printf("R$ %.2f\n", tabela_aux->v[i]->preco);
            printf("Empresa: %s\n", tabela_aux->v[i]->nome_empresa);
            printf("\n");
        }
    }
}

void hash_imprime_todas_sobremesas() {
    HashSobremesa* tabela_aux = hash_cria_sobremesa();
    char linha[200], nome_prato[101], nome_empresa[101];
    float preco;
    int id_prato, i;

    FILE* arq_aux = fopen("sobremesas.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de sobremesas.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_prato, nome_prato, &preco, nome_empresa);
        hash_insere_sobremesa(tabela_aux, id_prato, nome_prato, preco, nome_empresa);
    }
    fclose(arq_aux);

    for (i=0; i<N; i++) {
        if(tabela_aux->v[i] != NULL) {
            printf("Prato:\n");
            printf("%d-%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_sobremesa);
            printf("R$ %.2f\n", tabela_aux->v[i]->preco);
            printf("Empresa: %s\n", tabela_aux->v[i]->nome_empresa);
            printf("\n");
        }
    }
}

int hash_remove_cliente(long long int cpf) {
    int removido = 0;
    char linha[200], nome_cliente[101];
    long long int cpf_aux;
    HashCliente* tabela_aux = hash_cria_cliente();

    FILE* arq_aux = fopen("clientes.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de clientes.\n");
        exit(1);
    }

    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, " %100[^\t] %lld", nome_cliente, &cpf_aux);
        if(cpf_aux != cpf) {
            hash_insere_cliente(tabela_aux, nome_cliente, cpf_aux);
        }
        else {
            removido = 1;
        }
    }
    fclose(arq_aux);

    if(removido) {
        atualiza_arquivo_clientes(tabela_aux);
    }

    return removido;
}

int hash_remove_empresa(long long int cnpj) {
    int removido = 0;
    char linha[200], nome_empresa[101];
    long long int cnpj_aux;
    HashEmpresa* tabela_aux = hash_cria_empresa();

    FILE* arq_aux = fopen("empresas.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de empresas.\n");
        exit(1);
    }

    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, " %100[^\t] %lld", nome_empresa, &cnpj_aux);
        if(cnpj_aux != cnpj) {
            hash_insere_empresa(tabela_aux, nome_empresa, cnpj_aux);
        }
        else {
            removido = 1;
        }
    }
    fclose(arq_aux);

    if(removido) {
        atualiza_arquivo_empresas(tabela_aux);
    }

    return removido;
}

float financeiro(char* nome_empresa_logada) {
    float total = 0, preco;
    char linha[200], nome_almoco[101], nome_empresa[101];
    int id;
    long long int cpf_cliente;

    FILE* arq_aux = fopen("pedidos.txt", "rt");
    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\t] %lld", &id, nome_almoco, &preco, nome_empresa, &cpf_cliente);
        if (strcmp(nome_empresa, nome_empresa_logada) == 0) {
            total += preco;
        }
    }
    fclose(arq_aux);

    return total;
}

static int hash_verifica_almoco_empresa_logada(HashAlmoco* tabela_almoco, int id_almoco) {
    int i;
    for(i=0; i<N; i++) {
        if(tabela_almoco->v[i]) {
            if (tabela_almoco->v[i]->id == id_almoco) {
                return 1;
            }
        }
    }
    return 0;
}

int hash_remove_almoco(HashAlmoco* tabela_almoco, int id_almoco, char* nome_empresa_logada) {
    if(hash_verifica_almoco_empresa_logada(tabela_almoco, id_almoco) != 0) {
        int i;
        char linha[200], nome_almoco[101], nome_empresa[101];
        int id_aux;
        float preco;
        HashAlmoco* tabela_aux = hash_cria_almoco();

        FILE* arq_aux = fopen("almocos.txt", "rt");
        if (! arq_aux) {
            printf("Erro na abertura do arquivo de almocos.\n");
            exit(1);
        }

        while(fgets(linha, 199, arq_aux) != NULL) {
            sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_almoco, &preco, nome_empresa);
            if(id_aux != id_almoco) {
                hash_insere_almoco(tabela_aux, id_aux, nome_almoco, preco, nome_empresa);
            }
        }
        fclose(arq_aux);

        arq_aux = fopen("almocos.txt", "wt");
        for (i=0; i<N; i++) {
            if (tabela_aux->v[i] != NULL) {
                fprintf(arq_aux, "%d\t%s\t%f\t%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_almoco, tabela_aux->v[i]->preco, tabela_aux->v[i]->nome_empresa);
            }
        }
        fclose(arq_aux);
        return 1;
    }
    return 0;
}

HashAlmoco* hash_atualiza_tabela_almoco(char* nome_empresa_logada) {
    char linha[200], nome_prato[101], nome_empresa[101];
    int id_aux;
    float preco;
    HashAlmoco* tabela_almocos = hash_cria_almoco();

    FILE* arq_aux = fopen("almocos.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de almocos.\n");
        exit(1);
    }

    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_prato, &preco, nome_empresa);
        if (strcmp(nome_empresa, nome_empresa_logada) == 0) {
            hash_insere_almoco(tabela_almocos, id_aux, nome_prato, preco, nome_empresa);
        }
    }
    fclose(arq_aux);
    return tabela_almocos;
}

static int hash_verifica_lanche_empresa_logada(HashLanche* tabela_lanche, int id_lanche) {
    int i;
    for(i=0; i<N; i++) {
        if(tabela_lanche->v[i]) {
            if (tabela_lanche->v[i]->id == id_lanche) {
                return 1;
            }
        }
    }
    return 0;
}

int hash_remove_lanche(HashLanche* tabela_lanche, int id_lanche, char* nome_empresa_logada) {
    if(hash_verifica_lanche_empresa_logada(tabela_lanche, id_lanche) != 0) {
        int i;
        char linha[200], nome_lanche[101], nome_empresa[101];
        int id_aux;
        float preco;
        HashLanche* tabela_aux = hash_cria_lanche();

        FILE* arq_aux = fopen("lanches.txt", "rt");
        if (! arq_aux) {
            printf("Erro na abertura do arquivo de lanches.\n");
            exit(1);
        }

        while(fgets(linha, 199, arq_aux) != NULL) {
            sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_lanche, &preco, nome_empresa);
            if(id_aux != id_lanche) {
                hash_insere_lanche(tabela_aux, id_aux, nome_lanche, preco, nome_empresa);
            }
        }
        fclose(arq_aux);

        arq_aux = fopen("lanches.txt", "wt");
        for (i=0; i<N; i++) {
            if (tabela_aux->v[i] != NULL) {
                fprintf(arq_aux, "%d\t%s\t%f\t%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_lanche, tabela_aux->v[i]->preco, tabela_aux->v[i]->nome_empresa);
            }
        }
        fclose(arq_aux);
        return 1;
    }
    return 0;
}

HashLanche* hash_atualiza_tabela_lanche(char* nome_empresa_logada) {
    char linha[200], nome_prato[101], nome_empresa[101];
    int id_aux;
    float preco;
    HashLanche* tabela_lanches = hash_cria_lanche();

    FILE* arq_aux = fopen("lanches.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de lanches.\n");
        exit(1);
    }

    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_prato, &preco, nome_empresa);
        if (strcmp(nome_empresa, nome_empresa_logada) == 0) {
            hash_insere_lanche(tabela_lanches, id_aux, nome_prato, preco, nome_empresa);
        }
    }
    fclose(arq_aux);

    return tabela_lanches;
}

static int hash_verifica_jantar_empresa_logada(HashJantar* tabela_jantar, int id_jantar) {
    int i;
    for(i=0; i<N; i++) {
        if(tabela_jantar->v[i]) {
            if (tabela_jantar->v[i]->id == id_jantar) {
                return 1;
            }
        }
    }
    return 0;
}

int hash_remove_jantar(HashJantar* tabela_jantar, int id_jantar, char* nome_empresa_logada) {
    if(hash_verifica_jantar_empresa_logada(tabela_jantar, id_jantar) != 0) {
        int i;
        char linha[200], nome_jantar[101], nome_empresa[101];
        int id_aux;
        float preco;
        HashJantar* tabela_aux = hash_cria_jantar();

        FILE* arq_aux = fopen("jantares.txt", "rt");
        if (! arq_aux) {
            printf("Erro na abertura do arquivo de jantares.\n");
            exit(1);
        }

        while(fgets(linha, 199, arq_aux) != NULL) {
            sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_jantar, &preco, nome_empresa);
            if(id_aux != id_jantar) {
                hash_insere_jantar(tabela_aux, id_aux, nome_jantar, preco, nome_empresa);
            }
        }
        fclose(arq_aux);

        arq_aux = fopen("jantares.txt", "wt");
        for (i=0; i<N; i++) {
            if (tabela_aux->v[i] != NULL) {
                fprintf(arq_aux, "%d\t%s\t%f\t%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_jantar, tabela_aux->v[i]->preco, tabela_aux->v[i]->nome_empresa);
            }
        }
        fclose(arq_aux);
        return 1;
    }
    return 0;
}

HashJantar* hash_atualiza_tabela_jantar(char* nome_empresa_logada) {
    char linha[200], nome_prato[101], nome_empresa[101];
    int id_aux;
    float preco;
    HashJantar* tabela_jantares = hash_cria_jantar();

    FILE* arq_aux = fopen("jantares.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de jantares.\n");
        exit(1);
    }

    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_prato, &preco, nome_empresa);
        if (strcmp(nome_empresa, nome_empresa_logada) == 0) {
            hash_insere_jantar(tabela_jantares, id_aux, nome_prato, preco, nome_empresa);
        }
    }
    fclose(arq_aux);

    return tabela_jantares;
}

static int hash_verifica_sobremesa_empresa_logada(HashSobremesa* tabela_sobremesa, int id_sobremesa) {
    int i;
    for(i=0; i<N; i++) {
        if(tabela_sobremesa->v[i]) {
            if (tabela_sobremesa->v[i]->id == id_sobremesa) {
                return 1;
            }
        }
    }
    return 0;
}

int hash_remove_sobremesa(HashSobremesa* tabela_sobremesa, int id_sobremesa, char* nome_empresa_logada) {
    if(hash_verifica_sobremesa_empresa_logada(tabela_sobremesa, id_sobremesa) != 0) {
        int i;
        char linha[200], nome_sobremesa[101], nome_empresa[101];
        int id_aux;
        float preco;
        HashSobremesa* tabela_aux = hash_cria_sobremesa();

        FILE* arq_aux = fopen("sobremesas.txt", "rt");
        if (! arq_aux) {
            printf("Erro na abertura do arquivo de sobremesas.\n");
            exit(1);
        }

        while(fgets(linha, 199, arq_aux) != NULL) {
            sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_sobremesa, &preco, nome_empresa);
            if(id_aux != id_sobremesa) {
                hash_insere_sobremesa(tabela_aux, id_aux, nome_sobremesa, preco, nome_empresa);
            }
        }
        fclose(arq_aux);

        arq_aux = fopen("sobremesas.txt", "wt");
        for (i=0; i<N; i++) {
            if (tabela_aux->v[i] != NULL) {
                fprintf(arq_aux, "%d\t%s\t%f\t%s\n", tabela_aux->v[i]->id, tabela_aux->v[i]->nome_sobremesa, tabela_aux->v[i]->preco, tabela_aux->v[i]->nome_empresa);
            }
        }
        fclose(arq_aux);
        return 1;
    }
    return 0;
}

HashSobremesa* hash_atualiza_tabela_sobremesa(char* nome_empresa_logada) {
    char linha[200], nome_prato[101], nome_empresa[101];
    int id_aux;
    float preco;
    HashSobremesa* tabela_sobremesas = hash_cria_sobremesa();

    FILE* arq_aux = fopen("sobremesas.txt", "rt");
    if (! arq_aux) {
        printf("Erro na abertura do arquivo de sobremesas.\n");
        exit(1);
    }

    while(fgets(linha, 199, arq_aux) != NULL) {
        sscanf(linha, "%d %100[^\t] %f %100[^\n]", &id_aux, nome_prato, &preco, nome_empresa);
        if (strcmp(nome_empresa, nome_empresa_logada) == 0) {
            hash_insere_sobremesa(tabela_sobremesas, id_aux, nome_prato, preco, nome_empresa);
        }
    }
    fclose(arq_aux);

    return tabela_sobremesas;
}

int hash_almoco_vazia(HashAlmoco* tabela_almoco) {
    int i, vazia = 1;
    for(i=0; i<N; i++) {
        if(tabela_almoco->v[i]) {
            vazia = 0;
        }
    }
    return vazia;
}

int hash_lanche_vazia(HashLanche* tabela_lanche) {
    int i, vazia = 1;
    for(i=0; i<N; i++) {
        if(tabela_lanche->v[i]) {
            vazia = 0;
        }
    }
    return vazia;
}

int hash_jantar_vazia(HashJantar* tabela_jantar) {
    int i, vazia = 1;
    for(i=0; i<N; i++) {
        if(tabela_jantar->v[i]) {
            vazia = 0;
        }
    }
    return vazia;
}

int hash_sobremesa_vazia(HashSobremesa* tabela_sobremesa) {
    int i, vazia = 1;
    for(i=0; i<N; i++) {
        if(tabela_sobremesa->v[i]) {
            vazia = 0;
        }
    }
    return vazia;
}

int todos_pratos_vazios(HashAlmoco* tabela_almoco, HashLanche* tabela_lanche, HashJantar* tabela_jantar, HashSobremesa* tabela_sobremesa) {
    int vazias = 1;
    if(hash_almoco_vazia(tabela_almoco) == 0 ||
       hash_lanche_vazia(tabela_lanche) == 0 ||
       hash_jantar_vazia(tabela_jantar) == 0 ||
       hash_sobremesa_vazia(tabela_sobremesa) == 0) {
        vazias = 0;
    }
    return vazias;
}
