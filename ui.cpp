#include "ui.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "hashtable.h"


using namespace std;

// Helper function to convert a string to lowercase - Dylan
std::string toLowerUI(const std::string &str) {
    std::string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void setGradient(sf::RenderWindow& window) {
    sf::VertexArray background(sf::Quads, 4);
// gradient colors
    sf::Color colorLeft(200, 200, 200);
    sf::Color colorRight(0, 100, 10);

// positions for each vertex
    for (int i = 0; i < 4; ++i) {
        background[0].position = sf::Vector2f(0, 0);
        background[1].position = sf::Vector2f(window.getSize().x, 0);
        background[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
        background[3].position = sf::Vector2f(0, window.getSize().y);

        float factor = background[i].position.x / window.getSize().x;

        background[i].color = sf::Color(
                static_cast<sf::Uint8>((1.0f - factor) * colorLeft.r + factor * colorRight.r),
                static_cast<sf::Uint8>((1.0f - factor) * colorLeft.g + factor * colorRight.g),
                static_cast<sf::Uint8>((1.0f - factor) * colorLeft.b + factor * colorRight.b)
        );
    }



    window.draw(background);
}

class Button {
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text)
            : rectangle(sf::Vector2f(width, height)) {
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(sf::Color::Black);

        this->text.setFont(font);
        this->text.setString(text);
        this->text.setCharacterSize(18);
        this->text.setFillColor(sf::Color::Black);
        this->text.setPosition(
                x + (width - this->text.getLocalBounds().width) / 2.0f,
                y + (height - this->text.getLocalBounds().height) / 2.0f
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float btnPosX = rectangle.getPosition().x;
        float btnPosY = rectangle.getPosition().y;
        float btnxPosWidth = rectangle.getPosition().x + rectangle.getLocalBounds().width;
        float btnyPosHeight = rectangle.getPosition().y + rectangle.getLocalBounds().height;

        return (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY);
    }

private:
    sf::RectangleShape rectangle;
    sf::Text text;
};

using namespace std;

void startUI(string filePathIn) {
    sf::RenderWindow window(sf::VideoMode(1280, 420), "Artist Search");

    string page = "menu";
    std::vector<std::string> dividedInput;
    int count = 0;
    HashTable h;

    std::vector<Artist> artists = parseArtists(filePathIn);
    if (artists.empty()) {
        artists = parseArtists("../../" + filePathIn);
    }
    if (artists.empty()) {
        std::cerr << "No artists loaded. Please check the dataset file!" << std::endl;
    }
    else
    {
        std::cout << "Artists loaded successfully!" << std::endl;
    }

    h.createMap(artists);

    //variables for search
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


    sf::Font font;
    if (!font.loadFromFile("../../resources/font.ttf")) {
        std::cout << "Error loading font file" << std::endl;
    }

    // main menu
    std::string input_text;
    sf::Text text("", font, 30);
    text.setPosition(50, 360);
    text.setFillColor(sf::Color::Black);

    // text
    sf::Text title("Welcome to GatorTunes: Artist Search!", font, 40);
    title.setPosition(50, 30);
    title.setFillColor(sf::Color::Black);

    sf::Text title2("You will be able to filter for artists by these categories:", font, 30);
    title2.setPosition(50, 100);
    title2.setFillColor(sf::Color::Black);

    sf::Text options("1. Average Song Energy\n2. Average Song Danceability\n3. Explicit Language\n4. Average Song Popularity\n5. Genere", font, 25);
    options.setPosition(50, 150);
    options.setFillColor(sf::Color::Black);

    sf::Text instructions("Enter the number(s) of the categories you want to filter by! \n(please separate different categories with a space)", font, 30);
    instructions.setPosition(50, 290);
    instructions.setFillColor(sf::Color::Black);

    sf::Clock clock;  // Declare an instance of sf::Clock

    string results[10] = {"", "", "", "", "", "", "", "", "", ""};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (std::isprint(event.text.unicode))
                    input_text += event.text.unicode;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!input_text.empty())
                        input_text.pop_back();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    if (page == "menu") {
                        page = "search";
                        string filterInput = input_text;
                        input_text = "";
                        //search(input_text.substr(0, input_text.size() - 1));
                        //vector<Artist> artists = parseArtists(filePath); // artists declared here
                        HashTable h;
                        h.createMap(artists);


                        //split the input into a vector :) - aicha
                        //std::vector<std::string> dividedInput;

                        //split the string by spaces :-) - aicha
                        std::istringstream iss(filterInput);
                        std::string inputPart;
                        while (iss >> inputPart)
                        {
                            dividedInput.push_back(inputPart);
                        }
                        text.setPosition(50, 250);
                    }
                    else if (page == "search") {
                        if (count < dividedInput.size()) {
                            if (dividedInput[count] == "1") {
                                energyLevel = stoi(input_text);
                                energy = true;
                            }
                            if (dividedInput[count] == "2") {
                                danceabilityLevel = stoi(input_text);
                                danceability = true;
                            }
                            if (dividedInput[count] == "3") {
                                if (input_text == "T" || input_text == "t") {
                                    explicitLang = true;
                                }
                                else {
                                    explicitLang = false;
                                }
                            }
                            if (dividedInput[count] == "4") {
                                popularityLevel = stoi(input_text);
                                popularity = true;
                            }
                            if (dividedInput[count] == "5") {
                                genreType = input_text;
                                genre = true;
                            }
                            count++;
                            input_text = "";
                            if (count == dividedInput.size()) {
                                vector<Artist> filteredArtists;

                                //filter! :-P - aicha
                                if (energy)
                                {
                                    filteredArtists = h.energyFilter(filteredArtists, energyLevel);
                                }
                                if (danceability)
                                {
                                    filteredArtists = h.danceabilityFilter(filteredArtists, danceabilityLevel);
                                }
                                if (explicitLang)
                                {
                                    filteredArtists = h.languageFilter(filteredArtists, explicitLang);
                                }
                                if (popularity)
                                {
                                    filteredArtists = h.popularityFilter(filteredArtists, popularityLevel);
                                }
                                if (genre)
                                {
                                    filteredArtists = h.genreFilter(filteredArtists, genreType);
                                }
                                page = "results";
                                for (int i=0; i<10 && i<filteredArtists.size(); i++) {
                                    results[i] = filteredArtists[i].getName();
                                }
                            }
                        }
                    }
                }
            }
        }

        static sf::Time text_effect_time;
        static bool show_cursor;

        text_effect_time += clock.restart();  // Use the restart method of sf::Clock

        if (text_effect_time >= sf::seconds(0.5f))
        {
            show_cursor = !show_cursor;
            text_effect_time = sf::Time::Zero;
        }

        text.setString(input_text + (show_cursor ? '|' : ' '));

        window.clear(sf::Color::White);

        setGradient(window);

        if (page == "menu") {
            window.draw(title);
            window.draw(title2);
            window.draw(options);
            window.draw(instructions);
            window.draw(text);
        }
        else if (page == "search") {
            if (dividedInput[count] == "1") {
                sf::Text energy("Enter a number between 1-10 \nfor how energetic you would like the artist's songs to be.", font, 30);
                energy.setPosition(50, 100);
                energy.setFillColor(sf::Color::Black);
                window.draw(energy);
            }
            else if (dividedInput[count] == "2") {
                sf::Text danceability("Enter a number between 1-10 for how \ndanceable you would like the artist's songs to be.", font, 30);
                danceability.setPosition(50, 100);
                danceability.setFillColor(sf::Color::Black);
                window.draw(danceability);
            }
            else if (dividedInput[count] == "3") {
                sf::Text explicitLang("Type in 'T' if you want you want explicit \nlanguage and 'F' if you don't.", font, 30);
                explicitLang.setPosition(50, 100);
                explicitLang.setFillColor(sf::Color::Black);
                window.draw(explicitLang);
            }
            else if (dividedInput[count] == "4") {
                sf::Text popularity("Enter a number between 1-10 for how popular you \nwould like the artist's songs to be.", font, 30);
                popularity.setPosition(50, 100);
                popularity.setFillColor(sf::Color::Black);
                window.draw(popularity);
            }
            else if (dividedInput[count] == "5") {
                sf::Text genre("Enter the genre you would like \nto filter by.", font, 30);
                genre.setPosition(50, 100);
                genre.setFillColor(sf::Color::Black);
                window.draw(genre);
            }
            else {
                sf::Text invalid("Invalid Entry :(", font, 30);
                invalid.setPosition(50, 100);
                invalid.setFillColor(sf::Color::Black);
                window.draw(invalid);
            }
            window.draw(text);
        }
        else if(page == "results") {
            sf::Text resultTitle("Based on your choices, here are some artist you may like:", font, 30);
            resultTitle.setPosition(50, 30);
            resultTitle.setFillColor(sf::Color::Black);
            window.draw(resultTitle);

            string output = "";
            for (int i=0; i<10; i++) {
                output += to_string(i+1) + ". " + results[i] + "\n";
            }

            sf::Text result(output, font, 30);
            result.setPosition(50, 70);
            result.setFillColor(sf::Color::Black);
            window.draw(result);

        }

        window.display();
    }
}