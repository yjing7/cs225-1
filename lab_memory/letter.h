#ifndef LETTER_H
#define LETTER_H

#include <string>

using namespace std;

/**
 * Represents a group of students with the same first letter of their last
 * name.
 */
class Letter
{
	public:
	char letter;
	int count;

	Letter();
	void addStudent(const string & name);
	bool operator<(const Letter & other) const;
};

#endif
