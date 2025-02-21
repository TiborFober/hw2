#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

// Clothing
std::set<std::string> Clothing::keywords() const {
	std::set<std::string> keySet;
	std::set<std::string> nameWords = parseStringToWords(name_);
	std::set<std::string> brandWords = parseStringToWords(brand_);

	keySet = setUnion(nameWords, brandWords);



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