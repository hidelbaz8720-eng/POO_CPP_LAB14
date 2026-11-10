#include <iostream>
#include <exception>
#include <string>
#include <iomanip>

using namespace std;


class BanqueException : public exception {
protected:
    string message;
public:
    explicit BanqueException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Exception 1 : montant invalide (dépôt ou retrait <= 0)
class MontantInvalideException : public BanqueException {
private:
    double montant;
public:
    explicit MontantInvalideException(double m)
        : BanqueException("Montant invalide : " + to_string(m) 
                          + " (doit être strictement positif)"),
          montant(m) {}
    double getMontant() const { return montant; }
};

// Exception 2 : solde insuffisant pour un retrait
class SoldeInsuffisantException : public BanqueException {
private:
    double soldeActuel;
    double montantDemande;
public:
    SoldeInsuffisantException(double solde, double demande)
        : BanqueException("Solde insuffisant ! Solde : " + to_string(solde) 
                          + " | Demande : " + to_string(demande)
                          + " | Manque : " + to_string(demande - solde)),
          soldeActuel(solde), montantDemande(demande) {}
    
    double getSoldeActuel() const { return soldeActuel; }
    double getMontantDemande() const { return montantDemande; }
    double getManque() const { return montantDemande - soldeActuel; }
};


class Compte {
private:
    string titulaire;
    int numeroCompte;
    double solde;

public:
    Compte(const string& titulaire, int numero, double soldeInitial)
        : titulaire(titulaire), numeroCompte(numero) {
        if (soldeInitial < 0) {
            throw MontantInvalideException(soldeInitial);
        }
        solde = soldeInitial;
    }
    
    // Dépôt
    void deposer(double montant) {
        if (montant <= 0) {
            throw MontantInvalideException(montant);
        }
        solde += montant;
        cout << " Depot de " << fixed << setprecision(2) << montant 
             << " DH effectué. Nouveau solde : " << solde << " DH" << endl;
    }
    
    // Retrait
    void retirer(double montant) {
        if (montant <= 0) {
            throw MontantInvalideException(montant);
        }
        if (montant > solde) {
            throw SoldeInsuffisantException(solde, montant);
        }
        solde -= montant;
        cout << "  Retrait de " << fixed << setprecision(2) << montant 
             << " DH effectue. Nouveau solde : " << solde << " DH" << endl;
    }
    
    // Accesseurs
    string getTitulaire() const { return titulaire; }
    int getNumero() const { return numeroCompte; }
    double getSolde() const { return solde; }
    
    void afficher() const {
        cout << "  [Compte #" << numeroCompte << " - " << titulaire 
             << "] Solde : " << fixed << setprecision(2) << solde << " DH" << endl;
    }
};


int main() {
    cout << "===== Simulation bancaire =====" << endl << endl;
    
    Compte compte("Hamza ID EL BAZ", 1001, 500.00);
    compte.afficher();
    cout << endl;
    
 
    cout << "--- Test 1 : Dépôt valide de 250 DH ---" << endl;
    try {
        compte.deposer(250.0);
    }
    catch (const BanqueException& e) {
        cout << "  ✗ " << e.what() << endl;
    }
    cout << endl;
    

    cout << "--- Test 2 : Retrait valide de 300 DH ---" << endl;
    try {
        compte.retirer(300.0);
    }
    catch (const BanqueException& e) {
        cout << "null " << e.what() << endl;
    }
    cout << endl;
    

    cout << "--- Test 3 : Depot invalide de -100 DH ---" << endl;
    try {
        compte.deposer(-100.0);
    }
    catch (const MontantInvalideException& e) {
        cout << " Exception MontantInvalide : " << e.what() << endl;
        cout << "  Montant refuse : " << e.getMontant() << " DH" << endl;
    }
    cout << endl;
    

    cout << "--- Test 4 : Retrait invalide de 0 DH ---" << endl;
    try {
        compte.retirer(0.0);
    }
    catch (const MontantInvalideException& e) {
        cout << "  ✗ Exception MontantInvalide : " << e.what() << endl;
    }
    cout << endl;
    

    cout << "--- Test 5 : Retrait de 5000 DH (solde 450 DH) ---" << endl;
    try {
        compte.retirer(5000.0);
    }
    catch (const SoldeInsuffisantException& e) {
        cout << "  Exception SoldeInsuffisant : " << e.what() << endl;
        cout << "   Solde actuel   : " << e.getSoldeActuel() << " DH" << endl;
        cout << "  Montant demandé : " << e.getMontantDemande() << " DH" << endl;
        cout << "   Manque          : " << e.getManque() << " DH" << endl;
    }
    cout << endl;
    

    cout << "--- Test 6 : catch multiples (depot de -50 DH) ---" << endl;
    try {
        compte.deposer(-50.0);
    }
    catch (const MontantInvalideException& e) {
        cout << "  [catch MontantInvalide] " << e.what() << endl;
    }
    catch (const SoldeInsuffisantException& e) {
        cout << "  [catch SoldeInsuffisant] " << e.what() << endl;
    }
    catch (const BanqueException& e) {
        cout << "  [catch BanqueException] " << e.what() << endl;
    }
    cout << endl;

    cout << "--- Test 7 : try-catch imbriques (operations en chaine) ---" << endl;
    try {
        cout << "  > Tentative : depot 100 DH puis retrait 2000 DH" << endl;
        try {
            compte.deposer(100.0);
            compte.retirer(2000.0);  
        }
        catch (const MontantInvalideException& e) {
            cout << "  [inner] Montant invalide : " << e.what() << endl;
        }
        catch (const SoldeInsuffisantException& e) {
            cout << "  [inner] Solde insuffisant : " << e.what() << endl;
            cout << "  [inner] → Annulation du dépôt pour coherence" << endl;
            throw;  // propage au catch externe
        }
    }
    catch (const BanqueException& e) {
        cout << "  [outer] Exception remontée : " << e.what() << endl;
    }
    cout << endl;
    

    cout << "--- Test 8 : Creation compte avec solde -200 DH ---" << endl;
    try {
        Compte c2("Test", 1002, -200.0);
    }
    catch (const MontantInvalideException& e) {
        cout << " Creation refusee : " << e.what() << endl;
    }
    cout << endl;
    
 
    cout << "===== Etat final du compte =====" << endl;
    compte.afficher();
    cout << endl << "===== Fin de la simulation =====" << endl;
    
    return 0;
}