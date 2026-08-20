#include <iostream>
#include <vector>
#include <tuple>
#include "Product.h"         
#include "MySmartPointer.h"   
#include "Helper.h"

using namespace std;

int main() {
	Product* p1 = new Product("LEGO");
	Product* p2 = new Product("Cobi");
	Product* p3 = new Product("PS5");
	Product* p4 = new Product("XBOX SERIES X");
	Product* p5 = new Product("NINTENDO SWITCH 2");
	//Product* p6 = p4;

	MySmartPointer<Product> m1(p1);
	MySmartPointer<Product> m2(p2);
	MySmartPointer<Product> m3(p3);
	MySmartPointer<Product> m4(p4);
	MySmartPointer<Product> m5(p5);
	//MySmartPointer<Product> m6(p6);

	MySmartPointer<Product> x3(m3);
	MySmartPointer<Product> x33(m3);

	MySmartPointer<Product> x4(m4);

	//cout << m1.getRefCount() << endl;
	//cout << m2.getRefCount() << endl;
	//cout << m3.getRefCount() << endl;
	//cout << m4.getRefCount() << endl;
	//cout << m5.getRefCount() << endl;
	//cout << m6.getRefCount() << endl;
	//cout << x4.getRefCount() << endl;
	//cout << x44.getRefCount() << endl;

	vector<MySmartPointer<Product>> list;
	list.push_back(m1);
	list.push_back(m2);
	list.push_back(m3);
	list.push_back(m4);
	list.push_back(m5);
	//list.push_back(m6);


	tuple<int, int, int> results = countErrors(list);

	cout << get<0>(results) << endl;
	cout << get<1>(results) << endl;
	cout << get<2>(results) << endl;


	return 0;
}