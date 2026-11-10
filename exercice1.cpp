#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Fonction qui effectue la division avec gestion d'erreur
double diviser(int a, int b) {
    if (b == 0) {
        throw runtime_error("Erreur : division par zero impossible !");
    }
    return static_cast<double>(a) / b;
}


int main() {
    // Cas de test : tableau de paires (numérateur, dénominateur)
    int casTests[][2] = {
        {10, 2},    // Cas normal : 5
        {7, 3},     // Division décimale : 2.333...
        {-20, 4},   // Négatif : -5
        {5, 0},     // Division par zéro → exception
        {0, 5},     // Zéro au numérateur : 0
        {100, 0}    // Autre division par zéro → exception
    };
    
    int nbCas = sizeof(casTests) / sizeof(casTests[0]);
    
    cout << "===== Tests de division =====" << endl;
    cout << endl;
    
    for (int i = 0; i < nbCas; i++) {
        int a = casTests[i][0];
        int b = casTests[i][1];
        
        cout << "Test " << (i + 1) << " : " << a << " / " << b << endl;
        
        try {
            double resultat = diviser(a, b);
            cout << "  → Resultat : " << resultat << endl;
        }
        catch (const runtime_error& e) {
            cout << "  → Exception interceptee : " << e.what() << endl;
        }
        
        cout << endl;
    }
    
    cout << "===== Fin des tests =====" << endl;
    
    return 0;
}