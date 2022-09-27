#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
//#include "Game.h"

struct Pointxy {
    int x, y;
};

class Game {
public:
    int ScreenX;
    int ScreenY;
    //int Snakelength[600][2];
    std::vector<Pointxy> Snakelength;
    int EnemyX;
    int EnemyY;
    int YouX;
    int YouY;
    int Snakel = 1;
    int EternalMoveX = 0;
    int EternalMoveY = 0;
    int Schlangen_Wachstum; 
    int Schlangen_Wachstum_c = 0;
    int Scoreint = 0; 
    //EnemyX = 0;
    //EnemyY = 0;

    Game(int X, int Y, int x, int y, int SchlWachs);

    void Fill(int array[][2]);

    void GenerateEnemy();

    void Draw(sf::RectangleShape *rect, sf::RenderWindow *window);

    void Move(sf::Text *t, int lastSch[][2]);

    void M(int x, int y);

    bool Wall();
};

Game::Game (int X, int Y, int x, int y, int SchlWachs) { // TODO update Parameters
    Pointxy p;
    p.x = 0;
    p.y = 0;
    Snakelength.push_back(p);
    ScreenX = X;
    ScreenY = Y;
    YouX = x;
    YouY = y;
    Schlangen_Wachstum = SchlWachs;
}

void Game::Fill (int array[][2]) {
    for(int i = 0;i<(sizeof(array)/sizeof(*array));i++) {
        array[i][0] = 0;
        array[i][1] = 0;
    }
}

void Game::GenerateEnemy() {
    int c = 0;
    int rx;
    int ry;

    while(c <= 0) {
        c++;
        rx = 20 * (rand() % 39 + 1);
        ry = 20 * (rand() % 29 + 1);

        for(int i = 0;i<Snakel;i++) {
            if(Snakelength[i].x == rx) {
                c = 0;
            }else if(Snakelength[i].y == ry) {
                c = 0;
            } 
        }
    }
    EnemyX = rx;
    EnemyY = ry;
}

void Game::Draw (sf::RectangleShape *rect, sf::RenderWindow *window) {
    rect->setPosition(EnemyX, EnemyY);
    (*window).draw(*rect);

    for(int i = 0;i<Snakel;i++) {
        rect->setPosition(Snakelength[i].x, Snakelength[i].y);
        (*window).draw(*rect);
    }
}

void Game::Move(sf::Text *t, int lastSch[][2]) { //TODO Parameter, Snakelength function
    int LastX = Snakelength[0].x;
    int LastY = Snakelength[0].y;
    int lx2;
    int ly2;

    Snakelength[0].x += EternalMoveX;
    Snakelength[0].y += EternalMoveY;

    for(int i = 1;i<Snakel+1;i++) {
                std::cout << "Hallo1";

        lx2 = Snakelength[i].x;
        ly2 = Snakelength[i].y;

        Snakelength[i].x = LastX;
        Snakelength[i].y = LastY;
 
        LastX = lx2;
        LastY = ly2;
    } 

    if(Snakelength[0].x == EnemyX && Snakelength[0].y == EnemyY) {// TODO Overlook
        std::cout << "Hallo2";
        GenerateEnemy();
        Scoreint++;
        Pointxy p2;
        p2.x = 0;
        p2.y = 0;
        Pointxy Snakearray[Snakel];

        for(int i = 0;i<Snakel;i++) {
            p2.x = Snakelength[i].x;
            p2.y = Snakelength[i].y;
            Snakearray[i] = p2;
        }

        Snakelength.resize(1);
        Snakelength[0].x = lastSch[0][0];
        Snakelength[0].y = lastSch[0][1];
        Snakel++;

        for(int i = 1;i<Snakel;i++) {
            lx2 = LastX;
            ly2 = LastY;
            
            p2.x = Snakearray[i][0];
            p2.y = lastSch[i-1][1];

            Snakelength[i].x = p2.x;
            Snakelength[i].y = p2.y;
            
            Snakelength.push_back(p2);

            LastX = lx2;
            LastY = ly2;
        }
    }
    
    if(Schlangen_Wachstum_c == Schlangen_Wachstum) {
        lx2 = lastSch[0][0];
        ly2 = lastSch[0][1];

        lastSch[0][0] = LastX;
        lastSch[0][1] = LastY;

        for(int i = 1;i<Schlangen_Wachstum;i++) {
            LastX = lastSch[i][0];
            LastY = lastSch[i][1];

            lastSch[i][0] = lx2;
            lastSch[i][1] = ly2;

            lx2 = LastX;
            ly2 = LastY;
        }
    }
    if(Schlangen_Wachstum_c != Schlangen_Wachstum) {
        Schlangen_Wachstum_c++;
    } 
}

