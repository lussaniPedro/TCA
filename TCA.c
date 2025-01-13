#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

/* <Definição de macros> */
#define TD 13 // Tamanho da string de telefone
#define CLS (_WIN32 ? system("cls") : system("clear")); // Limpa o terminal
#define SPAUSE                                              \
    printf("Pressione qualquer tecla para continuar. . ."); \
    getch(); // Pausa o programa

#pragma GCC optimize("O3") // Otimiza o programa para uma execução mais rápida

/* <Declaração de structs> */
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
    char *estado;
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
    int numEncontros;
} TCategoria;

typedef struct
{
    TAmigo **amigos;
    int numAmigos;
    TCategoria **categorias;
    int numCategorias;
    TData data;
    THora horario;
    TLocal *local;
    char *descricao;
} TEncontro;

/* <Declaração de funções> */
/* Principal e papagaiadas */
void menu();                                            // Exibe o menu principal
void op_menu(int op);                                   // Dispara a opção do menu incial
void enviaDados();                                      // Envia os dados para o arquivo
void carregarDados();                                   // Carrega os dados em arquivo
void limparMemoria();                                   // Limpa a memória dos ponteiros
void digitarTitulo();                                   // Digita o titulo do programa
void mensagemError(int codigoErro);                     // Exibe uma mensagem de erro

/* Relatórios */
void menu_relatorios();                                  // Exibe o menu de relatórios
void op_relatorios();                                    // Dispara a função do menu de relatórios
void OpcaoMenuRelatorio(int op);                         // Dispara a opção do menu de relatórios

/* Manter amigo */
void op_amigo();                                         // Dispara a função do menu de amigos
void menu_amigo();                                       // Exibe o menu de amigos
void OpcaoMenuAmigo(int op);                             // Dispara a opção do menu de amigos
void incluirAmigo();                                     // Dispara a função para criar um amigo
TAmigo criarAmigo();                                     // Cria amigos
void OpcaoListarAmigo();                                 // Dispara a opção de listar amigos
void menuListarAmigo();                                  // Exibe o menu para listar amigos
void listarAmigos();                                     // Lista todos os amigos
void exibeAmigo(TAmigo amigo, int indice);               // Exibe um amigo
void OpcaoAlterarAmigo();                                // Dispara a opção para alterar amigo
void MenuAlterarAmigo(int indice);                       // Exibe o menu de alteração de amigo
void alterarAmigo(int op, int indice);                   // Altera um atributo de um amigo
void OpcaoExcluirAmigo();                                // Dispara a opção para excluir um amigo
void excluirAmigo(int indice);                           // Exclui um amigo
void excluirAmigoDeEncontros(int indice)  ;              // Exclui um amigo de todos os encontros
void limparAmigos();                                     // Limpa a memória dos amigos alocados
void salvarAmigos();                                     // Salva os amigos em arquivo
void carregarAmigos();                                   // carrega os amigos em arquivo

/* Manter local */
void op_local();                                         // Dispara a função do menu de locais
void menu_local();                                       // Exibe o menu de locais
void OpcaoMenuLocal(int op);                             // Dispara a opção do menu de locais
void incluirLocal();                                     // Dispara a função para criar um local
TLocal criarLocal();                                     // Cria um local
void menuListarLocal();                                  // Exibe o menu para listar locais
void OpcaoListarLocal();                                 // Dispara a opção para listar locais
void listarLocais();                                     // Lista todos os locais
void exibeLocal(TLocal local);                           // Exibe um local
void OpcaoExcluirLocal();                                // Dispara a opção para excluir um local
void excluirLocal(int indice);                           // Exclui um local
void OpcaoAlterarLocal();                                // Dispara a opção para alterar um local
void menuAlterarLocal(int indice);                       // Exibe o menu de alteração de local
void alterarLocal(int op, int indice);                   // Altera um atributo de um local
void limparLocais();                                     // Limpa a memória dos locais alocados
void salvarLocais();                                     // Salva os locais em arquivo
void carregarLocais();                                   // carrega os locais em arquivo

/* Manter categorias */
void op_categoria();                                     // Dispara a função do menu de categorias
void menu_categoria();                                   // Exibe o menu de categorias
void OpcaoMenuCategoria(int op);                         // Dispara a opção do menu de categorias
void incluirCategoria();                                 // Dispara a função para criar uma categoria
TCategoria criarCategoria();                             // Cria uma categoria
void alterarCategoria();                                 // Altera uma categoria
void OpcaoListarCategoria();                             // Dispara a opção para listar locais
void menuListarCategoria();                              // Exibe o menu para listar categorias
void listarCategorias();                                 // Lista todas as categorias
void exibeCategoria(TCategoria categoria, int indice);   // Exibe uma categoria
void OpcaoExcluirCategoria();                            // Dispara a opção para excluir uma categoria
void excluirCategoria(int indice);                       // Exclui uma categoria
void limparCategorias();                                 // Limpa a memória das categorias alocadas
void salvarCategorias();                                 // Salva os categorias em arquivo
void carregarCategorias();                               // carrega os categorias em arquivo

/* Manter encontro */
void op_encontro();                                      // Dispara a função do menu de encontros
void menu_encontro();                                    // Exibe o menu de encontros
void OpcaoMenuEncontro(int op);                          // Dispara a opção do menu de encontros
void incluirEncontro();                                  // Dispara a função para criar um encontro
TEncontro criarEncontro();                               // Cria um encontro
void OpcaoAlterarEncontro();                             // Dispara a opção para alterar encontro
void MenuAlterarEncontro(int indice);                    // Exibe o menu de alteração de encontros
void alterarEncontro(int op, int indice);                // Altera um encontro
void MenuAlterarAtributo(int indice, int i);             // Exibe o menu para alterar um atributo do encontro
void OpAlterarAmigosDeEncontros(int op, int indice);     // Dispara a opção para alterar amigos de um encontro
void OpExcluirAmigosDeEncontro(int indice);              // Dispara a opção para excluir um amigo de um encontro
void excluirAmigoDeEncontro(int index, int indice);      // Exclui um amigo de um encontro
void listarAmigosDeEncontros(int indice);                // Lista todos os amigos de um encontro
void incluirAmigosEmEncontros(int indice);               // Inclui amigos em um encontro
void alterarAmigosDeEncontros(int indice);               // Altera amigos de um encontro
void OpAlterarCategoriasDeEncontros(int op, int indice); // Dispara a opção para alterar categorias de um encontro
void OpExcluirCategoriasDeEncontro(int indice);          // Dispara a opção para excluir categorias de um encontro
void excluirCateoriasDeEncontro(int index, int indice);  // Exclui categorias de um encontro
void listarCategoriasDeEncontros(int indice);            // Lista todas as categorias de um encontro
void incluirCategoriasEmEncontros(int indice);           // Inclui categorias em um encontro
void alterarCategoriasDeEncontros(int indice);           // Altera categorias de um encontro
void OpcaoListarEncontro();                              // Dispara a função para listar encontros
void menuListarEncontro();                               // Exibe o menu para listar encontros
void listarEncontros();                                  // Lista todos os encontros
void exibeEncontro(TEncontro encontro, int i);           // Exibe um encontro
int menuListarEncontroPorCategoria();                    // Exibe o menu para listar encontros por categoria
void OpListarEncontroPorCategoria();                     // Dispara a função para listar encontros por categoria
void listarEncontrosPorCategoria();                      // Lista todos os encontros por categoria
void relatorioPorCategoria(int indice);                  // Relatório de encontros por categoria
void OpcaoExcluirEncontro();                             // Dispara a opção para excluir um encontro
void excluirEncontro(int indice);                        // Exclui um encontro
void limparEncontros();                                  // Limpa a memória dos encontros alocados
void salvarEncontros();                                  // Salva os encontros em arquivo
void carregarEncontros();                                // carrega os encontros em arquivo
void listarAmigosNaoInclusos(TEncontro encontro);        // Lista amigos não inclusos em um encontro
void listarCategoriasNaoInclusas(TEncontro encontro);    // Lista categorias não inclusas em um encontro

/* Validações */
int validarEmail(char *email);                           // Valida um e-mail
int validarTelefone(char *telefone);                     // Valida um número de telefone
int validarData(int dia, int mes, int ano);              // Valida dia mês e ano
int validarHorario(int hora, int min);                   // Valida hora e minuto
int validaSimNao(char op);                              // Valida uma opção de sim ou nao
void validaAlocacao(void *ptr);                          // Valida a alocação dinâmica

/* <Declaração de variáveis globais> */
TAmigo *_amigos;
int _numAmigos = 0;

TLocal *_local;
int _numLocais = 0;

TCategoria *_categorias;
int _numCategorias = 0;

TEncontro *_encontros;
int _numEncontros = 0;
    
