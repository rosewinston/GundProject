#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef ARTENTRY_H
#define ARTENTRY

class artEntry {
public:
     artEntry();
     artEntry(sql::SQLString ID, sql::SQLString Name, sql::SQLString Link);
     string text();
     string json();
     
     string ID;
     string Name;
     string Link;

private:

};

#endif /* ARTENTRY_H */
