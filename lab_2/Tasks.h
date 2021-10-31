#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>

enum class TaskStatus{not_started, started, paused, middle_progress, almost_finished, finished };

struct Time{
   short int day;
   short int month;
   short int year;

   short int hours;
   short int minutes;
   short int seconds;

   Time(){
       day = month = year = 1;
       hours = minutes = seconds = 1;
   }
   Time(short int day, short int month, short int year, short int hours, short int minutes, short int seconds){
       this->day = day;
       this->month = month;
       this->year = year;
       this->hours = hours;
       this->minutes = minutes;
       this->seconds = seconds;
   }
};

struct Task{
public:
    std::string title_;
    std::string description_;
    std::string executor_;
    std::size_t group_index_; // index of group, where item is stored
    TaskStatus status_;
//    Time time_of_set; // time, when task was set
//    Time start_time_;
//    Time end_time_;
    int spent_hours_;

public:
    Task(){;}
    Task(const std::string& title, const std::string& description, const std::string& executor, std::size_t group_index, TaskStatus status,
         int spend_hours_);

    // getters
    std::string get_title() const {return this->title_;}
    std::string get_description() const {return this->description_;}
    std::string get_executor() const {return this->executor_;}
    std::size_t get_group_index() const {return this->group_index_;}
    TaskStatus get_status() const {return this->status_;}
//    Time get_time_of_set() const {return this->time_of_set;}
//    Time get_start_time() const {return this->start_time_;}
//    Time get_end_time() const {return this->end_time_;}

    // setters
    void set_title(const std::string& new_title);
    void set_description(const std::string& new_descriprion);
    void set_executor(const std::string& new_executor);
    bool set_status(TaskStatus status);
    void set_spent_hours(int new_spent_hours);
//    bool set_start_time(const Time& start_time);
//    bool set_end_time(const Time& end_time);


};


class TaskGroup{
    std::string title_;
    std::vector<Task> tasks_;

    friend class TaskStructure;
public:
    TaskGroup(const std::string& title): title_(title){}
    int add_task(const Task& new_item);
    std::string get_title() const {return this->title_;}
    void set_title(const std::string& new_title);
};

class TaskStructure{
private:
  std::vector<TaskGroup> task_groups_;

  void read_groups_titles(const std::string& filename);
  void write_groups_titles(const std::string& filename) const;
public:
  void write_in_file(const std::string& file_tasks, const std::string& file_groups) const;
  int read_from_file(const std::string& file_tasks, const std::string& file_groups);
  int add_task_group(const std::string& group_title);
  int add_task(const Task& new_task);

//public slots:



//    signals:

};








#endif // TASKS_H
