#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 100

/* Declaração de estruturas */
typedef struct{
    int min;
    int seg;
} TTempo; // Struct tempo

typedef struct{
    char *titulo;
    char **artista;
    char *album;
    char **estilo;
    int  numArtista;
    int  numEstilo;
    TTempo duracao;
} TMusica; // Struct musica

/* Declaração de funções */
void menu(); // Exibe o menu
void op_menu(int option); // Executa a escolha do usuario
void op_listar(); // Dispara a opção para listar as musicas
void menu_listar(); // Exibe menu para listar musicas
void listarMusica(); // Exibe a playlist
void exibeMusica(TMusica playlist); // Exibe uma musica
void incluirMusica(); // Dispara a função de criar musica
TMusica criarMusica(); // Cria uma musica e adciona a playlist
void alterar_musica(); // Altera uma musica
int op_alterar(int op, int indice); // Dispara a opção de alteração
void menu_alterar(int opcao); // Exibe o menu de alteração
int OpAlterarArtista(int op, int indice); // Dispara a opção de alterar artista
int OpAlterarEstilo(int op, int indice); // Dispara a opção de alterar estilo
void listar_artista(int indice); // Lista os artistas
void adicionar_artista(int indice); // Adciona um novo artista
void alterar_artista(int indice); // Altera um artista
void excluir_artista(int indice); // Exclui um artista
void listar_estilo(int indice); // Lista os estilos
void adicionar_estilo(int indice); // Adciona um novo estilo
void alterar_estilo(int indice); // Altera um estilo
void excluir_estilo(int indice); // Exclui um estilo
void op_excluir(); // Dispara opção para excluir uma musica
void excluir_musica(int indice); // Exclui uma musica
int validarTempo(int min, int seg); // Valida o tempo
void limparMemoria(); // Limpa a memória alocada
void limparMusica(TMusica *music); // Limpa a memória das músicas
void limparArtista(TMusica *music); // Limpa a memória dos artistas
void limparGenero(TMusica *music); // Limpa a memória dos estilos
void salvar_arquivo(); // Salva os dados da playlist em arquivo
void carregar_arquivo(); // Carrega os dados da playlist em arquivo
void valida_alocacao(void *v); // Valida a alocação de memória

TMusica *_playList;
int _numMusicas = 0;

int main(){
    int op;

    carregar_arquivo();
    do{
        menu();

        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        op_menu(op);
    } while(op != 0);

    limparMemoria();
    return 0;
}

void menu(){
    system("cls");
    printf("- (1) Incluir musica\n");
    printf("- (2) Listar musicas\n");
    printf("- (3) Alterar musica\n");
    printf("- (4) Excluir musica\n");
    printf("- (0) Sair\n\n");
}

void op_menu(int option){
    switch(option){
    case 1:
        incluirMusica();
        break;
    case 2:
        op_listar();
        break;
    case 3:
        alterar_musica();
        break;
    case 4:
        op_excluir();
        break;
    case 0:
        printf("Saindo...\n");
        salvar_arquivo();
        break;
    default:
        printf("**ERRO! Opcao invalida!!!**");
        break;
    }
}

void op_excluir(){
    int indice;
    char opSn = 'x';

    if(_numMusicas == 0){
        printf("**Nao ha musicas na playlist!!!**\n");
        system("pause");
        return;
    }

    if(_numMusicas > 1){
        do{
            listarMusica();
            printf("** Qual musica deseja excluir [%d-%d]? ", 1, _numMusicas);
            scanf("%d", &indice);
            fflush(stdin);

            if(indice <= 0 && indice > _numMusicas){
                printf("Musica inexistente!!!");
            }
        } while(indice <= 0 && indice > _numMusicas);
    } else{
        indice = 1;
    }
    system("cls");

    indice--;
    printf("*** Musica [%d] ***\n", indice + 1);
    exibeMusica(_playList[indice]);
    while(opSn != 's' && opSn != 'n'){
        printf("Confirma a exclusao da musica [%d] (S/N)? ", indice+1);
        scanf("%c", &opSn);
        opSn = tolower(opSn);

        if(opSn != 's' && opSn != 'n'){
            printf("**Erro! Opcao invalida!**\n\n");
            continue;
        }

        system("cls");
        if(opSn == 's'){    
            excluir_musica(indice);
            printf("Musica exluida com sucesso!\n\n");
            system("pause");
        } else{
            return;
        }
    }
}

