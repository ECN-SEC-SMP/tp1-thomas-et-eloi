/**
 * @file lexique_ligne.hpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr) and Thomas Verron (thomas.verron@eleves.ec-nantes.fr)
 * @brief 
 * @version 0.1
 * @date 11-10-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

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