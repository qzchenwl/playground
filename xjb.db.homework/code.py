# -*- coding: utf8 -*-

import web,sqlite3

urls = ('/', 'Index',
        '/view/(.+)', 'View',
        '/login', 'Login',
        '/logout', 'Logout',
        '/search', 'Search',
        '/insert', 'Insert',
        '/delete', 'Delete',
        '/goto_insert','Goto_insert',
        '/forbidden','Forbidden')
app = web.application(urls, globals())
t_globals = {
        'cookie': web.cookies,
        }
render = web.template.render('templates', globals = t_globals)

class Index:
    def GET(self):
        if web.cookies().get('username'):
            return render.index()
        else:
            return render.login()

class Login:
    def POST(self):
        conn = sqlite3.connect('student.db')
        cur = conn.cursor()
        i = web.input(username='', password='')
        cur.execute("select * from user where ID=\""+i.username+"\" and PASSWORD=\""+i.password+"\"")
        if(cur.fetchall()):
            web.setcookie('username', i.username)
            conn.close()
            raise web.seeother('/')
        else:
            conn.close()
            raise web.seeother('/')

class Logout:
    def GET(self):
        web.setcookie('username', '', expires=-1)
        raise web.seeother('/')

class View:
    def GET(self, table_name):
        if not web.cookies().get('username'):
            raise web.seeother('/forbidden')
        try:
            conn = sqlite3.connect('student.db')
            cur = conn.cursor()
            cur.execute("select * from " + table_name)
            rows = cur.fetchall()
            all_pri = fetch_primary()
        except:
            rows = (("no table named " + table_name, ),)
            all_pri = {}
        conn.close()
        return render.rows(table_name, all_pri, rows)

class Goto_insert:
    def POST(self):
        i = web.input(table='')
        all_pri = fetch_primary()
        if i.table == "student":
            return render.student(all_pri)
        if i.table == "teacher":
            return render.teacher(all_pri)
        if i.table == "course":
            return render.course(all_pri)
        if i.table == "dept":
            return render.dept(all_pri)

class Delete:
    def POST(self):
        conn = sqlite3.connect('student.db')
        cur = conn.cursor()
        i = web.input(table='')
        if i.table == "student":
            i = web.input(id='', name='', sex='', age='', dept='', _class='')
            sql = "delete from student where id=\"%s\" and name=\"%s\" and sex=\"%s\" and age=%s and sdept=\"%s\" and class=\"%s\"" % (i.id, i.name, i.sex, i.age, i.dept, i._class)
            try:
                cur.execute(sql)
            except:
                return render.db_error()
            conn.commit()
            cur.execute("select * from student")
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "student"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "teacher":
            i = web.input(id='', name='', sex='', dept='')
            sql = "delete from teacher where id=\"%s\" and name=\"%s\" and sex=\"%s\" and tdept=\"%s\"" % (i.id, i.name, i.sex, i.dept)
            try:
                cur.execute(sql)
            except:
                return render.db_error()
            conn.commit()
            cur.execute("select * from teacher")
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "teacher"
            return render.rows(table_name, all_pri, rows)

class Insert:
    def POST(self):
        conn = sqlite3.connect('student.db')
        cur = conn.cursor()
        i = web.input(table='')
        if i.table == "student":
            i = web.input(id='', name='', sex='', age='', dept='', _class='')
            sql = "insert into student values(\"%s\",\"%s\",\"%s\",%s,\"%s\",\"%s\")" % (i.id, i.name, i.sex, i.age, i.dept, i._class)
            try: 
                cur.execute(sql)
            except:
                return render.db_error()
            conn.commit()
            cur.execute("select * from student")
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "student"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "teacher":
            i = web.input(id='', name='', sex='', dept='')
            sql = "insert into teacher values(\"%s\", \"%s\", \"%s\", \"%s\")" % (i.id, i.name, i.sex, i.dept)
            try:
                cur.execute(sql)
            except:
                return render.db_error()
            conn.commit()
            cur.execute("select * from teacher")
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "teacher"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "course":
            i = web.input(id='', name='', credit='')
            sql = "insert into course values(\"%s\", \"%s\", \"%s\")" % (i.id, i.name, i.credit)
            try:
                cur.execute(sql)
            except:
                return render.db_error()
            conn.commit()
            cur.execute("select * from course")
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "course"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "dept":
            i = web.input(id='', name='', description='')
            sql = "insert into dept values(\"%s\", \"%s\", \"%s\")" % (i.id, i.name, i.description)
            try:
                cur.execute(sql)
            except:
                return render.db_error()
            conn.commit()
            cur.execute("select * from dept")
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "dept"
            return render.rows(table_name, all_pri, rows)

