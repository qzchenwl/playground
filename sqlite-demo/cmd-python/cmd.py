#!/usr/bin/python
import sys,sqlite3

if __name__ == '__main__':
    conn = sqlite3.connect('student.db')
    cur = conn.cursor()
    cur.execute(sys.argv[1])
    rows = cur.fetchall()
    conn.commit()
    for row in rows:
        for item in row:
            print item,'\t',
        print ''
