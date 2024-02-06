#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef WORDENTRY_H
#define WORDENTRY_H

class wordEntry {
public:
     wordEntry();
     wordEntry(sql::SQLString id, sql::SQLString exhibition, sql::SQLString word);
     string text();
     string json();
     
  string id;
  string exhibition;
  string word;

private:

};

#endif /* WORDENTRY_H */
