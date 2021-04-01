#include <SFML/Graphics.hpp>
#include <ctype.h>

sf::String toUpper(sf::String);
void menuScreen(sf::RenderWindow);
void menu();
void game();
void winScreen();
void credits();
void refresh();
void render();
void setObject1();
void useLogic();
sf::String lookLogic(sf::String str);
sf::String checkLogic(sf::String);
void setObject2();

sf::Font font;
const int width = 800;
const int height = 800;
int findWordStart = 0;

sf::RenderWindow window(sf::VideoMode(width, height), "Escape Room");

sf::Text title;
sf::Text winTitle;
sf::Text option1;
sf::Text option2;
sf::Text option3;
sf::Text gameText;
sf::Text messageText;
sf::Text winMessageText;
sf::Text creditTitle;
sf::Text creditText;
sf::Text returnText;

sf::String playerInput;
sf::String playerWord = "";
sf::String playerString;
sf::Text playerText;
sf::RectangleShape shape(sf::Vector2f(width - 90, playerText.getLocalBounds().height + 50));

class Object {
public:
    sf::String objectName;
    sf::String objectType;
    sf::String objectColour;
    sf::String objectDescription;
    bool objectCanBeTaken;
    bool objectLocked;

    Object() {
        objectName = "Dummy";
        objectType = "Dummy";
        objectColour = "Dummy";
        objectDescription = "Dummy";
        objectCanBeTaken = false;
        objectLocked = false;
    };
    Object(sf::String name, sf::String type, sf::String description, bool canBeTaken, bool locked) {
        objectName = name;
        objectType = type;
        objectColour = "Dummy";
        objectDescription = description;
        objectCanBeTaken = canBeTaken;
        objectLocked = locked;
    };
    Object(sf::String name, sf::String type, sf::String colour, sf::String description, bool canBeTaken, bool locked) {
        objectName = name;
        objectType = type;
        objectColour = colour;
        objectDescription = description;
        objectCanBeTaken = canBeTaken;
        objectLocked = locked;
    };
};

Object objects[9]{
    {"DOOR", "Door", "A locked door made of metal that leads outside the room.\nThere appear to be two locks of different colours, a blue\nlock, and a red lock.", false, true},
    {"CUPBOARD", "Container", "A normal looking cupboard. There doesn't seem to be\nanything inside it. You notice strange markings on the ground\nnear the cupboard's feet", false, false},
    {"CABINET", "Container", "A cabinet with two drawers. Both drawers are empty,\nhowever, one seems to be shallower than the other. The shallow\ndrawer has a small gap in the back right corner.", false, false},
    {"CHEST", "Container", "A wooden chest. Maybe there is something useful in it?", false, false},
    {"BLUE LOCK", "Lock", "Blue", "A lock on the exit door. It is coloured blue.", false, true},
    {"RED LOCK", "Lock", "Red", "A lock on the exit door. It is coloured red.", false, true},
    {"BLUE KEY", "Key", "Blue", "A blue key. It might be able to be used for something.", false, false},
    {"RED KEY", "Key", "Red", "A red key. It might be able to be used for something.", false, false},
    {"CROWBAR", "Item", "A metal crowbar. It might be able to be used for something.", false, false}
};

Object object1;
Object object2;

int screen = 1;

