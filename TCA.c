#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    int hora;
    int min;
} THora;

typedef struct{
    int dia;
    int mes;
    int ano;
} TData;

typedef struct{
    char *logradouro;
    char *rua;
    char *bairro;
    char *cidade;
    int numero;
} TEndereco;

typedef struct{
    char *nome;
    TEndereco endereco;
} TLocal;

typedef struct{
    char *nome;
    char *apelido;
    char *email;
    char telefone[13];
    TData nasc;
} TAmigo;

typedef struct{
    char **nome;
} TCategoria;

typedef struct{
    TData data;
    THora horario;
    TAmigo amigos;
    TCategoria categoria;
    char *descricao;
} TEncontro;

/* Declaração de funções */
void menu();
void op_menu(int op);
void op_relatorios();
void menu_relatorios();
void OpcaoMenuRelatorio(int op);
void op_amigo();
void menu_amigo();
void OpcaoMenuAmigo(int op);
void incluirAmigo();
TAmigo criaAmigo();
void OpcaoListarAmigo();
void menuListarAmigo();
void listarAmigos();
void exibeAmigo(TAmigo amigo);
void OpcaoAlterarAmigo();
void MenuAlterarAmigo(int indice);
void alterarAmigo(int op, int indice);
void OpcaoExcluirAmigo();
void excluirAmigo(int indice);
void op_local();
void menu_local();
void OpcaoMenuLocal(int op);
void incluirLocal();
TLocal criarLocal();
void menuListarLocal();
void OpcaoListarLocal();
void listarLocais();
void exibeLocal(TLocal local);
void OpcaoExcluirLocal();
void excluirLocal(int indice);
void OpcaoAlterarLocal();
void menuAlterarLocal(int indice);
void alterarLocal(int op, int indice);
// void op_evento();
// void op_encontro();
int validarEmail(char *email);
int validarTelefone(char *telefone);
int validarData(int dia, int mes, int ano);
void validaAlocacao(void *ptr);

/* Declaração de variáveis globais */
TAmigo *_amigos;
TLocal *_local;
TEncontro *_encontros;
int _numAmigos = 0;
int _numLocais = 0;
int _numEncontros = 0;

int main(){
    int op;

    do{
        menu();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        op_menu(op);
    } while(op != 6);

    return 0;
}

void menu(){
    system("cls");
    printf("1. Manter amigos\n");
    printf("2. Manter local\n");
    printf("3. Manter categoria\n");
    printf("4. Manter encontros\n");
    printf("5. Relatorios\n");
    printf("6. Sair\n\n");
    printf("Digite a opcao: ");
}

void op_menu(int op){
    switch(op){
        case 1:
            op_amigo();
            break;
        case 2:
            op_local();
            break;
        case 3:
            // op_categoria();
            break;
        case 4:
            // op_encontro();
            break;
        case 5:
            op_relatorios();
            break;
        case 6:
            printf("Saindo...");
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            break;
    }
}

void op_relatorios(){
    int op;

    do{
        menu_relatorios();
        scanf("%d", &op);

        system("cls");
        OpcaoMenuRelatorio(op);
    } while(op != 5);
}

void menu_relatorios(){
    system("cls");
    printf("Relatorios\n");
    printf("1. Listar amigos\n");
    printf("2. Listar locais\n");
    printf("3. Listar encontros\n");
    printf("4. Relatorio por categoria\n");
    printf("5. Sair\n\n");
    printf("Digite a opcao: ");
}

void OpcaoMenuRelatorio(int op){
    switch(op){
        case 1:
            OpcaoListarAmigo();
            break;
        case 2:
            OpcaoListarLocal();
            break;
        case 3:
            // OpcaoListarEncontro();
            break;
        case 4:
            // OpcaoListarCategoria();
            break;
        case 5:
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            break;
    }
}

void op_local(){
    int op;

    do{
        menu_local();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        OpcaoMenuLocal(op);
    } while(op != 4);
}

