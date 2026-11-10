#include <iostream>
#include <exception>
#include <string>

using namespace std;


class StockInsuffisantException : public exception {
private:
    string message;
    int stockDisponible;
    int quantiteDemandee;

public:
    StockInsuffisantException(int stock, int demande)
        : stockDisponible(stock), quantiteDemandee(demande) {
        
        message = "Stock insuffisant ! Disponible : " 
                + to_string(stockDisponible) 
                + " | Demandé : " 
                + to_string(quantiteDemandee);
    }
    
    const char* what() const noexcept override {
        return message.c_str();
    }
    
    // Accesseurs (bonus)
    int getStockDisponible() const { return stockDisponible; }
    int getQuantiteDemandee() const { return quantiteDemandee; }
};


// ============================================
class Produit {
private:
    string nom;
    double prix;
    int stock;

public:
    // Constructeur
    Produit(const string& nom, double prix, int stockInitial)
        : nom(nom), prix(prix), stock(stockInitial) {
        if (stockInitial < 0) {
            throw invalid_argument("Le stock initial ne peut pas etre negatif !");
        }
    }
    
    // Méthode vendre avec gestion d'exception
    void vendre(int quantite) {
        if (quantite <= 0) {
            throw invalid_argument("La quantite à vendre doit etre positive !");
        }
        
        if (quantite > stock) {
            throw StockInsuffisantException(stock, quantite);
        }
        
        stock -= quantite;
        cout << "  Vente reussie : " << quantite 
             << " unite(s) de " << nom << endl;
    }
    
    // Accesseurs
    string getNom() const { return nom; }
    int getStock() const { return stock; }
    double getPrix() const { return prix; }
    
    // Affichage
    void afficher() const {
        cout << "  [Produit] " << nom 
             << " | Prix : " << prix << " DH"
             << " | Stock : " << stock << endl;
    }
};


// ============================================
int main() {
    cout << "===== Gestion de stock de produits =====" << endl << endl;
    
    // Création d'un produit
    Produit p1("Clavier mecanique", 350.0, 10);
    cout << "etat initial :" << endl;
    p1.afficher();
    cout << endl;
    
    // Test 1 : vente valide
    cout << "Test 1 : Vendre 3 claviers" << endl;
    try {
        p1.vendre(3);
    }
    catch (const StockInsuffisantException& e) {
        cout << "  Erreur : " << e.what() << endl;
    }
    p1.afficher();
    cout << endl;
    
    // Test 2 : vente valide (exactement le stock restant)
    cout << "Test 2 : Vendre 7 claviers" << endl;
    try {
        p1.vendre(7);
    }
    catch (const StockInsuffisantException& e) {
        cout << "  ✗ Erreur : " << e.what() << endl;
    }
    p1.afficher();
    cout << endl;
    
    // Test 3 : vente invalide (stock vide)
    cout << "Test 3 : Vendre 5 claviers (stock epuise)" << endl;
    try {
        p1.vendre(5);
    }
    catch (const StockInsuffisantException& e) {
        cout << "  ✗ Exception interceptee : " << e.what() << endl;
        cout << "    → Stock disponible : " << e.getStockDisponible() << endl;
        cout << "    → Quantite demandee : " << e.getQuantiteDemandee() << endl;
    }
    p1.afficher();
    cout << endl;
    
    // Test 4 : quantité invalide
    cout << "Test 4 : Vendre -2 unites (quantite invalide)" << endl;
    try {
        p1.vendre(-2);
    }
    catch (const invalid_argument& e) {
        cout << " Exception interceptee : " << e.what() << endl;
    }
    cout << endl;
    
    // Test 5 : nouveau produit avec stock partiel
    cout << "Test 5 : Nouveau produit - Souris gamer (stock : 4)" << endl;
    Produit p2("Souris gamer", 120.0, 4);
    p2.afficher();
    
    cout << "  Tentative de vendre 10 souris :" << endl;
    try {
        p2.vendre(10);
    }
    catch (const StockInsuffisantException& e) {
        cout << " Exception interceptee : " << e.what() << endl;
    }
    cout << endl;
    
    // Test 6 : tentative de création avec stock négatif
    cout << "Test 6 : Creation produit avec stock negatif" << endl;
    try {
        Produit p3("Ecran", 1500.0, -5);
    }
    catch (const invalid_argument& e) {
        cout << " Exception interceptee : " << e.what() << endl;
    }
    
    cout << endl << "===== Fin des tests =====" << endl;
    
    return 0;
}