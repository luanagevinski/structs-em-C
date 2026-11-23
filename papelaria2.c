#include <stdio.h>

#define MAX 15

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

int buscarPorCodigo(Produto lista[], int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrar(Produto lista[], int *qtd) {
    if (*qtd >= MAX) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    int codigo;
    printf("Codigo: ");
    scanf("%d", &codigo);

    if (buscarPorCodigo(lista, *qtd, codigo) != -1) {
        printf("Codigo ja cadastrado!\n");
        return;
    }

    lista[*qtd].codigo = codigo;
    printf("Nome: ");
    scanf(" %49[^\n]", lista[*qtd].nome);
    printf("Preco: ");
    scanf("%f", &lista[*qtd].preco);
    printf("Quantidade em estoque: ");
    scanf("%d", &lista[*qtd].estoque);

    (*qtd)++;
    printf("Produto cadastrado!\n");
}

void mostrarProduto(Produto p) {
    printf("Codigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Preco: %.2f\n", p.preco);
    printf("Quantidade em estoque: %d\n", p.estoque);
}

void  listar(Produto lista[], int qtd){
    if(qtd == 0){
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for(int i = 0; i < qtd; i++){
        mostrarProduto(lista[i]);
    }
}

void repor(Produto *p, int quantidade) {
    p->estoque += quantidade;
}

int vender(Produto *p, int quantidade) {
    if (quantidade > p->estoque) {
        return 0;
    }
    p->estoque -= quantidade;
    return 1;
}

float valorTotalEstoque(Produto lista[], int qtd) {
  float precoTotal = 0.0;
    if(qtd == 0){
        return precoTotal;
    }
    for (int i = 0; i < qtd; i++) {
        precoTotal += lista[i].preco * lista[i].estoque;
    }
    return precoTotal;
}

int maiorValorEstoque(Produto lista[], int qtd) {
    if (qtd == 0) {
        return -1;
    }
    int maiorIndice = 0;
    for (int i = 1; i < qtd; i++) {
        if (lista[i].preco * lista[i].estoque > lista[maiorIndice].preco * lista[maiorIndice].estoque) {
            maiorIndice = i;
        }
    }
    return maiorIndice;
}

int main() {
    Produto lista[MAX];
    int qtd = 0;
    int opcao, codigo, quantidade, pos;

    do {
        printf("\n===== PAPELARIA =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Repor estoque\n");
        printf("4 - Registrar venda\n");
        printf("5 - Consultar por codigo\n");
        printf("6 - Valor total e maior valor em estoque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(lista, &qtd);
                break;

            case 2:
                listar(lista, qtd);
                break;

            case 3:
            case 4:
            case 5:
                printf("Codigo do produto: ");
                scanf("%d", &codigo);
                pos = buscarPorCodigo(lista, qtd, codigo);
                if (pos == -1) {
                    printf("Produto nao encontrado.\n");
                    break;
                }

                if (opcao == 5) {
                    mostrarProduto(lista[pos]);
                    break;
                }

                printf("Quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade <= 0) {
                    printf("Quantidade invalida.\n");
                    break;
                }

                if (opcao == 3) {
                    repor(&lista[pos], quantidade);
                    printf("Estoque atualizado!\n");
                } else if (vender(&lista[pos], quantidade)) {
                    printf("Venda registrada!\n");
                } else {
                    printf("Estoque insuficiente! Disponivel: %d\n",
                           lista[pos].estoque);
                }
                break;

            case 6:
                if (qtd == 0) {
                    printf("Nenhum produto cadastrado.\n");
                    break;
                }
                printf("Valor total em estoque: R$ %.2f\n",
                       valorTotalEstoque(lista, qtd));
                pos = maiorValorEstoque(lista, qtd);
                if (pos != -1) {
                    printf("Maior valor em estoque: %s (R$ %.2f)\n",
                           lista[pos].nome,
                           lista[pos].preco * lista[pos].estoque);
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}


