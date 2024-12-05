#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <numeric>
#include <iterator> // Include the iterator header
#include "hashtable.h"
#include "ui.h"
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

// Sorting function for popularity (from greatest to least)
bool comparePopularity(const Artist& a, const Artist& b) {
    return a.getPopularity() > b.getPopularity(); // Descending order
}

// Function to display the top 10 artists
void displayTopArtists(const vector<Artist>& sortedArtists) {
    if (sortedArtists.empty()) {
        cout << "No artists matched your criteria. Please try again with different filters." << endl;
    } else {
        cout << "Based on your choices, here are some artist you may like:\n " << std::endl;
        int limit = min(10, static_cast<int>(sortedArtists.size()));
        for (int i = 0; i < limit; ++i) {
            const auto& artist = sortedArtists[i];
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


void merge(vector<Artist>& arr, int left, int right, bool (*compare)(const Artist&, const Artist&)) {
    if (left == right) return;

    int mid = (left + right) / 2;
    merge(arr, left, mid, compare);
    merge(arr, mid + 1, right, compare);

    vector<Artist> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (compare(arr[i], arr[j])) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }
    while (j <= right) {
        temp.push_back(arr[j]);
        j++;
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i - left];
    }
}

//merge sort: I can only get it to work for popularity atm - :Dylan
void mergeSort(vector<Artist>& arr, int left, int right, bool (*compare)(const Artist&, const Artist&)) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid, compare);
        mergeSort(arr, mid + 1, right, compare);
        merge(arr, left, right, compare);
    }
}

int main() {
    // File path to the dataset
    std::string filePath = "resources/dataset.csv"; // Ensure this is the correct relative path
    std::vector<Artist> artists = parseArtists(filePath);
    if (artists.empty()) {
        artists = parseArtists("../../" + filePath);
    }
    if (artists.empty()) {
        std::cerr << "No artists loaded. Please check the dataset file!" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Artists loaded successfully!" << std::endl;
    }

    //create a hashmap from the parsed data :p - aicha
    HashTable h;
    h.createMap(artists);

    //create a menu :) - aicha
    std::cout << "Welcome to GatorTunes: Artist Search!" << std::endl;
    std::cout << std:: endl;

    std::cout << "Would you like to launch the UI? (Y/N): ";
    std::string uiChoice;
    cin >> uiChoice;
    std::cin.ignore(); // Clear the newline character from the input buffer
    if (uiChoice == "y" || uiChoice == "Y") {
        startUI(filePath);
        return 0;
    }

    std::cout << "Let's get started!" << std::endl;
    std::cout << "You will be able to filter for artists by these categories: " << std::endl;

    std::cout << "1. Average Song Energy" << std::endl;
    std::cout << "   This is a perceptual measure of intensity and activity on average of the artist's song. "
                 "Typically, energetic tracks feel fast, loud, and noisy" << std::endl;
    std::cout << "2. Average Song Danceability" << std::endl;
    std::cout << "   This is how on suitable on average the artist's songs are for dancing." << std::endl;
    std::cout << "3. Explicit Language" << std::endl;
    std::cout << "   Whether or not the artist has songs with explicit lyrics" << std::endl;
    std::cout << "4. Average Song Popularity" << std::endl;
    std::cout << "   How popular the artist's songs are on average" << std::endl;
    std::cout << "5. Genre" << std::endl;
    std::cout << "   The genre in which the artist belongs" << std::endl;
    std::cout << std::endl;

    std::cout << "First, pick the categories you want to filter by!!! (You can choose up to five)" << std::endl;
    std::cout << "1. Energy" << std::endl;
    std::cout << "2. Danceability" << std::endl;
    std::cout << "3. Explicit Language" << std::endl;
    std::cout << "4. Popularity" << std::endl;
    std::cout << "5. Genre" << std::endl;


    //understanding the input: variables :D - aicha
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

    //split the string by spaces :-) - aicha
    std::istringstream iss(filterInput);
    std::vector<std::string> dividedInput((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

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

    //filter! :-P - aicha
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

    if (filteredArtists.empty()) {
        cout << "No artists matched your criteria. Please try again with different filters." << endl;
    } else {

        //finally, print the artist!
        //there are 31,000+ unique artists in the dataset, so like maybe we only show like 10 of them based on the choices made???
        //^we could show like 10 at a time and let them choose if they'd like to see more...
        //like "showing 10/however many artist
        //- aicha



        // Sort the filtered artists by popularity using merge sort
        mergeSort(filteredArtists, 0, filteredArtists.size() - 1, comparePopularity);

        // Display top ten artists
        displayTopArtists(filteredArtists);
    }

    return 0;
}