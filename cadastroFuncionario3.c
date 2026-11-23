#include <stdio.h>

#define MAX 8
#define HORAS_MES 160

typedef struct {
    int codigo;
    char nome[50];
    char cargo[30];
    float salarioBase;
    int horasExtras;
    float salarioBruto;
    float desconto;
    float salarioLiquido;
} Funcionario;

float valorHora(float salarioBase) {
    return salarioBase / 160;
}

float valorHorasExtras(Funcionario f) {
    return f.horasExtras * valorHora(f.salarioBase) * 1.5;
}

void calcularSalario(Funcionario *f) {
    f->salarioBruto = f->salarioBase + valorHorasExtras(*f);
    f->desconto = f->salarioBruto * 0.1;
    f->salarioLiquido = f->salarioBruto - f->desconto;  
}

void cadastrar(Funcionario *f) {
    printf("Codigo: ");
    scanf("%d", &f->codigo);
    printf("Nome: ");
    scanf(" %49[^\n]", f->nome);
    printf("Cargo: ");
    scanf(" %29[^\n]", f->cargo);
    printf("Salario base: ");
    scanf("%f", &f->salarioBase);
    printf("Horas extras: ");
    scanf("%d", &f->horasExtras);

    calcularSalario(f);
}

void mostrar(Funcionario f) {
    printf("Código: %d\n", f.codigo);
    printf("Nome: %s\n", f.nome);
    printf("Cargo: %s\n", f.cargo);
    printf("   Base: R$ %.2f | Extras: R$ %.2f\n", f.salarioBase, valorHorasExtras(f));
    printf("   Bruto: R$ %.2f | Desconto: R$ %.2f | LIQUIDO: R$ %.2f\n", f.salarioBruto, f.desconto, f.salarioLiquido);
}

int maiorLiquido(Funcionario lista[], int qtd) {
    if (qtd == 0) {
        return -1;
    }
    int indice = 0;
    for (int i = 1; i < qtd; i++) {
        if (lista[i].salarioLiquido > lista[indice].salarioLiquido) {
            indice = i;
        }
    }
    return indice;
}

float custoFolha(Funcionario lista[], int qtd) {
    float total = 0;
    for (int i = 0; i < qtd; i++) {
        total += lista[i].salarioBruto;
    }
    return total;
}

int main() {
    Funcionario lista[MAX];
    int qtd;

    do {
        printf("Quantos funcionarios (1 a %d)? ", MAX);
        scanf("%d", &qtd);
    } while (qtd < 1 || qtd > MAX);

    for (int i = 0; i < qtd; i++) {
        printf("\n--- Funcionario %d ---\n", i + 1);
        cadastrar(&lista[i]);
    }

    printf("\n===== FOLHA DE PAGAMENTO =====\n");
    for (int i = 0; i < qtd; i++) {
        mostrar(lista[i]);
    }

    int pos = maiorLiquido(lista, qtd);
    if (pos != -1) {
        printf("\nMaior salario liquido: %s (R$ %.2f)\n",
               lista[pos].nome, lista[pos].salarioLiquido);
    }
    printf("Custo total da folha: R$ %.2f\n", custoFolha(lista, qtd));

    return 0;
}
