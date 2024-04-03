#include "exhibitionEntry.h"

exhibitionEntry::exhibitionEntry() {
}

exhibitionEntry::exhibitionEntry(sql::SQLString id, sql::SQLString name, sql::SQLString link, sql::string isLink){
    this->ID = id;
    this->Name = name;
    this->Link = link;
    this->isLink = isLink;
}

string exhibitionEntry::text() {
	string result = ID + ". ";
	result += Name + " ";
	result += Link + " ";
	result += isLink; 
	return result;
}

string exhibitionEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"Name\":\"" + Name +  "\",";
	result += "\"Link\":\"" + Link + "\"}";
	result += "\"isLink\":\"" + isLink + "\"}";
	return result;
}