void excluir_musica(int indice){
    for(int i = indice; i < _numMusicas - 1; i++){
        _playList[i] = _playList[i + 1];
    }
    _numMusicas--;
    _playList = (TMusica*)realloc(_playList, _numMusicas * sizeof(TMusica));
}

void op_listar(){
    int indice, op;

    if(_numMusicas <= 0){
        printf("***Nao ha musicas na playlist***\n");
        system("pause");
        return;
    }

    if(_numMusicas == 1){
        exibeMusica(_playList[0]);
        system("pause");
        return;
    }

    while(1){
        menu_listar();
        scanf("%d", &op);
        fflush(stdin);
        system("cls");

        if(op == 1){
            listarMusica();
        } else if(op == 2){
            do{
                system("cls");
                printf("Qual musica deseja exibir [%d-%d]: ", 1, _numMusicas);
                scanf("%d", &indice);
                fflush(stdin);
                if(indice <= _numMusicas && indice >= 1){
                    system("cls");
                    printf("*** Musica [%d] ***\n", indice);
                    exibeMusica(_playList[indice - 1]);
                } else{
                    printf("***MUSICA INVALIDA!***\n\n");
                    system("pause");
                }
            } while(indice > _numMusicas || indice < 1);
        }else if(op == 3){
            return;
        }else{
            printf("***OPCAO INVALIDA***\n\n");
        }
        
        system("pause");
        system("cls");
    }
}

void menu_listar(){
    printf("- (1) Exibir TODAS as musicas\n");
    printf("- (2) Exibir APENAS UMA musica\n");
    printf("- (3) Voltar para o menu anterior\n\n");
    printf("** Digite a opcao: ");
}

void listarMusica(){
    for(int i = 0; i < _numMusicas; i++){
        printf("*** Musica [%d] ***\n", i+1);
        exibeMusica(_playList[i]);
    }
}

void exibeMusica(TMusica playList){
    if(_numMusicas <= 0){
        printf("***Nao ha musicas na playlist!!!***\n");
        system("pause");
        return;
    }

    printf("- Titulo: %s\n", playList.titulo);
    printf("- Album: %s\n", playList.album);

    printf("- Artista: ");
    for(int i = 0; i < playList.numArtista; i++){
        if(i < (playList.numArtista - 1)){
            printf("%s, ", playList.artista[i]);
        } else{
            printf("%s\n", playList.artista[i]);
        }
    }

    printf("- Estilo: ");
    for(int i = 0; i < playList.numEstilo; i++){
        if(i < (playList.numEstilo - 1)){
            printf("%s, ", playList.estilo[i]);
        } else{
            printf("%s\n", playList.estilo[i]);
        }
    }

    printf("- Duracao: %d:%d\n\n", playList.duracao.min, playList.duracao.seg);
}

void incluirMusica(){
    if(_numMusicas == 0){
        _playList = (TMusica *)malloc(1 * sizeof(TMusica));
    }
    else{
        _playList = (TMusica *)realloc(_playList, (_numMusicas + 1) * sizeof(TMusica));
    }
    valida_alocacao(&_playList[_numMusicas]);
    _playList[_numMusicas] = criarMusica();
    _numMusicas++;

    printf("\n** Musica adcionada com sucesso! **\n");
    system("pause");
}

