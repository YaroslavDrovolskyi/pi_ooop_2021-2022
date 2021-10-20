#include "Tasks.h"


Task::Task(const QString& title, const QString& description, const QString& executor, std::size_t group_index, TaskStatus status,
           const QDateTime& time_of_set, const QDateTime& start_time, const QDateTime& end_time){
    this->title_ = title;
    this->description_ = description;
    this->executor_ = executor;
    this->group_index_ = group_index;
    this->status_ = status;
    this->time_of_set = time_of_set;
    this->start_time_ = start_time;
    this->end_time_ = end_time;
}


bool Task::set_start_time(const QDateTime& start_time){
    if (this->status_ == TaskStatus::not_started){
        this->start_time_ = start_time;
        this->status_ = TaskStatus::started;

        return true;
    }
    return false;

}

bool Task::set_end_time(const QDateTime& end_time){
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



void TaskStructure::write_in_file() const{

}