void menu_local(){
    system("cls");
    printf("1. Incluir local\n");
    printf("2. Alterar local\n");
    printf("3. Excluir local\n");
    printf("4. Voltar\n\n");
    printf("Digite a opcao: ");
}

void incluirLocal(){
    if(_numLocais == 0){
        _local = (TLocal*)malloc(1 * sizeof(TLocal));
    } else{
        _local = (TLocal*)realloc(_local, (_numLocais + 1) * sizeof(TLocal));
    }
    _local[_numLocais] = criarLocal();
    _numLocais++;

    system("cls");
    printf("Local adcionado com sucesso!\n");
    system("pause");
}

TLocal criarLocal(){
    TLocal local;
    char strAux[100];

    printf("Digite o nome do local: ");
    gets(strAux);
    local.nome = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.nome, strAux);

    printf("Digite o logradouro: ");
    gets(strAux);
    local.endereco.logradouro = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.logradouro, strAux);

    printf("Digite a cidade: ");
    gets(strAux);
    local.endereco.cidade = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.cidade, strAux);

    printf("Digite o bairro: ");
    gets(strAux);
    local.endereco.bairro = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.bairro, strAux);

    printf("Digite a rua: ");
    gets(strAux);
    local.endereco.rua = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(local.endereco.rua, strAux);

    printf("Digite o numero: ");
    scanf("%d", &local.endereco.numero);
    fflush(stdin);

    return local;
}

void OpcaoAlterarLocal(){
    int indice;

    if(_numLocais == 0){
        printf("** Nenhum local cadastrado!!! **\n");
        system("pause");
        return;
    }

    if(_numLocais > 1){
        do{
            listarLocais();
            printf("Qual local deseja alterar [%d-%d]? ", 1, _numLocais);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if(indice < 0 || indice >= _numLocais){
                printf("Opcao invalida!!\n");
                system("pause");
            }
            system("cls");
        } while(indice < 0 || indice >= _numLocais);
    } else{
        indice = 0;
    }

    menuAlterarLocal(indice);
}

void menuAlterarLocal(int indice){
    int op;

    do{
        system("cls");
        printf("-- Lista de locais [%d] --\n", indice);
        exibeLocal(_local[indice]);

        printf("Digite o atributo a alterar\n");
        printf("1. Nome\n");
        printf("2. Logradouro\n");
        printf("3. Cidade\n");
        printf("4. Bairro\n");
        printf("5. Rua\n");
        printf("6. Numero\n");
        printf("7. Voltar\n\n");
        printf("Digite a opcao: ");
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        alterarLocal(op, indice);
    } while(op != 7);
}

void alterarLocal(int op, int indice){
    char strAux[100];

    switch(op){
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
            printf("Digite a nova rua: ");
            gets(strAux);
            _local[indice].endereco.rua = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(_local[indice].endereco.rua, strAux);
            break;
        case 6:
            printf("Digite o novo numero: ");
            scanf("%d", &_local[indice].endereco.numero);
            break;
        case 7:
            return;
        default:
            printf("Opcao invalida!!!\n\n");
            system("pause");
            break;
    }

    system("cls");
    printf("Local alterado com sucesso!\n");
    system("pause");
}