/* <PRINCIPAL */
int main()
{
    int op;
    digitarTitulo();
    carregarDados();

    do
    {
        menu();
        scanf("%d", &op);
        fflush(stdin);

        op_menu(op);
    } while (op != 6);

    enviaDados();
    limparMemoria();
    return 0;
}

void menu()
{
    CLS
    printf("-- Lista de Encontros --\n\n");

    printf("------------------------\n");
    printf("- (1) Manter amigos\n");
    printf("- (2) Manter local\n");
    printf("- (3) Manter categoria\n");
    printf("- (4) Manter encontros\n");
    printf("- (5) Relatorios\n");
    printf("- (6) Sair\n");
    printf("------------------------\n\n");

    printf("** Digite a opcao: ");
}

void op_menu(int op)
{
    CLS
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
        CLS
        printf("Saindo");
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(700);
        }
        break;
    default:
        mensagemError(-9);
        SPAUSE
        break;
    }
}

void digitarTitulo()
{
    char *palavra = "Hello World!";

    CLS
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        printf("%c", palavra[i]); // Imprime a palavra letra por letra
        Sleep(70);
    }
    Sleep(700);

    for (int i = 0; i < 12; i++)
    {
        printf("\b \b"); // Apaga a palavra
        Sleep(70);
    }
    Sleep(700);

    palavra = "-- Lista de Encontros --";
    CLS
    for (int i = 0; palavra[i] != '\0'; i++)
    {
        printf("%c", palavra[i]); // Imprime a palavra letra por letra
        Sleep(70);
    }
    printf("\n");
}

/* <RELATORIOS */
void op_relatorios()
{
    int op;

    do
    {
        menu_relatorios();
        scanf("%d", &op);

        CLS
        OpcaoMenuRelatorio(op);
    } while (op != 6);
}

void menu_relatorios()
{
    CLS
    printf("-- Relatorios --\n");
    printf("- (1) Listar amigos\n");
    printf("- (2) Listar local\n");
    printf("- (3) Listar categoria\n");
    printf("- (4) Listar encontros\n");
    printf("- (5) Relatorio por categoria\n");
    printf("- (6) Voltar ao menu anterior\n\n");
    printf("** Digite a opcao: ");
}

void OpcaoMenuRelatorio(int op)
{
    CLS
    switch (op)
    {
    case 1:
        OpcaoListarAmigo();
        break;
    case 2:
        OpcaoListarLocal();
        break;
    case 3:
        OpcaoListarCategoria();
        break;
    case 4:
        OpcaoListarEncontro();
        break;
    case 5:
        OpListarEncontroPorCategoria();
        break;
    case 6:
        break;
    default:
        mensagemError(-9);
        SPAUSE
        break;
    }
}

/* <ENCONTROS> */
void op_encontro()
{
    int op;

    do
    {
        menu_encontro();
        scanf("%d", &op);
        fflush(stdin);

        CLS
        OpcaoMenuEncontro(op);
    } while (op != 4);
}

void menu_encontro()
{
    CLS
    printf("-- Manter encontro --\n");
    printf("- (1) Incluir encontro\n");
    printf("- (2) Alterar encontro\n");
    printf("- (3) Excluir encontro\n");
    printf("- (4) Voltar\n\n");
    printf("** Digite a opcao: ");
}

void OpcaoMenuEncontro(int op)
{
    switch (op)
    {
    case 1:
        incluirEncontro();
        break;
    case 2:
        OpcaoAlterarEncontro();
        break;
    case 3:
        OpcaoExcluirEncontro();
        break;
    case 4:
        break;
    default:
        mensagemError(-9);
        SPAUSE
        break;
    }
}

void incluirEncontro()
{
    if (_numAmigos == 0 || _numCategorias == 0 || _numLocais == 0)
    {
        mensagemError(-6);
        SPAUSE
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

    CLS
    printf("Encontro adcionado com sucesso!\n");
    SPAUSE
}

TEncontro criarEncontro()
{
    int indice, aux;
    TEncontro encontro;
    char op = 'x', strAux[100];

    do
    {
        printf("Digite a data do encontro: ");
        scanf("%d%d%d", &encontro.data.dia, &encontro.data.mes, &encontro.data.ano);
    } while (validarData(encontro.data.dia, encontro.data.mes, encontro.data.ano) == 1);

    do
    {
        printf("Digite o horario do encontro: ");
        scanf("%d%d", &encontro.horario.hora, &encontro.horario.min);
    } while (validarHorario(encontro.horario.hora, encontro.horario.min) == 1);

    encontro.numAmigos = 0;
    while (encontro.numAmigos < _numAmigos)
    {
        aux = 0;
        do  
        {
            listarAmigosNaoInclusos(encontro);
            printf("Qual amigo deseja adcionar ao encontro [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numAmigos)
            {
                mensagemError(-10);
                SPAUSE
            }
        } while (indice < 0 || indice >= _numAmigos);

        for (int i = 0; i < encontro.numAmigos; i++)
        {
            if (encontro.amigos[i]->id == _amigos[indice].id)
            {
                mensagemError(-20);
                SPAUSE
                aux = 1;
                break;
            }
        }

        if (aux == 1)
        {
            continue;
        }

        if (encontro.numAmigos == 0)
        {
            encontro.amigos = (TAmigo **)malloc(1 * sizeof(TAmigo*));
        }
        else
        {
            encontro.amigos = (TAmigo **)realloc(encontro.amigos, (encontro.numAmigos + 1) * sizeof(TAmigo*));
        }
        validaAlocacao(encontro.amigos);

        encontro.amigos[encontro.numAmigos] = &_amigos[indice];
        encontro.numAmigos++;

        if (encontro.numAmigos == _numAmigos)
        {
            break;
        }

        do
        {
            printf("Deseja adicionar outro amigo? [s/n]: ");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);
        } while (validaSimNao(op));

        if (op == 's')
        {
            continue;
        }
        else
        {
            break;
        }
    }

    do
    {
        listarLocais();
        printf("Qual local deseja adcionar ao encontro [%d-%d]? ", 1, _numLocais);
        scanf("%d", &indice);
        fflush(stdin);
        indice--;

        if (indice < 0 || indice >= _numLocais)
        {
            mensagemError(-9);
            SPAUSE
        }
    } while (indice < 0 || indice >= _numLocais);
    encontro.local = &_local[indice];

    encontro.numCategorias = 0;
    while (encontro.numCategorias < _numCategorias)
    {
        aux = 0;
        do
        {
            listarCategoriasNaoInclusas(encontro);
            printf("Qual categoria deseja adcionar ao encontro [%d-%d]? ", 1, _numCategorias);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numCategorias)
            {
                mensagemError(-10);
                SPAUSE
            }
        } while (indice < 0 || indice >= _numCategorias);

        for (int i = 0; i < encontro.numCategorias; i++)
        {
            if (encontro.categorias[i]->id == _categorias[indice].id)
            {
                mensagemError(-22);
                SPAUSE
                aux = 1;
                break;
            }
        }

        if (aux == 1)
        {
            continue;
        }

        if (encontro.numCategorias == 0)
        {
            encontro.categorias = (TCategoria **)malloc(1 * sizeof(TCategoria*));
        }
        else
        {
            encontro.categorias = (TCategoria **)realloc(encontro.categorias, (encontro.numCategorias + 1) * sizeof(TCategoria*));
        }
        validaAlocacao(encontro.categorias);

        encontro.categorias[encontro.numCategorias] = &_categorias[indice];
        encontro.numCategorias++;
        _categorias[indice].numEncontros++;

        if (encontro.numCategorias == _numCategorias)
        {
            break;
        }

        do
        {
            printf("Deseja adicionar outra categoria? [s/n]: ");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);
        } while (validaSimNao(op));

        if (op == 's')
        {
            continue;
        }
        else
        {
            break;
        }
    }

    CLS
    printf("Digite a descricao do encontro: ");
    gets(strAux);
    encontro.descricao = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(encontro.descricao, strAux);

    return encontro;
}

void listarAmigosNaoInclusos(TEncontro encontro){
    CLS
    printf("-- Lista de amigos [%d] --\n\n", (_numAmigos - encontro.numAmigos));
    for(int i = 0; i < _numAmigos; i++){
        int check = 0;
        for(int j = 0; j < encontro.numAmigos; j++){
            if(encontro.amigos[j]->id == _amigos[i].id){ // Verifica se o amigo esta incluso ao encontro
                check = 1;
                break;
            }
        }

        if(!check){ // Exibe caso o amigo nao esteja incluso
            exibeAmigo(_amigos[i], i);
        }
    }
}

void listarCategoriasNaoInclusas(TEncontro encontro){
    CLS
    printf("-- Lista de categorias [%d] --\n\n", (_numCategorias - encontro.numCategorias));
    for(int i = 0; i < _numCategorias; i++){
        int check = 0;
        for(int j = 0; j < encontro.numCategorias; j++){
            if(encontro.categorias[j]->id == _categorias[i].id){ // Verifica se a categoria esta inclusa ao encontro
                check = 1;
                break;
            }
        }

        if(!check){ // Exibe caso a categoria nao esteja inclusa
            exibeCategoria(_categorias[i], i);
        }
    }
}

