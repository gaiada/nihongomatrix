/***************************************************************************
 *   Copyright (C) 2011 by Gaiada,45,69,64   *
 *   gaiada@gaiadaware   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "kanji.h"
#include <iostream>
#include "database.h"
#include "misc.h"

kanji::kanji()
{
	id 	= "00";
	name 	= "unknown";
	meaning = "unknown";
	imgfile = "unknown.gif";
	grade 	= "4kb";
}


kanji::~kanji()
{
}



vector<string> kanji::selectKanji(string statement){
	Database *db = new Database(strtocharptr("Database.sqlite"));
	vector<string> kanji;
	vector<vector<string> > result = db->query(statement);
	for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
	{
		kanji = *it;
		cout << "Values: (kanji (romaji)=" << kanji.at(1) << ", mean=" << kanji.at(2) << ", grade=" << kanji.at(3)<< ", image=" << kanji.at(4)<< ")" << endl;
	}
		db->close();
		return kanji;
}

vector<vector<string> > kanji::SelectAllKanji(){
	Database *db = new Database(strtocharptr("Database.sqlite"));
	vector<vector<string> > result = db->query(strtocharptr("SELECT * FROM kanji;"));
	return result;
}






bool kanji::setByName(string nome){
	string stmt = "select * from kanji where kanji = '" + nome + "';";
	vector<string> members = selectKanji(stmt);
	id 	= members.at(0);
	name 	= members.at(1);
	meaning = members.at(2);
	grade 	= members.at(3);
	return true;

}
