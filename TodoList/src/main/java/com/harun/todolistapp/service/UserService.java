
package com.harun.todolistapp.service;


import com.harun.todolistapp.domain.TodoList;
import com.harun.todolistapp.domain.User;

/**
 *
 * @author Harun Çatal
 */
public interface UserService {
    public void register(User u);
    
    public User login(String loginName, String password);
    public void saveTodoList(TodoList t);
   
      
}
