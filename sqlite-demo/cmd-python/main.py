#!/usr/bin/python
import sqlite3

conn = sqlite3.connect('example')
c = conn.cursor()
c.execute('''insert into stocks values('2006-01-15','BuoY', 'asdf',100,35.14)''')
conn.commit()
rec = c.execute('''select * from stocks''')
print c.fetchall()

