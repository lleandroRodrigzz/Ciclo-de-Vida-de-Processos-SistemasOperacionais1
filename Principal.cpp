#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Parâmetros de cores (5:Roxo, 2:Verde)
#include "TadFilaCircularPrioridadeDePonteiros.h" // TAD Para Fila De Prontos
#include "TadFilaComum.h" // TAD para Fila de Espera e Bloqueados

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF) 
{
    int i;
    textcolor(CorT);
    textbackground(CorF);
    gotoxy(CI, LI); printf("%c", 201);
    gotoxy(CI, LF); printf("%c", 200);
    gotoxy(CF, LI); printf("%c", 187);
    gotoxy(CF, LF); printf("%c", 188);

    for (i = CI + 1; i < CF; i++) {
        gotoxy(i, LI); printf("%c", 205);
        gotoxy(i, LF); printf("%c", 205);
    }
    for (i = LI + 1; i < LF; i++) {
        gotoxy(CI, i); printf("%c", 186);
        gotoxy(CF, i); printf("%c", 186);
    }
    textcolor(7);
    textbackground(0);
}

void criaTabelaPCB()
{
    gotoxy(65, 5);
    textcolor(2);
    printf("TABELA PCB");
    Moldura(27, 6, 116, 9, 5, 0); // Quadrado da tabela PCB
    gotoxy(29, 7);
    textcolor(2);
    printf("PID | PRIORIDADE | ESTADO | T.EXECUCAO |  T.ESPERA  | T.RESTANTE | T.BLOQUEADO | FILHO");
    textcolor(15);
}

void Menu(void) 
{
    textcolor(3);
    Moldura(48, 13, 74, 20, 0, 5); // Quadrado interno
    textcolor(2);
    gotoxy(50, 15); printf("[A] - Iniciar Simulacao");
    gotoxy(53, 18); printf("[ESC] - Finalizar");
}

void nomeTrab()
{
    textcolor(2);
    int x = 15;
    int y = 3;
    gotoxy(x, y);
    char linha[200];
    FILE *Ptr = fopen("letreiro.txt", "r");
    fgets(linha, sizeof(linha), Ptr);
    while (!feof(Ptr))
    {
        gotoxy(x, y);
        printf("%s", linha);
        fgets(linha, sizeof(linha), Ptr);
        y++;
    }
    gotoxy(x, y);
    printf("%s", linha);
    
    textcolor(15);
    gotoxy(25, 26);
    printf("Trabalho feito por ");
    textcolor(2);
    printf("Leandro Marcos C. Rodrigues ");
    textcolor(15);
    printf("e ");
    textcolor(2);
    printf("Victor Hugo D. Oliveira");
    gotoxy(26, 27);
    textcolor(15);
    printf("Disciplina De Sistemas Operacionais I || Professor ");
    textcolor(5);
    printf("Robson A. Siscoutto");
}

char Quadro() 
{
    clrscr();
    Moldura(1, 1, 120, 30, 0, 5); // Quadrado grande/principal
    Menu(); // Opções do menu
    nomeTrab(); // Letreiro Grande
    gotoxy(120, 30);
    return toupper(getch());
}

void criaQuadExecucao() {
    gotoxy(10, 3);
    textcolor(2);
    printf("EXECUCAO");
    Moldura(3, 4, 25, 11, 5, 0); // Quadrado interno
    textcolor(2);
    gotoxy(5, 5);
    printf("PID: ");
    textcolor(15);
    gotoxy(5, 6);
    textcolor(2);
    printf("T.RESTANTE ATUAL: ");
    textcolor(15);
    gotoxy(5, 7);
    textcolor(2);
    printf("CPU-BURST: ");
    textcolor(15);
    printf("10u.t");
    gotoxy(5, 8);
    textcolor(2);
    printf("PRIORIDADE: ");
    textcolor(15);
    gotoxy(5, 9);
    textcolor(2);
    printf("ESTADO: ");
    textcolor(15);
    gotoxy(5, 10);
    textcolor(2);
    printf("CRIOU FILHO: ");
    textcolor(15);
    gotoxy(120, 30);
}

