#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "letter.h"
#include "room.h"

/**
 * An allocator object to wrap the allocation of last-name letter groups
 * to rooms
 */
class Allocator
{
	public:
	// Initialization
	Allocator(const string & studentFile, const string & roomFile);
    ~Allocator();
	// Solving
	void allocate();

	// Printing results
	void printStudents();
	void printRooms();

	private:
	// Initialization
	void createLetterGroups();
	void loadStudents(const string & file);
	void loadRooms(const string & file);

	// Solving
	int  solve();
	Room * largestOpening();
	int  minSpaceRemaining();

	// Member variables
	Letter * alpha;     // Array of all letters (size 26)
	Room   * rooms;     // Array of all rooms
	int roomCount;      // Size of the rooms array
	int studentCount;   // Total number of students
	int totalCapacity;  // Total number of available seats across all rooms
};

#endif
