#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>
#define TD 13

typedef struct
{
    int hora;
    int min;
} THora;

typedef struct
{
    int dia;
    int mes;
    int ano;
} TData;

typedef struct
{
    char *logradouro;
    char *bairro;
    char *cidade;
    int numero;
} TEndereco;

typedef struct
{
    int id;
    char *nome;
    TEndereco endereco;
} TLocal;

typedef struct
{
    int id;
    char *nome;
    char *apelido;
    char *email;
    char telefone[TD];
    TData nasc;
} TAmigo;

typedef struct
{
    int id;
    char *nome;
} TCategoria;

typedef struct
{
    TAmigo *amigos;
    int numAmigos;
    TCategoria *categoria;
    int numCategorias;
    TData data;
    THora horario;
    TLocal local;
    char *descricao;
} TEncontro;

/* Declaração de funções */
void menu();                                           // Exibe o menu principal
void op_menu(int op);                                  // Dispara a opção do menu incial
void menu_relatorios();                                // Exibe o menu de relatórios
void op_relatorios();                                  // Dispara a função do menu de relatórios
void OpcaoMenuRelatorio(int op);                       // Dispara a opção do menu de relatórios
void op_amigo();                                       // Dispara a função do menu de amigos
void menu_amigo();                                     // Exibe o menu de amigos
void OpcaoMenuAmigo(int op);                           // Dispara a opção do menu de amigos
void incluirAmigo();                                   // Dispara a função para criar um amigo
TAmigo criarAmigo();                                   // Cria amigos
void OpcaoListarAmigo();                               // Dispara a opção de listar amigos
void menuListarAmigo();                                // Exibe o menu para listar amigos
void listarAmigos();                                   // Lista todos os amigos
void exibeAmigo(TAmigo amigo);                         // Exibe um amigo
void OpcaoAlterarAmigo();                              // Dispara a opção para alterar amigo
void MenuAlterarAmigo(int indice);                     // Exibe o menu de alteração de amigo
void alterarAmigo(int op, int indice);                 // Altera um atributo de um amigo
void OpcaoExcluirAmigo();                              // Dispara a opção para excluir um amigo
void excluirAmigo(int indice);                         // Exclui um amigo
void excluirAmigoDeEncontros(int indice);              // Exclui um amigo de todos os encontros
void op_local();                                       // Dispara a função do menu de locais
void menu_local();                                     // Exibe o menu de locais
void OpcaoMenuLocal(int op);                           // Dispara a opção do menu de locais
void incluirLocal();                                   // Dispara a função para criar um local
TLocal criarLocal();                                   // Cria um local
void menuListarLocal();                                // Exibe o menu para listar locais
void OpcaoListarLocal();                               // Dispara a opção para listar locais
void listarLocais();                                   // Lista todos os locais
void exibeLocal(TLocal local);                         // Exibe um local
void OpcaoExcluirLocal();                              // Dispara a opção para excluir um local
void excluirLocal(int indice);                         // Exclui um local
void OpcaoAlterarLocal();                              // Dispara a opção para alterar um local
void menuAlterarLocal(int indice);                     // Exibe o menu de alteração de local
void alterarLocal(int op, int indice);                 // Altera um atributo de um local
void op_categoria();                                   // Dispara a função do menu de categorias
void menu_categoria();                                 // Exibe o menu de categorias
void OpcaoMenuCategoria(int op);                       // Dispara a opção do menu de categorias
void incluirCategoria();                               // Dispara a função para criar uma categoria
TCategoria criarCategoria();                           // Cria uma categoria
void alterarCategoria();                               // Altera uma categoria
void menuListarCategoria();                            // Exibe o menu para listar categorias
void listarCategorias();                               // Lista todas as categorias
void exibeCategoria(TCategoria categoria, int indice); // Exibe uma categoria
void OpcaoExcluirCategoria();                          // Dispara a opção para excluir uma categoria
void excluirCategoria(int indice);                     // Exclui uma categoria
void op_encontro();                                    // Dispara a função do menu de encontros
void menu_encontro();                                  // Exibe o menu de encontros
void OpcaoMenuEncontro(int op);                        // Dispara a opção do menu de encontros
void incluirEncontro();                                // Dispara a função para criar um encontro
TEncontro criarEncontro();                             // Cria um encontro
void OpcaoListarEncontro();                            // Dispara a função para listar encontros
void menuListarEncontro();                             // Exibe o menu para listar encontros
void listarEncontros();                                // Lista todos os encontros
void exibeEncontro(TEncontro encontro, int i);         // Exibe um encontro
void OpcaoExcluirEncontro();                           // Dispara a opção para excluir um encontro
void excluirEncontro(int indice);                      // Exclui um encontro
void digitarTitulo();                                  // Digita o titulo do programa
int validarEmail(char *email);                         // Valida um e-mail
int validarTelefone(char *telefone);                   // Valida um número de telefone
int validarData(int dia, int mes, int ano);            // Valida dia mês e ano
int validarHorario(int hora, int min);                 // Valida hora e minuto
void validaAlocacao(void *ptr);                        // Valida a alocação dinâmica
void mensagemError(int codigoErro);                    // Exibe uma mensagem de erro

/* Declaração de variáveis globais */
TAmigo *_amigos;
TLocal *_local;
TCategoria *_categoria;
TEncontro *_encontros;
int _numAmigos = 0;
int _numLocais = 0;
int _numCategorias = 0;
int _numEncontros = 0;

