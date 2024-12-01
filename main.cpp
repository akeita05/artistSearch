//
// Created by Aicha Keita on 11/29/24.
//
#include <iostream>
#include "artists.h"


int main() {
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
    std::cout << "Enter the number(s) of the categories you want to filter by! (please separate different categories with a comma)" << std::endl;

    //variables :) - aicha
    std::string filterInput;

    //interpret the input :) - aicha
    std::cin >> filterInput;


    return 0;
}