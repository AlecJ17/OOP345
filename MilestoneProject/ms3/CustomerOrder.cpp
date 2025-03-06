// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 22,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <vector>
#include "CustomerOrder.h"
namespace seneca {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        std::vector<Item*> items;
        while (more) {
            items.push_back(new Item(util.extractToken(str, next_pos, more)));
        }
        m_cntItem = items.size();
        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++) {
            m_lstItem[i] = items[i];
        }
        m_widthField = std::max(m_widthField, util.getFieldWidth());
    }

    // Copy Constructor - Throws exception
    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::runtime_error("Copy constructor is not allowed");
    }

    // Move Constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
            : m_name(std::move(other.m_name)), m_product(std::move(other.m_product)),
              m_cntItem(other.m_cntItem), m_lstItem(other.m_lstItem) {
        other.m_lstItem = nullptr;
        other.m_cntItem = 0; // Ensuring the source object is left in a valid state.
    }

    // Move Assignment Operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            // Free existing resources
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // Transfer resources
            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            // Nullify the moved-from object
            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        bool filled = true;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (!m_lstItem[i]->m_isFilled){
                filled = false;
            }
        }
        return filled;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        bool filled = true;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                filled = false;
            }
        }
        return filled;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        bool continueLoop = true;
        for (size_t i = 0; i < m_cntItem && continueLoop; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    continueLoop = false; // Exit the loop after processing the item
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
               << std::left << std::setw(m_widthField - 2) << std::setfill(' ') << m_lstItem[i]->m_itemName
               << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

}