void OpcaoAlterarEncontro()
{
    int indice;

    if (_numEncontros == 0)
    {
        mensagemError(-5);
        SPAUSE
        return;
    }

    if (_numEncontros > 1)
    {
        do
        {
            listarEncontros();
            printf("Qual encontro deseja alterar [%d-%d]? ", 1, _numEncontros);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if (indice < 0 || indice >= _numEncontros)
            {
                mensagemError(-9);
                SPAUSE
            }
            CLS
        } while (indice < 0 || indice >= _numEncontros);
    }
    else
    {
        indice = 0;
    }

    MenuAlterarEncontro(indice);
}

int menuListarEncontroPorCategoria()
{
    int op;

    do
    {
        printf("- (1) Listar os encontros de TODAS as categorias\n");
        printf("- (2) Listar os encontros de APENAS UMA categoria\n");
        printf("- (3) Voltar ao menu anterior\n\n");
        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        if (op < 1 || op > 3)
        {
            mensagemError(-9);
            SPAUSE
        }
    } while (op < 1 || op > 3);
    CLS

    return op;
}

void OpListarEncontroPorCategoria()
{
    int indice, op;
    char opSn;

    if (_numEncontros == 0)
    {
        mensagemError(-5);
        SPAUSE
        return;
    }

    if (_numCategorias > 1)
    {
        op = menuListarEncontroPorCategoria();

        if (op == 1)
        {
            for(int i = 0; i < _numCategorias; i++){
                printf("Categoria[%d - %s]: %d\n", i + 1, _categorias[i].nome, _categorias[i].numEncontros);
            }

            do{
                printf("Deseja exibir os encontros pelas categorias? [s/n]: ");
                scanf("%c", &opSn);
                fflush(stdin);
                opSn = tolower(opSn);
            } while(validaSimNao(opSn));

            if(opSn == 's'){
                listarEncontrosPorCategoria();
            }

            return;
        }
        else if (op == 2)
        {
            do
            {
                listarCategorias();
                printf("Qual categoria deseja listar? ");
                scanf("%d", &indice);
                fflush(stdin);
                indice--;

                if (indice < 0 || indice >= _numCategorias)
                {
                    mensagemError(-10);
                    SPAUSE
                }
            } while (indice < 0 || indice >= _numCategorias);
        }
        else
        {
            return;
        }
    }
    else
    {
        indice = 0;
    }

    relatorioPorCategoria(indice);
    SPAUSE
}

void listarEncontrosPorCategoria()
{
    printf("-- Relatorio de encontros por categoria --\n\n");
    for (int i = 0; i < _numCategorias; i++)
    {
        relatorioPorCategoria(i);
        printf("-------------------------------------------\n\n");
    }
    SPAUSE
}

void relatorioPorCategoria(int indice)
{
    if (_categorias[indice].numEncontros == 0)
    {
        printf("Categoria [%d - %s]: Ha %d encontros nesta categoria.\n\n", indice + 1, _categorias[indice].nome, _categorias[indice].numEncontros);
    } else {
        printf("Categoria [%d - %s]: Ha %d encontros nesta categoria:\n\n", indice + 1, _categorias[indice].nome, _categorias[indice].numEncontros);
        for (int i = 0; i < _numEncontros; i++){
            for (int j = 0; j < _encontros[i].numCategorias; j++){
                if (_encontros[i].categorias[j]->id == _categorias[indice].id){
                    exibeEncontro(_encontros[i], i + 1);
                }
            }
        }
    }
}

void MenuAlterarEncontro(int indice)
{
    int op;

    do
    {
        printf("-- Lista de encontros[%d] --\n", indice + 1);
        exibeEncontro(_encontros[indice], indice + 1);

        printf("Qual atributo deseja alterar?\n");
        printf("- (1) Data\n");
        printf("- (2) Horario\n");
        printf("- (3) Amigos\n");
        printf("- (4) Local\n");
        printf("- (5) Categorias\n");
        printf("- (6) Descricao\n");
        printf("- (7) Voltar para o menu anterior\n\n");
        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        alterarEncontro(op, indice);
        CLS
    } while (op != 7);
}

void alterarEncontro(int op, int indice)
{
    int index;
    char strAux[100];

    switch (op)
    {
    case 1:
        printf("Digite a nova data do encontro: ");
        scanf("%d%d%d", &_encontros[indice].data.dia, &_encontros[indice].data.mes, &_encontros[indice].data.ano);
        break;
    case 2:
        printf("Digite o novo horario do encontro: ");
        scanf("%d%d", &_encontros[indice].horario.hora, &_encontros[indice].horario.min);
        break;
    case 3:
        MenuAlterarAtributo(indice, 1);
        return;
    case 4:
        MenuAlterarAtributo(indice, 2);
        return;
    case 5:
        do
        {
            listarLocais();
            printf("Onde vai ser o novo local[%d-%d]? ", 1, _numLocais);
            scanf("%d", &index);
            fflush(stdin);
            CLS

            if (index < 1 || index > _numLocais)
            {
                mensagemError(-10);
                SPAUSE
            }
        } while (index < 1 || index > _numLocais);
        index--;
        _encontros[indice].local = &_local[index];
        _local[index].id = 1;
        break;
    case 6:
        printf("Digite a nova descricao do encontro: ");
        gets(strAux);
        _encontros[indice].descricao = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_encontros[indice].descricao, strAux);
        break;
    case 7:
        return;
    default:
        mensagemError(-9);
        SPAUSE
        return;
    }

    CLS
    printf("Encontro alterado com sucesso\n");
    SPAUSE
}

void MenuAlterarAtributo(int indice, int i)
{
    int op;

    do
    {
        switch (i)
        {
        case 1:
            CLS
            printf("- (1) Incluir amigo\n");
            printf("- (2) Alterar amigos\n");
            printf("- (3) Excluir amigos\n");
            printf("- (4) Listar amigos\n");
            printf("- (5) Voltar\n\n");
            printf("** Digite a opcao: ");
            scanf("%d", &op);
            fflush(stdin);

            OpAlterarAmigosDeEncontros(op, indice);
            break;
        case 2:
            CLS
            printf("- (1) Incluir categoria\n");
            printf("- (2) Alterar categoria\n");
            printf("- (3) Excluir categoria\n");
            printf("- (4) Listar categorias\n");
            printf("- (5) Voltar\n\n");
            printf("** Digite a opcao: ");
            scanf("%d", &op);
            fflush(stdin);

            OpAlterarCategoriasDeEncontros(op, indice);
            break;
        default:
            mensagemError(-9);
            SPAUSE
            break;
        }
    } while (op != 5);
}

void OpAlterarAmigosDeEncontros(int op, int indice)
{
    CLS
    switch (op)
    {
    case 1:
        incluirAmigosEmEncontros(indice);
        break;
    case 2:
        alterarAmigosDeEncontros(indice);
        break;
    case 3:
        OpExcluirAmigosDeEncontro(indice);
        break;
    case 4:
        listarAmigosDeEncontros(indice);
        break;
    case 5:
        break;
    default:
        mensagemError(-9);
        SPAUSE
        break;
    }
}

