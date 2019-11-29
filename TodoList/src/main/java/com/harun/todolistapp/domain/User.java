package com.harun.todolistapp.domain;

/**
 *
 * @author Harun Çatal
 */
public class User {

    private Integer userId;
    private String name;
    private String surname;
    private String loginName;
    private String password;
    private String loginStatus;

    public User() {
    }
    

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getLoginName() {
        return loginName;
    }

    public void setLoginName(String loginName) {
        this.loginName = loginName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getLoginStatus() {
        return loginStatus;
    }

    public void setLoginStatus(String loginStatus) {
        this.loginStatus = loginStatus;
    }

    @Override
    public String toString() {
        return "User{" + "userId=" + userId + ", name=" + name + ", surname=" + surname + ", loginName=" + loginName + ", password=" + password + ", loginStatus=" + loginStatus + '}';
    }

}
