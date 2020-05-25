#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return (version + " " + kernel);
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  vector<string> key_words {"MemTotal", "MemFree", "Buffers"};
  double MemUtil, MemTotal, MemFree;
  vector<string> memtype, memory, unit;
  string line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      for (size_t i = 0 ; i < key_words.size(); i++)
      {
        if (line.find(key_words[i]) != string::npos)
        {
          std::istringstream linestream (line);
          string memtype_temp, memory_temp, unit_temp;
          linestream >> memtype_temp >> memory_temp >> unit_temp;
          memtype.push_back(memtype_temp);
          memory.push_back(memory_temp);
          unit.push_back(unit_temp);
        }
      }
    }
  }
  MemTotal = std::stod(memory[0]);
  MemFree = std::stod(memory[1]);

  MemUtil = 1 - MemFree/(MemTotal);

  return MemUtil;  
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  string line;
  long int uptime, idletime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream (line);
    linestream >> uptime >> idletime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
//long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
//long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
//long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
//long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
std::vector<std::string> LinuxParser::CpuUtilization() 
{
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string line;
  string key_word = "cpu "; //note the space
  string field;
  std::vector<std::string> cpu_fields_string;
  if (filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      if(line.find(key_word) != string::npos)
      {
        std::istringstream linestream(line);
        while(linestream>>field)
        {
          cpu_fields_string.push_back(field);
        }          
      }
    }
  }
  return cpu_fields_string; 
}

std::vector<std::string> LinuxParser::CpuUtilization(int pid)
{
  string field;
  std::vector<std::string> proc_stats;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open())
  {
    while(std::getline(filestream, field, ' '))
    {
      proc_stats.push_back(field);
    }
  }
  
  return proc_stats;
  
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  string line;
  int value;
  string key_word = "processes";
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      if (line.find(key_word) != string::npos)
      {
        std::istringstream linestream(line);
        linestream >> key_word >> value;
      }
        
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
  string line;
  int value;
  string key_word = "procs_running";
  std::ifstream filestream(kProcDirectory + kStatFilename);
  
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      if (line.find(key_word) != string::npos)
      {
        std::istringstream linestream(line);
        linestream >> key_word >> value;
      }
        
    }
  }
  return value;
}


// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  string line;
  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open())
  {
    std::getline(filestream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) 
{ 
  string key, memory, unit;
  string line;
  string key_word = "VmSize:";
  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      if (line.find(key_word) != string::npos)
      {
        std::istringstream linestream(line);
        linestream >> key >> memory >> unit;
      }
    }
  }
  if (memory == "")
    return "0";
  else
    return std::to_string(std::stol(memory) / 1024);

}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
//string LinuxParser::Uid(int pid) {return string();}


// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid)
{ 
  string line, line2;
  string key_word = "Uid:";
  string key, userid, username, temp1, temp2, temp3, temp4;
  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      if(line.find(key_word) != string::npos)
      {
        std::istringstream linestream(line);
        linestream >> key >> userid >> temp1 >> temp2 >>temp3;
      }
    }
  }
  std::ifstream filestream2 (kPasswordPath);
  if(filestream2.is_open())
  {
    while(std::getline(filestream2, line2))
    {
      if(line2.find(userid) != string::npos)
      {
        std::istringstream linestream2(line2);
        username = line2.substr(0,line2.find(":"));
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{ 
  vector<string> fields;
  string field;
  long process_start_clock_ticks, process_uptime_seconds;
  long system_uptime_seconds = UpTime();
  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open())
  {
    while(std::getline(filestream, field, ' '))
      fields.push_back(field);
  }
  process_start_clock_ticks = std::stol(fields[21]);
  process_uptime_seconds = system_uptime_seconds - process_start_clock_ticks / sysconf(_SC_CLK_TCK); 
  return process_uptime_seconds;
  
}