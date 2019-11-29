
package com.harun.todolistapp.dao;

import com.harun.todolistapp.domain.TodoList;
import com.harun.todolistapp.rm.TodoListRowMapper;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.SqlParameterSource;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Repository;

/**
 *
 * @author Harun Çatal
 */
@Repository
public class TodoListDbOperationsImplementation extends BaseDbOperations implements TodoListDbOperations {

    @Override
    public void save(TodoList todoList) {
        String sql = "INSERT INTO todoList (userId,month,day,year,title,description,status) VALUES (:userId, :month, :day, :year, :title, :description, :status)";
        Map m = new HashMap();
        m.put("userId", todoList.getUserId());
        m.put("month", todoList.getMonth());
        m.put("day", todoList.getDay());
        m.put("year", todoList.getYear());
        m.put("title", todoList.getTitle());
        m.put("description", todoList.getDescription());
        m.put("status", todoList.getStatus());

        SqlParameterSource ps = new MapSqlParameterSource(m);
        KeyHolder kh = new GeneratedKeyHolder();
        getNamedParameterJdbcTemplate().update(sql, ps, kh);
        Integer todoListId = kh.getKey().intValue();
        todoList.setTodoListId(todoListId);

    }

    @Override
    public void update(TodoList todoList) {
        String sql = "UPDATE todoList SET month=:month, day=:day, year=:year, title=:title, description=:description, status=:status  WHERE todoListId=:todoListId";
        Map m = new HashMap();
        m.put("todoListId", todoList.getTodoListId());
        m.put("month", todoList.getMonth());
        m.put("day", todoList.getDay());
        m.put("year", todoList.getYear());
        m.put("title", todoList.getTitle());
        m.put("description", todoList.getDescription());
        m.put("status", todoList.getStatus());

        getNamedParameterJdbcTemplate().update(sql, m);
    }

    @Override
    public void delete(TodoList todoList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void delete(Integer todoListId) {
        String sql = "DELETE FROM todoList WHERE todoListId=?";
        getJdbcTemplate().update(sql, todoListId);
    }

    @Override
    public TodoList findById(Integer todoListId) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE todoListId=?";
        return getJdbcTemplate().queryForObject(sql, new TodoListRowMapper(), todoListId);
    }

    @Override
    public List<TodoList> findAll() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public List<TodoList> findByProperty(String propName, Object propValue) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE " + propName + "=?";
        return getJdbcTemplate().query(sql, new TodoListRowMapper(), propValue);
    }

    @Override
    public List<TodoList> orderByStatus(String propName, Object propValue) {
        String sql = "SELECT todoListId, userId, month, day, year, title, description, status FROM todoList WHERE " + propName + "=? ORDER BY status";
        return getJdbcTemplate().query(sql, new TodoListRowMapper(), propValue);
    }

}
