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

void galleryDB::addEntryWord(string word){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	stmnt->executeQuery("INSERT INTO word_response(word) VALUES ('"+word+"')");
}


void galleryDB::addEmotion(string art_piece, string emotion){

	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	stmnt->executeQuery("INSERT INTO emotion_response(art_piece, emotion) VALUES ('"+art_piece+"','"+emotion+"')");
}


vector<string> galleryDB::sumWord(string timestamp){
	timestamp.append("%");
	string word;
	vector<string> wordList; 
	if (!conn)
	{
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
	sql::ResultSet *res = stmnt->executeQuery("SELECT word FROM word_response WHERE timestamp like '" + timestamp + "'");
	while (res->next())
	{
		word = res->getString("word");
		wordList.push_back(word); 
		
	}
	return wordList;
}
	
// Get all arts function
map<string, string> galleryDB::getAllArts(vector<string> &artList, vector<string> &artLink) {
	map<string, string> list;
	if (!conn) {
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	
  	sql::ResultSet *res = stmnt->executeQuery(
			"SELECT DISTINCT Name, Link FROM art_pieces"
	);
    
    // Loop through and print results
    while (res->next()) {
    	string art;
    	art = res->getString("Name");
    	string link;
    	link = res->getString("Link");
	    list[art] = link;
	    artList.push_back(art);
	    artLink.push_back(link);
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
			"SELECT * FROM art_pieces WHERE Name like '%"+search+"%'");
    
    // Loop through and print results
	while (res->next()) {
    	exhibitionEntry entry(res->getString("ID"),res->getString("Name"),res->getString("Link"));
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

  	
  	stmnt->executeQuery("INSERT INTO art_pieces(Name,Link) VALUES ('"+name+"','"+link+"')");
}

exhibitionEntry galleryDB::fetchArt(string id){

	exhibitionEntry entry;	
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());

  	
    sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM art_pieces WHERE ID = '"+id+"'");
    
    // Get first entry
    if (res->next()) {
    	entry = exhibitionEntry(res->getString("ID"),res->getString("Name"), res->getString("Link"));
    }
    return entry;
}

void galleryDB::editEntry(string idnum,string name,string link){
	std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
	
	if (!conn) {
   		cerr << "Invalid database connection" << endl;
   		exit (EXIT_FAILURE);
  	}

  	std::auto_ptr<sql::Statement> stmnt(conn->createStatement());
  	stmnt->executeQuery("UPDATE art_pieces SET Name = '"+name+"', Link ='"+link+"' WHERE ID='"+idnum+"'");
}


void galleryDB::deleteEntry(string idnum){
  // Establish Connection
  std::unique_ptr<sql::Connection>  conn(driver->connect(db_url, properties));
    
  if (!conn) {
   	cerr << "Invalid database connection" << endl;
   	exit (EXIT_FAILURE);
  }

  std::auto_ptr<sql::Statement> stmt(conn->createStatement());

  stmt->execute("DELETE FROM art_pieces WHERE ID='"+idnum+"'");
}


// function to summarize results of emotion responses for each art piece
void galleryDB::summaryEmotion(vector<string> &emotionVec, vector<string> &artVec, vector<string> &countVec) {	
	if (!conn) {
		cerr << "Invalid database connection" << endl;
		exit(EXIT_FAILURE);
	}
	std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	
  	sql::ResultSet *res = stmnt->executeQuery(
			"SELECT emotion, art_piece, COUNT(emotion) as count_emotion FROM emotion_response GROUP BY emotion, art_piece"
	);
    
    // Loop through and print results
    while (res->next()) {
    	string emotion;
	    emotion = res->getString("emotion");
        emotionVec.push_back(emotion);
    	string art;
    	art = res->getString("art_piece");
    	artVec.push_back(art);
    	string countStr;
    	countStr = res->getString("count_emotion");
    	countVec.push_back(countStr);
    	//cout << art << " " << emotion << " " << countInt << endl;
    }
}
