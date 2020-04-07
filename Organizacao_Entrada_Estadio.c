/*******************************************************************************
Autor: ALLEN HICHARD MARQUES DOS SANTOS
Componente Curricular: Algoritmos I
Concluido em: 09/07/2014
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
/*
ESTRUTURA QUE GUARDA AS INFORMAÇÕES DOS TORCEDORES DA LISTA DO ARQUIVO FILA.TXT, ONDE CADA TORCEDOR
RECEBE O PRIMEIRO NOME, CATEGORIA, BLOCO E ASSENTO, SENDO QUE TODO O REGISTO CHAMADO ARQUIVO FOI
APELIDADO PELO NOME ARQ, PARA ACESSAR AS INFORMAÇÕES DA LISTA TANTO PELO NOME QUANTO SEU APELIDO.
*/
typedef struct arquivo
    {
     char nome[20];
     int cat, bl, ass;
     struct arquivo *prox;
    }arq;
/*
ESTRUTURA OPCIONAL PARA DIFERENCIAR DOS DEMAIS CÓDIGOS, POR TER MOSTRADO MEU CÓDIGO A ALGUNS COLEGAS
PREFERIR MODIFICAR E FAZER COM OUTRA ALTERNATIVA, PARA NÃO TER O RISCO DE PLÁGIO, ELA AUXILIA UMA ALOCAÇÃO
DINÂMICA DENTRO DO CÓDIGO PARA GUARDAR AS INFORMAÇÕES DOS PORTÕES ABERTOS, GUARDANDO NO VETOR.
*/
typedef struct filho
    {
     int port;
    }cada;
