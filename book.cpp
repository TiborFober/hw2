#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

using namespace std;

// Book
set<string> Book::keywords() const
{
	set<string> keySet;
	set<string> nameWords = parseStringToWords(name_);
	set<string> authorWords = parseStringToWords(author_);

	keySet = setUnion(nameWords, authorWords);  
	keySet.insert(isbn_);  
	return keySet;
}

string Book::displayString() const
{
	stringstream ss;
	ss << name_ << "\n"
		<< "Author: " << author_ << " ISBN: " << isbn_ << "\n"
		<< fixed << setprecision(2) << price_ << " " << qty_ << " left.";

	return ss.str();
}

void Book::dump(std::ostream& os) const
{
	Product::dump(os);
	os << isbn_ << "\n" << author_ << endl;
}