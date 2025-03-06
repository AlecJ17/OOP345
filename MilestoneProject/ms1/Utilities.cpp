// Name: Alec Josef Serrano
// Seneca Student ID: 133592238
// Seneca email: ajserano2@myseneca.ca
// Date of completion: July 10,2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <stdexcept>
#include "Utilities.h"

namespace seneca{
    char Utilities::m_delimiter = '|'; // Default delimiter

    Utilities::Utilities() : m_widthField(1) {}

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string token; // Initialize token as empty

        if (next_pos >= str.length()) {
            more = false; // No more tokens to extract
        } else {
            size_t end_pos = str.find(m_delimiter, next_pos);

            if (end_pos == next_pos) { // Handle the case where the delimiter is right at the current position
                more = false; // No further tokens as we hit consecutive delimiters
                throw std::string("No token between delimiters"); // Throw indicating an error
            } else if (end_pos == std::string::npos) {
                token = str.substr(next_pos); // Handle last token
                next_pos = str.length(); // Move next_pos to the end to stop further processing
                more = false; // Indicate that there are no more tokens after this
            } else {
                token = str.substr(next_pos, end_pos - next_pos); // Extract the token
                next_pos = end_pos + 1; // Move next_pos past the delimiter for next token extraction
                more = true; // Indicate there might be more tokens
            }

            if (token.empty()) {
                more = false; // Ensure to set more to false to prevent loops if token is empty
                throw std::string("Extracted token is empty");
            }

            if (m_widthField < token.length()) {
                m_widthField = token.length(); // Update the width field if the extracted token is longer
            }

            token = trim(token); // Ensure no leading/trailing spaces
        }

        return token;
    }



    std::string& Utilities::trim(std::string& s) {
        // Find the first non-space character
        size_t start = s.find_first_not_of(' ');

        // Find the last non-space character
        size_t end = s.find_last_not_of(' ');

        // If no non-space characters are found, clear the string
        if (start == std::string::npos || end == std::string::npos) {
            s.clear();
        } else {
            // Trim leading and trailing spaces
            s = s.substr(start, end - start + 1);
        }

        return s;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}