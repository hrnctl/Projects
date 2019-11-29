
package com.harun.todolistapp.domain;



/**
 *
 * @author Harun Çatal
 */
public class TodoList {

    private Integer todoListId;
    private Integer userId;
    private String month;
    private String day;
    private String year;
    private String title;
    private String description;
    private String status;

    public TodoList() {
    }

    public Integer getTodoListId() {
        return todoListId;
    }

    public void setTodoListId(Integer todoListId) {
        this.todoListId = todoListId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public String getMonth() {
        return month;
    }

    public void setMonth(String month) {
        this.month = month;
    }

    public String getDay() {
        return day;
    }

    public void setDay(String day) {
        this.day = day;
    }

    public String getYear() {
        return year;
    }

    public void setYear(String year) {
        this.year = year;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "TodoList{" + "todoListId=" + todoListId + ", userId=" + userId + ", month=" + month + ", day=" + day + ", year=" + year + ", title=" + title + ", description=" + description + ", status=" + status + '}';
    }
    

}
