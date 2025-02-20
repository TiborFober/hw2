#include "book.h"
#include "util.h"
#include <sstream>


using namespace std;

// Book
set<string> Book::keywords() const
{
	set<string> keySet;

	keySet = setUnion<string>(keySet, parseStringToWords(name_));
	keySet = setUnion<string>(keySet, parseStringToWords(author_));
	keySet.insert(isbn_);

	return keySet;
}

string Book::displayString() const
{
	stringstream ss;
	ss << name_ << "\n";
	ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
	ss << price_ << " " << qty_ << " left.";

	return ss.str();
}

void Book::dump(std::ostream& os) const
{
	Product::dump(os);
	os << isbn_ << "\n" << author_ << endl;
}