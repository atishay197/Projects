create table contacts (name varchar(40), phno varchar(12), uid varchar(20));
create table ingridient(name varchar(50) , qty int);
create table orderlist(name varchar(20), vegnonveg varchar(5), orderno varchar(5), profit int(10));

insert into ingridient values('Bread', 100);
insert into ingridient values('Chicken', 50);
insert into ingridient values('Vegetable', 40);
insert into ingridient values('Paneer', 40);
insert into ingridient values('Morroca', 30);
insert into ingridient values('American', 30);
insert into ingridient values('Mexican', 30);
insert into ingridient values('Coke', 50);
insert into ingridient values('Pepsi', 50);
insert into ingridient values('Mirinda', 50);
insert into ingridient values('7up', 50);
insert into ingridient values('Potato', 100);
insert into ingridient values('CI', 50);
insert into ingridient values('BI', 50);

/*
import java.sql.*;
import javax.swing.JOptionPane;
import javax.swing.table.*;


DefaultTableModel model = (DefaultTableModel)p1.getModel();
        try
        {
            Class.forName("java.sql.DriverManager");
            Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/atishaydatabase","","");
            
            Statement st = con.createStatement();
            String sql = "Select * from newtable;";
            ResultSet rs = st.executeQuery(sql);
            while(rs.next())
            {
                String a1 = rs.getString("a");
                String b1 = rs.getString("b");
                String c1 = rs.getString("c");
                model.addRow(new Object[]{a1,b1,c1});
            }
            rs.close();
            st.close();
            con.close();
        }
        catch (Exception e)
        {
            JOptionPane.showMessageDialog(this, "Error in connection");
        }





            Statement st = con.createStatement();
            String sql = "Select * from ingridient;";
            ResultSet rs = st.executeQuery(sql);
            while(rs.next())
            {
                String a1 = rs.getString("name");
                int b1 = rs.getInt("qty");
                model.addRow(new Object[]{a1,b1});
            }
            rs.close();
            st.close();
            con.close();
        }
*/