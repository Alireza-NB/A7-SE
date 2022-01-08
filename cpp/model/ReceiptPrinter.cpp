#include "ReceiptPrinter.h"

ReceiptPrinter() : ReceiptPrinter(40)
{
}

ReceiptPrinter(int columns) : columns(columns)
    {}

    std::string printReceipt(Receipt* receipt)
    {
        std::string result;
        for (const auto &item : receipt->getItems())
        {
            result.append(presentReceiptItem(item));
        }
        for (const auto &discount : receipt->getDiscounts())
        {
            result.append(presentDiscount(discount));
        }
        result.append("\n");
        result.append(presentTotal(receipt));
        return result;
    }

    std::string presentReceiptItem(ReceiptItem* item) const
    {
        std::string price = getFormattedNumberAsString(item->getTotalPrice(), 2);
        std::string name = item->getProduct()->getName();

        std::string line = formatLineWithWhitespace(name, price);

        if (item->getQuantity() != 1)
        {
            line += "  " + getFormattedNumberAsString(item->getPrice(), 2) + " * " + presentQuantity(item) + "\n";
        }
        return line;
    }

    std::string presentDiscount(Discount* discount) const
    {
        std::string name = discount->getDescription() + "(" + discount->getProduct()->getName() + ")";
        std::string pricePresentation = getFormattedNumberAsString(discount->getDiscountAmount(), 2);
        return formatLineWithWhitespace(name, pricePresentation);
    }

    std::string presentTotal(Receipt* receipt) const
    {
        std::string total = "Total: ";
        std::string pricePresentation = presentPrice(receipt->getTotalPrice());
        return formatLineWithWhitespace(total, pricePresentation);
    }

    std::string formatLineWithWhitespace(const std::string &name, const std::string &value) const
    {
        int whitespaceSize = columns - name.length() - value.length();
        std::string whitespace;
//        char whitespace[whitespaceSize];
        for (int i = 0; i < whitespaceSize; i++)
        {
            whitespace.append(" ");
//            whitespace[i] = " ";
        }
        return name + whitespace + value + "\n";
    }

    std::string presentPrice(double price) const
    { return getFormattedNumberAsString(price, 2); }
