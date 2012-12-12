#ifndef ROOM_H
#define ROOM_H

#include <string>

#include "letter.h"

using namespace std;

/**
 * Represents a testing room, which has a group of letters allocated to it
 * (where letters are first letters of last names)
 */
class Room
{
	public:
	string name;      // The room name
	int capacity;     // The capacity of the room
	int count;        // The number of students currently allocated
	Letter * letters; // An array of letters currently allocated
	int letterCount;  // The number of valid letters in the letters array

	Room();
	Room(const Room & other);
	Room(const string & init_name, int init_capacity);
	Room & operator=(const Room & other);
	~Room();

	void addLetter(const Letter & L);
	int spaceRemaining();
	void print();

	private:
	void clear();
	void copy(const Room & other);
};

#endif
