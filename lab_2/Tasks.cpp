#include "Tasks.h"
#include <fstream>
#include <cassert>
#include <algorithm>


Task::Task(const std::string& title, const std::string& description, const std::string& executor, std::size_t group_index, int status, int spent_hours){
    this->title_ = title;
    this->description_ = description;
    this->executor_ = executor;
    this->group_index_ = group_index;
    this->status_ = status;
    this->spent_hours_ = spent_hours;
//    this->time_of_set = time_of_set;
//    this->start_time_ = start_time;
//    this->end_time_ = end_time;
}

/*
bool Task::set_start_time(const Time& start_time){
    if (this->status_ == TaskStatus::not_started){
        this->start_time_ = start_time;
        this->status_ = TaskStatus::started;

        return true;
    }
    return false;

}

bool Task::set_end_time(const Time& end_time){
    if (this->status_ != TaskStatus::not_started && this->status_ != TaskStatus::finished){
        this->end_time_ = end_time;
        this->status_ = TaskStatus::started;

        return true;
    }
    return false;
}

*/

void Task::set_status(int status){
    this->status_ = status;
}



void TaskStructure::write_in_file(const std::string& filename_tasks, const std::string& filename_groups) const{
    write_groups_titles(filename_groups);

    std::ofstream file_tasks(filename_tasks, std::ios::binary | std::ofstream::trunc);
    for(auto& group : this->task_groups_){
        for(const Task& task : group.tasks_){
            std::size_t str_size = 0;

            file_tasks.write((char*)&task.group_index_, sizeof(std::size_t));

            // write title
            str_size = task.title_.size();
            file_tasks.write((char*)&str_size, sizeof(str_size));
            file_tasks.write(&(task.title_)[0], str_size);

            // write description
            str_size = task.description_.size();
            file_tasks.write((char*)&str_size, sizeof(str_size));
            file_tasks.write(&(task.description_)[0], str_size);

            // write executor
            str_size = task.executor_.size();
            file_tasks.write((char*)&str_size, sizeof(str_size));
            file_tasks.write(&(task.executor_)[0], str_size);

            file_tasks.write((char*)&task.status_, sizeof(int));
            file_tasks.write((char*)&task.spent_hours_, sizeof(int));
//            file_tasks.write((char*)&task.time_of_set, sizeof(Time));
//            file_tasks.write((char*)&task.start_time_, sizeof(Time));
//            file_tasks.write((char*)&task.end_time_, sizeof(Time));
        }
    }


    file_tasks.close();

}

int TaskStructure::read_from_file(const std::string& file_tasks, const std::string& file_groups){
    read_groups_titles(file_groups);

    std::ifstream file;
    file.open(file_tasks, std::ios::binary);
    std::size_t str_size;
    Task new_item;

    while (file.read((char*)&new_item.group_index_, sizeof(std::size_t))) {

        // read title
        file.read((char*)&str_size, sizeof(str_size));
        new_item.title_.resize(str_size);
        file.read(&(new_item.title_)[0], str_size);

        // read description
        file.read((char*)&str_size, sizeof(str_size));
        new_item.description_.resize(str_size);
        file.read(&(new_item.description_)[0], str_size);

        // read executor
        file.read((char*)&str_size, sizeof(str_size));
        new_item.executor_.resize(str_size);
        file.read(&(new_item.executor_)[0], str_size);

        file.read((char*)&new_item.status_, sizeof(int));
        file.read((char*)&new_item.spent_hours_, sizeof(int));
        add_task(new_item);
    }
        file.close();

        return 1;

}

int TaskStructure::add_task(const Task &new_item){
    if (new_item.group_index_ < this->task_groups_.size()){
        this->task_groups_[new_item.group_index_].add_task(new_item);
        return 1;
    }
    return -1;
}

int TaskStructure::add_task_group(const std::string& group_title){
    this->task_groups_.push_back(TaskGroup(group_title));

    return 1;
}

int TaskGroup::add_task(const Task &new_item){
    this->tasks_.push_back(new_item);
    return 1;
}

void TaskStructure::write_groups_titles(const std::string& filename) const{
    // write groups titles
    std::ofstream file(filename, std::ios::binary | std::ofstream::trunc);
    for(auto& group : this->task_groups_){
        std::string title = group.get_title();
        std::size_t title_size = title.size();

        file.write((char*)&title_size, sizeof(std::size_t));
        file.write(&(title)[0], title_size);
    }
    file.close();
}

