
package com.harun.todolistapp.controller;
import com.harun.todolistapp.domain.TodoList;
import com.harun.todolistapp.service.TodoListService;
import com.harun.todolistapp.service.UserService;
import javax.servlet.http.HttpSession;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

/**
 *
 * @author Harun Çatal
 */
@Controller
public class TodoListController {

    @Autowired
    private UserService userService;

    @Autowired
    private TodoListService todoListservice;

    @RequestMapping(value = {"/saveAddedTask"})
    public String saveOrUpdateAddedTask(@ModelAttribute("command") TodoList todoList, Model m, HttpSession session) {
        Integer todoListId = (Integer) session.getAttribute("pTodoListId");
        if (todoListId == null) {
            Integer userId = (Integer) session.getAttribute("userId");
            todoList.setUserId(userId);
            userService.saveTodoList(todoList);

            return "redirect:todoListlist?act=worklist";
        } else {
            todoList.setTodoListId(todoListId);
            todoListservice.update(todoList);
            return "redirect:todoListlist?act=worklist";

        }

    }

    @RequestMapping(value = {"/saveAddedTaskStatus"})
    public String updateAddedTask(@ModelAttribute("command") TodoList todoList, Model m, HttpSession session) {
        Integer todoListId = (Integer) session.getAttribute("pTodoListId");

        todoList.setTodoListId(todoListId);
        todoListservice.update(todoList);
        return "redirect:status?act=update";

    }

    @RequestMapping(value = {"/status"})
    public String giveStatus(Model m, HttpSession session) {
        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findByStatus(userId));
        return "viewTaskByStatus";
    }

    
    @RequestMapping(value = {"/todoListlist"})
    public String goToTodoListlist(Model m, HttpSession session) {

        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findUserTodoList(userId));
        

        return "todoListlist";
    }

    @RequestMapping(value = "/del_todoListlist")
    public String deleteTodoListList(@RequestParam("todoListId") Integer todoListId) {

        todoListservice.delete(todoListId);
        return "redirect:todoListlist?act=del";
    }

    @RequestMapping(value = "/del_todoListlist_status")
    public String deleteTodoListListStatus(@RequestParam("todoListId") Integer todoListId) {

        todoListservice.delete(todoListId);
        return "redirect:status?act=del";
    }
    
   
    
    @RequestMapping(value = {"/edit_todoListlist"})
    public String editList(Model m, HttpSession session, @RequestParam("todoListId") Integer todoListId) {

        session.setAttribute("pTodoListId", todoListId);
        TodoList t = todoListservice.findById(todoListId);
        m.addAttribute("command", t);
        return "addNewTask";
    }

    
    @RequestMapping(value = {"/edit_todoListlist_status"})
    public String editListStatus(Model m, HttpSession session, @RequestParam("todoListId") Integer todoListId) {

        session.setAttribute("pTodoListId", todoListId);
        TodoList t = todoListservice.findById(todoListId);
        m.addAttribute("command", t);
        return "addNewTaskStatus";
    }

    @RequestMapping(value = {"/search"})
    public String search(Model m, HttpSession session, @RequestParam("freetext") String freetext) {

        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findUserTodoList(userId, freetext));
        return "todoListlist";
    }

    @RequestMapping(value = {"/search_status"})
    public String searchStatus(Model m, HttpSession session, @RequestParam("freetext") String freetext) {
        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findUserTodoList(userId, freetext));
        return "viewTaskByStatus";
    }

    @RequestMapping(value = {"/High"})
    public String searchStatusHigh(Model m, HttpSession session) {
        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findUserTodoListOnlyHigh(userId));
        return "viewTaskByStatus";
    }

    
    @RequestMapping(value = {"/Low"})
    public String searchStatusLow(Model m, HttpSession session) {
        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findUserTodoListOnlyLow(userId));
        return "viewTaskByStatus";
    }
    
    @RequestMapping(value = {"/time"})
    public String giveTimetask(Model m, HttpSession session) {

        Integer userId = (Integer) session.getAttribute("userId");
        m.addAttribute("todoListlists", todoListservice.findUserTodoList(userId));

        return "todoListlist";
    }

    
}
