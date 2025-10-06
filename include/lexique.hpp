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
private:
   string nom;
   vector<char> mots;
   vector<int> frequences;
public:
    lexique(string n, string f);
    ~lexique();
    void saveLexique(string f);
    int getFrequenceFromWord(string mot);
    void deleteWord(string mot);
    void displayNbWords();
    
    
    friend ostream& operator<<(ostream& os, const lexique& lexique);
};

