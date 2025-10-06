#include <iostream>
#include <string>
#include <vector>

using namespace std;

class lexique
{
private:
   string nom;
   vector<string> mots;
   vector<int> frequences;
public:
    lexique(string n, string f);
    ~lexique();
    void saveLexique(string f);
    int getFrequenceFromWord(string mot);
    void deleteWord(string mot);
    void displayNbWords();
};

