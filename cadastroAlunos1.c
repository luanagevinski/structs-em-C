#include <stdio.h>
#define MAX 10

typedef struct{
    char nome[50];
    int matricula;
    float nota1;
    float nota2;
    float media;
} Aluno;

void calcularMedia(Aluno *aluno){
    float soma = 0;
        soma = aluno->nota1 + aluno->nota2;
    
   aluno->media = soma / 2;
}

void cadastrar(Aluno *aluno, int *total){
        if(*total < MAX){
                    printf("----CADASTRAR ALUNO----\n");
                    printf("Digite sua matricula: \n");
                    scanf("%d", &aluno[*total].matricula);
                    printf("Digite o nome: \n");
                    scanf(" %49[^\n]", aluno[*total].nome);
                    printf("Digite sua nota 1: \n");
                    scanf("%f", &aluno[*total].nota1);
                    printf("Digite sua nota 2: \n");
                    scanf("%f", &aluno[*total].nota2);
                printf("Aluno cadastrado com sucesso!\n");
                calcularMedia(&aluno[*total]);
                (*total)++;
                

            } else{
            printf("Chegou ao limite.\n");
            }
    }



float mediaTurma(Aluno turma[], int qtd){
    float soma = 0;

    if(qtd == 0){
        return 0.0;
    }
    for(int i = 0; i < qtd; i++){
        soma += turma[i].media;
    }
    return soma / qtd;

}

void mostrarAluno (Aluno a){
    printf("Matricula: %d\n", a.matricula);
    printf("Nome: %s\n", a.nome);
    printf("Nota 1: %.1f\n", a.nota1);
    printf("Nota 2: %.1f\n", a.nota2);
    printf("Media: %.1f\n", a.media);

    if(a.media >= 6.0){
        printf("Aprovado!\n");
    }else{
        printf("Reprovado!\n");
    }
}

int acimaDaMedia(Aluno turma[], int qtd, float mediaGeral){
    int contador = 0;    
    for(int i = 0; i < qtd; i++){
        if( turma[i].media > mediaGeral ){      
            contador++;                    
        }
    }
    return contador;  
                       
}

int maiorMedia(Aluno turma[], int qtd){
    if(qtd == 0){
        return -1;
    }
    int indiceMaior = 0;
    for(int i = 1; i < qtd; i++){
        if(turma[i].media > turma[indiceMaior].media){
            indiceMaior = i;
        }
    }
    return indiceMaior;
}

int menorMedia(Aluno turma[], int qtd){
    if(qtd == 0){
        return -1;
    }
    int indiceMenor = 0;
    for(int i = 1; i < qtd; i++){
        if(turma[i].media < turma[indiceMenor].media){
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

int main(){
    Aluno turma[MAX];
    int total = 0;

//cadastro
for(int i = 0; i < MAX; i++){
    cadastrar(turma, &total);
}

//mostrar todos
printf("\n----ALUNOS----"); 
for(int i = 0; i < total; i++){
    mostrarAluno(turma[i]);
printf("\n");
}

//maior e menor média
int posMaior = maiorMedia(turma, total);
int posMenor = menorMedia(turma, total);
printf("Maior media: %s com %.1f\n", turma[posMaior].nome, turma[posMaior].media);
printf("Menor media: %s com %.1f\n", turma[posMenor].nome, turma[posMenor].media);

//media geral
float geral = mediaTurma(turma, total);
printf("Media geral da turma: %.1f\n", geral);

//quantos acima da media
int qtdAcima = acimaDaMedia(turma, total, geral);
printf("Alunos acima da media: %d\n", qtdAcima);

return 0;
}