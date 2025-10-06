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
#include <bits/stdc++.h>
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

/**
 * @brief Save the lexique in a selected file
 * 
 * @param f Selected file's path
 */
void lexique::saveLexique(string f){
    ofstream Fichier(f);
    for(char mot : mots){
        vector<char>::iterator it = find(mots.begin(), mots.end(), mot);
        Fichier << "Mot : " << mot << "/ Nombre d'itération : " << frequences[it-mots.begin()] << endl;
    }
    Fichier.close();
}


/**
 * @brief Return the number of iteration of a selected word
 * 
 * @param mot Selected word
 * @return int 
 */
int lexique::getFrequenceFromWord(string mot){
    vector<char>::iterator it = find(mots.begin(), mots.end(), mot);
    if(it != mots.end()){
        return frequences[it-mots.begin()];
    }
    return 0;
}


/**
 * @brief Delete a selected word from the lexique
 * 
 * @param mot selected word
 */
void lexique::deleteWord(string mot){
    vector<char>::iterator it = find(mots.begin(), mots.end(), mot);
    if(it != mots.end()) mots.erase(it);
}

/**
 * @brief Display in terminal the number of words
 * 
 */
void lexique::displayNbWords(){
    cout << mots.size() << endl;
}

/**
 * @brief overload operator << to display lexique in terminal
 * 
 * @param os Out-put stream
 * @param lexique selected lexique 
 * @return ostream& 
 */
ostream& operator<<(ostream& os, const lexique& lexique){
    for(char mot : lexique.mots){
        vector<char>::const_iterator it = find(lexique.mots.begin(), lexique.mots.end(), mot);
        os << "Mots : " << mot << "/ Nombre d'itération : " << lexique.frequences[it-lexique.mots.begin()] << endl;
    }
    return os;
}
    


