#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 20  // Tamanho da tabela hash para pistas/suspeitos

/**
 * Estrutura que representa uma pista coletada
 * Usada para criar uma árvore binária de busca (BST) das pistas
 */
typedef struct PistaNode {
    char conteudo[100];              // Conteúdo da pista encontrada
    struct PistaNode* esquerda;      // Ponteiro para pista lexicograficamente menor
    struct PistaNode* direita;       // Ponteiro para pista lexicograficamente maior
} PistaNode;

/**
 * Estrutura que representa uma sala da mansão
 * Cada sala possui um nome, uma pista opcional e ponteiros para duas salas adjacentes
 */
typedef struct Sala {
    char nome[50];           // Nome da sala
    char pista[100];         // Pista encontrada nesta sala (pode estar vazia)
    struct Sala* esquerda;   // Ponteiro para a sala à esquerda
    struct Sala* direita;    // Ponteiro para a sala à direita
} Sala;

/**
 * Estrutura que representa um nó da tabela hash
 * Cada nó contém uma pista (chave) e o suspeito associado (valor)
 */
typedef struct HashNode {
    char pista[100];            // Chave: pista encontrada
    char suspeito[50];          // Valor: nome do suspeito associado
    struct HashNode* proximo;   // Ponteiro para o próximo nó (tratamento de colisões)
} HashNode;

/**
 * Estrutura que representa a tabela hash de pistas/suspeitos
 */
typedef struct TabelaHash {
    HashNode* tabela[TAMANHO_HASH];  // Array de ponteiros para os nós
} TabelaHash;

/**
 * Função: funcaoHash
 * Propósito: Calcular o índice na tabela hash para uma dada pista
 * Parâmetros: pista - string da pista para calcular o hash
 * Retorno: índice na tabela hash (0 a TAMANHO_HASH-1)
 */
int funcaoHash(const char* pista) {
    int hash = 0;
    for (int i = 0; pista[i] != '\0'; i++) {
        hash += (int)pista[i];
    }
    return hash % TAMANHO_HASH;
}

/**
 * Função: criarTabelaHash
 * Propósito: Criar e inicializar uma nova tabela hash
 * Retorno: ponteiro para a tabela hash criada
 */
TabelaHash* criarTabelaHash() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) {
        printf("Erro: Falha na alocação de memória para tabela hash!\n");
        return NULL;
    }
    
    // Inicializa todos os ponteiros como NULL
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela->tabela[i] = NULL;
    }
    
    return tabela;
}

/**
 * Função: inserirNaHash
 * Propósito: Inserir uma associação pista/suspeito na tabela hash
 * Parâmetros: tabela - ponteiro para a tabela hash
 *             pista - string da pista (chave)
 *             suspeito - string do nome do suspeito (valor)
 * Retorno: void
 */
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* suspeito) {
    if (tabela == NULL) return;
    
    int indice = funcaoHash(pista);
    
    // Cria um novo nó
    HashNode* novoNode = (HashNode*)malloc(sizeof(HashNode));
    if (novoNode == NULL) {
        printf("Erro: Falha na alocação de memória para nó hash!\n");
        return;
    }
    
    strcpy(novoNode->pista, pista);
    strcpy(novoNode->suspeito, suspeito);
    novoNode->proximo = tabela->tabela[indice];  // Inserção no início da lista
    tabela->tabela[indice] = novoNode;
}

/**
 * Função: encontrarSuspeito
 * Propósito: Buscar o suspeito associado a uma pista na tabela hash
 * Parâmetros: tabela - ponteiro para a tabela hash
 *             pista - string da pista a ser buscada
 * Retorno: ponteiro para o nome do suspeito ou NULL se não encontrado
 */
char* encontrarSuspeito(TabelaHash* tabela, const char* pista) {
    if (tabela == NULL) return NULL;
    
    int indice = funcaoHash(pista);
    HashNode* atual = tabela->tabela[indice];
    
    // Percorre a lista encadeada no índice
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    
    return NULL;  // Pista não encontrada
}

/**
 * Função: criarSala
 * Propósito: Criar uma nova sala com nome e pista especificados usando alocação dinâmica
 * Parâmetros: nome - string com o nome da sala
 *             pista - string com a pista da sala (pode ser vazia)
 * Retorno: ponteiro para a nova sala criada
 */
