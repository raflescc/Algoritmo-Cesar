/*
 * =============================================
 *   CIFRADO DE HILL (3x3) - Implementacion C
 * =============================================
 * - Matriz clave K: 3x3
 * - Mensaje M: 3xn  |  Cifrado C: 3xn
 * - Llenado por columnas (de arriba hacia abajo)
 * - Relleno con letra 'x'
 * - Algebra mod 26
 * =============================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 300

/* ============================================================
   UTILIDADES
   ============================================================ */

int mod26(int x) {
    return ((x % 26) + 26) % 26;
};

int charANum(char c) {
    return (int)(tolower((unsigned char)c) - 'a');
};

char numAChar(int n) {
    return (char)('a' + mod26(n));
};

/* Copia solo letras en minusculas al arreglo dest, retorna longitud */
int limpiarTexto(const char *src, char *dest) {
    int i, j;
    j = 0;
    for (i = 0; src[i] != '\0'; i++) {
        if (isalpha((unsigned char)src[i])) {
            dest[j] = (char)tolower((unsigned char)src[i]);
            j++;
        };
    };
    dest[j] = '\0';
    return j;
};

/* ============================================================
   IMPRIMIR MATRICES
   ============================================================ */

void imprimirMatriz3x3(const char *nombre, int m[3][3]) {
    int i, j;
    printf("\n  Matriz %s:\n", nombre);
    for (i = 0; i < 3; i++) {
        printf("  | ");
        for (j = 0; j < 3; j++) {
            printf("%4d ", m[i][j]);
        };
        printf("|\n");
    };
};

void imprimirMatriz3x3Letras(const char *nombre, int m[3][3]) {
    int i, j;
    printf("\n  Matriz %s (letras):\n", nombre);
    for (i = 0; i < 3; i++) {
        printf("  | ");
        for (j = 0; j < 3; j++) {
            printf("  %c  ", numAChar(m[i][j]));
        };
        printf("|\n");
    };
};

void imprimirMatriz3xN(const char *nombre, int m[3][MAX], int n) {
    int i, j;
    printf("\n  Matriz %s:\n", nombre);
    for (i = 0; i < 3; i++) {
        printf("  | ");
        for (j = 0; j < n; j++) {
            printf("%4d ", m[i][j]);
        }
        printf("|\n");
    };
};

void imprimirMatriz3xNLetras(const char *nombre, int m[3][MAX], int n) {
    int i, j;
    printf("\n  Matriz %s (letras):\n", nombre);
    for (i = 0; i < 3; i++) {
        printf("  | ");
        for (j = 0; j < n; j++) {
            printf("  %c  ", numAChar(m[i][j]));
        };
        printf("|\n");
    };
};

/* ============================================================
   DETERMINANTE, ADJUNTA E INVERSA
   ============================================================ */

int determinante3x3(int m[3][3]) {
    return m[0][0] * (m[1][1]*m[2][2] - m[1][2]*m[2][1])
         - m[0][1] * (m[1][0]*m[2][2] - m[1][2]*m[2][0])
         + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
};

/* Calcula la adjunta (transpuesta de la matriz de cofactores) */
void adjunta3x3(int m[3][3], int adj[3][3]) {
    int cof[3][3];
    int i, j;

    cof[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1]);
    cof[0][1] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0]);
    cof[0][2] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
    cof[1][0] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1]);
    cof[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0]);
    cof[1][2] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0]);
    cof[2][0] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1]);
    cof[2][1] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0]);
    cof[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0]);

    /* Adjunta = transpuesta de cofactores */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            adj[i][j] = cof[j][i];
};

/* Retorna el inverso de a mod 26, o -1 si no existe */
int inversoMod26(int a) {
    int i;
    a = mod26(a);
    for (i = 1; i < 26; i++) {
        if (mod26(a * i) == 1)
            return i;
    };
    return -1;
};

/* Muestra det, adjunta e inversa. Llena Kinv. Retorna 1 si ok, 0 si falla. */
int calcularInversa(int K[3][3], int Kinv[3][3]) {
    int det, detMod, detInv;
    int adj[3][3];
    int i, j;

    det    = determinante3x3(K);
    detMod = mod26(det);
    detInv = inversoMod26(detMod);

    printf("\n  +---------------------------------------+\n");
    printf("  |   Propiedades de la Matriz Clave K   |\n");
    printf("  +---------------------------------------+\n");

    printf("\n  Determinante(K)        = %d\n", det);
    printf("  Determinante(K) mod 26 = %d\n", detMod);

    if (detInv == -1) {
        printf("\n  [!] El det mod 26 = %d no tiene inverso mod 26.\n", detMod);
        printf("      mcd(%d, 26) != 1 => clave NO valida para Hill.\n", detMod);
        return 0;
    };
    printf("  Inverso modular:  %d^(-1) mod 26 = %d\n", detMod, detInv);
    printf("  Verificacion:     %d x %d = %d = 1 (mod 26)\n",
           detMod, detInv, detMod * detInv);

    adjunta3x3(K, adj);

    printf("\n  Adjunta(K):\n");
    for (i = 0; i < 3; i++) {
        printf("  | ");
        for (j = 0; j < 3; j++)
            printf("%6d ", adj[i][j]);
        printf("|\n");
    };

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            Kinv[i][j] = mod26(detInv * adj[i][j]);

    printf("\n  K^(-1) mod 26  =  %d * Adjunta(K)  mod 26:\n", detInv);
    for (i = 0; i < 3; i++) {
        printf("  | ");
        for (j = 0; j < 3; j++)
            printf("%4d ", Kinv[i][j]);
        printf("|\n");
    };
    imprimirMatriz3x3Letras("K^(-1)", Kinv);

    return 1;
};

