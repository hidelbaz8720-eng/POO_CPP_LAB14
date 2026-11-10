#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;
class FichierException : public runtime_error {
public:
    explicit FichierException(const string& msg) 
        : runtime_error(msg) {}
};

void lireFichier(const string& nomFichier) {
    // 1. Ouvrir le fichier en lecture
    ifstream fichier(nomFichier);
    
    // 2. Vérifier que l'ouverture a réussi
    if (!fichier.is_open()) {
        throw FichierException(
            "Impossible d'ouvrir le fichier : \"" + nomFichier + "\""
        );
    }
    
    cout << "===== Contenu du fichier : " << nomFichier << " =====" << endl;
    cout << endl;
    
    // 3. Lecture ligne par ligne
    string ligne;
    int numeroLigne = 1;
    int nbLignes = 0;
    
    while (getline(fichier, ligne)) {
        cout << "  Ligne " << numeroLigne << " : " << ligne << endl;
        numeroLigne++;
        nbLignes++;
    }
    
    // 4. Vérifier qu'il n'y a pas eu d'erreur pendant la lecture
    if (fichier.bad()) {
        throw FichierException(
            "Erreur materielle pendant la lecture du fichier : \"" 
            + nomFichier + "\""
        );
    }
    
    cout << endl;
    cout << "===== Fin du fichier (" << nbLignes << " ligne(s)) =====" << endl;
    

    fichier.close();
}


int main() {
    // Liste des fichiers à tester
    string fichiers[] = {
        "exemple.txt",          // Fichier existant (à créer au préalable)
        "inexistant.txt",       // Fichier absent
        "/dossier/faux.txt"     // Chemin invalide
    };
    
    int nbFichiers = sizeof(fichiers) / sizeof(fichiers[0]);
    
    cout << "===== Lecture de fichiers avec gestion d'erreurs =====" << endl << endl;
    
    for (int i = 0; i < nbFichiers; i++) {
        cout << "--- Test " << (i + 1) << " ---" << endl;
        
        try {
            lireFichier(fichiers[i]);
        }
        catch (const FichierException& e) {
            cout << "Erreur fichier : " << e.what() << endl;
            cout << "Verifiez que le fichier existe et est accessible." << endl;
        }
        catch (const exception& e) {
            cout << " Erreur inattendue : " << e.what() << endl;
        }
        
        cout << endl;
    }
    
    cout << "===== Fin du programme =====" << endl;
    
    return 0;
}