Sala* criarSala(const char* nome, const char* pista) {
    // Aloca memória dinamicamente para uma nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return NULL;
    }
    
    // Copia o nome e a pista para a sala e inicializa os ponteiros como NULL
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * Função: criarPistaNode
 * Propósito: Criar um novo nó para a árvore de pistas usando alocação dinâmica
 * Parâmetros: conteudo - string com o conteúdo da pista
 * Retorno: ponteiro para o novo nó de pista criado
 */
PistaNode* criarPistaNode(const char* conteudo) {
    // Aloca memória dinamicamente para um novo nó de pista
    PistaNode* novoNode = (PistaNode*)malloc(sizeof(PistaNode));
    
    // Verifica se a alocação foi bem-sucedida
    if (novoNode == NULL) {
        printf("Erro: Falha na alocação de memória para pista!\n");
        return NULL;
    }
    
    // Copia o conteúdo e inicializa os ponteiros como NULL
    strcpy(novoNode->conteudo, conteudo);
    novoNode->esquerda = NULL;
    novoNode->direita = NULL;
    
    return novoNode;
}

/**
 * Função: inserirPista (também conhecida como adicionarPista)
 * Propósito: Inserir uma nova pista na árvore BST de pistas em ordem alfabética
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 *             conteudo - string com o conteúdo da pista a ser inserida
 * Retorno: ponteiro para a raiz da árvore (pode ter mudado)
 */
PistaNode* inserirPista(PistaNode* raiz, const char* conteudo) {
    // Caso base: árvore vazia ou chegou ao local de inserção
    if (raiz == NULL) {
        return criarPistaNode(conteudo);
    }
    
    // Compara a nova pista com a pista atual
    int comparacao = strcmp(conteudo, raiz->conteudo);
    
    if (comparacao < 0) {
        // Nova pista é menor lexicograficamente - insere à esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, conteudo);
    } else if (comparacao > 0) {
        // Nova pista é maior lexicograficamente - insere à direita
        raiz->direita = inserirPista(raiz->direita, conteudo);
    }
    // Se comparacao == 0, a pista já existe, não insere duplicata
    
    return raiz;
}

/**
 * Função: exibirPistas
 * Propósito: Exibir todas as pistas coletadas em ordem alfabética
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 *             contador - ponteiro para variável que conta as pistas exibidas
 * Retorno: void
 */
void exibirPistas(PistaNode* raiz, int* contador) {
    if (raiz != NULL) {
        // Percorre em ordem (in-order): esquerda, raiz, direita
        exibirPistas(raiz->esquerda, contador);
        
        (*contador)++;
        printf("%d. %s\n", *contador, raiz->conteudo);
        
        exibirPistas(raiz->direita, contador);
    }
}

/**
 * Função: contarPistasPorSuspeito
 * Propósito: Contar quantas pistas apontam para um determinado suspeito
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 *             tabela - ponteiro para a tabela hash
 *             suspeito - nome do suspeito a ser contado
 * Retorno: número de pistas que apontam para o suspeito
 */
int contarPistasPorSuspeito(PistaNode* raiz, TabelaHash* tabela, const char* suspeito) {
    if (raiz == NULL) return 0;
    
    int count = 0;
    char* suspeitoAssociado = encontrarSuspeito(tabela, raiz->conteudo);
    
    if (suspeitoAssociado != NULL && strcmp(suspeitoAssociado, suspeito) == 0) {
        count = 1;
    }
    
    // Recursivamente conta nas subárvores esquerda e direita
    count += contarPistasPorSuspeito(raiz->esquerda, tabela, suspeito);
    count += contarPistasPorSuspeito(raiz->direita, tabela, suspeito);
    
    return count;
}

/**
 * Função: listarPistasPorSuspeito
 * Propósito: Listar todas as pistas que apontam para um determinado suspeito
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 *             tabela - ponteiro para a tabela hash
 *             suspeito - nome do suspeito
 * Retorno: void
 */
void listarPistasPorSuspeito(PistaNode* raiz, TabelaHash* tabela, const char* suspeito) {
    if (raiz == NULL) return;
    
    // Percorre em ordem (in-order)
    listarPistasPorSuspeito(raiz->esquerda, tabela, suspeito);
    
    char* suspeitoAssociado = encontrarSuspeito(tabela, raiz->conteudo);
    if (suspeitoAssociado != NULL && strcmp(suspeitoAssociado, suspeito) == 0) {
        printf("   - %s\n", raiz->conteudo);
    }
    
    listarPistasPorSuspeito(raiz->direita, tabela, suspeito);
}

