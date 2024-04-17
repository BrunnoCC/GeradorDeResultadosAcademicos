#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_NOME 50
#define MAX_CURSO 50
#define MAX_NOTAS 5

typedef struct {
    char nome[MAX_NOME];
    char telefone[15];
    char curso[MAX_CURSO];
    float notas[MAX_NOTAS];
    float media;
    char situacao[10];
} Aluno;

void calcularMediaESituacao(Aluno *aluno) {
    float soma = 0.0;
    for (int i = 0; i < 2; i++) {
        soma += aluno->notas[i];
    }
    aluno->media = soma / 2;
    if (aluno->media >= 7.0)
        strcpy(aluno->situacao, "APROVADO");
    else
        strcpy(aluno->situacao, "REPROVADO");
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }


    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), entrada);

    Aluno alunos[MAX_ALUNOS];
    int numAlunos = 0;


    char linha[100];
    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        sscanf(linha, "%[^,],%[^,],%[^,],%f,%f\n", alunos[numAlunos].nome, alunos[numAlunos].telefone, alunos[numAlunos].curso,
            &alunos[numAlunos].notas[0], &alunos[numAlunos].notas[1]);
        calcularMediaESituacao(&alunos[numAlunos]);
        fprintf(saida, "%s, %.2f, %s\n", alunos[numAlunos].nome, alunos[numAlunos].media, alunos[numAlunos].situacao);
        numAlunos++;
    }

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. Verifique o arquivo SituacaoFinal.csv.\n");

    return 0;
}