class Search:
    def POST(self):
        conn = sqlite3.connect('student.db')
        cur = conn.cursor()
        i = web.input(table='')
        if i.table == "student":
            sql0 = "select * from student "
            sql = ""
            i = web.input(id='', name='', sex='', age='', dept='')
            x = 0
            if i.id:
                if x == 1:
                    sql += " and "
                sql += "id = \"" + i.id + "\" "
                x = 1
            if i.name:
                if x == 1:
                    sql += " and "
                sql += "name = \"" + i.name + "\" "
                x = 1
            if i.sex:
                if x == 1:
                    sql += " and "
                sql += "sex = \"" + i.sex + "\" "
                x = 1
            if i.age:
                if x == 1:
                    sql += " and "
                sql += "age = " + i.age + " "
                x = 1
            if i.dept:
                if x == 1:
                    sql += " and "
                sql += "sdept = \"" + i.dept + "\" "
                x = 1
            if sql:
                sql = sql0 + "where " + sql
            else:
                sql = sql0
            cur.execute(sql)
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "student"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "teacher":
            sql0 = "select * from teacher "
            sql = ""
            i = web.input(id='', name='', sex='', dept='')
            x = 0
            if i.id:
                if x == 1:
                    sql += " and "
                sql += "id = \"" + i.id + "\" "
                x = 1
            if i.name:
                if x == 1:
                    sql += " and "
                sql += "name = \"" + i.name + "\" "
                x = 1
            if i.sex:
                if x == 1:
                    sql += " and "
                sql += "sex = \"" + i.sex + "\" "
                x = 1
            if i.dept:
                if x == 1:
                    sql += " and "
                sql += "tdept = \"" + i.dept + "\" "
                x = 1
            if sql:
                sql = sql0 + "where " + sql
            else:
                sql = sql0
            cur.execute(sql)
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "teacher"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "course":
            sql0 = "select * from course "
            sql = ""
            i = web.input(id='', name='', credit='')
            x = 0
            if i.id:
                if x == 1:
                    sql += " and "
                sql += "id = \"" + i.id + "\" "
                x = 1
            if i.name:
                if x == 1:
                    sql += " and "
                sql += "name = \"" + i.name + "\" "
                x = 1
            if i.credit:
                if x == 1:
                    sql += " and "
                sql += "credit = " + i.credit + " "
                x = 1
            if sql:
                sql = sql0 + "where " + sql
            else:
                sql = sql0
            cur.execute(sql)
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "course"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "sc":
            sql0 = "select * from sc "
            sql = ""
            i = web.input(sid='', cid='', tid='')
            x = 0
            if i.sid:
                if x == 1:
                    sql += " and "
                sql += "student_id = \"" + i.sid + "\" "
                x = 1
            if i.cid:
                if x == 1:
                    sql += " and "
                sql += "course_id = \"" + i.cid + "\" "
                x = 1
            if i.tid:
                if x == 1:
                    sql += " and "
                sql += "teacher_id = \"" + i.tid + "\" "
                x = 1
            if sql:
                sql = sql0 + " where " + sql
            else:
                sql = sql0
            cur.execute(sql)
            rows = cur.fetchall()
            conn.close()
            all_pri = fetch_primary()
            table_name = "sc"
            return render.rows(table_name, all_pri, rows)
        elif i.table == "dept":
            sql0 = "select * from dept "
            sql = ""
            i = web.input(id='', name='')
            x = 0
            if i.id:
                if x == 1:
                    sql += " and "
                sql += "id = \"" + i.id + "\""
                x = 1
            if i.name:
                if x == 1:
                    sql += " and "
                sql += "name = \"" + i.name + "\""
                x = 1
            if sql:
                sql = sql0 + "where " + sql
            else:
                sql = sql0
            cur.execute(sql)
            rows = cur.fetchall()
            cur.close()
            all_pri = fetch_primary()
            table_name = "dept"
            return render.rows(table_name, all_pri, rows)
        else:
            raise web.seeother('/') 


def fetch_primary():
    all_pri = {}
    conn = sqlite3.connect('student.db')
    cur = conn.cursor()
    cur.execute("select * from student")
    all_pri["student"] = cur.fetchall()
    cur.execute("select * from teacher")
    all_pri["teacher"] = cur.fetchall()
    cur.execute("select * from course")
    all_pri["course"] = cur.fetchall()
    cur.execute("select * from dept")
    all_pri["dept"] = cur.fetchall()
    return all_pri



class Forbidden:
    def GET(self):
        return render.forbidden()

if __name__ == "__main__":
    app.run()
