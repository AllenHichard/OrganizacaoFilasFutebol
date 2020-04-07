/*******************************************************************************
Autor: ALLEN HICHARD MARQUES DOS SANTOS
Componente Curricular: Algoritmos I
Concluido em: 09/07/2014
Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
******************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
/*
ESTRUTURA QUE GUARDA AS INFORMA��ES DOS TORCEDORES DA LISTA DO ARQUIVO FILA.TXT, ONDE CADA TORCEDOR
RECEBE O PRIMEIRO NOME, CATEGORIA, BLOCO E ASSENTO, SENDO QUE TODO O REGISTO CHAMADO ARQUIVO FOI
APELIDADO PELO NOME ARQ, PARA ACESSAR AS INFORMA��ES DA LISTA TANTO PELO NOME QUANTO SEU APELIDO.
*/
typedef struct arquivo
    {
     char nome[20];
     int cat, bl, ass;
     struct arquivo *prox;
    }arq;
/*
ESTRUTURA OPCIONAL PARA DIFERENCIAR DOS DEMAIS C�DIGOS, POR TER MOSTRADO MEU C�DIGO A ALGUNS COLEGAS
PREFERIR MODIFICAR E FAZER COM OUTRA ALTERNATIVA, PARA N�O TER O RISCO DE PL�GIO, ELA AUXILIA UMA ALOCA��O
DIN�MICA DENTRO DO C�DIGO PARA GUARDAR AS INFORMA��ES DOS PORT�ES ABERTOS, GUARDANDO NO VETOR.
*/
typedef struct filho
    {
     int port;
    }cada;
