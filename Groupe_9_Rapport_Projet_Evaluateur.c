#include <stdio.h>
#include <stdbool.h> // Indispensable pour utiliser le type bool

/* --- VARIABLES GLOBALES --- */
char calu; 
bool erreur = false; // Initialisé à 'false' (pas d'erreur au début)

/* --- PROTOTYPES --- */
int expression();
int terme();
int facteur();
int nombre();
void lire_utile();
void vider_ligne();

/* --- FONCTION PRINCIPALE --- */
int main() {
    int resultat;

    printf("A toi ('.' pour quitter) : ");
    lire_utile(); 

    while (calu != '.') {
        erreur = false; // On repart de zéro pour chaque nouvelle ligne
        resultat = expression(); 

        // Si le drapeau 'erreur' est toujours à 'false' après le calcul
        if (!erreur) { 
            if (calu == '=') {
                printf("sa valeur est %d\n", resultat);
                lire_utile(); 
            } else {
                printf("Erreur : syntaxe incorrecte (attendu '=')\n");
                vider_ligne();
            }
        } else {
            // Si une fonction a levé une erreur (erreur == true)
            vider_ligne(); 
        }

        if (calu != '.') printf("\nA toi : ");
    }

    printf("Au revoir...\n");
    return 0;
}

/* --- DÉTAIL DES FONCTIONS --- */

void lire_utile() {
    do {
        calu = getchar();
    } while (calu == ' ' || calu == '\t' || calu == '\n' || calu == '\r');
}

void vider_ligne() {
    while (calu != '=' && calu != '.' && calu != '\n' && calu != EOF) {
        calu = getchar();
    }
    if (calu == '=') lire_utile(); 
}

int expression() {
    int g, d;
    char op;

    g = terme(); 
    if (erreur) return 0; // On s'arrête si une erreur est détectée
    
    if (calu == '+' || calu == '-') {
        op = calu;
        lire_utile();
        d = expression(); 
        
        if (op == '+') return g + d;
        else return g - d;
    }
    return g;
}

int terme() {
    int g, d;
    char op;

    g = facteur(); 
    if (erreur) return 0;
    
    if (calu == '*' || calu == '/') {
        op = calu;
        lire_utile();
        d = terme(); 
        
        if (op == '*') return g * d;
        else {
            if (d == 0) {
                printf("Erreur : Division par zéro !\n");
                erreur = true; // On lève le drapeau d'erreur
                return 0;
            }
            return g / d;
        }
    }
    return g;
}

int facteur() {
    int res;
    if (erreur) return 0;

    if (calu == '(') {
        lire_utile();
        res = expression(); 
        if (calu == ')') {
            lire_utile();
        } else {
            printf("Erreur : parenthèse ')' manquante\n");
            erreur = true;
            return 0;
        }
    } else {
        res = nombre(); 
    }
    return res;
}

int nombre() {
    int val = 0;

    if (calu < '0' || calu > '9') {
        printf("Erreur : Nombre attendu (trouvé '%c')\n", calu);
        erreur = true;
        return 0;
    }

    while (calu >= '0' && calu <= '9') {
        val = val * 10 + (calu - '0');
        calu = getchar(); 
    }

    while (calu == ' ' || calu == '\t' || calu == '\n' || calu == '\r') {
        calu = getchar();
    }

    return val;
}