void OpcaoExcluirLocal(){
    int indice;
    char opSn;

    if(_numLocais == 0){
        printf("** Nenhum local cadastrado!!! **\n");
        system("pause");
        return;
    }

    if(_numLocais > 1){
        do{
            listarLocais();
            printf("Qual local deseja excluir [%d-%d]? ", 1, _numLocais);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if(indice < 0 || indice >= _numLocais){
                printf("\nOpcao invalida!!\n");
                system("pause");
            }
            system("cls");
        } while(indice < 0 || indice >= _numLocais);
    } else{
        indice = 0;
    }

    do{
        system("cls");
        exibeLocal(_local[indice]);

        printf("Confirma a exclusao do local[%d] (S/N)? ", indice + 1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if(opSn != 's' && opSn != 'n'){
            printf("\nOpcao invalida!!\n");
            system("pause");
        }
    } while(opSn != 's' && opSn != 'n');

    if(opSn == 's'){
        excluirLocal(indice);
        _numLocais--;
    } else{
        return;
    }

    system("cls");
    printf("Local excluido com sucesso!\n");
    system("pause");    
}

void excluirLocal(int indice){
    for(int i = indice; i < _numLocais; i++){
        _local[i] = _local[i + 1];
    }
}

void OpcaoListarLocal(){
    int op, indice;

    if(_numLocais == 0){
        printf("** Nenhum local adcionado!!! **\n");
        system("pause");
        return;
    }

    do{
        menuListarLocal();
        scanf("%d", &op);
        fflush(stdin);

        if(op < 1 || op > 3){
            printf("Opcao invalida!!\n\n");
        }
    } while(op < 1 || op > 3);
    system("cls");

    if(op == 2){
        do{
            if(_numLocais > 1){
                printf("Qual local deseja exibir [%d-%d]? ", 1, _numLocais);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;
            } else{
                indice = 0;
            }
            system("cls");
            if(indice >= 0 && indice <= _numLocais){
                printf("-- Lista de Locais [%d] --\n\n", indice + 1);
                exibeLocal(_local[indice]);
            } else{
                printf("Indice invalido!!\n\n");
            }
        } while(indice < 1 && indice >= _numLocais);
    } else if(op == 3){
        return;
    } else{
        listarLocais();
    }
    system("pause");
}

void menuListarLocal(){
    system("cls");
    printf("1. Exibir TODOS os locais\n");
    printf("2. Exibir APENAS UM local\n");
    printf("3. Voltar\n\n");
    printf("Digite a opcao: ");
}

void listarLocais(){
    printf("-- Lista de locais [%d] --\n\n", _numLocais);
    for(int i = 0; i < _numLocais; i++){
        exibeLocal(_local[i]);
    }
}

void exibeLocal(TLocal local){
    printf("Nome: %s\n", local.nome);
    printf("Logradouro: %s\n", local.endereco.logradouro);
    printf("Cidade: %s\n", local.endereco.cidade);
    printf("Bairro: %s\n", local.endereco.bairro);
    printf("Rua: %s\n", local.endereco.rua);
    printf("Numero: %d\n\n", local.endereco.numero);
}

void OpcaoMenuLocal(int op){
    switch(op){
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
            printf("Opcao invalida!\n");
            system("pause");
            break;
    }
}

void op_amigo(){
    int op;

    do{
        menu_amigo();
        scanf("%d", &op);
        fflush(stdin);

        system("cls");
        OpcaoMenuAmigo(op);
    } while(op != 4);
}

void menu_amigo(){
    system("cls");
    printf("1. Incluir amigo\n");
    printf("2. Alterar amigo\n");
    printf("3. Excluir amigo\n");
    printf("4. Voltar\n\n");
    printf("Digite a opcao: ");
}

void OpcaoMenuAmigo(int op){
    switch(op){
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
            printf("Opcao invalida!\n");
            system("pause");
            break;
    }
}

void incluirAmigo(){
    if(_numAmigos == 0){
        _amigos = (TAmigo*)malloc(1 * sizeof(TAmigo));
    } else{
        _amigos = (TAmigo*)realloc(_amigos, (_numAmigos + 1) * sizeof(TAmigo));
    }
    validaAlocacao(_amigos);

    _amigos[_numAmigos] = criaAmigo();
    _numAmigos++;

    system("cls");
    printf("Amigo adicionado com sucesso!!!\n");
    system("pause");
}

TAmigo criaAmigo(){
    char strAux[100];
    TAmigo amigo;

    printf("Digite o nome do amigo: ");
    gets(strAux);
    amigo.nome = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigo.nome, strAux);

    printf("Digite o apelido do amigo: ");
    gets(strAux);
    amigo.apelido = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(amigo.apelido, strAux);

    do{
        printf("Digite a data de nascimento: ");
        scanf("%d%d%d", &amigo.nasc.dia, &amigo.nasc.mes, &amigo.nasc.ano);
        fflush(stdin);
    } while(validarData(amigo.nasc.dia, amigo.nasc.mes, amigo.nasc.ano) == 0);

    do{
        printf("Digite o e-mail do amigo: ");
        gets(strAux);
        amigo.email = (char*)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(amigo.email, strAux);

        if(validarEmail(amigo.email) != 0){
            printf("E-mail invalido!\n\n");
        }
    } while(validarEmail(amigo.email) != 0);

    do{
        printf("Digite o numero de telefone do amigo: ");
        gets(amigo.telefone);

        if(validarTelefone(amigo.telefone) == 1){
            printf("Numero invalido!\n\n");
        }
    } while(validarTelefone(amigo.telefone) == 1);

    return amigo;
}

