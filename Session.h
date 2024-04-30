
#ifndef SESSION_H
#define SESSION_H

#include "Date.h"

class Session {

    public:

        //constructor
        Session(Date&, int, string);

        //setters
        void setDuration(int);
        void setAchievement(string);

        //getters
        int getDuration();
        string getAchievement();


        //other
        void print();
        bool lessThan(Session&);
        bool matchesDate(Date&);


    private:
        //variables
        Date& date;
        int duration;
        string achievement;

};


#endif
