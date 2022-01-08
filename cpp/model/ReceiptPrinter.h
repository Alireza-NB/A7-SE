#ifndef CPP_RECEIPTPRINTER_H
#define CPP_RECEIPTPRINTER_H


#include "Receipt.h"

#include <iomanip>
#include <sstream>

class ReceiptPrinter
{

public:
    ReceiptPrinter();

    ReceiptPrinter(int columns);

    std::string printReceipt(Receipt* receipt);

    std::string presentReceiptItem(ReceiptItem* item) const;

    std::string presentDiscount(Discount* discount) const;

    std::string presentTotal(Receipt* receipt) const;

    std::string formatLineWithWhitespace(const std::string &name, const std::string &value) const;

    std::string presentPrice(double price) const;

    static std::string presentQuantity(ReceiptItem* item)
    {
        return ProductUnit::Each == item->getProduct()->getUnit()
               ? getFormattedNumberAsString(item->getQuantity(), 0)
               : getFormattedNumberAsString(item->getQuantity(), 3);
    }

private:

    static std::string getFormattedNumberAsString(double number, int precision)
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << number;
        return stream.str();
    }

    const int columns;


};


#endif //CPP_RECEIPTPRINTER_H
