
#include <iostream>

using namespace std;

char *	strtocharptr(string sourcestr){
	char * stmt = new char[sourcestr.length()+1];
	strcpy(stmt,sourcestr.c_str());
	return stmt;
}

 
//------------------------ The Game -----------------------
/*
vector<string> getKanji(){
	Database *db;
	db = new Database("Database.sqlite");
//	db->query("INSERT INTO a VALUES(5, 4);");
	vector<string> kanji;
	vector<vector<string> > result = db->query("SELECT * FROM kanji;");
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		kanji = *it;
		cout << "Values: (kanji (romaji)=" << kanji.at(1) << ", mean=" << kanji.at(2) << ", grade=" << kanji.at(3)<< ", image=" << kanji.at(4)<< ")" << endl;
	}
		db->close();
	return kanji;
}
*/
