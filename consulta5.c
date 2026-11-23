#include <stdio.h>

#define MAX_PACIENTES 15
#define MAX_CONSULTAS 30

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int codigo;
    char nome[50];
    int idade;
} Paciente;

typedef struct {
    Paciente paciente;    
    Data data;             
    char descricao[100];
} Consulta;

int buscarPaciente(Paciente lista[], int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarPaciente(Paciente lista[], int *qtd) {
    if (*qtd >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido.\n");
        return;
    }

    int codigo;
    printf("Codigo: ");
    scanf("%d", &codigo);

    if (buscarPaciente(lista, *qtd, codigo) != -1) {
        printf("Codigo ja cadastrado!\n");
        return;
    }

    lista[*qtd].codigo = codigo;
    printf("Nome: ");
    scanf(" %49[^\n]", lista[*qtd].nome);
    printf("Idade: ");
    scanf("%d", &lista[*qtd].idade);

    (*qtd)++;
    printf("Paciente cadastrado!\n");
}

void listarPacientes(Paciente lista[], int qtd) {
    if (qtd == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s - %d anos\n", lista[i].codigo, lista[i].nome, lista[i].idade);
    }
}

int lerData(Data *d) {
    printf("Data (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);

    if (d->dia < 1 || d->dia > 31 || d->mes < 1 || d->mes > 12 || d->ano < 1900) {
        return 0;
    }
    return 1;
}

int mesmaData(Data a, Data b) {
    return a.dia == b.dia && a.mes == b.mes && a.ano == b.ano;
}

void mostrarConsulta(Consulta c) {
    printf("%02d/%02d/%04d - %s: %s\n",
           c.data.dia, c.data.mes, c.data.ano, c.paciente.nome, c.descricao);
}

void registrarConsulta(Paciente pacientes[], int qtdPacientes, Consulta consultas[], int *qtdConsultas) {
    if (*qtdConsultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido.\n");
        return;
    }

    int codigo;
    printf("Codigo do paciente: ");
    scanf("%d", &codigo);

    int pos = buscarPaciente(pacientes, qtdPacientes, codigo);
    if (pos == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    Data d;
    if (!lerData(&d)) {
        printf("Data invalida.\n");
        return;
    }

    consultas[*qtdConsultas].paciente = pacientes[pos];  
    consultas[*qtdConsultas].data = d;                    
    printf("Descricao do atendimento: ");
    scanf(" %99[^\n]", consultas[*qtdConsultas].descricao);

    (*qtdConsultas)++;
    printf("Consulta registrada!\n");
}

void consultasDoPaciente(Consulta consultas[], int qtd, int codigo) {
    int achou = 0;
    for (int i = 0; i < qtd; i++) {
        if (consultas[i].paciente.codigo == codigo) {
            mostrarConsulta(consultas[i]);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhuma consulta para esse paciente.\n");
    }
}

void consultasPorData(Consulta consultas[], int qtd, Data d) {
    int achou = 0;
    for (int i = 0; i < qtd; i++) {
        if (mesmaData(consultas[i].data, d)) {
            mostrarConsulta(consultas[i]);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhuma consulta nessa data.\n");
    }
}

int contarConsultas(Consulta consultas[], int qtd, int codigo) {
    int contador = 0;
    for (int i = 0; i < qtd; i++) {
        if (consultas[i].paciente.codigo == codigo) {
            contador++;
        }
    }
    return contador;
}

int pacienteMaisAtendido(Paciente pacientes[], int qtdPacientes, Consulta consultas[], int qtdConsultas) {
    if (qtdConsultas == 0) {
        return -1;
    }
    int indice = 0;
    for (int i = 1; i < qtdPacientes; i++) {
        if (contarConsultas(consultas, qtdConsultas, pacientes[i].codigo) >
            contarConsultas(consultas, qtdConsultas, pacientes[indice].codigo)) {
            indice = i;
        }
    }
    return indice;
}

int main() {
    Paciente pacientes[MAX_PACIENTES];
    Consulta consultas[MAX_CONSULTAS];
    int qtdPacientes = 0, qtdConsultas = 0;
    int opcao, codigo;
    Data d;

    do {
        printf("\n===== CLINICA =====\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Listar pacientes\n");
        printf("3 - Registrar consulta\n");
        printf("4 - Consultas de um paciente\n");
        printf("5 - Consultas em uma data\n");
        printf("6 - Consultas por paciente e mais atendido\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPaciente(pacientes, &qtdPacientes);
                break;
            case 2:
                listarPacientes(pacientes, qtdPacientes);
                break;
            case 3:
                registrarConsulta(pacientes, qtdPacientes, consultas, &qtdConsultas);
                break;
            case 4:
                printf("Codigo do paciente: ");
                scanf("%d", &codigo);
                consultasDoPaciente(consultas, qtdConsultas, codigo);
                break;
            case 5:
                if (lerData(&d)) {
                    consultasPorData(consultas, qtdConsultas, d);
                } else {
                    printf("Data invalida.\n");
                }
                break;
            case 6: {
                if (qtdPacientes == 0) {
                    printf("Nenhum paciente cadastrado.\n");
                    break;
                }
                for (int i = 0; i < qtdPacientes; i++) {
                    printf("%s: %d consulta(s)\n", pacientes[i].nome,
                           contarConsultas(consultas, qtdConsultas, pacientes[i].codigo));
                }
                int pos = pacienteMaisAtendido(pacientes, qtdPacientes, consultas, qtdConsultas);
                if (pos == -1) {
                    printf("Nenhuma consulta registrada.\n");
                } else {
                    printf("Paciente com mais atendimentos: %s\n", pacientes[pos].nome);
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
