// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 10,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {

    class Utilities {
        size_t m_widthField;
        static char m_delimiter;

    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        std::string& trim(std::string& s);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();

        // Static function to trim leading and trailing spaces
        static std::string trim(const std::string& str);
    };

} // namespace seneca

#endif // SENECA_UTILITIES_H