void alterarAmigosDeEncontros(int indice){
    int index, id, check = 0;
    char op;

    if(_encontros[indice].numAmigos == _numAmigos){
        mensagemError(-19);
        SPAUSE
        return;
    }

    while(1){
        if(_encontros[indice].numAmigos > 1){
            listarAmigosDeEncontros(indice);
            printf("Qual amigo deseja alterar ao encontro [%d-%d]? ", 1,_encontros[indice].numAmigos);
            scanf("%d", &index);
            fflush(stdin);
            index--;

            if (index < 0 || index >= _numAmigos)
            {
                mensagemError(-10);
                SPAUSE
                continue;
            }
        } else{
            index = 0;
        }

        do{
            CLS
            listarAmigos();
            printf("Qual amigo deseja adcionar ao encontro [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &id);
            fflush(stdin);
            id--;

            for(int i = 0; i < _encontros[indice].numAmigos; i++){
                if(_encontros[indice].amigos[i]->id == _amigos[id].id){
                    mensagemError(-20);
                    SPAUSE
                    check = 1;
                    break;
                }
            }

            if(id < 0 || id >= _numAmigos){
                mensagemError(-10);
                SPAUSE
            }
        } while(id < 0 || id >= _numAmigos || check);

        printf("Deseja realmente subistituir o(a) %s pelo(a) %s? (s/n) ", _amigos[index].nome, _amigos[id].nome);
        scanf("%c", &op);
        fflush(stdin);
        op = tolower(op);

        if(op == 's'){
            _encontros[indice].amigos[index] = &_amigos[id];
            break;
        } else if(op == 'n'){
            return;
        }
    }

    CLS
    printf("Amigo alterado com sucesso!!!\n");
    SPAUSE
}

void incluirAmigosEmEncontros(int indice)
{
    int index;
    char op;

    if (_encontros[indice].numAmigos == _numAmigos)
    {
        mensagemError(-19);
        SPAUSE
        return;
    }

    while (_encontros[indice].numAmigos < _numAmigos)
    {
        if(_encontros[indice].numAmigos < _numAmigos - 1){
            do
            {
                listarAmigosNaoInclusos(_encontros[indice]);
                printf("Qual amigo deseja adcionar ao encontro [%d-%d]? ", 1, (_numAmigos - _encontros[indice].numAmigos));
                scanf("%d", &index);
                fflush(stdin);
                index--;

                if (index < 0 || index >= (_numAmigos - _encontros[indice].numAmigos))
                {
                    mensagemError(-10);
                    SPAUSE
                }
            } while (index < 0 || index >= (_numAmigos - _encontros[indice].numAmigos));

            for (int i = 0; i < _encontros[indice].numAmigos; i++)
            {
                if (_encontros[indice].amigos[i]->id == _amigos[index].id)
                {
                    mensagemError(-20);
                    SPAUSE
                    return;
                }
            }
        } else{
            for (int i = 0; i < _encontros[indice].numAmigos; i++)
            {
                for(int j = 0; j < _numAmigos; j++){
                    if (_encontros[indice].amigos[i]->id != _amigos[j].id)
                    {
                        index = _amigos[j].id;
                    }
                }
            }
        }

        do{
            printf("Deseja adicionar o(a) %s ao encontro? (s/n) ", _amigos[index].nome);
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);
        } while(validaSimNao(op));

        if (op == 's')
        {
            return;
        }

        _encontros[indice].amigos = (TAmigo **)realloc(_encontros[indice].amigos, (_encontros[indice].numAmigos + 1) * sizeof(TAmigo *));
        validaAlocacao(_encontros[indice].amigos);

        _encontros[indice].amigos[_encontros[indice].numAmigos] = &_amigos[index];
        _encontros[indice].numAmigos++;

        if (_encontros[indice].numAmigos == _numAmigos)
        {
            break;
        }
        do
        {
            printf("Deseja adicionar outro amigo? [s/n]: ");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);
        } while (validaSimNao(op));

        if (op == 's')
        {
            continue;
        }
        else
        {
            break;
        }
    }

    CLS
    printf("Amigos adicionados com sucesso\n");
    SPAUSE
}

void listarAmigosDeEncontros(int indice)
{
    for (int i = 0; i < _encontros[indice].numAmigos; i++)
    {
        printf("[%d] - %s (%s)\n", i + 1, _encontros[indice].amigos[i]->nome, _encontros[indice].amigos[i]->apelido);
    }
    SPAUSE
}

void OpExcluirAmigosDeEncontro(int indice)
{
    int index;

    if (_encontros[indice].numAmigos > 0)
    {
        do
        {
            listarAmigosDeEncontros(indice);
            printf("Qual amigo deseja excluir [%d-%d]? ", 1, _encontros[indice].numAmigos);
            scanf("%d", &index);
            fflush(stdin);
            index--;

            if (index < 0 || index >= _encontros[indice].numAmigos)
            {
                mensagemError(-10);
                SPAUSE
            }
        } while (index < 0 || index >= _encontros[indice].numAmigos);
    }
    else
    {
        index = 0;
    }

    excluirAmigoDeEncontro(index, indice);

    CLS
    printf("Amigo excluido com sucesso\n");
    SPAUSE
}

void excluirAmigoDeEncontro(int index, int indice)
{
    for (int i = index; i < _encontros[indice].numAmigos; i++)
    {
        _encontros[indice].amigos[i] = _encontros[indice].amigos[i + 1];
    }
    _encontros[indice].numAmigos--;
}

void OpAlterarCategoriasDeEncontros(int op, int indice){
    CLS
    switch (op)
    {
    case 1:
        incluirCategoriasEmEncontros(indice);
        break;
    case 2:
        alterarCategoriasDeEncontros(indice);
        break;
    case 3:
        OpExcluirCategoriasDeEncontro(indice);
        break;
    case 4:
        listarCategoriasDeEncontros(indice);
        break;
    case 5:
        break;
    default:
        mensagemError(-9);
        SPAUSE
        break;
    }
}

void incluirCategoriasEmEncontros(int indice){
    int index;
    do{
        listarCategorias();
        printf("Qual categoria deseja incluir [%d-%d]? ", 1, _numCategorias);
        scanf("%d", &index);
        fflush(stdin);
        index--;

        if (index < 0 || index >= _numCategorias)
        {
            mensagemError(-10);
            SPAUSE
        }
    } while (index < 0 || index >= _numCategorias);

    _encontros[indice].categorias = (TCategoria **)realloc(_encontros[indice].categorias, (_encontros[indice].numCategorias + 1) * sizeof(TCategoria *));
    validaAlocacao(_encontros[indice].categorias);

    _encontros[indice].categorias[_encontros[indice].numCategorias] = &_categorias[index];
    _encontros[indice].numCategorias++;

    CLS
    printf("Categoria incluida com sucesso\n");
    SPAUSE
}

void alterarCategoriasDeEncontros(int indice){
    int index, id, check = 0;
    char op;

    if(_encontros[indice].numCategorias == _numCategorias){
        mensagemError(-19);
        SPAUSE
        return;
    }

    while(1){
        if(_encontros[indice].numCategorias > 1){
            listarCategoriasDeEncontros(indice);
            printf("Qual categoria do encontro deseja alterar [%d-%d]? ", 1,_encontros[indice].numCategorias);
            scanf("%d", &index);
            fflush(stdin);
            index--;

            if (index < 0 || index >= _numCategorias)
            {
                mensagemError(-10);
                SPAUSE
                continue;
            }
        } else{
            index = 0;
        }

        do{
            CLS
            listarCategorias();
            printf("Qual categoria deseja adcionar ao encontro [%d-%d]? ", 1, _numCategorias);
            scanf("%d", &id);
            fflush(stdin);
            id--;

            for(int i = 0; i < _encontros[indice].numCategorias; i++){
                if(_encontros[indice].categorias[i]->id == _categorias[id].id){
                    mensagemError(-22);
                    SPAUSE
                    check = 1;
                    break;
                }
            }

            if(id < 0 || id >= _numCategorias){
                mensagemError(-10);
                SPAUSE
            }
        } while(id < 0 || id >= _numCategorias || check);

        printf("Deseja realmente subistituir o(a) %s pelo(a) %s? (s/n) ", _categorias[index].nome, _categorias[id].nome);
        scanf("%c", &op);
        fflush(stdin);
        op = tolower(op);

        if(op == 's'){
            _encontros[indice].categorias[index] = &_categorias[id];
            break;
        } else if(op == 'n'){
            return;
        }
    }

    CLS
    printf("Categoria alterada com sucesso!!!\n");
    SPAUSE
}

void OpExcluirCategoriasDeEncontro(int indice)
{
    int index;

    if (_encontros[indice].numCategorias > 0)
    {
        do
        {
            listarCategoriasDeEncontros(indice);
            printf("Qual categoria deseja excluir [%d-%d]? ", 1, _encontros[indice].numCategorias);
            scanf("%d", &index);
            fflush(stdin);
            index--;

            if (index < 0 || index >= _encontros[indice].numCategorias)
            {
                mensagemError(-10);
                SPAUSE
            }
        } while (index < 0 || index >= _encontros[indice].numCategorias);
    }
    else
    {
        index = 0;
    }

    excluirAmigoDeEncontro(index, indice);

    CLS
    printf("Categoria excluida com sucesso\n");
    SPAUSE
}

void excluirCateoriasDeEncontro(int index, int indice)
{
    for (int i = index; i < _encontros[indice].numCategorias; i++)
    {
        _encontros[indice].categorias[i] = _encontros[indice].categorias[i + 1];
    }
    _encontros[indice].numCategorias--;
}

void listarCategoriasDeEncontros(int indice)
{
    for (int i = 0; i < _encontros[indice].numCategorias; i++)
    {
        printf("[%d] - %s\n", i + 1, _encontros[indice].categorias[i]->nome);
    }
    SPAUSE
}

void OpcaoListarEncontro()
{
    int op, indice;

    if (_numEncontros == 0)
    {
        mensagemError(-5);
        SPAUSE
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
                SPAUSE
            }
        } while (op < 1 || op > 3);
        CLS

        if (op == 1)
        {
            listarEncontros();
            SPAUSE
        }
        else if (op == 2)
        {
            do
            {
                printf("Qual encontro deseja exibir [%d-%d]? ", 1, _numEncontros);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;

                CLS
                if (indice >= 0 && indice <= _numEncontros)
                {
                    printf("-- Lista de Encontros [%d] --\n\n", indice + 1);
                    exibeEncontro(_encontros[indice], indice + 1);
                    SPAUSE
                }
                else
                {
                    mensagemError(-10);
                    SPAUSE
                }
            } while (indice < 1 && indice >= _numEncontros);
        }
        else
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
    CLS
    printf("1. Listar TODOS os encontros\n");
    printf("2. Listar APENAS UM encontro\n");
    printf("3. Voltar\n\n");
    printf("** Digite a opcao: ");
}

