
# TP1 - Création et manipulation d'un lexique

- SEC 2
- Eloi Tourangin - eloi.tourangin@eleves.ec-nantes.fr
- Thomas Verron - thomas.verron@eleves.ec-nantes.fr

Ce projet implémente une classe `lexique` en C++ qui gère un dictionnaire de mots avec leur nombre d'occurrences. Voici une description détaillée de chaque fonction et de son fonctionnement.

## Structure de la classe

```cpp
class lexique {
private:
    string nom;                  // Nom du lexique
    vector<string> mots;         // Liste des mots uniques
    vector<int> frequences;      // Fréquences correspondantes
};
```

La classe utilise deux vecteurs parallèles pour stocker les mots et leurs fréquences. Pour chaque mot à l'index i dans `mots`, sa fréquence est stockée à l'index i dans `frequences`.

## Détail des fonctions et leurs implémentations

### 1. Constructeur avec fichier

```cpp
lexique::lexique(string n, string f)
```

Ce constructeur crée un lexique à partir d'un fichier texte. Voici son fonctionnement détaillé :

```cpp
this->nom = n;
string contenu;
if(!util::readFileIntoString(f, contenu)) {
    cerr << "Error reading file " << f << endl;
    return;
}

util::to_lower(contenu);
```

1. Initialisation :
   - Assigne le nom du lexique
   - Lit le fichier complet avec `readFileIntoString`
   - Convertit tout en minuscules

```cpp
pch = strtok(const_cast<char*>(contenu.c_str()), 
            " \"!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~0123456789\n\r\t");

while (pch != NULL) {
    string tmp = string(pch);
    util::remove_punctuation(tmp);
    pch = const_cast<char*>(tmp.c_str());

    it_mots = find(ptr_mots->begin(), ptr_mots->end(), pch);
    
    if (it_mots != ptr_mots->end()) {
        int index = distance(ptr_mots->begin(), it_mots);
        (*ptr_frequences)[index]++;
    } else {
        ptr_mots->push_back(string(pch));
        ptr_frequences->push_back(1);
    }

    pch = strtok(NULL, " \"!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~0123456789\n\r\t");
}
```

2. Traitement du texte :
   - Découpe le texte en mots avec `strtok`
   - Pour chaque mot :
     * Nettoie la ponctuation restante
     * Cherche si le mot existe déjà
     * Si oui : incrémente sa fréquence
     * Si non : ajoute le mot avec fréquence 1

### 2. Constructeur lexique vide

```cpp
lexique::lexique(string n) {
    this->nom = n;
    this->mots = vector<string>();
    this->frequences = vector<int>();
}
```

Crée un lexique vide :
- Initialise le nom
- Crée des vecteurs vides pour les mots et fréquences

### 3. Destructeur

```cpp
lexique::~lexique() {
    this->mots.clear();
    this->frequences.clear();
    return;
}
```

Nettoie la mémoire en vidant les vecteurs de mots et fréquences.

### 4. Sauvegarde du lexique

```cpp
void lexique::saveLexique(string f) {
    ofstream Fichier(f);
    const int largeur = 40;
    for(string mot : mots) {
        vector<string>::iterator it = find(mots.begin(), mots.end(), mot);
        int espace = 60 - mot.size();
        Fichier << mot << string(espace,' ') << ":       " 
                << frequences[it-mots.begin()] << endl;
    }
    Fichier.close();
}
```

Fonctionnement :
1. Ouvre un fichier en écriture
2. Pour chaque mot :
   - Calcule l'espacement pour un alignement visuel
   - Écrit le mot, des espaces de formatage, et sa fréquence
3. Ferme le fichier

Note : L'utilisation de `find` à chaque itération n'est pas optimale puisque nous itérons déjà sur les mots dans l'ordre.
Une amélioration serait d'utiliser directement l'index de la boucle.

### 5. Recherche de fréquence

```cpp
int lexique::getFrequenceFromWord(string mot) const {
    vector<string>::const_iterator it = find(mots.begin(), mots.end(), mot);
    if(it != mots.end()) {
        return frequences[it-mots.begin()];
    }
    return 0;
}
```

Fonctionnement :
1. Cherche le mot dans le vecteur avec `find`
2. Si trouvé : retourne sa fréquence en utilisant la distance depuis le début
3. Si non trouvé : retourne 0

### 6. Suppression d'un mot

```cpp
void lexique::deleteWord(string mot) {
    vector<string>::iterator it = find(mots.begin(), mots.end(), mot);
    if(it != mots.end()) mots.erase(it);
}
```

Fonctionnement :
1. Cherche le mot dans le vecteur
2. Si trouvé : le supprime
3. Si non trouvé : ne fait rien

Note : Cette implémentation ne supprime que le mot, pas sa fréquence associée.

### 7. Affichage du nombre de mots

```cpp
void lexique::displayNbWords() {
    cout << mots.size();
}
```

Affiche simplement la taille du vecteur de mots.

### 8. Opérateur de fusion (+)

```cpp
lexique lexique::operator+(const lexique& autre) const {
    lexique nouveauLexique("Nouveau Lexique");
    nouveauLexique.mots = this->mots;
    nouveauLexique.frequences = this->frequences;

    for(string mot : autre.mots) {
        vector<string>::iterator it = find(nouveauLexique.mots.begin(), 
                                         nouveauLexique.mots.end(), mot);
        if(it != nouveauLexique.mots.end()) {
            size_t index = distance(nouveauLexique.mots.begin(), it);
            nouveauLexique.frequences[index] += autre.getFrequenceFromWord(mot);
        } else {
            nouveauLexique.mots.push_back(mot);
            nouveauLexique.frequences.push_back(autre.getFrequenceFromWord(mot));
        }
    }
    return nouveauLexique;
}
```