/* ============================================================
   LLENAR MATRICES DESDE TEXTO
   ============================================================ */

/* Llena K 3x3 desde 9 letras, por columnas */
void llenarMatrizClave(const char *clave, int K[3][3]) {
    int col, row;
    int idx = 0;
    for (col = 0; col < 3; col++)
        for (row = 0; row < 3; row++) {
            K[row][col] = charANum(clave[idx]);
            idx++;
        };
};

/* Llena matriz 3xN desde texto, por columnas */
void llenarMatriz3xN(const char *texto, int len, int m[3][MAX], int *numCols) {
    int col, row;
    *numCols = len / 3;
    for (col = 0; col < *numCols; col++)
        for (row = 0; row < 3; row++)
            m[row][col] = charANum(texto[col * 3 + row]);
};

/* ============================================================
   MULTIPLICACION  resultado = K * v  mod 26
   ============================================================ */

void multiplyKv(int K[3][3], int v[3], int res[3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        res[i] = 0;
        for (j = 0; j < 3; j++)
            res[i] += K[i][j] * v[j];
        res[i] = mod26(res[i]);
    };
};

/* ============================================================
   CIFRAR
   ============================================================ */

void cifrar(int K[3][3], const char *mensajeLimpio, int mostrarProc) {
    char mensaje[MAX];
    int M[3][MAX], C[3][MAX];
    int numCols, col, row, j;
    int v[3], res[3];
    char cifrado[MAX];
    int lenMsg;

    strcpy(mensaje, mensajeLimpio);
    lenMsg = (int)strlen(mensaje);

    /* Relleno con 'x' */
    while (lenMsg % 3 != 0) {
        mensaje[lenMsg] = 'x';
        lenMsg++;
    };
    mensaje[lenMsg] = '\0';

    numCols = lenMsg / 3;

    printf("\n  Mensaje con relleno : \"%s\"\n", mensaje);
    printf("  Longitud            : %d letras => %d columna(s)\n", lenMsg, numCols);

    llenarMatriz3xN(mensaje, lenMsg, M, &numCols);

    if (mostrarProc) {
        imprimirMatriz3xN("M (numeros)", M, numCols);
        imprimirMatriz3xNLetras("M", M, numCols);
    };

    printf("\n  --- C = K * M  (columna por columna, mod 26) ---\n");

    for (col = 0; col < numCols; col++) {
        for (row = 0; row < 3; row++) v[row] = M[row][col];

        if (mostrarProc) {
            printf("\n  Columna %d: m = [", col + 1);
            for (row = 0; row < 3; row++)
                printf("%d%s", v[row], row < 2 ? ", " : "");
            printf("]  letras: (");
            for (row = 0; row < 3; row++)
                printf("%c%s", numAChar(v[row]), row < 2 ? "," : "");
            printf(")\n");
        };

        multiplyKv(K, v, res);

        if (mostrarProc) {
            for (row = 0; row < 3; row++) {
                int suma = 0;
                printf("    c[%d] = ", row);
                for (j = 0; j < 3; j++) {
                    printf("%d*%d", K[row][j], v[j]);
                    suma += K[row][j] * v[j];
                    if (j < 2) printf(" + ");
                };
                printf(" = %d  mod 26 = %d  => '%c'\n", suma, res[row], numAChar(res[row]));
            };
        };

        for (row = 0; row < 3; row++)
            C[row][col] = res[row];
    };

    /* Construir cadena cifrada (lectura por columnas) */
    j = 0;
    for (col = 0; col < numCols; col++)
        for (row = 0; row < 3; row++)
            cifrado[j++] = numAChar(C[row][col]);
    cifrado[j] = '\0';

    if (mostrarProc) {
        imprimirMatriz3xN("C (numeros)", C, numCols);
        imprimirMatriz3xNLetras("C", C, numCols);
    };

    printf("\n  ========================================\n");
    printf("  Mensaje original  : %s\n", mensajeLimpio);
    printf("  Texto cifrado     : %s\n", cifrado);
    printf("  ========================================\n");
};

/* ============================================================
   DESCIFRAR
   ============================================================ */

