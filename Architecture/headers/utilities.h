#pragma once

#include "includes.h"

/**
 * @brief Class that converts time_t to string and vice versa
 *
 */
class TimeConverter
{
public:
    // Convert time_t to string
    static std::string timeToString(time_t currentTime);

    // Convert string to time_t
    static time_t stringToTime(string dateString);
};

// char * copy_to_pointer( string s, char * buffer);
void copy_to_pointer(string s, char *buffer); // updated by HK for compilation purposes
// convert a string to character pointer for encoding
// since send takes a void *

/**
 * @brief Behaves similarly to the python functions .split(delimeter)
 *
 * @param text
 * @param delimeter
 * @return vector<string>
 */
vector<string> split(string text, char delimeter);