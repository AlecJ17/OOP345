// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 22,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace seneca {

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& str) : Station(str) {}

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            CustomerOrder& order = m_orders.front();
            order.fillItem(*this, os);  // This should handle both filling and logging.
        }
    }


    bool Workstation::attemptToMoveOrder() {
        bool orderMoved = false; // Initialize the flag to control the return value.

        if (!m_orders.empty()) {
            CustomerOrder& order = m_orders.front();

            // Check if the current order is completely filled at this station or cannot be filled due to inventory shortage.
            if (order.isItemFilled(getItemName()) || getQuantity() == 0) {
                if (m_pNextStation != nullptr) {
                    // Move the order to the next station if it exists.
                    *m_pNextStation += std::move(order);
                } else {
                    // Determine if the order is completely filled or not, and move to the appropriate queue.
                    if (order.isOrderFilled()) {
                        g_completed.push_back(std::move(order));
                    } else {
                        g_incomplete.push_back(std::move(order));
                    }
                }
                m_orders.pop_front(); // Remove the order from the current station's queue.
                orderMoved = true; // Set true as the order has been moved.
            }
        }

        // Return the status of whether an order was moved.
        return orderMoved;
    }



    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation ? m_pNextStation : nullptr;
    }

    bool Workstation::isAllOrdersProcessed() const {
        return m_orders.empty();
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        } else {
            os << "End of Line";
        }
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}
