#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {

	vector<Product*>::iterator it;
	map<string, User*>::iterator itt;

	for (it = products_.begin(); it != products_.end(); it++) {
		delete (*it);
	}
	for (itt = users_.begin(); itt != users_.end(); itt++) {
		delete itt->second;
	}
}

void MyDataStore::addProduct(Product* toAdd) {
	products_.push_back(toAdd);
	std::set<std::string> keySet = toAdd->keywords();


	for (std::set<std::string>::iterator it = keySet.begin(); it != keySet.end(); ++it) {
		keywordMap_[*it].insert(toAdd);
	}
}

void MyDataStore::addUser(User* newUser) {
	users_[newUser->getName()] = newUser;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	std::set<Product*> resultSet;

	if (terms.empty()) return {};

	std::vector<std::set<Product*>> productSets;

	for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) 
	{
		cout << "- " << *it << endl;
	}

	for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) 
	{
		if (keywordMap_.find(*it) != keywordMap_.end()) 
		{
			productSets.push_back(keywordMap_[*it]);
		}

	}

	if (productSets.empty()) 
	{
		return {};
	}

	resultSet = productSets[0];
	for (size_t i = 1; i < productSets.size(); i++) {
		if (type == 0) {
			resultSet = setIntersection(resultSet, productSets[i]);
		}
		else {
			resultSet = setUnion(resultSet, productSets[i]);
		}
	}

	lastSearchResults_.clear();
	for (std::set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it) {
		lastSearchResults_.push_back(*it);
	}


	return lastSearchResults_;
}

void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>\n";

	vector<Product*>::iterator it;

	for (it = products_.begin(); it != products_.end(); it++) {
		(*it)->dump(ofile);
	}

	ofile << "</products>\n";
	ofile << "<users>\n";

	map<string, User*>::iterator it2;

	for (it2 = users_.begin(); it2 != users_.end(); it2++) {
		it2->second->dump(ofile);
	}
	ofile << "</users>";
}

void MyDataStore::addToCart(std::string user, int hitResultIndex) 
{
	if (users_.find(user) == users_.end()) {
		cout << "Invalid request" << endl;
		return;
	}


	userCarts_[user].push_back(lastSearchResults_[hitResultIndex]);
}

void MyDataStore::viewCart(std::string user) {
	if (users_.find(user) == users_.end()) {
		cout << "Invalid Username" << endl;
		return;
	}

	vector<Product*>& userCart = userCarts_[user];
	for (size_t i = 0; i < userCart.size(); i++) {
		cout << i + 1 << ". " << userCart[i]->displayString() << endl;
	}
}

void MyDataStore::buyCart(std::string user) {

	if (users_.find(user) == users_.end()) {
		cout << "Invalid Username" << endl;
		return;
	}

	User* currUser = users_[user];
	vector<Product*>& cart = userCarts_[user];
	vector<Product*> remaining;

	vector<Product*>::iterator it;

	for (it = cart.begin(); it != cart.end(); it++) {
		if (((*it)->getQty() > 0) && (currUser->getBalance() > (*it)->getPrice())) {
			(*it)->subtractQty(1);
			currUser->deductAmount((*it)->getPrice());
		}
		else {
			remaining.push_back(*it);
		}
	}

	cart = remaining;
}

void MyDataStore::printProducts() {
	vector<Product*>::iterator it;

	for (it = products_.begin(); it != products_.end(); it++) {
		cout << (*it)->displayString() << endl;
	}

	std::map<std::string, std::set<Product*>>::iterator itt;

	for (itt = keywordMap_.begin(); itt != keywordMap_.end(); itt++) {
		cout << (itt->first) << endl;
	}

}




