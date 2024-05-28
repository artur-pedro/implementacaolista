#include "sll.c"
#include <math.h>
typedef struct {
    char marca[30];
    int codigoNumerico;
    float valor;
} pacotedCafe;
int emptyList(Sllist *l){ 
    if(l != NULL){
        pacotedCafe *aux;
        while(aux != NULL){
            aux = (pacotedCafe*) sllRemovelast(l);
        } 
        return TRUE;
    }
    return FALSE;
}
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int telainicial();
Sllist *lista = NULL;
int compChar(void *key, void *pacote) {
    pacotedCafe *g = (pacotedCafe*) pacote;
    char *key_marca = (char*) key;
    if(key != NULL && pacote != NULL) {
        if(strcmp(key_marca, g->marca) == 0){
            return TRUE;
        }
    }
    return FALSE;
}
int compint(void *key, void *pacote) {
    pacotedCafe *g = (pacotedCafe*) pacote;
    int *key_codigoNumerico = (int*) key;
    if(key != NULL && pacote != NULL) {
        if(*key_codigoNumerico == g->codigoNumerico){
            return TRUE;
        }
    }
    return FALSE;
}
int compFloat(void *key, void *pacote) {
    pacotedCafe *g = (pacotedCafe*) pacote;
    float *key_valor = (float*) key;
    if(key != NULL && pacote != NULL) {
        if(*key_valor == g->valor){
            return TRUE;
        }
    }
    return FALSE;
}
int main() {
    do {
        int opcao2 = telainicial();
        switch (opcao2) {  
            case 1: {
                if (lista != NULL) {
                printf("Erro: lista ja foi inicializada.\n");
                break;
                } 
                if(((lista = sllCreate()) != NULL)) {
                    printf("Lista criada com sucesso!!!\n");
                }
                else {
                    printf("Nao foi possivel criar a lista!!\n");
                }
                break;
            }
            case 2: {
            if (lista == NULL) {
                printf("Erro: lista nao inicializada.\n");
                break;
            }
            pacotedCafe *novoCafe;
            novoCafe = (pacotedCafe*)malloc(sizeof(pacotedCafe));
            printf("Digite a marca: \n");
            scanf("%s", novoCafe->marca);
            printf("Digite o codigo numerico: \n");
            if (scanf("%d", &(novoCafe->codigoNumerico)) != 1) {
                printf("Opcao invalida. Este item nao sera adicionado.\n");
                limparBuffer();// Limpar o buffer de entrada
                break;
                }   
            novoCafe->codigoNumerico = abs(novoCafe->codigoNumerico);
            printf("Digite o valor em reais: \n");
            if(scanf("%f", &(novoCafe->valor)) != 1) {
                printf("Opcao invalida. Tente novamente.\n");
                limparBuffer();
                break; // Limpar o buffer de entrada
            }
            novoCafe->valor = fabs(novoCafe->valor);
            sllInsertAsLast(lista, (void*)novoCafe);
            break;
            }
            case 3: {
                if (lista == NULL) {
                    printf("Erro: lista nao inicializada.\n");
                    break;
                }
                int opcao = 0;
                printf("1 - para remover pela marca\n");
                printf("2 - para remover pelo codigo numerico\n");
                printf("3 - para remover pelo codigo valor\n");
                if (scanf("%d", &opcao) != 1) {
                printf("Opcao invalida. Tente novamente.\n");
                limparBuffer(); // Limpar o buffer de entrada
            }
                switch (opcao) {
                    case 1: {
                        char marca[30];
                        printf("Digite a marca do pacote a ser removido: \n");
                        scanf("%s", marca);
                        pacotedCafe *pacoteRemovido = (pacotedCafe *)sllRemoveSpec(lista, marca, compChar);
                        if (pacoteRemovido != NULL) {
                            printf("Pacote com a marca %s removido com sucesso.\n", marca);
                            free(pacoteRemovido); 
                        }
                        else {
                            printf("Pacote com a marca %s nao encontrado na lista.\n", marca);
                        }
                        break;
                    }
                    case 2: {
                        int codigo = 0;
                        printf("Digite o codigo numerico do pacote a ser removido: \n");
                        if (scanf("%d", &codigo) != 1) {
                            printf("Opcao invalida. Tente novamente.\n");
                            limparBuffer(); // Limpar o buffer de entrada
                        }
                        pacotedCafe *pacoteRemovido = (pacotedCafe *)sllRemoveSpec(lista, &codigo, compint);
                        if (pacoteRemovido != NULL) {
                             printf("Pacote com o codigo numerico %d removido com sucesso.\n", codigo);
                             free(pacoteRemovido); 
                        }
                        else {
                            printf("Pacote com o codigo numerico %d nao encontrado na lista.\n", codigo);
                        }
                        break;
                    }
                    case 3: {
                        float codigo = 0;
                        printf("Digite o valor do pacote a ser removido: \n");
                        if (scanf("%f", &codigo) != 1) {
                            printf("Opcao invalida. Tente novamente.\n");
                            limparBuffer(); // Limpar o buffer de entrada
                        }
                        pacotedCafe *pacoteRemovido = (pacotedCafe *)sllRemoveSpec(lista, &codigo, compFloat);
                        if (pacoteRemovido != NULL) {
                             printf("Pacote com o codigo numerico %.2f removido com sucesso.\n", codigo);
                             free(pacoteRemovido); 
                        }
                        else {
                            printf("Pacote com o codigo numerico %.2f nao encontrado na lista.\n", codigo);
                        }
                        break;
                    }
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
                break;
            }
            case 4: {
                if (lista != NULL) {
                    printf("Pacotes de cafe na lista:\n");
                    pacotedCafe *pacote = sllGetfirst(lista);
                    int i = 1; 
                    while (pacote != NULL) {
                        printf("Pacote %d:\n", i);
                        printf("Marca: %s\n", pacote->marca);
                        printf("Codigo Numerico: %d\n", pacote->codigoNumerico);
                        printf("Valor: %.2f\n", pacote->valor);
                        pacote = sllGetnext(lista);
                        i++; 
                    }
                }
                else{
                    printf("lista nao inicializada!!!\n");
                }
                break;
            }
            case 5: {
                int opcao = 0;
                printf("1 - para pesquisar pela marca\n");
                printf("2 - para pesquisar pelo codigo numerico\n");
                printf("3 - para pesquisar pelo valor\n");
                if (scanf("%d", &opcao) != 1) {
                    printf("Opcao invalida. Tente novamente.\n");
                    limparBuffer(); // Limpar o buffer de entrada
                }
                switch (opcao) {
                    case 1: {
                        char marca[30];
                        printf("Digite a marca do pacote a ser pesquisado: \n");
                        scanf("%s", marca);
                        pacotedCafe *pacoteEncontrado = (pacotedCafe *)sllQuery(lista, marca, compChar);
                        if (pacoteEncontrado != NULL) {
                            printf("Pacote encontrado: %s\n", pacoteEncontrado->marca);
                            printf("Marca: %s\n", pacoteEncontrado->marca);
                            printf("Codigo Numerico: %d \n", pacoteEncontrado->codigoNumerico);
                            printf("Valor: %.2f \n", pacoteEncontrado->valor);
                        } else {
                            printf("Pacote com a marca %s nao encontrado na lista.\n", marca);
                        }
                        break;
                    }
                    case 2: {
                        int codigo = 0;
                        printf("Digite o codigo numerico do pacote a ser pesquisado: \n");
                        if (scanf("%d", &codigo) != 1) {
                            printf("Opcao invalida. Tente novamente.\n");
                            limparBuffer(); // Limpar o buffer de entrada
                        }
                        pacotedCafe *pacoteEncontrado = (pacotedCafe *)sllQuery(lista, &codigo, compint);
                        if (pacoteEncontrado != NULL) {
                            printf("Pacote encontrado com codigo numerico: %d\n", pacoteEncontrado->codigoNumerico);
                            printf("Marca: %s\n", pacoteEncontrado->marca);
                            printf("Codigo Numerico: %d \n", pacoteEncontrado->codigoNumerico);
                            printf("Valor: %.2f \n", pacoteEncontrado->valor);
                        } else {
                            printf("Pacote com o codigo numerico %d nao encontrado na lista.\n", codigo);
                        }
                        break;
                    }
                    case 3: {
                        float valor = 0.0;
                        printf("Digite o valor do pacote a ser pesquisado: \n");
                        if (scanf("%f", &valor) != 1) {
                            printf("Opcao invalida. Tente novamente.\n");
                            limparBuffer(); // Limpar o buffer de entrada
                        }
                        pacotedCafe *pacoteEncontrado = (pacotedCafe *)sllQuery(lista, &valor, compFloat);
                        if (pacoteEncontrado != NULL) {
                            printf("Pacote encontrado com valor: %.2f\n", pacoteEncontrado->valor);
                            printf("Marca: %s\n", pacoteEncontrado->marca);
                            printf("Codigo Numerico: %d \n", pacoteEncontrado->codigoNumerico);
                            printf("Valor: %.2f \n", pacoteEncontrado->valor);
                        } else {
                            printf("Pacote com o valor %.2f nao encontrado na lista.\n", valor);
                        }
                        break;
                    }
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
                break;
            }

            case 6: {
                if (sllDestroy(lista)) {
                    printf("A lista foi destruida\n"); 
                    lista =NULL;
                }
                else {
                    printf("lista nao destruida\n");
                }
                break;
            }
            case 7: {
                if (lista == NULL) {
                    printf("Erro: lista nao inicializada.\n");
                    break;
            }           
                emptyList(lista);
                printf("lista esvaziada: \n");
                break;
            }

            case 8: {
                printf("Saindo do programa...\n");
                exit(1);
            }
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (1);
}
int telainicial() {
    int opcao = 0;
    printf("---------------- Bem vindo a lista que armazena pacotes de cafe ----------------\n");
    printf("Digite 1 - para criar uma lista\n");
    printf("Digite 2 - para inserir pacotes de cafes na lista\n");
    printf("Digite 3 - para remover algum pacote de cafe da lista\n");
    printf("Digite 4 - para listar os pacotes de cafe da lista\n");
    printf("Digite 5 - para consultar algum pacote de cafe da lista\n");
    printf("Digite 6 - para para destruir a lista\n");
    printf("Digite 7 - para para esvaziar a lista\n");
    printf("Digite 8 - para sair\n");
    if(scanf("%d", &opcao)!=1) {
        printf("Opcao invalida. Tente novamente.\n");
        limparBuffer(); // Limpar o buffer de entrada'
                        }
    return opcao;
}