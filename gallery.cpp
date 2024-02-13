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
			cout<<word<<endl; 
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

// string jsonSummaryEmotion(map<string, map<string, int> myMap){
// 	string result = "\"results\":[";
// 	for (auto art : myMap) {
// 		bool first = true;
// 		
// 		// Iterate over outer map
//         string artName = art.first;
// 		
// 		string emotion;
//         int count;
// 		for (auto emo : myMap[art]){
// 			emotion = emo.first;
// 			count = emo.second;
// 		}
// 		
//         if (not first) result += ",";
//         result += "{\""+artName+"\":{\""+emotion+"\":"+count+"}}";
//         first = false;
//     }
//     result += "]";
//     return result;
// }


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
  	vector<string> exhibitionLink;
  	map<string, string> allExhibitions = gldb.getAllExhibitions(exhibitionList, exhibitionLink);
  	
  	string result;
  	if (allExhibitions.size() == 0){
  		result = "{\"status\": \"failed\"}";
  	}
  	
  	else {
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
  		for (auto link : exhibitionLink){
  			if (not first) result += ",";
  			result += "\""+ link + "\"";
  			first = false;
  		}
  		result += "]}";
  	}
  	
  	res.set_content(result, "text/json");
    res.status = 200;
  });
  
	  // svr.Get(R"(/response/addEmotion/(.*)/(.*))", [&](const Request& req, Response& res) {
	  //   res.set_header("Access-Control-Allow-Origin","*");
	  //   string exhibition = req.matches[1];
	  //   string emotion = req.matches[2];
	  //   string result;
	    
	  //   gldb.addEmotion(art_piece, emotion);
	  //   result = "{\"status\":\"success\",\"art_piece\":\"" + art_piece + "\",\"emotion\":\"" + emotion + "\"}";
	    
	  //   res.set_content(result, "text/json");
	  //   res.status = 200;
	  // });

  
svr.Get(R"(/response/word/(.*)/(.*))", [&](const Request& req, Response& res) {
res.set_header("Access-Control-Allow-Origin","*");
string exhibition = req.matches[1];
string word = req.matches[2];
string result;

gldb.addEntryWord(exhibition, word);
result = "{\"status\":\"success\",\"exhibition\":\"" + exhibition + "\",\"word\":\"" + word + "\"}";

res.set_content(result, "text/json");
res.status = 200;
});

svr.Get(R"(/retrieve/words/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
res.set_header("Access-Control-Allow-Origin","*");

string exhibition = req.matches[1];
vector<string> wordResult = gldb.getWords(exhibition); 
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
	cout << "adding link" << endl;
	gldb.addEntry(name,link);

	res.set_content("{\"status\":\"success\"}", "text/json");
	res.status = 200;
}); 	

svr.Get(R"(/exhibition/update/(.*)/(.*)/(.*))", [&](const httplib::Request& req, httplib::Response& res) {
	res.set_header("Access-Control-Allow-Origin","*");

	string ID = req.matches[1];
	string name = req.matches[2];
	string link = req.matches[3];
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
 
// Summary Page for Emotions
	// svr.Get(R"(/response/summaryEmotion)", [&](const Request& req, Response& res){
	//   	res.set_header("Access-Control-Allow-Origin","*");
	//   	vector<string> exhibitionVec;
	//   	vector<string> emoVec;
	//   	vector<string> countVec;
	  	
	//   	gldb.summaryEmotion(emoVec, artVec, countVec);
	//   	string result;
	  	
	//   	if (artVec.size() > 0 && emoVec.size() > 0 && countVec.size() > 0){
	//   		result = "{\"status\":\"success\", ";
	//   		string emoStr = "\"emotions\":[";
	//   		string artStr = "\"arts\":[";
	//   		string countStr = "\"counts\":[";
	//   		bool first = true;
	//   		for (int i=0; i<artVec.size(); i++){
	//   			if (not first) {
	//   				artStr += ",";
	//   				emoStr += ",";     
	//   				countStr += ",";
	//   			}
	//   			artStr += "\"" + artVec[i] + "\"";
	//   			emoStr += "\"" + emoVec[i] + "\"";
	//   			countStr += countVec[i];
	//   			first = false;
	//   		}
	//   		artStr += "]";
	//   		emoStr += "]";
	//   		countStr += "]";
	//   		result += emoStr + "," + artStr + "," + countStr + "}";
	//   	}
	//   	else
	//   		result = "{\"status\":\"failed\"}";
	  		
	//   	res.set_content(result, "text/json");
	//   	res.status = 200;
	//   });


  
  cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);
  
   
}
