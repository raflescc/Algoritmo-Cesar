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
	char cifradoClave[100] = "";		// Mensaje cifrado con clave con máximo de 100 caracteres
	
	do{
		printf("=================================\n");
		printf("||       ALGORITMO CESAR       ||\n");
		printf("=================================\n");
		printf("\nMENU PRINCIPAL:\n");
		printf(" 1. Cifrar con S=3\n");
		printf(" 2. Descifrar con S=-3\n");
		printf(" 3. Cifrar con Clave\n");
		printf(" 4. Descifrar con Clave\n");
		printf(" 5. Salir\n");
		printf("    Opcion: ");
		scanf("%d", &op);
		system("cls");
		switch(op){
			case 1:
				printf("\n\tCIFRAR CON DESPLAZAMIENTO S=3\n");
				printf("\n\tMensaje (M): >> ");
				scanf(" %[^\n]", mensaje);
				cifrarConDesplazamiento(mensaje, s, cifrado);
				break;
			case 2:
				printf("\n\tDESCIFRAR CON DESPLAZAMIENTO S=-3\n");
				printf("\n\tCifrado (C): >> ");
				scanf(" %[^\n]", cifrado);
				descifrarConDesplazamiento(mensaje, s, cifrado);
				break;
			case 3:
				printf("\n\tCIFRAR CON CLAVE\n");
				printf("\n\tMensaje (M): >> ");
				scanf(" %[^\n]", mensaje);
				printf("\n\tClave (K):   >> ");
				scanf(" %[^\n]", clave);
				cifrarConClave(mensaje, clave, cifradoClave);
				break;
			case 4:
			    printf("\n\tDESCIFRAR CON CLAVE\n");
				printf("\n\tCifrado(C): >> ");
				scanf(" %[^\n]", cifradoClave);
				printf("\n\tClave (K):  >> ");
				scanf(" %[^\n]", clave);
				descifrarConClave(mensaje, clave, cifradoClave);
			    break;
			case 5:
				printf("\nSaliendo...\n");
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
	char alfabetoNormal[] = "abcdefghijklmnopqrstuvwxyz";
	char alfabetoDesplazamiento[] = "defghijklmnopqrstuvwxyzabc";
	printf("\n\tAlfabeto:\t%s", alfabetoNormal);
    printf("\n\tDesplazamiento:\t%s\n", alfabetoDesplazamiento);
	int i;
	for(i = 0; mensaje[i] != '\0'; i++){
        if(mensaje[i] >= 'a' && mensaje[i] <= 'z'){							// Manejo de minúsculas
            cifrado[i] = ((mensaje[i] - 'a' + desplazamiento) % 26) + 'a';
        }else if(mensaje[i] >= 'A' && mensaje[i] <= 'Z'){					// Manejo de mayúsculas
            cifrado[i] = ((mensaje[i] - 'A' + desplazamiento) % 26) + 'A';
        }else{
            cifrado[i] = mensaje[i];				// Manejo de espacios
        };
    };
    cifrado[i] = '\0';								// Agregar fin de cadena
	printf("\n\tCifrado (C):\t%s\n\n", cifrado);
	return;
};

void descifrarConDesplazamiento(char mensaje[], int desplazamiento, char cifrado[]){
	char alfabetoNormal[] = "abcdefghijklmnopqrstuvwxyz";
	char alfabetoDesplazamiento[] = "defghijklmnopqrstuvwxyzabc";
	int i;
	
    printf("\n\tDesplazamiento:\t%s\n", alfabetoDesplazamiento);
	printf("\tAlfabeto:\t%s\n", alfabetoNormal);
	
	for(i = 0; cifrado[i] != '\0'; i++){
        if(cifrado[i] >= 'a' && cifrado[i] <= 'z'){							// Manejo de minúsculas
            mensaje[i] = ((cifrado[i] - 'a' - desplazamiento + 26) % 26) + 'a';
        }else if(cifrado[i] >= 'A' && cifrado[i] <= 'Z'){					// Manejo de mayúsculas
            mensaje[i] = ((cifrado[i] - 'A' - desplazamiento + 26) % 26) + 'A';
        }else{
            mensaje[i] = cifrado[i];				// Manejo de espacios
        };
    };
    mensaje[i] = '\0';								// Agregar fin de cadena
	printf("\n\tMensaje (M'):\t%s\n\n", mensaje);
	return;
};

void cifrarConClave(char mensaje[], char clave[], char cifradoClave[]){
    char alfabetoNormal[] = "abcdefghijklmnopqrstuvwxyz";
    char alfabetoClave[27];
    int i, j;
    
    construirAlfabetoClave(clave, alfabetoClave);
    printf("\n\tAlfabeto:\t%s", alfabetoNormal);
    printf("\n\tClave comp.:\t%s\n", alfabetoClave);
    
    for(i = 0; mensaje[i] != '\0'; i++){
        
        if(mensaje[i] >= 'a' && mensaje[i] <= 'z'){
            int indice = mensaje[i] - 'a';
            cifradoClave[i] = alfabetoClave[indice];						// Manejo de mayúsculas
        }
        else if(mensaje[i] >= 'A' && mensaje[i] <= 'Z'){
            int indice = mensaje[i] - 'A';
            cifradoClave[i] = alfabetoClave[indice] - 32;					// Manejo de mayúsculas
        }
        else{
            cifradoClave[i] = mensaje[i];			// Manejo de espacios
        };
    };
    cifradoClave[i] = '\0';							// Agregar fin de cadena
    printf("\n\tCifrado (C):\t%s\n\n", cifradoClave);
};

void descifrarConClave(char mensaje[], char clave[], char cifradoClave[]){
	char alfabetoNormal[] = "abcdefghijklmnopqrstuvwxyz";
    char alfabetoClave[27];
    int i, j;

    construirAlfabetoClave(clave, alfabetoClave);
    printf("\n\tClave comp.:\t%s\n", alfabetoClave);
    printf("\tAlfabeto:\t%s\n", alfabetoNormal);

    for(i = 0; cifradoClave[i] != '\0'; i++){
        if(cifradoClave[i] >= 'a' && cifradoClave[i] <= 'z'){
            for(j = 0; j < 26; j++){
                if(cifradoClave[i] == alfabetoClave[j]){
                    mensaje[i] = 'a' + j;
                    break;
                };
            };
        }else if(cifradoClave[i] >= 'A' && cifradoClave[i] <= 'Z'){
            
            char minuscula = cifradoClave[i] + 32; 	// convertir a minúscula
            
            for(j = 0; j < 26; j++){
                if(minuscula == alfabetoClave[j]){
                    mensaje[i] = ('a' + j) - 32; 	// volver a mayúscula
                    break;
                };
            };
        }else{
            mensaje[i] = cifradoClave[i];
        };
    };
    mensaje[i] = '\0';								// Agregar fin de cadena
    printf("\n\tMensaje (M'):\t%s\n\n", mensaje);
}

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