int main()
{
    
    font.loadFromFile("Fonts/BLKCHCRY.TTF");

    sf::Event event;

    sf::Text dummy;
    dummy.setFont(font);
    dummy.setCharacterSize(60);
    dummy.setPosition(width / 2, height / 2);
    dummy.setString("To be made");

    
    menu();
    render();
    refresh();

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                {
                    if (playerInput.getSize() > 0)
                    {
                        playerInput.erase(playerInput.getSize() - 1, 1);
                        playerText.setString(playerInput);
                        refresh();
                    }
                    else;
                }
                else if (event.text.unicode == '\r') {}
                else if (event.text.unicode < 128)
                {
                    playerInput += event.text.unicode;
                    playerText.setString(playerInput);
                    refresh();
                }

                

            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    messageText.setString("");
                    if (screen == 1)
                    {
                        if (toUpper(playerText.getString()) == "PLAY" || playerText.getString() == "1")
                        {
                            screen = 2;

                            playerInput = "";
                            playerText.setString(playerInput);

                            game();
                            refresh();
                        }
                        else if (toUpper(playerText.getString()) == "CREDITS" || playerText.getString() == "2")
                        {
                            screen = 4;

                            playerInput = "";
                            playerText.setString(playerInput);

                            credits();
                            refresh();
                        }
                        else if (toUpper(playerText.getString()) == "EXIT" || playerText.getString() == "3")
                        {
                            window.close();
                        }
                        else
                        {
                            playerInput = "";
                            playerText.setString(playerInput);

                            refresh();
                        }
                    }
                    else if (screen == 2)
                    {
                        if (toUpper(playerText.getString()) == "HELP")
                        {
                            messageText.setString("Available commands are:\nUSE <OBJECT> WITH <OBJECT>,\nLOOK <OBJECT>, CHECK <OBJECT>,\nEXIT.");

                            playerInput = "";
                            playerText.setString(playerInput);

                            refresh();
                        }
                        else if (toUpper(playerText.getString()) == "EXIT")
                        {
                            playerInput = "";
                            playerText.setString(playerInput);

                            screen = 1;
                            menu();
                            refresh();
                        }
                        else if (toUpper(playerText.getString().substring(0,3)) == "USE")
                        {
                            if (playerText.getString().getSize() < 4)
                            {
                                messageText.setString("You must specify an object to be used.");
                                refresh();
                            }
                            else
                            {
                                playerText.setString(toUpper(playerText.getString()));
                                findWordStart = playerText.getString().find("ON");
                                /*playerText.setString(playerInput);*/


                                setObject1();
                                if (!object1.objectCanBeTaken)
                                {
                                    messageText.setString("You have not found " + object1.objectName + " yet!");
                                    refresh();
                                }
                                else if (findWordStart > 0)
                                {
                                    if (playerText.getString().substring(findWordStart, 2) == "ON")
                                    {
                                        messageText.setString("This is just before setObject2");
                                        setObject2();
                                        refresh();
                                    }
                                    else
                                    {
                                        messageText.setString("Please specify something to use this on");
                                        refresh();
                                    }
                                }
                                else
                                {
                                    messageText.setString("That is not a valid command.\nDid you mean USE <object> ON <object>?");
                                    refresh();
                                }
                            }
                            playerInput = "";
                            playerText.setString(playerInput);
                            refresh();
                        }
                        else if (toUpper(playerText.getString().substring(0, 4)) == "LOOK")
                        {
                            if (playerText.getString().getSize() < 5)
                            {
                                messageText.setString("You must specify an object to look at.");
                                refresh();
                            }
                            else
                            {
                                playerWord = toUpper(playerText.getString().substring(5, playerText.getString().getSize()));
                                playerString = lookLogic(playerWord);
                                messageText.setString(playerString);
                                refresh();
                            }
                            playerInput = "";
                            playerText.setString(playerInput);
                            refresh();
                        }
                        else if (toUpper(playerText.getString().substring(0, 5)) == "CHECK")
                        {
                            if (playerText.getString().getSize() < 6)
                            {
                                messageText.setString("You must specify an object to check.");
                                refresh();
                            }
                            else
                            {
                                playerWord = toUpper(playerText.getString().substring(6, playerText.getString().getSize()));
                                playerString = checkLogic(playerWord);
                                messageText.setString(playerString);
                                refresh();
                            }

                            playerInput = "";
                            playerText.setString(playerInput);
                            refresh();
                        }
                        else
                        {
                            messageText.setString("That is not a valid command.\nType HELP for a list of valid commands.");
                            playerInput = "";
                            playerText.setString(playerInput);
                            refresh();
                        }
                    }
                    else if (screen == 3)
                    {
                        screen = 1;
                        menu();
                        refresh();
                    }
                    else if (screen == 4)
                    {
                        screen = 1;
                        menu();
                        refresh();
                    }
                    refresh();
                    messageText.setString("");
                }
            }

            window.setKeyRepeatEnabled(false);
        }

        
    }



    return 0;
}

sf::String toUpper(sf::String s)
{
    // convert string to upper case
    sf::String str = s;
    for (auto& c : str) c = toupper(c);
    return str;
}

