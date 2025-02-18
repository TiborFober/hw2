#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Product {
public:
    Product(const std::string category, const std::string name, double price, int qty);
    virtual ~Product();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    virtual std::set<std::string> keywords() const = 0;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    virtual std::string displayString() const = 0;

    /**
     * Outputs the product info in the database format
     */
    virtual void dump(std::ostream& os) const;

    /**
     * Accessors and mutators
     */
    double getPrice() const;
    std::string getName() const;
    int getQty() const;
    void subtractQty(int num);

protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;

};

class Book : public Product
{
public:
    Book(std::string name, double price, int qty, std::string isbn, std::string author)
        : Product("book", name, price, qty), isbn_(isbn), author_(author) {}

    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;

private:
    std::string isbn_;
    std::string author_
};

class Clothing : public Product
{
public:
    Clothing(std::string name, double price, int qty, std::string size, std::string brand)
        : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
};

class Movie : public Product
{
public:
    Movie(std::string name, double price, int qty, std::string genre, std::string rating)
        : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};

#endif
