#include <iostream>
#include <random>
#include <sstream>
#include <unordered_set>
#include "GameGeek.h"

using namespace std;

#define NUM_GAMES 4

//global variables for testing purposes
string gameNames[NUM_GAMES] = 
{"Mario", "Zelda", "Wasteland", "Kirby"};
string orderedNames[NUM_GAMES] = {"Kirby", "Mario", "Wasteland", "Zelda"};
string orderedCats[NUM_GAMES] = {"Survival", "Platformer", "MMORP", "FPS"};

// generate a set (no duplicates) of "count" random integers
// from 0 to "range"
void ran(unordered_set<int>& s, int count, int range);
// generate a random integer in the given range
int ran(int range_from, int range_to);
int testMinutesPlayed();
int testMinutesPlayedOnDate();
int testAddGame();
int testAddGameOrder();
int testRemoveGame();
int testAddSessions();
int testAddSessionsOrder();
int testMinutesPlayedInCategory();

int testPrintFaveGame();
int testPrintFaveGameOnDate();

int main(){
    int choice = -1;
    while(choice != 0 && cin.good()){
        std::cout<<endl;
        std::cout<<" 0. Exit"<<endl;
        /* These will be a tutorial */
        std::cout<<" 1. [marked in tutorial 3] Test Game::minutesPlayed"<<endl;
        std::cout<<" 2. [marked in tutorial 3] Test Game::minutesPlayedOnDate"<<endl;
        /* ^^^^These will be a tutorial^^^^ */
           
        std::cout<<" 3. [2 marks] Test add Game to GameGeek"<<endl;
        std::cout<<" 4. [2 marks] Test add Game to GameGeek (in order)"<<endl;
        std::cout<<" 5. [2 marks] Test delete Game"<<endl;
        std::cout<<" 6. [2 marks] Test add and print sessions"<<endl;
        std::cout<<" 7. [2 marks] Test add and print sessions for correct order"<<endl; 
        std::cout<<" 8. [2 marks] Test printFaveGame"<<endl;
        std::cout<<" 9. [2 marks] Test printFaveGameOnDate"<<endl;
        std::cout<<" 10. [4 marks] Test minutesPlayedInCategory and minutesPlayedAllCategories"<<endl;


        std::cout<<" 11. [18 marks] Test all and get mark"<<endl<<endl;
        cin >> choice;
        std::cout<<endl;
        switch (choice)
        {
        case 1: testMinutesPlayed(); break;  
        case 2: testMinutesPlayedOnDate(); break;  
        case 3: testAddGame(); break;  
        case 4: testAddGameOrder(); break;  
        case 5: testRemoveGame(); break;
        case 6: testAddSessions(); break;  
        case 7: testAddSessionsOrder(); break;
        case 8: testPrintFaveGame(); break;   
        case 9: testPrintFaveGameOnDate(); break;
        case 10: testMinutesPlayedInCategory(); break;
        case 11:   int score = 0;
            score += testAddGame();
            score += testAddGameOrder(); 
            score += testRemoveGame();   
            score += testAddSessions();
            score += testAddSessionsOrder(); 
            score += testPrintFaveGame(); 
            score += testPrintFaveGameOnDate();
            score += testMinutesPlayedInCategory();
            std::cout << "Your score is "<<score<<" out of 18 (plus 2 for minutesPlayedAllCategories if applicable)"<<endl<<endl;   
            break;
        }
    }
    std::cout<<"Bye!"<<endl;
    return 0;  
}

void addGames(GameGeek& gg){
    for (int i = 0; i < NUM_GAMES; ++i){
        gg.addGame(gameNames[i], i);
    }
}

int testAddGame(){
    std::cout<<endl<<"Testing GameGeek addGame function..."<<endl<<endl;

    GameGeek gg;
    addGames(gg);
    
    //capture the output and put in a stringstream
    streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    gg.printAllGames();

    //replace std::out and print output to console
    std::cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;

    //find all Game GAMES
    int found = -1;
    for (int i = 0; i < NUM_GAMES; ++i){
        found = output.find(gameNames[i]);
        if (found == string::npos){
            std::cout<<"Game "<<gameNames[i]<<" not found"<<endl;
            std::cout<<"addGame test failed"<<endl;
            return 0;
        }
        
        found = output.find(CATEGORIES[i]);
        if (found == string::npos){
            std::cout<<"Game category "<<CATEGORIES[i]<<" not found"<<endl;
            std::cout<<"Is Game::print working properly?"<<endl;
            return 0;
        }
        
    }
    std::cout<<"All Games found, 2 marks"<<endl;
    return 2;
}

