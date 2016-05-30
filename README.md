# F-X29

Programas para uso nos labs de fisica 

----------------------------------------------------------------------------------------------------------------

Como compilar/executar os programas em terminal:

1) mmq.c (Calculo de coeficientes de retas e seus erros pelo metodo do mmq)

Compile com:

gcc mmq.c -o mmq -std=c99 -lm 

Execute com:

./mmq

OBS: nao se esqueca de que eh preciso, no minimo, 2 pontos distintos para descrever uma reta.

2) prop.c (Calculo de medias, desvios, erros, propagacao de erros)

Compile com:

gcc prop.c -o prop -std=c99 -lm

Execute com:

./prop

OBS: programa funcional APENAS para funcoes exponenciais com N termos cujas potencias sao numero inteiros.

Ex: y = K * x^(a) * z^(b) * w^(c)... , onde a, b, c pertencem aos inteiros e K eh uma constante real.