void criaQuadFilaBloqueadoKEYBOARD(TpFilaControl* FBloqKB) {
    Moldura(3, 12, 118, 16, 5, 0); 
    gotoxy(53, 11);
    textcolor(2);
    printf("FILA DE BLOQUEADOS TECLADO");
    textbackground(0);
    for (int i = 13; i < 16; i++) { 
        for (int j = 4; j < 118; j++) {  
            gotoxy(j, i);
            printf(" "); 
        }
    }
    textcolor(2);
    if (FilaVaziaF(FBloqKB)) 
	{
        gotoxy(55, 14);
        printf("V A Z I A");
    }
    else 
	{
        ExibirFilaFCIMA(FBloqKB,1);
    }
    Moldura(3, 18, 118, 22, 0, 0); 
    gotoxy(120, 30);
}

void criaQuadFilaBloqueadoMOUSE(TpFilaControl* FBloqMOUSE) {
    Moldura(3, 12, 118, 16, 5, 0); 
    gotoxy(53, 11);
    textcolor(2);
    printf("FILA DE BLOQUEADOS MOUSE  ");
    textbackground(0);
    for (int i = 13; i < 16; i++) { 
        for (int j = 4; j < 118; j++) {  
            gotoxy(j, i);
            printf(" "); 
        }
    }
    textcolor(2);
    if (FilaVaziaF(FBloqMOUSE)) {
        gotoxy(55, 14);
        printf("V A Z I A");
    }
    else 
	{
        ExibirFilaFCIMA(FBloqMOUSE,1);
    }
    gotoxy(120, 30);
}

void criaQuadFilaBloqueadoHD(TpFilaControl* FBloqHD) {
	limparAreaFilaEspera();
    Moldura(3, 18, 118, 22, 5, 0); 
    gotoxy(53, 17);
    textcolor(2);
    printf("FILA DE BLOQUEADOS HD");
    textbackground(0);
    for (int i = 19; i < 22; i++) { 
        for (int j = 4; j < 118; j++) {  
            gotoxy(j, i);
            printf(" "); 
        }
    }
    textcolor(2);
    if (FilaVaziaF(FBloqHD)) 
	{
        gotoxy(55, 20);
        printf("V A Z I A");
    }
    else 
	{
        ExibirFilaFBAIXO(FBloqHD,1);
    }
    gotoxy(120, 30);
}

void criaQuadFilaEspera(TpFilaControl* FEspera) { // Cabe 16 processos nas FILAS da interface
	limparAreaFilaEspera();
    Moldura(3, 18, 118, 22, 5, 0); 
    gotoxy(53, 17);
    textcolor(2);
    printf("FILA DE ESPERA");
    textbackground(0);
    for (int i = 19; i < 22; i++) 
	{ 
        for (int j = 4; j < 118; j++) 
		{  
            gotoxy(j, i);
            printf(" "); 
        }
    }
    textcolor(2);
    if (FilaVaziaF(FEspera))
	{
        gotoxy(55, 20);
        printf("V A Z I A");
    } 
	else 
	{
        ExibirFilaFBAIXO(FEspera,0);
    }
    gotoxy(120, 30);
}

void criaQuadFilaProntos(TpFilaCirc FPronto) { // Cabe 16 processos nas FILAS da interface, logo, MAXFILA == 16
    Moldura(3, 12, 118, 16, 5, 0); 
    gotoxy(53, 11);
    textcolor(2);
    printf("FILA DE PRONTO                   ");
    
    textbackground(0);  
    for (int i = 13; i < 16; i++) { 
        for (int j = 4; j < 118; j++) {  
            gotoxy(j, i);
            printf(" "); 
        }
    }
    textcolor(2);
    if (FilaVazia(FPronto.cont)) 
	{
        gotoxy(55, 14);
        printf("V A Z I A");
    } 
	else 
	{
        ExibeFC(FPronto);
    }
    gotoxy(120, 30);  
}

