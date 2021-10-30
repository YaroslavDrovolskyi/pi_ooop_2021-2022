#include "Tasks.h"
#include <fstream>
#include <cassert>


Task::Task(const std::string& title, const std::string& description, const std::string& executor, std::size_t group_index, TaskStatus status,
           const Time& time_of_set, const Time& start_time, const Time& end_time){
    this->title_ = title;
    this->description_ = description;
    this->executor_ = executor;
    this->group_index_ = group_index;
    this->status_ = status;
    this->time_of_set = time_of_set;
    this->start_time_ = start_time;
    this->end_time_ = end_time;
}


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

bool Task::set_status(TaskStatus status){
    if (this->status_ != TaskStatus::finished){
        this->status_ = status;
        return true;
    }

    return false;
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

            file_tasks.write((char*)&task.status_, sizeof(TaskStatus));
            file_tasks.write((char*)&task.time_of_set, sizeof(Time));
            file_tasks.write((char*)&task.start_time_, sizeof(Time));
            file_tasks.write((char*)&task.end_time_, sizeof(Time));
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

        file.read((char*)&new_item.status_, sizeof(TaskStatus));
        file.read((char*)&new_item.time_of_set, sizeof(Time));
        file.read((char*)&new_item.start_time_, sizeof(Time));
        file.read((char*)&new_item.end_time_, sizeof(Time));

        /*
        if (new_item.group_index_ == task_groups_.size()){
            assert(new_item.group_index_ < groups_titles.size());
            add_task_group(groups_titles[new_item.group_index_]);
        }
        */
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