/**
 * Função: verificarSuspeitoFinal
 * Propósito: Conduzir a fase de julgamento final, verificando se há evidências suficientes
 * Parâmetros: arvorePistas - ponteiro para a raiz da árvore de pistas
 *             tabela - ponteiro para a tabela hash de pistas/suspeitos
 * Retorno: void
 */
void verificarSuspeitoFinal(PistaNode* arvorePistas, TabelaHash* tabela) {
    char suspeitoAcusado[50];
    
    printf("\n=== FASE DE ACUSACAO FINAL ===\n");
    printf("Com base nas pistas coletadas, voce deve fazer sua acusacao!\n");
    printf("Suspeitos disponiveis: Dr. Smith, Sra. Johnson, Sr. Williams, Mordomo James\n");
    printf("\nQuem voce acusa do crime? ");
    
    // Lê o nome do suspeito com espaços
    fgets(suspeitoAcusado, sizeof(suspeitoAcusado), stdin);
    suspeitoAcusado[strcspn(suspeitoAcusado, "\n")] = 0; // Remove quebra de linha
    
    // Conta quantas pistas apontam para o suspeito acusado
    int pistasEncontradas = contarPistasPorSuspeito(arvorePistas, tabela, suspeitoAcusado);
    
    printf("\n=== ANALISE DAS EVIDENCIAS ===\n");
    printf("Suspeito acusado: %s\n", suspeitoAcusado);
    printf("Pistas que apontam para %s: %d\n", suspeitoAcusado, pistasEncontradas);
    
    if (pistasEncontradas > 0) {
        printf("\nPistas encontradas:\n");
        listarPistasPorSuspeito(arvorePistas, tabela, suspeitoAcusado);
    }
    
    printf("\n=== VEREDICTO ===\n");
    if (pistasEncontradas >= 2) {
        printf("*** PARABENS! ***\n");
        printf("Voce resolveu o caso com sucesso!\n");
        printf("Ha evidencias suficientes (%d pistas) para sustentar sua acusacao.\n", pistasEncontradas);
        printf("%s foi preso(a) e confessou o crime!\n", suspeitoAcusado);
        printf("A mansao misteriosa finalmente pode descansar em paz.\n");
    } else {
        printf("*** CASO NAO RESOLVIDO ***\n");
        printf("Evidencias insuficientes para uma condenacao.\n");
        printf("Voce precisa de pelo menos 2 pistas convincentes para sustentar a acusacao.\n");
        if (pistasEncontradas == 1) {
            printf("Apenas 1 pista foi encontrada - nao e suficiente para o tribunal.\n");
        } else {
            printf("Nenhuma pista aponta para %s.\n", suspeitoAcusado);
        }
        printf("O caso permanece em aberto...\n");
    }
}

/**
 * Função: inicializarSuspeitos
 * Propósito: Preencher a tabela hash com as associações entre pistas e suspeitos
 * Parâmetros: tabela - ponteiro para a tabela hash
 * Retorno: void
 */
void inicializarSuspeitos(TabelaHash* tabela) {
    // Dr. Smith - especialista em venenos
    inserirNaHash(tabela, "Livro sobre venenos deixado aberto na mesa", "Dr. Smith");
    inserirNaHash(tabela, "Frasco vazio de arsênico", "Dr. Smith");
    inserirNaHash(tabela, "Flores venenosas recentemente colhidas", "Dr. Smith");
    
    // Sra. Johnson - acesso aos documentos
    inserirNaHash(tabela, "Carta de ameaca parcialmente queimada", "Sra. Johnson");
    inserirNaHash(tabela, "Documento com assinatura falsificada", "Sra. Johnson");
    
    // Sr. Williams - conhece a casa
    inserirNaHash(tabela, "Uma pegada estranha na entrada principal", "Sr. Williams");
    inserirNaHash(tabela, "Cinzas ainda quentes na lareira", "Sr. Williams");
    inserirNaHash(tabela, "Partitura com codigo secreto", "Sr. Williams");
    
    // Mordomo James - acesso à cozinha e jardim
    inserirNaHash(tabela, "Faca com manchas suspeitas", "Mordomo James");
    inserirNaHash(tabela, "Luvas com residuos toxicos", "Mordomo James");
}

/**
 * Função: explorarSalas
 * Propósito: Permitir a navegação interativa do jogador pela mansão com coleta de pistas
 * Parâmetros: salaAtual - ponteiro para a sala onde o jogador está
 *             arvorePistas - ponteiro para ponteiro da raiz da árvore de pistas
 *             tabela - ponteiro para a tabela hash de suspeitos
 * Retorno: void
 */