void atualizarFilas(int paginaAtual, TpFilaCirc FPronto, TpFilaControl* FEspera, TpFilaControl* FBloqHD, TpFilaControl* FBloqMOUSE, TpFilaControl* FBloqKB) {
    textbackground(0);
    for (int i = 12; i < 22; i++) 
	{ 										
        for (int j = 3; j < 119; j++) 
		{ 									
            gotoxy(j, i);
            printf(" ");
        }
    }
    if (paginaAtual == 1) 
	{
        criaQuadFilaProntos(FPronto);
        criaQuadFilaEspera(FEspera);
    } 
    else if (paginaAtual == 2) 
	{
        criaQuadFilaBloqueadoMOUSE(FBloqMOUSE);
        criaQuadFilaBloqueadoHD(FBloqHD);
    }
    else if (paginaAtual == 3) 
	{
        criaQuadFilaBloqueadoKEYBOARD(FBloqKB);
    }
}

void limparCaixinhaOperacoes() {
    int startX = 85; 
    int startY = 28; 
    int endX = 117; 
    int endY = 28; 
    textbackground(0); 
    for (int y = startY; y <= endY; y++) {
        gotoxy(startX, y);
        for (int x = startX; x <= endX; x++) {
            printf(" "); 
        }
    }
}

void limparTabelaPCB();

void atualizarPcb(TpProcesso *dado) {
    limparTabelaPCB();
    gotoxy(65, 5);
    textcolor(2);
    printf("TABELA PCB");
    Moldura(27, 6, 116, 9, 5, 0); // Quadrado da tabela PCB
    gotoxy(29, 7);
    textcolor(2);
    printf("PID | PRIORIDADE | ESTADO | T.EXECUCAO |  T.ESPERA  | T.RESTANTE | T.BLOQUEADO | FILHO");
    textcolor(15);
    gotoxy(29, 8);
    if(dado != NULL)
    {
    	printf("%d", dado->pid);
	    gotoxy(38, 8);
	    printf("%d", dado->prioridade);
	    gotoxy(49, 8);
	    printf("%c", dado->estado);
	    gotoxy(60, 8);
	    printf("%d", dado->tempoExecucao);
	    gotoxy(73, 8);
	    printf("%d", dado->tempoEspera);
	    gotoxy(86, 8);
	    printf("%d", dado->tempoRestante);
	    gotoxy(100, 8);
	    printf("%d", dado->tempoBloqueado);
	    gotoxy(111, 8);
	    printf("%d", dado->criouFilho);
	}
	gotoxy(120,30);
}

void limparTabelaPCB() {
    int startX = 27; 
    int startY = 6;  
    int endX = 116;  
    int endY = 9;    
    
    textbackground(0);  

    for (int y = startY; y <= endY; y++) {  
        for (int x = startX; x <= endX; x++) {  
            gotoxy(x, y);  
            printf(" ");   
        }
    }
    textcolor(15);  
    textbackground(0);
    gotoxy(120,30);
    criaTabelaPCB();
}

void limparQuadExecucao() {
    int startX = 3;  // Coluna inicial 
    int startY = 4;  // Linha inicial 
    int endX = 25;   // Coluna final 
    int endY = 11;   // Linha final 
    
    textbackground(0);  
    
    for (int y = startY; y <= endY; y++) {
        gotoxy(startX, y);  
        for (int x = startX; x <= endX; x++) {
            printf(" ");  
        }
    }
    criaQuadExecucao();
    gotoxy(120, 30);  // Reposiciona o cursor para o final da tela (ou em outro lugar apropriado)
}

void atualizarQuadExecucao(TpProcesso *dado) {
    limparQuadExecucao();
    gotoxy(10, 3);
    textcolor(2);
    printf("EXECUCAO");
    Moldura(3, 4, 25, 11, 5, 0); // Quadrado interno
    textcolor(2);
    gotoxy(5, 5);
    printf("PID: ");
    textcolor(15);
    printf("%d", dado->pid);
    gotoxy(5, 6);
    textcolor(2);
    printf("T.RESTANTE ATUAL:");
    textcolor(15);
    printf("%d", dado->tempoRestante);
    gotoxy(5, 7);
    textcolor(2);
    printf("CPU-BURST: ");
    textcolor(15);
    printf("10u.t");
    gotoxy(5, 8);
    textcolor(2);
    printf("PRIORIDADE: ");
    textcolor(15);
    printf("%d", dado->prioridade);
    gotoxy(5, 9);
    textcolor(2);
    printf("ESTADO: ");
    textcolor(15);
    printf("R"); // RUNNING
    gotoxy(5, 10);
    textcolor(2);
    printf("CRIOU FILHO: ");
    textcolor(15);
    if (dado->criouFilho == 0)
        printf("N");
    else
        printf("S");
    gotoxy(120, 30);
}

