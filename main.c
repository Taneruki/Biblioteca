#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <time.h>

struct descricao{

    char nome[255];
    char autor[255];
    char editora[255];
    char genero[50];
    char lancamento[50];
    char status[25];
};

struct User{

    char name[40];
    char e_mail[50];
    char senha[38];
    int age;
    long int cep;
    unsigned int userCode;
};

void inicio(int p, struct User *a){

    char string[50] = "oi";

    inicio:

    if(p == 1){

        logo(1, NULL);
    }
    else if(p == 2){

        logo(2, &a);
    }
    else if(p == 3){

        logo(3, NULL);
    }


    //getchar();
    gets(string);


    switch(string[0]){


        case '/':

            switch(string[1]){

                case 'a':
                    if(p > 1){

                        if(strcmp(string, "/acervo") == 0){

                            acervo(&a);
                        }
                    }
                    else{

                        goto erro;
                    }
                break;

                case 'd':

                    if(p > 1){

                        if(strcmp(string, "/devolver") == 0){

                            devolverLivro(&a);
                        }
                    }else{

                        goto erro;
                    }
                break;

                case 'e':

                    if(strcmp(string, "/exit") == 0){

                        printf("Adeus...");
                        exit(1);
                    }else{

                        goto erro;
                    }
                break;

                case 'l':

                    if(p <= 1){

                        if (strcmp(string, "/login") == 0){

                            login();
                        }
                    }

                    if(p >= 2){

                        if(strcmp(string, "/logout") == 0){

                            system("cls");
                            inicio(1, NULL);
                        }
                    }
                break;

                case 'p':

                    if(p > 1){

                        if(strcmp(string, "/pegar") == 0){

                            pesquiserLivro(&a);
                        }
                    }
                    else{

                        goto erro;
                    }
                break;

                case 'r':

                    if(p <= 1){

                        if(strcmp(string, "/register") == 0){

                            registrar();
                        }
                        else{

                            goto erro;
                        }
                    }

                    if(p > 1){

                        if(strcmp(string, "/renovar") == 0){

                            renovarLivro(&a);
                        }
                        else{

                            goto erro;
                        }
                    }
                break;

                default:

                    erro:
                    printf("Comando invalido.\nAperte ENTER para tentar novamente.\n");
                    getchar();
                    system("cls");
                    goto inicio;
            }
        break;

        default:

        printf("Comando invalido.\nAperte ENTER para tentar novamente.\n");
        getchar();
        system("cls");
        goto inicio;


    }
}

void logo(int p, struct User **b){

    system("Color 03");
    printf("\n\t\t\t\t%s\n\t\t\t\t%s\n\t\t\t\t%s\n\t\t\t\t%s\n\t\t\t\t%s\n\t\t\t\t%s\n",
                                    "###### ###### ###### ###### ###### ######",
                                    "##                                     ##",
                                    "##    Bem vindo a biblioteca nacional  ##",
                                    "##	 Policarpo Quaresma!           ##",
                                    "##                                     ##",
                                    "###### ###### ###### ###### ###### ######");

    switch(p){

        case 1:

            printf("\n-> Digite \"/login\" para entrar.");
            printf("\n-> Digite \"/register\" para registrar.");
            printf("\n-> Digite \"/exit\" para sair.\n");
        break;

        case 2:

            printf("\n\t-> Digite \"/acervo\" para consultar nosso acervo de livros.\n");
            printf("\t-> Caso já saiba o livro que gostaria pegar, digite \"/pegar\" e em seguida o nome do livro.\n");
            printf("\t-> Se caso queira renovar um livro, digite \"/renovar\".\n");
            printf("\t-> Caso queira devolver um livro, digite \"/devolver\".\n");
            printf("\t-> E se quiser sair da sua conta digite \"/logout\".\n");
            printf("\t-> Digite \"/exit\" para sair.\n");
            printf("\nBem vindo/a %s. O que gostaria de fazer?\n", (**b).name);
        break;

        case 3:

            printf("\n\t-> Digite \"/acervo\" para consultar nosso acervo de livros.\n");
            printf("\t-> Caso já saiba o livro que gostaria pegar, digite \"/pegar\" e em seguida o nome do livro.\n");
            printf("\t-> Se caso queira renovar um livro, digite \"/renovar\".\n");
            printf("\t-> E caso queira devolver um livro, digite \"/devolver\".\n");
            printf("\t-> E se quiser sair da sua conta digite \"/logout\".\n");
            printf("\t-> Digite \"/exit\" para sair.\n\n");
        break;
    }


}

