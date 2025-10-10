#pragma once
#include "lexique.hpp"
#include <map>
#include <vector>

class lexique_ligne : public lexique
{
private:
    map<string, vector<int>> lexique_map;
public:
    lexique_ligne(string n, string f);
    ~lexique_ligne();

    void displayLinesFromWord(string mot) const;

};