TpProcesso* criarFilho(TpProcesso *pai, int &PIDIncrement) {
    TpProcesso *filho = new TpProcesso;
    filho->pid = PIDIncrement;
    filho->ppid = pai->pid;
    filho->prioridade = pai->prioridade; 
    filho->tempoExecucao = 0;
    filho->tempoEspera = 0;
    filho->tempoBloqueado = 0;
    filho->tempoRestante = (rand() % 20) + 1; 
    filho->estado = 'P'; // Estado inicial como pronto
    filho->criouFilho = 0; 
    return filho;
}

void executarProcesso(TpFilaCirc &FPronto, TpProcesso *procExecut, TpFilaControl *&FEspera, TpFilaControl *&FTerminated, 
						int CPUBurst, TpFilaControl *&FBloqHD, TpFilaControl *&FBloqMS, TpFilaControl *&FBloqKB, int &PIDIncrement) {
    int cont = 0;
    while (cont < CPUBurst) 
	{
        if (procExecut->tempoRestante > 0) 
		{
            Sleep(1000); 
            procExecut->tempoRestante--;
            procExecut->tempoExecucao++;
            atualizarPcb(procExecut);
            atualizarQuadExecucao(procExecut);
        } 
		else 
		{
            procExecut->estado = 'T'; // Processo terminou
            gotoxy(85, 28);
            textcolor(2);
            printf("Processo com PID %d terminou!", procExecut->pid);
            Sleep(2000);
            InserirF(FTerminated, procExecut);
            FTerminated->qtdeFinalizado++;
            limparCaixinhaOperacoes();
            return;
        }
        
		int acao = (rand() % 100) + 1;
		if(acao <= 5 && procExecut->estado != 'B')			//criaFilho 5% de chance
		{
			PIDIncrement++;
			TpProcesso *novoFilho = criarFilho(procExecut,PIDIncrement);
			procExecut->criouFilho++;  // Incrementa o contador de filhos
			InserirFilaEspParaPron(FPronto,novoFilho);
			gotoxy(85, 28);
            textcolor(2);
            printf("Processo %d criou filho PID %d", procExecut->pid, novoFilho->pid);
            criaQuadFilaProntos(FPronto);  
            Sleep(2000);
            limparCaixinhaOperacoes();
		}
		else if(acao > 5 && acao <= 15) 						//bloqueia 15% de chance
		{
			int sorteioBloq;
			procExecut->estado = 'B';			//Bloqueado
            sorteioBloq = (rand() % 3) + 1;  	// Escolhe qual recurso vai bloquear o processo
            switch(sorteioBloq) 
			{
                case 1:
                	textcolor(2);
                    gotoxy(85, 28); printf("Proc.Bloqueado pelo HD com PID %d", procExecut->pid);
                    procExecut->tempoBloqueado = 10;
                    InserirF(FBloqHD, procExecut);
                    atualizarPcb(NULL);
                    break;
                case 2:
                	textcolor(2);
                    gotoxy(85, 28); printf("Proc.Bloqueado pelo MS com PID %d", procExecut->pid);
                    procExecut->tempoBloqueado = 5;
                    InserirF(FBloqMS, procExecut);
                    atualizarPcb(NULL);
                    break;
                case 3:
                	textcolor(2);
                    gotoxy(85, 28); printf("Proc.Bloqueado pelo KB com PID %d", procExecut->pid);
                    procExecut->tempoBloqueado = 15;
                    InserirF(FBloqKB, procExecut);
                    atualizarPcb(NULL);
                    break;
            }
            Sleep(2000);
            limparCaixinhaOperacoes();
            return; 
		}
        cont++;
    }

    if (procExecut->tempoRestante > 0 && procExecut->estado != 'T') 
	{
        procExecut->estado = 'E';  						// Muda o estado para 'E' (espera)
        procExecut->tempoEspera = (rand() % 15) + 1;  // Define um tempo que um processo vai esperar na fila
        InserirF(FEspera, procExecut);  				// Insere na fila de espera
        criaQuadFilaEspera(FEspera);
    }
    
    limparQuadExecucao();
    atualizarPcb(NULL);
}

