#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//struct
typedef struct {
    int codigo;
    char nome[30];
    char sobrenome[30];
    char endereco[40];
    int telefone;
    float salario;
} Dados;

Dados dados;

//ponteiro para file
FILE *fptr;

//contador de registros
int contadorRegistro = 0;



void inserir() {
    char numstr[10];
    char resp;
    system("cls");

    //usa o ponteiro para abrir o arquivo
    fptr = fopen("arquivo", "ab");

    //caso o arquivo nao exista ou nao seja encontrado
    if(fptr == NULL)    {
        printf("Erro durante a abertura do arquivo..\n");
        system("pause");

    }//se houver arquivo
    else {
        do {

            system("cls");
            fflush(stdin);
            printf("Digite o Codigo do cliente..\n");
            scanf("%d", &dados.codigo);
            fflush(stdin);

            printf("Digite o nome do cliente..\n");
            gets(dados.nome);
            fflush(stdin);

            printf("Digite o sobrenome..\n");
            gets(dados.sobrenome);
            fflush(stdin);

            printf("Digite o Endereco..\n");
            gets(dados.endereco);
            fflush(stdin);

            printf("Digite o Telefone do cliente..\n");
            gets(numstr);
            dados.telefone = atoi(numstr);

            printf("Digite o Salario..\n");
            gets(numstr);
            dados.salario = atof(numstr);

            fwrite(&dados, sizeof(Dados),1,fptr);

            contadorRegistro++;

            printf("Gravado com sucesso...Continuar ? [S/N] \n");
            scanf("%c", &resp);


        } while(resp == 's');
        //usa o ponteiro para fechar o arquivo
        fclose(fptr);
    }

}

void exibir() {

    //usa o ponteiro para abrir o arquivo
    fptr = fopen("arquivo","rb");

    //enquanto o fread ler 1 elemento e retornar a quantidade de elementos lidos
    while(fread(&dados, sizeof(Dados),1, fptr) == 1){
        printf("%d, %s, %s, %s, %d, %.2f\n", dados.codigo, dados.nome, dados.sobrenome, dados.endereco, dados.telefone, dados.salario);
    }

    //usa o ponteiro para fechar o arquivo
    fclose(fptr);
    system("pause");
}

int main() {


    int op;
    while(op != 4) {
        system("cls");
        printf("[1] Inserir novo registro...\n");
        printf("[2] Exibir os registros...\n");
        printf("[3] Pesquisar registros...\n");
        printf("[4] Sair do sistema...\n");

        printf("Informe a opcao desejada...");
        scanf("%d", &op);
        fflush(stdin);
        switch(op) {
        case 1:
            inserir();
            getchar();
            break;
        case 2:
            exibir();
            getchar();
            break;
        case 3:
            printf("Funcao em desenvolvimento...");
            getchar();
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida");
            getchar();
            break;
        }

    }













    return 0;
}