/*
PROTÓTIPO DAS FUNÇÕES DAS LISTAS ENCADEADAS
CADA FUNÇÃO SERÁ EXPLICADA NO SEU EXCOPO, NO FINAL DO CÓDIGO
*/
void inserefila(int i, struct arquivo **primeirofila, struct arquivo **ultimofila);
void imprimefila(struct arquivo **primeirofila);
void removerfila(struct arquivo **primeirofila);
//corpo principal do programa
main()
{
     struct arquivo *primeirofila1=NULL;//armazenas as informações da primeira fila
     struct arquivo *ultimofila1;//guarda a informação do ultimo da fila
     struct arquivo *primeirofila2=NULL;//armazenas as informações da segunda fila
     struct arquivo *ultimofila2;//guarda a informação do ultimo da fila
     struct arquivo *primeirofila3=NULL;//armazenas as informações da terceira fila
     struct arquivo *ultimofila3;//guarda a informação do ultimo da fila
     int qlinhas=1;//conta a quantidade de torcedores, iniciada com um porque na ultimo torcedor nao conta como mais um torcedor;
     int caractere;//auxilia na contagem quanto das linhas de torcedores, como dos portoes abertos
     int i=0;//indice do vetor que guardas as informações da lista;
     int j=0;//indice do vetor que guardas as informações da arquivo vai meu filho;
     int portao=0;//conta as quantidades dos portoes que serao abertos
     int porta1=0;// conta os torcedores que passaram pelo primeiro portao
     int porta2=0;// conta os torcedores que passaram pelo segundo portao
     int porta3=0;// conta os torcedores que passaram pelo terceiro portao
     FILE *fila;//cria um ponteiro para o tipo de arquivo
     fila = fopen("fila.txt", "r");//guarda no ponteiro o arquivo que será aberto
     //caso na execução o arquivo fila.txt não for encontrado, a mensagem a seguir é mostrada informando que o arquivo nao existe.
     //o "r" usado após o nome do arquivo é para o modo de leitura.
     if(fila == NULL)
     {
            printf("esse arquivo nao existe");
            getch();
            return 0 ;
     }
     /*
     caso o arquivo seja encontrado o arquivo fila será percorrido enquanto não for encontrado EOF(end of file"final do arquivo")
     A função "fgetc" fará com que o arquivo seja percorrido caracter por caracter e toda vez que encontrar uma quebra de linha contará
     mais um, a variável que recebe esse adicional inicializa com 1 pois no último torcedor inserido não há uma quebra de linha
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
      Aloca dinânicamente a quantidade de torcedores para que não tenha um desperdício de memória
      Essa alocação se comporta de acordo com a quantidade de torcedores inseridos no arquivo fila.txt
      Caso a memória do compútador não for suficiente para a alocação a mensagem de erro será apresentada.
      */
      arq *a = (arq*)calloc(qlinhas,(sizeof(arq)));
      if(!a)
            printf("\n\nErro! Memória Insuficiente!\n");
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
                          //ORGANIZAÇÃO EM TRÊS FILAS DINÃMICAS
     /*
     A DIVISÃO EM FILAS É DE ACORDO COM SUA CATEGORIA, CADA TORCEDOR TEM UMA CATEGORIA QUE PODE SER 1, 2 0U 3,
     NA PRIMEIRA FILA OS TORCEDORES DA CATEGORIA 1 E ASSIM POR DIANTE. A FORMA QUE A FILA É ORGANIZADA É POR ORDEM
     DE CHEGADA, ENTÃO O PRIMEIRO A CHEGAR É O PRIMEIRO DA FILA SE ACORDO COM SUA CATEGORIA E ASSIM POR DIANTE, OU SEJA
     OS TORCEDORES DE MODO QUE FOREM CHEGANDO VÃO FICANDO NO FINAL DA FILA.
     APÓS A FILA FORMADA CASO NECESSÁRIO PODE PEDIR UMA FUNÇÃO IMPRIMIRFILA ABAIXO QUE VAI VER SUA POSIÇÕES E MOSTRAR NA TELA
     QUAL POSIÇÃO TEM CADA CANDIDATO
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

                          //FIM DA ORGANIZAÇÃO EM TRÊS FILAS
      /*
      Abertura do segundo arquivo do programa: o arquivo vaimeufilho, esse arquivo é inseridos números de um a três
      esse números são os portões a serem aberto, os torcedores passam por esses portões de acordo com sua categoria
      condições que seram explicadas abaixo
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
      Como citado no registro filho, essa é a alocação que guarda os portões em cada posição do vetor
      então as informações de todos os portões do arquivo vai meu filho ficam guardados, podendo assim acessar
      seu conteúdo quando necessário
      */
      cada *b = (cada*)calloc(portao,(sizeof(cada)));
      if(!b)
            printf("\n\nErro! Memória Insuficiente!\n");
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
       criação do arquivo log.txt. O arquivo é aberto no modo w+, ou seja cria um arquivo para guardar informações
       informações essas que seram a ordem de passagem pelo portão de cada torcedor e a quantidade de quantos torcedores
       passaram por cada portão
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
        condição para o primeiro portão, quando for aberto o primeiro portão, será analisado a categoria dos torcedores.
        os torcedores que podem entrar pelo primeiro portão são os da categoria 1 e 3, dando preferência ao da primeira
        categoria, se não haver mais nenhum torcedores tanto na primeira quanto na terceira fila, será mostrado no arquivo none
        que simboliza que não houve torcedor para o portão aberto.
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
          condição para o segundo portão, quando for aberto o segundo portão, será analisado a categoria dos torcedores.
          os torcedores que podem entrar pelo segundo portão são os da categoria 2 e 3, dando preferência ao da segunda
          categoria, se não haver mais nenhum torcedores tanto na segunda quanto na terceira fila, será mostrado no arquivo none
          que simboliza que não houve torcedor para o portão aberto.
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
          condição para o terceiro portão, quando for aberto o terceiro portão, será analisado a categoria dos torcedores.
          o torcedor que pode entrar pelo terceiro portão é apenas o da categoria 3, se não haver mais nenhum torcedor
          da terceira fila, será mostrado no arquivo none, que simboliza que não houve torcedor para o portão aberto.
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
       //quantidades de torcedores que passam por cada tipo de portão, dentro de cada condição acima é somado
       //quantos passam pelo respectivo portão para mostrar no arquivo log.txt
       fprintf(log,"Total\n");
       fprintf(log,"portao 1 %d torcedor(es) \n", porta1);//torcedores que passaram pelo primeiro portão
       fprintf(log,"portao 2 %d torcedor(es) \n", porta2);//torcedores que passaram pelo segundo portão
       fprintf(log,"portao 3 %d torcedor(es) \n", porta3);//torcedores que passaram pelo terceiro portão
       fclose(log);
}
     /*
     FUNÇÃO QUE RECEBE COMO PARÂMETRO OS PONTEIROS DA FILA, ENTÃO ELA RECEBE TRÊS PONTEIROS DIFERENTES
     ONDE SE O PONTEIRO FOR VAZIO ELE GUARDA O PRIMEIRO TORCEDOR DE CADA RESPECTIVA FILA, APÓS SE JÁ TIVER
     TORCEDOR NO RESPECTIVO PONTEIRO ELE GUARDA O PROXIMO DEPOIS DO PRIMEIRO TORCEDOR E ASSIM POR DIANTE
     SENDO COLOCADO UM PRONTEIRO ADICIONAL QUE GUARDA SEMPRE O ÚLTIMO TORCEDOR, ESSE ÚLTIMO PONTEIRO
     SERVE PARA NÃO TER NECESSIDADE DE PERCORRER A LISTA PARA ENCONTRAR O ÚLTIMO, FACILITA ENTÃO A INSERÇÃO.
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
     PRECORRE A LISTA E IMPRIME O ÍNDICE DO VETOR ONDE ESTAR CADA TORCEDOR, OU SEJA POR EXEMPLO SE ESSA FUNÇÃO FOR CHAMADO
     PARA IMPRIMIR OS TORCEDORES DA SEGUNDA CATEGORIA, ELA ME MOSTRA QUAIS AS POSIÇÕES DO VETOR TEM TORCEDORES DA SEGUNDA CATEGORIA
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
      FUNÇÃO QUE REMOVE O PRIMEIRO DA FILA DE CADA RESPECTIVO PONTEIRO, ELA PEGA O PRIMEIRO DA FILA E GUARDA EM UMA VARIÁVEL
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

//INÍCIO DO MANUAL DE USO

                                            //OBJETIVO DO PROGRAMA
                                    //RETIRADO DO PRÓPRIO TEXTO DO PROBLEMA
/*
Torcedores serão divididos em: categoria 1, categoria 2 e categoria 3. Para os portões, a priori, serão considerados
apenas 3: portão 1, portão 2 e portão 3. O portão 1 foi definido como entrada apenas dos torcedores das categorias 1 e 3,
no entanto, a prioridade é da categoria 1. O portão 2 foi definido como entrada dos torcedores das categorias 2 e 3, no
entanto, a prioridade é da categoria 2. Por fim, o portão 3 foi definido como entrada somente dos torcedores da categoria 3.
A simulação do sistema será da seguinte forma. A fila de torcedores será dada por um arquivo texto chamado fila.txt. O sistema
deverá ler este arquivo e criar outras três filas, com todos os dados dos torcedores, de acordo com as suas respectivas
categorias. O acesso aos portões será regulado por um sistema que avaliará qual o portão menos congestionado e indicará qual o
torcedor deverá entrar por este portão, respeitando as filas e as permissões e prioridades do portão. Este procedimento será
simulado através da leitura de um arquivo texto chamado vai_meu_filho.txt, que indicará, em ordem, qual portão está menos
congestionado. Para cada passagem de um torcedor por um portão, o sistema deverá gravar em um arquivo texto chamado
log.txt, as seguintes informações: portão, a categoria, o nome, o bloco e o assento do torcedor. Quando encerrar a leitura do arquivo
vai_meu_filho.txt, a quantidade total de torcedores que passaram por cada portão também deverá ser registrada no final do arquivo log.txt.
*/

                                 //COMO UTILIZAR O PROGRAMA

                                    //PRIMEIRO PASSO