void OpcaoListarAmigo(){
    int op, indice;

    if(_numAmigos == 0){
        printf("** Nenhum amigo cadastrado!!! **\n");
        system("pause");
        return;
    }

    do{
        menuListarAmigo();
        scanf("%d", &op);
        fflush(stdin);

        if(op < 1 || op > 3){
            printf("Opcao invalida!!\n\n");
        }
    } while(op < 1 || op > 3);
    system("cls");

    if(op == 2){
        do{
            if(_numAmigos > 1){
                printf("Qual amigo deseja exibir [%d-%d]? ", 1, _numAmigos);
                scanf("%d", &indice);
                fflush(stdin);
                indice--;
            } else{
                indice = 0;
            }
            system("cls");
            if(indice >= 0 && indice <= _numAmigos){
                printf("-- Lista de amigos [%d] --\n\n", indice + 1);
                exibeAmigo(_amigos[indice]);
            } else{
                printf("Indice invalido!!\n\n");
            }
        } while(indice < 1 && indice >= _numAmigos);
    } else if(op == 3){
        return;
    } else{
        listarAmigos();
    }
    system("pause");
}

void menuListarAmigo(){
    system("cls");
    printf("1. Exibir TODOS os amigos\n");
    printf("2. Exibir APENAS UM amigo\n");
    printf("3. Voltar\n\n");
    printf("Digite a opcao: ");
}

void listarAmigos(){
    printf("-- Lista de amigos [%d] --\n\n", _numAmigos);
    for(int i = 0; i < _numAmigos; i++){
        exibeAmigo(_amigos[i]);
    }
}

void exibeAmigo(TAmigo amigo){
    printf("Nome: %s\n", amigo.nome);
    printf("Apelido: %s\n", amigo.apelido);
    printf("Email: %s\n", amigo.email);
    printf("Telefone: +%c%c (%c%c) %c%c%c%c%c-%c%c%c%c\n\n", amigo.telefone[0], amigo.telefone[1], amigo.telefone[2], amigo.telefone[3], amigo.telefone[4], amigo.telefone[5], amigo.telefone[6], amigo.telefone[7], amigo.telefone[8], amigo.telefone[9], amigo.telefone[10], amigo.telefone[11], amigo.telefone[12]);
}

void OpcaoExcluirAmigo(){
    int indice;
    char opSn;

    if(_numAmigos == 0){
        printf("** Nenhum amigo cadastrado!!! **\n");
        system("pause");
        return;
    }

    if(_numAmigos > 1){
        do{
            listarAmigos();
            printf("Qual amigo deseja excluir [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if(indice < 0 || indice >= _numAmigos){
                printf("\nOpcao invalida!!\n");
                system("pause");
            }
            system("cls");
        } while(indice < 0 || indice >= _numAmigos);
    } else{
        indice = 0;
    }

    do{
        system("cls");
        exibeAmigo(_amigos[indice]);

        printf("Confirma a exclusao do amigo[%d] (S/N)? ", indice + 1);
        scanf("%c", &opSn);
        fflush(stdin);
        opSn = tolower(opSn);

        if(opSn != 's' && opSn != 'n'){
            printf("\nOpcao invalida!!\n");
            system("pause");
        }
    } while(opSn != 's' && opSn != 'n');

    if(opSn == 's'){
        excluirAmigo(indice);
        _numAmigos--;
    } else{
        return;
    }

    system("cls");
    printf("Amigo excluido com sucesso!\n");
    system("pause");
}

