
package com.harun.todolistapp.rm;

import com.harun.todolistapp.domain.User;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.springframework.jdbc.core.RowMapper;

/**
 *
 * @author Harun Çatal
 */
public class UserRowMapper implements RowMapper<User> {

    @Override
    public User mapRow(ResultSet rs, int i) throws SQLException {
        User u = new User();
        u.setUserId(rs.getInt("userId"));
        u.setName(rs.getString("name"));
        u.setSurname(rs.getString("surname"));
        u.setLoginName(rs.getString("loginName"));
       
        return u;
    }

}
