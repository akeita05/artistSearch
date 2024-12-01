//
// Created by Aicha Keita on 12/1/24.
//
#include "artists.h"

Artist::Artist(std::string &name, float energy, float danceability, bool language, float popularity, std::string &genre):
name(name), energy(0.0), danceability(0.0), language(false), popularity(0.0), genre(genre){}

//getters!- aicha
const std::string& Artist::getName() const
{
    return name;
}

float Artist::getEnergy() const {
    return energy;
}

float Artist::getDanceability() const {
    return danceability;
}

bool Artist::getLanguage() const {
    return language;
}

float Artist::getPopularity() const {
    return popularity;
}

const std::string &Artist::getGenre() const {
    return genre;
}

//setters! - aicha
void Artist::setEnergy(float newEnergy) {
    energy = newEnergy;
}

void Artist::setDanceability(float newDanceability) {
    danceability = newDanceability;
}

void Artist::setLanguage(bool newLanguage) {
    language = newLanguage;
}

void Artist::setPopularity(float newPopularity) {
    popularity = newPopularity;
}
