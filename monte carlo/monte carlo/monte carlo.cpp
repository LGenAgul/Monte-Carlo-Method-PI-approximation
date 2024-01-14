#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <sstream>

int main()
{
    //initializing variables
    const int MAX_POINTS = 1000000;
    const double thickness = 5.0;
    int counter = 0;
    double approxPI;
    int resolution_x = 1200, resolution_y = 600;
    double yCord = 100.0 - thickness;
    int pointPerFrame = 1000;
    sf::Clock Clock;
    sf::RenderWindow window(sf::VideoMode(resolution_x,resolution_y), "Monte Carlo Simulation");
    //rectangle
    sf::CircleShape sector;
    sector.setOutlineColor(sf::Color::Black);
    sector.setOutlineThickness(5);
    sector.setPosition(thickness, yCord);
    sector.setRadius(250.0);
    sector.setFillColor(sf::Color::Transparent);
    //square
    sf::RectangleShape outerQuad;
    outerQuad.setOutlineColor(sf::Color::Black);
    outerQuad.setOutlineThickness(5);
    outerQuad.setPosition(thickness, yCord);
    outerQuad.setSize(sf::Vector2f(500.0, 500.0));
    outerQuad.setFillColor(sf::Color::Transparent);
    //initializing circles
    std::vector<sf::CircleShape> lilCircles;
   
    //initializing randomness
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<double> posX(outerQuad.getPosition().x, outerQuad.getPosition().x + outerQuad.getSize().x);
    std::uniform_real_distribution<double> posY(outerQuad.getPosition().y, outerQuad.getPosition().y + outerQuad.getSize().y);
    //text
    sf::Texture texture;
    sf::Sprite equation;
    sf::Image image;
    sf::Font font;
    sf::Text red, blue,sum,pi;
    image.loadFromFile("equation.png");
   texture.loadFromFile("equation.png");
    font.loadFromFile("Gellisto.ttf");
    equation.setTexture(texture);
    equation.setPosition(5, 5);
    equation.setScale(0.4, 0.4);

 
    red.setPosition(520, 100);
    red.setFont(font);
    red.setCharacterSize(50);
    red.setFillColor(sf::Color::Red);
    
   
    blue.setPosition(520, 230);
    blue.setCharacterSize(50);
    blue.setFont(font);
    blue.setFillColor(sf::Color::Blue);

    sum.setString("Test");
    sum.setPosition(520, 370);
    sum.setCharacterSize(50);
    sum.setFont(font);
    sum.setFillColor(sf::Color::Magenta);

    pi.setString("Test");
    pi.setPosition(520, 520);
    pi.setCharacterSize(50);
    pi.setFont(font);
    pi.setFillColor(sf::Color::Black);

    double numberOfRed = 0.0;
    double numberOfBlue = 0.0;
    double totalPoints = 0.0;
    std::vector<sf::CircleShape> allPoints;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
     
        for (int i = 0; i < pointPerFrame && allPoints.size() < MAX_POINTS;i++) { // MAX_POINTS is the total number of points you want to generate
            

                double x = posX(gen);
                double y = posY(gen);

                sf::CircleShape lilCircle;
                lilCircle.setRadius(1.0);
                lilCircle.setPosition(x, y);

                double dx = x - (sector.getPosition().x + sector.getRadius());
                double dy = y - (sector.getPosition().y + sector.getRadius());
                if (dx * dx + dy * dy <= sector.getRadius() * sector.getRadius()) {
                    lilCircle.setFillColor(sf::Color::Red);
                    numberOfRed++;
                }
                else {
                    lilCircle.setFillColor(sf::Color::Blue);
                    numberOfBlue++;
                }

                allPoints.push_back(lilCircle);
                
            }

        window.clear(sf::Color::White);

        approxPI = 4.0 * numberOfRed / allPoints.size();

        for (const auto& point : allPoints)
        {
            window.draw(point);
        }
    
        //console logging
        if (Clock.getElapsedTime().asSeconds() >= 0.1f)
        {
        /*    if (static_cast<int>(numberOfBlue + numberOfRed) % 100 == 0) {
                
                std::cout << "numberOfRed=" << numberOfRed << "\n";
                std::cout << "Total=" << numberOfBlue + numberOfRed << "\n";
                std::cout << "pi is approximately" << approxPI << "\n";
                std::cout << "==================================" << "\n";
                counter++;
            }
            if (counter > 5)
            {
                system("CLS");
                counter = 0;
            }*/



            std::string redstring = "r= " + std::to_string(static_cast<int64_t>(numberOfRed));
            red.setString(redstring);

            std::string bluestring = "b= " + std::to_string(static_cast<int64_t>(numberOfBlue));
            blue.setString(bluestring);

            std::string sumstring = "r+b= " + std::to_string(static_cast<int64_t>(numberOfBlue+numberOfRed));
            sum.setString(sumstring);

  

            std::stringstream stream;
            stream << std::fixed << std::setprecision(15) << approxPI;

            std::string pistring = "pi= " + stream.str();
            pi.setString(pistring);
            Clock.restart();
        }
        
        

        window.draw(outerQuad);
        window.draw(sector);
        window.draw(equation);
        window.draw(red);
        window.draw(blue);
        window.draw(sum);
        window.draw(pi);
        window.display();
        
    }
    

    return 0;
}