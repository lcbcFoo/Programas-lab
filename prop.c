/* Autor: Lucas Castro (Foo) *
 * Ultima modificacao: 23/05/2016 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {

    int N, i, quantidade, j;
    long double *valoresX, *desvios, *erros, *errosIns, *medias;
    long double calculado = 1, erroCalc, *errosTotais, constante, *potencias;
    long double soma = 0;


    printf("Lembre-se das unidades das medidas inseridas!\n\n");
    printf("O programa funciona apenas para funcoes potencia, independende da quantidade de termos (ex: y = x^3 * z^(-4) * h^(1)...\n\n");
    printf("Sera necessario apenas digitar a constante, o numero de variaveis e a potencia delas (respectivamente). Em seguida o programa ira pedir as medidas e o erro instrumental de cada medida.\n\n");
    printf("O programa ira calcular a media, o desvio padrao e o erro estatistico de cada variavel com base no numero de medidas.\n\n");
    printf("Alem disso, ele ira calcular o valor da funcao, com base nas potencias e a constante inseridas, e ira propagar o erro para esse valor.\n\n");

    /* Recebe as variaveis e a constante */
    printf("\n\n\n\nInsira o numero de variaveis da formula: \n");
    scanf("%d", &quantidade);
    printf("Insira a constante: \n");
    scanf("%Lf", &constante);

    potencias = malloc(quantidade * sizeof(long double));
    desvios = malloc(quantidade * sizeof(long double));
    erros = malloc(quantidade * sizeof(long double));
    medias = malloc(quantidade * sizeof(long double));
    errosIns = malloc(quantidade * sizeof(long double));
    errosTotais = malloc(quantidade * sizeof(long double));

    /* Recebe as potencias das variaveis */
    printf("Digite as respectivas potencias: \n");

    for(i = 0; i < quantidade; i++)
        scanf("%Lf", &potencias[i]);

    for(j = 0; j < quantidade; j++){

        /* Recebe quantidade de medidas da variavel atual */
        printf("\nInsira o numero de medidas: \n");
        scanf("%d", &N);

        valoresX = malloc (N * sizeof(long double));

        /* Recebe as medidas */
        printf("Insira os %d valores medidos:\n", N);
        soma = 0;

        for(i = 0; i < N; i++){
            scanf("%Lf", &valoresX[i]);
            soma += valoresX[i];
        }

        /* Recebe o erro instrumental */
        printf("Insira o erro instrumental: \n");
        scanf("%Lf", &errosIns[j]);

        /* Calcula / Imprime a media */
        medias[j] = soma / N;
        printf("\nMedia = %Lf\n", medias[j]);

        /* Calcula / Imprime o desvio padrao, os erros exp e os erros totais */
        soma = 0;

        for(i = 0; i < N; i++)
            soma += (long double) ((valoresX[i] - medias[j]) * (valoresX[i] - medias[j]));

        if(N == 1){
            desvios[j] = 0;
            erros[j] = 0;
            errosTotais[j] = errosIns[j];
        }

        else{
            desvios[j] = sqrt(soma / (N - 1));
            erros[j] = desvios[j] / (sqrt(N));
            errosTotais[j] = sqrt(pow(erros[j], 2) + pow(errosIns[j], 2));
        }
            
        printf("Desvio Padrao = %Lf\n", desvios[j]);
        printf("Erro Estatistico = %Lf\n", erros[j]);
        printf("Erros Totais = %Lf\n", errosTotais[j]);
        free(valoresX);
    }

    /* Calcula / Imprime o valor da grandeza desejada */
    calculado *= constante;

    for(j = 0; j < quantidade; j++)
        calculado *= pow(medias[j], potencias[j]);


    printf("\nResultado obtido = %Lf\n", calculado);



    /* Calcula / imprime o erro propagado para essa grandeza */
    soma = 0;

    for(j = 0; j < quantidade; j++){
        if(abs(potencias[j]) > 2)
            soma += (long double) pow(potencias[j] * ((long double) pow(errosTotais[j], potencias[j] - 1)) / medias[j], 2);

        else
            soma += (long double) pow(potencias[j] * errosTotais[j] / medias[j], 2);
    }

    erroCalc = calculado * sqrt(soma);
    printf("Erro calculado = %Lf\n", erroCalc);


    /* Desaloca memoria */
    free(desvios);
    free(erros);
    free(potencias);
    free(medias);
    free(errosIns);
    free(errosTotais);


    return 0;
}