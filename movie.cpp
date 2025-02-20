#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

// Movie
set<string> Movie::keywords() const
{
	set<string> keySet;

	keySet = setUnion<string>(keySet, parseStringToWords(name_));
	keySet.insert(genre_);

	return keySet;
}

string Movie::displayString() const
{
	stringstream ss;
	ss << name_ << "\n"
		<< "Genre: " << genre_ << " Rating: " << rating_ << "\n"
		<< price_ << " " << qty_ << " left.";

	return ss.str();
}

void Movie::dump(std::ostream& os) const
{
	Product::dump(os);
	os << genre_ << "\n" << rating_ << endl;
}