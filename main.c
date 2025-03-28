// Sistema de Gerenciamento de Faturas

//-------------------------------------------------------
// Aluno: Vitor G. J. de Carvalho                       |
// RGM: 33046794                                        |
// Disciplina: Estruturas de Dados avancadas            |
// Professor: Marcelo T. Uemura                         |
// Data: 27/03/2025                                     |
//-------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma fatura
typedef struct Fatura {
    int numero;                  // Número da fatura
    char dataVencimento[11];     // Data de vencimento (formato: DD/MM/AAAA)
    float valor;                 // Valor da fatura
    char status[10];             // Status: "pendente" ou "paga"
    struct Fatura* esquerda;     // Ponteiro para o filho esquerdo
    struct Fatura* direita;      // Ponteiro para o filho direito
} Fatura;

// Função para criar uma nova fatura
Fatura* criarFatura(int numero, const char* dataVencimento, float valor, const char* status) {
    Fatura* novaFatura = (Fatura*)malloc(sizeof(Fatura));
    novaFatura->numero = numero;
    strcpy(novaFatura->dataVencimento, dataVencimento);
    novaFatura->valor = valor;
    strcpy(novaFatura->status, status);
    novaFatura->esquerda = NULL;
    novaFatura->direita = NULL;
    return novaFatura;
}

// Função para inserir uma fatura na árvore
Fatura* inserirFatura(Fatura* raiz, Fatura* novaFatura) {
    if (raiz == NULL) {
        return novaFatura;
    }
    if (novaFatura->numero < raiz->numero) {
        raiz->esquerda = inserirFatura(raiz->esquerda, novaFatura);
    } else if (novaFatura->numero > raiz->numero) {
        raiz->direita = inserirFatura(raiz->direita, novaFatura);
    }
    return raiz;
}

// Função para exibir as faturas em ordem crescente
void exibirFaturas(Fatura* raiz) {
    if (raiz != NULL) {
        exibirFaturas(raiz->esquerda);
        printf("Número: %d\n Vencimento: %s\n Valor: %.2f\n Status: %s\n ---------------------\n",
               raiz->numero, raiz->dataVencimento, raiz->valor, raiz->status);
        exibirFaturas(raiz->direita);
    }
}

// Função para buscar uma fatura pelo número
Fatura* buscarFatura(Fatura* raiz, int numero) {
    if (raiz == NULL || raiz->numero == numero) {
        return raiz;
    }
    if (numero < raiz->numero) {
        return buscarFatura(raiz->esquerda, numero);
    }
    return buscarFatura(raiz->direita, numero);
}

// Função para atualizar o status de uma fatura
void atualizarStatus(Fatura* raiz, int numero, const char* novoStatus) {
    Fatura* fatura = buscarFatura(raiz, numero);
    if (fatura != NULL) {
        strcpy(fatura->status, novoStatus);
        printf("Status da fatura %d atualizado para %s.\n", numero, novoStatus);
    } else {
        printf("Fatura %d não encontrada.\n", numero);
    }
}