void explorarSalas(Sala* salaAtual, PistaNode** arvorePistas, TabelaHash* tabela) {
    char escolha;
    int pistasColetadas = 0;
    
    // Continua explorando até o jogador decidir sair
    while (salaAtual != NULL) {
        printf("\n=== DETECTIVE QUEST - NIVEL MESTRE ===\n");
        printf("Voce esta na: %s\n", salaAtual->nome);
        
        // Verifica se há uma pista nesta sala
        if (strlen(salaAtual->pista) > 0) {
            printf("\n*** PISTA ENCONTRADA! ***\n");
            printf("Pista: %s\n", salaAtual->pista);
            
            // Adiciona a pista à árvore de pistas
            *arvorePistas = inserirPista(*arvorePistas, salaAtual->pista);
            pistasColetadas++;
            
            // Encontra o suspeito associado à pista
            char* suspeito = encontrarSuspeito(tabela, salaAtual->pista);
            if (suspeito != NULL) {
                printf("Esta pista aponta para: %s\n", suspeito);
            } else {
                printf("Pista nao associada a nenhum suspeito conhecido.\n");
            }
            
            printf("Pista adicionada ao seu caderno de investigacao!\n");
        } else {
            printf("\nEsta sala nao contem pistas visiveis.\n");
        }
        
        // Verifica se é uma sala final (nó-folha)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\nVoce chegou ao fim deste caminho!\n");
            printf("Esta sala nao possui mais saidas.\n");
            printf("Pressione 's' para sair ou explore outro caminho.\n");
        }
        
        // Exibe as opções disponíveis
        printf("\nOpcoes de navegacao:\n");
        if (salaAtual->esquerda != NULL) {
            printf("(e) - Ir para a esquerda: %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("(d) - Ir para a direita: %s\n", salaAtual->direita->nome);
        }
        printf("(s) - Encerrar investigacao e fazer acusacao final\n");
        
        printf("\nEscolha sua acao: ");
        scanf(" %c", &escolha);
        getchar(); // Limpa o buffer para fgets
        
        // Processa a escolha do jogador
        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                    printf("\nMovendo-se para a esquerda...\n");
                } else {
                    printf("\nNao ha caminho a esquerda! Tente outra direcao.\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                    printf("\nMovendo-se para a direita...\n");
                } else {
                    printf("\nNao ha caminho a direita! Tente outra direcao.\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("\n=== RELATORIO FINAL DE INVESTIGACAO ===\n");
                printf("Investigacao da mansao encerrada!\n");
                
                // Exibe todas as pistas coletadas
                if (*arvorePistas != NULL) {
                    printf("\nPistas coletadas (em ordem alfabetica):\n");
                    printf("========================================\n");
                    int contador = 0;
                    exibirPistas(*arvorePistas, &contador);
                    printf("========================================\n");
                    printf("Total de pistas coletadas: %d\n", contador);
                    
                    // Inicia a fase de acusação final
                    verificarSuspeitoFinal(*arvorePistas, tabela);
                } else {
                    printf("\nNenhuma pista foi coletada durante a investigacao.\n");
                    printf("Impossivel fazer uma acusacao sem evidencias!\n");
                }
                
                printf("\nObrigado por jogar Detective Quest - Nivel Mestre!\n");
                return;
                
            default:
                printf("\nOpcao invalida! Use 'e' para esquerda, 'd' para direita ou 's' para sair.\n");
                break;
        }
    }
}

/**
 * Função: liberarMemoriaSalas
 * Propósito: Liberar toda a memória alocada para a árvore de salas
 * Parâmetros: raiz - ponteiro para a raiz da árvore
 * Retorno: void
 */
void liberarMemoriaSalas(Sala* raiz) {
    if (raiz != NULL) {
        liberarMemoriaSalas(raiz->esquerda);
        liberarMemoriaSalas(raiz->direita);
        free(raiz);
    }
}

/**
 * Função: liberarMemoriaPistas
 * Propósito: Liberar toda a memória alocada para a árvore de pistas
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 * Retorno: void
 */
void liberarMemoriaPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarMemoriaPistas(raiz->esquerda);
        liberarMemoriaPistas(raiz->direita);
        free(raiz);
    }
}