void login(){

    FILE *flogar = fopen("registros.dat", "rb");

    rewind(flogar);
    struct User user;

    char nome[40];
    char mail[50];
    char senha[38];
    int age;
    long int cep;
    long int userCode;
    int i = 0;

    printf("\nBem vindo usuario, para consultar nosso acervo e alugar um de nossos livros, \nprecisaremos saber seu user code e sua senha: \n");

    login:
    printf("\n\t-> User Code: ");
    scanf("%li", &userCode);


    while(!feof(flogar)){

        fread(&user.name, sizeof(user.name), 1, flogar);
        fread(&user.age, sizeof(user.age), 1, flogar);
        fread(&user.cep, sizeof(user.cep), 1, flogar);
        fread(&user.e_mail, sizeof(user.e_mail), 1, flogar);
        fread(&user.senha, sizeof(user.senha), 1, flogar);
        fread(&user.userCode, sizeof(user.userCode), 1, flogar);

        if(userCode == user.userCode){

            i++;
            printf("\t-> Senha: ");
            scanf("%s", senha);
            getchar();

            if(strcmp(senha, user.senha) == 0){

                system("cls");

                inicio(2, &user);
            }
            else{

                printf("\nSenha incorreta.\n");
                rewind(flogar);
                goto login;
            }
        }

        if(feof(flogar) && i <= 0){

            printf("\nInválido.\n");
            rewind(flogar);
            goto login;
        }
    }

    fclose(flogar);
}

void registrar(){

    int cont = 0;

    FILE *fregistrar = fopen("registros.dat", "ab");

    struct User NewUser;

    printf("\n\n\t------------- Registro de Usuario -------------\n\n");

    nameStart:
    printf("\t-> Nome: ");
    gets(NewUser.name);
    int namelen = strlen(NewUser.name);
    for(int i = 0; i < namelen; i++){

        if(NewUser.name[i] == ' '){
            cont++;
        }
        if(NewUser.name[i] >= '0' && NewUser.name[i] <= '9'){

            printf("\t-> Não pode haver números no nome.\n");
            getchar();
            goto nameStart;
        }
    }


    if(cont == 0){

        printf("\t-> Nome simples, tente outra vez: \n");
        goto nameStart;
    }

    printf("\t-> Idade: ");
    while(NewUser.age <= 13 || NewUser.age >= 110){

        scanf("%i", &NewUser.age);
        NewUser.age <= 13 || NewUser.age >= 110 ? printf("\t-> Idade invalida, tente novamente: ") : 0;
    }


    printf("\t-> CEP: ");
    do{

        scanf("%ld", &NewUser.cep);
        NewUser.cep <= 10000000 || NewUser.cep >= 100000000 ? printf("\t-> Valor invalido, tente novamente: ") : 0;
    }while(NewUser.cep <= 10000000 || NewUser.cep >= 100000000);

    char confirm[128];

    start:
    printf("\t-> E-mail: ");
    scanf("%s", NewUser.e_mail);
    printf("\t-> Confirme seu e-mail: ");
    scanf("%s", confirm);
    while(strcmp(NewUser.e_mail, confirm) == 1){

        printf("\t-> Nao validado, tente novamente: \n");
        goto start;
    }

    printf("\t-> Senha: ");
    int len = 0;


    while(len < 8 || len > 38){

        scanf("%s", NewUser.senha);
        len = strlen(NewUser.senha);
    }

    srand(time(NULL));


    while(NewUser.userCode <= 1000 || NewUser.userCode >= 9999){

        NewUser.userCode = rand() % 10000;
    }

    printf("\t-> Seu user code: %i\n", NewUser.userCode);
    getchar();
    rewind(fregistrar);

    fwrite(&NewUser.name, sizeof(NewUser.name), 1, fregistrar);
    fwrite(&NewUser.age, sizeof(NewUser.age), 1, fregistrar);
    fwrite(&NewUser.cep, sizeof(NewUser.cep), 1, fregistrar);
    fwrite(&NewUser.e_mail, sizeof(NewUser.e_mail), 1, fregistrar);
    fwrite(&NewUser.senha, sizeof(NewUser.senha), 1, fregistrar);
    fwrite(&NewUser.userCode, sizeof(NewUser.userCode), 1, fregistrar);

    fclose(fregistrar);

    printf("Pressione ENTER para continuar: ");
    getchar();
    int i = 0;
    while(i < 18){

        printf("\n");
        i++;
    }
    inicio(1, NULL);
}

void acervo(struct User *c){

    char nome[255];
    char autor[255];
    char editora[255];
    char genero[50];
    char lancamento[50];

    struct descricao livro;
    FILE *livros;

    livros = fopen("Livros.txt", "r");

    printf("\n");
    while(!feof(livros)){

        if(fgets(nome, sizeof(livro.nome), livros))
            printf("\t-> %s\n", nome);

        if(fgets(autor, sizeof(livro.autor), livros))
            printf("\t-> %s\n", autor);

        if(fgets(genero, sizeof(livro.genero), livros))
            printf("\t-> %s\n", genero);

        if(fgets(lancamento, sizeof(livro.lancamento), livros))
            printf("\t-> %s\n", lancamento);

        if(fgets(editora, sizeof(livro.editora), livros))
            printf("\t-> %s\n", editora);
    }

    fclose(livros);
    printf("||--------------------------------------------------------------------------------------------------------------------||\n\n");

    printf("Pressione ENTER para prosseguir: ");
    getchar();

    int i = 0;
    while(i != 16){

        printf("\n");
        i++;
    }

    inicio(3, NULL);
}

