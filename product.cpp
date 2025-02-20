#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category)
{

}

Product::~Product()
{

}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

// Implementation of Book, Clothing and Movie

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