void listarEncontros()
{
    CLS
    printf("-- Lista de encontros [%d] --\n\n", _numEncontros);
    for (int i = 0; i < _numEncontros; i++)
    {
        exibeEncontro(_encontros[i], i + 1);
        printf("\n");
    }
}

void exibeEncontro(TEncontro encontro, int i)
{
    printf("Encontro[%d]:\n", i);
    printf("Local: %s, %s - %s\n", encontro.local->nome, encontro.local->endereco.cidade, encontro.local->endereco.estado);
    printf("Categorias: ");
    for (int j = 0; j < encontro.numCategorias; j++)
    {
        if (j < encontro.numCategorias - 1)
        {
            printf("%s, ", encontro.categorias[j]->nome);
        }
        else
        {
            printf("%s\n", encontro.categorias[j]->nome);
        }
    }
    printf("Amigos: ");
    for (int k = 0; k < encontro.numAmigos; k++)
    {
        if (k < encontro.numAmigos - 1)
        {
            printf("%s (%s), ", encontro.amigos[k]->nome, encontro.amigos[k]->apelido);
        }
        else
        {
            printf("%s (%s)\n", encontro.amigos[k]->nome, encontro.amigos[k]->apelido);
        }
    }
    printf("Data: %.2d/%.2d/%d\n", encontro.data.dia, encontro.data.mes, encontro.data.ano);
    printf("Horario: %d:%.2d\n", encontro.horario.hora, encontro.horario.min);
    printf("Descricao: %s\n\n", encontro.descricao);
}

void OpcaoExcluirEncontro()
{
    int indice;
    char op;

    if (_numEncontros == 0)
    {
        mensagemError(-5);
        SPAUSE
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
                SPAUSE
            }
            CLS
        } while (indice < 0 || indice >= _numEncontros);
    }
    else
    {
        indice = 0;
    }

    do
    {
        CLS
        exibeEncontro(_encontros[indice], indice);

        printf("\nConfirma a exclusao do encontro[%d] (S/N)? ", indice + 1);
        scanf("%c", &op);
        fflush(stdin);
        op = tolower(op);
    } while (validaSimNao(op));

    if (op == 's')
    {
        excluirEncontro(indice);
    }
    else
    {
        return;
    }

    CLS
    printf("Encontro excluido com sucesso!\n");
    SPAUSE
}

void excluirEncontro(int indice)
{
    for (int i = indice; i < _numEncontros; i++)
    {
        _encontros[i] = _encontros[i + 1];
    }
    _numEncontros--;
}

void salvarEncontros()
{
    FILE *eFile = fopen("encontros.txt", "w");

    if (eFile == NULL)
    {
        mensagemError(-18);
        SPAUSE
    }

    for (int i = 0; i < _numEncontros; i++)
    {
        fprintf(eFile, "%d;", _encontros[i].data.dia);
        fprintf(eFile, "%d;", _encontros[i].data.mes);
        fprintf(eFile, "%d;", _encontros[i].data.ano);
        fprintf(eFile, "%d;", _encontros[i].horario.hora);
        fprintf(eFile, "%d;",_encontros[i].horario.min);

        fprintf(eFile, "%d;", _encontros[i].local->id);
        fprintf(eFile, "%s;", _encontros[i].descricao);

        for (int j = 0; j < _encontros[i].numAmigos; j++)
        {
            fprintf(eFile, "%d@", _encontros[i].amigos[j]->id);
        }

        for (int k = 0; k < _encontros[i].numCategorias; k++)
        {
            fprintf(eFile, "%d#", _encontros[i].categorias[k]->id);
        }

        fprintf(eFile, "\n");
    }

    fclose(eFile);
}

void carregarEncontros()
{
    FILE *eFile = fopen("encontros.txt", "r");
    char strAux[100], c;
    int id, sep, i, j;

    if(eFile){
        i = 0;
        sep = 0;

        while(!feof(eFile)){
            c = fgetc(eFile);
            if(c != ';' && c != '@' && c != '#' && c != '\n' && c != EOF){
                strAux[i] = c;
                i++;
            } else if(c == ';' || c == '@' || c == '#' || c == '\n'){
                strAux[i] = '\0';
                i = 0;

                if(c == ';'){
                    if(sep == 0){
                        if(_numEncontros == 0){
                            _encontros = (TEncontro*)malloc(1 * sizeof(TEncontro));
                        } else{
                            _encontros = (TEncontro*)realloc(_encontros, (_numEncontros + 1) * sizeof(TEncontro));
                        }
                        validaAlocacao(_encontros);

                        _encontros[_numEncontros].numAmigos = 0;
                        _encontros[_numEncontros].numCategorias = 0;

                        _encontros[_numEncontros].data.dia = atoi(strAux);
                        sep++;
                    } else if(sep == 1){
                        _encontros[_numEncontros].data.mes = atoi(strAux);
                        sep++;
                    } else if(sep == 2){
                        _encontros[_numEncontros].data.ano = atoi(strAux);
                        sep++;
                    } else if(sep == 3){
                        _encontros[_numEncontros].horario.hora = atoi(strAux);
                        sep++;
                    } else if(sep == 4){
                        _encontros[_numEncontros].horario.min = atoi(strAux);
                        sep++;
                    } else if(sep == 5){
                        id = atoi(strAux);
                        _encontros[_numEncontros].local = &_local[id];
                        sep++;
                    } else if(sep == 6){
                        _encontros[_numEncontros].descricao = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_encontros[_numEncontros].descricao);
                        strcpy(_encontros[_numEncontros].descricao, strAux);
                        sep = 0;
                    }
                } else if(c == '@'){
                    if(_encontros[_numEncontros].numAmigos == 0){
                        _encontros[_numEncontros].amigos = (TAmigo**)malloc(1 * sizeof(TAmigo*));
                    } else{
                        _encontros[_numEncontros].amigos = (TAmigo**)realloc(_encontros[_numEncontros].amigos, (_encontros[_numEncontros].numAmigos + 1) * sizeof(TAmigo*));
                    }
                    validaAlocacao(_encontros[_numEncontros].amigos);

                    id = atoi(strAux);
                    j = _encontros[_numEncontros].numAmigos;

                    _encontros[_numEncontros].amigos[j] = &_amigos[id];
                    _encontros[_numEncontros].numAmigos++;
                } else if(c == '#'){
                    if(_encontros[_numEncontros].numCategorias == 0){
                        _encontros[_numEncontros].categorias = (TCategoria**)malloc(1 * sizeof(TCategoria*));
                    } else{
                        _encontros[_numEncontros].categorias = (TCategoria**)realloc(_encontros[_numEncontros].categorias, (_encontros[_numEncontros].numCategorias + 1) * sizeof(TCategoria*));
                    }
                    validaAlocacao(_encontros[_numEncontros].categorias);

                    id = atoi(strAux);
                    j = _encontros[_numEncontros].numCategorias;

                    _encontros[_numEncontros].categorias[j] = &_categorias[id];
                    _encontros[_numEncontros].numCategorias++;
                } else{
                    sep = 0;
                    _numEncontros++;
                }
            } 
        }
    }

    fclose(eFile);
}

/* <CATEGORIAS> */
void op_categoria()
{
    int op;

    do
    {
        menu_categoria();
        scanf("%d", &op);
        fflush(stdin);

        CLS
        OpcaoMenuCategoria(op);
    } while (op != 4);
}

void menu_categoria()
{
    CLS
    printf("1. Incluir categoria\n");
    printf("2. Alterar categoria\n");
    printf("3. Excluir categoria\n");
    printf("4. Voltar\n\n");
    printf("** Digite a opcao: ");
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
        SPAUSE
        break;
    }
}

void alterarCategoria()
{
    int indice;

    if (_numCategorias == 0)
    {
        mensagemError(-16);
        SPAUSE
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
                SPAUSE
            }
            CLS
        } while (indice < 0 || indice >= _numCategorias);
    }
    else
    {
        indice = 0;
    }

    exibeCategoria(_categorias[indice], indice + 1);
    _categorias[indice] = criarCategoria();

    CLS
    printf("Categoria alterada com sucesso!\n");
    SPAUSE
}

void incluirCategoria()
{
    char op;

    while (1)
    {
        CLS
        if (_numCategorias == 0)
        {
            _categorias = (TCategoria *)malloc(1 * sizeof(TCategoria));
        }
        else
        {
            _categorias = (TCategoria *)realloc(_categorias, _numCategorias * sizeof(TCategoria));
        }
        validaAlocacao(_categorias);

        _categorias[_numCategorias] = criarCategoria();
        _numCategorias++;

        CLS
        printf("Categoria adcionada com sucesso!\n");
        SPAUSE

        CLS
        printf("Deseja adcionar mais uma categoria (S/N)? ");
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
            SPAUSE
        }
    }
}

