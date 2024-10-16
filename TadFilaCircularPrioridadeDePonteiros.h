#define MAXFILA 16

struct TpProcesso {
	int pid;				//Indentificador *Vale lembrar que cada processo poderá utilizar a CPU por no máximo 10 unidades de tempo por vez*
	int ppid;				//Guarda o PID do pai se ele for um filho
	int prioridade;			// Define a prioridade do processo
	char estado;			//'P' - Pronto	//'E' - Espera	//'R' - Running
	int tempoExecucao;		// Tempo que o processo precisa para executar
	int tempoRestante;		// Tempo restante para a conclusão do processo
	int tempoEspera;		// Tempo total que o processo passou em espera	
	int tempoBloqueado;		// Tempo total que o processo ficou bloqueado
	int criouFilho;		    // contador de filhos
	TpProcesso *prox;		// Ponteiro para proximo processo da fila
};

struct TpFilaCirc {
	TpProcesso *inicio;
	TpProcesso *fim;
	int cont;
};

void Inicializar(TpFilaCirc &F) {
    F.inicio = NULL;
    F.fim = NULL;
    F.cont = 0;
}

char FilaCheia(int cont) {
    return cont == MAXFILA; 
}

char FilaVazia(int cont) {
    return cont == 0;
}

void OrganizaPrioridade(TpFilaCirc &F) {
    int trocado;
    do {
        TpProcesso *atual = F.inicio;
        TpProcesso *prox = atual->prox;
        trocado = 0;
        for (int i = 0; i < F.cont; i++) 
		{  
            if (atual->prioridade < prox->prioridade) 
			{  
                TpProcesso temp = *atual;
                atual->pid = prox->pid;
                atual->prioridade = prox->prioridade;
                atual->estado = prox->estado;
                atual->tempoExecucao = prox->tempoExecucao;
                atual->tempoRestante = prox->tempoRestante;
                atual->tempoEspera = prox->tempoEspera;
                atual->tempoBloqueado = prox->tempoBloqueado;
                atual->criouFilho = prox->criouFilho;

                prox->pid = temp.pid;
                prox->prioridade = temp.prioridade;
                prox->estado = temp.estado;
                prox->tempoExecucao = temp.tempoExecucao;
                prox->tempoRestante = temp.tempoRestante;
                prox->tempoEspera = temp.tempoEspera;
                prox->tempoBloqueado = temp.tempoBloqueado;
                prox->criouFilho = temp.criouFilho;

                trocado = 1;
            }
            atual = prox;
            prox = prox->prox;
        }
    } while (trocado);
}

void InserirFilaEspParaPron(TpFilaCirc &FPronto, TpProcesso *proc) {
    proc->estado = 'P';  

    if (FilaVazia(FPronto.cont)) 
	{
        FPronto.inicio = FPronto.fim = proc;
        proc->prox = proc;  
    } 
    else if (FPronto.inicio->prioridade < proc->prioridade) 
	{
        proc->prox = FPronto.inicio;
        FPronto.fim->prox = proc;
        FPronto.inicio = proc;  
    } 
    else 
	{
        proc->prox = FPronto.inicio;
        FPronto.fim->prox = proc;
        FPronto.fim = proc;  
        OrganizaPrioridade(FPronto);  
    }

    FPronto.cont++;  
}


void Inserir(TpFilaCirc &F, int prior, int Pid) {
    TpProcesso *novo = new TpProcesso;
    novo->pid = Pid;
    novo->ppid = 0;
    novo->criouFilho = 0;  
    novo->prioridade = prior;
    novo->estado = 'P';				
    novo->tempoExecucao = 0;
    novo->tempoRestante = (rand() % 30) + 1;	
    novo->tempoEspera = 0;			
    novo->tempoBloqueado = 0;		
    novo->criouFilho = 0;			
    novo->prox = NULL;

    if(FilaVazia(F.cont)) 
	{
        F.inicio = F.fim = novo;
        novo->prox = novo; // Aponta para si mesmo, formando um círculo
    } 
	else if(F.inicio->prioridade < novo->prioridade)
	{
		novo->prox = F.inicio;
		F.fim->prox = novo;		//caso com 2 elementos na fila
		F.inicio = novo;
	}
	else
	{
        novo->prox = F.inicio;
        F.fim->prox = novo;
        F.fim = novo;
        OrganizaPrioridade(F); //organiza as prioridades do processo em caso de 3 ou mais elementos na fila de prontos
    }
    F.cont++;
}

TpProcesso* Retirar(TpFilaCirc &F) {
    if (FilaVazia(F.cont)) 
		return NULL;
	else
	{
		TpProcesso *temp = F.inicio;
	    if (F.inicio == F.fim) 
		{
	        F.inicio = F.fim = NULL;
	    } 
		else 
		{
	        F.inicio = temp->prox;
	        F.fim->prox = F.inicio;
	    }
	    F.cont--;
	    return temp;
	}
}

void ExibeFC(TpFilaCirc F) {
    if (FilaVazia(F.cont)) 
	{
        printf("Fila Vazia\n");
    }
	else
	{
		int y = 13;
		int x = 4;
		TpProcesso* temp = F.inicio;
		do{
			textcolor(15);
			gotoxy(x,y);	//linha 13
       	    printf("PD:%d", temp->pid);
       	    gotoxy(x,y+1);	//linha 14
       	    printf("PR:%d", temp->prioridade);
       	    gotoxy(x,y+2);	//linha 15
       	    printf("TR:%d", temp->tempoRestante);
        	temp = temp->prox;
        	x+=7;
    	}while (temp != F.inicio && temp != NULL);
    	textcolor(2);
    	for(int i = 10; i < 115; i+=7)
    	{
    		gotoxy(i,13);printf("|");
    		gotoxy(i,14);printf("|");
    		gotoxy(i,15);printf("|");
		}
	}
}
