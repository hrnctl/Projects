
package com.harun.todolistapp.rm;

import com.harun.todolistapp.domain.TodoList;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.jdbc.core.RowMapper;

/**
 *
 * @author Harun Çatal
 */
public class TodoListRowMapper implements RowMapper<TodoList>{

    @Override
    public TodoList mapRow(ResultSet rs, int i) throws SQLException {
       TodoList t=new TodoList();
       t.setTodoListId(rs.getInt("todoListId"));
       t.setUserId(rs.getInt("userId"));
       t.setMonth(rs.getString("month"));
       t.setDay(rs.getString("day"));
       t.setYear(rs.getString("year"));
       t.setTitle(rs.getString("title"));
       t.setDescription(rs.getString("description"));
       t.setStatus(rs.getString("status"));
       return t;
       
    }
    
}
