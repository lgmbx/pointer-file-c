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



            printf("Gravado com sucesso...Continuar ? [S/N] \n");
            scanf("%c", &resp);


        } while(resp == 's');
        //usa o ponteiro para fechar o arquivo
        fclose(fptr);
    }

}

void exibir() {

    //usa o ponteiro para abrir o arquivo
    fptr = fopen("arquivo.txt","rb");

    //enquanto o fread ler 1 elemento e retornar a quantidade de elementos lidos
    while(fread(&dados, sizeof(Dados),1, fptr)){
        printf("%d, %s, %s, %s, %d, %.2f\n", dados.codigo, dados.nome, dados.sobrenome, dados.endereco, dados.telefone, dados.salario);
    }

    //usa o ponteiro para fechar o arquivo
    fclose(fptr);

}

void pesquisar(){
    fptr = fopen("arquivo.txt", "rb");

    char nomePesquisa[20];
    printf("Digite o nome a ser pesquisado: ");
    gets(nomePesquisa);
    fflush(stdin);

    while(fread(&dados, sizeof(Dados),1, fptr)){
        if(strcmp(nomePesquisa, dados.nome) == 0){
            printf("\n Nome........: %s",dados.nome);
            printf("\n Sobrenome...: %s",dados.sobrenome);
            printf("\n Endereço....: %s",dados.endereco);
            printf("\n Telefone....: %d",dados.telefone);
            printf("\n Salario.....: %.2f \n",dados.salario);
        }
    }

    fclose(fptr);
}

void alterar(){


    fptr = fopen("arquivo.txt", "rb+");

    int contador = 0;
    char numstr[10];

    char nomePesquisa[20];
    printf("Digite o nome a ser pesquisado: ");
    gets(nomePesquisa);
    fflush(stdin);

    fread(&dados, sizeof(Dados), 1, fptr);

    while(!feof(fptr) && strcmp(nomePesquisa, dados.nome) != 0){
        fread(&dados, sizeof(Dados), 1, fptr);
        contador++;
    }
    if(feof(fptr)){
        printf("\nNao encontrado!\n");
    }
    else{
        fseek(fptr, contador * sizeof(Dados), SEEK_SET);

        printf("\n Nome...: %s \n", dados.nome);

        printf("\n DIGITE NOVO Sobrenome...: %s \n", dados.sobrenome);
        gets(dados.sobrenome);
        fflush(stdin);


        printf("\n DIGITE NOVO Endereco....: %s \n", dados.endereco);
        gets(dados.endereco);
        fflush(stdin);


        printf("\n DIGITE NOVO Telefone....: %d \n",dados.telefone);
        gets(numstr);
        dados.telefone=atoi(numstr);
        fflush(stdin);


        printf("\n DIGITE NOVO Salario.....: %.2f\n",dados.salario);
        gets(numstr);
        dados.salario=atof(numstr);
        fflush(stdin);


        fwrite(&dados, sizeof(Dados),1,fptr);

        printf("Registro alterado com sucesso...\n");
    }

    fclose(fptr);
}


void excluir(){
    FILE *temp;

    fptr = fopen("arquivo.txt", "rb+");
    temp = fopen("temp.txt", "w+b");

    int codigoPesquisa = 0;

    printf("Digite o CODIGO DO CLIENTE para exclui-lo do registro: ");
    scanf("%d", &codigoPesquisa);
    fflush(stdin);


    while(fread(&dados, sizeof(Dados), 1, fptr)){

        if(codigoPesquisa != dados.codigo){
            fwrite(&dados, sizeof(Dados),1, temp);
        }
    }

    fclose(temp);
    fclose(fptr);

    remove("arquivo.txt");

    rename("temp.txt", "arquivo.txt");


}

int main() {


    int op;
    while(op != 6) {
        system("cls");
        printf("[1] Inserir novo registro...\n");
        printf("[2] Exibir os registros...\n");
        printf("[3] Pesquisar registros...\n");
        printf("[4] Alterar registro...\n");
        printf("[5] Excluir registro...\n");
        printf("[6] Sair do sistema...\n");

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
            pesquisar();


            getchar();
            break;
        case 4:
            alterar();
            break;
        case 5:
            excluir();
            break;
        case 6:
            break;
        default:
            printf("Opcao invalida");
            getchar();
            break;
        }

    }













    return 0;
}