int main()
{
    int op;

    digitarTitulo();
    while (1)
    {
        menu();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        op_menu(op);
    }
}

void menu()
{
    system("cls");
    printf("-- Lista de Encontros -- \n");
    printf("1. Manter amigos\n");
    printf("2. Manter local\n");
    printf("3. Manter categoria\n");
    printf("4. Manter encontros\n");
    printf("5. Relatorios\n");
    printf("6. Sair\n\n");
    printf("Digite a opcao: ");
}

void op_menu(int op)
{
    switch (op)
    {
    case 1:
        op_amigo();
        break;
    case 2:
        op_local();
        break;
    case 3:
        op_categoria();
        break;
    case 4:
        op_encontro();
        break;
    case 5:
        op_relatorios();
        break;
    case 6:
        system("cls");
        printf("Saindo");
        for (int i = 0; i < 3; i++)
        {
            Sleep(700);
            printf(".");
        }
        exit(0);
    default:
        mensagemError(-9);
        system("pause");
        break;
    }
}

void op_encontro()
{
    int op;

    do
    {
        menu_encontro();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        OpcaoMenuEncontro(op);
    } while (op != 4);
}

void menu_encontro()
{
    system("cls");
    printf("1. Incluir encontro\n");
    printf("2. Alterar encontro\n");
    printf("3. excluir encontro\n");
    printf("4. Voltar\n");
    printf("Digite a opcao: ");
}

void OpcaoMenuEncontro(int op)
{
    switch (op)
    {
    case 1:
        incluirEncontro();
        break;
    case 2:
        // OpcaoAlterarEncontro();
        break;
    case 3:
        OpcaoExcluirEncontro();
        break;
    case 4:
        break;
    default:
        mensagemError(-9);
        system("pause");
        break;
    }
}

void incluirEncontro()
{
    if (_numAmigos == 0 || _numCategorias == 0 || _numLocais == 0)
    {
        mensagemError(-6);
        system("pause");
        return;
    }

    if (_numEncontros == 0)
    {
        _encontros = (TEncontro *)malloc(1 * sizeof(TEncontro));
    }
    else
    {
        _encontros = (TEncontro *)realloc(_encontros, (_numEncontros + 1) * sizeof(TEncontro));
    }
    validaAlocacao(_encontros);

    _encontros[_numEncontros] = criarEncontro();
    _numEncontros++;

    system("cls");
    printf("Encontro adcionado com sucesso!\n");
    sleep(1);
}

