#include "exhibitionEntry.h"

exhibitionEntry::exhibitionEntry() {
}

exhibitionEntry::exhibitionEntry(sql::SQLString id, sql::SQLString name, sql::SQLString link){
    this->ID = id;
    this->Name = name;
    this->Link = link;
}

string exhibitionEntry::text() {
	string result = ID + ". ";
	result += Name + " ";
	result += Link;
	return result;
}

string exhibitionEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"Name\":\"" + Name +  "\",";
	result += "\"Link\":\"" + Link + "\"}";
	return result;
}
