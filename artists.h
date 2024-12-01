//
// Created by Aicha Keita on 12/1/24.
//

#ifndef ARTISTSEARCH_ARTISTS_H
#define ARTISTSEARCH_ARTISTS_H

#include <iostream>
#include <string>

//I'm making an artist class so that its easier to manipulate and filter in the main :D - aicha
class Artist
{
private:
    std::string name;
    float energy;
    float danceability;
    bool language;
    float popularity;
    std::string genre;

public:
    //constructor - aicha
    Artist(std::string& name, float energy, float danceability, bool language, float popularity, std::string& genre);

    //getter for name - aicha
    const std::string& getName() const;

    //setter for energy - aicha
    void setEnergy(float newEnergy);

    //setter for danceability - aicha
    void setDanceability(float newDanceability);

    //setter for language
    void setLanguage(bool newLanguage);

    //setter for popularity - aicha
    void setPopularity(float newPopularity);

};


#endif //ARTISTSEARCH_ARTISTS_H
