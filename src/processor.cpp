#include "processor.h"
#include<vector>
#include<string>
#include<iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
    previdle_sum = previdle + previowait;
    idle_sum = idle + iowait;

    prevnonidle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal; //guest is already included in user
    nonidle = user + nice + system + irq + softirq + steal;

    prevtotal = previdle + prevnonidle;
    total = idle + nonidle;

    total_delta = total - prevtotal;
    nonidle_delta = nonidle - prevnonidle;

    cpu_utilization = nonidle_delta / total_delta;

    change_prev_to_current();

    return cpu_utilization;  
}

float Processor::SetCpuFields(std::vector<std::string> cpu_fields_string)
{
    user = std::stod(cpu_fields_string[1]);
    nice = std::stod(cpu_fields_string[2]);
    system = std::stod(cpu_fields_string[3]);
    idle = std::stod(cpu_fields_string[4]);
    iowait = std::stod(cpu_fields_string[5]);
    irq = std::stod(cpu_fields_string[6]);
    softirq = std::stod(cpu_fields_string[7]);
    steal = std::stod(cpu_fields_string[8]);
    guest = std::stod(cpu_fields_string[9]);
    guest_nice = std::stod(cpu_fields_string[10]);
}

void Processor::change_prev_to_current()
{
    prevuser = user;
    prevnice = nice;
    previdle = idle;
    prevsystem = system;
    previowait = iowait;
    previrq = irq;
    prevsoftirq = softirq;
    prevsteal = steal;
    prevguest = guest;
    prevguest_nice = guest_nice;
}