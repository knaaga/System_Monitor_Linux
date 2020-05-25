#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
{
    proc_id = pid;    
    proc_mem_ = std::stol(LinuxParser::Ram(pid));
}

// TODO: Return this process's ID
int Process::Pid() 
{ 
    return proc_id; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
    vector<string> proc_stats = LinuxParser::CpuUtilization(proc_id);
    // the following values are clock ticks
    long utime = std::stol(proc_stats[13]);
    long stime = std::stol(proc_stats[14]);
    long cutime = std::stol(proc_stats[15]);
    long cstime = std::stol(proc_stats[16]);
    float totaltime = (utime + stime + cutime + cstime) / sysconf(_SC_CLK_TCK);
    float totaluptime = UpTime(); // in seconds

    float proc_cpu_util = (totaltime - totaltime_prev) / (totaluptime - totaluptime_prev );

    totaltime_prev = totaltime;
    totaluptime_prev = totaluptime;

    return proc_cpu_util;
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
    return LinuxParser::Command(proc_id);
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    return to_string(proc_mem_);
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
    return LinuxParser::User(proc_id);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{ 
    return LinuxParser::UpTime(proc_id);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const 
{ 
    return (this->proc_mem_ > a.proc_mem_ );
}