int testAddGameOrder(){
    std::cout<<endl<<"Testing GameGeek addGame function for correct order..."<<endl<<endl;

    GameGeek gg;
    addGames(gg);
    
    //capture the output and put in a stringstream
    streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    gg.printAllGames();

    //replace std::out and print output to console
    std::cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;

    //find all Game GAMES
    int found = -1;
    for (int i = 0; i < NUM_GAMES; ++i){
        found = output.find(orderedNames[i], found+1);
        if (found == string::npos){
            std::cout<<"Game "<<orderedNames[i]<<" not found in correct place"<<endl;
            std::cout<<"add Games in order test failed"<<endl;
            return 0;
        }
        
    }
    std::cout<<"All Game found in order, testing for categories in order"<<endl;

    found = -1;
    for (int i = 0; i < NUM_GAMES; ++i){
        found = output.find(orderedCats[i], found+1);
        if (found == string::npos){
            std::cout<<"Game category "<<orderedCats[i]<<" not found in correct place"<<endl;
            std::cout<<"add Games in order test failed"<<endl;
            return 0;
        }
        
    }

    std::cout<<"Games and categories found in order, 2 marks"<<endl;
    return 2;
}

int testRemoveGame(){
     std::cout<<endl<<"Testing GameGeek removeGame function..."<<endl<<endl;

    GameGeek gg;
    addGames(gg);

    //remove the Games in a certain order
    int indices[4] = {2,0,3,1};

    for (int i = 0; i < NUM_GAMES; ++i){
        gg.printAllGames();
        int index = indices[i];
        gg.removeGame(gameNames[index]);
         //capture the output and put in a stringstream
        streambuf* oldCoutStreamBuf = std::cout.rdbuf();
        ostringstream strCout;
        std::cout.rdbuf( strCout.rdbuf() );

        gg.printAllGames();

        //replace std::out and print output to console
        std::cout.rdbuf( oldCoutStreamBuf );
        string output = strCout.str();
        std::cout << output;

        //find deleted Game name
        int found = output.find(gameNames[index]);
        if (found == string::npos){
            std::cout<<"Game "<<gameNames[index]<<" removed, not found - success!"<<endl;
        }else{
            std::cout<<"Game "<<gameNames[index]<<" found"<<endl;
            std::cout<<"removeGame failed"<<endl;
            return 0;
        }
        
        
    }
    std::cout<<"Removing game that does not exist"<<endl;

    gg.removeGame(gameNames[0]);
    
    std::cout<<"removeGame success, 2 marks"<<endl;
    return 2;
    
   
        
}

int testAddSessions(){
    std::cout<<endl<<"Testing add session function..."<<endl<<endl;

    const string ach[3] = {"Found Pokimon","Mario Jumps", "Luigi says oh no" };

    GameGeek gg;
    addGames(gg);
    int score = 0;
    Date date1(2023, 4, 20);
    Date date2(2023, 4, 21);
    Date date3(2023, 8, 20);
    gg.addSession(gameNames[0], date1, 20, ach[0]);
    gg.addSession(gameNames[0], date2, 40, ach[1]);
    gg.addSession(gameNames[1], date3, 100, ach[2]);

    //capture the output and put in a stringstream
    streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    gg.printSessions(gameNames[0]);

    //replace std::out and print output to console
    std::cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;

    int found = -1;
    // find game title
    found = output.find(gameNames[0]);
    if (found == string::npos){
        std::cout<<gameNames[0]<<" not found"<<endl;
        std::cout<<"add session test failed"<<endl;
        return 0;
    } 

    //find achievements
    for (int i = 0; i < 2; ++i){
        found = output.find(ach[i]);
        if (found == string::npos){
            std::cout<<"Acheivement "<<ach[i]<<" not found"<<endl;
            std::cout<<"add and print session test failed"<<endl;
            return 0;
        }
        
    }
    found = output.find(ach[2]);
    if (found != string::npos){
        std::cout<<"Acheivement "<<ach[2]<<" found, wrong session printed"<<endl;
        std::cout<<"add and print session test failed"<<endl;
        return 0;
    }

    std::cout<<"Sessions added and printed correctly, 2 marks"<<endl<<endl;
    return 2;

}