/*
PROT�TIPO DAS FUN��ES DAS LISTAS ENCADEADAS
CADA FUN��O SER� EXPLICADA NO SEU EXCOPO, NO FINAL DO C�DIGO
*/
void inserefila(int i, struct arquivo **primeirofila, struct arquivo **ultimofila);
void imprimefila(struct arquivo **primeirofila);
void removerfila(struct arquivo **primeirofila);
//corpo principal do programa
main()
{
     struct arquivo *primeirofila1=NULL;//armazenas as informa��es da primeira fila
     struct arquivo *ultimofila1;//guarda a informa��o do ultimo da fila
     struct arquivo *primeirofila2=NULL;//armazenas as informa��es da segunda fila
     struct arquivo *ultimofila2;//guarda a informa��o do ultimo da fila
     struct arquivo *primeirofila3=NULL;//armazenas as informa��es da terceira fila
     struct arquivo *ultimofila3;//guarda a informa��o do ultimo da fila
     int qlinhas=1;//conta a quantidade de torcedores, iniciada com um porque na ultimo torcedor nao conta como mais um torcedor;
     int caractere;//auxilia na contagem quanto das linhas de torcedores, como dos portoes abertos
     int i=0;//indice do vetor que guardas as informa��es da lista;
     int j=0;//indice do vetor que guardas as informa��es da arquivo vai meu filho;
     int portao=0;//conta as quantidades dos portoes que serao abertos
     int porta1=0;// conta os torcedores que passaram pelo primeiro portao
     int porta2=0;// conta os torcedores que passaram pelo segundo portao
     int porta3=0;// conta os torcedores que passaram pelo terceiro portao
     FILE *fila;//cria um ponteiro para o tipo de arquivo
     fila = fopen("fila.txt", "r");//guarda no ponteiro o arquivo que ser� aberto
     //caso na execu��o o arquivo fila.txt n�o for encontrado, a mensagem a seguir � mostrada informando que o arquivo nao existe.
     //o "r" usado ap�s o nome do arquivo � para o modo de leitura.
     if(fila == NULL)
     {
            printf("esse arquivo nao existe");
            getch();
            return 0 ;
     }
     /*
     caso o arquivo seja encontrado o arquivo fila ser� percorrido enquanto n�o for encontrado EOF(end of file"final do arquivo")
     A fun��o "fgetc" far� com que o arquivo seja percorrido caracter por caracter e toda vez que encontrar uma quebra de linha contar�
     mais um, a vari�vel que recebe esse adicional inicializa com 1 pois no �ltimo torcedor inserido n�o h� uma quebra de linha
     */
      while((caractere = fgetc(fila)) != EOF)
      {
            if(caractere == '\n')
            {
            qlinhas++;
            }
      }
      fclose(fila);//fecha o arquivo.
      //printf("total de torcedores na fila %d\n", qlinhas);
      fila = fopen("fila.txt", "r");
      if(fila == NULL)
      {
             printf("esse arquivo nao existe");
             getch();
             return 0 ;
      }
      /*
      Aloca din�nicamente a quantidade de torcedores para que n�o tenha um desperd�cio de mem�ria
      Essa aloca��o se comporta de acordo com a quantidade de torcedores inseridos no arquivo fila.txt
      Caso a mem�ria do comp�tador n�o for suficiente para a aloca��o a mensagem de erro ser� apresentada.
      */
      arq *a = (arq*)calloc(qlinhas,(sizeof(arq)));
      if(!a)
            printf("\n\nErro! Mem�ria Insuficiente!\n");
      else
	  {
            while((fscanf(fila,"%s categoria %d bloco %d assento %d", a[i].nome, &a[i].cat, &a[i].bl, &a[i].ass)) != EOF)
            {
            //printf("%s categoria %d bloco %d assento %d\n",a[i].nome, a[i].cat, a[i].bl, a[i].ass);
            i++;
            }
      fclose(fila);
      }
      //getch();
                          //ORGANIZA��O EM TR�S FILAS DIN�MICAS
     /*
     A DIVIS�O EM FILAS � DE ACORDO COM SUA CATEGORIA, CADA TORCEDOR TEM UMA CATEGORIA QUE PODE SER 1, 2 0U 3,
     NA PRIMEIRA FILA OS TORCEDORES DA CATEGORIA 1 E ASSIM POR DIANTE. A FORMA QUE A FILA � ORGANIZADA � POR ORDEM
     DE CHEGADA, ENT�O O PRIMEIRO A CHEGAR � O PRIMEIRO DA FILA SE ACORDO COM SUA CATEGORIA E ASSIM POR DIANTE, OU SEJA
     OS TORCEDORES DE MODO QUE FOREM CHEGANDO V�O FICANDO NO FINAL DA FILA.
     AP�S A FILA FORMADA CASO NECESS�RIO PODE PEDIR UMA FUN��O IMPRIMIRFILA ABAIXO QUE VAI VER SUA POSI��ES E MOSTRAR NA TELA
     QUAL POSI��O TEM CADA CANDIDATO
     */
     //printf("primeira fila\n");
     for(i=0; i<=qlinhas; i++)
     {
            if(a[i].cat==1)
            {
            inserefila(i, &primeirofila1,&ultimofila1);
            }
     //imprimefila(&primeirofila1);
     //printf("segunda fila\n");
            else if(a[i].cat==2)
            {
            inserefila(i,&primeirofila2,&ultimofila2);
            }
     //imprimefila(&primeirofila2);
     //printf("terceira fila\n");
            else if(a[i].cat==3)
            {
            inserefila(i,&primeirofila3,&ultimofila3);
            }
     }
     //imprimefila(&primeirofila3);

                          //FIM DA ORGANIZA��O EM TR�S FILAS
      /*
      Abertura do segundo arquivo do programa: o arquivo vaimeufilho, esse arquivo � inseridos n�meros de um a tr�s
      esse n�meros s�o os port�es a serem aberto, os torcedores passam por esses port�es de acordo com sua categoria
      condi��es que seram explicadas abaixo
      */
      FILE *vaimeufilho;
      vaimeufilho = fopen("vai_meu_filho.txt", "r");
      if(vaimeufilho == NULL)
      {
             printf("esse arquivo nao existe");
             getch();
             return 0 ;
      }
      while((caractere = fgetc(vaimeufilho)) != EOF)
      {
             if(caractere != ' '&&caractere!='\n')
             {
             portao++;
             }
      }
      //printf("numero de portoes abertos  %d\n", portao);
      fclose(vaimeufilho);
      vaimeufilho = fopen("vai_meu_filho.txt", "r");
      if(vaimeufilho == NULL)
      {
             printf("esse arquivo nao existe");
             getch();
             return 0 ;
      }
      /*
      Como citado no registro filho, essa � a aloca��o que guarda os port�es em cada posi��o do vetor
      ent�o as informa��es de todos os port�es do arquivo vai meu filho ficam guardados, podendo assim acessar
      seu conte�do quando necess�rio
      */
      cada *b = (cada*)calloc(portao,(sizeof(cada)));
      if(!b)
            printf("\n\nErro! Mem�ria Insuficiente!\n");
      else
	  {
             while((fscanf(vaimeufilho,"%d", &b[j].port)) != EOF)
             {
             //printf("%d ",b[j].port);
             j++;
             }
      fclose(vaimeufilho);
      }
      //getch();
       /*
       cria��o do arquivo log.txt. O arquivo � aberto no modo w+, ou seja cria um arquivo para guardar informa��es
       informa��es essas que seram a ordem de passagem pelo port�o de cada torcedor e a quantidade de quantos torcedores
       passaram por cada port�o
       */
       FILE *log;
       log = fopen("log.txt", "w+");
       fprintf(log,"Entrada\n");
       arq *aux1,*aux2,*aux3 ;
       for(j=0; j<portao; j++)
       {
            aux1=primeirofila1;
            aux2=primeirofila2;
            aux3=primeirofila3;
       /*
        condi��o para o primeiro port�o, quando for aberto o primeiro port�o, ser� analisado a categoria dos torcedores.
        os torcedores que podem entrar pelo primeiro port�o s�o os da categoria 1 e 3, dando prefer�ncia ao da primeira
        categoria, se n�o haver mais nenhum torcedores tanto na primeira quanto na terceira fila, ser� mostrado no arquivo none
        que simboliza que n�o houve torcedor para o port�o aberto.
       */
            if(b[j].port==1)
            {
            	porta1++;
                    if(primeirofila1!=NULL)
                    {
               		fprintf(log,"portao %d categoria %d  %s bloco %d assento %d\n", b[j].port, a[aux1->cat].cat, a[aux1->cat].nome, a[aux1->cat].bl, a[aux1->cat].ass);
	               	removerfila(&primeirofila1);
	               //getch();
                    }
                    else if(primeirofila3!=NULL)
                    {
                	fprintf(log,"portao %d categoria %d  %s bloco %d assento %d\n", b[j].port, a[aux3->cat].cat, a[aux3->cat].nome, a[aux3->cat].bl, a[aux3->cat].ass);
                	removerfila(&primeirofila3);
                	//getch();
                    }
                    else
                    {
                	fprintf(log,"portao %d none \n",b[j].port);
                	porta1--;
                    }
            }
          /*
          condi��o para o segundo port�o, quando for aberto o segundo port�o, ser� analisado a categoria dos torcedores.
          os torcedores que podem entrar pelo segundo port�o s�o os da categoria 2 e 3, dando prefer�ncia ao da segunda
          categoria, se n�o haver mais nenhum torcedores tanto na segunda quanto na terceira fila, ser� mostrado no arquivo none
          que simboliza que n�o houve torcedor para o port�o aberto.
          */
           else if(b[j].port==2)
           {
                porta2++;
                    if(primeirofila2!=NULL)
                    {
                    fprintf(log,"portao %d categoria %d  %s bloco %d assento %d\n", b[j].port, a[aux2->cat].cat, a[aux2->cat].nome, a[aux2->cat].bl, a[aux2->cat].ass);
                    removerfila(&primeirofila2);
                    //getch();
                    }
                    else if(primeirofila3!=NULL)
                    {
                    fprintf(log,"portao %d categoria %d  %s bloco %d assento %d\n", b[j].port, a[aux3->cat].cat, a[aux3->cat].nome, a[aux3->cat].bl, a[aux3->cat].ass);
                    removerfila(&primeirofila3);
                   //getch();
                    }
                    else
                    {
                    fprintf(log,"portao %d none \n",b[j].port);
                    porta2--;
                    }
             }
          /*
          condi��o para o terceiro port�o, quando for aberto o terceiro port�o, ser� analisado a categoria dos torcedores.
          o torcedor que pode entrar pelo terceiro port�o � apenas o da categoria 3, se n�o haver mais nenhum torcedor
          da terceira fila, ser� mostrado no arquivo none, que simboliza que n�o houve torcedor para o port�o aberto.
          */
           else if(b[j].port==3)
           {
                    porta3++;
                    if(primeirofila3!=NULL)
                    {
                    fprintf(log,"portao %d categoria %d  %s bloco %d assento %d\n", b[j].port, a[aux3->cat].cat, a[aux3->cat].nome, a[aux3->cat].bl, a[aux3->cat].ass);
                    removerfila(&primeirofila3);
                    //getch();
                    }
                    else
                    {
                    fprintf(log,"portao %d none \n",b[j].port);
                    porta3--;
                    }
           }
       }
       //getch();
       //quantidades de torcedores que passam por cada tipo de port�o, dentro de cada condi��o acima � somado
       //quantos passam pelo respectivo port�o para mostrar no arquivo log.txt
       fprintf(log,"Total\n");
       fprintf(log,"portao 1 %d torcedor(es) \n", porta1);//torcedores que passaram pelo primeiro port�o
       fprintf(log,"portao 2 %d torcedor(es) \n", porta2);//torcedores que passaram pelo segundo port�o
       fprintf(log,"portao 3 %d torcedor(es) \n", porta3);//torcedores que passaram pelo terceiro port�o
       fclose(log);
}
     /*
     FUN��O QUE RECEBE COMO PAR�METRO OS PONTEIROS DA FILA, ENT�O ELA RECEBE TR�S PONTEIROS DIFERENTES
     ONDE SE O PONTEIRO FOR VAZIO ELE GUARDA O PRIMEIRO TORCEDOR DE CADA RESPECTIVA FILA, AP�S SE J� TIVER
     TORCEDOR NO RESPECTIVO PONTEIRO ELE GUARDA O PROXIMO DEPOIS DO PRIMEIRO TORCEDOR E ASSIM POR DIANTE
     SENDO COLOCADO UM PRONTEIRO ADICIONAL QUE GUARDA SEMPRE O �LTIMO TORCEDOR, ESSE �LTIMO PONTEIRO
     SERVE PARA N�O TER NECESSIDADE DE PERCORRER A LISTA PARA ENCONTRAR O �LTIMO, FACILITA ENT�O A INSER��O.
     */
     void inserefila(int i,struct arquivo **primeirofila, struct arquivo **ultimofila)
     {
        struct arquivo *aux;
        aux = (struct arquivo*)malloc(sizeof(struct arquivo));
        aux->cat = i;
        if((*primeirofila)==NULL)
        {
            aux->prox =NULL;
            (*primeirofila) = aux;
            (*ultimofila) = (*primeirofila);
        }
        else
        {
            (*ultimofila)->prox=aux;
            (*ultimofila)=(*ultimofila)->prox;
            aux->prox=NULL;
        }
     }
     /*
     PRECORRE A LISTA E IMPRIME O �NDICE DO VETOR ONDE ESTAR CADA TORCEDOR, OU SEJA POR EXEMPLO SE ESSA FUN��O FOR CHAMADO
     PARA IMPRIMIR OS TORCEDORES DA SEGUNDA CATEGORIA, ELA ME MOSTRA QUAIS AS POSI��ES DO VETOR TEM TORCEDORES DA SEGUNDA CATEGORIA
     */
     void imprimefila(struct arquivo **primeirofila)
     {
        struct arquivo *aux;
        aux=(*primeirofila);
        while(aux!=NULL)
        {
            printf("item = %d\n", aux->cat);
            aux=aux->prox;
        }
     }
      /*
      FUN��O QUE REMOVE O PRIMEIRO DA FILA DE CADA RESPECTIVO PONTEIRO, ELA PEGA O PRIMEIRO DA FILA E GUARDA EM UMA VARI�VEL
      DEPOIS ESSE PRIMEIRO DA FILA RECEBE O SEGUNDO DA FILA, TORNANDO ESSE SEGUNDO O PRIMEIRO DA FILA.
      */
     void removerfila(struct arquivo **primeirofila)
     {
        struct arquivo *aux;
        aux = (*primeirofila);
        (*primeirofila)=(*primeirofila)->prox;
        free(aux);
     }

