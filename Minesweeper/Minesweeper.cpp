#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"
#include "Random.h"
#include "Board.h"
#include "Tiles.h"
//Minesweeper
using namespace std;
int main()
{
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite revealedTile(TextureManager::GetTexture("tile_revealed"));
    sf::Sprite one(TextureManager::GetTexture("number_1"));
    sf::Sprite two(TextureManager::GetTexture("number_2"));
    sf::Sprite three(TextureManager::GetTexture("number_3"));
    sf::Sprite four(TextureManager::GetTexture("number_4"));
    sf::Sprite five(TextureManager::GetTexture("number_5"));
    sf::Sprite six(TextureManager::GetTexture("number_6"));
    sf::Sprite seven(TextureManager::GetTexture("number_7"));
    sf::Sprite eight(TextureManager::GetTexture("number_8"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite happy(TextureManager::GetTexture("face_happy"));
    sf::Sprite win(TextureManager::GetTexture("face_win"));
    sf::Sprite lose(TextureManager::GetTexture("face_lose"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite digitSprites[11];
    sf::Texture numZero;
    numZero.loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
    sf::Sprite numZeroSprite(numZero);
    digitSprites[0] = numZeroSprite;
    sf::Texture numOne;
    numOne.loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
    sf::Sprite numOneSprite(numOne);
    digitSprites[1] = numOneSprite;
    sf::Texture numTwo;
    numTwo.loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32));
    sf::Sprite numTwoSprite(numTwo);
    digitSprites[2] = numTwoSprite;
    sf::Texture numThree;
    numThree.loadFromFile("images/digits.png", sf::IntRect(63, 0, 21, 32));
    sf::Sprite numThreeSprite(numThree);
    digitSprites[3] = numThreeSprite;
    sf::Texture numFour;
    numFour.loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32));
    sf::Sprite numFourSprite(numFour);
    digitSprites[4] = numFourSprite;
    sf::Texture numFive;
    numFive.loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32));
    sf::Sprite numFiveSprite(numFive);
    digitSprites[5] = numFiveSprite;
    sf::Texture numSix;
    numSix.loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32));
    sf::Sprite numSixSprite(numSix);
    digitSprites[6] = numSixSprite;
    sf::Texture numSeven;
    numSeven.loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32));
    sf::Sprite numSevenSprite(numSeven);
    digitSprites[7] = numSevenSprite;
    sf::Texture numEight;
    numEight.loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32));
    sf::Sprite numEightSprite(numEight);
    digitSprites[8] = numEightSprite;
    sf::Texture numNine;
    numNine.loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32));
    sf::Sprite numNineSprite(numNine);
    digitSprites[9] = numNineSprite;
    sf::Texture dash;
    dash.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));
    sf::Sprite dashSprite(dash);
    digitSprites[10] = dashSprite;

    Board::Load("boards/config.cfg");
    sf::RenderWindow window(sf::VideoMode(Board::dimensions[0], Board::dimensions[1]), "Minesweeper");
    happy.setPosition(static_cast<float>(Board::dimensions[0] / 2 - 32), static_cast<float>(Board::dimensions[1] - 100));
    lose.setPosition(static_cast<float>(Board::dimensions[0] / 2 - 32), static_cast<float>(Board::dimensions[1] - 100));
    win.setPosition(static_cast<float>(Board::dimensions[0] / 2 - 32), static_cast<float>(Board::dimensions[1] - 100));
    debug.setPosition(static_cast<float>(Board::dimensions[0] / 2 + 96), static_cast<float>(Board::dimensions[1] - 100));
    test1.setPosition(static_cast<float>(Board::dimensions[0] / 2 + 160), static_cast<float>(Board::dimensions[1] - 100));
    test2.setPosition(static_cast<float>(Board::dimensions[0] / 2 + 224), static_cast<float>(Board::dimensions[1] - 100));
    test3.setPosition(static_cast<float>(Board::dimensions[0] / 2 + 288), static_cast<float>(Board::dimensions[1] - 100));
    digitSprites[10].setPosition(static_cast<float>(0), static_cast<float>(Board::dimensions[1] - 100));
    vector<vector<Tiles>> minefield = Board::MineField();
    int lost = 0;
    int debugged = 0;
    int clickCount = 0;
    int won = 0;
    while (window.isOpen())
    {
        int totalMines = 0;
        int flags = 0;
        int remaining = 0;
        for (unsigned int i = 0; i < minefield.size(); i++)
        {
            for (unsigned int j = 0; j < minefield[i].size(); j++)
            {
                if (minefield[i][j].isMine == true)
                {
                    totalMines += 1;
                }
                if (minefield[i][j].isFlagged == true)
                {
                    flags += 1;
                }
            }
        }
        remaining = totalMines - flags;
        int neg = 0;
        if (remaining < 0)
        {
            neg = 1;
        }
        int ones = abs(remaining % 10);
        int tens = abs((remaining / 10) % 10);
        int hundreds = abs((remaining / 100) % 10);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                unsigned int tileX = event.mouseButton.x / 32;
                unsigned int tileY = event.mouseButton.y / 32;
                sf::Vector2f click(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (happy.getGlobalBounds().contains(click))
                {
                    won = 0;
                    lost = 0;
                    minefield = Board::MineField();
                    continue;
                }
                if (lose.getGlobalBounds().contains(click))
                {
                    won = 0;
                    lost = 0;
                    minefield = Board::MineField();
                    continue;
                }
                if (win.getGlobalBounds().contains(click))
                {
                    won = 0;
                    lost = 0;
                    minefield = Board::MineField();
                    continue;
                }
                if (test1.getGlobalBounds().contains(click))
                {
                    lost = 0;
                    won = 0;
                    minefield = Board::Test("boards/testboard1.brd");
                    continue;
                }
                if (test2.getGlobalBounds().contains(click))
                {
                    lost = 0;
                    won = 0;
                    minefield = Board::Test("boards/testboard2.brd");
                    continue;
                }
                if (test3.getGlobalBounds().contains(click))
                {
                    lost = 0;
                    won = 0;
                    minefield = Board::Test("boards/testboard3.brd");
                    continue;
                }
                if (lost == 0 && won == 0)
                {
                    if (debug.getGlobalBounds().contains(click))
                    {
                        clickCount += 1;
                        debugged = clickCount % 2;
                    }
                    if (tileX >= 0 && tileX <minefield[0].size() && tileY >= 0 && tileY < minefield.size())
                    {
                        Tiles& tile = minefield[tileY][tileX];
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (tile.isFlagged == false)
                            {
                                if (tile.isMine == true)
                                {
                                    lost = 1;
                                    for (unsigned int i = 0; i < minefield.size(); i++)
                                    {
                                        for (unsigned int j = 0; j < minefield[i].size(); j++)
                                        {
                                            if (minefield[i][j].isMine == true)
                                            {
                                                minefield[i][j].isRevealed = true;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    Board::adjacentReveal(&tile);
                                }
                                int revealed = 0;
                                int mines = 0;
                                for (unsigned int i = 0; i < minefield.size(); i++)
                                {
                                    for (unsigned int j = 0; j < minefield[i].size(); j++)
                                    {
                                        if (minefield[i][j].isMine == true)
                                        {
                                            mines += 1;
                                        }
                                        if (minefield[i][j].isRevealed == true && minefield[i][j].isMine == false)
                                        {
                                            revealed += 1;
                                        }
                                    }
                                }
                                if (revealed == minefield.size()* minefield[0].size() - mines)
                                {
                                    won = 1;
                                    for (unsigned int i = 0; i < minefield.size(); i++)
                                    {
                                        for (unsigned int j = 0; j < minefield[i].size(); j++)
                                        {
                                            if (minefield[i][j].isRevealed == false)
                                            {
                                                minefield[i][j].isFlagged = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else if (event.mouseButton.button == sf::Mouse::Right)
                        {
                            if (tile.isRevealed == false)
                            {
                                if (tile.isFlagged == true)
                                {
                                    tile.isFlagged = false;
                                }
                                else
                                {
                                    tile.isFlagged = true;
                                }
                            }
                        }
                    }
                }   
            }
        }
        window.clear(sf::Color::White);
        for (unsigned int i = 0; i < minefield[0].size(); i++)
        {
            for (unsigned int j = 0; j < minefield.size(); j++)
            {
                Tiles& tile = minefield[j][i];
                sf::Vector2f coord(static_cast<float>(i * 32), static_cast<float>(j * 32));
                if (tile.isRevealed == false)
                {
                    hiddenTile.setPosition(coord);
                    window.draw(hiddenTile);
                    if (tile.isFlagged)
                    {
                        flag.setPosition(coord);
                        window.draw(flag);
                    }
                    if (debugged == 1 && tile.isMine == true)
                    {
                        mine.setPosition(coord);
                        window.draw(mine);
                    }
                }
                else
                {
                    revealedTile.setPosition(coord);
                    window.draw(revealedTile);
                    if (tile.isMine)
                    {
                        mine.setPosition(coord);
                        window.draw(mine);
                    }
                    else if (tile.adjacentMines > 0)
                    {
                        if (tile.adjacentMines == 1)
                        {
                            one.setPosition(coord);
                            window.draw(one);
                        }
                        if (tile.adjacentMines == 2)
                        {
                            two.setPosition(coord);
                            window.draw(two);
                        }
                        if (tile.adjacentMines == 3)
                        {
                            three.setPosition(coord);
                            window.draw(three);
                        }
                        if (tile.adjacentMines == 4)
                        {
                            four.setPosition(coord);
                            window.draw(four);
                        }
                        if (tile.adjacentMines == 5)
                        {
                            five.setPosition(coord);
                            window.draw(five);
                        }
                        if (tile.adjacentMines == 6)
                        {
                            six.setPosition(coord);
                            window.draw(six);
                        }
                        if (tile.adjacentMines == 7)
                        {
                            seven.setPosition(coord);
                            window.draw(seven);
                        }
                        if (tile.adjacentMines == 8)
                        {
                            eight.setPosition(coord);
                            window.draw(eight);
                        }
                    }
                }
            }
        }
        if (won == 1)
        {
            window.draw(win);
        }
        else if (lost == 1)
        {
            window.draw(lose);
        }
        else if (lost == 0)
        {
            window.draw(happy);
        }
        if (neg == 1)
        {
            window.draw(digitSprites[10]);
        }
        for (int i = 0; i < 10; i++)
        {
            if (ones == i)
            {
                digitSprites[i].setPosition(static_cast<float>(63), static_cast<float>(Board::dimensions[1] - 100));
                window.draw(digitSprites[i]);
            }
            if (tens == i)
            {
                digitSprites[i].setPosition(static_cast<float>(42), static_cast<float>(Board::dimensions[1] - 100));
                window.draw(digitSprites[i]);
            }
            if (hundreds == i)
            {
                digitSprites[i].setPosition(static_cast<float>(21), static_cast<float>(Board::dimensions[1] - 100));
                window.draw(digitSprites[i]);
            }
        }
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}