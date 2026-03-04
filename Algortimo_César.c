#include <stdlib.h>
#include <stdio.h>

/*
* Cambiar el orden en el que se muestran e introducen los datos:

	1. Cifrar con desplazamiento S=3
	2. Descifrar con desplazamiento S=-3
	3. Cifrar con clave
	4. Descifrar con clave
	   Opcion >> 
	
	Para cada caso, solicitar el mensaje a cifrar/descifrar porque no siempre va a ser el mismo, es decir, tal vez
	el usuario quiere descifrar directamente un mensaje, por lo que no hay necesidad de ingresarlo antes, sino al 
	momento de querer descifrar. Lo mismo con el desplazmaiento, la opción es si quieres cifrar o descifrar el
	mensaje.
*/

void cifrarConDesplazamiento(char mensaje[], int desplazamiento, char cifrado[]);
void descifrarConDesplazamiento(char mensaje[], int desplazamiento, char cifrado[]);
void construirAlfabetoClave(char clave[], char nuevoAlfabeto[]);
void cifrarConClave(char mensaje[], char clave[], char cifradoClave[]);

int main(){
	
	int op = 0;
	int s = 3;
	char mensaje[100] = "";				// Mensaje con máximo de 100 caracteres
	char clave[100] = "";				// Clave con máximo de 100 caracteres
	char cifrado[100] = "";				// Mensaje cifrado con máximo de 100 caracteres
	char cifradoClave[100] = "";				// Mensaje cifrado con clave con máximo de 100 caracteres
	
	do{
		//system("cls");
		printf("=================================\n");
		printf("||       ALGORITMO CESAR       ||\n");
		printf("=================================\n");
		printf("\nMENU PRINCIPAL:\n");
		printf("\n1. Ingresar Mensaje");
		if(mensaje[0] == '\0'){
			printf("\t\tMensaje actual:\t[ Sin mensaje ]\n");
		}else{
			printf("\t\tMensaje actual:\t%s\n", mensaje);
		};
		printf("2. Ingresar Clave");
		if(clave[0] == '\0'){
			printf("\t\tClave actual:\t[ Sin clave ]\n");
		}else{
			printf("\t\tClave actual:\t%s\n", clave);
		};
		printf("3. Cifrar con S=3");
		if(cifrado[0] == '\0'){
			printf("\t\tCifrado S=3:\n");
		}else{
			printf("\t\tCifrado S=3:\t%s\n", cifrado);
		};
		printf("4. Cifrar con Clave");
		if(cifradoClave[0] == '\0'){
			printf("\t\tCifrado clave:\n");
		}else{
			printf("\t\tCifrado clave:\t%s\n", cifradoClave);
		};
		printf("5. Salir\n");
		printf("   Opcion: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("\n\t-- Ingresar Mensaje:\n\t> ");
				scanf(" %[^\n]", mensaje);
				//system("cls");
				break;
			case 2:
				printf("\n\t-- Ingresar Clave:\n\t> ");
				scanf(" %[^\n]", clave);
				//system("cls");
				break;				break;
			case 3:
				printf("Cifrar con S=3\n");
				cifrarConDesplazamiento(mensaje, s, cifrado);
				descifrarConDesplazamiento(mensaje, s, cifrado);
				break;
			case 4:
			    if(mensaje[0] == '\0' || clave[0] == '\0'){
			        printf("Debes ingresar mensaje y clave primero\n");
			    }else{
			        cifrarConClave(mensaje, clave, cifradoClave);
			    };
			    break;
			case 5:
				printf("Saliendo...\n");
				break;
			default:
				printf("Opción no válida\n");
				break;
		};
	}while(op != 5);

	printf("Fin del programa\n");
	return 0;
};

void cifrarConDesplazamiento(char mensaje[], int desplazamiento, char cifrado[]){
	int i;
	for(i=0; mensaje[i] != '\0'; i++){
		if(mensaje[i] >= 'a' && mensaje[i] <= 'z'){
			cifrado[i] = ((mensaje[i] - 'a' + desplazamiento) % 26) + 'a';
		};
	};
	printf("%s\n",cifrado);
	return;
};

void descifrarConDesplazamiento(char mensaje[], int desplazamiento, char cifrado[]){
	int i;
	for(i = 0; cifrado[i] != '\0'; i++){
		if(cifrado[i] >= 'a' && cifrado[i] <= 'z'){
			mensaje[i] = ((cifrado[i] - 'a' - desplazamiento + 26) % 26) + 'a';
		};
	};
	printf("%s\n", mensaje);
	return;
};

void construirAlfabetoClave(char clave[], char nuevoAlfabeto[]){
    int usado[26] = {0};
    int i, j = 0;
    // 1. Agregar letras de la clave sin repetir
    for(i = 0; clave[i] != '\0'; i++){
        if(clave[i] >= 'a' && clave[i] <= 'z'){
            int indice = clave[i] - 'a';
            if(!usado[indice]){
                nuevoAlfabeto[j++] = clave[i];
                usado[indice] = 1;
            };
        };
    };
    // 2. Agregar resto del alfabeto
    for(i = 0; i < 26; i++){
        if(!usado[i]){
            nuevoAlfabeto[j++] = 'a' + i;
        };
    };
    nuevoAlfabeto[j] = '\0';
};

void cifrarConClave(char mensaje[], char clave[], char cifradoClave[]){
    char alfabetoNormal[] = "abcdefghijklmnopqrstuvwxyz";
    char alfabetoClave[27];
    int i, j;
    construirAlfabetoClave(clave, alfabetoClave);
    printf("\n\t Alfabeto:\t%s", alfabetoNormal);
    printf("\n\t Clave comp.:\t%s\n", alfabetoClave);
    for(i = 0; mensaje[i] != '\0'; i++){
        if(mensaje[i] >= 'a' && mensaje[i] <= 'z'){
            int indice = mensaje[i] - 'a';
            cifradoClave[i] = alfabetoClave[indice];
        };
    };
    printf("\n\t Mensaje cifrado: %s\n", cifradoClave);
};