/**
 * Função: liberarMemoriaHash
 * Propósito: Liberar toda a memória alocada para a tabela hash
 * Parâmetros: tabela - ponteiro para a tabela hash
 * Retorno: void
 */
void liberarMemoriaHash(TabelaHash* tabela) {
    if (tabela == NULL) return;
    
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashNode* atual = tabela->tabela[i];
        while (atual != NULL) {
            HashNode* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(tabela);
}

/**
 * Função: main
 * Propósito: Montar o mapa inicial da mansão com pistas, inicializar a tabela de suspeitos
 * e iniciar a exploração completa do nível mestre
 * Retorno: 0 se o programa executar com sucesso
 */
int main() {
    printf("=== BEM-VINDO AO DETECTIVE QUEST - NIVEL MESTRE ===\n");
    printf("Explore a mansao misteriosa, colete pistas e desvende quem e o culpado!\n");
    printf("Use 'e' para ir a esquerda, 'd' para direita e 's' para encerrar.\n");
    printf("As pistas serao associadas automaticamente aos suspeitos!\n");
    printf("No final, voce devera fazer uma acusacao baseada nas evidencias!\n");
    
    // Inicializa a árvore de pistas como vazia
    PistaNode* arvorePistas = NULL;
    
    // Cria e inicializa a tabela hash de suspeitos
    TabelaHash* tabelaSuspeitos = criarTabelaHash();
    if (tabelaSuspeitos == NULL) {
        printf("Erro: Nao foi possivel criar a tabela de suspeitos!\n");
        return 1;
    }
    
    // Preenche a tabela hash com as associações pista/suspeito
    inicializarSuspeitos(tabelaSuspeitos);
    
    // Criação manual da árvore binária representando o mapa da mansão com pistas
    
    // Nível 0 - Raiz (Hall de entrada)
    Sala* hallEntrada = criarSala("Hall de Entrada", "Uma pegada estranha na entrada principal");
    
    // Nível 1
    Sala* biblioteca = criarSala("Biblioteca", "Livro sobre venenos deixado aberto na mesa");
    Sala* salaEstar = criarSala("Sala de Estar", "Cinzas ainda quentes na lareira");
    
    // Nível 2 - Lado esquerdo (filhos da Biblioteca)
    Sala* escritorio = criarSala("Escritorio", "Carta de ameaca parcialmente queimada");
    Sala* salaMusica = criarSala("Sala de Musica", "");  // Sem pista
    
    // Nível 2 - Lado direito (filhos da Sala de Estar)
    Sala* cozinha = criarSala("Cozinha", "Faca com manchas suspeitas");
    Sala* jardim = criarSala("Jardim", "Flores venenosas recentemente colhidas");
    
    // Nível 3 - Folhas (salas finais)
    Sala* cofre = criarSala("Cofre Secreto", "Documento com assinatura falsificada");
    Sala* piano = criarSala("Piano Antigo", "Partitura com codigo secreto");
    Sala* despensa = criarSala("Despensa", "Frasco vazio de arsênico");
    Sala* greenhouse = criarSala("Estufa", "Luvas com residuos toxicos");
    
    // Montagem da estrutura da árvore
    
    // Hall de entrada -> Biblioteca (esquerda) e Sala de Estar (direita)
    hallEntrada->esquerda = biblioteca;
    hallEntrada->direita = salaEstar;
    
    // Biblioteca -> Escritório (esquerda) e Sala de Música (direita)
    biblioteca->esquerda = escritorio;
    biblioteca->direita = salaMusica;
    
    // Sala de Estar -> Cozinha (esquerda) e Jardim (direita)
    salaEstar->esquerda = cozinha;
    salaEstar->direita = jardim;
    
    // Escritório -> Cofre Secreto (esquerda apenas)
    escritorio->esquerda = cofre;
    
    // Sala de Música -> Piano Antigo (direita apenas)
    salaMusica->direita = piano;
    
    // Cozinha -> Despensa (esquerda apenas)
    cozinha->esquerda = despensa;
    
    // Jardim -> Estufa (direita apenas)
    jardim->direita = greenhouse;
    
    // Inicia a exploração a partir do Hall de entrada
    explorarSalas(hallEntrada, &arvorePistas, tabelaSuspeitos);
    
    // Libera toda a memória alocada
    liberarMemoriaSalas(hallEntrada);
    liberarMemoriaPistas(arvorePistas);
    liberarMemoriaHash(tabelaSuspeitos);
    
    return 0;
}