TEncontro criarEncontro()
{
    int indice;
    TEncontro encontro;
    char op = 'x', strAux[100];

    do
    {
        printf("Digite a data do encontro: ");
        scanf("%d%d%d", &encontro.data.dia, &encontro.data.mes, &encontro.data.ano);
    } while (validarData(encontro.data.dia, encontro.data.mes, encontro.data.ano));

    do
    {
        printf("Digite o horario do encontro: ");
        scanf("%d%d", &encontro.horario.hora, &encontro.horario.min);
    } while (validarHorario(encontro.horario.hora, encontro.horario.min));

    int aux = 0;
    encontro.numAmigos = 0;
    while (1)
    {
        do
        {
            listarAmigos();
            printf("Qual amigo deseja adcionar a este encontro [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &indice);
            fflush(stdin);

            if (indice < 1 || indice > _numAmigos)
            {
                mensagemError(-9);
            }

            for (int i = 0; i < encontro.numAmigos; i++)
            {
                if (encontro.amigos[i].id == _amigos[indice - 1].id)
                {
                    aux = 1;
                    break;
                }
            }

            if (aux)
            {
                mensagemError(-4);
            }
        } while (indice < 1 || indice > _numAmigos || aux);
        indice--;

        if (encontro.numAmigos == 0)
        {
            encontro.amigos = (TAmigo *)malloc(1 * sizeof(TAmigo));
        }
        else
        {
            encontro.amigos = (TAmigo *)realloc(encontro.amigos, (encontro.numAmigos + 1) * sizeof(TAmigo));
        }
        validaAlocacao(encontro.amigos);
        _amigos[encontro.numAmigos].id = encontro.numAmigos;
        encontro.amigos[encontro.numAmigos] = _amigos[indice];
        encontro.numAmigos++;

        if (encontro.numAmigos >= _numAmigos)
        {
            break;
        }

        do
        {
            printf("Deseja adcionar mais um amigo (S/N)? ");
            scanf("%c", &op);
            op = tolower(op);
            fflush(stdin);

            if (op != 'n' && op != 's')
            {
                mensagemError(-9);
            }
            else if (op == 'n')
            {
                break;
            }
        } while (op != 'n' && op != 's');
        system("cls");
    }

    do
    {
        listarLocais();
        printf("Onde vai ser o encontro [%d-%d]? ", 1, _numLocais);
        scanf("%d", &indice);
        fflush(stdin);
        system("cls");
    } while (indice < 1 || indice > _numLocais);
    indice--;
    encontro.local = _local[indice];
    _local[indice].id = 1;

    aux = 0;
    encontro.numCategorias = 0;
    while (1)
    {
        do
        {
            listarCategorias();
            printf("Qual categoria deseja adcionar a este encontro [%d-%d]? ", 1, _numCategorias);
            scanf("%d", &indice);
            fflush(stdin);

            if (indice < 1 || indice > _numCategorias)
            {
                mensagemError(-9);
            }

            for (int i = 0; i < encontro.numCategorias; i++)
            {
                if (encontro.categoria[i].id == _categoria[indice - 1].id)
                {
                    aux = 1;
                }
            }

            if (aux)
            {
                mensagemError(-15);
            }
        } while (indice < 1 || indice > _numCategorias || aux);
        indice--;

        if (encontro.numCategorias == 0)
        {
            encontro.categoria = (TCategoria *)malloc(1 * sizeof(TCategoria));
        }
        else
        {
            encontro.categoria = (TCategoria *)realloc(encontro.categoria, (encontro.numCategorias + 1) * sizeof(TCategoria));
        }
        validaAlocacao(encontro.categoria);
        encontro.categoria[encontro.numCategorias] = _categoria[indice];
        encontro.numCategorias++;
        _categoria[indice].id = 1;

        if (encontro.numCategorias >= _numCategorias)
        {
            break;
        }

        do
        {
            printf("Deseja adcionar mais uma categoria (S/N)? ");
            scanf("%c", &op);
            op = tolower(op);
            fflush(stdin);

            if (op != 'n' && op != 's')
            {
                mensagemError(-9);
            }
        } while (op != 'n' && op != 's');

        if (op == 'n')
        {
            break;
        }
        system("cls");
    }

    printf("Descricao do encontro: ");
    gets(strAux);
    encontro.descricao = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(encontro.descricao, strAux);

    return encontro;
}

void OpcaoListarEncontro()
{
    int op, indice;

    if (_numEncontros == 0)
    {
        mensagemError(-5);
        return;
    }

    if (_numEncontros > 1)
    {
        do
        {
            menuListarEncontro();
            scanf("%d", &op);
            fflush(stdin);

            if (op < 1 || op > 3)
            {
                mensagemError(-9);
            }
        } while (op < 1 || op > 3);
        system("cls");

        if (op == 1)
        {
            listarEncontros();
        }
        else if (op == 2)
        {
            do
            {
                printf("Qual encontro deseja exibir [%d-%d]? ", 1, _numEncontros);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;

                system("cls");
                if (indice >= 0 && indice <= _numEncontros)
                {
                    printf("-- Lista de Encontros [%d] --\n\n", indice + 1);
                    exibeEncontro(_encontros[indice], indice + 1);
                    system("pause");
                }
                else
                {
                    mensagemError(-10);
                }
            } while (indice < 1 && indice >= _numEncontros);
        }
        else if (op == 3)
        {
            return;
        }
    }
    else
    {
        listarEncontros();
    }
}

void menuListarEncontro()
{
    system("cls");
    printf("1. Listar TODOS os encontros\n");
    printf("2. Listar APENAS UM encontro\n");
    printf("3. Voltar\n\n");
    printf("Digite a opcao: ");
}

void listarEncontros()
{
    system("cls");
    printf("-- Lista de encontros [%d] --\n\n", _numEncontros);
    for (int i = 0; i < _numEncontros; i++)
    {
        exibeEncontro(_encontros[i], i + 1);
    }
    system("pause");
}

void exibeEncontro(TEncontro encontro, int i)
{
    printf("Encontro[%d]\n", i);
    printf("Local: %s\n", encontro.local.nome);
    printf("Categorias: ");
    for (int j = 0; j < encontro.numCategorias; j++)
    {
        if (j < encontro.numCategorias - 1)
        {
            printf("%s, ", encontro.categoria[j].nome);
        }
        else
        {
            printf("%s\n", encontro.categoria[j].nome);
        }
    }
    printf("Amigos: ");
    for (int k = 0; k < encontro.numAmigos; k++)
    {
        if (k < encontro.numAmigos - 1)
        {
            printf("%s (%s), ", encontro.amigos[k].nome, encontro.amigos[k].apelido);
        }
        else
        {
            printf("%s (%s)\n", encontro.amigos[k].nome, encontro.amigos[k].apelido);
        }
    }
    printf("Data: %.2d/%.2d/%d\n", encontro.data.dia, encontro.data.mes, encontro.data.ano);
    printf("Horario: %d:%d\n", encontro.horario.hora, encontro.horario.min);
    printf("Descricao: %s\n\n", encontro.descricao);
}

void OpcaoExcluirEncontro()
{
    int indice;
    char opSn;

    if (_numEncontros == 0)
    {
        mensagemError(-5);
        return;
    }

    if (_numEncontros > 1)
    {
        do
        {
            listarEncontros();
            printf("Qual encontro deseja excluir [%d-%d]? ", 1, _numEncontros);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numEncontros)
            {
                mensagemError(-10);
            }
            system("cls");
        } while (indice < 0 || indice >= _numEncontros);
    }
    else
    {
        indice = 0;
    }

    do
    {
        system("cls");
        exibeEncontro(_encontros[indice], indice);

        printf("\nConfirma a exclusao do encontro[%d] (S/N)? ", indice + 1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if (opSn != 's' && opSn != 'n')
        {
            mensagemError(-9);
        }
    } while (opSn != 's' && opSn != 'n');

    if (opSn == 's')
    {
        excluirEncontro(indice);
    }
    else
    {
        return;
    }

    system("cls");
    printf("Encontro excluido com sucesso!\n");
    sleep(1);
}

void excluirEncontro(int indice)
{
    for (int i = indice; i < _numEncontros; i++)
    {
        _encontros[i] = _encontros[i + 1];
    }
    _numEncontros--;
}

void op_categoria()
{
    int op;

    do
    {
        menu_categoria();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        OpcaoMenuCategoria(op);
    } while (op != 4);
}

void menu_categoria()
{
    system("cls");
    printf("1. Incluir categoria\n");
    printf("2. Alterar categoria\n");
    printf("3. Excluir categoria\n");
    printf("4. Voltar\n\n");
    printf("Digite a opcao: ");
}

void OpcaoMenuCategoria(int op)
{
    switch (op)
    {
    case 1:
        incluirCategoria();
        break;
    case 2:
        alterarCategoria();
        break;
    case 3:
        OpcaoExcluirCategoria();
        break;
    case 4:
        break;
    default:
        mensagemError(-9);
        break;
    }
}

void alterarCategoria()
{
    int indice;

    if (_numCategorias == 0)
    {
        mensagemError(-3);
        return;
    }

    if (_numCategorias > 1)
    {
        do
        {
            listarCategorias();
            printf("Qual categoria deseja alterar [%d-%d]? ", 1, _numCategorias);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numCategorias)
            {
                mensagemError(-10);
            }
            system("cls");
        } while (indice < 0 || indice >= _numCategorias);
    }
    else
    {
        indice = 0;
    }

    exibeCategoria(_categoria[indice], indice + 1);
    _categoria[indice] = criarCategoria();

    system("cls");
    printf("Categoria alterada com sucesso!\n");
    system("pause");
}

