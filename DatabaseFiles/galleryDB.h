#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
/* uncomment for applications that use vectors */
#include <vector>
#include <map>
#include <utility>      // std::pair, std::make_pair
#include <mariadb/conncpp.hpp>

// #include "emotionEntry.h" unused- remove later
#include "wordEntry.h"
#include "exhibitionEntry.h"

#ifndef GALLERYDB_H
#define GALLERYDB_H

#define DB_URL "jdbc:mariadb://localhost:3306/gallery"
#define USER "winston1"
#define PASS "Rose2024"

using namespace std;

class galleryDB {
public:
    //default constructor to create object to allow for interaction w/ database 
    galleryDB();
    //add user's word entry to word table in database 
    void addEntryWord(string eID, string word); 
    //get all words within the database word table for a certain exhibition 
    vector<string> getWords(string exhibition); 
    // function to get all exhibition names
    map<string, string> getAllExhibitions(vector<string> &exhibitionList, vector<string> &exhibitionLink);
    //find exhibition matching string
    vector<exhibitionEntry> find(string search);
    //return eID from exhibition name
    string geteID(string exhibition);
    // add exhibition to DB
    void addEntry(string name, string link);
    //edit exhibition name in DB
    void editEntry(string idnum,string name,string link);
    //delete exhibition in DB
    void deleteEntry(string idnum);
    
private:
    const string db_url=DB_URL;
    const string user=USER;
    const string pass=PASS;
    sql::Driver* driver;
    sql::Properties properties;
    std::unique_ptr<sql::Connection> conn;

};

#endif /* GALLERYDB_H */
