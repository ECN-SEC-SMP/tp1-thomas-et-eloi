/**
 * @file lexique.cpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr) & Thomas Verron (thomas.verron@eleves.ec-nantes.fr)
 * @brief 
 * @version 0.1
 * @date 06-10-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "lexique.hpp"
#include "utilitaire.hpp"
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

/**
 * @brief Construct a new lexique::lexique object
 * 
 * @param n Name of the lexique
 * @param f Path to the file to read
 */
lexique::lexique(string n, string f)
{
    this->nom = n;
    string contenu;
    char * pch;
    vector<string> *ptr_mots = &this->mots;
    vector<int> *ptr_frequences = &this->frequences;

    vector<string>::iterator it_mots;

    if(!util::readFileIntoString(f, contenu)) {
        cerr << "Error reading file " << f << endl;
        return;
    }

    util::to_lower(contenu);

    pch = strtok(const_cast<char*>(contenu.c_str()), " ,.-");

    while (pch != NULL)
    {
        // Search for the word in the existing list
        it_mots = find(ptr_mots->begin(), ptr_mots->end(), pch);
        if (it_mots != ptr_mots->end())
        {
            // Word found, increment its frequency
            int index = distance(ptr_mots->begin(), it_mots);
            (*ptr_frequences)[index]++;
        }
        else
        {
            // Word not found, add it to the lexicon with frequency 1
            ptr_mots->push_back(string(pch));
            ptr_frequences->push_back(1);
        }

        pch = strtok(NULL, " ,.-");
    }

    cout << "Lexique " << this->nom << " créé avec " << this->mots.size() << " mots." << endl;

    return;
}

/**
 * @brief Destroy the lexique::lexique object
 * 
 */
lexique::~lexique()
{
    // Destructeur
    this->mots.clear();
    this->frequences.clear();
    return;
}