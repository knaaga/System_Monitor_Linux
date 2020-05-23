#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<vector>
#include<string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  float SetCpuFields(std::vector<std::string>);
  void change_prev_to_current();

  // TODO: Declare any necessary private members
 private:
    double user, prevuser ;
    double nice, prevnice ;
    double system, prevsystem ;
    double idle, previdle ;
    double iowait, previowait ;
    double irq, previrq ;
    double softirq, prevsoftirq ;
    double steal, prevsteal ;
    double guest, prevguest ;
    double guest_nice, prevguest_nice ;

    double idle_sum, previdle_sum;
    double nonidle, prevnonidle ;
    double total, prevtotal ;

    double nonidle_delta ;
    double total_delta ;

    float cpu_utilization ;
};

#endif