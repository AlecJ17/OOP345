// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 22,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include "Workstation.h"

namespace seneca {

    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder = 0;
        Workstation* m_firstStation = nullptr;
        std::vector<Workstation*> m_loadOrder;   // For displaying in loaded order

    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        void reorderStations();

        bool run(std::ostream& os);

        void display(std::ostream& os) const;
    };
}
#endif // SENECA_LINEMANAGER_H