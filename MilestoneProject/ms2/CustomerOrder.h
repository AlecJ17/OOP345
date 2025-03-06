// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 10,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>
#include <iostream>
#include "Utilities.h"
#include "Station.h"

namespace seneca {

    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {}
    };

    class CustomerOrder {
    private:
        std::string m_name;        // Customer name
        std::string m_product;     // Product being assembled
        size_t m_cntItem;          // Number of items in the customer's order
        Item** m_lstItem;          // Dynamically allocated array of item pointers
        static size_t m_widthField; // Maximum width of a field, used for display purposes

        // Preventing copying
        CustomerOrder& operator=(const CustomerOrder& src) = delete;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& str);

        CustomerOrder(const CustomerOrder& src);
        // Allowing moving
        CustomerOrder(CustomerOrder&& src) noexcept;
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;

        // Destructor
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };

} // namespace seneca

#endif // SENECA_CUSTOMERORDER_H
