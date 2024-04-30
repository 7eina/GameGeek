// GameGeek class mainatains a collection of Games and functions related to 
// making, adding, and deleting Games and Sessions. This class will also 
// print relevant information, and print appropriate error messages for any failed function calls


#include "GameGeek.h"


//constructor
GameGeek::GameGeek() {
    numGames = 0;
    Game* games[MAX_ARRAY];
}

//destructor
GameGeek::~GameGeek() {
    for (int i = 0; i < numGames; i++) {
        delete games[i];
    }
}


//other

//adds game to games array in INCREASING order defined by Game::lessThan()
void GameGeek::addGame(string title, int category) {
    if (numGames == MAX_ARRAY) {
        cout << "Error: Max saved games reached, failed to add game." << endl;
        return;
    }
    else{
        Game* g = new Game(title, category);
        int index = 0;
        //if no prev games add game @i=0
        if (numGames == 0) {
            games[0] = g;
            numGames++;
        }
        else {
            //find index as defined by Game::lessThan()
            while (index < numGames && games[index]->lessThan(*g)) {
                index++;
            }
            //shift array elts right
            for (int j = numGames; j > index; j--) {
                games[j] = games[j-1];
            }
            //add game
            games[index] = g;
            numGames++;
        }
        cout << "Game " << title << " added successfully." << endl;
    }
}

//returns pointer to the game with the given title or nullptr otherwise
Game* GameGeek::getGame(string title) {
    int index = 0;
    while (index < numGames && !games[index]->equals(title)) {
        index++;
    }
    if (index == numGames) { //game not found - fail
        cout << "Error: Game " << title << " not found." << endl;
        return nullptr;
    }
    else { //game found - success
        cout << "Game " << title << " found." << endl;
        return games[index];
    }
}

//removes game with given title from games array and shifts array left
void GameGeek::removeGame(string title) {
    Game* g = getGame(title);
    //check if game exists in array
    if (g == nullptr) {
        cout << "Error: Game " << title << " not found." << endl;
        return;
    }
    else {
        int index = 0;
        //find game index
        while (index < numGames && !games[index]->equals(title)) {
            index++;
        }
        delete games[index];
        //shift array left
        for (int j = index; j < numGames; j++) {
            games[j] = games[j+1];
        }
        numGames--;
        cout << "Game " << title << " removed successfully." << endl;
        return;
    }
}

//find game that matches title and add session to it in order defined by Game::lessThan()
bool GameGeek::addSession(string gameTitle, Date& date, int duration, string achievement) {
    Game* g = getGame(gameTitle);
    //check if game exists
    if (g == nullptr) {
        cout << "Error: Game " << gameTitle << " not found." << endl;
        return false;
    }
    else {
        //add session to game
        g->addSession(date, duration, achievement);
        cout << "Session added successfully." << endl;
        return true;
    }
}

//prints title of category and total minutes played for all games in that category
void GameGeek::minutesPlayedInCategory(int c) {
    int catMinutes = 0;
    for (int i = 0; i < numGames; i++) {
        if (games[i]->getCategory() == c) {
            catMinutes = catMinutes + games[i]->minutesPlayed();
        }
    }
    cout << "Category: " << CATEGORIES[c] << ", ";
    cout << "Total minutes played: " << catMinutes << endl;
}

//prints title and total minutes played for all categories
void GameGeek::minutesPlayedAllCategories() {
    for (int i = 0; i < CATEGORY_MAX; i++) {
        minutesPlayedInCategory(i);
    }
}

//prints title of game with most minutes played
void GameGeek::printFaveGame() {
    int maxMins = 0;
    int faveIndex = 0;
    for (int i = 0; i < numGames; i++) {
        if (games[i]->minutesPlayed() > maxMins) {
            maxMins = games[i]->minutesPlayed();
            faveIndex = i;
        }
    }
    Game* g = games[faveIndex];
    cout << " ~~~ Favourite Game ~~~" << endl;
    g->print();
}

//prints title of game with most minutes played on given date
void GameGeek::printFaveGameOnDate(Date& date) {
    int maxMins = 0;
    int faveIndex = 0;
    for (int i = 0; i < numGames; i++) {
        if (games[i]->minutesPlayedOnDate(date) > maxMins) {
            maxMins = games[i]->minutesPlayedOnDate(date);
            faveIndex = i;
        }
    }
    Game* g = games[faveIndex];
    g->print();
}

//prints each game in GameGeek
void GameGeek::printAllGames() {
    for (int i = 0; i < numGames; i++) {
        games[i]->print();
    }
}

//every session of the game with the given title
void GameGeek::printSessions(string title) {
    Game* g = getGame(title);
    //check if game exists
    if (g == nullptr) {
        cout << "Error: Game " << title << " not found." << endl;
        return;
    }
    else {
        g->printSessions();
    }
}
