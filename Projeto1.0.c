#include <stdio.h>
#include <stdlib.h> // Para alocação de memória (malloc, free) e rand()
#include <string.h> // Para funções de string (strcpy)
#include <time.h>   // Para inicializar a semente do gerador aleatório (srand)

// Struct atualizada
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Protótipos das Funções ---
void inserirTerritorios(struct Territorio* mapa, int total);
void exibirTerritorios(struct Territorio* mapa, int total);
void menuAtaque(struct Territorio* mapa, int total);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
void limparBuffer();

// --- Função Principal ---
int main() {
    struct Territorio* territorios = NULL; // Ponteiro para o vetor dinâmico
    int numTerritorios = 0;
    char opcao;

    // Inicializa a semente para o gerador de números aleatórios
    srand(time(NULL));

    // Pede ao usuário o número total de territórios
    printf("Digite o numero total de territorios para o mapa: ");
    scanf("%d", &numTerritorios);
    limparBuffer();

    // Validação de entrada
    if (numTerritorios <= 1) {
        printf("Erro: E necessario ter pelo menos 2 territorios para jogar.\n");
        return 1; // Termina o programa com erro
    }

    // Alocação de memória dinâmica com calloc (inicializa a memória com zeros)
    territorios = (struct Territorio*) calloc(numTerritorios, sizeof(struct Territorio));

    // Verifica se a alocação de memória foi bem-sucedida
    if (territorios == NULL) {
        printf("Erro fatal: Falha ao alocar memoria para os territorios!\n");
        return 1; // Termina o programa com erro
    }

    // Menu principal
    do {
        printf("\n========= MENU WAR =========\n");
        printf("1. Inserir/Editar dados dos territorios\n");
        printf("2. Exibir mapa\n");
        printf("3. Atacar\n");
        printf("S. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);
        limparBuffer();

        switch (opcao) {
            case '1':
                inserirTerritorios(territorios, numTerritorios);
                break;
            case '2':
                exibirTerritorios(territorios, numTerritorios);
                break;
            case '3':
                menuAtaque(territorios, numTerritorios);
                break;
            case 's':
            case 'S':
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if (opcao != 's' && opcao != 'S') {
             printf("\nPressione Enter para continuar...");
             getchar();
        }

    } while (opcao != 's' && opcao != 'S');

    // Libera a memória alocada antes de encerrar o programa
    liberarMemoria(territorios);

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Preenche os dados de todos os territórios.
 */
void inserirTerritorios(struct Territorio* mapa, int total) {
    printf("\n--- Inserindo Dados dos Territorios ---\n");
    for (int i = 0; i < total; i++) {
        printf("---------------------------\n");
        printf("Digite o nome do territorio %d: ", i + 1);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Digite a cor do territorio %d: ", i + 1);
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Digite a quantidade de tropas do territorio %d: ", i + 1);
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
}

/**
 * @brief Exibe os dados de todos os territórios.
 */
void exibirTerritorios(struct Territorio* mapa, int total) {
    printf("\n--- Situacao Atual do Mapa ---\n");
    for (int i = 0; i < total; i++) {
        printf("---------------------------\n");
        printf("Territorio %d\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
}

/**
 * @brief Gerencia a seleção do atacante e defensor pelo usuário.
 */
void menuAtaque(struct Territorio* mapa, int total) {
    int idxAtacante, idxDefensor;

    exibirTerritorios(mapa, total);
    printf("---------------------------\n");
    printf("Escolha os territorios para a batalha:\n");

    printf("Digite o numero do territorio ATACANTE (1 a %d): ", total);
    scanf("%d", &idxAtacante);
    limparBuffer();

    printf("Digite o numero do territorio DEFENSOR (1 a %d): ", total);
    scanf("%d", &idxDefensor);
    limparBuffer();

    // Validações
    if (idxAtacante < 1 || idxAtacante > total || idxDefensor < 1 || idxDefensor > total) {
        printf("\nErro: Numero de territorio invalido.\n");
        return;
    }
    if (idxAtacante == idxDefensor) {
        printf("\nErro: Um territorio nao pode atacar a si mesmo.\n");
        return;
    }
    if (mapa[idxAtacante - 1].tropas < 2) {
        printf("\nErro: O territorio atacante precisa ter pelo menos 2 tropas para atacar.\n");
        return;
    }

    // Chama a função de ataque passando os endereços dos territórios corretos
    atacar(&mapa[idxAtacante - 1], &mapa[idxDefensor - 1]);
}

/**
 * @brief Simula o combate entre dois territórios usando dados.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtaque = (rand() % 6) + 1; // Gera número de 1 a 6
    int dadoDefesa = (rand() % 6) + 1; // Gera número de 1 a 6

    printf("\n--- BATALHA ---\n");
    printf("%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado do Ataque: %d\n", dadoAtaque);
    printf("Dado da Defesa: %d\n", dadoDefesa);
    printf("---------------\n");

    // O atacante vence se o dado for maior
    if (dadoAtaque > dadoDefesa) {
        printf("VITORIA DO ATACANTE!\n");
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);

        // Transfere a cor
        strcpy(defensor->cor, atacante->cor);

        // Transfere metade das tropas do atacante
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;

    } else { // Empate ou vitória do defensor
        printf("VITORIA DO DEFENSOR!\n");
        printf("%s defendeu o ataque com sucesso!\n", defensor->nome);

        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("%s perdeu 1 tropa na batalha.\n", atacante->nome);
        }
    }
}

/**
 * @brief Libera a memória alocada para o mapa de territórios.
 * @param mapa Ponteiro para o vetor de territórios.
 */
void liberarMemoria(struct Territorio* mapa) {
    printf("\nLiberando memoria alocada...\n");
    free(mapa); // Libera o bloco de memória
    mapa = NULL; // Boa prática: aponta o ponteiro para NULL após liberar
}

/**
 * @brief Limpa o buffer de entrada do teclado.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}