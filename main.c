#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////
//                         VARIÁVEIS E ESTRUTURAS                         //
////////////////////////////////////////////////////////////////////////////

//variaveis globais referentes a manipulação de arquivos
FILE *arq;
FILE *indid;
FILE *indisbn;
FILE *indautor;
FILE *indtitulo;
FILE *temp;

int nreg=-1; //variável para criar rrn
char ident[3]; // variável para criar ID
int id[3]={0,0,0}; //variável auxiliar para criar ID


//Estrutura que contera iformaçoes sobre o livro
struct livro
{
   int rrn;
   char id[4];
   char isbn[15];
   char autor[50];
   char titulo[50];
   char descricao[100];
   char tipo; //'g' se graduação, 'p' se for de pós graduação
   char rem;//'s' remover 'n' nao remover
};
typedef struct livro Livro;
Livro l;

// Estruturas referente a criação dos arquivos indices
struct LiID
{
   int rrn;
   char id[4];
};
typedef struct LiID liID;
liID lID;

struct LiISBN
{
   char id[4];
   char isbn[15];
};
typedef struct LiISBN liISBN;
liISBN lISBN;

struct LiAUTOR
{
   char id[4];
   char autor[50];
};
typedef struct LiAUTOR liAUTOR;
liAUTOR lAUTOR;

struct LiTITULO
{
   char id[4];
   char titulo[50];
};
typedef struct LiTITULO liTITULO;
liTITULO lTITULO;


