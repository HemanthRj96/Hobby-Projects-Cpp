#include<iostream>

using namespace std;

// Abstract factory tutorial code

/*/// PROBLEM ///
Imagine that you're creating a furniture shop simulator.Your code consists of classes that represent :
1. A family of related products, say : Chair + Sofa + CoffeeTable.
2. Several variants of this family.
For example, products Chair + Sofa + CoffeeTable are available in these variants : Modern, Victorian, ArtDeco.
You need a way to create individual furniture objects so that they match other objects of the same family. 
Customers get quite mad when they receive non-matching furniture. 
Also, you don't want to change existing code when adding new products or families of products to the program. 
Furniture vendors update their catalogs very often, and you wouldn't want to change the core code each time it happens.
*/

// https://refactoring.guru/design-patterns/abstract-factory Check this link to see more in detail


// Abstract for products
class Product
{
public:
	virtual ~Product() {};
	virtual void TheFunction() = 0;
};

// Concrete product A
class Product_A : public Product
{
public:
	virtual void TheFunction() override { cout << "This is product A" << endl; }
};

// Concrete product B
class Product_B : public Product
{
public:
	virtual void TheFunction() override { cout << "This is product B" << endl; }
};

// Abstract for factory
class Factory
{
public:
	virtual void FactoryType() const = 0;
	virtual Product_A* CreateProduct_A()const = 0;
	virtual Product_B* CreateProduct_B()const = 0;
};

// Concrete factory A
class Factory_A : public Factory
{
public:
	virtual void FactoryType() const override { cout << "This is factory A" << endl; }
	virtual Product_A* CreateProduct_A() const override { return new Product_A(); }
	virtual Product_B* CreateProduct_B() const override { return new Product_B(); }
};

// Concrete factory B
class Factory_B : public Factory
{
public:
	virtual void FactoryType() const override { cout << "This is factory B" << endl; }
	virtual Product_A* CreateProduct_A() const override { return new Product_A(); }
	virtual Product_B* CreateProduct_B() const override { return new Product_B(); }

};

void GetFromFactory(const Factory& factory)
{
	Product* product = nullptr;

	factory.FactoryType();
	product = factory.CreateProduct_A();
	product->TheFunction();
	product = factory.CreateProduct_B();
	product->TheFunction();
}

void AbstractFactoryMain_()
{
	Factory* factory = nullptr;

	factory = new Factory_A();
	GetFromFactory(*factory);
	factory = new Factory_B();
	GetFromFactory(*factory);
}