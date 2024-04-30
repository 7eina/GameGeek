// Game class stores and tracks data about a single game
// includes functions related to adding sessions, printing sessions, 
// and comparing games


#include "Game.h"


//constructor - initialize member variables
Game::Game(string title, int category){
    this->title = title;
    this->category = category;
    this->numSessions = 0;
    Session *sessions[MAX_ARRAY];
}

//destructor
Game::~Game() {
    for (int i = 0; i < numSessions; i++) {
        delete sessions[i];
    }
}

//sets category - within specified range (0 - 3)
void Game::setCategory(int) {
    this->category = category;
    if (category < 0) category = 0;
    else if (category >= CATEGORY_MAX) category = 3;
}

//getter ^
int Game::getCategory() {
    return this->category;
}


//other

//returns true if this Game's title comes before g's title alphabetically
bool Game::lessThan(Game& g) {
    if (this->title.compare(g.title) < 0) return true;
    else return false;
}

//returns true if this Game's title is equal to title passed in
bool Game::equals(string t) {
    if (this->title == t) return true;
    else return false;
}

//adds session to sessions array in order defined by Session::lessThan()
//returns true if session was added successfully
bool Game::addSession(Date& date, int duration, string achievement) {
    if (numSessions == MAX_ARRAY) {
        cout << "Error: Session array is full." << endl;
        return false;
    }
    else {
        Session* s = new Session(date, duration, achievement);
        int index = 0;
        //if no prev sessions add session @i=0
        if (numSessions == 0) {
            sessions[0] = s;
            numSessions++;
            return true;
        }
        else {
            //find index as defined by Session::lessThan()
            while (index < numSessions && sessions[index]->lessThan(*s)) {
                index++;
            }
            //shift array elts right
            for (int j = numSessions; j > index; j--) {
                sessions[j] = sessions[j-1];
            }
            //add session
            sessions[index] = s;
            numSessions++;
        }
        return true;
    }
}

//returns total minutes played for this game for all sessions
int Game::minutesPlayed() {
    int totalTime = 0;
    for (int i = 0; i < numSessions; i++) {
        totalTime = totalTime + sessions[i]->getDuration();
    }
    return totalTime;
}

//returns total minutes spent playing this game on given date
int Game::minutesPlayedOnDate(Date& d) {
    int totalTimeOnDate = 0;
    for (int i = 0; i < numSessions; i++) {
        if (sessions[i]->matchesDate(d)) {
            totalTimeOnDate = totalTimeOnDate + sessions[i]->getDuration();
        }
    }
    return totalTimeOnDate;
}

//prints Game metadata
void Game::print() {
    cout << "Title: " << title << endl;
    cout << "Category: " << CATEGORIES[category] << endl;
    cout << "Number of sessions: " << numSessions << endl;
    cout << "Total minutes played: " << minutesPlayed() << endl;
}

//prints game metadata and all sessions of this game
void Game::printSessions() {
    Game::print();
    for (int i = 0; i < numSessions; i++) {
        sessions[i]->print();
    }
}