
package com.harun.todolistapp.service;

import com.harun.todolistapp.dao.BaseDbOperations;
import com.harun.todolistapp.dao.TodoListDbOperations;

import com.harun.todolistapp.domain.TodoList;
import com.harun.todolistapp.rm.TodoListRowMapper;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 *
 * @author Harun Çatal
 */
@Service
public class TodoListServiceImplementation extends BaseDbOperations implements TodoListService {

    @Autowired
    private TodoListDbOperations todoListDbOp;
    
  
    @Override
    public void save(TodoList t) {
        throw new UnsupportedOperationException("Not supported yet."); }

    @Override
    public void update(TodoList t) {
        todoListDbOp.update(t);
    }

    @Override
    public void delete(Integer todoListId) {
        todoListDbOp.delete(todoListId);
    }

    @Override
    public TodoList findById(Integer todoListId) {
        return todoListDbOp.findById(todoListId);
    }

    @Override
    public List<TodoList> findUserTodoList(Integer userId) {
        return todoListDbOp.findByProperty("userId", userId);
    }

    @Override
    public List<TodoList> findUserTodoList(Integer userId, String txt) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE userId=? AND (month LIKE '%" + txt + "%' OR day LIKE '%" + txt + "%' OR year LIKE '%" + txt + "%' OR title LIKE '%" + txt + "%' OR description LIKE '%" + txt + "%' OR status LIKE '%" + txt + "%')";
        return getJdbcTemplate().query(sql, new TodoListRowMapper(), userId);
    }

    @Override
    public List<TodoList> findByStatus(Integer userId) {
        return todoListDbOp.orderByStatus("userId", userId);
    }

    @Override
    public List<TodoList> findUserTodoListOnlyHigh(Integer userId) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE userId=? AND status='a'";
        return getJdbcTemplate().query(sql, new TodoListRowMapper(), userId);
    }

    @Override
    public List<TodoList> findUserTodoListOnlyMedium(Integer userId) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE userId=? AND status='b'";
        return getJdbcTemplate().query(sql, new TodoListRowMapper(), userId);
    }

    @Override
    public List<TodoList> findUserTodoListOnlyLow(Integer userId) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE userId=? AND status='c'";
        return getJdbcTemplate().query(sql, new TodoListRowMapper(), userId);
    }
   
}