//FINAL DO ALGORITMO DO TERCEIRO PBL

//IN�CIO DO MANUAL DE USO

                                            //OBJETIVO DO PROGRAMA
                                    //RETIRADO DO PR�PRIO TEXTO DO PROBLEMA
/*
Torcedores ser�o divididos em: categoria 1, categoria 2 e categoria 3. Para os port�es, a priori, ser�o considerados
apenas 3: port�o 1, port�o 2 e port�o 3. O port�o 1 foi definido como entrada apenas dos torcedores das categorias 1 e 3,
no entanto, a prioridade � da categoria 1. O port�o 2 foi definido como entrada dos torcedores das categorias 2 e 3, no
entanto, a prioridade � da categoria 2. Por fim, o port�o 3 foi definido como entrada somente dos torcedores da categoria 3.
A simula��o do sistema ser� da seguinte forma. A fila de torcedores ser� dada por um arquivo texto chamado fila.txt. O sistema
dever� ler este arquivo e criar outras tr�s filas, com todos os dados dos torcedores, de acordo com as suas respectivas
categorias. O acesso aos port�es ser� regulado por um sistema que avaliar� qual o port�o menos congestionado e indicar� qual o
torcedor dever� entrar por este port�o, respeitando as filas e as permiss�es e prioridades do port�o. Este procedimento ser�
simulado atrav�s da leitura de um arquivo texto chamado vai_meu_filho.txt, que indicar�, em ordem, qual port�o est� menos
congestionado. Para cada passagem de um torcedor por um port�o, o sistema dever� gravar em um arquivo texto chamado
log.txt, as seguintes informa��es: port�o, a categoria, o nome, o bloco e o assento do torcedor. Quando encerrar a leitura do arquivo
vai_meu_filho.txt, a quantidade total de torcedores que passaram por cada port�o tamb�m dever� ser registrada no final do arquivo log.txt.
*/

                                 //COMO UTILIZAR O PROGRAMA

                                    //PRIMEIRO PASSO

