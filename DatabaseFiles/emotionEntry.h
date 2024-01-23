#include <mariadb/conncpp.hpp>
#include <string>
using namespace std;

#ifndef EMOTIONENTRY_H
#define EMOTIONENTRY_H

class emotionEntry {
public:
     emotionEntry();
     emotionEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString art_piece, sql::SQLString emotion);
     string text();
     string json();
     
  string id;
  string timestamp;
  string art_piece;
  string emotion;

private:

};

#endif /* EMOTIONENTRY_H */
