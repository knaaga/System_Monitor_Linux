#include <string>
#include <sstream>
#include <iomanip>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function

std::string num_format(const int number) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << number;
    return ss.str();
}

string Format::ElapsedTime(long seconds) 
{ 
    int hh, mm, ss;

    std::ostringstream timestream;
    hh = seconds / 3600;
    mm = (seconds % 3600) / 60;
    ss = (seconds % 3600) % 60;
    timestream  << num_format(hh) << ':' << num_format(mm) << ':' << num_format(ss);
    return timestream.str(); 
}