void excluirAmigo(int indice){
    for(int i = indice; i < _numAmigos; i++){
        _amigos[i] = _amigos[i + 1];
    }
}

void OpcaoAlterarAmigo(){
    int indice;

    if(_numAmigos == 0){
        printf("** Nenhum amigo cadastrado!!! **\n");
        system("pause");
        return;
    }

    if(_numAmigos > 1){
        do{
            listarAmigos();
            printf("Qual amigo deseja alterar [%d-%d]? ", 1, _numAmigos);
            scanf("%d", &indice);
            fflush(stdin);
            indice--;

            if(indice < 0 || indice >= _numAmigos){
                printf("Opcao invalida!!\n");
                system("pause");
            }
            system("cls");
        } while(indice < 0 || indice >= _numAmigos);
    } else{
        indice = 0;
    }

    MenuAlterarAmigo(indice);
}

void MenuAlterarAmigo(int indice){
    int op;

    do{
        printf("-- Lista de amigos[%d] --\n", indice+1);
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
    } while(op != 5);
}

void alterarAmigo(int op, int indice){
    char strAux[100];

    switch(op){
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
            do{
                printf("Digite a nova data de nascimento do amigo: ");
                scanf("%d%d%d", &_amigos[indice].nasc.dia, &_amigos[indice].nasc.mes, &_amigos[indice].nasc.ano);
                fflush(stdin);
            } while(validarData(_amigos[indice].nasc.dia, _amigos[indice].nasc.mes, _amigos[indice].nasc.ano) == 0);
            break;
        case 4:
            do{
                printf("Digite o novo email do amigo: ");
                gets(strAux);
                _amigos[indice].email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
                strcpy(_amigos[indice].email, strAux);
                
                if(validarEmail(_amigos[indice].email) <= 1){
                    printf("Email invalido!\n\n");
                }
            } while(validarEmail(_amigos[indice].email) <= 1);
            break;
        case 5:
            do{
                printf("Digite o numero de telefone do amigo: ");
                gets(_amigos[indice].telefone);

                if(validarTelefone(_amigos[indice].telefone) == 1){
                    printf("Numero invalido!\n\n");
                }
            } while(validarTelefone(_amigos[indice].telefone) == 1);
            break;
        case 6:
            break;
        default:
            printf("Opcao invalida!!!\n\n");
            system("pause");
            break;
    }
}


int validarEmail(char *email){
    int countA = 0, countB = 0, x = 0;

    for(int i = 0; email[i] != '\0'; i++){
        if(email[i] == '@'){
            countA++;
        } else if(email[i] == '.'){
            countB++;
        }
    }

    if(countA != 1 || countB < 1){
        x = 1;
    }

    return x;
}

int validarTelefone(char *telefone){
    int count = 0, x = 0, tam = strlen(telefone);

    for(int i = 0; telefone[i] != '\0'; i++){
        if(isdigit(telefone[i])){
            count++;
        }
    }

    if(count != tam || tam != 13){
        x = 1;
    }

    return x;
}

int validarData(int dia, int mes, int ano){
    int x = 1;

    if(ano <= 0){
        x = 0;
    } else if((mes <= 0) || (mes > 12)){
        x = 0;
    }

    if(mes == 2){
        if(ano % 4 == 0){
            if(dia > 29){
                x = 0;
            }
        } else if(dia > 28){
            x = 0;
        }
    } else if((mes == 4) || (mes == 6) || (mes == 9) || (mes == 11)){
        if(dia > 30){
            x = 0;
        }
    } else if((dia > 31) || (dia <= 0)){
        x = 0;
    }

    if(x == 0){
        printf("Data invalida!!! Digite novamente!\n\n");
    }

    return x;
}

void validaAlocacao(void *ptr){
    if(!ptr){
        printf("***ERRO!!! FALHA AO ALOCAR MEMORIA!***\n");
        exit(1);
    }
}