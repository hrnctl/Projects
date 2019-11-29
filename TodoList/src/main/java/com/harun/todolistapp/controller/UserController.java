
package com.harun.todolistapp.controller;

import com.harun.todolistapp.command.LoginCommand;
import com.harun.todolistapp.command.RegCommand;
import com.harun.todolistapp.domain.TodoList;
import com.harun.todolistapp.domain.User;
import com.harun.todolistapp.service.UserService;
import javax.servlet.http.HttpSession;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 *
 * @author Harun Çatal
 */
@Controller
public class UserController {
    
    @Autowired
    private UserService userService;
    
    @RequestMapping(value = {"/", "/index"})
    public String index() {
        return "index";
    }
    
    @RequestMapping(value = {"/aboutme"})
    public String getAboutMe() {
        return "aboutme"; // Return About me JSP page
    }
    
    @RequestMapping(value = {"/reg_form"})
    public String register(Model m) {
        RegCommand cmd = new RegCommand();
        m.addAttribute("command", cmd);
        return "register";
    }
    
    @RequestMapping(value = {"/register"})
    public String registerUser(@ModelAttribute("command") RegCommand cmd, Model m) {
        User u = cmd.getU();
        userService.register(u);
        
        return "redirect:loginform?act=reg"; // Redirecting means not to show JSP page rather it redirects to the "index" action handeler
    }
    
    @RequestMapping(value = {"/loginform"})
    public String loginForm(Model m) {
        LoginCommand cmd = new LoginCommand();
        m.addAttribute("command", cmd);
        return "login";
    }
    
    @RequestMapping(value = {"/logindo"})
    public String logindo(@ModelAttribute("command") LoginCommand cmd, Model m, HttpSession session) {
        User loggedinUser = userService.login(cmd.getLoginName(), cmd.getPassword());
        if (loggedinUser == null) {
            m.addAttribute("error", "User could not found. Please try again..");
            return "login";
        } else {
            addUserInSession(loggedinUser, session);
            return "redirect:addTask?act=taskpage";
        }
        
    }
    @RequestMapping(value ="/logout")
    public String logout(HttpSession session){
    session.invalidate();
    return "redirect:index?act=log";
    }
    
    @RequestMapping(value = {"/addTask"})
    public String addTask(Model m) {
        TodoList todoList = new TodoList();
        m.addAttribute("command", todoList);
        
        return "addNewTask";
    }
    
    private void addUserInSession(User u, HttpSession session) {
        session.setAttribute("user", u);
        session.setAttribute("userId", u.getUserId());
    }
    
}
