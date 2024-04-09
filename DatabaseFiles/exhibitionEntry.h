#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef EXHIBITIONENTRY_H
#define EXHIBITIONENTRY

class exhibitionEntry {
public:
     exhibitionEntry();
     exhibitionEntry(sql::SQLString ID, sql::SQLString Name, sql::SQLString Link);
     string text();
     string json();
     
     string ID;
     string Name;
     string Link;

private:

};

#endif /* exhibitionEntry_H */