//O USU�RIO TEM QUE CRIAR UM ARQUIVO CHAMADO FILA DO TIPO DE TXT.
//EXEMPLO: NOME DO ARQUIVO: FILA.TXT, SE FEITO NO BLOCO DE NOTAS O ARQUIVO ALTOMATICAMENTE COLOCA O TXT
//SENDO APENAS NECESS�RIO A INFORMA��O DO NOME
//AP�S O ARQUIVO FEITO, PODE INSERIR QUALQUER QUANTIDADE DE PESSOAS EM UMA FILA UNICA.
//EXEMPLO DO QUE DEVE CONTER NESSE TIPO DE ARQUIVO ARQUIVO:
          /*
          joao categoria 1 bloco 410 assento 9
          maria categoria 3 bloco 502 assento 7
          zezim categoria 2 bloco 310 assento 22
          ciclano categoria 1 bloco 620 assento 15
          beltrano categoria 2 bloco 330 assento 30
          fulano categoria 3 bloco 500 assento 20
          marcos categoria 3 bloco 500 assento 21
          */
//O ARQUIVO TEM QUE SER INSCRITO NESSA ORDEM DE INFORMA��O, PARA A LEITURA CORRETA DO ARQUIVO
//COMO O ARQUIVO CONTA OS TORCEDORES POR LINHAS DE ARQUIVO, ENTAO J� � CONTADO DESDE O PRIMEIRO ESPA�O VAZIO
//OU SEJA NO ULTIMO TORCEDOR A SER INSERIDO "NAO PODE HAVER QUEBRA DE LINHA".


                                    //SEGUNDO PASSO

