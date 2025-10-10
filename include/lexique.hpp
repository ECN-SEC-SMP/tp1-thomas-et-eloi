/**
 * @file lexique.hpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr) & Thomas Verron (thomas.verron@eleves.ec-nantes.fr)
 * @brief 
 * @version 0.1
 * @date 06-10-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class lexique
{
protected:
   string nom;
   vector<string> mots;
   vector<int> frequences;
public:
    lexique(string n, string f);
    lexique(string n);
    ~lexique();
    void saveLexique(string f);
    int getFrequenceFromWord(string mot) const;
    void deleteWord(string mot);
    void displayNbWords();
    
    lexique operator+(const lexique& autre) const;
    lexique operator-(const lexique& autre) const;
    friend ostream& operator<<(ostream& os, const lexique& lexique);
};