void menu()
{
    font.loadFromFile("Fonts/BLKCHCRY.TTF");
    

    title.setFont(font);
    title.setCharacterSize(70);
    title.setString("Escape Room");
    title.setOrigin(title.getLocalBounds().width / 2.0f, title.getLocalBounds().height / 2.0f);
    title.setPosition(width / 2.0f, height / 20);


    option1.setFont(font);
    option1.setCharacterSize(50);
    option1.setString("Play");
    option1.setOrigin(option1.getLocalBounds().width / 2.0f, option1.getLocalBounds().height / 2.0f);
    option1.setPosition(width / 2.0f, height - 500);


    option2.setFont(font);
    option2.setCharacterSize(50);
    option2.setString("Credits");
    option2.setOrigin(option2.getLocalBounds().width / 2.0f, option2.getLocalBounds().height / 2.0f);
    option2.setPosition(width / 2.0f, height - 400);


    option3.setFont(font);
    option3.setCharacterSize(50);
    option3.setString("Exit");
    option3.setOrigin(option3.getLocalBounds().width / 2.0f, option3.getLocalBounds().height / 2.0f);
    option3.setPosition(width / 2.0f, height - 300);



    playerText.setFont(font);
    playerText.setCharacterSize(30);
    playerText.setOrigin(playerText.getLocalBounds().width / 2.0f, playerText.getLocalBounds().height / 2.0f);
    playerText.setPosition(width / width + 50, height - 50);
    playerText.setString("");


    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setPosition(width / width + 45, height - 55);

    playerInput = "";

}

void game()
{
    font.loadFromFile("Fonts/BLKCHCRY.TTF");

    gameText.setFont(font);
    gameText.setCharacterSize(30);
    gameText.setOrigin(gameText.getLocalBounds().width / 2.0f, gameText.getLocalBounds().height / 2.0f);
    gameText.setPosition(width / width + 50, height / height + 30);
    gameText.setString("You find yourself locked in a room. In it, there is a door with \ntwo different coloured locks on it. One lock is coloured blue,\nand the other is coloured red. There is also a chest, a cabinet,\nand a cupboard.");

    messageText.setFont(font);
    messageText.setCharacterSize(30);
    messageText.setOrigin(messageText.getLocalBounds().width / 2.0f, gameText.getLocalBounds().height / 2.0f);
    messageText.setPosition(width / width + 50, height - 150);
    messageText.setString("");

    playerText.setFont(font);
    playerText.setCharacterSize(30);
    playerText.setOrigin(playerText.getLocalBounds().width / 2.0f, playerText.getLocalBounds().height / 2.0f);
    playerText.setPosition(width / width + 50, height - 50);


    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setPosition(width / width + 45, height - 55);
}

void winScreen()
{
    font.loadFromFile("Fonts/BLKCHCRY.TTF");

    winTitle.setFont(font);
    winTitle.setCharacterSize(70);
    winTitle.setString("You Win!");
    winTitle.setOrigin(winTitle.getLocalBounds().width / 2.0f, winTitle.getLocalBounds().height / 2.0f);
    winTitle.setPosition(width / 2.0f, height / 20);

    winMessageText.setFont(font);
    winMessageText.setCharacterSize(30);
    winMessageText.setOrigin(winMessageText.getLocalBounds().width / 2.0f, winMessageText.getLocalBounds().height / 2.0f);
    winMessageText.setPosition(width / 4.0f, height / 2.0f);
    winMessageText.setString("Press enter to go back to the menu.");

    playerText.setFont(font);
    playerText.setCharacterSize(30);
    playerText.setOrigin(playerText.getLocalBounds().width / 2.0f, playerText.getLocalBounds().height / 2.0f);
    playerText.setPosition(width / width + 50, height - 50);


    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setPosition(width / width + 45, height - 55);
}