void Game::M (int x, int y) {
    EternalMoveX = x;
    EternalMoveY = y;
}

bool Game::Wall () { // Wall is y < 0, x < 0, x > 780, y > 580 
    int Sx = Snakelength[0].x + EternalMoveX;
    int Sy = Snakelength[0].y + EternalMoveY;

    if(Sx < 0 || Sx > ScreenX-20) {
        return false;
    }else if(Sy < 0 || Sy > ScreenY-20) {
        return false;
    }

    return true;
}

class button {
private:
    sf::RectangleShape buttonrect;
public:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    button(int xx, int yx, int widthx, int heightx) {
        x = xx;
        y = yx;
        width = widthx;
        height = heightx;
    }

    void Draw(sf::RenderWindow *window) {
        buttonrect.setSize(sf::Vector2f(width, height));
        buttonrect.setPosition(x, y);
        buttonrect.setFillColor(sf::Color::Blue);
        buttonrect.setOutlineThickness(0);

        window->draw(buttonrect);
    }

    bool buttonCollision(int x1, int y1) {
        if(x1 > x && x1 < x + width) {
            if(y1 > y && y1 < y + height) {
                return true;
            }
        }
        return false;
    }
}; 

class Menu {
private: 
    int buttonAnzahl = 0;
    button Menubutton[20];
public:

};

int main()
{
    int wachs;

    std::cout << "Schlangen Wachstum: ";
    std::cin >> wachs;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");


    window.setFramerateLimit(16);

    //Objekte:
    Game Spiel(800, 600, 0, 0, wachs);
    Spiel.Snakelength[0].x = 0;
    Spiel.Snakelength[0].y = 0;
    //Spiel.Fill(Spiel.Snakelength);
    /*Spiel.Snakelength[0][0] = 60;
    Spiel.Snakelength[1][0] = 40;
    Spiel.Snakelength[2][0] = 20;
    Spiel.Snakelength[3][0] = 0;*/

    int SchlangenArray[Spiel.Schlangen_Wachstum][2];
    Spiel.Fill(SchlangenArray);

    sf::RectangleShape Background;
    Background.setSize(sf::Vector2f(800, 600));
    Background.setFillColor(sf::Color::Red);
    Background.setPosition(0, 0);
    Background.setOutlineThickness(0);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Game Over!", font, 50);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Regular);
    text.setPosition(sf::Vector2f(200, 200));
    
    sf::Text Score(std::to_string(Spiel.Scoreint), font, 30);
    Score.setFillColor(sf::Color::White);
    Score.setStyle(sf::Text::Regular);
    Score.setPosition(sf::Vector2f(20, 0));

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(0, 0);
    rect.setOutlineThickness(0);

    sf::RectangleShape button;
    rect.setSize(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(0, 0);
    rect.setOutlineThickness(0);

    //Objekte
    //Schleifen Variablen

    bool Bewegen = false;
    int c = 0;
    int fps = 0;
    bool GAME_OVER_ON = false;

    //Schleifen Variablen
    Spiel.GenerateEnemy();

    while (window.isOpen())
    {   
        Score.setString("Score:" + std::to_string(Spiel.Scoreint));
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                Spiel.M(-20, 0);
                Bewegen = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                Spiel.M(20, 0);
                Bewegen = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                Spiel.M(0, -20);
                Bewegen = 1;
            }   
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                Spiel.M(0, 20);
                Bewegen = 1;
            } 
        }
        window.clear();
        if(Bewegen && Spiel.Wall()) {
            Spiel.Move(&text, SchlangenArray);
            c = 0;
        }
        //window.draw(text);
        window.draw(Background);
        Spiel.Draw(&rect, &window);

        //Vorübergehend:

        for(int i = 1;i<Spiel.Snakel;i++) {
            if(Spiel.Snakelength[i].x == Spiel.Snakelength[0].x && Spiel.Snakelength[i].y == Spiel.Snakelength[0].y) {
                //Bewegen = 0;    
                GAME_OVER_ON = 1;
                Spiel.Snakel = 0;
            }
        }

        if(GAME_OVER_ON)
            window.draw(text);

        //Vorübergehend

        window.draw(Score);
        window.display();
        c++;
    }
    return EXIT_SUCCESS;
}