
package com.harun.todolistapp.dao;


import javax.sql.DataSource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcDaoSupport;

/**
 *
 * @author Harun Çatal
 * 
 */

 abstract public class BaseDbOperations extends NamedParameterJdbcDaoSupport{
    @Autowired
    public void setDataSource2(DataSource ds){
         super.setDataSource(ds);
    }
    
}