int testAddSessionsOrder(){
    std::cout<<endl<<"Testing add sessions in order function..."<<endl<<endl;

    const string ach[3] = {"Found Pokimon","Mario Jumps", "Luigi says oh no" };
    const string achOrder[3] = {"Mario Jumps", "Luigi says oh no", "Found Pokimon" };

    GameGeek gg;
    addGames(gg);
    int score = 0;
    Date date1(2023, 4, 20);
    Date date2(2023, 4, 21);
    Date date3(2023, 8, 20);
    // date3, date1, date2
    gg.addSession(gameNames[1], date3, 20, ach[0]);
    gg.addSession(gameNames[1], date1, 40, ach[1]);
    gg.addSession(gameNames[1], date2, 100, ach[2]);

    //capture the output and put in a stringstream
    streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    gg.printSessions(gameNames[1]);

    //replace std::out and print output to console
    std::cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;

    int found = -1;
    for (int i = 0; i < 3; ++i){
        found = output.find(achOrder[i], found+1);
        if (found == string::npos){
            std::cout<<"Session with acheivement "<<achOrder[i]<<" not found in correct place"<<endl;
            std::cout<<"add session in order test failed"<<endl;
            return 0;
        }     
    }
    

    std::cout<<"Sessions added and printed correctly in order, 2 marks"<<endl<<endl;
    return 2;

}

int testPrintFaveGame(){
    std::cout<<endl<<"Testing printFaveGame function..."<<endl<<endl;

    const string ach[3] = {"Found Pokimon","Mario Jumps", "Luigi says oh no" };

    GameGeek gg;
    addGames(gg);
    Date date1(2023, 4, 20);
    Date date2(2023, 4, 21);
    Date date3(2023, 8, 20);
    unordered_set<int> indices;
    //grab 3 indices in random order
    cout<<"Grabbing random indices"<<endl;
    ran(indices, 3, 3);
    cout<<"Done grabbing random indices"<<endl;

    unordered_set<int>::iterator index = indices.begin();
    int ranSession = ran(1, 100);

    cout<<"Index "<<*index<<endl;
    gg.addSession(gameNames[*index], date1, 20, ach[0]);
    gg.addSession(gameNames[*index], date2, 40, ach[1]);
    ++index;
    cout<<"Index "<<*index<<endl;
    gg.addSession(gameNames[*index], date3, 111, ach[2]);
    gg.addSession(gameNames[*index], date1, 222, ach[0]);
    gg.addSession(gameNames[*index], date1, ranSession, ach[0]);
    int mostPopular = *index;
    ranSession += 333;
    ++index;
    cout<<"Index "<<*index<<endl;
    gg.addSession(gameNames[*index], date2, 40, ach[1]);
    gg.addSession(gameNames[*index], date3, 100, ach[2]);
    gg.addSession(gameNames[*index], date2, 40, ach[1]);
    gg.addSession(gameNames[*index], date3, 100, ach[2]);

    //capture the output and put in a stringstream
    streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    gg.printFaveGame();

    //replace std::out and print output to console
    std::cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;

    int found = -1;
    // find game title
    found = output.find(gameNames[mostPopular]);
    if (found == string::npos){
        std::cout<<gameNames[mostPopular]<<" not found"<<endl;
        std::cout<<"fave game test failed"<<endl;
        return 0;
    }

    found = output.find(to_string(ranSession));
    if (found == string::npos){
        std::cout<<"Number of minutes played not found"<<endl;
        std::cout<<"fave game test failed"<<endl;
        return 0;
    } 

    std::cout<<"FaveGame test passed, 2 marks"<<endl<<endl;
    return 2;
}