void processarFilaBloque(TpFilaControl *&FB, TpFilaCirc &FPronto) {
    if (!FilaVaziaF(FB)) 
	{
        TpFila *temp = FB->inicio;
        while (temp != NULL) 
		{
            temp->info->tempoBloqueado--;

            if (temp->info->tempoBloqueado == 0) 
			{
                TpProcesso *procRetirado = RetirarF(FB);
                gotoxy(85, 28);
                textcolor(2);
                printf("Proc. %d desbloq. e pronto", procRetirado->pid);
                procRetirado->estado = 'P';
                InserirFilaEspParaPron(FPronto, procRetirado);
                Sleep(2000);  
                limparCaixinhaOperacoes();
                break; 
            }
            temp = temp->prox;
        }
    }
}

void processarFilaEspera(TpFilaControl *&FEspera, TpFilaCirc &FPronto) {
    if (!FilaVaziaF(FEspera)) 
	{
        TpFila *temp = FEspera->inicio;
        TpFila *ant = NULL;
        
        while (temp != NULL) 
		{
            if (temp->info->tempoEspera > 0) 
			{
                temp->info->tempoEspera--;  
                Sleep(1000);
            }

            // Se o tempo de espera chegou a zero, move o processo para a fila de prontos
            if (temp->info->tempoEspera == 0) 
			{
                TpProcesso *procRetirado = RetirarF(FEspera);
                procRetirado->estado = 'P';
                InserirFilaEspParaPron(FPronto, procRetirado);
                
                gotoxy(85, 28);
                textcolor(2);
                printf("Proc. %d foi F.De prontos", procRetirado->pid);
                Sleep(2000);  
                
                criaQuadFilaProntos(FPronto);
                criaQuadFilaEspera(FEspera);
                limparCaixinhaOperacoes();

                break;
            }
            limparAreaFilaEspera();
            criaQuadFilaEspera(FEspera);
            temp = temp->prox;
        }
    }
}

void iniciarSimulacao(int &paginaAtual) {
    char op;
    int novaPrior;
    int PIDincrement = 0;
    int CPUBurst = 10;  
    int ut = 0;  
    char isPaused = '0';

    TpFilaCirc FPronto, FPCBs;
    TpFilaControl *FEspera, *FBloqHD, *FBloqMS, *FBloqKB, *FTerminated;

    Inicializar(FPronto);  // Inicializadores
    InicializarF(FEspera);
    InicializarF(FBloqHD);
    InicializarF(FBloqMS);
    InicializarF(FBloqKB);
    InicializarF(FTerminated); // Fila de processos terminados

    criaQuadFilaProntos(FPronto); 
    criaQuadFilaEspera(FEspera);  

    while (true) 
	{  
		if(isPaused == '0')
		{
			if (!FilaVazia(FPronto.cont)) 
			{ 
	            TpProcesso *procExecut = Retirar(FPronto);
	            criaQuadFilaProntos(FPronto);
	            executarProcesso(FPronto ,procExecut, FEspera, FTerminated, CPUBurst, FBloqHD, FBloqMS, FBloqKB, PIDincrement);  
	        }
	        processarFilaEspera(FEspera, FPronto);	
	        processarFilaBloque(FBloqHD,FPronto);
	        processarFilaBloque(FBloqMS,FPronto);
	        processarFilaBloque(FBloqKB,FPronto);
		}        
        if (kbhit())		// Interações do usuário
		{ 
            op = toupper(getch());
            switch (op) 
			{
                case 'A':  // Mover para a página anterior
                    if (paginaAtual > 1) 
					{
                        paginaAtual--;
                        atualizarFilas(paginaAtual, FPronto, FEspera, FBloqHD, FBloqMS, FBloqKB);
                        gotoxy(19, 27);
                        textcolor(2);
                        printf("%d", paginaAtual);
                        gotoxy(120, 30);
                    }
                    break;

                case 'D':  // Mover para a próxima página
                    if (paginaAtual < 3) 
					{
                        paginaAtual++;
                        atualizarFilas(paginaAtual, FPronto, FEspera, FBloqHD, FBloqMS, FBloqKB);
                        gotoxy(19, 27);
                        textcolor(2);
                        printf("%d", paginaAtual);
                        gotoxy(120, 30);
                    }
                    break;

                case 'C':  // Criar novo processo
                    gotoxy(85, 28);
                    textcolor(2);
                    printf("Prioridade do novo processo: ");
                    scanf("%d", &novaPrior);
                    if(novaPrior > 0)
                    {
                    	PIDincrement++;
                    	Inserir(FPronto, novaPrior, PIDincrement);  
	                    criaQuadFilaProntos(FPronto);  
					}
					limparCaixinhaOperacoes();  
					gotoxy(120, 30);
                    break;
                    
                case 'P':  // Tecla para pausar/continuar
	                if(isPaused == '0') 
					{
						isPaused = '1';
						textcolor(2);
	                    gotoxy(85, 28); printf("Pausado...'P' para continuar...");
	                } 
					else 
					{
						isPaused = '0';
	                    limparCaixinhaOperacoes();
	                }
	                gotoxy(120,30);
	                break;

                case 'Z':  // Encerrar a simulação
                if(FilaVazia(FPronto.cont) && FilaVaziaF(FEspera) && FilaVaziaF(FBloqKB) && FilaVaziaF(FBloqMS) && FilaVaziaF(FBloqHD))
				{
                    clrscr();
                    Moldura(1, 1, 120, 30, 0, 5);  
                    textcolor(2);
                    int x = 17;
                    int y = 10;
                    gotoxy(x, y);
                    ExibirRelatorio(FTerminated);
                    gotoxy(120, 30);
                    getch();
                    return;
                }
            }
        }
    }
}

