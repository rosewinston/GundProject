#include "wordEntry.h"

wordEntry::wordEntry() {
}

wordEntry::wordEntry(sql::SQLString id, sql::SQLString timestamp, sql::SQLString word) {
    this->id = id;
    this->timestamp = timestamp;
    this->word = word;
 
}

string wordEntry::text() {
	string result = id + ". ";
	result += timestamp + " ";
	result += word;
	return result;

}

string wordEntry::json() {
	string result = "{\"id\":\"" + id + "\",";
	result += "\"timestamp\":\"" + timestamp + "\",";
	result += "\"word\":\"" + word + "\"}";
	return result;
}
