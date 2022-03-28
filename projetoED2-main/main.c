#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "projetoED2.h"

int main() {
    //Início definição de variáveis
    char linha[200], nome[81];
    long long int documento;
    HashCliente* tabela_cliente = hash_cria_cliente();
    HashEmpresa* tabela_empresa = hash_cria_empresa();
    HashAlmoco* tabela_almoco = hash_cria_almoco();
    HashLanche* tabela_lanche = hash_cria_lanche();
    HashJantar* tabela_jantar = hash_cria_jantar();
    HashSobremesa* tabela_sobremesa = hash_cria_sobremesa();
    HashPedido* tabela_pedido = hash_cria_pedido();
    Empresa* empresa = NULL;
    Cliente* cliente = NULL;
    //Fim definição de variáveis

    system("color 2");

    //Início da leitura do arquivo e inserção dos clientes na tabela
    FILE* arq = fopen("clientes.txt", "rt");
    if (! arq) {
        printf("Erro na abertura do arquivo de clientes.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq) != NULL) {
        sscanf(linha, " %80[^\t] %lld", nome, &documento);
        hash_insere_cliente(tabela_cliente, nome, documento);
    }
    fclose(arq);
    //Fim da leitura do arquivo e inserção dos clientes na tabela

    //Início da leitura do arquivo e inserção das empresas na tabela
    arq = fopen("empresas.txt", "rt");
    if (! arq) {
        printf("Erro na abertura do arquivo de empresas.\n");
        exit(1);
    }
    while(fgets(linha, 199, arq) != NULL) {
        sscanf(linha, " %80[^\t] %lld", nome, &documento);
        hash_insere_empresa(tabela_empresa, nome, documento);
    }
    fclose(arq);
    //Fim da leitura do arquivo e inserção das empresas na tabela


    //Início das definições de novas variáveis
    int nivel1 = 1;
    int e_cliente = 0, e_empresa = 0;
    char nome_cadastro_cliente[81], nome_cadastro_empresa[81];
    int opcao_cliente_empresa, opcao_cliente_empresa_nv2, opcao_cadastro;
    long long int senha, documento_usuario;
    //Fim das definições de novas variáveis

    //Início do login
    do {
        criarMenuLinhaSuperior();
        criarMenuItem(STRTAM, "Ola, seja bem vindo ao Pedido Michelin, voce e:");
        criarMenuLinhaHorizontal(STRTAM);
        criarMenuItem(STRTAM, "[1] - Cliente");
        criarMenuItem(STRTAM, "[2] - Empresa");
        criarMenuItem(STRTAM, "[0] - Sair do programa");
        criarMenuLinhaRodape(STRTAM);
        scanf("%d", &opcao_cliente_empresa);

        switch (opcao_cliente_empresa) {
            case 1:
                do {
                    system("cls");
                    criarMenuLinhaSuperior();
                    criarMenuItem(STRTAM, "[1] - Login");
                    criarMenuItem(STRTAM, "[2] - Cadastro");
                    criarMenuItem(STRTAM, "[0] - Voltar");
                    criarMenuLinhaRodape(STRTAM);
                    scanf("%d", &opcao_cliente_empresa_nv2);

                    switch(opcao_cliente_empresa_nv2) {
                        case 1:
                            system("cls");
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Certo, informe sua senha (CPF):");
                            criarMenuLinhaRodape(STRTAM);
                            scanf("%lld", &senha);

                            cliente = hash_busca_cliente(tabela_cliente, senha);
                            if (cliente) {
                                documento_usuario = senha;
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Seja bem vindo! Essas sao suas informacoes:");
                                criarMenuLinhaRodape(STRTAM);

                                imprime_cliente(cliente);
                                e_cliente = 1;
                                nivel1 = 0;
                                opcao_cliente_empresa_nv2 = 0;
                            }
                            else {
                                do {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Voce nao possui um cadastro, deseja se cadastrar?");
                                    criarMenuLinhaHorizontal(STRTAM);
                                    criarMenuItem(STRTAM, "[1] - Sim");
                                    criarMenuItem(STRTAM, "[0] - Nao");
                                    criarMenuLinhaRodape(STRTAM);
                                    scanf("%d", &opcao_cadastro);

                                    switch (opcao_cadastro) {
                                        case 1:
                                            system("cls");
                                            criarMenuLinhaSuperior();
                                            criarMenuItem(STRTAM, "Informe seu nome:");
                                            criarMenuLinhaRodape(STRTAM);
                                            scanf(" %80[^\n]", nome_cadastro_cliente);
                                            criarMenuLinhaSuperior();
                                            criarMenuItem(STRTAM, "CPF:");
                                            criarMenuLinhaRodape(STRTAM);
                                            scanf("%lld", &senha);

                                            hash_insere_cliente(tabela_cliente, nome_cadastro_cliente, senha);
                                            printf("Voce foi cadastrado no nosso banco de dados.\n");
                                            atualiza_arquivo_clientes(tabela_cliente);
                                            documento_usuario = senha;
                                            e_cliente = 1;
                                            opcao_cadastro = 0;
                                            nivel1 = 0;
                                            opcao_cliente_empresa_nv2 = 0;
                                        break;

                                        case 0:
                                            opcao_cliente_empresa_nv2 = 0;
                                            system("cls");
                                        break;

                                        default:
                                            system("cls");
                                            criarMenuLinhaSuperior();
                                            criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                            criarMenuLinhaRodape(STRTAM);
                                        break;
                                    }
                                } while (opcao_cadastro != 0);
                            }
                        break;

                        case 2:
                            system("cls");
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Informe seu nome:");
                            criarMenuLinhaRodape(STRTAM);
                            scanf(" %80[^\n]", nome_cadastro_cliente);
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "CPF:");
                            criarMenuLinhaRodape(STRTAM);
                            scanf("%lld", &senha);

                            hash_insere_cliente(tabela_cliente, nome_cadastro_cliente, senha);
                            printf("Voce foi cadastrado no nosso banco de dados.\n");
                            atualiza_arquivo_clientes(tabela_cliente);
                            documento_usuario = senha;
                            e_cliente = 1;
                            opcao_cadastro = 0;
                            nivel1 = 0;
                            opcao_cliente_empresa_nv2 = 0;
                        break;

                        case 0:
                            system("cls");
                        break;

                        default:
                            system("cls");
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                            criarMenuLinhaRodape(STRTAM);
                        break;
                    }
                } while (opcao_cliente_empresa_nv2 != 0);
            break;

            case 2:
                do {
                    system("cls");
                    criarMenuLinhaSuperior();
                    criarMenuItem(STRTAM, "[1] - Login");
                    criarMenuItem(STRTAM, "[2] - Cadastro");
                    criarMenuItem(STRTAM, "[0] - Voltar");
                    criarMenuLinhaRodape(STRTAM);
                    scanf("%d", &opcao_cliente_empresa_nv2);

                    switch(opcao_cliente_empresa_nv2) {
                        case 1:
                            system("cls");
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Certo, informe sua senha (CNPJ):");
                            criarMenuLinhaRodape(STRTAM);
                            scanf("%lld", &senha);

                            empresa = hash_busca_empresa(tabela_empresa, senha);
                            if (empresa) {
                                documento_usuario = senha;
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Seja bem vindo! Essas sao suas informacoes:");
                                criarMenuLinhaRodape(STRTAM);

                                imprime_empresa(empresa);
                                e_empresa= 1;
                                nivel1 = 0;
                                opcao_cliente_empresa_nv2 = 0;
                            }
                            else {
                                do {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Voce nao possui um cadastro, deseja se cadastrar?");
                                    criarMenuLinhaHorizontal(STRTAM);
                                    criarMenuItem(STRTAM, "[1] - Sim");
                                    criarMenuItem(STRTAM, "[0] - Nao");
                                    criarMenuLinhaRodape(STRTAM);
                                    scanf("%d", &opcao_cadastro);

                                    switch (opcao_cadastro) {
                                        case 1:
                                            system("cls");
                                            criarMenuLinhaSuperior();
                                            criarMenuItem(STRTAM, "Informe o nome da sua empresa:");
                                            criarMenuLinhaRodape(STRTAM);
                                            scanf(" %80[^\n]", nome_cadastro_empresa);
                                            criarMenuLinhaSuperior();
                                            criarMenuItem(STRTAM, "CNPJ:");
                                            criarMenuLinhaRodape(STRTAM);
                                            scanf("%lld", &senha);

                                            hash_insere_empresa(tabela_empresa, nome_cadastro_empresa, senha);
                                            printf("Voce foi cadastrado no nosso banco de dados.\n");
                                            atualiza_arquivo_empresas(tabela_empresa);
                                            documento_usuario = senha;
                                            e_empresa= 1;
                                            opcao_cadastro = 0;
                                            nivel1 = 0;
                                            opcao_cliente_empresa_nv2 = 0;
                                        break;

                                        case 0:
                                            opcao_cliente_empresa_nv2 = 0;
                                            system("cls");
                                        break;

                                        default:
                                            system("cls");
                                            criarMenuLinhaSuperior();
                                            criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                            criarMenuLinhaRodape(STRTAM);
                                        break;
                                    }
                                } while (opcao_cadastro != 0);
                            }
                        break;

                        case 2:
                            system("cls");
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Informe o nome da sua empresa:");
                            criarMenuLinhaRodape(STRTAM);
                            scanf(" %80[^\n]", nome_cadastro_empresa);
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "CNPJ:");
                            criarMenuLinhaRodape(STRTAM);
                            scanf("%lld", &senha);

                            hash_insere_empresa(tabela_empresa, nome_cadastro_empresa, senha);
                            printf("Voce foi cadastrado no nosso banco de dados.\n");
                            atualiza_arquivo_empresas(tabela_empresa);
                            documento_usuario = senha;
                            e_empresa= 1;
                            opcao_cadastro = 0;
                            nivel1 = 0;
                            opcao_cliente_empresa_nv2 = 0;
                        break;

                        case 0:
                            system("cls");
                        break;

                        default:
                            system("cls");
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                            criarMenuLinhaRodape(STRTAM);
                        break;
                    }
                } while (opcao_cliente_empresa_nv2 != 0);
            break;

            case 0:
                nivel1 = 0;
            break;

            default:
                system("cls");
                criarMenuLinhaSuperior();
                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                criarMenuLinhaRodape(STRTAM);
            break;
        }
    } while(nivel1 != 0);
    //Fim do login


    if (e_cliente) {
    int opcao_cliente_nv1, opcao_cliente_nv2, id_almoco, id_lanche, id_jantar, id_sobremesa;
        do {
            criarMenuLinhaSuperior();
            criarMenuItem(STRTAM, "[1] - Almoco");
            criarMenuItem(STRTAM, "[2] - Lanche");
            criarMenuItem(STRTAM, "[3] - Jantar");
            criarMenuItem(STRTAM, "[4] - Sobremesa");
            criarMenuItem(STRTAM, "[5] - Apagar minha conta");
            criarMenuItem(STRTAM, "[0] - Sair do programa");
            criarMenuLinhaRodape(STRTAM);
            scanf("%d", &opcao_cliente_nv1);

            switch (opcao_cliente_nv1) {
                case 1:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Todos os Almocos");
                        criarMenuLinhaRodape(STRTAM);
                        hash_imprime_todos_almocos();
                        criarMenuLinhaSuperior();

                        criarMenuItem(STRTAM, "[1] - Escolher um almoco");
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);
                        scanf("%d", &opcao_cliente_nv2);

                        switch(opcao_cliente_nv2) {
                            case 1:
                                printf("Informe o ID:\n");
                                scanf("%d", &id_almoco);
                                if (id_almoco == 0) {
                                    break;
                                }
                                Almoco* almoco_aux = hash_verifica_almoco(id_almoco);
                                if (almoco_aux) {
                                    hash_insere_pedido_almoco(tabela_pedido, almoco_aux, documento_usuario);
                                    printf("Pedido feito, obrigado. Aproveite sua refeicao!\n");
                                    Sleep(2000);
                                }
                                else {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Almoco nao encontrado");
                                    criarMenuLinhaRodape(STRTAM);
                                    Sleep(1000);
                                }
                            break;

                            case 0:
                                system("cls");
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while(opcao_cliente_nv2);
                break;

                case 2:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Todos os Lanches");
                        criarMenuLinhaRodape(STRTAM);
                        hash_imprime_todos_lanches();
                        criarMenuLinhaSuperior();

                        criarMenuItem(STRTAM, "[1] - Escolher um lanche");
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);
                        scanf("%d", &opcao_cliente_nv2);

                        switch(opcao_cliente_nv2) {
                            case 1:
                                printf("Informe o ID:\n");
                                scanf("%d", &id_lanche);
                                if (id_lanche == 0) {
                                    break;
                                }
                                Lanche* lanche_aux = hash_verifica_lanche(id_lanche);
                                if (lanche_aux) {
                                    hash_insere_pedido_lanche(tabela_pedido, lanche_aux, documento_usuario);
                                    printf("Pedido feito, obrigado. Aproveite sua refeicao!\n");
                                    Sleep(2000);
                                }
                                else {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Lanche nao encontrado");
                                    criarMenuLinhaRodape(STRTAM);
                                    Sleep(1000);
                                }
                            break;

                            case 0:
                                system("cls");
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while(opcao_cliente_nv2);
                break;

                case 3:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Todos os Jantares");
                        criarMenuLinhaRodape(STRTAM);
                        hash_imprime_todos_jantares();

                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "[1] - Escolher um jantar");
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);
                        scanf("%d", &opcao_cliente_nv2);

                        switch(opcao_cliente_nv2) {
                            case 1:
                                printf("Informe o ID:\n");
                                scanf("%d", &id_jantar);
                                if (id_jantar == 0) {
                                    break;
                                }
                                Jantar* jantar_aux = hash_verifica_jantar(id_jantar);
                                if (jantar_aux) {
                                    hash_insere_pedido_jantar(tabela_pedido, jantar_aux, documento_usuario);
                                    printf("Pedido feito, obrigado. Aproveite sua refeicao!\n");
                                    Sleep(2000);
                                }
                                else {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Jantar nao encontrado.");
                                    criarMenuLinhaRodape(STRTAM);
                                    Sleep(1000);
                                }
                            break;

                            case 0:
                                system("cls");
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while(opcao_cliente_nv2);
                break;

                case 4:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Todas as Sobremesas");
                        criarMenuLinhaRodape(STRTAM);
                        hash_imprime_todas_sobremesas();

                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "[1] - Escolher uma sobremesa");
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);
                        scanf("%d", &opcao_cliente_nv2);

                        switch(opcao_cliente_nv2) {
                            case 1:
                                printf("Informe o ID:\n");
                                scanf("%d", &id_sobremesa);
                                if (id_sobremesa == 0) {
                                    break;
                                }
                                Sobremesa* sobremesa_aux = hash_verifica_sobremesa(id_sobremesa);
                                if (sobremesa_aux) {
                                    hash_insere_pedido_sobremesa(tabela_pedido, sobremesa_aux, documento_usuario);
                                    printf("Pedido feito, obrigado. Aproveite sua refeicao!\n");
                                    Sleep(2000);
                                }
                                else {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Sobremesa nao encontrada.");
                                    criarMenuLinhaRodape(STRTAM);
                                    Sleep(1000);
                                }
                            break;

                            case 0:
                                system("cls");
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while(opcao_cliente_nv2);
                break;

                case 5:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Tem certeza?");
                        criarMenuLinhaHorizontal(STRTAM);
                        criarMenuItem(STRTAM, "[1] - Sim");
                        criarMenuItem(STRTAM, "[0] - Nao, voltar");
                        criarMenuLinhaRodape(STRTAM);
                        scanf("%d", &opcao_cliente_nv2);

                        switch (opcao_cliente_nv2) {
                            case 1:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Estamos tristes em ver voce ir... :(");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(2000);
                                int remocao = hash_remove_cliente(documento_usuario);
                                if (remocao) {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Voce foi removido do nosso banco de dados.");
                                    criarMenuLinhaRodape(STRTAM);
                                    Sleep(1000);
                                    exit(1);
                                }

                            break;
                            case 0:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Que bom que voce ainda permanece aqui :)");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                            break;
                        }
                    } while(opcao_cliente_nv2 != 0);
                break;
                case 0:
                    opcao_cliente_nv1 = 0;
                break;

                default:
                    system("cls");
                    criarMenuLinhaSuperior();
                    criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                    criarMenuLinhaRodape(STRTAM);
                break;
            }
        } while(opcao_cliente_nv1 != 0);
    }

    else if (e_empresa) {
        //Início da definição de novas variáveis
        int id_prato;
        char nome_empresa[101], nome_empresa_logada[101];
        char nome_prato[101];
        float preco;
        long long int cpf_cliente;
        //Fim da definição de novas variáveis

        //Descobrindo o nome da empresa atual
        if (empresa != NULL) {
            strcpy(nome_empresa_logada, retorna_nome_empresa(empresa));
        }
        else {
            strcpy(nome_empresa_logada, nome_cadastro_empresa);
        }
        //Descobrindo o nome da empresa atual

        tabela_almoco = hash_atualiza_tabela_almoco(nome_empresa_logada);
        tabela_lanche = hash_atualiza_tabela_lanche(nome_empresa_logada);
        tabela_jantar = hash_atualiza_tabela_jantar(nome_empresa_logada);
        tabela_sobremesa = hash_atualiza_tabela_sobremesa(nome_empresa_logada);

        arq = fopen("pedidos.txt", "rt");
        if (! arq) {
            printf("Erro na abertura do arquivo de pedidos.\n");
            exit(1);
        }
        while(fgets(linha, 199, arq) != NULL) {
            sscanf(linha, "%d %100[^\t] %f %100[^\t] %lld", &id_prato, nome_prato, &preco, nome_empresa, &cpf_cliente);
            if(strcmp(nome_empresa, nome_empresa_logada) == 0) {
                hash_insere_pedido(tabela_pedido, id_prato, nome_prato, preco, nome_empresa, cpf_cliente);
            }
        }
        fclose(arq);
        id_prato = NULL;

        int  opcao_empresa_nv1, opcao_empresa_nv2;
        int id_almoco, id_lanche, id_jantar, id_sobremesa;
        float total_financeiro;
        do {
            criarMenuLinhaSuperior();
            criarMenuItem(STRTAM, "[1] - Cadastrar pratos");
            criarMenuItem(STRTAM, "[2] - Visualizar pratos cadastrados");
            criarMenuItem(STRTAM, "[3] - Excluir pratos");
            criarMenuItem(STRTAM, "[4] - Consultar financeiro");
            criarMenuItem(STRTAM, "[5] - Apagar minha conta");
            criarMenuItem(STRTAM, "[0] - Sair do programa");
            criarMenuLinhaRodape(STRTAM);
            scanf("%d", &opcao_empresa_nv1);

            switch (opcao_empresa_nv1) {
                case 1:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "[1] - Cadastrar almoco");
                        criarMenuItem(STRTAM, "[2] - Cadastrar lanche");
                        criarMenuItem(STRTAM, "[3] - Cadastrar jantar");
                        criarMenuItem(STRTAM, "[4] - Cadastrar sobremesa");
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);

                        scanf("%d", &opcao_empresa_nv2);
                        switch (opcao_empresa_nv2) {
                            case 1:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Informe o nome do prato:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf(" %[^\n]", nome_prato);
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Preco:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf("%f", &preco);
                                int id_almoco = atualiza_arquivo_almocos(id_prato, nome_prato, preco, nome_empresa_logada);
                                hash_insere_almoco(tabela_almoco, id_almoco, nome_prato, preco, nome_empresa_logada);
                                printf("Almoco cadastrado com sucesso\n");
                                Sleep(1000);
                            break;

                            case 2:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Informe o nome do prato:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf(" %[^\n]", nome_prato);
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Preco:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf("%f", &preco);
                                int id_lanche = atualiza_arquivo_lanches(id_prato, nome_prato, preco, nome_empresa_logada);
                                hash_insere_lanche(tabela_lanche, id_lanche, nome_prato, preco, nome_empresa_logada);
                                printf("Lanche cadastrado com sucesso\n");
                                Sleep(1000);
                            break;

                            case 3:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Informe o nome do prato:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf(" %[^\n]", nome_prato);
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Preco:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf("%f", &preco);
                                int id_jantar = atualiza_arquivo_jantares(id_prato, nome_prato, preco, nome_empresa_logada);
                                hash_insere_jantar(tabela_jantar, id_jantar, nome_prato, preco, nome_empresa_logada);
                                printf("Jantar cadastrado com sucesso\n");
                                Sleep(1000);
                            break;

                            case 4:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Informe o nome do prato:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf(" %[^\n]", nome_prato);
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Preco:");
                                criarMenuLinhaRodape(STRTAM);
                                scanf("%f", &preco);
                                int id_sobremesa = atualiza_arquivo_sobremesas(id_prato, nome_prato, preco, nome_empresa_logada);
                                hash_insere_sobremesa(tabela_sobremesa, id_sobremesa, nome_prato, preco, nome_empresa_logada);
                                printf("Sobremesa cadastrada com sucesso\n");
                                Sleep(1000);
                            break;

                            case 0:
                                system("cls");
                            break;
                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                            break;
                        }
                    } while(opcao_empresa_nv2 != 0);

                break;

                case 2:
                    if(todos_pratos_vazios(tabela_almoco, tabela_lanche, tabela_jantar, tabela_sobremesa) == 1) {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Voce nao possui nenhum prato cadastrado");
                        criarMenuLinhaRodape(STRTAM);
                    }
                    else {
                        system("cls");
                        if (hash_almoco_vazia(tabela_almoco) == 0) {
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Seus Almocos:");
                            criarMenuLinhaRodape(STRTAM);
                            hash_imprime_almocos_empresa(tabela_almoco);
                            printf("\n");
                        }

                        if (hash_lanche_vazia(tabela_lanche) == 0) {
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Seus Lanches:");
                            criarMenuLinhaRodape(STRTAM);
                            hash_imprime_lanches_empresa(tabela_lanche);
                            printf("\n");
                        }

                        if (hash_jantar_vazia(tabela_jantar) == 0) {
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Seus Jantares:");
                            criarMenuLinhaRodape(STRTAM);
                            hash_imprime_jantares_empresa(tabela_jantar);
                            printf("\n");
                        }

                        if (hash_sobremesa_vazia(tabela_sobremesa) == 0) {
                            criarMenuLinhaSuperior();
                            criarMenuItem(STRTAM, "Suas Sobremesas:");
                            criarMenuLinhaRodape(STRTAM);
                            hash_imprime_sobremesas_empresa(tabela_sobremesa);
                            printf("\n");
                        }
                    }
                break;

                case 3:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "O que voce deseja remover?");
                        criarMenuLinhaHorizontal(STRTAM);
                        criarMenuItem(STRTAM, "[1] - Almocos");
                        criarMenuItem(STRTAM, "[2] - Lanches");
                        criarMenuItem(STRTAM, "[3] - Jantares");
                        criarMenuItem(STRTAM, "[4] - Sobremesas");
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);

                        scanf("%d", &opcao_empresa_nv2);

                        switch (opcao_empresa_nv2) {
                            case 1:
                                do {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Seus almocos");
                                    criarMenuLinhaRodape(STRTAM);
                                    hash_imprime_almocos_empresa(tabela_almoco);
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Informe um ID");
                                    criarMenuItem(STRTAM, "[0] - Voltar");
                                    criarMenuLinhaRodape(STRTAM);

                                    scanf("%d", &id_almoco);
                                    if(hash_remove_almoco(tabela_almoco, id_almoco, nome_empresa_logada) == 1) {
                                        tabela_almoco = hash_atualiza_tabela_almoco(nome_empresa_logada);
                                        printf("Almoco removido com sucesso!\n");
                                        Sleep(2000);
                                        break;
                                    }
                                    else if (id_almoco == 0) {
                                        system("cls");
                                    }
                                    else {
                                        criarMenuLinhaSuperior();
                                        criarMenuItem(STRTAM, "Almoco nao encontrado");
                                        criarMenuLinhaRodape(STRTAM);
                                        Sleep(1000);
                                    }
                                } while (id_almoco != 0);
                            break;

                            case 2:
                                do {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Seus lanches");
                                    criarMenuLinhaRodape(STRTAM);
                                    hash_imprime_lanches_empresa(tabela_lanche);
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Informe um ID");
                                    criarMenuItem(STRTAM, "[0] - Voltar");
                                    criarMenuLinhaRodape(STRTAM);

                                    scanf("%d", &id_lanche);
                                    if(hash_remove_lanche(tabela_lanche, id_lanche, nome_empresa_logada) == 1) {
                                        tabela_lanche = hash_atualiza_tabela_lanche(nome_empresa_logada);
                                        printf("Lanche removido com sucesso!\n");
                                        Sleep(2000);
                                        break;
                                    }
                                    else if (id_lanche == 0) {
                                        system("cls");
                                    }
                                    else {
                                        criarMenuLinhaSuperior();
                                        criarMenuItem(STRTAM, "Lanche nao encontrado");
                                        criarMenuLinhaRodape(STRTAM);
                                        Sleep(1000);
                                    }
                                } while (id_lanche != 0);
                            break;

                            case 3:
                                do {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Seus jantares");
                                    criarMenuLinhaRodape(STRTAM);
                                    hash_imprime_jantares_empresa(tabela_jantar);
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Informe um ID");
                                    criarMenuItem(STRTAM, "[0] - Voltar");
                                    criarMenuLinhaRodape(STRTAM);

                                    scanf("%d", &id_jantar);
                                    if(hash_remove_jantar(tabela_jantar, id_jantar, nome_empresa_logada) == 1) {
                                        tabela_jantar = hash_atualiza_tabela_jantar(nome_empresa_logada);
                                        printf("Jantar removido com sucesso!\n");
                                        Sleep(2000);
                                        break;
                                    }
                                    else if (id_jantar == 0) {
                                        system("cls");
                                    }
                                    else {
                                        criarMenuLinhaSuperior();
                                        criarMenuItem(STRTAM, "Jantar nao encontrado");
                                        criarMenuLinhaRodape(STRTAM);
                                        Sleep(1000);
                                    }
                                } while (id_jantar != 0);
                            break;

                            case 4:
                                do {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Suas sobremesas");
                                    criarMenuLinhaRodape(STRTAM);
                                    hash_imprime_sobremesas_empresa(tabela_sobremesa);
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Informe um ID");
                                    criarMenuItem(STRTAM, "[0] - Voltar");
                                    criarMenuLinhaRodape(STRTAM);

                                    scanf("%d", &id_sobremesa);
                                    if(hash_remove_sobremesa(tabela_sobremesa, id_sobremesa, nome_empresa_logada) == 1) {
                                        tabela_sobremesa = hash_atualiza_tabela_sobremesa(nome_empresa_logada);
                                        printf("Sobremesa removida com sucesso!\n");
                                        Sleep(2000);
                                        break;
                                    }
                                    else if (id_sobremesa == 0) {
                                        system("cls");
                                    }
                                    else {
                                        criarMenuLinhaSuperior();
                                        criarMenuItem(STRTAM, "Sobremesa nao encontrado");
                                        criarMenuLinhaRodape(STRTAM);
                                        Sleep(1000);
                                    }
                                } while (id_sobremesa != 0);
                            break;

                            case 0:
                                system("cls");
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while (opcao_empresa_nv2 != 0);
                break;

                case 4:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Financeiro:");
                        criarMenuLinhaRodape(STRTAM);
                        hash_imprime_pedidos_empresa(tabela_pedido);

                        total_financeiro = financeiro(nome_empresa_logada);
                        criarMenuLinhaSuperior();
                        printf(" Esses sao seus ganhos totais:\n");
                        printf(" R$ %.2f\n", total_financeiro);
                        criarMenuLinhaRodape(STRTAM);
                        printf("\n");

                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "[0] - Voltar");
                        criarMenuLinhaRodape(STRTAM);

                        scanf("%d", &opcao_empresa_nv2);

                        switch (opcao_empresa_nv2) {
                            case 0:
                                system("cls");
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while(opcao_empresa_nv2 != 0);
                break;

                case 5:
                    do {
                        system("cls");
                        criarMenuLinhaSuperior();
                        criarMenuItem(STRTAM, "Tem certeza?");
                        criarMenuLinhaHorizontal(STRTAM);
                        criarMenuItem(STRTAM, "[1] - Sim");
                        criarMenuItem(STRTAM, "[0] - Nao, voltar");
                        criarMenuLinhaRodape(STRTAM);
                        scanf("%d", &opcao_empresa_nv2);

                        switch (opcao_empresa_nv2) {
                            case 1:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Estamos tristes em ver voce ir... :(");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(2000);
                                int remocao = hash_remove_empresa(documento_usuario);
                                if (remocao) {
                                    system("cls");
                                    criarMenuLinhaSuperior();
                                    criarMenuItem(STRTAM, "Voce foi removido do nosso banco de dados");
                                    criarMenuLinhaRodape(STRTAM);
                                    Sleep(1000);
                                    exit(1);
                                }

                            break;
                            case 0:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Que bom que voce ainda permanece aqui :)");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;

                            default:
                                system("cls");
                                criarMenuLinhaSuperior();
                                criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                                criarMenuLinhaRodape(STRTAM);
                                Sleep(1000);
                            break;
                        }
                    } while(opcao_empresa_nv2 != 0);
                break;

                case 0:
                break;

                default:
                    system("cls");
                    criarMenuLinhaSuperior();
                    criarMenuItem(STRTAM, "Opcao invalida, tente novamente.");
                    criarMenuLinhaRodape(STRTAM);
                break;
            }
        } while(opcao_empresa_nv1 != 0);
    }
    criarMenuLinhaSuperior();
    criarMenuItem(STRTAM, "Obrigado por usar nosso programa.");
    criarMenuLinhaRodape(STRTAM);
    return 0;
}