int testPrintFaveGameOnDate(){
    std::cout<<endl<<"Testing printFaveGameOnDate function..."<<endl<<endl;

    const string ach[3] = {"Found Pokimon","Mario Jumps", "Luigi says oh no" };

    GameGeek gg;
    addGames(gg);
    Date date1(2023, 4, 20);
    Date date2(2023, 4, 21);
    Date date3(2023, 8, 20);
    unordered_set<int> indices;
    //grab 3 indices in random order
    cout<<"Grabbing random indices"<<endl;
    ran(indices, 3, 3);
    cout<<"Done grabbing random indices"<<endl;

    unordered_set<int>::iterator index = indices.begin();
    int ranSession = ran(1, 100);

    cout<<"Index "<<*index<<endl;
    cout<<"ranSession: "<<ranSession<<endl;
    gg.addSession(gameNames[*index], date1, 20, ach[0]);
    gg.addSession(gameNames[*index], date2, 40, ach[1]);
    gg.addSession(gameNames[*index], date3, 40, ach[1]);
    ++index;
    cout<<"Index "<<*index<<endl;
    gg.addSession(gameNames[*index], date3, 111, ach[2]);
    gg.addSession(gameNames[*index], date1, 222, ach[0]);
    gg.addSession(gameNames[*index], date3, ranSession, ach[0]);
    int mostPopular = *index;
    ranSession += 333;
    ++index;
    cout<<"Index "<<*index<<endl;
    gg.addSession(gameNames[*index], date2, 40, ach[1]);
    gg.addSession(gameNames[*index], date3, 110, ach[2]);
    gg.addSession(gameNames[*index], date2, 40, ach[1]);
    gg.addSession(gameNames[*index], date1, 100, ach[2]);

    //capture the output and put in a stringstream
    streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );

    gg.printFaveGameOnDate(date3);

    //replace std::out and print output to console
    std::cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;

    int found = -1;
    // find game title
    found = output.find(gameNames[mostPopular]);
    if (found == string::npos){
        std::cout<<gameNames[mostPopular]<<" not found"<<endl;
        std::cout<<"fave game on date test failed"<<endl;
        return 0;
    }

    found = output.find(to_string(ranSession));
    if (found == string::npos){
        std::cout<<"Number of minutes played "<<ranSession<<" not found"<<endl;
        std::cout<<"fave game on date test failed"<<endl;
        return 0;
    } 

    std::cout<<"faveGameOnDate test passed, 2 marks"<<endl<<endl;
    return 2;
}


int testMinutesPlayedInCategory(){
    string gameNames[6] = {"Mario", "Zelda", "Wasteland", "Kirby", "Sonic", "Minecraft"};
    int cats[6] = {1,3,2,3,1,3};
    int sess[18];

    for (int i = 0; i < 18; ++i){
        sess[i] = ran(5,20);
    }
    GameGeek gg;

    Date d1(2023, 5, 4);
    int mpc[4] = {0,0,0,0};
    for (int i = 0; i < 6; ++i){
        gg.addGame(gameNames[i], cats[i]);
        for (int j = 0; j < 3; ++j){
            gg.addSession(gameNames[i], d1, sess[i*3+j],"Died");
            mpc[cats[i]]+=sess[i*3+j];
        }
    }

    
    for(int i = 0; i < 4; ++i){
        //capture the output and put in a stringstream
        streambuf* oldCoutStreamBuf = std::cout.rdbuf();
        ostringstream strCout;
        std::cout.rdbuf( strCout.rdbuf() );

        gg.minutesPlayedInCategory(i);

        //replace std::out and print output to console
        std::cout.rdbuf( oldCoutStreamBuf );
        string output = strCout.str();
        std::cout << output;

        int found = -1;
        // find game title
        found = output.find(CATEGORIES[i]);
        if (found == string::npos){
            std::cout<<CATEGORIES[i]<<" not found"<<endl;
            std::cout<<"minutes played in category test failed"<<endl;
            return 0;
        }

        found = -1;
        // find game title
        found = output.find(to_string(mpc[i]));
        if (found == string::npos){
            std::cout<<"Minutes played in "<<CATEGORIES[i]<< " should be "<<to_string(mpc[i])<<endl;
            std::cout<<"minutes played in category test failed"<<endl;
            return 0;
        }
    }


    cout<<endl<<"**** testing minutesPlayedAllCategories ****"<<endl<<endl;
    gg.minutesPlayedAllCategories();
    cout<<endl<<"***MANUAL MARKS****\nIf minutesPlayedAllCategories executes correctly, add 2 marks"<<endl;

    cout<<"minutesPlayedInCategory test passed, 2 marks."<<endl;

    return 2;
}

