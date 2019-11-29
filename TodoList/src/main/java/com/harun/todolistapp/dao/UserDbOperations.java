package com.harun.todolistapp.dao;

import com.harun.todolistapp.domain.User;

/**
 *
 * @author Harun Çatal
 */
public interface UserDbOperations {

    public void save(User u);

    public void update(User u);
}
