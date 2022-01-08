#include "Product.h"

Product::Product(const std::string& name, ProductUnit *unit) : name(name), unit(unit) {}

std::string Product::getName() const {
    return name;
}

ProductUnit* Product::getUnit() const {
    return unit;
}

bool Product::operator==(const Product& rhs) const {
    return name == rhs.name &&
           unit == rhs.unit;
}

bool Product::operator!=(const Product& rhs) const {
    return !(rhs == *this);
}

bool Product::operator<(const Product& rhs) const {
    return (name < rhs.name) ? true : ( (name > rhs.name) ? false : (unit < rhs.unit));
}

bool Product::operator>(const Product& rhs) const {
    return rhs < *this;
}

bool Product::operator<=(const Product& rhs) const {
    return !(rhs < *this);
}

bool Product::operator>=(const Product& rhs) const {
    return !(*this < rhs);
}