TCategoria criarCategoria()
{
    char strAux[100];
    TCategoria categoria;

    while(1){
        CLS
        int check = 1;
        printf("Digite o nome da categoria: ");
        gets(strAux);
        categoria.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(categoria.nome, strAux);

        for(int i = 0; i < _numCategorias; i++){
            if(strcmp(_categorias[i].nome, categoria.nome) == 0){
                mensagemError(-22);
                SPAUSE
                check = 0;
                break;
            }
        }

        if(check){
            break;
        }
    }

    categoria.id = _numCategorias;
    categoria.numEncontros = 0;

    return categoria;
}

void OpcaoListarCategoria()
{
    int op, indice;

    if (_numCategorias == 0)
    {
        mensagemError(-16);
        SPAUSE
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
                SPAUSE
            }
        } while (op < 1 || op > 3);
        CLS

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

                CLS
                if (indice >= 0 && indice <= _numCategorias)
                {
                    printf("-- Lista de categorias [%d] --\n\n", indice + 1);
                    exibeCategoria(_categorias[indice], indice);
                    printf("\n");
                }
                else
                {
                    mensagemError(-10);
                    SPAUSE
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
    SPAUSE
}

void listarCategorias()
{
    CLS
    printf("-- Lista de categorias [%d] --\n\n", _numCategorias);
    for (int i = 0; i < _numCategorias; i++)
    {
        exibeCategoria(_categorias[i], i);
    }
    printf("\n");
}

void exibeCategoria(TCategoria categoria, int indice)
{
    printf("[%d] - %s\n", indice + 1, categoria.nome);
}

void menuListarCategoria()
{
    CLS
    printf("1. Exibir TODAS as categorias\n");
    printf("2. Exibir APENAS UMA categoria\n");
    printf("3. Voltar\n\n");
    printf("** Digite a opcao: ");
}

void OpcaoExcluirCategoria()
{
    int indice;
    char op;

    if (_numCategorias == 0)
    {
        mensagemError(-16);
        SPAUSE
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
                SPAUSE
            }
            CLS
        } while (indice < 0 || indice >= _numCategorias);
    }
    else
    {
        indice = 0;
    }

    do
    {
        CLS
        exibeCategoria(_categorias[indice], indice);

        printf("\nConfirma a exclusao da categoria[%d] (S/N)? ", indice + 1);
        scanf("%c", &op);
        fflush(stdin);
        op = tolower(op);
    } while (validaSimNao(op));

    if (op == 's')
    {
        for (int i = 0; i < _numEncontros; i++)
        {
            for (int j = 0; j < _encontros[i].numCategorias; j++)
            {
                if (_categorias[indice].id == _encontros[i].categorias[j]->id)
                {
                    mensagemError(-17);
                    SPAUSE
                    printf("Categoria adicionada ao encontro: [%d]\n\n", i + 1);
                    SPAUSE
                    return;
                }
            }
        }
    }
    else
    {
        return;
    }

    excluirCategoria(indice);

    CLS
    printf("Categoria excluida com sucesso!\n");
    SPAUSE
}

void excluirCategoria(int indice)
{
    for (int i = indice; i < _numCategorias; i++)
    {
        _categorias[i] = _categorias[i + 1];
        _categorias[i].id--;
    }
    _numCategorias--;
}

void salvarCategorias()
{
    FILE *cFile = fopen("categorias.txt", "w");

    if (cFile == NULL)
    {
        mensagemError(-18);
        SPAUSE
    }

    for (int i = 0; i < _numCategorias; i++)
    {
        fprintf(cFile, "%s;", _categorias[i].nome);
        fprintf(cFile, "%d;%d;", _categorias[i].id, _categorias[i].numEncontros);
        fprintf(cFile, "\n");
    }

    fclose(cFile);
}

void carregarCategorias()
{
    char strAux[100], c;
    int sep, i;


    FILE *cFile = fopen("categorias.txt", "r");
    if(cFile){
        i = 0;
        sep = 0;

        while(!feof(cFile)){
            c = fgetc(cFile);
            if(c != ';' && c != '\n' && c != EOF){
                strAux[i] = c;
                i++;
            } else if(c == ';' || c == '\n'){
                strAux[i] = '\0';
                i = 0;

                if(c == ';'){
                    if(sep == 0){
                        if(_numCategorias == 0){
                            _categorias = (TCategoria*)malloc(1 * sizeof(TCategoria));
                        } else{
                            _categorias = (TCategoria*)realloc(_categorias, (_numCategorias + 1) * sizeof(TCategoria));
                        }
                        validaAlocacao(_categorias);

                        _categorias[_numCategorias].nome = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_categorias[_numCategorias].nome);
                        strcpy(_categorias[_numCategorias].nome, strAux);
                        sep++;
                    } else if(sep == 1){
                        _categorias[_numCategorias].id = atoi(strAux);
                        sep++;
                    } else if(sep == 2){
                        _categorias[_numCategorias].numEncontros = atoi(strAux);
                        sep++;
                    }
                } else if(c == '\n'){
                    sep = 0;
                    _numCategorias++;
                }
            }
        }
    }

    fclose(cFile);
}
/* </CATEGORIAS> */

/* <LOCAIS> */
void op_local()
{
    int op;

    do
    {
        menu_local();
        scanf("%d", &op);
        fflush(stdin);

        CLS
        OpcaoMenuLocal(op);
    } while (op != 4);
}

void menu_local()
{
    CLS
    printf("-- Manter local --\n");
    printf("- (1) Incluir local\n");
    printf("- (2) Alterar local\n");
    printf("- (3) Excluir local\n");
    printf("- (4) Voltar\n\n");
    printf("** Digite a opcao: ");
}

void incluirLocal()
{
    if (_numLocais == 0)
    {
        _local = (TLocal *)malloc(1 * sizeof(TLocal));
    }
    else
    {
        _local = (TLocal *)realloc(_local, _numLocais * sizeof(TLocal));
    }
    validaAlocacao(_local);

    _local[_numLocais] = criarLocal();
    _numLocais++;

    CLS
    printf("Local adcionado com sucesso!\n");
    SPAUSE
}

TLocal criarLocal()
{
    TLocal local;
    char strAux[100];

    printf("Digite o nome do local: ");
    gets(strAux);
    local.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.nome, strAux);

    printf("Digite o estado: ");
    gets(strAux);
    local.endereco.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.estado, strAux);

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

    do
    {
        printf("Digite o numero: ");
        scanf("%d", &local.endereco.numero);
        fflush(stdin);

        if(local.endereco.numero < 0){
            mensagemError(-23);
            SPAUSE
        }
    } while(local.endereco.numero < 0);

    local.id = _numLocais;

    return local;
}

void OpcaoAlterarLocal()
{
    int indice;

    if (_numLocais == 0)
    {
        mensagemError(-1);
        SPAUSE
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
                SPAUSE
            }
            CLS
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
        CLS
        printf("-- Lista de locais [%d] --\n", indice + 1);
        exibeLocal(_local[indice]);

        printf("Digite o atributo a alterar\n");
        printf("- (1) Nome\n");
        printf("- (2) Estado\n");
        printf("- (3) Cidade\n");
        printf("- (4) Bairro\n");
        printf("- (5) Logradouro\n");
        printf("- (6) Numero\n");
        printf("- (7) Voltar\n\n");
        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        CLS
        alterarLocal(op, indice);
    } while (op != 7);
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
        printf("Digite o novo estado: ");
        gets(strAux);
        _local[indice].endereco.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_local[indice].endereco.estado, strAux);
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
        printf("Digite o novo logradouro: ");
        gets(strAux);
        _local[indice].endereco.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(_local[indice].endereco.logradouro, strAux);
        break;
    case 6:
        do
        {
            printf("Digite o novo numero: ");
            scanf("%d", &_local[indice].endereco.numero);

            if(_local[indice].endereco.numero < 0){
                mensagemError(-23);
                SPAUSE
            }
        } while(_local[indice].endereco.numero < 0);
        break;
    case 7:
        return;
    default:
        mensagemError(-9);
        SPAUSE
        break;
    }

    CLS
    printf("Local alterado com sucesso!\n");
    SPAUSE
}