void pesquiserLivro(struct User **d){

    time_t tempo;
    time(&tempo);
    struct tm *tempo0 = localtime(&tempo);

    char nomeLivro[255];

    pesquisar:

    printf("Digite o nome do livro: ");
    fgets(nomeLivro, sizeof(nomeLivro), stdin);

    struct descricao livroPs;
    char nome[200];
    int j = 0;
    char SN;

    strcpy(nome, nomeLivro);

    FILE *livros;

    livros = fopen("Livros.txt", "r");

    while(!feof(livros)){

        if(fgets(livroPs.nome, sizeof(livroPs.nome), livros))
        if(fgets(livroPs.autor, sizeof(livroPs.autor), livros))
        if(fgets(livroPs.genero, sizeof(livroPs.genero), livros))
        if(fgets(livroPs.lancamento, sizeof(livroPs.lancamento), livros))
        if(fgets(livroPs.editora, sizeof(livroPs.editora), livros))


        if(strcmp(nome, livroPs.nome) == 0){

            j++;
            printf("\n\n\t-> Sobre o livro: ");
            printf("\n\n-> Nome: %s\n", livroPs.nome);
            printf("-> Autor: %s\n", livroPs.autor);
            printf("-> Gênero: %s\n", livroPs.genero);
            printf("-> Lançamento Original: %s\n", livroPs.lancamento);
            printf("-> Editora: %s\n", livroPs.editora);

            printf("-> Aperte S parar pegar e N caso tenha mudado de ideia: ");
            scanf("%c", &SN);

            if(SN == 'S'){

                    printf("\n\n-> Devolver ou renovar dia: %02d:%02d:%04d. \nBom proveito!\n", tempo0->tm_mday + 7, tempo0->tm_mon + 1, tempo0->tm_year + 1900);

                    FILE *fpegar = fopen("Livros pegos.dat", "ab");

                    fwrite(&(**d).name, sizeof((**d).name), 1, fpegar);
                    fwrite(&livroPs.nome, sizeof(livroPs.nome), 1, fpegar);

                    fclose(fpegar);

                    printf("Pressione ENTER para continuar: ");
                    getchar();
                    getchar();
                    int i = 0;
                    while(i <= 16){

                        printf("\n");
                        i++;
                    }
                    inicio(3, NULL);
                }
            }

        }
        if(j == 0){

            printf("\nNão possuímos este livro em nossa biblioteca.\n");
            printf("Pressione ENTER para continuar: ");
            getchar();
            printf("\n");
            goto pesquisar;
        }
    fclose(livros);
}

void renovarLivro(struct User **e){

    char nome[255];
    char nomeLivro[255];

    FILE *frenovar = fopen("Livros pegos.dat", "r");

    while(!feof(frenovar)){

        fread(nome, sizeof(nome), 1, frenovar);
        fread(nomeLivro, sizeof(nomeLivro), 1, frenovar);

        if(strcmp(nome, (**e).name) == 0){

            printf("Livro renovado.");
        }
        else{

            printf("Está conta não tem livros a renovar.\n");
            printf("Pressione ENTER para continuar: ");
            getchar();
        }
    }

    fclose(frenovar);
}

void devolverLivro(struct User **f){

    char nome[255];
    char nomeLivro[1][255];
    printf("\t-> Digite o nome do livro: ");
    gets(nomeLivro[0]);

    FILE *fdevolver = fopen("Livros pegos.dat", "a");

    while(!feof(fdevolver)){

        fread(&nome, sizeof(nome), 1, fdevolver);
        fread(&nomeLivro[1], sizeof(nomeLivro[1]), 1, fdevolver);

        if(strcmp(nome, (**f).name) != 0 && strcmp(nomeLivro[0], nomeLivro[1]) != 0){

            fwrite(&nome, sizeof(nome), 1, fdevolver);
            fwrite(&nomeLivro[1], sizeof(nomeLivro[1]), 1, fdevolver);
        }
    }

    printf("Livro devolvido, tenha um bom dia :)");
    fclose(fdevolver);
}

void addLivro(){

    char nome[255];
    char autor[255];
    char editora[255];
    char genero[50];
    char lancamento[50];

    struct descricao livro;

    FILE *livros;

    livros = fopen("Livros.txt", "a");

    int r;
    int i = 0;
    char a[5];

    printf("Digite o número de livros que deseja adiconar: ");
    scanf("%d", &r);
    getchar();

    do{

        printf("\n\n\t-> Nome: ");
        fgets(livro.nome, sizeof(livro.nome), stdin);

        printf("\n\t-> Autor: ");
        fgets(livro.autor, sizeof(livro.autor), stdin);

        printf("\n\t-> Gênero: ");
        fgets(livro.genero, sizeof(livro.genero), stdin);

        printf("\n\t-> Lançamento: ");
        fgets(livro.lancamento, sizeof(livro.lancamento), stdin);

        printf("\n\t-> Editora: ");
        fgets(livro.editora, sizeof(livro.editora), stdin);

        fprintf(livros, "%s%s%s%s%s", livro.nome, livro.autor, livro.genero, livro.lancamento, livro.editora);

        i++;
    }while(i < r);


    fclose(livros);
}

void main(){

    setlocale(LC_ALL, "Portuguese");

    inicio(1, NULL);
}