//APOS A CRIA��O DO ARQUIVO FILA.TXT O PROGRAMA PEDIR� OUTRO TIPO DE ARQUIVO CHAMADO VAIMEUFILHO
//EXEMPLO: NOME DO ARQUIVO: VAIMEUFILHO.TXT, SE FEITO NO BLOCO DE NOTAS O ARQUIVO ALTOMATICAMENTE COLOCA O TXT
//SENDO APENAS NECESS�RIO A INFORMA��O DO NOME
//NELE SER� COLOCADO AS INFORMA��ES DOS PORTOES A SEREM ABERTO
//EXEMPLO DO QUE DEVE CONTER NESSE TIPO DE ARQUIVO ARQUIVO:
          /*
          1 3 1 2 1 2 2 1
          */
//S� SERAM CONSIDERADOS TRES TIPOS DE PORTOES 1, 2 E 3.


                                      //TERCEIRO PASSO

                                //GERANDO O ARQUIVO LOG.TXT

//SER� FEITO UMA ANALISE DE CADA PORTAO ABERTO EM ORDEM
//O PORTAO ATUAL ANALISARA A FILA DO TORCEDOR
//COMO CITADO EM OBJETIVOS ANALISAR� AS CONDI�OES DO PORTAO ABERTO ATUALMENTE
//SE O TORCEDOR FOR APTO A PASSAR PELO PORTAO O ARQUIVO LOG.TXT ESCREVE SEUS DADOS
//O ARQUIVO LOG.TXT � CRIADO AUTOMATICAMENTE PELO PROGRAMA
//DE ACORDO COM A INFORMA��ES ACIMA, SE FOR FEITO OS DOIS ARQUIVO DE ACORDO COM AS INFORMA��ES CITADAS
//O ARQUIVO LOG.TXT GUARDAR� AS SEGUINTES INFORMA��ES
/*
                                          SA�DAS DO PROGRAMA
  portao 1 categoria 1  joao bloco 410 assento 9
  portao 3 categoria 3  maria bloco 502 assento 7
  portao 1 categoria 1  ciclano bloco 620 assento 15
  portao 2 categoria 2  zezim bloco 310 assento 22
  portao 1 categoria 3  fulano bloco 500 assento 20
  portao 2 categoria 2  beltrano bloco 330 assento 30
  portao 2 categoria 3  marcos bloco 500 assento 21
  portao 1 none
  Total
  portao 1 torcedores 3
  portao 2 torcedores 3
  portao 3 torcedores 1

  NO CASO ACIMA FOI LIDO O ARQUIVO FILA.TXT E ANALISADO SUA CATEGORIA DE ACORDO COM O PORT�O ABERTO NO MOMENTO
  DA� ANALISADO SUA PRIORI DE ACORDO QUE O PORT�O E SUA CATEGORIA, E CADA VEZ QUE PASSA O TORCEDOR PELO PORT�O
  � CONTABILIZADO, NO �LTIMO PORT�O COMO N�O TINHA NINGU�M PARA ENTRAR O SEGUINTE NOME � INSCRITO NO LOG.TXT
  "NONE"
*/
/*
                             TESTES EFETUADOS PARA O FUNCIONAMENTO DO PROGRAMA

  Caso�1:�O�n�mero�de�torcedores�ser�maior�que�o�n�mero�de�port�es�que�ser�o�abertos.
  Caso�2:�Imprimir�todas�as�filas�e�verificar�se�elas�est�o�devidamente�organizadas.
  Caso�3:�Colocar�torcedores�somente�nas�categorias�1�e�2�e�abrir�somente�o�port�o�3.
  Caso�4:�Colocar�apenas�torcedores�na�categoria�3�e�abrir�somente�os�port�es�1�e�2.
  caso 5: Abri o fila.txt sem nenhuma torcedor
  caso 5: abri o vaimeufilho sem nenhum port�o a ser aberto
  caso 6: O n�mero de port�es serem maior do que o n�mero de torcedores
  caso 7: Organizar o vaimeufilho um abaixo do outro
  caso 8: foram colocados torcedores com categorias diferentes do proposto pelo problema
*/



                                  //SITUA��ES EM QUE O PROGRAMA N�O FUNCIONA

