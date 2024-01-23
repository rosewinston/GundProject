#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef WORDENTRY_H
#define WORDENTRY_H

class wordEntry {
public:
     wordEntry();
     wordEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString word);
     string text();
     string json();
     
  string id;
  string timestamp;
  string word;

private:

};

#endif /* WORDENTRY_H */
