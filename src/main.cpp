/**
 * @file main.cpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr) & Thomas Verron (thomas.verron@eleves.ec-nantes.fr)
 * @brief 
 * @version 0.1
 * @date 06-10-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "utilitaire.hpp"
#include "lexique_ligne.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    cout << "=== TP1 - Tests complets des classes lexique et lexique_ligne ===" << endl << endl;

    // Test 1: Constructeur vide de lexique
    cout << "Test 1: Création d'un lexique vide" << endl;
    lexique lexVide("Lexique Vide");
    cout << "Nombre de mots dans le lexique vide: ";
    lexVide.displayNbWords();
    cout << endl << endl;

    // Test 2: Construction et statistiques de base
    cout << "Test 2: Construction depuis Les Misérables" << endl;
    lexique lexLesMiserables("Les Miserables", "assets/lesMiserables_A.txt");
    cout << "Nombre de mots dans Les Misérables: ";
    lexLesMiserables.displayNbWords();
    cout << endl;
    
    lexLesMiserables.saveLexique("assets/lexique_lesMiserables.txt");
    cout << "Lexique sauvegardé dans assets/lexique_lesMiserables.txt" << endl << endl;

    // Test 3: Deuxième lexique et opérations
    cout << "Test 3: Construction et opérations avec Notre Dame de Paris" << endl;
    lexique lexNDDP("Notre Dame de Paris", "assets/notreDameDeParis_A.txt");
    cout << "Nombre de mots dans Notre Dame de Paris: ";
    lexNDDP.displayNbWords();
    cout << endl;

    // Test 4: Opérateur de fusion
    cout << "Test 4: Test de l'opérateur de fusion" << endl;
    lexique lexCombined = lexLesMiserables + lexNDDP;
    cout << "Nombre de mots après fusion: ";
    lexCombined.displayNbWords();
    cout << endl;
    lexCombined.saveLexique("assets/lexique_combined.txt");
    cout << "Lexique fusionné sauvegardé" << endl << endl;

    // Test 5: Opérateur de différence
    cout << "Test 5: Test de l'opérateur de différence" << endl;
    lexique lexDiff = lexCombined - lexNDDP;
    cout << "Nombre de mots après soustraction: ";
    lexDiff.displayNbWords();
    cout << endl;
    lexDiff.saveLexique("assets/lexique_difference.txt");
    cout << "Lexique différence sauvegardé" << endl << endl;

    // Test 6: Recherche et suppression
    cout << "Test 6: Test de recherche et suppression" << endl;
    string motTest = "the";
    cout << "Le mot '" << motTest << "' apparaît " 
         << lexLesMiserables.getFrequenceFromWord(motTest) 
         << " fois dans Les Misérables" << endl;
    
    lexLesMiserables.deleteWord(motTest);
    cout << "Après suppression, le mot apparaît " 
         << lexLesMiserables.getFrequenceFromWord(motTest) 
         << " fois" << endl << endl;

    // Test 7: Opérateur d'affichage
    cout << "Test 7: Test de l'opérateur d'affichage" << endl;
    lexique lexPetit("Test", "assets/small_test.txt");
    cout << "Contenu du petit lexique:\n" << lexPetit << endl;

    cout << "=== Tests de la classe lexique_ligne ===" << endl << endl;

    // Test 8: Construction lexique_ligne
    cout << "Test 8: Construction d'un lexique_ligne" << endl;
    lexique_ligne lexLigne("Les Misérables - avec lignes", "assets/lesMiserables_A.txt");
    
    // Test 9: Recherche de mots avec différents cas
    cout << "Test 9: Tests de displayLinesFromWord" << endl;
    cout << "a) Mot apparaissant plusieurs fois:" << endl;
    lexLigne.displayLinesFromWord("included");
    
    cout << "b) Mot apparaissant une seule fois:" << endl;
    lexLigne.displayLinesFromWord("unique");
    
    cout << "c) Mot inexistant:" << endl;
    lexLigne.displayLinesFromWord("xyzabc123");

    // Test 10: Héritage - utilisation des méthodes de la classe mère
    cout << "\nTest 10: Test d'héritage" << endl;
    cout << "Nombre de mots dans le lexique_ligne: ";
    lexLigne.displayNbWords();
    cout << endl;
    cout << "Fréquence du mot 'included': " 
         << lexLigne.getFrequenceFromWord("included") << endl;

    cout << "\n=== Fin des tests ===" << endl;
    return 0;
}