#include "mydatastore.h"
#include "util.h"
#include <iomanip>

using namespace std;

MyDataStore::~MyDataStore()
{

}

void MyDataStore::addProduct(Product* p)
{
	products_.push_back(p);

	set<string> keywords = p->keywords();

	for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it)
	{
		keywordMap[*it].insert(p);
	}
}

void MyDataStore::addUser(User* u)
{
	users_.insert(make_pair(u->getName(), u));
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
	set<Product*> result;

	if (terms.empty())
	{
		return vector<Product*>();
	}

	for (vector<string>::iterator itTerms = terms.begin(); itTerms != terms.end(); ++itTerms)
	{
		map<string, set<Product*>>::iterator itMap = keywordMap.find(*itTerms);

		if (itMap != keywordMap.end())
		{
			set<Product*> productSet = itMap->second;

			if (type == 0) // AND (intersection)
			{
				if (result.empty())
				{
					result = productSet;
				}
				else
				{
					result = setIntersection(result, productSet);
				}


			}
			else if(type == 1) // OR (union)
			{
				result = setUnion(result, productSet);
			}
		}
		else if (type == 0) // AND search and keyword not found, return empty vector
		{
			return vector<Product*>();
		}

	}

	vector<Product*> returnVal;

	for (set<Product*>::iterator it = result.begin(); it != result.end(); ++it)
	{
		returnVal.push_back(*it);
	}

	return returnVal;
}

void MyDataStore::dump(ostream& ofile)
{
	ofile << "<products>" << endl;
	for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
	{
		(*it)->dump(ofile);
	}
	ofile << "</products>" << endl;

	ofile << "<users>" << endl;
	for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it)
	{
		ofile << fixed << setprecision(2);
		it->second->dump(ofile);
	}
	ofile << "</users>" << endl;

}


void MyDataStore::addToCart(std::string username, Product* p)
{
	if (users_.find(username) == users_.end())  
	{
		cout << "Invalid username" << endl;
		return;
	}

	if (!p) 
	{
		cout << "Invalid request" << endl;
		return;
	}

	shoppingCart_[username].push(p);
}

void MyDataStore::viewCart(std::string username)
{
	if (shoppingCart_.find(username) == shoppingCart_.end()) 
	{
		cout << "Username not found" << endl;
		return;
	}
	if (shoppingCart_[username].empty()) 
	{
		cout << "Cart is empty" << endl;
		return;
	}

	queue<Product*> tempCart = shoppingCart_[username];

	int index = 1;

	while (!tempCart.empty())
	{
		Product* prod = tempCart.front();
		cout << "Item " << index << ":" << endl;
		cout << prod->displayString() << endl;
		cout << endl;

		tempCart.pop();
		index++;

	}

}

void MyDataStore::buyCart(std::string username)
{
	if (users_.find(username) == users_.end())
	{
		cout << "Invalid username" << endl;
		return;
	}

	if (shoppingCart_.find(username) == shoppingCart_.end())
	{
		cout << "No shopping cart for user" << endl;
		return;
	}

	queue<Product*>& tempCart = shoppingCart_[username];
	queue<Product*> newCart;

	while (!tempCart.empty())
	{
		Product* prod = tempCart.front();
		tempCart.pop(); 

		if (prod->getQty() > 0) 
		{
			if (users_[username]->getBalance() >= prod->getPrice())
			{
				users_[username]->deductAmount(prod->getPrice());
				prod->subtractQty(1);
			}
			else
			{
				newCart.push(prod);
			}
		}
		else
		{
			newCart.push(prod);
		}
	}

	shoppingCart_[username] = newCart;
}