TMusica criarMusica(){
    TMusica musica;
    char strAux[100], opSn;

    printf("- Titulo: ");
    gets(strAux);
    musica.titulo = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    valida_alocacao(musica.titulo);
    strcpy(musica.titulo, strAux);

    printf("- Album: ");
    gets(strAux);
    musica.album = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    valida_alocacao(musica.album);
    strcpy(musica.album, strAux);

    musica.numArtista = 0;
    while(1){
        printf("- Autor: ");
        gets(strAux);      

        if(musica.numArtista == 0){
            musica.artista = (char**)malloc(1 * sizeof(char*));
        } else{
            musica.artista = (char**)realloc(musica.artista, (musica.numArtista + 1) * sizeof(char*));
        }
        valida_alocacao(musica.artista);

        musica.artista[musica.numArtista] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(musica.artista[musica.numArtista], strAux);
        valida_alocacao(musica.artista[musica.numArtista]);
        musica.numArtista++;

        do{
            printf("** Deseja adicionar mais um artista (S/N)? ");
            scanf("%c", &opSn);
            fflush(stdin);
            opSn = tolower(opSn);

            if(opSn != 's' && opSn != 'n'){
                printf("**Erro! Opcao inexistente!**\n\n");
            }

            printf("\n");
        } while(opSn != 's' && opSn != 'n');

        if(opSn == 'N' || opSn == 'n'){
            break;
        }
    }

    musica.numEstilo = 0;
    while(1){
        printf("- Estilo: ");
        gets(strAux);

        if(musica.numEstilo == 0){
            musica.estilo = (char**)malloc(1 * sizeof(char*));
        } else{
            musica.estilo = (char**)realloc(musica.estilo, (musica.numEstilo + 1) * sizeof(char*));
        }
        valida_alocacao(musica.estilo);

        musica.estilo[musica.numEstilo] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(musica.estilo[musica.numEstilo], strAux);
        valida_alocacao(musica.estilo[musica.numEstilo]);
        musica.numEstilo++;

        do{
            printf("** Deseja adicionar mais um estilo (S/N)? ");
            scanf("%c", &opSn);
            fflush(stdin);
            opSn = tolower(opSn);

            if(opSn != 's' && opSn != 'n'){
                printf("**Erro! Opcao inexistente!**\n\n");
            }

            printf("\n");
        } while(opSn != 's' && opSn != 'n');

        if(opSn == 'N' || opSn == 'n'){
            break;
        }
    }

    do{
        printf("- Tempo (Min/Seg): ");
        scanf("%d%d", &musica.duracao.min, &musica.duracao.seg);
        fflush(stdin);
    } while(validarTempo(musica.duracao.min, musica.duracao.seg) == 0);

    return musica;
}