void incluirCategoria()
{
    char op;

    while (1)
    {
        system("cls");
        if (_numCategorias == 0)
        {
            _categoria = (TCategoria *)malloc(1 * sizeof(TCategoria));
        }
        else
        {
            _categoria = (TCategoria *)realloc(_categoria, (_numCategorias + 1) * sizeof(TCategoria));
        }
        validaAlocacao(_categoria);

        _categoria[_numCategorias] = criarCategoria();
        _numCategorias++;

        system("cls");
        printf("Categoria adcionada com sucesso!\n");

        printf("Deseja adcionar mias uma categoria (S/N)? ");
        scanf("%c", &op);
        op = tolower(op);
        fflush(stdin);

        if (op == 's')
        {
            continue;
        }
        else if (op == 'n')
        {
            break;
        }
        else
        {
            mensagemError(-9);
        }
    }
}

TCategoria criarCategoria()
{
    char strAux[100];
    TCategoria categoria;

    printf("Digite o nome da categoria: ");
    gets(strAux);
    categoria.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(categoria.nome, strAux);

    return categoria;
}

void OpcaoListarCategoria()
{
    int op, indice;

    if (_numCategorias == 0)
    {
        mensagemError(-16);
        return;
    }

    if (_numCategorias > 1)
    {
        do
        {
            menuListarCategoria();
            scanf("%d", &op);
            fflush(stdin);

            if (op < 1 || op > 3)
            {
                mensagemError(-9);
            }
        } while (op < 1 || op > 3);
        system("cls");

        if (op == 1)
        {
            listarCategorias();
        }
        else if (op == 2)
        {
            do
            {
                printf("Qual categoria deseja exibir [%d-%d]? ", 1, _numCategorias);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;

                system("cls");
                if (indice >= 0 && indice <= _numCategorias)
                {
                    printf("-- Lista de categorias [%d] --\n\n", indice + 1);
                    exibeCategoria(_categoria[indice], indice);
                    printf("\n");
                }
                else
                {
                    mensagemError(-10);
                }
            } while (indice < 1 && indice >= _numCategorias);
        }
        else if (op == 3)
        {
            return;
        }
    }
    else
    {
        listarCategorias();
    }
    system("pause");
}

void listarCategorias()
{
    printf("-- Lista de categorias [%d] --\n\n", _numCategorias);
    for (int i = 0; i < _numCategorias; i++)
    {
        exibeCategoria(_categoria[i], i);
    }
    printf("\n");
}

void exibeCategoria(TCategoria categoria, int indice)
{
    printf("[%d] - %s\n", indice + 1, categoria.nome);
}

void menuListarCategoria()
{
    system("cls");
    printf("1. Exibir TODAS as categorias\n");
    printf("2. Exibir APENAS UMA categoria\n");
    printf("3. Voltar\n\n");
    printf("Digite a opcao: ");
}

void OpcaoExcluirCategoria()
{
    int indice;
    char opSn;

    if (_numCategorias == 0)
    {
        mensagemError(-16);
        return;
    }

    if (_numCategorias > 1)
    {
        do
        {
            listarCategorias();
            printf("Qual categoria deseja excluir [%d-%d]? ", 1, _numCategorias);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numCategorias)
            {
                mensagemError(-10);
            }
            system("cls");
        } while (indice < 0 || indice >= _numCategorias);
    }
    else
    {
        indice = 0;
    }

    do
    {
        system("cls");
        exibeCategoria(_categoria[indice], indice);

        printf("\nConfirma a exclusao da categoria[%d] (S/N)? ", indice + 1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if (opSn != 's' && opSn != 'n')
        {
            mensagemError(-9);
        }
    } while (opSn != 's' && opSn != 'n');

    system("cls");
    if (opSn == 's')
    {
        if (_categoria[indice].id != 1)
        {
            excluirCategoria(indice);
        }
        else
        {
            mensagemError(-17);
            return;
        }
    }
    else
    {
        return;
    }

    printf("Categoria excluida com sucesso!\n");
    system("pause");
}

