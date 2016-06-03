/* Autor: Lucas de Camargo Barros de Castro (Foo)
 * Ultima modificacao: 30/05/2016 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Struct that represents a number *
 * Vars:
 *	char string[1000]; - string representation of the number
 * 	int* number;       - integer pointer representation of the number
 *	int decimalDigits; - how many decimal digits the number has
 *	int stringSize;    - ...
 *	int numberSize;    - ...
 *  int isZero;        - marks true if the number is a zero
*/
typedef struct Number{
	char string[1000];
	int* number;
	int decimalDigits;
	int stringSize;
	int numberSize;
	int isZero;
} Number;


/* Returns how many decimal digits the number has 
 *
 * Param:
 *  char* number - string which contains the number
 *  int n        - string's size
 */
void getDecimalDigits(Number* n){
	int flag = 0;

	n->decimalDigits = 0;

	for(int i = 0; i < n->stringSize; i++){
		if(n->string[i] == '.')
			flag = 1;

		else if(flag)
			n->decimalDigits++;
	}
}

/* Tests if the number is a zero */
void testZero(Number* n){
	for(int i = 0; i < n->stringSize; i++)
		if(n->string[i] != '0' && n->string[i] != '.'){
			n->isZero = 0;
			return;
		}

	n->stringSize = 3;
	n->string[0] = '0';
	n->string[1] = '.';
	n->string[2] = '0';
	n->isZero = 1;
}

/* Remove the left zeros of the integer pointer of a Number */
void removeLeftZeros(Number* n){

	int zeros = 0;

	if(n->isZero)
		return;

	while((n->numberSize > zeros) && (n->number[zeros] == 0)){
		zeros++;
	}

	if(zeros == n->numberSize){
		n->number = malloc(sizeof(int));
		n->number[0] = 0;
		n->numberSize = 1;
	}

	int* newInt = malloc((n->numberSize - zeros) * sizeof(int));

	for(int i = 0; i < n->numberSize - zeros; i++){
		newInt[i] = n->number[zeros + i];
	}

	n->numberSize = n->numberSize - zeros;
	free(n->number);
	n->number = newInt;
}

/* Multiply two integers contained in integer pointers
 *
 * Param:
 *  Number* n1      - first number
 *  Number* n2      - second number
 *  Number* result  - integer pointer where the result will be placed
*/
void multiply(Number* n1, Number* n2, Number* result) {

    if(n1->numberSize < n2->numberSize){
    	multiply(n2, n1, result);
    	return;
    }

    if((n1->isZero) || (n2->isZero)){
    	result->isZero = 1;
    	result->number = calloc(1, sizeof(int));
    	result->numberSize = 1;
    	return;
    }

    result->numberSize = n1->numberSize + n2->numberSize;
    result->number = calloc(result->numberSize, sizeof(int));
    result->isZero = 0;
    
    for(int i = 0; i < n2->numberSize; i++){

        for(int j = 0; j < n1->numberSize; j++){
            result->number[i + j + 1] += n2->number[i] * n1->number[j];
        }
    }  

    for(int j = result->numberSize - 1; j >= 0; j--){
        if(result->number[j] / 10 > 0){
            result->number[j - 1] += result->number[j] / 10;
            result->number[j] = result->number[j] % 10;           
        }
    } 

    removeLeftZeros(result); 
}

/* Convert a string which contains a decimal number to a integer pointer
 *
 * Param:
 * 	Number* n - pointer for the number which will be string-to-int converted
 */
void stringToIntPointer(Number* n){

	int flag = 0;

	if(n->decimalDigits)
		flag = 1;

	n->number = malloc((n->stringSize - flag) * sizeof(int));

	for(int i = 0, j = 0; i < n->stringSize; i++){
		if(n->string[i] != '.' && n->string[i] != '\n')
			n->number[j++] = (n->string[i] - '0');
	}

	n->numberSize = n->stringSize - flag;

	removeLeftZeros(n);

	for(int i =0 ; i < n->numberSize; i++)
		printf("%d", n->number[i]);
	printf("\n");
}

/* Check if the string has the format "<numbers>.<numbers>", if it is only "<number>"
 * put a ".0" in its end 
 */
void putDot(char* string, int* n){
	for(int i = 0; i < (*n); i++)
		if(string[i] == '.')
			return;

	string[(*n)] = '.';
	string[(*n) + 1] = '0';
	(*n) += 2;
}

/* Convert an integer pointer to a string
 *
 * Param:
 *  Number* n - pointer to the Number which will be integer-pinter-to-string converted
 */
void  intPointerToString(Number* n){

	if(n->isZero){
		n->stringSize = 4;
		strcpy(n->string, "0.0\0");
		return;
	}

	if(n->decimalDigits == 0){
		n->stringSize = n->numberSize + 2;
		n->string[n->stringSize - 2 ] = '.';

		for(int i = 0, j = 0; i < n->stringSize - 1; i++)
			if(i != n->stringSize - 2)
				n->string[i] = n->number[j++] + '0';	
		
		n->string[n->stringSize - 1] = '0';
	}
	
	else if(n->numberSize - n->decimalDigits == 0){
		int i = 2;
		
		while(n->numberSize - n->decimalDigits + i - 1 <= 0)
			i++;

		n->stringSize = n->numberSize + i;
		n->string[0] = '0';
		n->string[1] = '.';

		for(int j = 2; j < i; j++)
			n->string[j] = '0';

		for(int j = 0; j < n->numberSize; j++)
			n->string[i++] = n->number[j] + '0';
	}

	else if(n->numberSize - n->decimalDigits > 0){
		n->stringSize = n->numberSize + 1;
		n->string[n->stringSize - n->decimalDigits - 1] = '.';

		for(int i = 0, j = 0; i < n->stringSize; i++)
			if(i != n->stringSize - n->decimalDigits - 1)
				n->string[i] = n->number[j++] + '0';
	}

	else {
		n->string[0] = '0';
		n->string[1] = '.';

		int i;

		for(i = 2; i < n->decimalDigits - n->numberSize + 2; i++)
			n->string[i] = '0';

		for(int j = 0; j < n->numberSize; j++){
			n->string[i] = n->number[j] + '0';
			i++;
		}

		n->string[i] = '\0';
		n->stringSize = i;
	}

	n->string[n->stringSize] = '\0';

	for(int i = n->stringSize - 1; i >= 0; i--)
		if(n->string[i] == '0'){
			n->stringSize--;
			n->string[i] = '\0';
		}

		else
			break;

	if(n->string[n->stringSize - 1] == '.'){
		n->stringSize++;
		n->string[n->stringSize - 1] = '0';
	}
}

int main(){

	Number n1;
	Number n2;
	Number result;

	printf("Digite o primeiro numero\n");
	scanf(" %s", n1.string);
	n1.stringSize = strlen(n1.string);
	putDot(n1.string, &n1.stringSize);
	testZero(&n1);

	printf("Digite o segundo numero\n");
	scanf(" %s", n2.string);
	n2.stringSize = strlen(n2.string);
	putDot(n2.string, &n2.stringSize);
	testZero(&n2);

	getDecimalDigits(&n1);
	getDecimalDigits(&n2);
	result.decimalDigits = n1.decimalDigits + n2.decimalDigits;
	stringToIntPointer(&n1);
	stringToIntPointer(&n2);

	multiply(&n1, &n2, &result);
	intPointerToString(&result);
	printf("Resultado: %s\n", result.string);

	free(n1.number);
	free(n2.number);
	free(result.number);

	return 0;
}