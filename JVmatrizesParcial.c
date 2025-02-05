#include <stdio.h>
#include <stdlib.h>



#define V 'X'
#define M '.'
#define MAXL 100
#define MAXC 100


// o trecho abaixo define algumas macros
#ifdef __unix__
    #include <unistd.h>
    #define LIMPATELA "clear"
    #define DORME(a) sleep(a)
    #define TEMPO 5
#else
    #include <Windows.h>
    #define LIMPATELA "cls"
    #define DORME(a) Sleep(a)
    #define TEMPO 100
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Inicio dos prototipos ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



//Atencao!!!! Nas etapa 1a de desenvolvimento voce nao deve mudar nenhum dos prototipos abaixo...
void limpaMatriz(char m[ ][MAXC], int nL, int nC);
void imprimeMatriz(char m[][MAXC],int nL, int nC);
void copiaMatriz(char mCopia[][MAXC],char m[][MAXC], int nL, int nC);
void atualizaTabuleiro(char mAtual[][MAXC], char nAnterior[][MAXC], int nL, int nC);
void jogaJogoVida(char mAtual[ ][MAXC], int nL, int nC, int nCiclos);

void inicBloco(char m[ ][MAXC], int nL, int nC);
void inicBote(char m[ ][MAXC], int nL, int nC);
void inicBlinker(char m[ ][MAXC], int nL, int nC);
void inicSapo(char m[ ][MAXC], int nL, int nC);
void inicGlider(char m[ ][MAXC], int nL, int nC);
void inicLWSS(char m[ ][MAXC], int nL, int nC);

//Atencao!!!! Nas etapa 1b de desenvolvimento vc pode  alterar esse protótipo, sua respectiva chamada e definição
int menuInicJogo(char m[ ][MAXC], int nL, int nC);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////// Início da parte a ser alterada na etapa 1b   ///////////////////////////////////

int main()
{

   char tab[MAXL][MAXC];

   int nL=20,nC=20,nCiclos=50; //ou fornecidos pelo usuario
   int op; //opcao fornecida pelo usuario e retornada pela funcao menuInicJogo



   //Etapa 1b: implementar laco INdeterminado que repete enquanto o usuario quiser continuar jogando:
      //cada jogo equivale a nCiclos de um padrao de inicializacao
      //por exemplo o usuario pode escolher jogar nCiclos do padrao Sapo
     // quando terminar ele pode
     // encerrar o programa
     // ou jogar mais nCiclos de outro padrao qualquer escolhido no menu

        op = menuInicJogo(tab,nL,nC);
        printf("iniciando jogo com opcao %d\n\n", op);
        DORME(TEMPO);
        jogaJogoVida(tab,nL,nC,nCiclos); //Etapa 1a: complete essa funcao no trecho de sua definição

  //fim do laco indeterminado

   return 0;
}

int  menuInicJogo(char mat[ ][MAXC], int nL, int nC)
{
    int opcao;

   limpaMatriz(mat,nL,nC);

   printf("(1)Bloco\n(2)Bote\n(3)Blinker\n(4)Sapo\n(5)Glider\n(6)LWSS\nEntre com a opcao: ");
   scanf("%d",&opcao);
   switch(opcao)
   {
     case 1:   inicBloco(mat,nL,nC); break;
     case 2:   inicBote(mat,nL,nC); break;
     case 3:   inicBlinker(mat,nL,nC); break;
     case 4:   inicSapo(mat,nL,nC); break;
     case 5:   inicGlider(mat,nL,nC); break;
     case 6:   inicLWSS(mat,nL,nC); break;
   }

    imprimeMatriz(mat,nL,nC);
    printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo...");
    while(getchar()!='\n'); //limpa a memória do teclado (caso tenha sobrado ENTER (\n)
    getchar();

    return opcao;

}


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// Inicio da Parte a ser completada na Etapa 1 /////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void imprimeMatriz(char m[][MAXC],int nL, int nC)
{
    int i, j;
    for (i=0;i< nL;i++){
        for ( j=0; j<nC;j++){
            printf("%3c", m[i][j]);
        }
        printf("\n");
    }
}

void copiaMatriz(char mCopia[][MAXC],char m[][MAXC], int nL, int nC)
{
    int i, j;
    for (i=0;i<nL;i++){
        for(j=0;j<nC;j++){
            mCopia[i][j]= m[i][j];
        }
    }


}