void excluirCategoria(int indice)
{
    for (int i = indice; i < _numCategorias; i++)
    {
        _categoria[i] = _categoria[i + 1];
    }
    _numCategorias--;
}

void op_relatorios()
{
    int op;

    do
    {
        menu_relatorios();
        scanf("%d", &op);

        system("cls");
        OpcaoMenuRelatorio(op);
    } while (op != 5);
}

void menu_relatorios()
{
    system("cls");
    printf("Relatorios\n");
    printf("1. Listar amigos\n");
    printf("2. Listar locais\n");
    printf("3. Listar encontros\n");
    printf("4. Relatorio por categoria\n");
    printf("5. Voltar\n\n");
    printf("Digite a opcao: ");
}

void OpcaoMenuRelatorio(int op)
{
    switch (op)
    {
    case 1:
        OpcaoListarAmigo();
        break;
    case 2:
        OpcaoListarLocal();
        break;
    case 3:
        OpcaoListarEncontro();
        break;
    case 4:
        OpcaoListarCategoria();
        break;
    case 5:
        break;
    default:
        mensagemError(-9);
        break;
    }
}

void op_local()
{
    int op;

    do
    {
        menu_local();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        OpcaoMenuLocal(op);
    } while (op != 4);
}

void menu_local()
{
    system("cls");
    printf("1. Incluir local\n");
    printf("2. Alterar local\n");
    printf("3. Excluir local\n");
    printf("4. Voltar\n\n");
    printf("Digite a opcao: ");
}

void incluirLocal()
{
    if (_numLocais == 0)
    {
        _local = (TLocal *)malloc(1 * sizeof(TLocal));
    }
    else
    {
        _local = (TLocal *)realloc(_local, (_numLocais + 1) * sizeof(TLocal));
    }
    validaAlocacao(_local);

    _local[_numLocais] = criarLocal();
    _numLocais++;

    system("cls");
    printf("Local adcionado com sucesso!\n");
    sleep(1);
}

TLocal criarLocal()
{
    TLocal local;
    char strAux[100];

    printf("Digite o nome do local: ");
    gets(strAux);
    local.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.nome, strAux);

    printf("Digite a cidade: ");
    gets(strAux);
    local.endereco.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.cidade, strAux);

    printf("Digite o bairro: ");
    gets(strAux);
    local.endereco.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.bairro, strAux);

    printf("Digite o logradouro: ");
    gets(strAux);
    local.endereco.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.logradouro, strAux);

    printf("Digite o numero: ");
    scanf("%d", &local.endereco.numero);
    fflush(stdin);

    return local;
}

void OpcaoAlterarLocal()
{
    int indice;

    if (_numLocais == 0)
    {
        mensagemError(-1);
        return;
    }

    if (_numLocais > 1)
    {
        do
        {
            listarLocais();
            printf("Qual local deseja alterar [%d-%d]? ", 1, _numLocais);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numLocais)
            {
                mensagemError(-9);
            }
            system("cls");
        } while (indice < 0 || indice >= _numLocais);
    }
    else
    {
        indice = 0;
    }

    menuAlterarLocal(indice);
}

void menuAlterarLocal(int indice)
{
    int op;

    do
    {
        system("cls");
        printf("-- Lista de locais [%d] --\n", indice);
        exibeLocal(_local[indice]);

        printf("Digite o atributo a alterar\n");
        printf("1. Nome\n");
        printf("2. Logradouro\n");
        printf("3. Cidade\n");
        printf("4. Bairro\n");
        printf("5. Numero\n");
        printf("6. Voltar\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        alterarLocal(op, indice);
    } while (op != 6);
}

void alterarLocal(int op, int indice)
{
    char strAux[100];

    switch (op)
    {
    case 1:
        printf("Digite o novo nome do local: ");
        gets(strAux);
        _local[indice].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_local[indice].nome, strAux);
        break;
    case 2:
        printf("Digite o novo logradouro: ");
        gets(strAux);
        _local[indice].endereco.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_local[indice].endereco.logradouro, strAux);
        break;
    case 3:
        printf("Digite a nova cidade: ");
        gets(strAux);
        _local[indice].endereco.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_local[indice].endereco.cidade, strAux);
        fflush(stdin);
        break;
    case 4:
        printf("Digite o novo bairro: ");
        gets(strAux);
        _local[indice].endereco.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_local[indice].endereco.bairro, strAux);
        break;
    case 5:
        printf("Digite o novo numero: ");
        scanf("%d", &_local[indice].endereco.numero);
        break;
    case 6:
        return;
    default:
        mensagemError(-9);
        break;
    }

    system("cls");
    printf("Local alterado com sucesso!\n");
    sleep(1);
}

void OpcaoExcluirLocal()
{
    int indice;
    char opSn;

    if (_numLocais == 0)
    {
        mensagemError(-1);
        return;
    }

    if (_numLocais > 1)
    {
        do
        {
            listarLocais();
            printf("Qual local deseja excluir [%d-%d]? ", 1, _numLocais);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numLocais)
            {
                mensagemError(-10);
            }
            system("cls");
        } while (indice < 0 || indice >= _numLocais);
    }
    else
    {
        indice = 0;
    }

    do
    {
        system("cls");
        exibeLocal(_local[indice]);

        printf("Confirma a exclusao do local[%d] (S/N)? ", indice + 1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if (opSn != 's' && opSn != 'n')
        {
            mensagemError(-9);
        }
    } while (opSn != 's' && opSn != 'n');

    if (opSn == 's')
    {
        if(_local[indice].id != 1){
            excluirLocal(indice);
        } else{
            mensagemError(-2);
        }
    }
    else
    {
        return;
    }

    system("cls");
    printf("Local excluido com sucesso!\n");
    sleep(1);
}

