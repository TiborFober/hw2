#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore
{
public:
	~MyDataStore();

	virtual void addProduct(Product* p);
	virtual void addUser(User* u);
	virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
	virtual void dump(std::ostream& ofile);

	// Shopping cart functions
	void addToCart(std::string username, Product* p);
	void viewCart(std::string username);
	void buyCart(std::string username);

private:
	std::vector<Product*> products_;
	std::map<std::string, User*> users_;
	std::map<std::string, std::set<Product*>> keywordMap;
	std::map<std::string, std::queue<Product*>> shoppingCart_;
};


#endif