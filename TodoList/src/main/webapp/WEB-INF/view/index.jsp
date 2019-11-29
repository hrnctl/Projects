
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@taglib uri="http://www.springframework.org/tags/form" prefix="f" %>

<%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>

<%@taglib uri="http://www.springframework.org/tags" prefix="s" %>
<!DOCTYPE html>
<html>
    
    <div>
        <jsp:include page="include/menu.jsp"/>
    </div>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Registration</title>
        <link href="static/css/style_index.css" rel="stylesheet" type="text/css"/>
    </head>
    <body>

        <div id="main">
        	</br>
        	</br>
        	</br>
        	</br>
        	</br>
            <h1>Welcome to To Do List Application</h1>
            
         	<h2></h2>
         	<s:url var="url_registrationform" value="/reg_form"/>
            <h2>You can easily <a href="${url_registrationform}">register</a> and start to a planned life</h2>
        </div>
        <div id="footer">
            <footer>
                <jsp:include page="include/footer.jsp"/>
            </footer>
        </div>
    </body>
</html>
