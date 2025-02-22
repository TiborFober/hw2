#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() 
{
	for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
	{
		delete (*it);
	}

	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it)
	{
		delete it->second;
	}
}

void MyDataStore::addProduct(Product* prod) 
{
	products_.push_back(prod);

	set<std::string> keySet = prod->keywords();


	for (set<string>::iterator it = keySet.begin(); it != keySet.end(); ++it) 
	{
		keywordMap_[*it].insert(prod);
	}
}

void MyDataStore::addUser(User* newUser) 
{
	users_[newUser->getName()] = newUser;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) 
{
	set<Product*> resultSet;

	if (terms.empty())
		return vector<Product*>(); // return empty vector

	vector<set<Product*>> productSets;

	for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it) {
		if (keywordMap_.find(*it) != keywordMap_.end()) 
		{
			productSets.push_back(keywordMap_[*it]);
		}
		else 
		{
			productSets.push_back(set<Product*>());
		}
	}

	if (type == 0) 
	{
		resultSet = productSets[0];
		for (size_t i = 1; i < productSets.size(); i++) 
		{
			resultSet = setIntersection(resultSet, productSets[i]);
		}
	}
	else if (type == 1) 
	{
		resultSet = productSets[0];
		for (size_t i = 1; i < productSets.size(); i++) 
		{
			resultSet = setUnion(resultSet, productSets[i]);
		}
	}

	searchResults_.clear();
	for (set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it)
	{
		searchResults_.push_back(*it);
	}

	return searchResults_;
}

void MyDataStore::dump(std::ostream& ofile) 
{
	ofile << "<products>\n";

	for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) 
	{
		(*it)->dump(ofile);
	}

	ofile << "</products>\n";
	ofile << "<users>\n";

	map<string, User*>::iterator it2;

	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) 
	{
		it->second->dump(ofile);
	}
	ofile << "</users>";
}

void MyDataStore::addToCart(string user, int hitResIndex) 
{
	if (users_.find(user) == users_.end()) 
	{
		std::cout << "Invalid request" << std::endl;
		return;
	}

	userCarts_[user].push_back(searchResults_[hitResIndex]);
}

void MyDataStore::viewCart(std::string user) 
{
	if (users_.find(user) == users_.end()) 
	{
		cout << "Invalid Username" << endl;
		return;
	}

	if (userCarts_.find(user) == userCarts_.end() || userCarts_[user].empty())
	{
		cout << "Cart is empty" << endl;
		return;
	}

	vector<Product*>& userCart = userCarts_[user];

	size_t index = 1;
	for (vector<Product*>::iterator it = userCarts_[user].begin(); it != userCarts_[user].end(); ++it)
	{
		cout << "Item " << index << endl;
		cout << (*it)->displayString() << endl;
		index++;
	}
}

void MyDataStore::buyCart(std::string user) 
{
	if (users_.find(user) == users_.end()) 
	{
		cout << "Invalid Username" << endl;
		return;
	}

	
	
	vector<Product*> remainingItems;

	vector<Product*>::iterator it;

	for (it = userCarts_[user].begin(); it != userCarts_[user].end(); it++)
	{
		if (((*it)->getQty() > 0) && (users_[user]->getBalance() > (*it)->getPrice())) 
		{
			(*it)->subtractQty(1);
			users_[user]->deductAmount((*it)->getPrice());
		}
		else 
		{
			remainingItems.push_back(*it);
		}
	}

	userCarts_[user] = remainingItems;
}

void MyDataStore::printProducts() 
{

	for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) 
	{
		cout << (*it)->displayString() << endl;
	}


	for (map<string, set<Product*>>::iterator it = keywordMap_.begin(); it != keywordMap_.end(); ++it) 
	{
		cout << it->first << endl;
	}

}



