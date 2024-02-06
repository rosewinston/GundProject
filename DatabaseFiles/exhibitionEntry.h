#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef exhibitionEntry_H
#define exhibitionEntry

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