//O USUÁRIO TEM QUE CRIAR UM ARQUIVO CHAMADO FILA DO TIPO DE TXT.
//EXEMPLO: NOME DO ARQUIVO: FILA.TXT, SE FEITO NO BLOCO DE NOTAS O ARQUIVO ALTOMATICAMENTE COLOCA O TXT
//SENDO APENAS NECESSÁRIO A INFORMAÇÃO DO NOME
//APÓS O ARQUIVO FEITO, PODE INSERIR QUALQUER QUANTIDADE DE PESSOAS EM UMA FILA UNICA.
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
//O ARQUIVO TEM QUE SER INSCRITO NESSA ORDEM DE INFORMAÇÃO, PARA A LEITURA CORRETA DO ARQUIVO
//COMO O ARQUIVO CONTA OS TORCEDORES POR LINHAS DE ARQUIVO, ENTAO JÁ É CONTADO DESDE O PRIMEIRO ESPAÇO VAZIO
//OU SEJA NO ULTIMO TORCEDOR A SER INSERIDO "NAO PODE HAVER QUEBRA DE LINHA".


                                    //SEGUNDO PASSO

//APOS A CRIAÇÃO DO ARQUIVO FILA.TXT O PROGRAMA PEDIRÁ OUTRO TIPO DE ARQUIVO CHAMADO VAIMEUFILHO
//EXEMPLO: NOME DO ARQUIVO: VAIMEUFILHO.TXT, SE FEITO NO BLOCO DE NOTAS O ARQUIVO ALTOMATICAMENTE COLOCA O TXT
//SENDO APENAS NECESSÁRIO A INFORMAÇÃO DO NOME
//NELE SERÁ COLOCADO AS INFORMAÇÕES DOS PORTOES A SEREM ABERTO
//EXEMPLO DO QUE DEVE CONTER NESSE TIPO DE ARQUIVO ARQUIVO:
          /*
          1 3 1 2 1 2 2 1
          */
