#include "artEntry.h"

artEntry::artEntry() {
}

artEntry::artEntry(sql::SQLString id, sql::SQLString name, sql::SQLString link){
    this->ID = id;
    this->Name = name;
    this->Link = link;
}

string artEntry::text() {
	string result = ID + ". ";
	result += Name + " ";
	result += Link;
	return result;
}

string artEntry::json() {
	string result = "{\"ID\":\"" + ID + "\",";
	result += "\"Name\":\"" + Name +  "\",";
	result += "\"Link\":\"" + Link + "\"}";
	return result;
}