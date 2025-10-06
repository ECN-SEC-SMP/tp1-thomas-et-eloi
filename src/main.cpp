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
#include "lexique.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
    cout << "TP1 - Manipulation of lexical data" << endl;

    lexique lexLesMiserables("Les Miserables", "assets/lesMiserables_A.txt");

    lexique lexNDDP("Notre Dame de Paris", "assets/notreDameDeParis_A.txt");

    cout << "Lexique of The Miserables well created and contains ";
    lexLesMiserables.displayNbWords();
    cout << " words." << endl;

    lexLesMiserables.saveLexique("assets/lexique_lesMiserables.txt");

    lexNDDP.saveLexique("assets/lexique_notreDameDeParis.txt");

    cout << lexLesMiserables << endl;

    cout << "The word 'the' appears " << lexLesMiserables.getFrequenceFromWord("the") << " times in Les Miserables." << endl;

    lexLesMiserables.deleteWord("the");

    cout << "After deleting 'the', it now appears " << lexLesMiserables.getFrequenceFromWord("the") << " times in Les Miserables." << endl;

    return 0;
}