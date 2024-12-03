//
// Created by Aicha Keita on 12/1/24.
//

#ifndef ARTISTSEARCH_HASHTABLE_H
#define ARTISTSEARCH_HASHTABLE_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "artists.h"

class HashTable
{
private:
    std::unordered_map<std::string, Artist> hashMap;

public:
    //function to turn the parsed vector in a usable hashMap :) - aicha
    std::unordered_map<std::string, Artist> createMap(std::vector<Artist> artists);

    //filter by energy :p - aicha
    std::vector<Artist> energyFilter(std::vector<Artist> artists, float energyLevel);

    //filter by danceability :p - aicha
    std::vector<Artist> danceabilityFilter(std::vector<Artist> artists, float danceabilityLevel);

    //filter by language :p - aicha
    std::vector<Artist> languageFilter(std::vector<Artist> artists, bool language);

    //filter by popularity :p - aicha
    std::vector<Artist> popularityFilter(std::vector<Artist> artists, float popularityLevel);

    //filter by genre :p - aicha
    std::vector<Artist> genreFilter(std::vector<Artist> artists, std::string genre);

    //getter for the hashMap - aicha
    std::unordered_map<std::string, Artist> getHashmap();

};
#endif //ARTISTSEARCH_HASHTABLE_H