void OpcaoExcluirLocal()
{
    int indice;
    char op;

    if (_numLocais == 0)
    {
        mensagemError(-1);
        SPAUSE
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
                SPAUSE
            }
            CLS
        } while (indice < 0 || indice >= _numLocais);
    }
    else
    {
        indice = 0;
    }

    do
    {
        CLS
        exibeLocal(_local[indice]);

        printf("Confirma a exclusao do local[%d] (S/N)? ", indice + 1);
        scanf("%c", &op);
        fflush(stdin);
        op = tolower(op);
    } while (validaSimNao(op));

    if (op == 's')
    {
        for (int i = 0; i < _numEncontros; i++)
        {
            if (_local[indice].id == _encontros[i].local->id)
            {
                mensagemError(-2);
                SPAUSE
                printf("Local adicionado ao encontro: [%d]\n\n", i + 1);
                SPAUSE
                return;
            }
        }
    }
    else
    {
        return;
    }

    excluirLocal(indice);

    CLS
    printf("Local excluido com sucesso!\n");
    SPAUSE
}

void menuExcluirLocais()
{
    CLS
    printf("- (1) Excluir APENAS UM local\n");
    printf("- (2) Excluir TODOS os locais\n");
    printf("- (3) Voltar\n\n");
    printf("** Digite a opcao: ");
}

void excluirLocal(int indice)
{
    for (int i = indice; i < _numLocais; i++)
    {
        _local[i] = _local[i + 1];
        _local[i].id--;
    }
    _numLocais--;
}

void OpcaoListarLocal()
{
    int op, indice;

    if (_numLocais == 0)
    {
        mensagemError(-1);
        SPAUSE
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
                SPAUSE
            }
        } while (op < 1 || op > 3);
        CLS

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

                CLS
                if (indice >= 0 && indice <= _numLocais)
                {
                    printf("-- Lista de Locais [%d] --\n\n", indice + 1);
                    exibeLocal(_local[indice]);
                }
                else
                {
                    mensagemError(-10);
                    SPAUSE
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
    SPAUSE
}

void menuListarLocal()
{
    CLS
    printf("1. Exibir TODOS os locais\n");
    printf("2. Exibir APENAS UM local\n");
    printf("3. Voltar\n\n");
    printf("** Digite a opcao: ");
}

void listarLocais()
{
    CLS
    printf("-- Lista de locais [%d] --\n\n", _numLocais);
    for (int i = 0; i < _numLocais; i++)
    {
        exibeLocal(_local[i]);
    }
}

void salvarLocais()
{
    FILE *lFile = fopen("locais.txt", "w");

    if (lFile == NULL)
    {
        mensagemError(-18);
        SPAUSE
    }

    for (int i = 0; i < _numLocais; i++)
    {
        fprintf(lFile, "%s;", _local[i].nome);
        fprintf(lFile, "%s;", _local[i].endereco.bairro);
        fprintf(lFile, "%s;", _local[i].endereco.cidade);
        fprintf(lFile, "%s;", _local[i].endereco.logradouro);
        fprintf(lFile, "%s;", _local[i].endereco.estado);
        fprintf(lFile, "%d;", _local[i].endereco.numero);
        fprintf(lFile, "%d;", _local[i].id);
        fprintf(lFile, "\n");
    }

    fclose(lFile);
}

void carregarLocais()
{
    char strAux[100], c;
    int sep, i;

    FILE *lFile = fopen("locais.txt", "r");

    if(lFile){
        i = 0;
        sep = 0;

        while(!feof(lFile)){
            c = fgetc(lFile);
            if(c != ';' && c != '\n' && c != EOF){
                strAux[i] = c;
                i++;
            } else if(c == ';' || c == '\n' || c == EOF){
                strAux[i] = '\0';
                i = 0;

                if(c == ';'){
                    if(sep == 0){
                        if(_numLocais == 0){
                            _local = (TLocal*)malloc(1 * sizeof(TLocal));
                        } else{
                            _local = (TLocal*)realloc(_local, (_numLocais + 1) * sizeof(TLocal));
                        }
                        validaAlocacao(_local);

                        _local[_numLocais].nome = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_local[_numLocais].nome);
                        strcpy(_local[_numLocais].nome, strAux);
                        sep++;
                    } else if(sep == 1){
                        _local[_numLocais].endereco.bairro = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_local[_numLocais].endereco.bairro);
                        strcpy(_local[_numLocais].endereco.bairro, strAux);
                        sep++;
                    } else if(sep == 2){
                        _local[_numLocais].endereco.cidade = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_local[_numLocais].endereco.cidade);
                        strcpy(_local[_numLocais].endereco.cidade, strAux);
                        sep++;
                    } else if(sep == 3){
                        _local[_numLocais].endereco.logradouro = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_local[_numLocais].endereco.logradouro);
                        strcpy(_local[_numLocais].endereco.logradouro, strAux);
                        sep++;
                    } else if(sep == 4){
                        _local[_numLocais].endereco.estado = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_local[_numLocais].endereco.estado);
                        strcpy(_local[_numLocais].endereco.estado, strAux);
                        sep++;
                    } else if(sep == 5){
                        _local[_numLocais].endereco.numero = atoi(strAux);
                        sep++;
                    } else if(sep == 6){
                        _local[_numLocais].id = atoi(strAux);
                        sep++;
                    } else{
                        sep = 0;
                    }
                } else if(c == '\n'){
                    sep = 0;
                    _numLocais++;
                }
            }
        }
    }

    fclose(lFile);
}

void exibeLocal(TLocal local)
{
    printf("Nome: %s\n", local.nome);
    printf("Logradouro: %s\n", local.endereco.logradouro);
    printf("Cidade: %s\n", local.endereco.cidade);
    printf("Bairro: %s\n", local.endereco.bairro);
    printf("Estado: %s\n", local.endereco.estado);
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
        SPAUSE
        break;
    }
}

/* <AMIGOS> */
void op_amigo()
{
    int op;

    do
    {
        menu_amigo();
        scanf("%d", &op);
        fflush(stdin);

        CLS
        OpcaoMenuAmigo(op);
    } while (op != 4);
}

void menu_amigo()
{
    CLS
    printf("-- Manter amigo --\n");
    printf("- (1) Incluir amigo\n");
    printf("- (2) Alterar amigo\n");
    printf("- (3) Excluir amigo\n");
    printf("- (4) Voltar\n\n");
    printf("** Digite a opcao: ");
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
        SPAUSE
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

    CLS
    printf("Amigo adicionado com sucesso!\n");
    SPAUSE
}

TAmigo criarAmigo()
{
    char strAux[100];
    TAmigo amigo;

    while(1){
        int check = 1;

        printf("Digite o nome do amigo: ");
        gets(strAux);
        amigo.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(amigo.nome, strAux);

        for(int i = 0; i < _numAmigos; i++){
            if(strcmp(_amigos[i].nome, amigo.nome) == 0){
                check = 0;
                break;
            }
        }

        if(check){
            break;
        } else{
            mensagemError(-24);
            SPAUSE
        }
    }

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
    } while (validarEmail(amigo.email) != 0);

    do
    {
        printf("Digite o numero de telefone do amigo: ");
        gets(amigo.telefone);
    } while (validarTelefone(amigo.telefone) == 1);

    amigo.id = _numAmigos;

    for(int i = 0; i < _numEncontros; i++){
        for(int j = 0; j < _encontros[i].numAmigos; j++){
            printf("%d - %s: %d\n", i + 1, _encontros[i].amigos[j]->nome, _encontros[i].amigos[j]->id);
        }
    }
    SPAUSE

    return amigo;
}

void OpcaoListarAmigo()
{
    int op, indice;

    if (_numAmigos == 0)
    {
        mensagemError(-3);
        SPAUSE
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
                SPAUSE
            }
        } while (op < 1 || op > 3);
        CLS

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
                    CLS
                    printf("-- Lista de amigos [%d] --\n\n", indice + 1);
                    exibeAmigo(_amigos[indice], indice);
                }
                else
                {
                    mensagemError(-10);
                    SPAUSE
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
    SPAUSE
}

void menuListarAmigo()
{
    CLS
    printf("1. Exibir TODOS os amigos\n");
    printf("2. Exibir APENAS UM amigo\n");
    printf("3. Voltar\n\n");
    printf("** Digite a opcao: ");
}

void listarAmigos()
{
    CLS
    printf("-- Lista de amigos [%d] --\n\n", _numAmigos);
    for (int i = 0; i < _numAmigos; i++)
    {
        exibeAmigo(_amigos[i], i);
    }
}

void exibeAmigo(TAmigo amigo, int indice)
{
    printf("Amigo[%d]:\n", indice + 1);
    printf("Nome: %s\n", amigo.nome);
    printf("Apelido: %s\n", amigo.apelido);
    printf("Email: %s\n", amigo.email);
    printf("Data de nascimento: %.2d/%.2d/%d\n", amigo.nasc.dia, amigo.nasc.mes, amigo.nasc.ano);
    printf("Telefone: +%c%c (%c%c) %c%c%c%c%c-%c%c%c%c\n\n", amigo.telefone[0], amigo.telefone[1], amigo.telefone[2], amigo.telefone[3], amigo.telefone[4], amigo.telefone[5], amigo.telefone[6], amigo.telefone[7], amigo.telefone[8], amigo.telefone[9], amigo.telefone[10], amigo.telefone[11], amigo.telefone[12]);
}