//N�O PODE SER QUEBRADO LINHA NO ULTIMO TORCEDOR INSERIDO NO ARQUIVO LOG.TXT
//N�O PODE COLOCAR NUMEROS DE DOIS DIGITOS OU MAIS NO ARQUIVO VAIMEUFILHO, ISSO OCASIONAR� ERRO DE EXECU��O
//SE COLOCAR N�MEROS MENORES QUE 1 E MAIORES QUE 3 N�O TEM PROBLEMA ALGUM, S� QUE ESSA INFORMA��O SER� PERDIDA NA EXECU��O


                                          //O PROGRAMA

/*
O software foi desenvolvido em um sistema operacional Windows, foi utilizado o DEV C++, que � um compilador de c�digos de
linguagem de programa��o �c� e �c++�. al�m disso, para ter certeza do completo funcionamento, foi testado o c�digo no sistema
operacional Linux, como tem algumas condi��es que n�o existem no Linux a exemplo de algumas bibliotecas, foram feitos apenas
adapta��es para o teste, mas n�o houve modifica��es de condi��es do c�digo.
*/

                                          //MELHORIAS DO C�DIGO

          /*
          ->AUMENTAR A CAPACIDADE DE PORTOES LIDOS, PARA MAIS CATEGORIAS DE TORCEDORES
          ->GERAR ARQUIVOS COM CADA CATEGORIA DE TORCEDOR
          ->INTERFACE GR�FICA DAS FILAS
          */



//FINAL DO MANUAL DE USO