// Função auxiliar para encontrar o menor nó da árvor
Fatura* encontrarMinimo(Fatura* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Função par remover uma fatura da árvore
Fatura* removerFatura(Fatura* raiz, int numero) {
    if (raiz == NULL) {
        return NULL;
    }
    if (numero < raiz->numero) {
        raiz->esquerda = removerFatura(raiz->esquerda, numero);
    } else if (numero > raiz->numero) {
        raiz->direita = removerFatura(raiz->direita, numero);
    } else {
        //No sem filhos
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        // Nó com um filho
        if (raiz->esquerda == NULL) {
            Fatura* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Fatura* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // No com dois filhos
        Fatura* temp = encontrarMinimo(raiz->direita);
        raiz->numero = temp->numero;
        strcpy(raiz->dataVencimento, temp->dataVencimento);
        raiz->valor = temp->valor;
        strcpy(raiz->status, temp->status);
        raiz->direita = removerFatura(raiz->direita, temp->numero);
    }
    return raiz;
}

// ---------------------------------------------------------------------
// Trecho de codigo reaproveitado dos exercicios anteriores de arvores binarias

// Função para exibir a árvore binária graficamente
void exibirArvore(Fatura* raiz, int espaco) {
    if (raiz == NULL) {
        return;
    }

    // Define o número de espaços entre os níveis
    int incremento = 5;
    espaco += incremento;

    // Exibe o filho direito primeiro (mais à direita na árvore)
    exibirArvore(raiz->direita, espaco);

    // Imprime o nó atual após os espaços correspondentes ao nível
    printf("\n");
    for (int i = incremento; i < espaco; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->numero);

    // Exibe o filho esquerdo (mais à esquerda na árvore)
    exibirArvore(raiz->esquerda, espaco);
}
//----------------------------------------------------------------------

// Função principal
int main() {
    Fatura* raiz = NULL;
    int opcao, numero;
    char dataVencimento[11];
    float valor;
    char status[10];

    do {
        system("cls"); // Limpa a tela
        printf("--------------------------------------------------------\n");
        printf("|          Sistema de Gerenciamento de Faturas         |\n");
        printf("|                                                      |\n");
        printf("|1. Inserir fatura                                     |\n");
        printf("|2. Exibir faturas                                     |\n");  
        printf("|3. Buscar fatura                                      |\n");
        printf("|4. Atualizar status de fatura                         |\n");
        printf("|5. Remover fatura                                     |\n");
        printf("|6. Exibir árvore graficamente                         |\n");
        printf("|7. Sair                                               |\n");
        printf("--------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        system("cls"); // Limpa a tela antes de executar a operação

        switch (opcao) {
            case 1:
                printf("Digite o numero da fatura: ");
                scanf("%d", &numero);
                printf("Digite a data de vencimento (DD/MM/AAAA): ");
                scanf("%s", dataVencimento);
                printf("Digite o valor da fatura: ");
                scanf("%f", &valor);
                printf("Digite o status da fatura (pendente/paga): ");
                scanf("%s", status);
                raiz = inserirFatura(raiz, criarFatura(numero, dataVencimento, valor, status));
                printf("Fatura inserida com sucesso!\n");
                break;

            case 2:
                printf("Faturas cadastradas:\n");
                printf("--------------------\n");
                exibirFaturas(raiz);
                break;

            case 3:
                printf("Digite o numero da fatura para buscar: ");
                scanf("%d", &numero);
                Fatura* encontrada = buscarFatura(raiz, numero);
                if (encontrada != NULL) {
                    printf("Fatura encontrada: Numero: %d\n Vencimento: %s\n Valor: %.2f\n Status: %s\n",
                           encontrada->numero, encontrada->dataVencimento, encontrada->valor, encontrada->status);
                } else {
                    printf("Fatura nao encontrada.\n");
                }
                break;

            case 4:
                printf("Digite o numero da fatura para atualizar: ");
                scanf("%d", &numero);
                printf("Digite o novo status (pendente/paga): ");
                scanf("%s", status);
                atualizarStatus(raiz, numero, status);
                break;

            case 5:
                printf("Digite o numero da fatura para remover: ");
                scanf("%d", &numero);
                raiz = removerFatura(raiz, numero);
                printf("Fatura removida com sucesso!\n");
                break;
                
            case 6:
                printf("Exibindo a árvore binária:\n");
                exibirArvore(raiz, 0);
                break;

            case 7:
                printf("Saindo do sistema...\n");
                break;


            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if (opcao != 7) {
            printf("\nPressione qualquer tecla para continuar...");
            getchar(); // Aguarda o usuário pressionar uma tecla
            getchar(); // Para capturar o Enter
        }

    } while (opcao != 7);

    return 0;
}