// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de s  trings, facilitando a manutenção.
#define TAM_NOME 30
#define TAM_COR 10
#define TAM_MISSAO 100
#define TOTAL_MISSOES 5

// --- Definição da Estrutura (struct) ---
// Aqui, foi criado um "Territorio" que guarda nome, quantas missoes.
typedef struct {
    char nome[TAM_NOME];
    char cor [TAM_COR];
    int tropas;
} Territorios;

// --- Protótipos das Funções ---
// "Protótipos" informam ao compilador sobre as funções que serão usadas, e que se encontram depois da função main.
void limparBuffer();
Territorio* cadastrarTerritorios(int quantidade);
void exibirMapa0(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(char* missao);


//Vetor de missões pré-definidas
char* missoesPredefinidas[TOTAL_MISSOES] = {
    "Consquitar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar pelo menos 5 territorios",
    "Destruir todas as tropas inimigas",
    "Manter 10 tropas em seu territorio principal",
};

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios

        int quantidade;
        printf("=== SISTEMA DE GUERRA - WAR ===\n\n");
        printf("Quantos territorios deseja cadastrar? ");
        scanf("%d", $quantidade);
        limparBuffer();

        if (quantidade <=0) {
            printf("Quantidade invalida!\n");
            return 1;
        }

        //Alocação dinâmica de memória para territórios
        Territorio* mapa = cadastrarTerritorios(quantidade);
        if (mapa == NULL) {
            printf("Erro na alocação de memória!\n");
            return 1;
        }

        //Alocação dinâmica para a missão do jogador
        char* missaoJogador = (char*)malloc(TAM_MISSAO * sizeof(char));
        if (missaoJogador == NULL) {
            printf("Erro na alocção de memória para missão!\n");
            liberarMemoria(mapa);
            return 1;
        }

        //Atribuir missão aleatória ao Jogador
        atribuirMissao(missaoJogador, missoesPredefinidas, TOTAL_MISSOES);

        printf("\n=== MISSAO DO JOGADOR ===\n");
        exibirMissao(missaoJogador);
        printf("===================\n\n");

        exibirMapa(mapa, quantidade);

        //Sistema de ataques
        int continuar = 1;
        inte turno = 1;

        while (continuar) {
            printf("\n=== TURNO %d - FASE DE ATAQUE ===\n, turno");

            //Exibir territórios disponíveis
            printf("\nTerritorios disponiveis:\n");
            for (int i = 0; i < quantidade; i++) {
                printf("%d - %s (%s) - %d tropas\n",
                        i + 1, mapa[1].nome, mapa[i].cor, mapa[i].tropas);
            }

            //Selecionar atacante
            int idxAtacante, idxDefensor;
            printf("\nSelecione o territorio ATACANTE (numero): ");
            scanf("%d", &idxAtacante);
            idxAtacante--; // Ajusta para o índice do array

            if (idAtacante < 0 || idxAtacante >= quantidade) {
                printf("Territorio invalido\n");
                continue;
            }

            //Selecionar defensor
            printf("Selecione o territorio DEFENSERO (numero): ");
            scanf("%d", &idxDefensor);
            idxDefensor--; // Ajusta para o índice do array

            if (idxDefensor < 0 || idxDefensor >= quantidade) {
                printf("Territorio invalido\n");
                continue;
            }

            // Validar Ataque
            if (idxAtacante == idxDefensor) {
                printf("Nao pode atecar o proprio territorio\n");
                continue;
            }

            if (strcmp(mapa[idxAtacante].cor, mapa [idxDefensor].cor) == 0) {
                printf("Nao pode atacar o territorio da mesma cor!\n");
                continue;
            }

            if (mapa[idxAtacante].tropas <= 1) {
                printf("Atacante precisa de pelo menos 2 tropas para atacar!\n");
                continue;
            }

            // Realizar ataque
            printf("\n=== BATALHA ===\n");
            printf("%s (%s) ataca &s\n",
                mapa[idxAtacante].nome, mapa[idxAtacante].cor,
                mapa[idxDefensor].nome, mapa[idxDefensor].cor);

            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

            // Exibir resultado
            exibirMapa(mapa, quantidade);

            // Verificar se a missão foi cumprida
            if (verificarMissao(missaoJogador, mapa, quantidade)) {
                printf("\n PARABENES! Voce cumpriu sua missao: %s\n", missaoJogador);
                printf(" VITORIA DO JOGADOR!\n");
                break;
            }

            
        }
    
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
