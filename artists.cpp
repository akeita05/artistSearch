//
// Created by Aicha Keita on 12/1/24.
//

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "artists.h"

using namespace std;

Artist::Artist(const std::string &name, float energy, float danceability, bool language, float popularity, const std::string &genre)
        : name(name), energy(energy), danceability(danceability), language(language), popularity(popularity), genre(genre) {}



// Helper function to trim whitespace
string trim(const string &str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}
// Helper function to check if a string is a valid float
bool isValidFloat(const std::string &str) {
    std::istringstream iss(str);
    float f;
    iss >> noskipws >> f; // No skipping of whitespace
    return iss.eof() && !iss.fail();
}

vector<Artist> parseArtists(const string &filename) {
    vector<Artist> artists;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return artists;
    }

    string line;
    bool isHeader = true;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;

        // Skip the header row
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string cell;

        // Variables to store parsed values
        string name;
        float popularity = 0.0f, danceability = 0.0f, energy = 0.0f;
        bool explicitLang = false;
        string genre;

        try {
            // Parse index (ignored)
            getline(ss, cell, ',');

            // Parse artist name
            getline(ss, name, ',');
            name = trim(name);

            // Parse popularity
            getline(ss, cell, ',');
            cell = trim(cell);
            if (isValidFloat(cell)) {
                popularity = stof(cell);
            }

            // Parse explicit language
            getline(ss, cell, ',');
            cell = trim(cell);
            explicitLang = (cell == "TRUE" || cell == "True" || cell == "true");

            // Parse danceability
            getline(ss, cell, ',');
            cell = trim(cell);
            if (isValidFloat(cell)) {
                danceability = stof(cell);
            }

            // Parse energy
            getline(ss, cell, ',');
            cell = trim(cell);
            if (isValidFloat(cell)) {
                energy = stof(cell);
            }

            // Parse genre
            getline(ss, genre, ',');  // This reads everything after the last comma
            genre = trim(genre);


            // Add artist to the list
            artists.emplace_back(name, energy, danceability, explicitLang, popularity, genre);

        } catch (const exception &e) {
            cerr << "Warning: Failed to parse line " << lineNumber << ": " << line << endl;
            cerr << "Reason: " << e.what() << endl;
        }
    }

    file.close();
    return artists;
}



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
