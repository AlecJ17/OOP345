// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 22,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <unordered_set>
#include <sstream>
#include "LineManager.h"

namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream f(file);
        if (!f) {
            throw std::runtime_error("Unable to open [" + file + "] file.");
        }

        std::unordered_map<std::string, Workstation*> stationMap;
        std::vector<std::string> orderFromFile;
        for (auto* ws : stations) {
            stationMap[ws->getItemName()] = ws;
        }

        std::string line;
        while (std::getline(f, line)) {
            std::istringstream record(line);
            std::string stationName, nextStationName;
            std::getline(record, stationName, '|');
            if (std::getline(record, nextStationName) && !nextStationName.empty()) {
                stationMap[stationName]->setNextStation(stationMap[nextStationName]);
            }
            orderFromFile.push_back(stationName);  // Capture the order as they appear in the file
        }

        // Setting up m_activeLine in the order from the file
        m_activeLine.clear();
        std::transform(orderFromFile.begin(), orderFromFile.end(), std::back_inserter(m_activeLine),
                       [&](const std::string& name) { return stationMap[name]; });

        // Identify the first station
        std::unordered_set<Workstation*> hasNext;
        std::for_each(stationMap.begin(), stationMap.end(), [&](const auto& pair) {
            if (pair.second->getNextStation() != nullptr) {
                hasNext.insert(pair.second->getNextStation());
            }
        });

        auto it = std::find_if(stationMap.begin(), stationMap.end(),
                               [&](const auto& pair) { return hasNext.find(pair.second) == hasNext.end(); });

        if (it != stationMap.end()) {
            m_firstStation = it->second;
        } else {
            throw std::runtime_error("First station not found.");
        }

        // Update the count of customer orders
        m_cntCustomerOrder = g_pending.size();  // Assuming g_pending is defined and accessible
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> reordered;
        Workstation* current = m_firstStation;
        while (current != nullptr) {
            reordered.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = std::move(reordered);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iterationCount = 0; // Keeps track of the number of iterations
        os << "Line Manager Iteration: " << ++iterationCount << std::endl;

        // Move the first pending order to the first station, if available
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // Execute one fill operation for each station on the line
        for (auto& station : m_activeLine) {
            station->fill(os);
        }

        // Attempt to move an order down the line for each station
        for (auto& station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        // Check if all customer orders have been filled or cannot be filled
        bool allOrdersProcessed = g_pending.empty() && std::all_of(m_activeLine.begin(), m_activeLine.end(),
                                                                   [](const Workstation* ws) { return ws->isAllOrdersProcessed(); });

        // Return true if all orders are processed, false otherwise
        return allOrdersProcessed;
    }


    void LineManager::display(std::ostream& os) const {
        for (const auto* station : m_activeLine) {
            os << station->getItemName();
            if (station->getNextStation()) {
                os << " --> " << station->getNextStation()->getItemName();
            } else {
                os << " --> End of Line";
            }
            os << '\n';
        }
    }
}
