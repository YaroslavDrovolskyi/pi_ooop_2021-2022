#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <QString>
#include <QVector>
#include <QDate>
  enum class TaskStatus{not_started, started, paused, middle_progress, almost_finished, finished };

class Task{
    QString title_;
    QString descriprion_;
    QString executor_;
    std::size_t group_index_;
    TaskStatus status_;
    QDateTime time_of_set; // time, when task was set
    QDateTime start_time_;
    QDateTime end_time_;

public:
    Task(const QString& title, const QString& description, const QString& executor, std::size_t group_index, TaskStatus status,
         const QDateTime& time_of_set, const QDateTime& start_time, const QDateTime& end_time);

    QString get_title() const {return this->title_;}
    QString get_description() const {return this->description_;}
    QString get_executor() const {return this->executor_;}
    std::size_t get_group_index() const {return this->group_index_;}
    TaskStatus get_status() const {return this->status_;}
    QDateTime get_time_of_set() const {return this->time_of_set;}
    QDateTime get_start_time() const {return this->start_time_;}
    QDateTime get_end_time() const {return this->end_time_;}

    bool set_start_time(const QDateTime& start_time);
    bool set_end_time(const QDateTime& end_time);
    bool set_status(TaskStatus status);
};


class TaskGroup{
    QString title_;
    QVector<Task> tasks;

public:
    TaskGroup(const QString& title): title_(title){}
    void add_task(const Task& new_task);
};

class TaskStructure{
    QVector<TaskGroup> task_groups_;
};








#endif // TASKS_H