void credits()
{

    font.loadFromFile("Fonts/BLKCHCRY.TTF");

    creditTitle.setFont(font);
    creditTitle.setCharacterSize(50);
    creditTitle.setString("CREDITS");
    creditTitle.setOrigin(creditTitle.getLocalBounds().width / 2.0f, creditTitle.getLocalBounds().height / 2.0f);
    creditTitle.setPosition(width / 2.0f, height / 20);

    creditText.setFont(font);
    creditText.setCharacterSize(26);
    creditText.setOrigin(creditText.getLocalBounds().width / 2.0f, creditText.getLocalBounds().height / 2.0f);
    creditText.setPosition(width / 12.0f, height - 500);
    creditText.setString("Programming - Zach Lemmon\nUI - Zach Lemmon\n\nAssets Used:\nSFML libraries from https://www.sfml-dev.org/ \nPublic Domain Font: Black Chancery Regular\nFont by Doug Miles from\nhttp://www.publicdomainfiles.com/show_file.php?id=13487095304649");

    returnText.setFont(font);
    returnText.setCharacterSize(30);
    returnText.setOrigin(returnText.getLocalBounds().width / 2.0f, returnText.getLocalBounds().height / 2.0f);
    returnText.setPosition(width / 4.0f, height - 50);
    returnText.setString("Press enter to go back to the menu.");
}

void render()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Escape Room");
    return;
}

void refresh()
{
    if (screen == 1)
    {
        window.clear();
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.draw(shape);
        window.draw(playerText);
        window.display();
    }
    else if (screen == 2)
    {
        window.clear();
        window.draw(gameText);
        window.draw(messageText);
        window.draw(shape);
        window.draw(playerText);
        window.display();
    }
    else if (screen == 3)
    {
        window.clear();
        window.draw(winTitle);
        window.draw(winMessageText);
        window.draw(shape);
        window.draw(playerText);
        window.display();
    }
    else if (screen == 4)
    {
        window.clear();
        window.draw(creditTitle);
        window.draw(creditText);
        window.draw(returnText);
        window.display();
    }

    return;
}

void setObject1()
{
    object1.objectName = toUpper(playerText.getString().substring(4, findWordStart - 5));
    if (object1.objectName == "CROWBAR")
    {
        object1 = objects[8];
    }
    else if (object1.objectName == "BLUE KEY")
    {
        object1 = objects[6];
    }
    else if (object1.objectName == "RED KEY")
    {
        object1 = objects[7];
    }
    else
    {
        messageText.setString("This object cannot be used.");
    }
    
}

void setObject2()
{
    if (findWordStart + 3 >= playerInput.getSize())
    {
        messageText.setString("You must specify an object to use this on.");
    }
    else
    {
        object2.objectName = toUpper(playerText.getString().substring(findWordStart + 3, playerInput.getSize()));
        if (object2.objectName == "DOOR")
        {
            object2 = objects[0];
        }
        else if (object2.objectName == "CUPBOARD")
        {
            object2 = objects[1];
        }
        else if (object2.objectName == "CABINET")
        {
            object2 = objects[2];
        }
        else if (object2.objectName == "CHEST")
        {
            object2 = objects[3];
        }
        else if (object2.objectName == "BLUE LOCK")
        {
            object2 = objects[4];
        }
        else if (object2.objectName == "RED LOCK")
        {
            object2 = objects[5];
        }
        else if (object2.objectName == "BLUE KEY")
        {
            object2 = objects[6];
        }
        else if (object2.objectName == "RED KEY")
        {
            object2 = objects[7];
        }
        else if (object2.objectName == "CROWBAR")
        {
            object2 = objects[8];
        }
        else
        {
            messageText.setString("This object does not exist.");
            return;
        }
    }
    useLogic();
}

