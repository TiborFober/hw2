#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

// Clothing
set<string> Clothing::keywords() const
{
	set<string> keySet;

	keySet = setUnion<string>(keySet, parseStringToWords(name_));
	keySet = setUnion<string>(keySet, parseStringToWords(brand_));

	return keySet;
}

string Clothing::displayString() const
{
	stringstream ss;
	ss << name_ << "\n"
		<< "Size: " << size_ << " Brand: " << brand_ << "\n"
		<< price_ << " " << qty_ << " left.";

	return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
	Product::dump(os);
	os << size_ << "\n" << brand_ << endl;
}