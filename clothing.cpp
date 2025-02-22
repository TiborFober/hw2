#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

// Clothing
std::set<std::string> Clothing::keywords() const 
{
	/*
	std::set<std::string> keySet;
	std::set<std::string> nameWords = parseStringToWords(name_);
	std::set<std::string> brandWords = parseStringToWords(brand_);

	keySet = setUnion(nameWords, brandWords);

	return keySet; */
	std::set<std::string> keychain = parseStringToWords(name_);

	set<string> brandSet = parseStringToWords(brand_);
	set<string>::iterator it;

	for (it = brandSet.begin(); it != brandSet.end(); it++) {
		keychain.insert(*it);
	}
	keychain.insert(convToLower(size_));

	return keychain;
}


string Clothing::displayString() const
{
	stringstream ss;
	ss << name_ << "\n"
		<< "Size: " << size_ << " Brand: " << brand_ << "\n"
		<< price_ << " " << qty_ << " left.\n";

	return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ <<
		"\n" << size_ << "\n" << brand_ << std::endl;

	//Product::dump(os);
	//os << size_ << "\n" << brand_ << endl;
}