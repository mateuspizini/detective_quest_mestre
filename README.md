# 🕵️ Detective Quest - Nível Mestre

Um jogo de investigação interativo implementado em C que combina estruturas de dados avançadas para criar uma experiência de detetive envolvente.

## 📋 Sobre o Projeto

Este é o nível mais avançado do Detective Quest, onde o jogador explora uma mansão misteriosa, coleta pistas e deve identificar o culpado com base nas evidências coletadas. O projeto demonstra a integração de três estruturas de dados fundamentais:

- **Árvore Binária**: Para navegação pela mansão
- **BST (Binary Search Tree)**: Para armazenamento ordenado de pistas
- **Tabela Hash**: Para associação eficiente entre pistas e suspeitos

## 🎮 Como Jogar

### Compilação
```bash
gcc detective_quest_mestre.c -o detective_quest_mestre.exe
```

### Execução
```bash
./detective_quest_mestre.exe
```

### Controles
- `e` - Ir para a esquerda
- `d` - Ir para a direita  
- `s` - Encerrar investigação e fazer acusação

## 🏗️ Estruturas de Dados Implementadas

### 1. Árvore Binária de Salas
```c
typedef struct Sala {
    char nome[50];           // Nome da sala
    char pista[100];         // Pista encontrada nesta sala
    struct Sala* esquerda;   // Sala à esquerda
    struct Sala* direita;    // Sala à direita
} Sala;
```

### 2. BST de Pistas
```c
typedef struct PistaNode {
    char conteudo[100];              // Conteúdo da pista
    struct PistaNode* esquerda;      // Pista lexicograficamente menor
    struct PistaNode* direita;       // Pista lexicograficamente maior
} PistaNode;
```

### 3. Tabela Hash de Suspeitos
```c
typedef struct HashNode {
    char pista[100];            // Chave: pista encontrada
    char suspeito[50];          // Valor: suspeito associado
    struct HashNode* proximo;   // Tratamento de colisões
} HashNode;
```

## 🗺️ Mapa da Mansão

```
                    Hall de Entrada
                   /                \
            Biblioteca            Sala de Estar
           /         \            /            \
    Escritório   Sala Música   Cozinha      Jardim
       /             \           /             \
Cofre Secreto   Piano Antigo  Despensa      Estufa
```

## 🕵️ Suspeitos e Pistas

### Dr. Smith (Especialista em Venenos)
- Livro sobre venenos deixado aberto na mesa
- Frasco vazio de arsênico
- Flores venenosas recentemente colhidas

### Sra. Johnson (Acesso aos Documentos)
- Carta de ameaça parcialmente queimada
- Documento com assinatura falsificada

### Sr. Williams (Conhece a Casa)
- Uma pegada estranha na entrada principal
- Cinzas ainda quentes na lareira
- Partitura com código secreto

### Mordomo James (Acesso à Cozinha e Jardim)
- Faca com manchas suspeitas
- Luvas com resíduos tóxicos

## 🎯 Objetivo

Colete pelo menos **2 pistas** que apontem para o mesmo suspeito para fazer uma acusação bem-sucedida. O sistema verifica automaticamente se há evidências suficientes para sustentar sua acusação.

## ⚙️ Funcionalidades Técnicas

### Funções Principais Documentadas:
- `criarSala()` - Criação dinâmica de cômodos
- `explorarSalas()` - Navegação e coleta de pistas
- `inserirPista()` - Inserção na BST de evidências  
- `inserirNaHash()` - Associação pista/suspeito
- `encontrarSuspeito()` - Consulta na tabela hash
- `verificarSuspeitoFinal()` - Sistema de acusação

### Gerenciamento de Memória:
- Alocação dinâmica para todas as estruturas
- Funções específicas de liberação de memória
- Tratamento de erros de alocação

## 🏆 Conceitos Trabalhados

- **Árvores Binárias**: Estrutura hierárquica de navegação
- **BST**: Inserção e busca ordenada
- **Tabela Hash**: Função hash e tratamento de colisões
- **Recursividade**: Percorrimento de árvores
- **Alocação Dinâmica**: Gerenciamento eficiente de memória
- **Structs e Ponteiros**: Manipulação de dados compostos

## 📁 Arquivos do Projeto

- `detective_quest_mestre.c` - Código principal do jogo
- `README.md` - Documentação do projeto
- `README.txt` - Guia de teste rápido

## 🚀 Como Vencer

1. **Explore todas as salas** para coletar o máximo de pistas
2. **Dr. Smith** tem 3 pistas (mais fácil de acusar)
3. **Sr. Williams** tem 3 pistas (também uma boa opção)
4. **Sra. Johnson** e **Mordomo James** têm 2 pistas cada
5. Faça sua acusação baseada nas evidências coletadas

---

*Desenvolvido como parte do curso de Análise de Sistemas - Estruturas de Dados*