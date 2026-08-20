#pragma once
#include <string>

class Product{
	public:
		Product();
		Product(const std::string& description);
		Product(const Product& other);
		Product& operator=(const Product& other);
		std::string getDescription() const;

	private:
		std::string description;
};