//SÓ SERAM CONSIDERADOS TRES TIPOS DE PORTOES 1, 2 E 3.


                                      //TERCEIRO PASSO

                                //GERANDO O ARQUIVO LOG.TXT

//SERÁ FEITO UMA ANALISE DE CADA PORTAO ABERTO EM ORDEM
//O PORTAO ATUAL ANALISARA A FILA DO TORCEDOR
//COMO CITADO EM OBJETIVOS ANALISARÁ AS CONDIÇOES DO PORTAO ABERTO ATUALMENTE
//SE O TORCEDOR FOR APTO A PASSAR PELO PORTAO O ARQUIVO LOG.TXT ESCREVE SEUS DADOS
//O ARQUIVO LOG.TXT É CRIADO AUTOMATICAMENTE PELO PROGRAMA
//DE ACORDO COM A INFORMAÇÕES ACIMA, SE FOR FEITO OS DOIS ARQUIVO DE ACORDO COM AS INFORMAÇÕES CITADAS
//O ARQUIVO LOG.TXT GUARDARÁ AS SEGUINTES INFORMAÇÕES
/*
                                          SAÍDAS DO PROGRAMA
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

  NO CASO ACIMA FOI LIDO O ARQUIVO FILA.TXT E ANALISADO SUA CATEGORIA DE ACORDO COM O PORTÃO ABERTO NO MOMENTO
  DAÍ ANALISADO SUA PRIORI DE ACORDO QUE O PORTÃO E SUA CATEGORIA, E CADA VEZ QUE PASSA O TORCEDOR PELO PORTÃO
  É CONTABILIZADO, NO ÚLTIMO PORTÃO COMO NÃO TINHA NINGUÉM PARA ENTRAR O SEGUINTE NOME É INSCRITO NO LOG.TXT
  "NONE"
*/
/*
                             TESTES EFETUADOS PARA O FUNCIONAMENTO DO PROGRAMA

  Caso 1: O número de torcedores ser maior que o número de portões que serão abertos.
  Caso 2: Imprimir todas as filas e verificar se elas estão devidamente organizadas.
  Caso 3: Colocar torcedores somente nas categorias 1 e 2 e abrir somente o portão 3.
  Caso 4: Colocar apenas torcedores na categoria 3 e abrir somente os portões 1 e 2.
  caso 5: Abri o fila.txt sem nenhuma torcedor
  caso 5: abri o vaimeufilho sem nenhum portão a ser aberto
  caso 6: O número de portões serem maior do que o número de torcedores
  caso 7: Organizar o vaimeufilho um abaixo do outro
  caso 8: foram colocados torcedores com categorias diferentes do proposto pelo problema
*/



                                  //SITUAÇÕES EM QUE O PROGRAMA NÃO FUNCIONA

//NÃO PODE SER QUEBRADO LINHA NO ULTIMO TORCEDOR INSERIDO NO ARQUIVO LOG.TXT
//NÃO PODE COLOCAR NUMEROS DE DOIS DIGITOS OU MAIS NO ARQUIVO VAIMEUFILHO, ISSO OCASIONARÁ ERRO DE EXECUÇÃO
//SE COLOCAR NÚMEROS MENORES QUE 1 E MAIORES QUE 3 NÃO TEM PROBLEMA ALGUM, SÓ QUE ESSA INFORMAÇÃO SERÁ PERDIDA NA EXECUÇÃO


                                          //O PROGRAMA

/*
O software foi desenvolvido em um sistema operacional Windows, foi utilizado o DEV C++, que é um compilador de códigos de
linguagem de programação “c” e “c++”. além disso, para ter certeza do completo funcionamento, foi testado o código no sistema
operacional Linux, como tem algumas condições que não existem no Linux a exemplo de algumas bibliotecas, foram feitos apenas
adaptações para o teste, mas não houve modificações de condições do código.
*/

                                          //MELHORIAS DO CÓDIGO

          /*
          ->AUMENTAR A CAPACIDADE DE PORTOES LIDOS, PARA MAIS CATEGORIAS DE TORCEDORES
          ->GERAR ARQUIVOS COM CADA CATEGORIA DE TORCEDOR
          ->INTERFACE GRÁFICA DAS FILAS
          */



//FINAL DO MANUAL DE USO



