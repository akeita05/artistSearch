//
// Created by Aicha Keita on 11/29/24.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


#include "hashtable.h"


// Helper function to convert a string to lowercase - Dylan
std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}


int main()
{

    string filePath = "resources/dataset.csv"; // Ensure this is the correct relative path
    vector<Artist> artists = parseArtists(filePath); // artists declared here

    //create a hashmap from the parsed data :p - aicha
    HashTable h;
    h.createMap(artists);

    if (artists.empty()) {
        cerr << "No artists loaded. Please check the dataset file!" << endl;
        return 1;
    }


    //create a menu :) - aicha
    std::cout << "Welcome to GatorTunes: Artist Search!" << std::endl;
    std::cout << std:: endl;

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
    std::cout << "6. Search for an Artist" << std::endl; // Just to test parsing function - dylan
    std::cout << std::endl;

    std::cout << "First, pick the categories you want to filter by!!! (You can choose up to five)" << std::endl;
    std::cout << "1. Energy" << std::endl;
    std::cout << "2. Danceability" << std::endl;
    std::cout << "3. Explicit Language" << std::endl;
    std::cout << "4. Popularity" << std::endl;
    std::cout << "5. Genre" << std::endl;
    std::cout << "Enter the number(s) of the categories you want to filter by! (please separate different categories with a space)" << std::endl;

    //variables :) - aicha
    std::string filterInput;

    //interpret the input :) - aicha
    std::getline(std::cin, filterInput);
    std::cout << std::endl;

    //split the input into a vector :) - aicha
    std::vector<std::string> dividedInput;

    //split the string by spaces :-) - aicha
    std::istringstream iss(filterInput);
    std::string inputPart;
    while (iss >> inputPart)
    {
        dividedInput.push_back(inputPart);
    }

    //understanding the input: variables :D - aicha
    int filterNum = dividedInput.size();

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

    //figure our what we are filtering by and give the user choices :D - aicha
    while (filterNum > 0)
    {
        if(dividedInput[0] == "1" && !energy)
        {
            //TO DO: energy choices
            std::cout << "You've chosen energy!" << std::endl;
            std::cout << "Enter a number between 1-10 for how energetic you would like the artist's songs to be." << std::endl;
            std::cout << "(10 being the highest possible energy, 1 being the lowest)" << std::endl;

            std::cin >> energyLevel;
            energy = true;

            std::cout << std::endl;
        }
        else if (dividedInput[0] == "2" && !danceability)
        {
            //TO DO: danceability choices
            std::cout << "You've chosen danceability!" << std::endl;
            std::cout << "Enter a number between 1-10 for how danceable you would like the artist's songs to be." << std::endl;
            std::cout << "(10 being the highest possible danceability, 1 being the lowest)" << std::endl;

            std::cin >> danceabilityLevel;
            danceability = true;

            std::cout << std::endl;
        }
        else if (dividedInput[0] == "3" && !language)
        {
            //TO DO: explicit language choices
            std::cout << "You've chosen explicit language!" << std::endl;
            std::cout << "Type in 'T' if you want you want explicit language and 'F' if you don't." << std::endl;

            std::string tOrF;
            std::cin >> tOrF;

            if (tOrF == "T")
            {
                explicitLang = true;
            }
            else if (tOrF == "F")
            {
                explicitLang = false;
            }

            language = true;

            std::cout << std::endl;
        }
        else if (dividedInput[0] == "4" && !popularity)
        {
            //TO DO: popularity choices
            std::cout << "You've chosen popularity!" << std::endl;
            std::cout << "Enter a number between 1-10 for how popular you would like the artist's songs to be." << std::endl;
            std::cout << "(10 being the most popular, 1 being the least)" << std::endl;

            std::cin >> popularityLevel;
            popularity = true;

            std::cout << std::endl;
        }
        else if (dividedInput[0] == "5" && !genre)
        {
            //TO DO: genre choices
            //y'all there's like 114 different genres so if anyone has an idea of how to do it I'm all ears - aicha
            genre = true;

            std::cout << std::endl;


        }  else if (dividedInput[0] == "6" && !popularity) { // this is just so i can test if the parsing works - Dylan
            std::cout << "Enter the name of the artist you want to search for: ";
            std::string searchTerm;
            std::getline(std::cin, searchTerm);

            bool found = false;

            std::string lowerSearchTerm = toLower(searchTerm);

            // Search for the artist in the list
            for (const Artist& artist : artists)
            {
                if (toLower(artist.getName()).find(lowerSearchTerm) != string::npos)
                {
                    cout << "Found artist: " << artist.getName() << std::endl;
                    cout << "Danceability: " << artist.getDanceability() << std::endl;
                    cout << "Explicit: " << artist.getLanguage() << std::endl;
                    cout << "Energy: " << artist.getEnergy() << std::endl;
                    cout << "Genre: " << artist.getGenre() << std::endl;

                    found = true;
                    break;  // We stop after finding the first match
                }
            }

            if (!found)
            {
                std::cout << "No artist found with the name: " << searchTerm << std::endl;
            }

            if (!found)
            {
                std::cout << "No artist found with the name: " << searchTerm << std::endl;
            }
        }




        else
        {
            std::cout << "Invalid Entry :(" << std::endl;

            std::cout << std::endl;
        }

        //remove the first element and move on :D - aicha
        dividedInput.erase(dividedInput.begin());
        filterNum--;
    }

    vector<Artist> filteredArtists;

    //filter! :-P - aicha
    if (energy)
    {
        h.energyFilter(filteredArtists, energyLevel);
    }

    if (danceability)
    {
        h.danceabilityFilter(filteredArtists, danceabilityLevel);
    }
    if (language)
    {
        h.languageFilter(filteredArtists, explicitLang);
    }
    if (popularity)
    {
        h.popularityFilter(filteredArtists, popularityLevel);
    }
    if (genre)
    {
        h.genreFilter(filteredArtists, genreType);
    }

    //finally, print the artist!
    //there are 31,000+ unique artists in the dataset, so like maybe we only show like 10 of them based on the choices made???
    std::cout << "Based on your choices, here are some artist you may like: " << std::endl;
    //print the artist(s) that match!

    return 0;
}