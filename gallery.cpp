#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "httplib.h"
#include "DatabaseFiles/galleryDB.h"
#include <string>

using namespace httplib;
using namespace std;

const int port = 5005;

string getWordJSON(vector<string> &wordList){
	string result; 
	
	if (wordList.size()==0){
		result = "{\"status\": \"failed\"}";
		return result;
	}
	else{
		result = "{\"status\": \"success\", \"words\":[";
		bool first = true;
		//string words = "\"words\":[";
		
		for (string word : wordList){
			std::cout<<word<<endl; 
			if (not first) result += ",";
			result += "\"" + word + "\"";
			first = false;
 		}
		result += "]}";
		return result;
   }
}

 string jsonResults(vector<exhibitionEntry> pbList) {
	string res = "{\"results\":[";
	for (int i = 0; i<pbList.size(); i++) {
		res += pbList[i].json();
		if (i < pbList.size()-1) {
			res +=",";
		}
	}
	res += "]}";
	return res;
}

//Replaces all occurances of a string within a string
string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

// Takes string and replaces all occurances of "-SLASH-" with "/" and "|" with "?" to fix the URL for display
string decryptUrl(string url){
	string fixedUrl = ReplaceAll(url,"-SLASH-","/");
	fixedUrl = ReplaceAll(fixedUrl,"|","?");
	return fixedUrl;
}

int main(void) {
  Server svr;
  // Object of GalleryDB
  galleryDB gldb;
  vector<exhibitionEntry> results;
  /* "/" just returnsAPI name */
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content("Gallery API", "text/plain"); 
  });
  
  	// Get all exhibition pieces names
	svr.Get(R"(/response/getAllExhibitions)", [&](const Request& req, Response& res){
		res.set_header("Access-Control-Allow-Origin","*");
		vector<string> exhibitionList;
		vector<string> exhibitionInfo;
		map<string, string> allExhibitions = gldb.getAllExhibitions(exhibitionList, exhibitionInfo);
		string result;
		//std::cout << "begin Get" << endl;
		if (allExhibitions.size() == 0){
			std::cout << "allExhibitions too small" << endl;
			result = "{\"status\": \"failed\"}";
		}
		
		else {
			// std::cout << "call recieved- else statement" << endl;
			result = "{\"status\": \"success\", \"exhibitions\":[";
			bool first = true;
			for (auto it : allExhibitions) {
				if (not first) result += ",";
				string exhibition = it.first;
				string link = it.second;
				string json = "{\""+exhibition+"\":\""+link+"\"}";
				result += json;
				first = false;
			}
			result += "], \"exhibitions\":[";
			
			first = true;
			for (auto exhibition : exhibitionList){
				if (not first) result += ",";
				result += "\""+ exhibition + "\"";
				first = false;
			}
			result += "], \"links\":[";
			
			first = true;
			for (auto link : exhibitionInfo){
				if (not first) result += ",";
				result += "\""+ link + "\"";
				first = false;
			}
			result += "]}";
		}
		
		res.set_content(result, "text/json");
		res.status = 200;
 	});
  
	//listener for adding a word to the database
	svr.Get(R"(/response/word/(.*)/(.*))", [&](const Request& req, Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");
		string exhibition = req.matches[1];
		string word = req.matches[2];
		string result;
		string eID = gldb.geteID(exhibition);
		gldb.addEntryWord(eID, word);
		result = "{\"status\":\"success\",\"eID\":\"" + eID + "\",\"word\":\"" + word + "\"}";

		res.set_content(result, "text/json");
		res.status = 200;
	});

	svr.Get(R"(/retrieve/words/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");

		string exhibition = req.matches[1];
		string eID = gldb.geteID(exhibition);
		vector<string> wordResult = gldb.getWords(eID); 
		string json = getWordJSON(wordResult); 
		
		res.set_content(json, "text/json");
		res.status = 200;
	});

	svr.Get(R"(/admin/join/(.*)/(.*))",  [&](const Request& req, Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");
		string username = req.matches[1];
		string password = req.matches[2];
		string result;
		
		if (username == "GalleryAdmin" && password == "WYjX5aKujKh67m") {
			result = "{\"status\":\"success\"}";
		}
		else {
		result = "{\"status\":\"failure\"}";
		}
		res.set_content(result, "text/json");
		res.status = 200;
	});
		
	svr.Get(R"(/exhibition/find)", [&](const httplib::Request& req, httplib::Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");
		results = gldb.find("");
		string json = jsonResults(results);
			res.set_content(json, "text/json");
		res.status = 200;
	});

	svr.Get(R"(/exhibition/find/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");
		
		string name = req.matches[1];
		results = gldb.find(name);
		string json = jsonResults(results);
		res.set_content(json, "text/json");
		res.status = 200;
	});


	svr.Get(R"(/exhibition/add/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");

		string name = req.matches[1];
		string link = req.matches[2];
		std::cout << "adding exhibition" << endl;
		link = decryptUrl(link);
		gldb.addEntry(name,link);

		res.set_content("{\"status\":\"success\"}", "text/json");
		res.status = 200;
	}); 	

	svr.Get(R"(/exhibition/update/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");

		string ID = req.matches[1];
		string name = req.matches[2];
		string link = req.matches[3];
		link = decryptUrl(link);
		gldb.editEntry(ID,name,link);
		res.set_content("{\"status\":\"success\"}", "text/json");
		res.status = 200;
	}); 

	svr.Get(R"(/exhibition/delete/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
		res.set_header("Access-Control-Allow-Origin","*");

		string ID = req.matches[1];
			gldb.deleteEntry(ID);
		res.set_content("{\"status\":\"success\"}", "text/json");
		res.status = 200;
	});  

  std::cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);
  
   
}
