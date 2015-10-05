#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main () {
    
    int N, i; 
    long double *valoresX, *valoresY, *valoresXY, *valoresX2, somaX = 0, somaY = 0; 
    long double somaXY = 0, somaX2 = 0, a, b, conta1, conta2, *valoresW, erroA;
    long double somaW = 0, somaWX2 = 0, somaWX = 0, erroB, *errosY; 
    char flag;
   
    
    printf("Insira o numero de medidas realizadas: \n");
    scanf("%d", &N);
     

    valoresX = malloc(N * sizeof(long double));
    valoresW = malloc(N * sizeof(long double));
    valoresY = malloc(N * sizeof(long double));
    valoresXY = malloc(N * sizeof(long double));
    valoresX2 = malloc(N * sizeof(long double));
    errosY = malloc(N * sizeof(long double));
    
    
    printf("Insira os %d valores de X: \n", N);
    
    for(i = 0; i < N; i++){
        scanf("%Lf", &valoresX[i]);
    }    
    
    printf("Os erros em Y sao os mesmos? (y/n): \n");
    
    scanf(" %c", &flag);
    
    if(flag == 'y'){
        printf("Insira o erro em Y: \n");
        scanf("%Lf", &errosY[0]);
        
        for(i = 0; i < N; i++)
            errosY[i] = errosY[0];
        
        printf("Insira os %d valores de y: \n", N);
        
        for(i = 0; i < N; i++)
            scanf("%Lf", &valoresY[i]);
    }        
        
    else{    
        printf("Insira os %d valores de Y e seus erros: \n", N);
    
        for(i = 0; i < N; i++){
            scanf("%Lf", &valoresY[i]);
            scanf("%Lf", &errosY[i]);
        }    
    }
    
    for(i = 0; i < N; i++){
        valoresXY[i] = valoresX[i] * valoresY[i];
        valoresX2[i] = valoresX[i] * valoresX[i];
    }
    
    for(i = 0; i < N; i++){
        somaX += valoresX[i];
        somaY += valoresY[i];
        somaX2 += valoresX2[i];
        somaXY += valoresXY[i];
    } 
    
    /* Calcula o valor de a */
    conta1 = (N * somaXY) - (somaX * somaY);
    conta2 = (N * somaX2) - (somaX * somaX);
    
    a = conta1 / conta2;
    
    printf("a = %Lf\n", a);
    
    /* Calcula erro de a */
    
    for(i = 0; i < N; i++){
        valoresW[i] = 1 / (errosY[i] * errosY[i]);
        somaW += valoresW[i];
        
        somaWX2 += valoresW[i] * valoresX[i] * valoresX[i];
        somaWX += valoresW[i] * valoresX[i];
    }
    
    erroA = sqrt(somaW / ((somaW * somaWX2) - (somaWX * somaWX)));
    
    printf("Erro em a = %Lf\n\n", erroA); 
       
        
    /* Calcula o valor de b */
    conta1 = somaX2 * somaY - somaXY * somaX;
    conta2 = N * somaX2 - somaX * somaX;
  
    b = conta1 / conta2;
    
    printf("b = %Lf\n", b);
    
    /* Calcula erro de b */
    
    erroB = sqrt(somaWX2 / ((somaW * somaWX2) - (somaWX * somaWX)));
    
    printf("Erro em b = %Lf\n", erroB);
    
    
    free(valoresX);
    free(valoresX2);
    free(valoresXY);
    free(valoresY);
    free(errosY);
    free(valoresW);
    
    return 0;
}        