void alterar_musica(){
    int indice, op, aux;
    char opSn;

    if(_numMusicas == 0){
        printf("***Nao ha musicas na playlist!!!***\n");
        system("pause");
        return;
    }

    if(_numMusicas > 1){
        do{
            listarMusica();
            printf("** Digite o numero da musica a ser alterada [%d-%d]: ", 1, _numMusicas);
            scanf("%d", &indice);
            fflush(stdin);

            if(indice < 1 || indice > _numMusicas){
                printf("**Numero invalido!**\n");
                system("pause");
            }
            system("cls");
        } while(indice < 1 || indice > _numMusicas);
    } else{
        indice = 1;
    }
    indice--;

    while(1){
        system("cls");
        printf("*** Musica [%d] ***\n", indice + 1);
        exibeMusica(_playList[indice]);

        printf("Digite o atributo a alterar\n");
        printf("- (1) Titulo\n");
        printf("- (2) Album\n");
        printf("- (3) Artista\n");
        printf("- (4) Estilo\n");
        printf("- (5) Duracao\n");
        printf("- (0) Voltar ao menu anterior\n\n");
        printf("** Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);
        system("cls");

        aux = op_alterar(op, indice);

        system("cls");
        if(aux == 1){
            printf("Musica alterada com sucesso!\n\n");
        } 
        
        if(aux == -1 || aux == 1){
            opSn = 'x';
            while(opSn != 's' && opSn != 'n'){
                printf("Deseja alterar mais um atributo (S/N)? ");
                scanf("%c", &opSn);
                opSn = tolower(opSn);

                if(opSn == 'n'){
                    return;
                }
            }
        } else if(aux == -2){
            return;
        }
    }
}

int op_alterar(int op, int indice){
    char strAux[100];
    int option, x = 1;

    printf("***Musica [%d]***\n", indice+1);
    switch(op){
    case 0:
        x = -2;
        break;
    case 1:
        printf("- Titulo: %s\n\n", _playList[indice].titulo);
        printf("Digite o novo titulo da musica: ");
        gets(strAux);
        _playList[indice].titulo = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        valida_alocacao(_playList[indice].titulo);
        strcpy(_playList[indice].titulo, strAux);
        fflush(stdin);
        break;
    case 2:
        printf("- Album: %s\n\n", _playList[indice].album);
        printf("Digite o novo album da musica: ");
        gets(strAux);
        _playList[indice].album = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        valida_alocacao(_playList[indice].album);
        strcpy(_playList[indice].album, strAux);
        fflush(stdin);
        break;
    case 3:
        do{
            system("cls");
            menu_alterar(1);
            scanf("%d", &option);
            fflush(stdin);
            x = OpAlterarArtista(option, indice);
        } while(option != 0);
        break;
    case 4:
        do{
            system("cls");
            menu_alterar(2);
            scanf("%d", &option);
            fflush(stdin);
            x = OpAlterarEstilo(option, indice);
        } while(option != 0);
        break;
    case 5:
        printf("- Duracao: %d:%d\n\n", _playList[indice].duracao.min, _playList[indice].duracao.seg);
        do{
            printf("Digite a nova duracao da musica: ");
            scanf("%d%d", &_playList[indice].duracao.min, &_playList[indice].duracao.seg);
            fflush(stdin);
        } while(validarTempo(_playList[indice].duracao.min, _playList[indice].duracao.seg) == 0);
        break;
    default:
        system("cls");
        printf("**Opcao invalida!**\n");
        system("pause");
        x = -3;
    }

    return x;
}

void menu_alterar(int opcao){
    system("cls");
    switch(opcao){
        case 1:
            printf("- (1) Listar artistas\n");
            printf("- (2) Adicionar artista\n");
            printf("- (3) Alterar artista\n");
            printf("- (4) Excluir artista\n");
            printf("- (0) Voltar ao menu anterior\n\n");
            printf("** Digite a opcao: ");
            break;
        case 2:
            printf("- (1) Listar estilos\n");
            printf("- (2) Adicionar estilo\n");
            printf("- (3) Alterar estilo\n");
            printf("- (4) Excluir estilo\n");
            printf("- (0) Voltar ao menu anterior\n\n");
            printf("** Digite a opcao: ");
            break;
    }
}

int OpAlterarArtista(int op, int indice){
    switch(op){
        case 0:
            return -3;
        case 1:
            system("cls");
            listar_artista(indice);
            system("pause");
            return -3;
        case 2:
            system("cls");
            adicionar_artista(indice);
            break;
        case 3:
            system("cls");
            alterar_artista(indice);
            break;
        case 4:
            system("cls");
            excluir_artista(indice);
            break;
        default:
            printf("Opcao invalida!!!\n");
            break;
    }

    return 1;
}

int OpAlterarEstilo(int op, int indice){
    switch(op){
        case 0:
            return -3;
        case 1:
            system("cls");
            listar_estilo(indice);
            system("pause");
            return -3;
        case 2:
            system("cls");
            adicionar_estilo(indice);
            break;
        case 3:
            system("cls");
            alterar_estilo(indice);
            break;
        case 4:
            system("cls");
            excluir_estilo(indice);
            break;
        default:
            printf("Opcao invalida!!!\n");
            break;
    }

    return 1;
}

void listar_artista(int indice){
    printf("Lista de artistas:\n");
    for(int i = 0; i < _playList[indice].numArtista; i++){
        printf("[%d] - %s\n", i + 1, _playList[indice].artista[i]);
    }
    printf("\n");
}

void adicionar_artista(int indice){
    char strAux[100];

    printf("- Novo artista: ");
    gets(strAux);

    if(_playList[indice].numArtista == 0){
        _playList[indice].artista = (char**)malloc(1 * sizeof(char*));
    } else{
        _playList[indice].artista = (char**)realloc(_playList[indice].artista, (_playList[indice].numArtista + 1) * sizeof(char*));
    }
    valida_alocacao(_playList[indice].artista);

    _playList[indice].artista[_playList[indice].numArtista] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(_playList[indice].artista[_playList[indice].numArtista], strAux);
    valida_alocacao(_playList[indice].artista[_playList[indice].numArtista]);
    _playList[indice].numArtista++;

    system("cls");
    printf("Artista adicionado com sucesso!!!\n\n");
    system("pause");
}

void alterar_artista(int indice){
    char strAux[100];
    int op;

    if(_playList[indice].numArtista > 1){
        do{
            system("cls");
            listar_artista(indice);
            printf("Digite qual artista deseja alterar [%d-%d]: ", 1, _playList[indice].numArtista);
            scanf("%d", &op);
            fflush(stdin);

            if(op < 1 || op > _playList[indice].numArtista){
                system("cls");
                printf("Artista invalido!!!\n");
                system("pause");
            }
        } while(op < 1 || op > _playList[indice].numArtista);
        op--;
    } else{
        op = 0;
    }

    system("cls");
    printf("- Artista[%d]: %s\n", op+1, _playList[indice].artista[op]);

    printf("Digite o novo artista: ");
    gets(strAux);

    _playList[indice].artista[op] = malloc((strlen(strAux) + 1) * sizeof(char));
    valida_alocacao(_playList[indice].artista[op]);
    strcpy(_playList[indice].artista[op], strAux);

    system("cls");
    printf("Artista alterado com sucesso!\n\n");
    system("pause");
}

void excluir_artista(int indice){
    char opSn = 'x';
    int op;

    if(_playList[indice].numArtista == 1){
        printf("ERRO!!! Exclusao nao permitida!\n");
        system("pause");
        return;
    }

    do{
        listar_artista(indice);
        printf("** Qual artista deseja excluir [%d-%d]? ", 1, _playList[indice].numArtista);
        scanf("%d", &op);
        fflush(stdin);

        if(op <= 1 || op > _playList[indice].numArtista){
            printf("Artista inexistente!!!\n\n");
        }
    } while(op <= 1 || op > _playList[indice].numArtista);
    system("cls");

    op--;
    while(opSn != 's' && opSn != 'n'){
        printf("- Artista[%d]: %s\n", op+1, _playList[indice].artista[op]);
        printf("Confirma a exclusao do artista [%d] (S/N)? ", op+1);
        scanf("%c", &opSn);
        opSn = tolower(opSn);

        if(opSn != 's' && opSn != 'n'){
            printf("**Erro! Opcao invalida!**\n\n");
            continue;
        }

        if(opSn == 'n'){
            return;
        }
    }

    for(int i = op; i < _playList[indice].numArtista - 1; i++){
        _playList[indice].artista[i] = _playList[indice].artista[i + 1];
    }
    _playList[indice].numArtista--;

    system("cls");
    printf("Artista excluido com sucesso!!!\n\n");
    system("pause");
}

void listar_estilo(int indice){
    printf("Lista de estilos:\n");
    for(int i = 0; i < _playList[indice].numEstilo; i++){
        printf("[%d] - %s\n", i+1, _playList[indice].estilo[i]);
    }
    printf("\n");
}

void adicionar_estilo(int indice){
    char strAux[100];

    printf("- Novo estilo: ");
    gets(strAux);  

    if(_playList[indice].numEstilo == 0){
        _playList[indice].estilo = (char**)malloc(1 * sizeof(char*));
    } else{
        _playList[indice].estilo = (char**)realloc(_playList[indice].estilo, (_playList[indice].numEstilo + 1) * sizeof(char*));
    }
    valida_alocacao(_playList[indice].estilo);

    _playList[indice].estilo[_playList[indice].numEstilo] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(_playList[indice].estilo[_playList[indice].numEstilo], strAux);
    valida_alocacao(_playList[indice].estilo[_playList[indice].numEstilo]);
    _playList[indice].numEstilo++;

    system("cls");
    printf("Estilo adicionado com sucesso!!!\n\n");
    system("pause");
}

void alterar_estilo(int indice){
    char strAux[100];
    int op;

    if(_playList[indice].numEstilo > 1){
        do{
            system("cls");
            listar_estilo(indice);
            printf("Digite qual estilo deseja alterar [%d-%d]: ", 1, _playList[indice].numEstilo);
            scanf("%d", &op);
            fflush(stdin);

            if(op < 1 || op > _playList[indice].numEstilo){
                system("cls");
                printf("Estilo inexistente!!!\n");
                system("pause");
            }
        } while(op < 1 || op > _playList[indice].numEstilo);
        op--;
    } else{
        op = 0;
    }

    system("cls");
    printf("- Estilo[%d]: %s\n", op+1, _playList[indice].estilo[op]);

    printf("Digite o novo estilo: ");
    gets(strAux);

    _playList[indice].estilo[op] = malloc((strlen(strAux) + 1) * sizeof(char));
    valida_alocacao(_playList[indice].estilo[op]);
    strcpy(_playList[indice].estilo[op], strAux);

    system("cls");
    printf("Estilo alterado com sucesso!!!\n\n");
    system("pause");
}

void excluir_estilo(int indice){
    char opSn = 'x';
    int op;

    if(_playList[indice].numEstilo == 1){
        printf("ERRO!!! Exclusao nao permitida!\n\n");
        system("pause");
        return;
    }

    do{
        listar_estilo(indice);
        printf("** Qual estilo deseja excluir [%d-%d]? ", 1, _playList[indice].numEstilo);
        scanf("%d", &op);
        fflush(stdin);

        if(op <= 1 || op > _playList[indice].numEstilo){
            printf("Estilo inexistente!!!\n\n");
        }
    } while(op <= 1 || op > _playList[indice].numEstilo);
    system("cls");

    op--;
    while(opSn != 's' && opSn != 'n'){
        printf("- Estilo[%d]: %s\n", op+1, _playList[indice].estilo[op]);
        printf("Confirma a exclusao do estilo [%d] (S/N)? ", op+1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if(opSn != 's' && opSn != 'n'){
            printf("**Erro! Opcao invalida!**\n\n");
            continue;
        }

        if(opSn == 'n'){
            return;
        }
    }

    for(int i = op; i < _playList[indice].numEstilo - 1; i++){
        _playList[indice].estilo[i] = _playList[indice].estilo[i + 1];
    }
    _playList[indice].numEstilo--;

    system("cls");
    printf("Estilo excluido com sucesso!!!\n\n");
    system("pause");
}

int validarTempo(int min, int seg){
    int x = 1;

    if(min < 0){
        printf("**Erro ao inserir duracao!**\n\n");
        x = 0;
    } else if(seg >= 60 || seg < 0){
        printf("**Erro ao inserir duracao!**\n\n");
        x = 0;
    } else if(seg == 0 && min == 0){
        printf("**Erro ao inserir duracao!**\n\n");
        x = 0;
    }

    return x;
}

void limparMemoria(){
    for(int i = 0; i < _numMusicas; i++){
        limparMusica(&_playList[i]);
    }
    free(_playList);
}

void limparMusica(TMusica *music){
    free(music->titulo);
    free(music->album);
    limparArtista(music);
    limparGenero(music);
}

void limparArtista(TMusica *music){
    for(int i = 0; i < music->numArtista; i++){
        free(music->artista[i]);
    }
    free(music->artista);
}

void limparGenero(TMusica *music){
    for(int i = 0; i < music->numEstilo; i++){
        free(music->estilo[i]);
    }
    free(music->estilo);
}

void salvar_arquivo(){
    // Abertura do arquivo
    FILE *pArq = fopen("playlist.txt", "w");

    if(pArq == NULL){
        printf("***ERRO! ARQUIVO NAO ENCONTRADO!***\n");
        exit(1);
    }

    for(int i = 0; i < _numMusicas; i++){
        fprintf(pArq, "%s;", _playList[i].titulo);
        fprintf(pArq, "%s;", _playList[i].album);
        fprintf(pArq, "%d;", _playList[i].duracao.min);
        fprintf(pArq, "%d;", _playList[i].duracao.seg);

        for(int j = 0; j < _playList[i].numArtista; j++){
            fprintf(pArq, "%s@", _playList[i].artista[j]);
        }

        for(int j = 0; j < _playList[i].numEstilo; j++){
            fprintf(pArq, "%s#", _playList[i].estilo[j]);
        }
        fprintf(pArq, "%c", '\n');
    }

    printf("** Dados salvos com sucesso!!!\n");

    // Fechamento do arquivo
    fclose(pArq);
}

void carregar_arquivo(){
    int i, j, sep;
    char strAux[100], c;

    // Abertura do arquivo
    FILE *pArq = fopen("playlist.txt", "r");
    if(pArq){
        i = 0;
        sep = 0;

        while(!feof(pArq)){
            c = fgetc(pArq);
            if(c != ';' && c != '@' && c != '#' && c != '\n' && c != EOF){
                strAux[i] = c;
                i++;
            } else if(c == ';' || c == '@' || c == '#' || c == '\n'){
                strAux[i] = '\0';
                i = 0;

                if(c == ';'){
                    if(sep == 0){
                        if(_numMusicas == 0){
                            _playList = (TMusica*)malloc(1 * sizeof(TMusica));
                        } else{
                            _playList = (TMusica*)realloc(_playList, (_numMusicas + 1) * sizeof(TMusica));
                        }
                        valida_alocacao(_playList);

                        _playList[_numMusicas].titulo = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(_playList[_numMusicas].titulo, strAux);
                        _playList[_numMusicas].numArtista = 0;
                        _playList[_numMusicas].numEstilo = 0;
                        sep++;
                    } else if(sep == 1){
                        _playList[_numMusicas].album = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(_playList[_numMusicas].album, strAux);
                        sep++;
                    } else if(sep == 2){
                        _playList[_numMusicas].duracao.min = atoi(strAux);
                        sep++;
                    } else if(sep == 3){
                        _playList[_numMusicas].duracao.seg = atoi(strAux);
                        sep = 0;
                    }
                } else if(c == '@'){
                    if(sep == 0){
                        _playList[_numMusicas].artista = (char**)malloc(1 * sizeof(char*));
                        j = _playList[_numMusicas].numArtista;
                        _playList[_numMusicas].artista[j] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(_playList[_numMusicas].artista[j], strAux);
                        _playList[_numMusicas].numArtista++;
                    } else{
                        j = _playList[_numMusicas].numArtista;
                        _playList[_numMusicas].artista = (char**)realloc(_playList[_numMusicas].artista, (j + 1) * sizeof(char*));
                        _playList[_numMusicas].artista[j] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(_playList[_numMusicas].artista[j], strAux);
                        _playList[_numMusicas].numArtista++;
                    }
                    sep = -1;
                } else if(c == '#'){
                    if(sep == -1){
                        _playList[_numMusicas].estilo = (char**)malloc(1 * sizeof(char*));
                        j = _playList[_numMusicas].numEstilo;
                        _playList[_numMusicas].estilo[j] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(_playList[_numMusicas].estilo[j], strAux);
                        _playList[_numMusicas].numEstilo++;
                    } else{
                        j = _playList[_numMusicas].numEstilo;
                        _playList[_numMusicas].estilo = (char**)realloc(_playList[_numMusicas].estilo, (j + 1) * sizeof(char*));
                        _playList[_numMusicas].estilo[j] = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(_playList[_numMusicas].estilo[j], strAux);
                        _playList[_numMusicas].numEstilo++;
                    }
                    sep = -2;
                } else{
                    sep = 0;
                    _numMusicas++;
                }
            }
        }
    }

    // Fechamento do arquivo
    fclose(pArq);
}

void valida_alocacao(void *v){
    if(!v){
        printf("*********************************\n");
        printf("*** ERRO AO ALOCAR MEMORIA!!! ***\n");
        printf("*********************************\n");
        exit(1);
    }
}