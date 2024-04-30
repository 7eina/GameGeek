// Session class stores data about a single session of a game
// includes functions related to comparing sessions and printing sessions


#include "Session.h"


//constructor
Session::Session(Date& date, int duration, string achievement) : date(date) {
    this->duration = duration;
    this->achievement = achievement;
}


//setters
void Session::setDuration(int) {
    this->duration = duration;
    if (duration < 0) duration = 1;
}

void Session::setAchievement(string) {
    this->achievement = achievement;
}


//getters
int Session::getDuration() {
    return this->duration;
}

string Session::getAchievement() {
    return this->achievement    ;
}


//other
//checks if current session date matches the date passed in
bool Session::matchesDate(Date& d) {
    if (this->date.equals(d)) return true;
    else return false;
}

//checks if current session date is less than the date of the session passed in
bool Session::lessThan(Session& s) {
    if (this->date.lessThan(s.date)) return true;
    else return false;
}

//prints the session data (Date & Achievement)
void Session::print() {
    cout << "Played on " << this->date.getMonthName() << " ";
    cout << this->date.getDay() << ", " << this->date.getYear();
    cout << " for " << this->duration << " minutes." << endl;
    cout << "Achievement: " << this->achievement << endl;
}


