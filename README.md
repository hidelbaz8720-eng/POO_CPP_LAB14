# TP 14 : Gestion des Exceptions en C++

**Cours** : Programmation orientée objet : C++  
**Plateforme** : MLIAEdu  
**Auteur** : HAMZA ID EL BAZ  




##  Présentation

Ce TP couvre la **gestion des exceptions** en C++ à travers 4 exercices progressifs :

| # | Exercice | Concepts clés |
|---|----------|---------------|
| 1 | Division sécurisée | `try/catch` basique, `runtime_error` |
| 2 | Stock de produits | Exception personnalisée avec attributs |
| 3 | Lecture de fichier | `ifstream`, gestion I/O, `bad()` |
| 4 | Simulation bancaire | Hiérarchie d'exceptions, catch multiples/imbriqués |

---



## 🔹 Exercice 1 : Division sécurisée

**Objectif** : Intercepter une division par zéro avec `try-catch`.
<img width="1366" height="768" alt="ex1" src="https://github.com/user-attachments/assets/5ab74a53-03a4-403b-ae80-c40485db7210" />


##  Exercice 2 : Gestion d'un stock de produits

**Objectif** : Créer et manipuler une **exception personnalisée**.
<img width="1366" height="768" alt="ex2" src="https://github.com/user-attachments/assets/e29ce184-5050-4773-a435-c70b3fd15a26" />


### Points clés

- **Héritage de `std::exception`** + `what()` en `noexcept override`
- **Attributs métier** dans l'exception (`stockDisponible`, `quantiteDemandee`)
- **Validation dans le constructeur** (`stockInitial >= 0`)
- **Deux types d'exceptions** : `invalid_argument` et `StockInsuffisantException`



##  Exercice 3 : Lecture d'un fichier avec gestion d'erreurs

**Objectif** : Gérer les erreurs d'ouverture et de lecture avec `ifstream`.

<img width="1366" height="768" alt="ex3" src="https://github.com/user-attachments/assets/0e08c75a-e342-4a3a-b6dc-f9a95659c183" />


### Points clés

- **`ifstream` ne lève pas d'exception par défaut** → toujours vérifier `is_open()`
- **`getline()`** lit ligne par ligne en préservant les espaces
- **`bad()`** détecte les erreurs matérielles après lecture
- **`FichierException : public runtime_error`** simplifie l'implémentation de `what()`
- **`explicit`** empêche les conversions implicites

---

##  Exercice 4 : Simulation bancaire avec plusieurs exceptions

**Objectif** : Maîtriser **plusieurs types d'exceptions** avec catch multiples et imbriqués.
<img width="1366" height="768" alt="ex4_1" src="https://github.com/user-attachments/assets/2ed028ca-59ab-440f-b173-dbbfce231dab" />
<img width="1366" height="768" alt="ex4_2" src="https://github.com/user-attachments/assets/f6bf797c-8b47-46de-afc8-50dd7efcf3a6" />



### Points clés

- **Hiérarchie** : `BanqueException` → `MontantInvalideException`, `SoldeInsuffisantException`
- **Attributs métier** pour diagnostic (`getManque()`, `getMontant()`)
- **`catch` multiples** : du spécifique au générique
- **`try-catch` imbriqués** avec `throw;` pour propagation
- **Validation constructeur** : refus d'un solde initial négatif

---

##  Compilation et exécution

### Avec g++
# Exécution
./exercice1
./exercice2
./exercice3
./exercice4
```



##  Conclusion

Ce TP a permis de couvrir **toute la chaîne de la gestion d'exceptions** en C++ :

- `try / catch / throw` basiques
-  Exceptions personnalisées enrichies
-  Gestion des erreurs d'entrée/sortie
-  Hiérarchie et polymorphisme d'exceptions
- Catch multiples et imbriqués
-  Propagation via `throw;`

**Prochaine étape** : QCM du TP 14, puis TP sur l'**héritage et le polymorphisme**.