void TaskStructure::read_groups_titles(const std::string& filename){
    std::ifstream file(filename, std::ios::binary);
    std::string title;
    std::size_t title_size;
    while (file.read((char*)&title_size, sizeof(std::size_t))){
        title.resize(title_size);
        file.read(&(title)[0], title_size);

        add_task_group(title);
    }
}



void TaskGroup::set_title(const std::string& new_title){
    this->title_ = new_title;
}


void Task::set_title(const std::string& new_title){
    this->title_ = new_title;
}

void Task::set_description(const std::string& new_description){
    this->description_ = new_description;
}

void Task::set_executor(const std::string& new_executor){
    this->executor_ = new_executor;
}

void Task::set_spent_hours(int new_spent_hours){
    this->spent_hours_ = new_spent_hours;
}


TaskGroup& TaskStructure::operator[] (const int index){
    assert(index >= 0 && index < this->task_groups_.size());

    return this->task_groups_[index];
}

Task& TaskGroup::operator[] (const int index){
    assert(index >= 0 && index < this->tasks_.size());

    return this->tasks_[index];
}

std::size_t TaskGroup::size(){
    return this->tasks_.size();
}

std::size_t TaskStructure::size(){
    return this->task_groups_.size();
}


Task Task::get_default_task(std::size_t taskgroup_index){
    Task a("default title", "default description", "executor", taskgroup_index, 0, 0);
    return a;
}

TaskGroup TaskGroup::get_default_taskgroup(){
    return TaskGroup("group title");
}

void TaskGroup::remove_task(std::size_t index){
    assert(index < tasks_.size());

    tasks_.erase(tasks_.begin() + index);
}

void TaskStructure::remove_task(std::size_t group_index, std::size_t task_index){
    assert(group_index < task_groups_.size());

    task_groups_[group_index].remove_task(task_index);
}

void TaskStructure::remove_group(std::size_t index){
    assert(index < task_groups_.size());
    task_groups_.erase(task_groups_.begin() + index);

    for(std::size_t i = index; i < task_groups_.size(); i++){ // fix indexes of groups
        for(Task& task : task_groups_[i].tasks_){
            task.group_index_--;
        }
    }
}

std::string Task::get_html_text() const{
    std::string result = "<div align = left><b>Title: </b>" + this->title_ + "</div>";
    result += "<div align = left><b>Description: </b>" + this->description_ + "</div>";
    result += "<div align = left><b>Executor: </b>" + this->executor_ + "</div>";
    result += "<div align = left><b>Status: </b>" + std::to_string(this->status_) + "% </div>";
    result += "<div align = left><b>Spent time: </b>" + std::to_string(this->spent_hours_) +  " hours <br> </div>";

    return result;
}

std::string TaskGroup::get_html_text() const {
    std::string result = "<h2 align = center>" + this->title_ + "</h2>";
    if (tasks_.size() == 0){
        result += "<div align = center> This group is empty <br> </div>";
    }
    else{
        for(const Task& task : tasks_){
            result+=task.get_html_text();
        }
    }

    return result;
}

std::string TaskStructure::get_html_text() const{
    std::string result = "";
    if (task_groups_.size() == 0){
        result += "<div align = center> No tasks and no groups of tasks <br> </div>";
    }
    else{
        for(const TaskGroup& group : task_groups_){
            result+=group.get_html_text();
        }
    }

    return result;
}

void TaskGroup::sort_tasks(bool (*comparator)(const Task&, const Task&)){
    std::sort(tasks_.begin(), tasks_.end(), comparator);
}

void TaskStructure::sort_tasks(bool (*comparator)(const Task&, const Task&)){
    for(TaskGroup& group : task_groups_){
        group.sort_tasks(comparator);
    }
}

bool Task::compare_by_title(const Task &a, const Task &b){
    return a.get_title() < b.get_title();
}

bool Task::compare_by_status(const Task &a, const Task &b){
        return a.get_status() <= b.get_status();
}

bool Task::compare_by_spent_hours(const Task &a, const Task &b){
    return a.get_spent_hours() <= b.get_spent_hours();
}