void excluirLocal(int indice)
{
    for (int i = indice; i < _numLocais; i++)
    {
        _local[i] = _local[i + 1];
    }
    _numLocais--;
}

void OpcaoListarLocal()
{
    int op, indice;

    if (_numLocais == 0)
    {
        mensagemError(-1);
        return;
    }

    if (_numLocais > 1)
    {
        do
        {
            menuListarLocal();
            scanf("%d", &op);
            fflush(stdin);

            if (op < 1 || op > 3)
            {
                mensagemError(-9);
            }
        } while (op < 1 || op > 3);
        system("cls");

        if (op == 1)
        {
            listarLocais();
        }
        else if (op == 2)
        {
            do
            {
                printf("Qual local deseja exibir [%d-%d]? ", 1, _numLocais);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;

                system("cls");
                if (indice >= 0 && indice <= _numLocais)
                {
                    printf("-- Lista de Locais [%d] --\n\n", indice + 1);
                    exibeLocal(_local[indice]);
                }
                else
                {
                    mensagemError(-10);
                }
            } while (indice < 1 && indice >= _numLocais);
        }
        else if (op == 3)
        {
            return;
        }
    }
    else
    {
        listarLocais();
    }
    system("pause");
}

void menuListarLocal()
{
    system("cls");
    printf("1. Exibir TODOS os locais\n");
    printf("2. Exibir APENAS UM local\n");
    printf("3. Voltar\n\n");
    printf("Digite a opcao: ");
}

void listarLocais()
{
    system("cls");
    printf("-- Lista de locais [%d] --\n\n", _numLocais);
    for (int i = 0; i < _numLocais; i++)
    {
        exibeLocal(_local[i]);
    }
}

void exibeLocal(TLocal local)
{
    printf("Nome: %s\n", local.nome);
    printf("Logradouro: %s\n", local.endereco.logradouro);
    printf("Cidade: %s\n", local.endereco.cidade);
    printf("Bairro: %s\n", local.endereco.bairro);
    printf("Numero: %d\n\n", local.endereco.numero);
}

void OpcaoMenuLocal(int op)
{
    switch (op)
    {
    case 1:
        incluirLocal();
        break;
    case 2:
        OpcaoAlterarLocal();
        break;
    case 3:
        OpcaoExcluirLocal();
        break;
    case 4:
        break;
    default:
        mensagemError(-9);
        break;
    }
}

void op_amigo()
{
    int op;

    do
    {
        menu_amigo();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        OpcaoMenuAmigo(op);
    } while (op != 4);
}

void menu_amigo()
{
    system("cls");
    printf("1. Incluir amigo\n");
    printf("2. Alterar amigo\n");
    printf("3. Excluir amigo\n");
    printf("4. Voltar\n\n");
    printf("Digite a opcao: ");
}

void OpcaoMenuAmigo(int op)
{
    switch (op)
    {
    case 1:
        incluirAmigo();
        break;
    case 2:
        OpcaoAlterarAmigo();
        break;
    case 3:
        OpcaoExcluirAmigo();
        break;
    case 4:
        break;
    default:
        mensagemError(-9);
        break;
    }
}

void incluirAmigo()
{
    if (_numAmigos == 0)
    {
        _amigos = (TAmigo *)malloc(1 * sizeof(TAmigo));
    }
    else
    {
        _amigos = (TAmigo *)realloc(_amigos, (_numAmigos + 1) * sizeof(TAmigo));
    }
    validaAlocacao(_amigos);

    _amigos[_numAmigos] = criarAmigo();
    _numAmigos++;

    system("cls");
    printf("Amigo adicionado com sucesso!\n");
    system("pause");
}

TAmigo criarAmigo()
{
    char strAux[100];
    TAmigo amigo;

    printf("Digite o nome do amigo: ");
    gets(strAux);
    amigo.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigo.nome, strAux);

    printf("Digite o apelido do amigo: ");
    gets(strAux);
    amigo.apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigo.apelido, strAux);

    do
    {
        printf("Digite a data de nascimento: ");
        scanf("%d%d%d", &amigo.nasc.dia, &amigo.nasc.mes, &amigo.nasc.ano);
        fflush(stdin);
    } while (validarData(amigo.nasc.dia, amigo.nasc.mes, amigo.nasc.ano) == 1);

    do
    {
        printf("Digite o e-mail do amigo: ");
        gets(strAux);
        amigo.email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(amigo.email, strAux);

        if (validarEmail(amigo.email) != 0)
        {
            printf("E-mail invalido!\n\n");
        }
    } while (validarEmail(amigo.email) != 0);

    do
    {
        printf("Digite o numero de telefone do amigo: ");
        gets(amigo.telefone);

        if (validarTelefone(amigo.telefone) == 1)
        {
            printf("Numero invalido!\n\n");
        }
    } while (validarTelefone(amigo.telefone) == 1);

    return amigo;
}

