#include "../headers/utilities.h"

string TimeConverter::timeToString(time_t currentTime)
{
    struct tm *timeinfo;
    char buffer[80];

    timeinfo = localtime(&currentTime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return std::string(buffer);
}

time_t TimeConverter::stringToTime(string dateString)
{
    struct tm timeinfo = {};
    if (strptime(dateString.c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo) == nullptr)
    {
        // Invalid string format
        throw std::invalid_argument("Invalid date string format");
    }

    time_t convertedTime = mktime(&timeinfo);
    if (convertedTime == -1)
    {
        // mktime failed (possibly due to out-of-range values)
        throw std::out_of_range("Invalid time value");
    }

    return convertedTime;
}

vector<string> split(string text, char delimeter)
{
    vector<string> results;
    size_t i = 0;
    size_t j = 0;
    while (i < text.size())
    {
        j = i;
        while (j < text.size() && text[j] != delimeter)
            j++;

        string content = text.substr(i, j - i);
        results.emplace_back(content);
        i = j + 1;
    }
    return results;
}


void copy_to_pointer( string s, char * output ){

    int n = s.size();
    for ( int i = 0 ; i < n; i++ ) output[i] = s[i];
    
}
