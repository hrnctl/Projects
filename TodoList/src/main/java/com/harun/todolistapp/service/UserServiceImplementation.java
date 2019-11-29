
package com.harun.todolistapp.service;

import com.harun.todolistapp.dao.BaseDbOperations;

import com.harun.todolistapp.dao.TodoListDbOperations;
import com.harun.todolistapp.dao.UserDbOperations;
import com.harun.todolistapp.domain.TodoList;

import com.harun.todolistapp.domain.User;
import com.harun.todolistapp.rm.UserRowMapper;
import java.util.HashMap;
import java.util.Map;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.stereotype.Service;

/**
 *
 * @author Harun Çatal
 */
@Service
public class UserServiceImplementation extends BaseDbOperations implements UserService {

    @Autowired
    private UserDbOperations userDbOp;
    
    @Autowired
    private TodoListDbOperations todoListDbOp;
    
 
    @Override
    public void register(User u) {
        userDbOp.save(u);
    }

    @Override
    public User login(String loginName, String password) {
        String sql = "SELECT userid, name, surname,loginName FROM user WHERE loginName=:ln AND password=:pw";
        Map m = new HashMap();
        m.put("ln", loginName);
        m.put("pw", password);
        try{
            User u = getNamedParameterJdbcTemplate().queryForObject(sql, m, new UserRowMapper());
            
            return u;
        } catch(EmptyResultDataAccessException ex)
        {
        return null;
        }
        

    }

    @Override
    public void saveTodoList(TodoList t) {
       todoListDbOp.save(t);
    }
    
    

}