void OpcaoListarAmigo()
{
    int op, indice;

    if (_numAmigos == 0)
    {
        mensagemError(-3);
        return;
    }

    if (_numAmigos > 1)
    {
        do
        {
            menuListarAmigo();
            scanf("%d", &op);
            fflush(stdin);

            if (op < 1 || op > 3)
            {
                mensagemError(-9);
            }
        } while (op < 1 || op > 3);
        system("cls");

        if (op == 1)
        {
            listarAmigos();
        }
        else if (op == 2)
        {
            do
            {
                printf("Qual amigo deseja exibir [%d-%d]? ", 1, _numAmigos);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;

                if (indice >= 0 && indice <= _numAmigos)
                {
                    system("cls");
                    printf("-- Lista de amigos [%d] --\n\n", indice + 1);
                    exibeAmigo(_amigos[indice]);
                }
                else
                {
                    mensagemError(-10);
                }
            } while (indice < 1 && indice >= _numAmigos);
        }
        else if (op == 3)
        {
            return;
        }
    }
    else
    {
        listarAmigos();
    }
    system("pause");
}

void menuListarAmigo()
{
    system("cls");
    printf("1. Exibir TODOS os amigos\n");
    printf("2. Exibir APENAS UM amigo\n");
    printf("3. Voltar\n\n");
    printf("Digite a opcao: ");
}

void listarAmigos()
{
    system("cls");
    printf("-- Lista de amigos [%d] --\n\n", _numAmigos);
    for (int i = 0; i < _numAmigos; i++)
    {
        exibeAmigo(_amigos[i]);
    }
}

void exibeAmigo(TAmigo amigo)
{
    printf("Nome: %s\n", amigo.nome);
    printf("Apelido: %s\n", amigo.apelido);
    printf("Email: %s\n", amigo.email);
    printf("Telefone: +%c%c (%c%c) %c%c%c%c%c-%c%c%c%c\n\n", amigo.telefone[0], amigo.telefone[1], amigo.telefone[2], amigo.telefone[3], amigo.telefone[4], amigo.telefone[5], amigo.telefone[6], amigo.telefone[7], amigo.telefone[8], amigo.telefone[9], amigo.telefone[10], amigo.telefone[11], amigo.telefone[12]);
}

void OpcaoExcluirAmigo()
{
    int indice;
    char opSn;

    if (_numAmigos == 0)
    {
        mensagemError(-3);
        return;
    }

    if (_numAmigos > 1)
    {
        do
        {
            listarAmigos();
            printf("Qual amigo deseja excluir [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numAmigos)
            {
                mensagemError(-9);
                system("pause");
            }
            system("cls");
        } while (indice < 0 || indice >= _numAmigos);
    }
    else
    {
        indice = 0;
    }

    do
    {
        system("cls");
        exibeAmigo(_amigos[indice]);

        printf("Confirma a exclusao do amigo[%d] (S/N)? ", indice + 1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if (opSn != 's' && opSn != 'n')
        {
            mensagemError(-9);
            system("pause");
        }
    } while (opSn != 's' && opSn != 'n');

    if (opSn == 's')
    {
        excluirAmigoDeEncontros(indice);
        excluirAmigo(indice);
    }
    else
    {
        return;
    }

    system("cls");
    printf("Amigo excluido com sucesso!\n");
    sleep(1);
}

void excluirAmigo(int indice)
{
    for (int i = indice; i < _numAmigos; i++)
    {
        _amigos[i] = _amigos[i + 1];
    }
    _numAmigos--;
}

void excluirAmigoDeEncontros(int indice)
{
    int i, j, k, aux = 0;

    if (_numEncontros == 0)
    {
        return;
    }

    for (i = 0; i < _numEncontros; i++)
    {
        for (j = 0; j < _encontros[i].numAmigos; j++)
        {
            if (_encontros[i].amigos[j].id == _amigos[indice].id)
            {
                aux = 1;
                break;
            }
            else
            {
                aux = 0;
            }
        }

        if (aux == 1)
        {
            for (k = j; k < _encontros[i].numAmigos - 1; k++)
            {
                _encontros[i].amigos[k] = _encontros[i].amigos[k + 1];
            }
            _encontros[i].numAmigos--;
            j--;

            if ((_encontros[i].numAmigos + 1) == 1)
            {
                excluirEncontro(i);
                i--;
            }
        }
    }
}

void OpcaoAlterarAmigo()
{
    int indice;

    if (_numAmigos == 0)
    {
        mensagemError(-3);
        return;
    }

    if (_numAmigos > 1)
    {
        do
        {
            listarAmigos();
            printf("Qual amigo deseja alterar [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numAmigos)
            {
                mensagemError(-9);
            }
            system("cls");
        } while (indice < 0 || indice >= _numAmigos);
    }
    else
    {
        indice = 0;
    }

    MenuAlterarAmigo(indice);
}

void MenuAlterarAmigo(int indice)
{
    int op;

    do
    {
        printf("-- Lista de amigos[%d] --\n", indice + 1);
        exibeAmigo(_amigos[indice]);

        printf("Qual atributo deseja alterar?\n");
        printf("1. Nome\n");
        printf("2. Apelido\n");
        printf("3. Nascimento\n");
        printf("4. Email\n");
        printf("5. Numero\n");
        printf("6. Voltar\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        alterarAmigo(op, indice);
        system("cls");
    } while (op != 6);
}

void alterarAmigo(int op, int indice)
{
    char strAux[100];

    switch (op)
    {
    case 1:
        printf("Digite o novo nome do amigo: ");
        gets(strAux);
        _amigos[indice].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_amigos[indice].nome, strAux);
        break;
    case 2:
        printf("Digite o novo apelido do amigo: ");
        gets(strAux);
        _amigos[indice].apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_amigos[indice].apelido, strAux);
        break;
    case 3:
        do
        {
            printf("Digite a nova data de nascimento do amigo: ");
            scanf("%d%d%d", &_amigos[indice].nasc.dia, &_amigos[indice].nasc.mes, &_amigos[indice].nasc.ano);
            fflush(stdin);
        } while (validarData(_amigos[indice].nasc.dia, _amigos[indice].nasc.mes, _amigos[indice].nasc.ano) == 1);
        break;
    case 4:
        do
        {
            printf("Digite o novo email do amigo: ");
            gets(strAux);
            _amigos[indice].email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(_amigos[indice].email, strAux);
        } while (validarEmail(_amigos[indice].email) == 1);
        break;
    case 5:
        do
        {
            printf("Digite o numero de telefone do amigo: ");
            gets(_amigos[indice].telefone);
        } while (validarTelefone(_amigos[indice].telefone) == 1);
        break;
    case 6:
        return;
    default:
        mensagemError(-9);
        return;
    }

    system("cls");
    printf("Amigo alterado com sucesso!\n");
    sleep(1);
}

void digitarTitulo()
{
    char *palavra = "Ola Mundo!";

    system("cls");
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        printf("%c", palavra[i]);
        Sleep(100);
    }
    Sleep(700);
    palavra = "-- Lista de Encontros --";

    system("cls");
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        printf("%c", palavra[i]);
        Sleep(100);
    }
    printf("\n");
}

