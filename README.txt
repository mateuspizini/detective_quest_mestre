Detective Quest - Nível Mestre - Teste Automatizado
===============================================

Para testar o programa, execute:
.\detective_quest_mestre.exe

O programa implementa:

1. ÁRVORE BINÁRIA DE SALAS:
   - Estrutura de navegação pela mansão
   - Cada sala tem nome, pista opcional e ponteiros para esquerda/direita

2. BST DE PISTAS:
   - Armazena pistas coletadas em ordem alfabética
   - Inserção automática sem duplicatas
   - Exibição ordenada no relatório final

3. TABELA HASH DE SUSPEITOS:
   - Associa cada pista a um suspeito específico
   - Função hash baseada na soma dos caracteres
   - Tratamento de colisões com listas encadeadas

4. SISTEMA DE ACUSAÇÃO:
   - Contador de pistas por suspeito
   - Verificação de evidências suficientes (≥2 pistas)
   - Veredicto automático baseado nas evidências

SUSPEITOS E SUAS PISTAS:

Dr. Smith (especialista em venenos):
- Livro sobre venenos deixado aberto na mesa
- Frasco vazio de arsênico  
- Flores venenosas recentemente colhidas

Sra. Johnson (acesso aos documentos):
- Carta de ameaça parcialmente queimada
- Documento com assinatura falsificada

Sr. Williams (conhece a casa):
- Uma pegada estranha na entrada principal
- Cinzas ainda quentes na lareira
- Partitura com código secreto

Mordomo James (acesso à cozinha e jardim):
- Faca com manchas suspeitas
- Luvas com resíduos tóxicos

MAPA DA MANSÃO:
                    Hall de Entrada
                   /                \
            Biblioteca            Sala de Estar
           /         \            /            \
    Escritório   Sala Música   Cozinha      Jardim
       /             \           /             \
Cofre Secreto   Piano Antigo  Despensa      Estufa

COMO VENCER:
- Explore todas as salas para coletar o máximo de pistas
- Dr. Smith tem 3 pistas (mais fácil de acusar)
- Sr. Williams tem 3 pistas (também uma boa opção)
- Sra. Johnson e Mordomo James têm 2 pistas cada