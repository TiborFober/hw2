#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

// Movie
set<string> Movie::keywords() const
{
	set<string> keySet;
	set<string> nameWords = parseStringToWords(name_);
	set<string> genreWords = parseStringToWords(genre_);

	keySet = setUnion(nameWords, genreWords); 
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