int validarEmail(char *email)
{
    int countA = 0, countB = 0, x = 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            countA++;
        }
        else if (email[i] == '.')
        {
            countB++;
        }
    }

    if (countA != 1 || countB < 1)
    {
        mensagemError(-11);
        x = 1;
    }

    return x;
}

int validarTelefone(char *telefone)
{
    int count = 0, x = 0, tam = strlen(telefone);

    for (int i = 0; telefone[i] != '\0'; i++)
    {
        if (isdigit(telefone[i]))
        {
            count++;
        }
    }

    if (count != tam || tam != 13)
    {
        mensagemError(-12);
        x = 1;
    }

    return x;
}

int validarData(int dia, int mes, int ano)
{
    int x = 0;

    if (ano <= 0)
    {
        x = 1;
    }
    else if ((mes <= 0) || (mes > 12))
    {
        x = 1;
    }

    if (mes == 2)
    {
        if (ano % 4 == 0)
        {
            if (dia > 29)
            {
                x = 1;
            }
        }
        else if (dia > 28)
        {
            x = 1;
        }
    }
    else if ((mes == 4) || (mes == 6) || (mes == 9) || (mes == 11))
    {
        if (dia > 30)
        {
            x = 1;
        }
    }
    else if ((dia > 31) || (dia <= 0))
    {
        x = 1;
    }

    if (x == 1)
    {
        mensagemError(-13);
    }

    return x;
}

int validarHorario(int hora, int min)
{
    int x = 0;

    if (hora < 0 || hora > 23)
    {
        x = 1;
    }
    else if (min < 0 || min > 59)
    {
        x = 1;
    }

    if (x == 1)
    {
        mensagemError(-14);
    }

    return x;
}

void validaAlocacao(void *ptr)
{
    if (!ptr)
    {
        mensagemError(-8);
        exit(1);
    }
}

void mensagemError(int codigoErro)
{
    switch (codigoErro)
    {
    case -1:
        printf("ERRO: Nenhum local adicionado!!!\n");
        break;
    case -2:
        printf("ERRO: Falha ao excluir local!!!\n");
        break;
    case -3:
        printf("ERRO: Nenhum amigo cadastrado!!!\n");
        break;
    case -4:
        mensagemError(-4);
        printf("ERRO: Amigo ja adicionado!!! Digite novamente!\n");
        break;
    case -5:
        printf("ERRO: Nenhum encontro cadastrado!!!\n");
        break;
    case -6:
        printf("ERRO: Falha ao incluir encontro!!!\n");
        break;
    case -7:
        printf("ERRO: Falha ao alterar encontro!!!\n");
        break;
    case -8:
        printf("ERRO: Falha ao alocar memoria!!!\n");
        break;
    case -9:
        printf("ERRO: Opcao invalida!!!\n");
        break;
    case -10:
        printf("ERRO: Indice invalido!!!\n");
        break;
    case -11:
        printf("ERRO: E-mail invalido!!!\n");
        break;
    case -12:
        printf("ERRO: Telefone invalido!!!\n");
        break;
    case -13:
        printf("ERRO: Data invalida!!! Digite novamente!\n");
        break;
    case -14:
        printf("ERRO: Horario invalido!!! Digite novamente!\n");
        break;
    case -15:
        printf("ERRO: Categoria ja adicionada!!! Digite novamente!\n");
        break;
    case -16:
        printf("ERRO: Nenhuma categoria cadastrada!!!\n");
        break;
    case -17:
        printf("ERRO: Falha ao excluir categoria!!!\n");
        break;
    default:
        printf("ERRO!!!\n");
        break;
    }

    system("pause");
}