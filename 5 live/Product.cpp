#include "Product.h"
#include <string>

Product::Product() {
	description = "";
}

Product::Product(const std::string& description) {
	this->description = description;
}

Product::Product(const Product& other) {
	description = other.description;
}

Product& Product::operator=(const Product& other) {
	if (this == &other) return (*this);
	description = other.description;
	return (*this);
}

std::string Product::getDescription() const {
	return description;
}