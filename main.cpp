//
// Created by Aicha Keita on 11/29/24.
//
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


int main()
{
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


    return 0;
}