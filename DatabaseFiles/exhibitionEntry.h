#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef EXHIBITIONENTRY_H
#define EXHIBITIONENTRY

class exhibitionEntry {
public:
     exhibitionEntry();
     exhibitionEntry(sql::SQLString ID, sql::SQLString Name, sql::SQLString Link, sql::SQLBoolean linkBool);
     string text();
     string json();
     
     string ID;
     string Name;
     string Link;
     bool linkBool;

private:

};

#endif /* exhibitionEntry_H */
