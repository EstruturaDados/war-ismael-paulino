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

            // Verificar se deseja continuar
            printf("\nDeseja realizar outro ataque? (1-Sim, 0-Não: ");
            scanf("%d", &continuar);
            limparBuffer();

            turno++;
        }

        // Liberar memória
        free(missaoJogador);
        liberarMemoria(mapa);
        printf("\nJogo finalizad. Memoria liberada.\n");

    return 0;
}

    // Função para atribuir missão aleatória
    void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
        int indiceAleatorio = rand() % totalMissoes;
        strcpy(destino, missoes[indiceAleatorio]);
    }

    // Função para verificar se a missão foi cumprida
    int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
        //Lógica simples de verificação para cada tipo de missão
        if (strsr(missao, "Conquistar 3 territorios seguidos")) {
            // Verificar se há 3 territórios da mesma cor em sequência
            for (int i =0; i < tamanho - 2; i++) {
                if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0 &&
                    strcmp(mapa[i+1].cor, mapa[i+2].cor) == 0) {
                    return 1;
                }
            }
        }
        else if (strtr(missao, "Eliminar todas as tropas da cor vermelha")) {
            // Verificar se não há mais tropas vermelhas
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i];cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                    return 0;
                }
            }
            return 1;
        }
        else if (strtr(missao, "Controlar pelo menos 5 territorios")) {
            // Conta territórios controlados pelo jogador (assumindo cor "azul")
            int count = 0
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, "azul") == 0) {
                    count++;
                }
            }
            return count >=5;
        }
        else if (strstr(missao, "Destruir todas as tropas inimigas")) {
            // Verificar se todas as tropas são jogador (assumindo cor "azul")
            for (int i = 0; i < tamanho; i++) {
                if (strcmp(mapa[i].cor, "azul") != 0 && mapa [i].tropas > 0)
                }
            }
            return 1;
    
        }
        else if (strstr(missao, "Manter 10 tropas em seu territorio principal")) {
            // Verificar se o primeiro território tem pelo menos 10 tropas
            return (mapa[0].tropas >= 10);
        }

        return 0;
    }
    
    // Função para exibir a missão
    void exibirMissao(char* missao) {
        printf("Sua missao: %s\n", missao);
    }

    // Função para cadastrar territórios
    Territorio* cadastrarTerritorios(int quantidade) {
        Territorio* mapa = (Territorio*)calloc(quantidade, sizeof(Territorio));
        inf (mapa == NULL) return NULL;
    
        prinf("Territorio %d\n", i + 1);
    
        // Nome do território
        printf(" Nome: ");
        fhets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
    
        // Número de tropas
        printf(" Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();

        printf("\n");
    }
    return mapa;
}

// Função para exibir o mapa
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n=== MAPA ATUAL ===\n");
    printf("===========================================\n");
    printf("%-20s %-10s %-10s\n", "TERRITORIO", "COR", "TROPAS");
    printf("===========================================\n");

    for (int i = 0 < quantidade; i++) {
        printf("%-20s %-10s %-10d\n",
            mapa[i].nome,
            mapa[i].cor,
            mapa[i].tropas);
    }

    printf ("==========================================\n");
}

// Função de ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simulaçã de dados de batalha
    int dadoAtacante = (radn() % 6) + 1; // Dado de 1 a 6
    int dadoDefensor = (rand() % 6) + 1; // Dado de 1 a 6

    printf("Dado do atacant:> %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("VITORIA do atacante!\n");

        // Conquista do território
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // Recebe metade das tropas do atacante
        atacante->tropas -= atacante->tropas / 2; // Atacante perder metada das tropas

        printf("%s conquistou %s"\n", atacante->nome, defensor->nome);
    }
    else if (dadoAtacante < dadoDefensor) {
        // Defensor vence
        printf("VITORIA do defensor!\n");

        // Atacante perde 1 tropa
        atacante->tropas--;;
        printf("Atacante perdeu 1 tropa.\n").

    }
    
    else {
        // Empate
        printf("EMPATE! Nenhuma mudanca.\n");
    }

}

// Função para liberar memória
void liberarMemora(Territori* mapa) {
    free(mapa);
}

// Função para limpas o buffer de entrada
voide limpasBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c !=EOF);
}
