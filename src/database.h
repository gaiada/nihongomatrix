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
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>
#include <sqlite3.h>

using namespace std;

class Database
{

public:
	Database(char* filename);
	Database(string filename);

	~Database();
	
	bool open(char* filename);
	vector<vector<string> > query(char* query);
	vector<vector<string> > query(string query);

	void close();
	
private:
	sqlite3 *database;
};

#endif

