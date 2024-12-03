//
// Created by Aicha Keita on 12/1/24.
//

#include "hashtable.h"

//helper functions!
bool inRange(float low, float high, float level)
{
    return (low <= level && level <= high);
}

//function to turn the parsed vector in a usable hashMap :p - aicha
std::unordered_map<std::string, Artist> HashTable::createMap(std::vector<Artist> artists)
{
    for (int i = 0; i < artists.size(); i++)
    {
        string artistName = artists[i].getName();
        auto it = hashMap.find(artistName);

        if (it == hashMap.end())
        {
            hashMap.insert(make_pair(artistName, artists[i]));
        }
        else
        {
            Artist &existingArtist = it->second;

            float newEnergy = (existingArtist.getEnergy() + artists[i].getEnergy()) / 2;
            float newDanceability = (existingArtist.getDanceability() + artists[i].getDanceability()) / 2;
            float newPopularity = (existingArtist.getPopularity() + artists[i].getPopularity()) / 2;

            if(existingArtist.getLanguage() != artists[i].getLanguage())
            {
                existingArtist.setLanguage(true);
            }

            existingArtist.setEnergy(newEnergy);
            existingArtist.setDanceability(newDanceability);
            existingArtist.setPopularity(newPopularity);
        }
    }

    return hashMap;
}

//filter by energy :p - aicha
std::vector<Artist> HashTable::energyFilter(std::vector<Artist> artists, float energyLevel)
{
    float energy = energyLevel / 10;

    if(artists.empty())
    {
        for (auto it : hashMap)
        {
            if (inRange(energy - 0.05, energy + 0.05, it.second.getEnergy()))
            {
                artists.push_back(it.second);
            }
        }

        return artists;
    }

    for(int i = 0; i < artists.size(); i++)
    {
        if(!(inRange(energy - 0.05, energy + 0.05, artists[i].getEnergy())))
        {
            artists.erase(artists.begin() + i);
        }
    }

    return artists;
}

//filter by danceability :p - aicha
std::vector<Artist> HashTable::danceabilityFilter(std::vector<Artist> artists, float danceabilityLevel)
{
    float danceability = danceabilityLevel / 10;

    if(artists.empty())
    {
        for (auto it : hashMap)
        {
            if (inRange(danceability - 0.05, danceability + 0.05, it.second.getDanceability()))
            {
                artists.push_back(it.second);
            }
        }

        return artists;
    }

    for(int i = 0; i < artists.size(); i++)
    {
        if(!(inRange(danceability - 0.05, danceability + 0.05, artists[i].getDanceability())))
        {
            artists.erase(artists.begin() + i);
        }
    }

    return artists;
}

//filter by language :p - aicha
std::vector<Artist> HashTable::languageFilter(std::vector<Artist> artists, bool language)
{
    if(artists.empty())
    {
        for (auto it : hashMap)
        {
            if (it.second.getLanguage() == language)
            {
                artists.push_back(it.second);
            }
        }

        return artists;
    }

    for(int i = 0; i < artists.size(); i++)
    {
        if(artists[i].getLanguage() != language)
        {
            artists.erase(artists.begin() + i);
        }
    }

    return artists;
}

//filter by popularity :p - aicha
std::vector<Artist> HashTable::popularityFilter(std::vector<Artist> artists, float popularityLevel)
{
    float popularity = popularityLevel * 10;

    if(artists.empty())
    {
        for (auto it : hashMap)
        {
            if (inRange(popularity - 20, popularity + 20, it.second.getPopularity()))
            {
                artists.push_back(it.second);
            }
        }

        return artists;
    }

    for(int i = 0; i < artists.size(); i++)
    {
        if(!(inRange(popularity - 20, popularity + 20, artists[i].getPopularity())))
        {
            artists.erase(artists.begin() + i);
        }
    }

    return artists;
}

//filter by genre :p - aicha
std::vector<Artist> HashTable::genreFilter(std::vector<Artist> artists, std::string genre)
{
    if(artists.empty())
    {
        for (auto it : hashMap)
        {
            if (it.second.getGenre() == genre)
            {
                artists.push_back(it.second);
            }
        }

        return artists;
    }

    for(int i = 0; i < artists.size(); i++)
    {
        if(artists[i].getGenre() != genre)
        {
            artists.erase(artists.begin() + i);
        }
    }

    return artists;
}

//getter for the hashmap - aicha
std::unordered_map<std::string, Artist> HashTable::getHashmap()
{
    return hashMap;
}