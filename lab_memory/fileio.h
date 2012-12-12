#ifndef FILEIO_H
#define FILEIO_H

#include <string>

#include "room.h"

/**
 * Utility functions for reading students/rooms from files
 * NOTE: There are NO bugs in fileio
 */
namespace fileio
{
	void init();
	void halt();
	void loadStudents(const string & file);
	void loadRooms(const string & file);
	int  getNumStudents();
	int  getNumRooms();
	bool areMoreStudents();
	bool areMoreRooms();
	string nextStudent();
	Room nextRoom();
}

#endif
