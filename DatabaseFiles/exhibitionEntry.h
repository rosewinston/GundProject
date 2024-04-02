#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef EXHIBITIONENTRY_H
#define EXHIBITIONENTRY

class exhibitionEntry {
public:
     exhibitionEntry();
     exhibitionEntry(sql::SQLString ID, sql::SQLString Name, sql::SQLString Link, sql::SQLBoolean Full_Link);
     string text();
     string json();
     
     string ID;
     string Name;
     string Link;
     bool Full_Link;

private:

};

#endif /* exhibitionEntry_H */
