/*#define MAXFILA 16		//Evitar warning de redefined, pois ja temos um MAXFILA no TAD de fila circular

struct TpProcesso {
    int pid;			
    int prioridade;			//Na fila de espera, nao usar a variavel PRIORIDADE pra nada!!!
    char estado;		
    int tempoExecucao;	
    int tempoRestante;	
    int tempoEspera;	
    int tempoBloqueado;
    int criouFilho;	
	TpProcesso *prox;		//Na fila de espera, nao usar a variavel ponteiro PROX pra nada!!!   
};*/

struct TpFila {
    TpProcesso *info;       
    TpFila *prox;          
};

struct TpFilaControl {
    TpFila *inicio;        //'Descritor'
    TpFila *fim;     
	int qtdeFinalizado;       
};


void InicializarF(TpFilaControl* &FE) {
    FE = new TpFilaControl;  
    FE->inicio = NULL;       
    FE->fim = NULL;     
	FE->qtdeFinalizado = 0;     
}


char FilaVaziaF(TpFilaControl *FE) {
    return FE->inicio == NULL;
}

void InserirF(TpFilaControl *&FE, TpProcesso *TP) {
    TpFila *nova = new TpFila;
    nova->info = TP;
    nova->prox = NULL;

    if (FE->inicio == NULL) 
	{  
        FE->inicio = nova;  
        FE->fim = nova;     
    } 
    else 
	{  
        FE->fim->prox = nova;  
        FE->fim = nova;        
    }
}


TpProcesso *RetirarF(TpFilaControl *&FE) {
    TpFila *aux = FE->inicio;
    TpProcesso *proc = aux->info;
    
    FE->inicio = aux->prox;  

    if (FE->inicio == NULL) 
	{  
        FE->fim = NULL;  
    }

    delete aux;
    return proc;
}


void LimparFila(TpFilaControl* &FE) {
    while (FE->inicio != NULL) 
	{
        RetirarF(FE);  
    }
}


void limparAreaFilaEspera() {
    int startX = 4;  // Coluna inicial
    int startY = 19; // Linha inicial
    int endX = 117;  // Coluna final
    int endY = 21;   // Linha final
    
    textbackground(0);  
    
    for (int y = startY; y <= endY; y++) 
	{
        gotoxy(startX, y);
        for (int x = startX; x <= endX; x++) 
		{
            printf(" ");  
        }
    }
    gotoxy(120, 30);  // Reposiciona o cursor no final
}

void ExibirFilaFBAIXO(TpFilaControl *FE, int select) 
{
    limparAreaFilaEspera();

    if (FilaVaziaF(FE)) 
	{  
        gotoxy(55, 20);
        printf("V A Z I A");
    } 
    else 
    {
        int y = 19; 
        int x = 4;   
        TpFila *temp = FE->inicio;  
        
        // Percorre a fila até chegar ao último elemento
        while (temp != NULL) {
            textcolor(15);
            gotoxy(x, y);         
            printf("PD: %d", temp->info->pid); 

            gotoxy(x, y + 1);     
            printf("E: %c", temp->info->estado);

            gotoxy(x, y + 2);     
            if(select == 0)
            	printf("TE: %d", temp->info->tempoEspera);  
            else
            	printf("TB: %d", temp->info->tempoBloqueado); 
            
            temp = temp->prox;  
            x += 7;  
        }

        // Desenha as linhas verticais de separação
        textcolor(2);
        for (int i = 10; i < 115; i += 7) {
            gotoxy(i, 19); printf("|");
            gotoxy(i, 20); printf("|");
            gotoxy(i, 21); printf("|");
        }
    }

    textcolor(15);  // Reseta a cor padrão
    gotoxy(120, 30);  // Reposiciona o cursor
}

void ExibirFilaFCIMA(TpFilaControl *FE, int select) 
{
    limparAreaFilaEspera();

    if (FilaVaziaF(FE)) 
	{  
        gotoxy(55, 20);
        printf("V A Z I A");
    } 
    else 
    {
        int y = 13;  
        int x = 4;   

        TpFila *temp = FE->inicio;  
        
        while (temp != NULL) 
		{
            textcolor(15);
            gotoxy(x, y);         
            printf("PD: %d", temp->info->pid);  

            gotoxy(x, y + 1);     
            printf("E: %c", temp->info->estado); 

            gotoxy(x, y + 2);     
            if(select == 0)
            	printf("TE: %d", temp->info->tempoEspera);  
            else
            	printf("TB: %d", temp->info->tempoBloqueado); 
            
            temp = temp->prox;  
            x += 7;  
        }

        textcolor(2);
        for (int i = 10; i < 115; i += 7) 
		{
            gotoxy(i, 13); printf("|");
            gotoxy(i, 14); printf("|");
            gotoxy(i, 15); printf("|");
        }
    }
}