void useLogic()
{
    messageText.setString("This is inside useLogic");
    if (object1.objectType == "Key" && object1.objectCanBeTaken == true && object2.objectType == "Lock" && object1.objectColour == object2.objectColour && object2.objectLocked == true)
    {
        messageText.setString("The key fits perfectly and opens the lock!");
        if (object2.objectColour == "Blue")
        {
            objects[4].objectLocked = false;
            objects[4].objectDescription += "\nThis lock has been unlocked.";
            if (objects[4].objectLocked == false && objects[5].objectLocked == false)
            {
                objects[0].objectLocked = false;
                screen = 3;
                winScreen();
            }
        }
        else if (object2.objectColour == "Red")
        {
            objects[5].objectLocked = false;
            objects[5].objectDescription += "\nThis lock has been unlocked.";
            if (objects[4].objectLocked == false && objects[5].objectLocked == false)
            {
                objects[0].objectLocked = false;
                screen = 3;
                winScreen();
            }
        }
        else
        {
            messageText.setString("This is end of lock check.");
        }
    }
    else if (object1.objectName == "CROWBAR" && object1.objectCanBeTaken == true && object2.objectName == "CABINET" && objects[6].objectCanBeTaken == true)
    {
        messageText.setString("You have already done this and taken the BLUE KEY.");
    }
    else if (object1.objectName == "CROWBAR" && object1.objectCanBeTaken == true && object2.objectName == "CABINET" && object2.objectLocked == false)
    {
        messageText.setString("You stick the crowbar into the crack in the drawer and\nwrench open a false panel, revealing a blue key which you\ntake.");
        objects[6].objectCanBeTaken = true;
    }
    else if (object1.objectType == "Key" && object1.objectCanBeTaken == true && object2.objectType == "Lock" && object1.objectColour == object2.objectColour && object2.objectLocked == false)
    {
        messageText.setString("You have already unlocked this lock!");
    }
    else if (object1.objectType == "Key" && object1.objectCanBeTaken == false || object1.objectType == "Item" && object1.objectCanBeTaken == false)
    {
        messageText.setString("You do not have this yet!");
    }
    else if (object1.objectType != "Key" && object1.objectType != "Item")
    {
        messageText.setString("This cannot be used.");
    }
    else if (object1.objectType == "Key" && object1.objectCanBeTaken == true && object2.objectType != "Lock")
    {
        messageText.setString("This must be used on a lock!");
    }
    else if (object1.objectType == "Key" && object1.objectCanBeTaken == true && object2.objectType == "Lock" && object1.objectColour != object2.objectColour)
    {
        messageText.setString("This key does not fit this lock!");
    }
    else if (object1.objectName == "CROWBAR" && object1.objectCanBeTaken == true && object2.objectName != "CABINET")
    {
        messageText.setString("This cannot be used on that");
    }
    else
    {
        messageText.setString("Something went wrong");
    }
}

sf::String lookLogic(sf::String str)
{
    sf::String desc = "";

    if (str == objects[0].objectName)
        desc = objects[0].objectDescription;
    else if (str == objects[1].objectName)
        desc = objects[1].objectDescription;
    else if (str == objects[2].objectName)
        desc = objects[2].objectDescription;
    else if (str == objects[3].objectName)
        desc = objects[3].objectDescription;
    else if (str == objects[4].objectName)
        desc = objects[4].objectDescription;
    else if (str == objects[5].objectName)
        desc = objects[5].objectDescription;
    else if (str == objects[6].objectName)
        desc = objects[6].objectDescription;
    else if (str == objects[7].objectName)
        desc = objects[7].objectDescription;
    else if (str == objects[8].objectName)
        desc = objects[8].objectDescription;
    else
        desc = "This is not something that can be looked at";
    
    return desc;
}

sf::String checkLogic(sf::String str)
{
    sf::String desc = "";

    if (str == objects[0].objectName)
        desc = objects[0].objectDescription;
    else if (str == objects[1].objectName)
    {
        if (objects[7].objectCanBeTaken == true)
        {
            desc = "You have already done this!";
        }
        else
        {

            objects[7].objectCanBeTaken = true;
            desc = "On closer inspection, you notice that the strange markings\nare drag marks. You push the cupboard to the side and\ndiscover a small alcove containing a red key,\nwhich you take.";
        }
    }
    else if (str == objects[2].objectName)
        desc = objects[2].objectDescription;
    else if (str == objects[3].objectName)
    {
        objects[8].objectCanBeTaken = true;
        desc = "You look inside the chest and find a crowbar, which you take.";
    }
    else if (str == objects[4].objectName)
        desc = objects[4].objectDescription;
    else if (str == objects[5].objectName)
        desc = objects[5].objectDescription;
    else if (str == objects[6].objectName)
        desc = objects[6].objectDescription;
    else if (str == objects[7].objectName)
        desc = objects[7].objectDescription;
    else if (str == objects[8].objectName)
        desc = objects[8].objectDescription;
    else
        desc = "This is not something that can be checked";

    return desc;
}