
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib uri="http://www.springframework.org/tags" prefix="s" %>
<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>User To do List</title>
        <link href="static/css/todolist.css" rel="stylesheet" type="text/css"/>

    </head>
    <body>
        <!-- ${todoListlists} -->

        <div>
            <jsp:include page="include/menu.jsp"/>
        </div>
        </br>
        </br>

        <div class="heading">
            <p><h2>Your Working List</h2></p>
    </div>
        <div class="search">
            <form action="<s:url value="/search"/>">
                <input type="text" name="freetext" placeholder="search">
                <button>Find</button>
            </form>
        </div>



    <table class="container">
        <thead>
            <tr>
                <th><h1>Month</h1></th>
                <th><h1>Day</h1></th>
                <th><h1>Year</h1></th>
                <th><h1>Title</h1></th>
                <th><h1>Description</h1></th>
                <th><h1>Status</h1></th>
                <th><h1>Action</h1></th>

            </tr>
        </thead>
        <tbody>

            <c:forEach var="t" items="${todoListlists}" varStatus = "status">
                <tr>

                    <td>${t.month}</td>
                    <td>${t.day}</td>
                    <td>${t.year}</td>
                    <td>${t.title}</td>
                    <td><textarea name="" id="t" cols="6" rows="3">${t.description}</textarea></td>
                        <c:if test="${t.status == 'a'}">
                        <td>(+) Completed</td>
                    </c:if>
                    
                    <c:if test="${t.status == 'c'}">
                        <td>(-) No Completed</td>
                    </c:if>
                    <s:url var="url_delete" value="/del_todoListlist">
                        <s:param name="todoListId" value="${t.todoListId}"/>
                    </s:url>
                    <s:url var="url_edit" value="/edit_todoListlist">
                        <s:param name="todoListId" value="${t.todoListId}"/>
                    </s:url>


                    <td><a href="${url_edit}" id="a1">Edit</a>| <a href="${url_delete}" id="a2">Delete</a></td>
                </tr>

            </c:forEach>
        </tbody>
    </table>
</body>
</html>
