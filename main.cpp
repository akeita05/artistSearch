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

// Displays 10 artists based off filter - Dylan
void displayTopArtists(vector<Artist> filteredArtists) {
    if (filteredArtists.empty()) {
        cout << "No artists matched your criteria. Please try again with different filters." << endl;
    } else {
        random_device randomDevice;      // Random number seed generator
        mt19937 generator(randomDevice());

        // Shuffle the filteredArtists vector
        shuffle(filteredArtists.begin(), filteredArtists.end(), generator);

        cout << "Displaying up to 10 randomly selected artists that matched your criteria:\n" << endl;

        int limit = min(10, static_cast<int>(filteredArtists.size()));
        for (int i = 0; i < limit; ++i) {
            cout << "Artist: " << filteredArtists[i].getName() << endl;
            cout << "  Danceability: " << filteredArtists[i].getDanceability() << endl;
            cout << "  Explicit: " << (filteredArtists[i].getLanguage() ? "Yes" : "No") << endl;
            cout << "  Energy: " << filteredArtists[i].getEnergy() << endl;
            cout << "  Popularity: " << filteredArtists[i].getPopularity() << endl;
            cout << "  Genre: " << filteredArtists[i].getGenre() << endl;
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
