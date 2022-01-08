#include "ShoppingCart.h"

void addItemQuantity(Product* product, double quantity);

std::vector<ProductQuantity*> ShoppingCart::getItems() const {
    return items;
}

std::map<Product*, double> ShoppingCart::getProductQuantities() const {
    return productQuantities;
}

void ShoppingCart::addItem(Product* product) {
    addItemQuantity(product, 1.0);
}

void ShoppingCart::addItemQuantity(Product* product, double quantity) {
    items.emplace_back(product, quantity);
    if (productQuantities.find(product) != productQuantities.end()) {
        productQuantities[product] += quantity;
    } else {
        productQuantities[product] = quantity;
    }
}

void ShoppingCart::handleOffers(Receipt* receipt, std::map<Product*, Offer> offers, SupermarketCatalog* catalog) {
    for (const auto& productQuantity : productQuantities) {
        Product* product = productQuantity.first;
        double quantity = productQuantity.second;
        if (offers.find(product) != offers.end()) {
            auto offer = offers[product];
            double unitPrice = catalog->getUnitPrice(product);
            int quantityAsInt = (int) quantity;
            Discount* discount = nullptr;
			int numberOfXs;
			switch(offer.getOfferType())
			{
				case SpecialOfferType::ThreeForTwo:
					numberOfXs = quantityAsInt / 3;
					if (quantityAsInt > 2)
					{
						double discountAmount = quantity * unitPrice - ((numberOfXs * 2 * unitPrice) + quantityAsInt % 3 * unitPrice);
                		discount = new Discount("3 for 2", -discountAmount, product);
					}
					break;
				case SpecialOfferType::TwoForAmount:
					numberOfXs = quantityAsInt / 2;
                	if (quantityAsInt >= 2)
					{
                    	double total = offer.getArgument() * numberOfXs + quantityAsInt % 2 * unitPrice;
                    	double discountN = unitPrice * quantity - total;
                    	discount = new Discount("2 for " + std::to_string(offer.getArgument()), -discountN, product);
                	}
					break;
				case SpecialOfferType::FiveForAmount:
					numberOfXs = quantityAsInt / 5;
					if (quantityAsInt >= 5)
					{
						double discountTotal = unitPrice * quantity - (offer.getArgument() * numberOfXs + quantityAsInt % 5 * unitPrice);
                		discount = new Discount(std::to_string(x) + " for " + std::to_string(offer.getArgument()), -discountTotal, product);
					}
				case SpecialOfferType::TenPercentDiscount:
					discount = new Discount(std::to_string(offer.getArgument()) + "% off", -quantity * unitPrice * offer.getArgument() / 100.0, product);
					break;	
			}
            if (discount != nullptr)
                receipt->addDiscount(*discount);
        }
    }
}