int ContarProcessosExecucaoPronto(TpFilaControl *FTerminado, int tempoCPU) {
    int contador = 0;  
    TpFila *atual = FTerminado->inicio;  
    
    while (atual != NULL) {
        TpProcesso *proc = atual->info;  

        if (proc->tempoExecucao > tempoCPU && proc->tempoBloqueado == 0) {
            contador++;  
        }

        atual = atual->prox;  
    }

    return contador;  
}

void ContarProcessosBloqueados(TpFilaControl *FTerminado, int &qtdeBloqueados, int &tempoMedioBloqueio) {
    int somaBloqueio = 0;
    qtdeBloqueados = 0;

    TpFila *atual = FTerminado->inicio;

    while (atual != NULL) {
        TpProcesso *proc = atual->info;

        if (proc->tempoBloqueado > 0) 
		{
            qtdeBloqueados++;
            somaBloqueio += proc->tempoBloqueado;
        }

        atual = atual->prox;
    }

    if (qtdeBloqueados > 0) 
	{
        tempoMedioBloqueio = somaBloqueio / qtdeBloqueados;
    } 
	else 
	{
        tempoMedioBloqueio = 0;
    }
}

void ExibirRelatorio(TpFilaControl *FTerminado) {
	limparAreaFilaEspera();
	char linha[200];
	int x = 20, y = 2, color = 1, cont = 0;
	FILE *Ptr = fopen("LetreiroRelatorio.txt", "r");
	fgets(linha, sizeof(linha), Ptr);
    
    while (!feof(Ptr)) {
        gotoxy(x, y);
        printf("%s", linha);
        fgets(linha, sizeof(linha), Ptr);
        y++;
    }

	if (FilaVaziaF(FTerminado)) {
		gotoxy(51, 15);
        printf("Relatorio Vazio!");
	} 
	else 
	{
		int QtdeFinalizado = FTerminado->qtdeFinalizado;
		int qtdeBloqueados = 0;
		int tempoTotalExecucao = 0;
		int tempoMedioBloqueio = 0;
		TpFila *FterminadoAux = FTerminado->inicio;
		x = 3; y = 12; color = 1;

		// Contar processos bloqueados e calcular tempo médio de bloqueio
		ContarProcessosBloqueados(FTerminado, qtdeBloqueados, tempoMedioBloqueio);

		// Exibir informações gerais
		textcolor(4);
		gotoxy(90, 11); printf("Processos Finalizados = %d", QtdeFinalizado);
		gotoxy(90, 12); printf("Qtde proc. Bloqueados = %d", qtdeBloqueados);
		gotoxy(90, 13); printf("Tempo Medio Bloqueio = %d", tempoMedioBloqueio);

		// Contar processos que ficaram entre execução e pronto
		int totalExecucaoPronto = ContarProcessosExecucaoPronto(FTerminado, 10);
		gotoxy(90, 14); printf("Qtde proc. Exec/Pronto = %d", totalExecucaoPronto);

		// Exibir tempo total de execução de cada processo
		gotoxy(3, 11); printf("Tempo Total de Execucao de cada Processo:");
        while (FterminadoAux != NULL) {
        	tempoTotalExecucao = FterminadoAux->info->tempoExecucao + FterminadoAux->info->tempoEspera;
        	textcolor(color);
            gotoxy(x, y); 
            printf("Processo: %d", FterminadoAux->info->pid);
            gotoxy(x, y + 1); 
			printf("Estado: %c", FterminadoAux->info->estado);
			gotoxy(x, y + 2); 
			printf("Filho(s): %d", FterminadoAux->info->criouFilho);
            gotoxy(x, y + 3); 
			printf("Tempo Total Execucao: %d u.t.", tempoTotalExecucao);

            FterminadoAux = FterminadoAux->prox;  
			y += 5;  
            if (color == 15) 
			{
            	color = 0;
            }
            color++;
            if (y == 27 && x < 92) 
			{
            	x += 33;
            	y = 11+1;
            }	
    	}

    	textcolor(4);
    	gotoxy(90, 14); printf("Tempo execucao total = %d s", tempoTotalExecucao);
    	textcolor(15);
	}

    textcolor(15);  // Reseta a cor padrão
    gotoxy(120, 30);  // Reposiciona o cursor
}