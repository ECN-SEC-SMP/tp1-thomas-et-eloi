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
    cout << "TP1 - Gestion de lexiques" << endl;

    lexique lexLesMiserables("Les Miserables", "assets/lesMiserables_A.txt");

    lexique lexNDDP("Notre Dame de Paris", "assets/notreDameDeParis_A.txt");

    return 0;
}