void atualizaMat(char mAtual[][MAXC], char mAnterior[][MAXC], int nL, int nC)
{
        int i, j,k,l;
        int vizinhos =0;
        /* Perguntar se precisa chamar a copiaMatriz para essa ser a primeira da mAnterior, e ir arualizando nessa mAtual, mantando a mCopia sempre igual a anterior,*/
    char mTemp[nL][MAXC]; // Matriz temporária para armazenar as mudanças

    // Copiar mAtual para mAnterior antes de modificar
    copiaMatriz(mAnterior, mAtual, nL, nC);

    for (i = 0; i < nL; i++) {
        for (j = 0; j < nC; j++) {
            vizinhos = 0;

            // Contar vizinhos vivos
            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue; // Ignorar a própria célula
                    int ni = i + k, nj = j + l;
                    if (ni >= 0 && ni < nL && nj >= 0 && nj < nC && mAnterior[ni][nj] == 'X') {
                        vizinhos++;
                    }
                }
            }

            // Aplicar regras do Jogo da Vida
            if (mAnterior[i][j] == 'X') {
                if (vizinhos < 2 || vizinhos > 3) {
                    mTemp[i][j] = '.'; // Morre por solidão ou superpopulação
                } else {
                    mTemp[i][j] = 'X'; // Sobrevive
                }
            } else {
                if (vizinhos == 3) {
                    mTemp[i][j] = 'X'; // Nasce uma nova célula
                } else {
                    mTemp[i][j] = '. '; // Permanece morta
                }
            }
        }
    }

    // Copiar a matriz temporária para mAtual
    copiaMatriz(mAtual, mTemp, nL, nC);
         /*Precisa incluir no loop o quadradinho que esta sendo comparado ou so os outros 8 em volta?
          for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue;// célula que tá sendo comparada
        /*como as celulas vivas sao X e as mortas sao . ,
			a soma destas posicoes consiste na quantidade de
			celulas vivas nesta região 3 x 3*/


}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FIM da Parte a ser completada ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


void jogaJogoVida(char mAtual[ ][MAXC], int nL, int nC, int nCiclos)
{
  char nAnterior[MAXL][MAXC];
  int c;

  //imprimindo na tela a matriz inicial
  system(LIMPATELA);
  imprimeMatriz(mAtual,nL,nC); //TO DO
  DORME(TEMPO);  // use getchar(); caso queira segurar a impressao ate que o
  //fim da impressao da matriz inicial

  //iniciando os ciclos do jogo escolhido
  for(c=1;c<=nCiclos;c++)
  {
        copiaMatriz(nAnterior,mAtual,nL,nC); // implemente a funcao que copia uma matriz na outra, equivalendo a nAnterior = mAtual;

        atualizaMat(mAtual,nAnterior,nL,nC); //implemente nesta funcao as regras que contam as celulas vizinhas em nAnterior
                                       //e atualizam a matriz mAtual conforme as regras do jogo da vida
                                     //lembre de usar os dados de nAnterior como a matriz do jogo no ciclo anterior para atualizar mAtual
        system(LIMPATELA);
        imprimeMatriz(mAtual,nL,nC);// implemente a funcao para imprimir a matriz na tela
        // getchar();
        DORME(TEMPO);
  }

}

////////////////////////////////////////////////
void limpaMatriz(char m[ ][MAXC], int nL, int nC)
{
    int i,j;
    for(i=0;i<nL;i++)
     for(j=0;j<nC;j++)
        m[i][j]=M;  // cada célula eh preenchida como morta M ('.')
}

////////////////////////////////////////////////
void inicBloco(char m[ ][MAXC], int nL, int nC)
{
 char padrao[2][2]={{V,V},{V,V}};
  int i,j,xInic=nL/2, yInic=nC/2;


 //posiciona o padrão no tabuleiro
 for(i=0;i<2;i++)
    for(j=0;j<2;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}

////////////////////////////////////////////////
void inicBote(char m[ ][MAXC], int nL, int nC)
{
 char padrao[3][3]={{V,V,M},{V,M,V},{M,V,M}};
  int i,j,xInic=nL/2, yInic=nC/2;


 //posiciona o padrão no tabuleiro
 for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}
////////////////////////////////////////////////
void inicBlinker(char m[ ][MAXC], int nL, int nC)
{
  char padrao[1][3]={{V,V,V}};
  int i,j, xInic=nL/2, yInic=nC/2;


 //posiciona o padrão no tabuleiro
 for(i=0;i<1;i++)
    for(j=0;j<3;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}


////////////////////////////////////////////////
void inicSapo(char m[ ][MAXC], int nL, int nC)
{

 char padrao[2][4]={{M,V,V,V},{V,V,V,M}};
  int i,j,xInic=nL/2, yInic=nC/2;


  //posiciona o padrão no tabuleiro
   for(i=0;i<2;i++)
      for(j=0;j<4;j++)
      m[xInic+i][yInic+j]=padrao[i][j];

}

////////////////////////////////////////////////
void inicGlider(char m[ ][MAXC], int nL, int nC)
{
char padrao[3][3]={{V,V,V},{V,M,M},{M,V,M}};
 int i,j,xInic,yInic;


 xInic=nL-4;
 yInic=nC-4;

 //posiciona o padrão no tabuleiro
 for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}

////////////////////////////////////////////////
void inicLWSS(char m[ ][MAXC], int nL, int nC)
{
char padrao[4][5]={{M,V,M,M,V},{V,M,M,M,M},{V,M,M,M,V},{V,V,V,V,M}};
 int i,j,xInic,yInic;



 xInic=nL-5;
 yInic=nC-6;

 //posiciona o padrão no tabuleiro
 for(i=0;i<4;i++)
    for(j=0;j<5;j++)
      m[xInic+i][yInic+j]=padrao[i][j];

}
