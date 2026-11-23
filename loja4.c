#include <stdio.h>

#define MAX_PRODUTOS 10
#define MAX_VENDAS 20

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int estoque;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
    float valorTotal;
} Venda;

int buscarProduto(Produto lista[], int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto(Produto lista[], int *qtd) {
    if (*qtd >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    int codigo;
    printf("Codigo: ");
    scanf("%d", &codigo);

    if (buscarProduto(lista, *qtd, codigo) != -1) {
        printf("Codigo ja cadastrado!\n");
        return;
    }

    lista[*qtd].codigo = codigo;
    printf("Nome: ");
    scanf(" %49[^\n]", lista[*qtd].nome);
    printf("Preco: ");
    scanf("%f", &lista[*qtd].preco);
    printf("Estoque: ");
    scanf("%d", &lista[*qtd].estoque);

    (*qtd)++;
    printf("Produto cadastrado!\n");
}

void listarProdutos(Produto lista[], int qtd) {
    if (qtd == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("Codigo: %d\n", lista[i].codigo);
        printf("Nome: %s\n", lista[i].nome);
        printf("Preco: %.2f\n", lista[i].preco);
        printf("Estoque: %d\n", lista[i].estoque);
    }
}

void baixarEstoque(Produto *p, int quantidade) {
    p->estoque -= quantidade;
}

void registrarVenda(Produto produtos[], int qtdProdutos, Venda vendas[], int *qtdVendas) {
    if (*qtdVendas >= MAX_VENDAS) {
        printf("Limite de vendas atingido.\n");
        return;
    }

    int codigo, quantidade;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    int pos = buscarProduto(produtos, qtdProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida.\n");
        return;
    }
    if (quantidade > produtos[pos].estoque) {
        printf("Estoque insuficiente! Disponivel: %d\n", produtos[pos].estoque);
        return;
    }

    baixarEstoque(&produtos[pos], quantidade);

    vendas[*qtdVendas].produto = produtos[pos];
    vendas[*qtdVendas].quantidade = quantidade;
    vendas[*qtdVendas].valorTotal = quantidade * produtos[pos].preco;

    printf("Venda registrada! Total: R$ %.2f\n", vendas[*qtdVendas].valorTotal);
    (*qtdVendas)++;
}

void listarVendas(Venda vendas[], int qtd) {
    if (qtd == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("Venda %d: %s - %d un. - R$ %.2f\n",
               i + 1, vendas[i].produto.nome, vendas[i].quantidade, vendas[i].valorTotal);
    }
}

float faturamentoTotal(Venda vendas[], int qtd) {
    float total = 0;
    for (int i = 0; i < qtd; i++) {
        total += vendas[i].valorTotal;
    }
    return total;
}

float faturamentoProduto(Venda vendas[], int qtdVendas, int codigo) {
    float total = 0;
    for (int i = 0; i < qtdVendas; i++) {
        if (vendas[i].produto.codigo == codigo) {
            total += vendas[i].valorTotal;
        }
    }
    return total;
}

int produtoMaiorFaturamento(Produto produtos[], int qtdProdutos, Venda vendas[], int qtdVendas) {
    if (qtdVendas == 0) {
        return -1;
    }
    int indice = 0;
    for (int i = 1; i < qtdProdutos; i++) {
        if (faturamentoProduto(vendas, qtdVendas, produtos[i].codigo) >
            faturamentoProduto(vendas, qtdVendas, produtos[indice].codigo)) {
            indice = i;
        }
    }
    return indice;
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    Venda vendas[MAX_VENDAS];
    int qtdProdutos = 0, qtdVendas = 0;
    int opcao;

    do {
        printf("\n===== LOJA =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Registrar venda\n");
        printf("4 - Listar vendas\n");
        printf("5 - Faturamento\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &qtdProdutos);
                break;
            case 2:
                listarProdutos(produtos, qtdProdutos);
                break;
            case 3:
                registrarVenda(produtos, qtdProdutos, vendas, &qtdVendas);
                break;
            case 4:
                listarVendas(vendas, qtdVendas);
                break;
            case 5: {
                printf("Faturamento total: R$ %.2f\n", faturamentoTotal(vendas, qtdVendas));
                int pos = produtoMaiorFaturamento(produtos, qtdProdutos, vendas, qtdVendas);
                if (pos == -1) {
                    printf("Nenhuma venda registrada.\n");
                } else {
                    printf("Produto com maior faturamento: %s (R$ %.2f)\n",
                           produtos[pos].nome,
                           faturamentoProduto(vendas, qtdVendas, produtos[pos].codigo));
                }
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
