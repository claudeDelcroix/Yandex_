//meilleure solution tres optimise avec une recherche binaire
#include <iostream>
#include <vector>
#include <algorithm> // Pour std::lower_bound
#include <iterator>  // Pour std::distance

// Utiliser 'long long' pour éviter les dépassements
typedef long long ll;

struct TaxBracket {
    int power;
    int rate; 
};

/**
 * Comparateur personnalisé pour std::lower_bound.
 * Il compare une structure TaxBracket avec une puissance (entier).
 * Renvoie 'true' si la puissance de la tranche est inférieure à la puissance de la voiture.
 */
bool compareBracketVsPower(const TaxBracket& bracket, int car_power) {
    return bracket.power < car_power;
}

int main() {
    // Optimisation des Entrées/Sorties
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<TaxBracket> brackets(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> brackets[i].power >> brackets[i].rate;
    }

    int m;
    std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        int car_power;
        std::cin >> car_power;
        
        ll tax = 0;

        // --- Logique optimisée avec std::lower_bound O(log n) ---

        // std::lower_bound trouve le premier élément qui n'est PAS inférieur
        // à car_power.
        // On utilise notre comparateur personnalisé.
        auto it = std::lower_bound(
            brackets.begin(), 
            brackets.end(), 
            car_power, 
            compareBracketVsPower
        );

        // On calcule l'index de l'itérateur trouvé
        int idx = std::distance(brackets.begin(), it);

        if (idx == 0) {
            // Cas 1: car_power <= brackets[0].power
            // La puissance est dans la première tranche (ou avant).
            // L'énoncé n'étant pas clair, on suppose 0.
            tax = 0; 
        } 
        else if (idx == n && car_power > brackets[n-1].power) {
            // Cas 2: car_power est > à la puissance maximale (brackets[n-1].power)
            // L'itérateur 'it' est égal à 'brackets.end()'.
            // On applique le taux maximal (celui de la dernière tranche).
            tax = (ll)car_power * brackets[n - 1].rate;
        }
        else {
            // Cas 3: La puissance est dans une tranche (P_j, P_{j+1}]
            // 'idx' est l'index de P_{j+1}.
            // La tranche est (brackets[idx-1].power, brackets[idx].power]
            // Le taux à appliquer est celui de l'index 'idx - 1'.
            tax = (ll)car_power * brackets[idx - 1].rate;
        }
        
        std::cout << tax << "\n";
    }

    return 0;
}

//optimisation avant recherche binaire 
#include <iostream>
#include <vector>

// Utiliser 'long long' pour éviter les dépassements
// lors de la multiplication (puissance * taux)
typedef long long ll;

// 'price' est un 'taux', nommons-le plus clairement
struct TaxBracket {
    int power;
    int rate; 
};

int main() {
    // --- Optimisation des Entrées/Sorties ---
    // Essentiel pour les problèmes de programmation compétitive
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<TaxBracket> brackets(n);
    
    // Lire les tranches d'imposition
    // On suppose qu'elles sont triées par 'power', comme le suggère l'énoncé (i et i+1)
    for (int i = 0; i < n; i++) {
        std::cin >> brackets[i].power >> brackets[i].rate;
    }

    int m;
    std::cin >> m;
    
    // On n'a pas besoin de stocker toutes les voitures,
    // on peut les traiter une par une.
    for (int i = 0; i < m; i++) {
        int car_power;
        std::cin >> car_power;
        
        ll tax = 0; // La taxe calculée
        bool found_tax = false;

        // --- Logique corrigée et structurée ---

        // Cas 1: Puissance <= au premier seuil (P_0)
        // C'est le cas que votre code manquait. L'énoncé n'est pas clair,
        // mais on suppose logiquement que la taxe est 0.
        if (car_power <= brackets[0].power) {
            tax = 0; // Ou `(ll)car_power * 0`
            found_tax = true;
        } 
        // Cas 2: Puissance > au dernier seuil (P_{n-1})
        // Règle de l'énoncé: "strictement больше максимальной"
        else if (car_power > brackets[n - 1].power) {
            tax = (ll)car_power * brackets[n - 1].rate;
            found_tax = true;
        } 
        // Cas 3: La puissance est dans les tranches [ (P_0, P_1], ..., (P_{n-2}, P_{n-1}] ]
        else {
            // On cherche la tranche (P_j, P_{j+1}]
            // Taux appliqué : R_j
            for (int j = 0; j < n - 1; j++) {
                if (car_power > brackets[j].power && car_power <= brackets[j + 1].power) {
                    tax = (ll)car_power * brackets[j].rate;
                    found_tax = true;
                    // Optimisation: on a trouvé la tranche,
                    // inutile de continuer la boucle.
                    break; 
                }
            }
        }
        
        // Imprimer le résultat pour cette voiture
        // Utiliser "\n" est plus rapide que std::endl
        std::cout << tax << "\n";
    }

    return 0;
}

//premiere approche
#include <iostream>
#include <vector>

typedef struct taxe taxe;
struct taxe {
    int power;
    int price;
};

int main() {
    int n;
    std::cin >> n;
    int max = -1,max_price = 0;
    std::vector<taxe> taxes(n);
    for (int i = 0; i < n; i++) {
        std::cin >> taxes[i].power;
        std::cin >> taxes[i].price;
        if (max < taxes[i].power) {
            max = taxes[i].power;
            max_price = taxes[i].price;
        }
    }

    int m;
    std::cin >> m;
    std::vector<int> car(m);
    for (int i = 0; i < m; i++) {
        std::cin >> car[i];
    }
    std::vector<int> result_price;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (car[i] > taxes[j - 1].power && car[i] <= taxes[j].power) {
                std::cout<<"Debug : car["<<i<<"] = "<<car[i]<<" power = "<<taxes[j-1].power<<std::endl;
                std::cout<<"price : "<<taxes[j-1].price<<std::endl;
                std::cout<<"price : "<<car[i]*taxes[j-1].price<<std::endl;
                result_price.push_back(car[i]*taxes[j-1].price);
                break;
            }
        }
        if (car[i] >= max) {
            result_price.push_back(car[i]*max_price);
        }
    }

    for (const auto& price : result_price) {
        std::cout << price <<std::endl;
    }

    return 0;
}