void iniciarInterface(int &paginaAtual) {
    clrscr();
    Moldura(1, 1, 120, 30, 0, 5); // Moldura principal
    gotoxy(26, 3);
    textcolor(15);
    textcolor(2);
    printf("* SIMULACAO DE CICLO DE VIDA DE PROCECESSOS - SISTEMAS OPERACIONAIS I *");
    criaTabelaPCB();        // Cria a tabela PCB
    criaQuadExecucao();     // Cria o quadradinho do processo a ser executado
    gotoxy(3, 29);
    textcolor(2);
    printf("[C] - CRIAR NOVO PROCESSO E COLOCAR NA FILA DE PRONTO");
    gotoxy(59, 29);
    printf("[Z] - ENCERRAR SIMULACAO");
    Moldura(84, 27, 118, 29, 5, 0);    // Caixinha de operações
    textcolor(11);
    Moldura(3, 23, 118, 25, 5, 0);    // Caixinha de legendas
    textcolor(2);
    gotoxy(55, 23); printf("%c", 253);
    gotoxy(63, 23); printf("%c", 252);
    textcolor(5);
    gotoxy(54, 23); printf("%c", 188);
    gotoxy(64, 23); printf("%c", 200);
    gotoxy(56, 23);
    textcolor(15);
    printf("LEGENDA");                      // LEGENDAS
    gotoxy(4, 24);
    textcolor(2); printf(" PD:");
    textcolor(15); printf("PID");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("E:");
    textcolor(15); printf("ESTADO");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("TR:");
    textcolor(15); printf("T.REST.DE EXEC.");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("PR:");
    textcolor(15); printf("PRIORIDADE");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("TE:");
    textcolor(15); printf("T.DE ESPERA");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("MS:");
    textcolor(15); printf("MOUSE");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("KB:");
    textcolor(15); printf("TECLADO");
    textcolor(5); printf(" * ", 186);
    textcolor(2); printf("TB:");
    textcolor(15); printf("TEMPO BLOQ.");
    gotoxy(3, 27);
    textcolor(2);
    printf("[A/D] - PAGINA: %d", paginaAtual);
    gotoxy(25,27);
    printf("[P] - PAUSAR");
    gotoxy(120, 30);
    iniciarSimulacao(paginaAtual);
}

void Executar() {
    int paginaAtual = 1;
    char op;
    
    do {
        op = Quadro();
        switch (op) {
            case 'A':
                iniciarInterface(paginaAtual);
                break;
        }
    } while (op != 27);
}

int main() {
    srand(time(NULL));
    Executar();
    clrscr();
    textcolor(15);
    return 0;
}

