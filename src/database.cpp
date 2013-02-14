/***************************************************************************
 *   Copyright (C) 2011 by Gaiada,45,69,64   					*
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
#include "database.h"
#include <iostream>
#include "misc.h"

Database::Database(char* filename)
{
	database = NULL;
	open(filename);
}

Database::Database(string filename)
{
	database = NULL;
	open(strtocharptr(filename));
}


Database::~Database()
{
}

bool Database::open(char* filename)
{
	if(sqlite3_open(filename, &database) == SQLITE_OK)
		return true;
		
	return false;   
}

vector<vector<string> > Database::query(char* query)
{
	sqlite3_stmt *statement;
	vector<vector<string> > results;

	if(sqlite3_prepare_v2(database, query, -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);
			
			if(result == SQLITE_ROW)
			{
				vector<string> values;
				for(int col = 0; col < cols; col++)
				{
					values.push_back((char*)sqlite3_column_text(statement, col));
				}
				results.push_back(values);
			}
			else
			{
				break;
			}
		}
		sqlite3_finalize(statement);
	}
	string error = sqlite3_errmsg(database);
	if(error != "not an error") cout << query << " " << error << endl;
	return results;
}

vector<vector<string> > Database::query(string querystr){
	return query(strtocharptr(querystr));
}


void Database::close()
{
	sqlite3_close(database);
}
