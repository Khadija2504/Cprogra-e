# Task Management System

This is a simple task management system written in C that allows you to **add**, **modify**, **delete**, and **display** tasks. Each task has a title, description, status, creation date, and a deadline. The tasks are categorized into three statuses: **To Do**, **In Progress**, and **Completed**.

## Features

- **Add** new tasks with a title, description, status, and deadline.
- **Modify** an existing task's title, description, status, or deadline.
- **Delete** tasks by their ID.
- **Search** for tasks by their ID or title.
- **View** all tasks and their deadlines.
- **Display** tasks that are due within a given number of days.
- **Calculate** the remaining days until a task's deadline.
- **Sort** tasks by title or deadline.

## Data Structures

### Task

Contains the task's:

- **ID**: Unique identifier for each task.
- **Title**: A short description of the task.
- **Description**: Detailed description of the task.
- **Status**: Task's current status (To Do, In Progress, Completed).
- **Creation Date**: The date the task was created.
- **Deadline**: The date by which the task needs to be completed.

### Date

A structure representing a date with:

- **Day**: The day of the month (1-31).
- **Month**: The month (1-12).
- **Year**: The year (e.g., 2024).

### Status

Tasks can have one of three statuses:

- **To Do**
- **In Progress**
- **Completed**

## Functions

- `addTache()`: Adds a new task to the system.
- `modifyTache(int id)`: Modifies an existing task by its ID.
- `deleteTache(int id)`: Deletes a task by its ID.
- `searchTacheById(int id)`: Searches for a task by its ID.
- `searchTacheByTitle(const char *title)`: Searches for a task by its title.
- `searchTacheByDeadline(struct Date deadlineDate)`: Searches for tasks with a deadline on or before a given date.
- `displayTaches()`: Displays all tasks.
- `displayTachesWithDeadline(struct Date DateActuelle, int days)`: Displays tasks that have a deadline within the next specified number of days.
- `joursRestants(struct Date DateActuelle)`: Displays the remaining days until each task's deadline.

## Example Usage

```c
#include <stdio.h>

int main() {
    // Initialize tasks
    addTache();
    addTache();

    // Display all tasks
    displayTaches();

    // Modify a task with ID 1
    modifyTache(1);

    // Delete task with ID 2
    deleteTache(2);

    // Search tasks by title
    searchTacheByTitle("Task Title");

    // Display tasks due in 5 days
    struct Date currentDate = {12, 11, 2024};
    displayTachesWithDeadline(currentDate, 5);

    // Calculate remaining days for each task
    joursRestants(currentDate);

    return 0;
}