// s is the set to store count random numbers from 0 to range - 1
void ran(unordered_set<int>& s, int count, int range){
    const int range_from  = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range-1);

    while (s.size() < count){
        s.insert(distr(generator));
    }
}

// generate and return a single random number in the range range_from to range_to - 1
int ran(int range_from, int range_to){
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to-1);
    return distr(generator);
}

int testMinutesPlayed(){
    cout<<"Testing minutes played of Game"<<endl;
    Game g1("Mario", 1);
    Date d1(2023, 5, 4);
    int total = 0;
    for (int i = 0; i < 5; ++i){
        g1.addSession(d1, (i+1)*10, "Died");
        total += (i+1)*10;
    }

    cout<<"All sessions added"<<endl;
    g1.print();

    if (total != g1.minutesPlayed()){
        cout<<"minutesPlayed is "<<g1.minutesPlayed()<<", should be "<<total<<endl;
        return 1;
    }

    streambuf* oldCoutStreamBuf = cout.rdbuf();
    ostringstream strCout;
    cout.rdbuf( strCout.rdbuf() );

    cout<<"Calling Game::print()"<<endl;
    g1.print();

    //replace std::out and print output to console
    //std::cout.rdbuf( oldCoutStreamBuf );
    // Restore old cout.
    cout.rdbuf( oldCoutStreamBuf );
    string output = strCout.str();
    std::cout << output;
    //find Game name
    int found = output.find("Mario");
    if (found == string::npos){
        std::cout<<"Mario not found, test failed"<<endl;
        return 1;
    }

    found = output.find(to_string(total));
    if (found == string::npos){
        std::cout<<"Total minutes played of "<<total<<" not found in Game::print, test failed"<<endl;
        return 1;
    }

    cout<<"minutesPlayed test passed!"<<endl;

    return 0;
}

int testMinutesPlayedOnDate(){
    Game g1("Mario", 1);
    Date d1(2023, 5, 4);
    Date d2(2023, 6, 1);
    Date d3(2023, 8, 11);
    int total1 = 0, total2 = 0, total3 = 0;
    for (int i = 0; i < 5; ++i){
        g1.addSession(d1, (i+1)*10, "Died");
        total1 += (i+1)*10;
    }

    for (int i = 0; i < 3; ++i){
        g1.addSession(d2, (i+1)*10, "Died");
        total2 += (i+1)*10;
    }

    for (int i = 0; i < 6; ++i){
        g1.addSession(d3, (i+1)*10, "Died");
        total3 += (i+1)*10;
    }

    g1.print(); 

    bool passed = true;

    if (total1 != g1.minutesPlayedOnDate(d1)){
        passed = false;
        cout<<"For the date: "<<endl;
        d1.print(); cout <<endl;
        cout<<"minutesPlayedOnDate is "<<g1.minutesPlayedOnDate(d1)<<", should be "<<total1<<endl;
    }

    if (total2 != g1.minutesPlayedOnDate(d2)){
        passed = false;
        cout<<"For the date: "<<endl;
        d2.print(); cout <<endl;
        cout<<"minutesPlayedOnDate is "<<g1.minutesPlayedOnDate(d2)<<", should be "<<total2<<endl;
    }

    if (total3 != g1.minutesPlayedOnDate(d3)){
        passed = false;
        cout<<"For the date: "<<endl;
        d3.print(); cout <<endl;
        cout<<"minutesPlayedOnDate is "<<g1.minutesPlayedOnDate(d3)<<", should be "<<total3<<endl;
    }
    

    cout<<endl<<"minutesPlayedOnDate test "<<(passed ? "passed":"failed")<<endl;

    return 0;
}