////////////////////////////////////////////////////////////////////////////
//                         FUNÇÕES                                        //
////////////////////////////////////////////////////////////////////////////
void insereArquivo()
{
////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO DE BASE DE DADOS
    arq=fopen("catalogo.txt","ab");
    if( arq == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ID
    indid=fopen("indiceID.txt","ab");
    if( indid == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ISBN
    indisbn=fopen("indiceISBN.txt","ab");
    if( indisbn == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE AUTOR
    indautor=fopen("indiceAUTOR.txt","ab");
    if( indautor == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE TITULO
    indtitulo=fopen("indiceTITULO.txt","ab");
    if( indtitulo == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

////////////////////////////////////////////////////////////////////////////

int i;
    if(id[2]<9)
    {
        if(id[1]<8)
            id[2]=id[2]+1;
        else
        {
            printf("Ja foi adicionado 80 livros\n");
            return;
        }
    }
    else
    {
        id[2]=0;
        id[1]=id[1]+1;
    }

    //CONVERTE VETOR DE INT ID PARA CHAR E GUARDA NO VETOR DE CHAR IDENT
    for(i=0;i<3;i++)
    ident[i]=id[i]+'0';

    //ATRIBUIÇÃO DO VALOR ID PARA VARIAVEIS GLOBAIS PARA O FUTURO
    //ARMAZENAMENTO NOS RESPECTIVOS ARQUIVOS
    strcpy(l.id,ident);
    strcpy(lID.id,ident);
    strcpy(lISBN.id,ident);
    strcpy(lAUTOR.id,ident);
    strcpy(lTITULO.id,ident);
//TERMINA GERA ID

////////////////////////////////////////////////////////////////////////////

//GERA RRN
    nreg=nreg+1;
    l.rrn=nreg;
    lID.rrn=l.rrn;
//TERMINA GERA RRN

////////////////////////////////////////////////////////////////////////////

    //ENTRADA DE VALORES PELO USUARIO

    printf("Digite o codigo ISBN:");
    scanf("%s",&l.isbn);
    strcpy(lISBN.isbn,l.isbn);

 /*   
    //PARA FACILITAR A CORREÇÃO O TRATAMENTO DO ERRO FOI COMENTADO
    //USUARIO DEVE INFORMAR APENAS 13 DIGITOS PARA ISBN
    while(strlen(l.isbn)!=13)
    {
        printf("ERRO!!!\nISBN deve possuir 13 digitos\n");
        printf("Digite o codigo ISBN:");
        scanf("%s",&l.isbn);
        strcpy(lISBN.isbn,l.isbn);
    }
    ////////////////////////////////////////////////////
   */ 

    printf("Digite o nome do autor:");
    fflush(stdin);
    scanf("%[^\n]",&l.autor);
    strcpy(lAUTOR.autor,l.autor);
    while(strlen(l.autor)==0)
    {
       printf("Digite o nome do autor:");
       fflush(stdin);
       scanf("%[^\n]",&l.autor);
       strcpy(lAUTOR.autor,l.autor);
    }


    printf("Digite o titulo:");
    fflush(stdin);
    scanf("%[^\n]",&l.titulo);
    strcpy(lTITULO.titulo,l.titulo);

     while(strlen(l.titulo)==0)
    {
       printf("Digite o titulo:");
       fflush(stdin);
       scanf("%[^\n]",&l.titulo);
       strcpy(lTITULO.titulo,l.titulo);
    }

    printf("Digite a descricao:");
    fflush(stdin);
    scanf("%[^\n]",&l.descricao);

    while(strlen(l.descricao)==0)
    {
       printf("Digite a descricao:");
       fflush(stdin);
       scanf("%[^\n]",&l.descricao);
    }
    printf("Digite o tipo(g=graduacao/p=pos graduacao):");
    fflush(stdin);
    scanf("%c",&l.tipo);

    //TRATAMENTO DE ERRO
    while(l.tipo!='p'&&l.tipo!='g')
    {
    printf("ERRO!!!\nDigite o tipo(g=graduacao/p=pos graduacao):");
    fflush(stdin);
    scanf("%c",&l.tipo);
    }
    fflush(stdin);
    l.rem='n';
////////////////////////////////////////////////////////////////////////////

// GRAVAÇÃO NOS ARQUIVOS

    //GRAVA NA BASE DE DADOS
    fwrite(&l,sizeof(l),1,arq);

    //GRAVA NO ARQUIVO DE INDICE ID
    fwrite(&lID,sizeof(lID),1,indid);

    //GRAVA NO ARQUIVO DE INDICE ISBN
    fwrite(&lISBN,sizeof(lISBN),1,indisbn);

    //GRAVA NO ARQUIVO DE INDICE AUTOR
    fwrite(&lAUTOR,sizeof(lAUTOR),1,indautor);

    //GRAVA NO ARQUIVO DE INDICE TITULO
    fwrite(&lTITULO,sizeof(lTITULO),1,indtitulo);
////////////////////////////////////////////////////////////////////////////

    //FECHAMENTO DOS ARQUIVOS
    fclose(arq);
    fclose(indid);
    fclose(indisbn);
    fclose(indautor);
    fclose(indtitulo);

}//Fecha insereArquivo

void leArquivo()
{
////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////

     //ABRE ARQUIVO INDICE ID PARA LEITURA
    indid=fopen("indiceID.txt","rb");
    if( indid == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO DE BASE DE DADOS PARA LEITURA
    arq=fopen("catalogo.txt","rb");
    if( arq == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ISBN PARA LEITURA
    indisbn=fopen("indiceISBN.txt","rb");
    if( indisbn == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

     //ABRE ARQUIVO INDICE AUTOR PARA LEITURA
    indautor=fopen("indiceAUTOR.txt","rb");
    if( indautor == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE TITULO PARA LEITURA
    indtitulo=fopen("indiceTITULO.txt","rb");
    if( indtitulo == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }
////////////////////////////////////////////////////////////////////////////

//IMPRESSÃO DOS DADOS NA TELA
    //IMPRIME BASE DE DADOS(CATALOGO.TXT)
    //LÊ UM REGISTRO DO ARQUIVO
    fread(&l,sizeof(l),1,arq);

    printf("\n\nArquivo base de dados:\n");

    while (!feof(arq)) {

    if(l.rem=='n')
    {
    //IMPRIME NA TELA CONTEUDO DO ARQUIVO
    printf ( "\nrrn= %d\n" ,l.rrn) ;
    printf ( "ID= %s\n" ,l.id) ;
    printf ( "ISBN= %s\n" ,l.isbn) ;
    printf ( "Autor= %s\n" ,l.autor) ;
    printf ( "Titulo= %s\n" ,l.titulo) ;
    printf ( "Descricao= %s\n" ,l.descricao) ;
    printf ( "Tipo= %c\n" ,l.tipo) ;

    }
    //LÊ PRÓXIMO REGISTRO DO ARQUIVO
    fread(&l,sizeof(l),1,arq);

    }
    printf("\n");
////////////////////////////////////////////////////////////////////////////

    //IMRPRIME ARQUIVO DE INDICE ID
    fread(&lID,sizeof(lID),1,indid);

    printf("\n\nArquivo indice ID:\n");
    while(!feof(indid))
    {
        printf ( "\nrrn= %d\n" ,lID.rrn) ;
        printf ( "ID= %s\n" ,lID.id) ;
        fread(&lID,sizeof(lID),1,indid);
    }
    printf("\n");
////////////////////////////////////////////////////////////////////////////

    //IMRPRIME ARQUIVO DE INDICE ISBN
    fread(&lISBN,sizeof(lISBN),1,indisbn);

    printf("\n\nArquivo indice ISBN:\n");
    while(!feof(indisbn))
    {
        printf ( "\nid= %s\n" ,lISBN.id) ;
        printf ( "ISBN= %s\n" ,lISBN.isbn) ;
        fread(&lISBN,sizeof(lISBN),1,indisbn);

    }
    printf("\n");
////////////////////////////////////////////////////////////////////////////

    //IMRPRIME ARQUIVO DE INDICE AUTOR
    fread(&lAUTOR,sizeof(lAUTOR),1,indautor);

    printf("\n\nArquivo indice AUTOR:\n");
    while(!feof(indautor))
    {
        printf ( "\nid= %s\n" ,lAUTOR.id) ;
        printf ( "Autor= %s\n" ,lAUTOR.autor) ;
        fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
    }
    printf("\n");
////////////////////////////////////////////////////////////////////////////

    //IMRPRIME ARQUIVO DE INDICE TITULO
    fread(&lTITULO,sizeof(lTITULO),1,indtitulo);

    printf("\n\nArquivo indice TITULO:\n");
    while(!feof(indtitulo))
    {
        printf ( "\nid= %s\n" ,lTITULO.id) ;
        printf ( "Titulo= %s\n" ,lTITULO.titulo) ;
        fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
    }
    printf("\n");
////////////////////////////////////////////////////////////////////////////

    //FECHAMENTO DOS ARQUIVOS
    fclose(arq);
    fclose(indid);
    fclose(indisbn);
    fclose(indautor);
    fclose(indtitulo);

}//FECHA FUNÇÃO leArquivo

int buscaID(char cod[4]){
////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////
    //ABRE ARQUIVO INDICE ID PARA LEITURA
    indid=fopen("indiceID.txt","rb");
            if( indid == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }

    //ABRE ARQUIVO BASE DE DADOS PARA LEITURA
    arq=fopen("catalogo.txt","rb");
            if( arq == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }
////////////////////////////////////////////////////////////////////////////

    //CRIAÇÃO DE VETORES PARA ARMAZENAR CONTEUDO
    // DOS ARQUIVOS PARA SER REALIZADA A BUSCA BINARIA
    liID lIDvet [80];
    Livro lvet [80];
    int i=0,k=0;//Variaveis para indicar a quantidade de registros

    //ARMAZENAMENTO DOS REGISTROS DE CATALOGO.TXT NO VETOR LVET
    fread(&l,sizeof(l),1,arq);
    while (!feof(arq))
     {
      lvet[i]=l;
      fread(&l,sizeof(l),1,arq);
      i++;
      }

    //ARMAZENAMENTO DOS REGISTROS DO ARQUIVO INDICE ID NO VETOR LIDVET
    fread(&lID,sizeof(lID),1,indid);
    while (!feof(indid)) {
    lIDvet[k]=lID;
    fread(&lID,sizeof(lID),1,indid);
    k++;
    }
////////////////////////////////////////////////////////////////////////////

    //ALGORITMO DE BUSCA BINÁRIA
     int inf = 0; //Limite inferior
     int inf2 = 0;

     int sup = i; //Limite superior
     int sup2 = k;

     int meio;
     int meio2;


     while (inf <= sup)
     {
          meio = inf + (sup-inf)/2;
          if (strcmp(cod,lIDvet[meio].id)==0)
          {

              while(inf2<=sup2)
              {
                  meio2=inf2+(sup2-inf2)/2;
                  if(lIDvet[meio].rrn==lvet[meio2].rrn)
                  {
                    if(lvet[meio2].rem=='s'){
                    printf("REGISTRO REMOVIDO\n");
                    return 0;
                    }
                    printf("Livro Encontrado");
                    printf ( "\nID= %s\n" ,lvet[meio2].id) ;
                    printf ( "ISBN= %s\n" ,lvet[meio2].isbn) ;
                    printf ( "Autor= %s\n" ,lvet[meio2].autor) ;
                    printf ( "Titulo= %s\n" ,lvet[meio2].titulo) ;
                    printf ( "Descricao= %s\n" ,lvet[meio2].descricao) ;
                    printf ( "Tipo= %c\n" ,lvet[meio2].tipo) ;


                    //FECHAMENTO DOS ARQUIVOS
                    fclose(arq);
                    fclose(indid);
                    return 1;
                  }

              else if (lIDvet[meio].rrn < lvet[meio2].rrn)
               sup2 = meio2-1;
              else
               inf2 = meio2+1;
             }


          }

          else if (strcmp(cod,lIDvet[meio].id)<0)
               sup = meio-1;
          else
               inf = meio+1;
     }
////////////////////////////////////////////////////////////////////////////

     //FECHAMENTO DOS ARQUIVOS
     fclose(arq);
     fclose(indid);
     printf("Livro não encontrado\n");
     return 0;   // não encontrado


}//FECHA FUNÇÃO BUSCA ID

void buscaISBN(char cod[13]){
////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////


    //ABRE ARQUIVO INDICE ISBN
    indisbn=fopen("indiceISBN.txt","rb");
    if( indisbn == NULL)
    {
        puts("Erro na abertura do arquivo.") ;
        system("PAUSE");
        exit(0);
    }

    //ABRE ARQUIVO INDICE ID
    indid=fopen("indiceID.txt","rb");
            if( indid == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }

    //ABRE ARQUIVO CATALOGO.TXT
    arq=fopen("catalogo.txt","rb");
            if( arq == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }
////////////////////////////////////////////////////////////////////////////

    fread(&lISBN,sizeof(lISBN),1,indisbn);
    while(!feof(indisbn))
    {
        if(strcmp(lISBN.isbn,cod)==0)
        {
          fseek(indisbn,sizeof(lISBN),SEEK_CUR);
          fread(&lID,sizeof(lID),1,indid);
          while(!feof(indid))
          {
            if(strcmp(lISBN.id,lID.id)==0)
            {
                fseek(indid,sizeof(lID),SEEK_CUR);
                fread(&l,sizeof(l),1,arq);
              while(!feof(arq))
              {
                if(lID.rrn==l.rrn)
                {
                  fseek(arq,sizeof(l),SEEK_CUR);
                  if(l.rem=='s')
                  {
                    printf("REGISTRO REMOVIDO\n");
                    return;
                  }
                  printf("Livro Encontrado");
                  printf ( "\nID= %s\n" ,l.id) ;
                  printf ( "ISBN= %s\n" ,l.isbn) ;
                  printf ( "Autor= %s\n" ,l.autor) ;
                  printf ( "Titulo= %s\n" ,l.titulo) ;
                  printf ( "Descricao= %s\n" ,l.descricao) ;
                  printf ( "Tipo= %c\n" ,l.tipo) ;
                  return;
                 }
               fread(&l,sizeof(l),1,arq);
              }
            }
            fread(&lID,sizeof(lID),1,indid);
           }
         }
    fread(&lISBN,sizeof(lISBN),1,indisbn);
    }
    printf("Livro não Encontrado!!!\n");
    return ;
}//FECHA BUSCA ISBN

void buscaAUTOR(char autor[50]){
////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO INDICE AUTOR
    indautor=fopen("indiceAUTOR.txt","rb");
    if( indautor == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ID
    indid=fopen("indiceID.txt","rb");
            if( indid == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }

    //ABRE ARQUIVO CATALOGO.TXT
    arq=fopen("catalogo.txt","rb");
            if( arq == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }
////////////////////////////////////////////////////////////////////////////

    fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
    while(!feof(indautor))
    {
        if(strcmp(lAUTOR.autor,autor)==0)
        {
            fseek(indautor,sizeof(lAUTOR),SEEK_CUR);
            fread(&lID,sizeof(lID),1,indid);
            while(!feof(indid))
            {
              if(strcmp(lAUTOR.id,lID.id)==0)
              {
                fseek(indid,sizeof(lID),SEEK_CUR);
                fread(&l,sizeof(l),1,arq);
                while(!feof(arq))
                {
                  if(lID.rrn==l.rrn)
                  {
                    fseek(arq,sizeof(l),SEEK_CUR);
                    if(l.rem=='s')
                    {
                       printf("REGISTRO REMOVIDO\n");
                       return;
                    }
                    printf("Livro Encontrado");
                    printf ( "\nID= %s\n" ,l.id) ;
                    printf ( "ISBN= %s\n" ,l.isbn) ;
                    printf ( "Autor= %s\n" ,l.autor) ;
                    printf ( "Titulo= %s\n" ,l.titulo) ;
                    printf ( "Descricao= %s\n" ,l.descricao) ;
                    printf ( "Tipo= %c\n" ,l.tipo) ;
                    return;
                  }
                  fread(&l,sizeof(l),1,arq);
                }
              }
            fread(&lID,sizeof(lID),1,indid);
            }
        }
    fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
    }
    printf("Livro não Encontrado!!!\n");
    return ;
}//FECHA BUSCA AUTOR

void buscaTITULO(char titulo[50]){
////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO INDICE TITULO
    indtitulo=fopen("indiceTITULO.txt","rb");
    if( indtitulo == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ID
    indid=fopen("indiceID.txt","rb");
            if( indid == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }

    //ABRE ARQUIVO CATALOGO.TXT
    arq=fopen("catalogo.txt","rb");
            if( arq == NULL)
            {
                puts("Erro na abertura do arquivo.") ;
                system("PAUSE");
                exit(0);
            }
////////////////////////////////////////////////////////////////////////////

    fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
    while(!feof(indtitulo))
    {
        if(strcmp(lTITULO.titulo,titulo)==0)
        {
            fseek(indtitulo,sizeof(lTITULO),SEEK_CUR);
            fread(&lID,sizeof(lID),1,indid);
            while(!feof(indid))
            {
               if(strcmp(lTITULO.id,lID.id)==0)
               {
                   fseek(indid,sizeof(lID),SEEK_CUR);
                   fread(&l,sizeof(l),1,arq);
                   while(!feof(arq))
                   {
                      if(lID.rrn==l.rrn)
                      {
                          fseek(arq,sizeof(l),SEEK_CUR);
                          if(l.rem=='s')
                          {
                          printf("REGISTRO REMOVIDO\n");
                          return;
                          }
                          printf("Livro Encontrado");
                          printf ( "\nID= %s\n" ,l.id) ;
                          printf ( "ISBN= %s\n" ,l.isbn) ;
                          printf ( "Autor= %s\n" ,l.autor) ;
                          printf ( "Titulo= %s\n" ,l.titulo) ;
                          printf ( "Descricao= %s\n" ,l.descricao) ;
                          printf ( "Tipo= %c\n" ,l.tipo) ;
                          return;
                      }
                   fread(&l,sizeof(l),1,arq);
                   }
               }
            fread(&lID,sizeof(lID),1,indid);
            }
        }
    fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
    }
    printf("Livro não Encontrado!!!\n");
    return ;
}//FECHA BUSCA TITULO

void editar(char cod[4])
{
     int result;
     result=buscaID(cod);

     if(result==1)
     {
//DECLARAÇÃO DE VARIAVEIS PARA ALTERAÇÃO DO REGISTRO
     int cont=0;//AXILIA NO MOVIMENTO DO PONTEIRO FSEEK
     char isbn[15];
     char autor[50];
     char titulo[50];
     char descricao[100];
     char tipo;

////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////
    //ABRE ARQUIVO CATALOGO.TXT
    arq=fopen("catalogo.txt","rb+");
    if( arq == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ID
    indid=fopen("indiceID.txt","rb+");
    if( indid == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ISBN
    indisbn=fopen("indiceISBN.txt","rb+");
    if( indisbn == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

     //ABRE ARQUIVO INDICE AUTOR
    indautor=fopen("indiceAUTOR.txt","rb+");
    if( indautor == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE TITULO
    indtitulo=fopen("indiceTITULO.txt","rb+");
    if( indtitulo == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }
////////////////////////////////////////////////////////////////////////////

//ENTRADA DE VALORES PELO USUARIO PARA EDIÇÃO DO REGISTRO
     fflush(stdin);
     printf("Digite o codigo ISBN:");
     scanf("%s",&isbn);

     /*
    PARA FACILITAR A CORREÇÃO O TRATAMENTO DO ERRO FOI COMENTADO
    //USUARIO DEVE INFORMAR APENAS 13 DIGITOS PARA ISBN
    while(strlen(isbn)!=13)
    {
        printf("ERRO!!!\nISBN deve possuir 13 digitos\n");
        printf("Digite o codigo ISBN:");
        scanf("%s",&isbn);
    }
    ////////////////////////////////////////////////////
    */


     printf("Digite o nome do autor:");
     fflush(stdin);
     scanf("%[^\n]",&autor);
     while(strlen(autor)==0)
    {
       printf("Digite o nome do autor:");
       fflush(stdin);
       scanf("%[^\n]",&autor);
    }

     printf("Digite o titulo:");
     fflush(stdin);
     scanf("%[^\n]",&titulo);
     while(strlen(titulo)==0)
    {
       printf("Digite o titulo:");
       fflush(stdin);
       scanf("%[^\n]",&titulo);
    }

     printf("Digite a descricao:");
     fflush(stdin);
     scanf("%[^\n]",&descricao);
      while(strlen(descricao)==0)
    {
       printf("Digite a descricao:");
       fflush(stdin);
       scanf("%[^\n]",&descricao);
    }

     printf("Digite o tipo(g=graduacao/p=pos graduacao):");
     fflush(stdin);



     scanf("%c",&tipo);
    while(tipo!='p'&&tipo!='g')
    {
    printf("ERRO!!!\nDigite o tipo(g=graduacao/p=pos graduacao):");
    fflush(stdin);
    scanf("%c",&tipo);
    }
////////////////////////////////////////////////////////////////////////////

//ALTERAÇÃO DOS ARQUIVOS

    cont=0;
     //ALTERAÇÃO DO ARQUIVO INDICE ISBN
     fread(&lISBN,sizeof(lISBN),1,indisbn);
            while(!feof(indisbn))
            {
               if(strcmp(lISBN.id,cod)==0)
               {
                   fseek(indisbn,sizeof(lISBN)*cont,SEEK_SET);/* Posiciona para trocar conteudo */
                   strcpy(lISBN.isbn,isbn);
                   //GRAVA NA BASE DE DADOS
                   fwrite(&lISBN,sizeof(lISBN),1,indisbn);
                   fclose(indisbn);
                   break;
               }
               cont++;
               fread(&lISBN,sizeof(lISBN),1,indisbn);
            }
    //////////////////////////////////////////

    //ALTERAÇÃO DO ARQUIVO INDICE TITULO
            cont=0;
            fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
            while(!feof(indtitulo))
            {
               if(strcmp(lTITULO.id,cod)==0)
               {
                   fseek(indtitulo,sizeof(lTITULO)*cont,SEEK_SET);/* Posiciona para trocar conteudo */
                   strcpy(lTITULO.titulo,titulo);
                   //GRAVA NA BASE DE DADOS
                   fwrite(&lTITULO,sizeof(lTITULO),1,indtitulo);
                   fclose(indtitulo);
                   break;
                }
            cont++;
            fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
            }

    //ALTERA DO ARQUIVO INDICE AUTOR
            cont=0;
            fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
            while(!feof(indautor))
            {
               if(strcmp(lAUTOR.id,cod)==0)
               {
                   fseek(indautor,sizeof(lAUTOR)*cont,SEEK_SET);/* Posiciona para trocar conteudo */
                   strcpy(lAUTOR.autor,autor);
                   //GRAVA NA BASE DE DADOS
                   fwrite(&lAUTOR,sizeof(lAUTOR),1,indautor);
                   fclose(indautor);
                   break;
               }
            cont++;
            fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
            }

    //ALTERA DO ARQUIVO CATALOGO.TXT
            cont=0;
            fread(&l,sizeof(l),1,arq);
            while(!feof(arq))
            {
               if(strcmp(l.id,cod)==0)
               {
                   fseek(arq,sizeof(l)*cont,SEEK_SET);/* Posiciona para trocar conteudo */
                   strcpy(l.isbn,isbn);
                   strcpy(l.autor,autor);
                   strcpy(l.titulo,titulo);
                   strcpy(l.descricao,descricao);
                   l.tipo=tipo;
                   //GRAVA NA BASE DE DADOS
                   fwrite(&l,sizeof(l),1,arq);
                   fclose(arq);
                   printf("\nLivro Alterado Com Sucesso\n");
                   break;
               }
            cont++;
            fread(&l,sizeof(l),1,arq);
            }
     }

     else
     {
     printf("Nao existe livro cadastrado com este ID\n");
     return;
     }
}//FECHA EDITAR


void remover(char cod[4])
{
    int result;
    result=buscaID(cod);
    if(result==0)
    {
      printf("Nao existe livro cadastrado com este ID\n");
      return;
    }
    else
    {

////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////

       //ABRE ARQUIVO DE BASE DE DADOS PARA LEITURA
       arq=fopen("catalogo.txt","rb+");
       if( arq == NULL)
       {
           puts("Erro na abertura do arquivo.") ;
           system("PAUSE");
           exit(0);
       }
    //ABRE ARQUIVO INDICE ID PARA LEITURA
       indid=fopen("indiceID.txt","rb+");
       if( indid == NULL)
       {
           puts("Erro na abertura do arquivo.") ;
           system("PAUSE");
           exit(0);
       }
    //ABRE ARQUIVO INDICE ISBN PARA LEITURA
       indisbn=fopen("indiceISBN.txt","rb+");
       if( indisbn == NULL)
       {
           puts("Erro na abertura do arquivo.") ;
           system("PAUSE");
           exit(0);
       }

    //ABRE ARQUIVO INDICE AUTOR PARA LEITURA
       indautor=fopen("indiceAUTOR.txt","rb+");
       if( indautor == NULL)
       {
            puts("Erro na abertura do arquivo.") ;
            system("PAUSE");
            exit(0);
       }
    //ABRE ARQUIVO INDICE TITULO PARA LEITURA
       indtitulo=fopen("indiceTITULO.txt","rb+");
       if( indtitulo == NULL)
       {
           puts("Erro na abertura do arquivo.") ;
           system("PAUSE");
           exit(0);
       }
////////////////////////////////////////////////////////////////////////////
      int cont=0;
    //Remoção arquivo indice ID
    //ABRE ARQUIVO TEMPORARIO
       temp=fopen("temp.txt","ab");
       if( temp == NULL)
       {
          puts("Erro na abertura do arquivo.") ;
          system("PAUSE");
          exit(0);
       }
       rewind(indid);
       while(fread(&lID,sizeof(lID),1,indid))
       {
          if(strcmp(lID.id,cod)!=0)
          fwrite(&lID, sizeof(lID), 1, temp);
       }
       fclose(indid);
       fclose(temp);
       remove("indiceID.txt");
       rename("temp.txt", "indiceID.txt");
   ///////////////////////////////////////////

   //Remoção arquivo indice ISBN
   //ABRE ARQUIVO TEMPORARIO
       temp=fopen("temp.txt","ab");
       if( temp == NULL)
       {
           puts("Erro na abertura do arquivo.") ;
           system("PAUSE");
           exit(0);
       }
       rewind(indisbn);
       while(fread(&lISBN,sizeof(lISBN),1,indisbn))
       {
           if(strcmp(lISBN.id,cod)!=0)
           fwrite(&lISBN, sizeof(lISBN), 1, temp);
       }
       fclose(indisbn);
       fclose(temp);
       remove("indiceISBN.txt");
       rename("temp.txt", "indiceISBN.txt");
    //////////////////////////////////////////////

    //Remoção arquivo indice AUTOR
    //ABRE ARQUIVO TEMPORARIO
       temp=fopen("temp.txt","ab");
       if( temp == NULL)
       {
          puts("Erro na abertura do arquivo.") ;
          system("PAUSE");
          exit(0);
       }
       rewind(indautor);
       while(fread(&lAUTOR,sizeof(lAUTOR),1,indautor))
       {
          if(strcmp(lAUTOR.id,cod)!=0)
          fwrite(&lAUTOR, sizeof(lAUTOR), 1, temp);
       }
       fclose(indautor);
       fclose(temp);
       remove("indiceAUTOR.txt");
       rename("temp.txt", "indiceAUTOR.txt");
    //////////////////////////////////////////////

    //Remoção arquivo indice TITULO
    //ABRE ARQUIVO TEMPORARIO
       temp=fopen("temp.txt","ab");
       if( temp == NULL)
       {
          puts("Erro na abertura do arquivo.") ;
          system("PAUSE");
          exit(0);
       }
       rewind(indtitulo);
       while(fread(&lTITULO,sizeof(lTITULO),1,indtitulo))
       {
           if(strcmp(lTITULO.id,cod)!=0)
           fwrite(&lTITULO, sizeof(lTITULO), 1, temp);
       }
       fclose(indtitulo);
       fclose(temp);
       remove("indiceTITULO.txt");
       rename("temp.txt", "indiceTITULO.txt");
    //////////////////////////////////////////////

    //REMOVE DO ARQUIVO CATALOGO.TXT
       cont=0;
       fread(&l,sizeof(l),1,arq);
       while(!feof(arq))
       {
          if(strcmp(l.id,cod)==0)
          {
             fseek(arq,sizeof(l)*cont,SEEK_SET);
             l.rem='s';
            //GRAVA NA BASE DE DADOS
            fwrite(&l,sizeof(l),1,arq);
            fclose(arq);
            break;
          }
          cont++;
          fread(&l,sizeof(l),1,arq);
       }
       printf("Registro excluido com sucesso!\n");
    }
}//FECHA FUNÇÃO REMOVER

void restaurar()
{
    int cont=0;

////////////////////////////////////////////////////////////////////////////
//                     ABERTURA DE ARQUIVOS                               //
////////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO DE BASE DE DADOS
   arq=fopen("catalogo.txt","rb+");
    if( arq == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE ID
    indid=fopen("indiceID.txt","ab+");
    if( indid == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }


    //ABRE ARQUIVO INDICE ISBN
    indisbn=fopen("indiceISBN.txt","ab+");
    if( indisbn == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

     //ABRE ARQUIVO INDICE AUTOR
    indautor=fopen("indiceAUTOR.txt","ab+");
    if( indautor == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

    //ABRE ARQUIVO INDICE TITULO
    indtitulo=fopen("indiceTITULO.txt","ab+");
    if( indtitulo == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }
////////////////////////////////////////////////////////////////////////////
//RESTAURAÇÃO DOS ARQUIVOS

    //Restaura arquivo catalogo
    //ABRE ARQUIVO TEMPORARIO
    temp=fopen("temp.txt","ab");
    if( temp == NULL)
    {
      puts("Erro na abertura do arquivo.") ;
      system("PAUSE");
      exit(0);
    }

    //PROCEDIMENTO DE RESTAURAÇÃO
    rewind(arq);
    while(fread(&l,sizeof(l),1,arq))
    {
      if(l.rem=='s')
      {
      //RESTAURA LOGICAMENTE REGISTRO DE CATALOGO.TXT
      l.rem='n';

      //RESTAURA FISICAMENTE REGISTROS NOS ARQUIVOS INDICES
      //PARA FUTURAMENTE ORDENALOS PELO ID
      strcpy(lID.id,l.id);
      lID.rrn=l.rrn;


      strcpy(lISBN.id,l.id);
      strcpy(lISBN.isbn,l.isbn);

      strcpy(lAUTOR.id,l.id);
      strcpy(lAUTOR.autor,l.autor);


      strcpy(lTITULO.id,l.id);
      strcpy(lTITULO.titulo,l.titulo);

      //ESCREVE NOS ARQUIVOS INDICES OS REGISTROS RESTAURADOS
      fwrite(&lID,sizeof(lID),1,indid);
      fwrite(&lISBN,sizeof(lISBN),1,indisbn);
      fwrite(&lAUTOR,sizeof(lAUTOR),1,indautor);
      fwrite(&lTITULO,sizeof(lTITULO),1,indtitulo);
      printf("Registros Restaurados\n");

      }
      //ESCREVE A TROCA DA VAR REM POR 'n'
      //NO ARQUIVO CATALOGO.TXT OS REGISTROS RESTAURADOS LOGICAMENTE
      fwrite(&l, sizeof(l), 1, temp);
    }
    //FECHAMENTO DOS ARQUIVOS PARA SALVAS AS ALTERAÇÕES
    fclose(arq);
    fclose(indid);
    fclose(indisbn);
    fclose(indautor);
    fclose(indtitulo);
    fclose(temp);
    //EXCLUSÃO DO ANTIGO ARQUIVO MUDANDO PARA O NOVO
    remove("catalogo.txt");
    rename("temp.txt","catalogo.txt");
   ///////////////////////////////////////////

     //Restaura arquivo indice ID
     //ABRE ARQUIVO INDICE ID PARA LEITURA
    indid=fopen("indiceID.txt","ab+");
    if( indid == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

//PROCEDIMENTO PARA RESTAURAR OS INDICES

    liID lIDvet [80];
    int k=0;

    fread(&lID,sizeof(lID),1,indid);
    while (!feof(indid)) {
    lIDvet[k]=lID;
    fread(&lID,sizeof(lID),1,indid);
    k++;
    }

//ALGORITMO BUBBLE SORT
    int i;
    int j;
    liID aux;
 for( i = 0; i < k; i++ )
  {
    for( j = i + 1; j < k; j++ ) // sempre 1 elemento à frente
    {
      // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
      if(strcmp(lIDvet[i].id,lIDvet[j].id)>0)
      {
         aux = lIDvet[i];
         lIDvet[i] = lIDvet[j];
         lIDvet[j] = aux;
      }
    }
  } // fim da ordenação
 //////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO TEMPORARIO
    temp=fopen("temp.txt","ab");
    if( temp == NULL)
    {
      puts("Erro na abertura do arquivo.") ;
      system("PAUSE");
      exit(0);
    }
    rewind(indid);
    for(i=0;i<k;i++)
    {
        strcpy(lID.id,lIDvet[i].id);
        lID.rrn=lIDvet[i].rrn;
        fwrite(&lID,sizeof(lID),1,temp);
    }

    fclose(indid);
    fclose(temp);
    remove("indiceID.txt");
    rename("temp.txt", "indiceID.txt");
////////////////////////////////////////////////////////////////////////////


     //Restaura arquivo indice ISBN
     //ABRE ARQUIVO INDICE ISBN
    indisbn=fopen("indiceISBN.txt","ab+");
    if( indisbn == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

//PROCEDIMENTO PARA RESTAURAR OS INDICES
    liISBN lISBNvet [80];
    k=0;

    fread(&lISBN,sizeof(lISBN),1,indisbn);
    while (!feof(indisbn)) {
    lISBNvet[k]=lISBN;
    fread(&lISBN,sizeof(lISBN),1,indisbn);
    k++;
    }

//ALGORITMO BUBBLE SORT
    liISBN auxISBN;
 for( i = 0; i < k; i++ )
  {
    for( j = i + 1; j < k; j++ ) // sempre 1 elemento à frente
    {
      // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
      if(strcmp(lISBNvet[i].id,lISBNvet[j].id)>0)
      {
         auxISBN = lISBNvet[i];
         lISBNvet[i] = lISBNvet[j];
         lISBNvet[j] = auxISBN;
      }
    }
  } // fim da ordenação
 //////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO TEMPORARIO
    temp=fopen("temp.txt","ab");
    if( temp == NULL)
    {
      puts("Erro na abertura do arquivo.") ;
      system("PAUSE");
      exit(0);
    }
    rewind(indisbn);
    for(i=0;i<k;i++)
    {
        strcpy(lISBN.id,lISBNvet[i].id);
        strcpy(lISBN.isbn,lISBNvet[i].isbn);
        fwrite(&lISBN,sizeof(lISBN),1,temp);
    }

    fclose(indisbn);
    fclose(temp);
    remove("indiceISBN.txt");
    rename("temp.txt", "indiceISBN.txt");
////////////////////////////////////////////////////////////////////////////


  //Restaura arquivo indice AUTOR
     //ABRE ARQUIVO INDICE AUTOR
    indautor=fopen("indiceAUTOR.txt","ab+");
    if( indautor == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

//PROCEDIMENTO PARA RESTAURAR OS INDICES
    liAUTOR lAUTORvet [80];
    k=0;

    fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
    while (!feof(indautor)) {
    lAUTORvet[k]=lAUTOR;
    fread(&lAUTOR,sizeof(lAUTOR),1,indautor);
    k++;
    }

//ALGORITMO BUBBLE SORT
    liAUTOR auxAUTOR;
 for( i = 0; i < k; i++ )
  {
    for( j = i + 1; j < k; j++ ) // sempre 1 elemento à frente
    {
      // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
      if(strcmp(lAUTORvet[i].id,lAUTORvet[j].id)>0)
      {
         auxAUTOR = lAUTORvet[i];
         lAUTORvet[i] = lAUTORvet[j];
         lAUTORvet[j] = auxAUTOR;
      }
    }
  } // fim da ordenação
 //////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO TEMPORARIO
    temp=fopen("temp.txt","ab");
    if( temp == NULL)
    {
      puts("Erro na abertura do arquivo.") ;
      system("PAUSE");
      exit(0);
    }
    rewind(indautor);
    for(i=0;i<k;i++)
    {
        strcpy(lAUTOR.id,lAUTORvet[i].id);
        strcpy(lAUTOR.autor,lAUTORvet[i].autor);
        fwrite(&lAUTOR,sizeof(lAUTOR),1,temp);
    }

    fclose(indautor);
    fclose(temp);
    remove("indiceAUTOR.txt");
    rename("temp.txt", "indiceAUTOR.txt");
////////////////////////////////////////////////////////////////////////////

 //Restaura arquivo indice TITULO
    //ABRE ARQUIVO INDICE TITULO
    indtitulo=fopen("indiceTITULO.txt","ab+");
    if( indtitulo == NULL)
    {
    puts("Erro na abertura do arquivo.") ;
    system("PAUSE");
    exit(0);
    }

//PROCEDIMENTO PARA RESTAURAR OS INDICES
    liTITULO lTITULOvet [80];
    k=0;

    fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
    while (!feof(indtitulo)) {
    lTITULOvet[k]=lTITULO;
    fread(&lTITULO,sizeof(lTITULO),1,indtitulo);
    k++;
    }

//ALGORITMO BUBBLE SORT
    liTITULO auxTITULO;
 for( i = 0; i < k; i++ )
  {
    for( j = i + 1; j < k; j++ ) // sempre 1 elemento à frente
    {
      // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
      if(strcmp(lTITULOvet[i].id,lTITULOvet[j].id)>0)
      {
         auxTITULO = lTITULOvet[i];
         lTITULOvet[i] = lTITULOvet[j];
         lTITULOvet[j] = auxTITULO;
      }
    }
  } // fim da ordenação
 //////////////////////////////////////////////////////////////////////////

    //ABRE ARQUIVO TEMPORARIO
    temp=fopen("temp.txt","ab");
    if( temp == NULL)
    {
      puts("Erro na abertura do arquivo.") ;
      system("PAUSE");
      exit(0);
    }
    rewind(indtitulo);
    for(i=0;i<k;i++)
    {
        strcpy(lTITULO.id,lTITULOvet[i].id);
        strcpy(lTITULO.titulo,lTITULOvet[i].titulo);
        fwrite(&lTITULO,sizeof(lTITULO),1,temp);
    }

    fclose(indtitulo);
    fclose(temp);
    remove("indiceTITULO.txt");
    rename("temp.txt", "indiceTITULO.txt");
////////////////////////////////////////////////////////////////////////////

}//Fecha função restaurar

////////////////////////////////////////////////////////////////////////////
//                           MAIN                                         //
////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
    //DECLARAÇÃO DE VARIAVEIS PARA CHAMADA DE FUNÇÕES
    char isbn[15];
    char autor[50];
    char titulo[50];
    char cod[4];
    char idR[4];
    int opcao=-1;
    while(opcao!=99999)
    {
    printf("_______________________________________\n");
    printf("\tAutor: Thiago Moreira\n");
    printf("_______________________________________\n\n");
    printf("____________MENU_______________________\n\n");
    printf("1- Inserir Livro\n");
    printf("2- Ler Arquivo\n");
    printf("3- Editar\n");
    printf("4- Pesquisa por ID\n");
    printf("5- Pesquisa por ISBN\n");
    printf("6- Pesquisa por AUTOR\n");
    printf("7- Pesquisa por TITULO\n");
    printf("8- Remocao por ID\n");
    printf("9- Restaurar registros excluidos\n");
    printf("10- Para sair\n");
    printf("_______________________________________\n\n");
    printf("Digite a opcao desejada:");
    scanf("%d",&opcao);
    switch(opcao)
    {
        case 1:
        insereArquivo();
        printf("\nLivro Inserido Com Sucesso\n");
        break;

        case 2:
        leArquivo();
        break;

        case 3:
        printf("Digite o ID do livro para editar:");
        fflush(stdin);
        scanf("%s",&cod);
        editar(cod);
        break;

        case 4:
        printf("Digite o ID que deseja buscar:");
        fflush(stdin);
        scanf("%s",&cod);
        buscaID(cod);
        break;

        case 5:

        printf("Digite o ISBN que deseja buscar:");
        fflush(stdin);
        scanf("%s",&isbn);
        buscaISBN(isbn);
        break;

        case 6:

        printf("Digite o nome do AUTOR que deseja buscar:");
        fflush(stdin);
        scanf("%[^\n]",&autor);
        while(strlen(autor)==0)
        {
           printf("Digite o nome do AUTOR que deseja buscar:");
           fflush(stdin);
           scanf("%[^\n]",&autor);
        }

        buscaAUTOR(autor);

        break;


        case 7:
        printf("Digite o nome do TITULO que deseja buscar:");
        fflush(stdin);
        scanf("%[^\n]",&titulo);
        while(strlen(titulo)==0)
        {
           printf("Digite o nome do TITULO que deseja buscar:");
           fflush(stdin);
           scanf("%[^\n]",&titulo);
        }
        buscaTITULO(titulo);
        break;

        case 8:
        printf("Digite o ID para realizar a remocao:");
        fflush(stdin);
        scanf("%s",&idR);
        remover(idR);

        break;

        case 9:

        restaurar();

        break;

        case 10:
        exit(0);
        break;

        default:
        printf("Opcao invalida!!!\n\n");
        break;

    }
   }

  system("PAUSE");
  return 0;
}