void OpcaoExcluirAmigo()
{
    int indice;
    char op;

    if (_numAmigos == 0)
    {
        mensagemError(-3);
        SPAUSE
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
                SPAUSE
            }
            CLS
        } while (indice < 0 || indice >= _numAmigos);
    }
    else
    {
        indice = 0;
    }

    do
    {
        CLS
        exibeAmigo(_amigos[indice], indice);

        printf("Confirma a exclusao do amigo[%d] (S/N)? ", indice + 1);
        scanf("%c", &op);
        fflush(stdin);
        op = tolower(op);
    } while (validaSimNao(op));

    if (op == 's')
    {
        excluirAmigoDeEncontros(indice);
        excluirAmigo(indice);
    }
    else
    {
        return;
    }

    CLS
    printf("Amigo excluido com sucesso!\n");
    SPAUSE
}

void excluirAmigo(int indice)
{
    for (int i = indice; i < _numAmigos; i++)
    {
        _amigos[i] = _amigos[i + 1];
        _amigos[i].id--;
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
            if (_encontros[i].amigos[j]->id == _amigos[indice].id)
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

            if (_encontros[i].numAmigos == 0)
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
        SPAUSE
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
                SPAUSE
            }
            CLS
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
        exibeAmigo(_amigos[indice], indice);

        printf("Qual atributo deseja alterar?\n");
        printf("- (1) Nome\n");
        printf("- (2) Apelido\n");
        printf("- (3) Nascimento\n");
        printf("- (4) Email\n");
        printf("- (5) Numero\n");
        printf("- (6) Voltar\n\n");
        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        alterarAmigo(op, indice);
        CLS
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
        SPAUSE
        return;
    }

    CLS
    printf("Amigo alterado com sucesso!\n");
    SPAUSE
}

void salvarAmigos()
{
    FILE *aFile = fopen("amigos.txt", "w");

    if (aFile == NULL)
    {
        mensagemError(-18);
        SPAUSE
    }

    for (int i = 0; i < _numAmigos; i++)
    {
        fprintf(aFile, "%s;", _amigos[i].nome);
        fprintf(aFile, "%s;", _amigos[i].apelido);
        fprintf(aFile, "%d;%d;%d;", _amigos[i].nasc.dia, _amigos[i].nasc.mes, _amigos[i].nasc.ano);
        fprintf(aFile, "%s;", _amigos[i].email);
        fprintf(aFile, "%s;", _amigos[i].telefone);
        fprintf(aFile, "%d;", _amigos[i].id);
        fprintf(aFile, "\n");
    }

    fclose(aFile);
}

void carregarAmigos()
{
    int sep, i;
    char strAux[100], c;

    // Abertura de arquivo
    FILE *aFile = fopen("amigos.txt", "r");
    if(aFile){
        i = 0;
        sep = 0;

        while(!feof(aFile)){
            c = fgetc(aFile);
            if(c != ';' && c != '\n' && c != EOF){
                strAux[i] = c;
                i++;
            } else if(c == ';' || c == '\n'){
                strAux[i] = '\0';
                i = 0;

                if(c == ';'){
                    if(sep == 0){
                        if(_numAmigos == 0){
                            _amigos = (TAmigo*)malloc(1 * sizeof(TAmigo));
                        } else{
                            _amigos = (TAmigo*)realloc(_amigos, (_numAmigos + 1) * sizeof(TAmigo));
                        }
                        validaAlocacao(_amigos);

                        _amigos[_numAmigos].nome = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_amigos[_numAmigos].nome);
                        strcpy(_amigos[_numAmigos].nome, strAux);
                        sep++;
                    } else if(sep == 1){
                        _amigos[_numAmigos].apelido = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_amigos[_numAmigos].apelido);
                        strcpy(_amigos[_numAmigos].apelido, strAux);
                        sep++;
                    } else if(sep == 2){
                        _amigos[_numAmigos].nasc.dia = atoi(strAux);
                        sep++;
                    } else if(sep == 3){
                        _amigos[_numAmigos].nasc.mes = atoi(strAux);
                        sep++;
                    } else if(sep == 4){
                        _amigos[_numAmigos].nasc.ano = atoi(strAux);
                        sep++;
                    } else if(sep == 5){
                        _amigos[_numAmigos].email = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        validaAlocacao(_amigos[_numAmigos].email);
                        strcpy(_amigos[_numAmigos].email, strAux);
                        sep++;
                    } else if(sep == 6){
                        strcpy(_amigos[_numAmigos].telefone, strAux);
                        sep++;
                    } else if(sep == 7){
                        _amigos[_numAmigos].id = atoi(strAux);
                        sep = 0;
                    }
                } else{
                    sep = 0;
                    _numAmigos++;
                }
            }   
        }
    }
    fclose(aFile);
}

/* <MANIPULAÇÃO DE ARQUIVOS E MEMÓRIA> */
void enviaDados()
{
    salvarAmigos();
    salvarLocais();
    salvarCategorias();
    salvarEncontros();
}

void carregarDados()
{
    carregarAmigos();
    carregarCategorias();
    carregarLocais();
    carregarEncontros();
}

void limparMemoria()
{
    limparAmigos();
    limparCategorias();
    limparLocais();
    limparEncontros();
}

void limparAmigos()
{
    for (int i = 0; i < _numAmigos; i++)
    {
        free(_amigos[i].nome);
        free(_amigos[i].apelido);
        free(_amigos[i].email);
    }
    free(_amigos);
}

void limparCategorias()
{
    for (int i = 0; i < _numCategorias; i++)
    {
        free(_categorias[i].nome);
    }
    free(_categorias);
}

void limparLocais()
{
    for (int i = 0; i < _numLocais; i++)
    {
        free(_local[i].nome);
        free(_local[i].endereco.bairro);
        free(_local[i].endereco.cidade);
        free(_local[i].endereco.logradouro);
    }
    free(_local);
}

void limparEncontros()
{
    for (int i = 0; i < _numEncontros; i++)
    {
        free(_encontros[i].amigos);
        free(_encontros[i].categorias);
        free(_encontros[i].descricao);
    }
    free(_encontros);
}

/* <CONTROLE DE ERROS> */
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
        SPAUSE
        x = 1;
    }

    return x;
}

int validarLocal(TLocal local){
    int check = 0;

    for(int i = 0; i < _numLocais; i++){
        if(strcmp(local.nome, _local[i].nome) == 0 && strcmp(local.endereco.bairro, _local[i].endereco.bairro) == 0 && strcmp(local.endereco.cidade, _local[i].endereco.cidade) == 0 && strcmp(local.endereco.logradouro, _local[i].endereco.logradouro) == 0 && local.endereco.numero == _local[i].endereco.numero){
            check = 1;
        }
    }

    if(check){
        mensagemError(-25);
        SPAUSE
    }

    return check;    
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
        SPAUSE
        x = 1;
    }

    return x;
}

int validaSimNao(char op){
    int x = 0;

    if(op != 's' && op != 'S' && op != 'n' && op != 'N'){
        x = 1;
    }

    if(x){
        mensagemError(-19);
        SPAUSE
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
        SPAUSE
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
        SPAUSE
    }

    return x;
}

void validaAlocacao(void *ptr)
{
    if (!ptr)
    {
        mensagemError(-8);
        SPAUSE
    }
}

void mensagemError(int codigoErro)
{
    CLS
    switch (codigoErro)
    {
    case -1:
        printf("ERRO: Nenhum local adicionado!!!\n");
        break;
    case -2:
        printf("ERRO: Falha ao excluir local!!!\n");
        return;
    case -3:
        printf("ERRO: Nenhum amigo cadastrado!!!\n");
        break;
    case -4:
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
        printf("***ERRO: Falha ao alocar memoria***\n");
        exit(1);
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
    case -16:
        printf("ERRO: Nenhuma categoria cadastrada!!!\n\n");
        break;
    case -17:
        printf("ERRO: Falha ao excluir categoria!!!\n");
        return;
    case -18:
        printf("***ERRO: Falha ao criar arquivo***\n\n");
        exit(1);
    case -19:
        printf("ERRO: Todos os amigos ja inclusos!!!\n\n");
        break;
    case -20:
        printf("ERRO: Amigo ja incluso neste encontro!!!\n\n");
        break;
    case -21:
        printf("ERRO: Falha ao excluir amigo!!!\n\n");
        break;
    case -22:
        printf("ERRO: Categoria ja cadastrada!!!\n");
        break;
    case -23:
        printf("ERRO: Numero invalido!!!\n\n");
        break;
    case -24:
        printf("ERRO: Amigo ja cadastrado!!!\n");
        break;
    case -25:
        printf("ERRO: Local ja cadastrado!!!\n");
        break;
    default:
        printf("UNKNOWN ERROR!!!\n\n");
        exit(1);
    }
}