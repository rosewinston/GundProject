#include <vector>
#include <iostream>
#include <mariadb/conncpp.hpp>
#include "galleryDB.h"


galleryDB::galleryDB() {
  	// Instantiate Driver
  	driver = sql::mariadb::get_driver_instance();
  	
 	// Configure Connection
  	// The URL or TCP connection string format is
  	// ``jdbc:mariadb://host:port/database``.
  	sql::SQLString url(db_url);

    // Use a properties map for the other connection options
  	sql::Properties my_properties({{"user", user}, {"password", pass}});
  	// Save properties in object
  	properties = my_properties;

    // Establish Connection
  	std::unique_ptr<sql::Connection> my_conn(driver->connect(db_url, properties));
    
    // Check success
    if (!my_conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}	
   	
   	// Save connection in object
   	conn = std::move(my_conn);
   	
}

void galleryDB::addEntryWord(string exhibition, string word){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	stmnt->executeQuery("INSERT INTO word_response(exhibition, word) VALUES ('"+exhibition+"','"+word+"')");
}


// void galleryDB::addEmotion(string exhibition, string emotion){

// 	if (!conn) {
//    		cerr << "Invalid database connection" << endl;
//    		exit (EXIT_FAILURE);
//   	}

//   	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

//   	stmnt->executeQuery("INSERT INTO emotion_response(exhibition, emotion) VALUES ('"+exhibition+"','"+emotion+"')");
// }


vector<string> galleryDB::getWords(string exhibition){
	string word;
	vector<string> wordList; 
	if (!conn)
	{
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
	sql::ResultSet *res = stmnt->executeQuery("SELECT word FROM word_response WHERE exhibition = '" + exhibition + "'");
	while (res->next())
	{
		word = res->getString("word");
		wordList.push_back(word); 
		
	}
	return wordList;
}
	
// Get all exhibitions function
map<string, string> galleryDB::getAllExhibitions(vector<string> &exhibitionList, vector<string> &exhibitionLink, vector<string> &exhibitionisLink) {
	map<string, string> list;
	if (!conn) {
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	
  	sql::ResultSet *res = stmnt->executeQuery(
			"SELECT DISTINCT Name, Link, isLink FROM exhibitions"
	);
    
    // Loop through and print results
    while (res->next()) {
    	string exhibition;
    	exhibition = res->getString("Name");
    	string link;	
    	link = res->getString("Link");
	    list[exhibition] = link;
	    exhibitionList.push_back(exhibition);
	    exhibitionLink.push_back(link);
    }
    
    return list;
}


vector<exhibitionEntry> galleryDB::find(string search) {
	vector<exhibitionEntry> list;
    
    // Make sure the connection is still valid
    if (!conn) {
		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
   	}	
    // Create a new Statement
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    // Execute query
    sql::ResultSet *res = stmnt->executeQuery(
			"SELECT * FROM exhibitions WHERE Name like '%"+search+"%'");
    
    // Loop through and print results
	while (res->next()) {
    	exhibitionEntry entry(res->getString("ID"),res->getString("Name"),res->getString("Link"),res->getString("isLink");
	    list.push_back(entry);

    }
    return list;

}


void galleryDB::addEntry(string name, string link){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
  	stmnt->executeQuery("INSERT INTO exhibitions(Name,Link) VALUES ('"+name+"','"+link+"')");
}

// exhibitionEntry galleryDB::fetchexhibition(string id){

// 	exhibitionEntry entry;	
	
// 	if (!conn) {
//    		cerr << "Invalid database connection" << endl;
//    		exit (EXIT_FAILURE);
//   	}

//   	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
//     sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM exhibitions WHERE ID = '"+id+"'");
    
//     // Get first entry
//     if (res->next()) {
//     	entry = exhibitionEntry(res->getString("ID"),res->getString("Name"), res->getString("Link"));
//     }
//     return entry;
// }

void galleryDB::editEntry(string idnum,string name,string link){
	std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
  	stmnt->executeQuery("UPDATE exhibitions SET Name = '"+name+"', Link ='"+link+"' WHERE ID='"+idnum+"'");
}


void galleryDB::deleteEntry(string idnum){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }

  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  stmt->execute("DELETE FROM exhibitions WHERE ID='"+idnum+"'");
}


// function to summarize results of emotion responses for each exhibition piece
// void galleryDB::summaryEmotion(vector<string> &emotionVec, vector<string> &exhibitionVec, vector<string> &countVec) {	
// 	if (!conn) {
// 		cerr << "Invalid database connection" << endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	
//   	sql::ResultSet *res = stmnt->executeQuery(
// 			"SELECT emotion, exhibition, COUNT(emotion) as count_emotion FROM emotion_response GROUP BY emotion, exhibition"
// 	);
    
//     // Loop through and print results
//     while (res->next()) {
//     	string emotion;
// 	    emotion = res->getString("emotion");
//         emotionVec.push_back(emotion);
//     	string exhibition;
//     	exhibition = res->getString("exhibition");
//     	exhibitionVec.push_back(exhibition);
//     	string countStr;
//     	countStr = res->getString("count_emotion");
//     	countVec.push_back(countStr);
//     	//cout << exhibition << " " << emotion << " " << countInt << endl;
//     }
// }
