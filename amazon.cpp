





#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "movie.h"
#include "book.h"
#include "clothing.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cerr << "Please specify a database file" << endl;
		return 1;
	}

	/****************
	 * Declare your derived DataStore object here replacing
	 *  DataStore type to your derived type
	 ****************/
	MyDataStore ds;



	// Instantiate the individual section and product parsers we want
	ProductSectionParser* productSectionParser = new ProductSectionParser;
	productSectionParser->addProductParser(new ProductBookParser);
	productSectionParser->addProductParser(new ProductClothingParser);
	productSectionParser->addProductParser(new ProductMovieParser);
	UserSectionParser* userSectionParser = new UserSectionParser;

	// Instantiate the parser
	DBParser parser;
	parser.addSectionParser("products", productSectionParser);
	parser.addSectionParser("users", userSectionParser);

	// Now parse the database to populate the DataStore
	if (parser.parse(argv[1], ds)) {
		cerr << "Error parsing!" << endl;
		return 1;
	}

	cout << "=====================================" << endl;
	cout << "Menu: " << endl;
	cout << "  AND term term ...                  " << endl;
	cout << "  OR term term ...                   " << endl;
	cout << "  ADD username search_hit_number     " << endl;
	cout << "  VIEWCART username                  " << endl;
	cout << "  BUYCART username                   " << endl;
	cout << "  QUIT new_db_filename               " << endl;
	cout << "====================================" << endl;

	vector<Product*> hits;
	bool done = false;
	while (!done) {
		cout << "\nEnter command: " << endl;
		string line;
		getline(cin, line);
		stringstream ss(line);
		string cmd;
		if ((ss >> cmd)) {
			if (cmd == "AND") {
				string term;
				vector<string> terms;
				while (ss >> term) {
					term = convToLower(term);
					terms.push_back(term);
				}
				hits = ds.search(terms, 0);
				displayProducts(hits);
			}
			else if (cmd == "OR") {
				string term;
				vector<string> terms;
				while (ss >> term) {
					term = convToLower(term);
					terms.push_back(term);
				}
				hits = ds.search(terms, 1);
				displayProducts(hits);
			}
			else if (cmd == "QUIT") {
				string filename;
				if (ss >> filename) {
					ofstream ofile(filename.c_str());
					ds.dump(ofile);
					ofile.close();
				}
				done = true;
			}
			/* Add support for other commands here */
			else if (cmd == "ADD")
			{
				std::string username;
				int hitIndex;
				if (ss >> username >> hitIndex)
				{
					hitIndex--;

					if (hitIndex < 0 || hitIndex >= static_cast<int>(hits.size()))
					{
						cout << "Invalid request" << endl;
					}
					else
					{
						ds.addToCart(username, hitIndex);
					}
				}
				else
				{
					cout << "Invalid request" << endl;
				}
			}
			else if (cmd == "VIEWCART")
			{
				std::string username;
				if (ss >> username)
				{
					ds.viewCart(username);
				}
				else
				{
					cout << "Invalid username" << endl;
				}
			}
			else if (cmd == "BUYCART")
			{
				std::string username;

				if (ss >> username)
				{
					ds.buyCart(username);
				}
				else
				{
					cout << "Invalid username" << endl;
				}
			}
			else {
				cout << "Unknown command" << endl;
			}
		}

	}
	return 0;
}

void displayProducts(std::vector<Product*>& hits) 
{
	
	if (hits.empty()) 
	{
		std::cout << "No results found." << std::endl;
		return;
	}

	size_t index = 1; 
	for (std::vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) 
	{
		std::cout << "Item " << index << ":" << std::endl;
		std::cout << (*it)->displayString() << std::endl;
		std::cout << std::endl;
		index++; 
	}

}