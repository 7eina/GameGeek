
#ifndef GAMEGEEK_H
#define GAMEGEEK_H

#include "Game.h"

class GameGeek {

    public:
        //constructor
        GameGeek();

        //destructor
        ~GameGeek();

        //other
        void addGame(string, int);
        void removeGame(string);
        bool addSession(string, Date&, int, string);

        //extracting + printing data
        void minutesPlayedInCategory(int);
        void minutesPlayedAllCategories();
        void printFaveGame();
        void printFaveGameOnDate(Date&);
        void printAllGames();
        void printSessions(string);

    private:
        //variables
        Game* games[MAX_ARRAY];
        int numGames;

        //functions
        Game* getGame(string);
};

#endif

