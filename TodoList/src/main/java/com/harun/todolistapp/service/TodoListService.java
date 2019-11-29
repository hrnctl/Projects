
package com.harun.todolistapp.service;


import com.harun.todolistapp.domain.TodoList;
import java.util.List;

/**
 *
 * @author Harun Çatal
 */
public interface TodoListService {

    public void save(TodoList t);

    public void update(TodoList t);

    public void delete(Integer todoListId);

    public TodoList findById(Integer todoListId);

    public List<TodoList> findUserTodoList(Integer userId);

    public List<TodoList> findByStatus(Integer userId);

    public List<TodoList> findUserTodoList(Integer userId, String txt);

    public List<TodoList> findUserTodoListOnlyHigh(Integer userId);

    public List<TodoList> findUserTodoListOnlyMedium(Integer userId);

    public List<TodoList> findUserTodoListOnlyLow(Integer userId);
    
    

}