Fonctionnement :
1. Crée un nouveau lexique et copie les mots et fréquences du premier lexique
2. Pour chaque mot du second lexique :
   - Si le mot existe déjà : additionne les fréquences
   - Si le mot n'existe pas : l'ajoute avec sa fréquence

### 9. Opérateur de différence (-)

```cpp
lexique lexique::operator-(const lexique& autre) const {
    lexique nouveauLexique("Nouveau Lexique");
    nouveauLexique.mots = this->mots;
    nouveauLexique.frequences = this->frequences;

    for(string mot : autre.mots) {
        vector<string>::iterator it = find(nouveauLexique.mots.begin(), 
                                         nouveauLexique.mots.end(), mot);
        if(it != nouveauLexique.mots.end()) {
            size_t index = distance(nouveauLexique.mots.begin(), it);
            int nouvelleFrequence = nouveauLexique.frequences[index] 
                                   - autre.getFrequenceFromWord(mot);
            if(nouvelleFrequence > 0) {
                nouveauLexique.frequences[index] = nouvelleFrequence;
            } else {
                nouveauLexique.mots.erase(it);
                nouveauLexique.frequences.erase(
                    nouveauLexique.frequences.begin() + index);
            }
        }
    }
    return nouveauLexique;
}
```

Fonctionnement :
1. Crée un nouveau lexique et copie les mots/fréquences du premier
2. Pour chaque mot du second lexique :
   - Si le mot existe dans le premier :
     * Soustrait la fréquence
     * Si résultat > 0 : met à jour la fréquence
     * Si résultat ≤ 0 : supprime le mot et sa fréquence
   - Si le mot n'existe pas : passe au suivant

### 10. Opérateur d'affichage (<<)

```cpp
ostream& operator<<(ostream& os, const lexique& lexique) {
    for(string mot : lexique.mots) {
        vector<string>::const_iterator it = find(lexique.mots.begin(), 
                                               lexique.mots.end(), mot);
        os << mot << " : " << lexique.frequences[it-lexique.mots.begin()] << endl;
    }
    return os;
}
```

Fonctionnement :
1. Pour chaque mot :
   - Trouve sa position dans le vecteur
   - Affiche le mot et sa fréquence
2. Retourne le flux pour permettre le chaînage

Note : Comme pour `saveLexique`, l'utilisation de `find` pourrait être évitée.

## Complexité et performances

La structure actuelle utilise deux vecteurs parallèles et `std::find` pour les recherches, ce qui donne les complexités suivantes :

- Recherche d'un mot : O(N) via `std::find`
- Ajout d'un nouveau mot : O(N) pour vérifier l'unicité + O(1) pour l'insertion
- Fusion de lexiques : O(M*N) où M et N sont les tailles des lexiques
- Différence de lexiques : O(M*N)

Une amélioration majeure serait d'utiliser `unordered_map<string,int>` pour obtenir :
- Recherche : O(1) en moyenne
- Ajout : O(1) en moyenne
- Fusion/Différence : O(M + N)

## Exemple d'utilisation

```cpp
int main() {
    // Création des lexiques
    lexique lex1("Les Miserables", "assets/lesMiserables_A.txt");
    lexique lex2("Notre Dame", "assets/notreDameDeParis_A.txt");
    
    // Sauvegarde
    lex1.saveLexique("assets/lexique_1.txt");
    lex2.saveLexique("assets/lexique_2.txt");
    
    // Opérations
    cout << "Fréquence de 'the': " << lex1.getFrequenceFromWord("the") << endl;
    
    // Fusion
    lexique fusion = lex1 + lex2;
    fusion.saveLexique("assets/fusion.txt");
    
    // Différence
    lexique diff = fusion - lex2;
    diff.saveLexique("assets/difference.txt");
    
    return 0;
}
```

## Compilation et tests

```bash
# Compiler
make

# Exécuter
./build/main.out
```

### Tests rapides

1. Test basique :
```cpp
lexique lex("test", "input.txt");  // contenu : "a a b c! a. b"
// Attendu : a->3, b->2, c->1
```

2. Test de fusion :
```cpp
lexique lex1("test1", "input1.txt");  // contenu : "a b a"
lexique lex2("test2", "input2.txt");  // contenu : "a c"
lexique fusion = lex1 + lex2;
// Attendu : a->3, b->1, c->1
```

3. Test de différence :
```cpp
lexique diff = lex1 - lex2;
// Attendu : a->1, b->1 (car 2-1=1 pour 'a')
```

## Améliorations possibles

1. Performance :
   - Utiliser `unordered_map<string,int>`
   - Éviter les `find` redondants dans les opérations
   - Optimiser la gestion mémoire

2. Robustesse :
   - Meilleure gestion des erreurs
   - Validation des entrées
   - Tests unitaires complets

3. Fonctionnalités :
   - Ajout de `operator+=` et `operator-=`
   - Support UTF-8 complet
   - Statistiques avancées (mots les plus fréquents, etc.)

4. Interface :
   - Méthodes pour trier par fréquence
   - Export dans différents formats
   - Interface de requête plus riche

