
#ifndef GAME_H
#define GAME_H

#include "Session.h"
#include "defs.h"



class Game {

    public:
        //constructor
        Game(string, int);

        //destructors
        ~Game();

        //setters
        void setCategory(int);

        //getters
        int getCategory();

        //other
        bool lessThan(Game&);
        bool equals(string);
        bool addSession(Date&, int, string);
        void printSessions();
        void print();
        int minutesPlayed();
        int minutesPlayedOnDate(Date&);

    private:
        //variables
        string title;
        int category;
        Session* sessions[MAX_ARRAY]{};
        int numSessions;
        
};


#endif