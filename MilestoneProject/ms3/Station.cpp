// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 22,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <stdexcept>
#include "Station.h"

namespace seneca{
    size_t Station::id_generator = 0;
    size_t Station::m_widthField = 0;

    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_itemName = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoi(util.extractToken(record, next_pos, more));
        m_quantity = std::stoi(util.extractToken(record, next_pos, more));
        m_description = util.extractToken(record, next_pos, more);

        m_id = ++id_generator;
        m_widthField = std::max(m_widthField, m_itemName.length());
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            m_quantity--;
        }
    }


    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id << " | "
           << std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName << " | "
           << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_quantity << " | "
               << m_description;
        }

        os << std::endl;
    }

}
