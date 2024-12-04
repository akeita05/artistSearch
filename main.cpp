#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

#include "hashtable.h"
using namespace std;


// Helper function to convert a string to lowercase - Dylan
std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Helper function to calculate total weight
double calculateTotalWeight(const vector<double>& weights) {
    return accumulate(weights.begin(), weights.end(), 0.0);
}

// Weighted random artists function
vector<Artist> selectWeightedRandomArtists(const vector<Artist>& artists, int maxCount) {
    vector<Artist> selectedArtists;
    if (artists.empty()) {
        return selectedArtists;
    }

    vector<double> weights;
    for (const auto& artist : artists) {
        weights.push_back(artist.getPopularity());
    }

    // Set up random number generation
    random_device randomDevice;
    mt19937 generator(randomDevice());
    uniform_real_distribution<double> dist(0.0, 1.0);


    double totalWeight = calculateTotalWeight(weights);

    // Select artists based on weighted probability
    for (int i = 0; i < maxCount && !artists.empty(); ++i) {
        double randomValue = dist(generator) * totalWeight;
        double cumulativeWeight = 0.0;

        for (size_t j = 0; j < artists.size(); ++j) {
            cumulativeWeight += weights[j];
            if (randomValue <= cumulativeWeight) {
                selectedArtists.push_back(artists[j]);
                break;
            }
        }
    }
    shuffle(selectedArtists.begin(), selectedArtists.end(), generator);

    return selectedArtists;
}

// Displays 10 artists based on filter and weighted randomness
void displayTopArtists(const vector<Artist>& filteredArtists) {
    if (filteredArtists.empty()) {
        cout << "No artists matched your criteria. Please try again with different filters." << endl;
    } else {
        vector<Artist> topArtists = selectWeightedRandomArtists(filteredArtists, 10);
        cout << "Displaying up to 10 weighted random artists:\n" << endl;

        for (const auto& artist : topArtists) {
            cout << "Artist: " << artist.getName() << endl;
            cout << "  Danceability: " << artist.getDanceability() << endl;
            cout << "  Explicit: " << (artist.getLanguage() ? "Yes" : "No") << endl;
            cout << "  Energy: " << artist.getEnergy() << endl;
            cout << "  Popularity: " << artist.getPopularity() << endl;
            cout << "  Genre: " << artist.getGenre() << endl;
            cout << endl;
        }
    }
}


int main() {
    // File path to the dataset
    std::string filePath = "resources/dataset.csv"; // Ensure this is the correct relative path
    std::vector<Artist> artists = parseArtists(filePath);

    if (artists.empty()) {
        std::cerr << "No artists loaded. Please check the dataset file!" << std::endl;
        return 1;
    }

    // Create the hash map
    HashTable h;
    h.createMap(artists);

    std::cout << "Welcome to GatorTunes: Artist Search!" << std::endl;
    std::cout << std::endl;

    std::cout << "You can filter for artists by the following categories: " << std::endl;
    std::cout << "1. Average Song Energy" << std::endl;
    std::cout << "2. Average Song Danceability" << std::endl;
    std::cout << "3. Explicit Language" << std::endl;
    std::cout << "4. Average Song Popularity" << std::endl;
    std::cout << "5. Genre" << std::endl;

    // Variables for filtering
    float energyLevel = 0.0;
    bool energy = false;

    float danceabilityLevel = 0.0;
    bool danceability = false;

    bool explicitLang = false;
    bool language = false;

    float popularityLevel = 0.0;
    bool popularity = false;

    std::string genreType;
    bool genre = false;

    // Get filtering options from the user
    std::cout << "Enter the numbers of the categories you want to filter by (separate with space): ";
    std::string filterInput;
    std::getline(std::cin, filterInput);
    std::cout << std::endl;

    // Parse the input
    std::istringstream iss(filterInput);
    std::vector<std::string> dividedInput(std::istream_iterator<std::string>{iss}, {});

    for (const auto& filter : dividedInput) {
        if (filter == "1" && !energy) {
            std::cout << "Enter a number between 1-10 for desired energy level: ";
            std::cin >> energyLevel;
            energy = true;
        } else if (filter == "2" && !danceability) {
            std::cout << "Enter a number between 1-10 for desired danceability: ";
            std::cin >> danceabilityLevel;
            danceability = true;
        } else if (filter == "3" && !language) {
            std::cout << "Type 'T' for explicit language or 'F' for clean lyrics: ";
            char choice;
            std::cin >> choice;
            explicitLang = (choice == 'T' || choice == 't');
            language = true;
        } else if (filter == "4" && !popularity) {
            std::cout << "Enter a number between 1-10 for desired popularity: ";
            std::cin >> popularityLevel;
            popularity = true;
        } else if (filter == "5" && !genre) {
            std::cout << "Enter the desired genre: ";
            std::cin.ignore();
            std::getline(std::cin, genreType);
            genre = true;
        } else {
            std::cout << "Invalid option: " << filter << std::endl;
        }
    }

    std::vector<Artist> filteredArtists;

    // Apply filters in sequence
    if (energy) {
        filteredArtists = h.energyFilter(filteredArtists, energyLevel);
    }
    if (danceability) {
        filteredArtists = h.danceabilityFilter(filteredArtists, danceabilityLevel);
    }
    if (language) {
        filteredArtists = h.languageFilter(filteredArtists, explicitLang);
    }
    if (popularity) {
        filteredArtists = h.popularityFilter(filteredArtists, popularityLevel);
    }
    if (genre) {
        filteredArtists = h.genreFilter(filteredArtists, genreType);
    }

    // Display filtered results
    if (filteredArtists.empty()) {
        std::cout << "No artists matched your criteria. Please try again with different filters." << std::endl;
    } else {
        displayTopArtists(filteredArtists);
    }

    return 0;
}
