//
// Created by Aicha Keita on 12/1/24.
//

#ifndef ARTISTSEARCH_ARTISTS_H
#define ARTISTSEARCH_ARTISTS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//I'm making an artist class so that it's easier to manipulate and filter in the main :D - aicha
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
    Artist(const std::string &name, float energy, float danceability, bool language, float popularity, const std::string &genre);

    //getter for name - aicha
    const std::string& getName() const;

    //getter for energy - aicha
    float getEnergy() const;

    //getter for danceability - aicha
    float getDanceability() const;

    //getter for language - aicha
    bool getLanguage() const;

    //getter for popularity - aicha
    float getPopularity() const;

    //getter for genre - aicha
    const std::string& getGenre() const;

    //setter for energy - aicha
    void setEnergy(float newEnergy);

    //setter for danceability - aicha
    void setDanceability(float newDanceability);

    //setter for language - aicha
    void setLanguage(bool newLanguage);

    //setter for popularity - aicha
    void setPopularity(float newPopularity);



};

vector<Artist> parseArtists(const string &filename); // getter for parsing artists - :Dylan


#endif //ARTISTSEARCH_ARTISTS_H
