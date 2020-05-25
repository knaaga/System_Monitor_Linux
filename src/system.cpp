#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() 
{ 
    std::vector<std::string> cpu_fields_string = LinuxParser::CpuUtilization();
    cpu.SetCpuFields(cpu_fields_string);
    return cpu;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    processes.clear();
    vector<int> pids = LinuxParser::Pids();
    //std::reverse(pids.begin(), pids.end());
    for (int pid : pids)
    {
        Process p(pid);
        processes.push_back(p);
    }
    std::sort(processes.begin(), processes.end());
    return processes; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() 
{ 
    return LinuxParser::Kernel(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() 
{
    return LinuxParser::MemoryUtilization(); 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() 
{ 
    return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() 
{ 
    return LinuxParser::RunningProcesses(); 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() 
{ 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() 
{ 
    long val =  LinuxParser::UpTime(); 
    return val;
}