void descifrar(int K[3][3], const char *textoCifradoRaw, int mostrarProc) {
    char texto[MAX];
    int C[3][MAX], M[3][MAX];
    int Kinv[3][3];
    int numCols, col, row, j;
    int v[3], res[3];
    char descifrado[MAX];
    int lenTxt;

    lenTxt = limpiarTexto(textoCifradoRaw, texto);

    if (lenTxt % 3 != 0) {
        printf("\n  [!] El texto cifrado debe tener longitud multiplo de 3.\n");
        return;
    };

    if (!calcularInversa(K, Kinv)) return;

    numCols = lenTxt / 3;

    llenarMatriz3xN(texto, lenTxt, C, &numCols);

    if (mostrarProc) {
        printf("\n  Texto cifrado: \"%s\"\n", texto);
        imprimirMatriz3xN("C (numeros)", C, numCols);
        imprimirMatriz3xNLetras("C", C, numCols);
        printf("\n  --- M = K^(-1) * C  (columna por columna, mod 26) ---\n");
    };

    for (col = 0; col < numCols; col++) {
        for (row = 0; row < 3; row++) v[row] = C[row][col];

        if (mostrarProc) {
            printf("\n  Columna %d: c = [", col + 1);
            for (row = 0; row < 3; row++)
                printf("%d%s", v[row], row < 2 ? ", " : "");
            printf("]  letras: (");
            for (row = 0; row < 3; row++)
                printf("%c%s", numAChar(v[row]), row < 2 ? "," : "");
            printf(")\n");
        };

        multiplyKv(Kinv, v, res);

        if (mostrarProc) {
            for (row = 0; row < 3; row++) {
                int suma = 0;
                printf("    m[%d] = ", row);
                for (j = 0; j < 3; j++) {
                    printf("%d*%d", Kinv[row][j], v[j]);
                    suma += Kinv[row][j] * v[j];
                    if (j < 2) printf(" + ");
                };
                printf(" = %d  mod 26 = %d  => '%c'\n", suma, res[row], numAChar(res[row]));
            };
        };
        for (row = 0; row < 3; row++)
            M[row][col] = res[row];
    };

    j = 0;
    for (col = 0; col < numCols; col++){
        for (row = 0; row < 3; row++){
            descifrado[j++] = numAChar(M[row][col]);
        };
    };
    descifrado[j] = '\0';

    if (mostrarProc) {
        imprimirMatriz3xN("M descifrada (numeros)", M, numCols);
        imprimirMatriz3xNLetras("M descifrada", M, numCols);
    };

    printf("\n  ========================================\n");
    printf("  Texto cifrado     : %s\n", texto);
    printf("  Mensaje descifrado: %s\n", descifrado);
    printf("  (las 'x' al final son relleno)\n");
    printf("  ========================================\n");
}

/* ============================================================
   MAIN
   ============================================================ */

int main() {
    char claveRaw[MAX], claveL[MAX];
    char textoRaw[MAX];
    int K[3][3], Kinv[3][3];
    int opcion, mostrarProc;
    char respProc;
    int lenClave;

    printf("=============================================\n");
    printf("                CIFRADO HILL\n");
    printf("=============================================\n");
    printf("  - Solo letras minusculas sin acentos\n");
    printf("=============================================\n\n");

    printf(" Ingrese la clave (exactamente 9 letras): ");
    scanf("%s", claveRaw);

    lenClave = limpiarTexto(claveRaw, claveL);

    if (lenClave != 9) {
        printf("\n [!] La clave debe tener exactamente 9 letras.\n");
        return 1;
    };

    llenarMatrizClave(claveL, K);

    printf("\n  Clave: \"%s\"\n", claveL);
    imprimirMatriz3x3("K (numeros)", K);
    imprimirMatriz3x3Letras("K", K);

    /* Verificar y mostrar propiedades de K */
    if (!calcularInversa(K, Kinv)) {
        printf("\n [!] Elija una clave cuyo determinante sea coprimo con 26.\n");
        printf("     (mcd(det, 26) debe ser 1)\n");
        return 1;
    };

    printf("\n  Mostrar procedimiento paso a paso? (s=si / n=no): ");
    scanf(" %c", &respProc);
    mostrarProc = (respProc == 's' || respProc == 'S') ? 1 : 0;

    printf("\n  +--------------------------+\n");
    printf("  |          MENU            |\n");
    printf("  |  1. Cifrar mensaje       |\n");
    printf("  |  2. Descifrar mensaje    |\n");
    printf("  +--------------------------+\n");
    printf("  Opcion: ");
    scanf("%d", &opcion);

    if(opcion == 1){
        char mensajeLimpio[MAX];
        printf("\n  Ingrese el mensaje a cifrar: ");
        scanf("%s", textoRaw);
        limpiarTexto(textoRaw, mensajeLimpio);
        printf("\n=== CIFRADO ===\n");
        cifrar(K, mensajeLimpio, mostrarProc);
    }else if (opcion == 2){
        printf("\n  Ingrese el texto cifrado: ");
        scanf("%s", textoRaw);
        printf("\n=== DESCIFRADO ===\n");
        descifrar(K, textoRaw, mostrarProc);
    }else{
        printf("\n  [!] Opcion no valida.\n");
    };

    return 0;
};
