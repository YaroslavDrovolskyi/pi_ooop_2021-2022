#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>

enum class TaskStatus{not_started, started, paused, middle_progress, almost_finished, finished };

/*
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
*/

struct Task{
private:
    std::string title_;
    std::string description_;
    std::string executor_;
    std::size_t group_index_; // index of group, where item is stored
    int  status_; // progress in procents
    int spent_hours_;

    friend class TaskStructure;
public:
    Task(){;}
    Task(const std::string& title, const std::string& description, const std::string& executor, std::size_t group_index, int status,
         int spend_hours_);

    // getters
    std::string get_title() const {return this->title_;}
    std::string get_description() const {return this->description_;}
    std::string get_executor() const {return this->executor_;}
    std::size_t get_group_index() const {return this->group_index_;}
    int get_status() const {return this->status_;}
    int get_spent_hours() const {return this->spent_hours_;}

    // setters
    void set_title(const std::string& new_title);
    void set_description(const std::string& new_descriprion);
    void set_executor(const std::string& new_executor);
    void set_status(int status);
    void set_spent_hours(int new_spent_hours);

    static Task get_default_task(std::size_t taskgroup_index);

    std::string get_html_text() const;

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
    std::size_t size();
    Task& operator[] (const int index);

    static TaskGroup get_default_taskgroup();

    void remove_task(std::size_t index);

    std::string get_html_text() const;
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
  std::size_t size();
  TaskGroup& operator[] (const int index);

  void remove_group(std::size_t index);
  void remove_task(std::size_t group_index, std::size_t task_index);

  std::string get_html_text() const;
//public slots:



//    signals:

};








#endif // TASKS_H
