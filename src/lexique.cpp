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

    util::remove_punctuation(contenu);

    pch = strtok(const_cast<char*>(contenu.c_str()), " 0123456789\n\r\t");

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

        pch = strtok(NULL, " 0123456789\n\r\t");
    }

    return;
}

lexique::lexique(string n){
    this->nom = n;
    this->mots = vector<string>();
    this->frequences = vector<int>();
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
    const int largeur = 40; // largeur de base
    for(string mot : mots){
        vector<string>::iterator it = find(mots.begin(), mots.end(), mot);
        int espace = 60 - mot.size();
        Fichier << mot << string(espace,' ') << ":       " << frequences[it-mots.begin()] << endl;
    }
    Fichier.close();
}


/**
 * @brief Return the number of iteration of a selected word
 * 
 * @param mot Selected word
 * @return int 
 */
int lexique::getFrequenceFromWord(string mot) const {
    vector<string>::const_iterator it = find(mots.begin(), mots.end(), mot);
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
    vector<string>::iterator it = find(mots.begin(), mots.end(), mot);
    if(it != mots.end()) mots.erase(it);
}

/**
 * @brief Display in terminal the number of words
 * 
 */
void lexique::displayNbWords(){
    cout << mots.size();
}

lexique lexique::operator+(const lexique& autre) const {
    lexique nouveauLexique("Nouveau Lexique");
    nouveauLexique.mots = this->mots;
    nouveauLexique.frequences = this->frequences;

    for(string mot : autre.mots){
        vector<string>::iterator it = find(nouveauLexique.mots.begin(), nouveauLexique.mots.end(), mot);
        if(it != nouveauLexique.mots.end()){
            size_t index = distance(nouveauLexique.mots.begin(), it);
            nouveauLexique.frequences[index] += autre.getFrequenceFromWord(mot);
        } else {
            // Le mot n'existe pas, on l'ajoute
            nouveauLexique.mots.push_back(mot);
            nouveauLexique.frequences.push_back(autre.getFrequenceFromWord(mot));
        }
    }

    return nouveauLexique;
}

lexique lexique::operator-(const lexique& autre) const {
    lexique nouveauLexique("Nouveau Lexique");
    nouveauLexique.mots = this->mots;
    nouveauLexique.frequences = this->frequences;

    for(string mot : autre.mots){
        vector<string>::iterator it = find(nouveauLexique.mots.begin(), nouveauLexique.mots.end(), mot);
        if(it != nouveauLexique.mots.end()){
            size_t index = distance(nouveauLexique.mots.begin(), it);
            int nouvelleFrequence = nouveauLexique.frequences[index] - autre.getFrequenceFromWord(mot);
            if(nouvelleFrequence > 0){
                nouveauLexique.frequences[index] = nouvelleFrequence;
            } else {
                // La fréquence devient nulle ou négative, on supprime le mot
                nouveauLexique.mots.erase(it);
                nouveauLexique.frequences.erase(nouveauLexique.frequences.begin() + index);
            }
        }
    }

    return nouveauLexique;
}

/**
 * @brief overload operator << to display lexique in terminal
 * 
 * @param os Out-put stream
 * @param lexique selected lexique 
 * @return ostream& 
 */
ostream& operator<<(ostream& os, const lexique& lexique){
    for(string mot : lexique.mots){
        vector<string>::const_iterator it = find(lexique.mots.begin(), lexique.mots.end(), mot);
        os << mot << " : " << lexique.frequences[it-lexique.mots.begin()] << endl;
    }
    return os;
}
    


