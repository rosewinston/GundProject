#include "exhibitionEntry.h"

exhibitionEntry::exhibitionEntry() {
}

exhibitionEntry::exhibitionEntry(sql::SQLString id, sql::SQLString name, sql::SQLString link, sql::SQLBoolean linkBool){
    this->ID = id;
    this->Name = name;
    this->Link = link;
    this->linkBool = linkBool;
}

string exhibitionEntry::text() {
	string result = ID + ". ";
	result += Name + " ";
	result += Link + " ";
	result += linkBool; 
	return result;
}

string exhibitionEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"Name\":\"" + Name +  "\",";
	result += "\"Link\":\"" + Link + "\"}";
	result += "\"Full_Link\":\"" + linkBool + "\"}";
	return result;
}
