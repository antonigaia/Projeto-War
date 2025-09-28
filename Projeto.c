#include <stdio.h>
#include <string.h>

//Variáveis Globais
#define MAX_TERRITORIO 5

struct Territorio{
    char nome [30];
    char cor [10];
    int tropas;
    
};
int main(){
    struct Territorio territorios[MAX_TERRITORIO];  

//Inserindo dados dos 5 territorios um por um
    for(int i=0; i<MAX_TERRITORIO; i++){
        printf("---------------------------\n");
        printf("Digite o nome do territorio %d: ", i+1);
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; // Remover o '\n'

        printf("Digite a cor do territorio %d: ", i+1);
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0; // Remover o '\n'

        printf("Digite a quantidade de tropas do territorio %d: ", i+1);
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpar o buffer de entrada
        
    }
//Exibindo os dados dos territorios
    printf("\nDados dos territorios:\n");
    for(int i=0; i<MAX_TERRITORIO; i++){
        printf("---------------------------\n");
        printf("Territorio %d-\n", i+1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n\n", territorios[i].tropas);
        
    }

    return 0;
}