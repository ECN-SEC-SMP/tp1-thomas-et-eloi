/**
 * @file lexique_ligne.cpp
 * @author Eloi Tourangin (eloi.tourangin@eleves.ec-nantes.fr) and Thomas Verron (thomas.verron@eleves.ec-nantes.fr)
 * @brief 
 * @version 0.1
 * @date 11-10-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "lexique_ligne.hpp"
#include "utilitaire.hpp"
#include <fstream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Construct a new lexique ligne::lexique ligne object
 * 
 * @param n Name of the lexique
 * @param f Path to the file
 */
lexique_ligne::lexique_ligne(string n, string f)
 : lexique(n, f)
{
    ifstream in(f);
    if(!in) {
        cerr << "Error opening file " << f << endl;
        return;
    }

    string line;

    getline(in, line);
    
    for(string mot : this->mots){
        this->lexique_map.insert({mot, vector<int>()});
    }

    util::to_lower(line);

    int line_no = 1;

    const char* DELIMS = " “!\"#$%&'()*+,-./:;<=>?@ [\\]^_`{|}~0123456789\n\r\t";

    string copy_line = line; // Make a copy of the line to use with strtok
    char * pch = strtok(copy_line.data(), DELIMS);

    while(pch != nullptr)
    {
        string tmp = string(pch);
        util::remove_punctuation(tmp);
        if(!tmp.empty()){
            auto it = this->lexique_map.find(tmp);
            if(it == this->lexique_map.end()){
                this->lexique_map.insert({tmp, vector<int>{line_no}});
            } else {
                if( it->second.empty() || it->second.back() != line_no){
                    it->second.push_back(line_no);
                }
            }
        }
        pch = strtok(nullptr, DELIMS);
    }

    while(getline(in, line))
    {
        line_no++;
        util::to_lower(line);
        copy_line = line; // Update the copy of the line for strtok
        pch = strtok(copy_line.data(), DELIMS);
        while(pch != nullptr)
        {
            string tmp = string(pch);
            util::remove_punctuation(tmp);
            if(!tmp.empty()){
                auto it = this->lexique_map.find(tmp);
                if(it == this->lexique_map.end()){
                    this->lexique_map.insert({tmp, vector<int>{line_no}});
                } else {
                    if( it->second.empty() || it->second.back() != line_no){
                        it->second.push_back(line_no);
                    }
                }
            }
            pch = strtok(nullptr, DELIMS);
        }
    }


    return;

}

/**
 * @brief Destroy the lexique ligne::lexique ligne object
 * 
 */
lexique_ligne::~lexique_ligne()
{
    this->lexique_map.clear();
    return;
}

/**
 * @brief Display the lines where a word appears
 * 
 * @param mot Selected word
 */
void lexique_ligne::displayLinesFromWord(string mot) const {
    auto it = this->lexique_map.find(mot);
    if(it != this->lexique_map.end()){
        cout << "Le mot \"" << mot << "\" apparaît aux lignes : ";
        for(int line_no : it->second){
            cout << line_no << " ";
        }
        cout << endl;
    } else {
        cout << "Le mot \"" << mot << "\" n'existe pas dans le lexique." << endl;
    }
}

