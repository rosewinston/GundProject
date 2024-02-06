#include "wordEntry.h"

wordEntry::wordEntry() {
}

wordEntry::wordEntry(sql::SQLString id, sql::SQLString exhibition, sql::SQLString word) {
    this->id = id;
    this->exhibition = exhibition;
    this->word = word;
 
}

string wordEntry::text() {
	string result = id + ". ";
	result += exhibition + " ";
	result += word;
	return result;

}

string wordEntry::json() {
	string result = "{\"id\":\"" + id + "\",";
	result += "\"exhibition\":\"" + exhibition + "\",";
	result += "\"word\":\"" + word + "\"}";
	return result;
}
