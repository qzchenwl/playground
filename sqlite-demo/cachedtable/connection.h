 /****************************************************************************
 **
 ** Copyright (C) 2004-2006 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://www.trolltech.com/products/qt/opensource.html
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://www.trolltech.com/products/qt/licensing.html or contact the
 ** sales department at sales@trolltech.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/
 
 #ifndef CONNECTION_H
 #define CONNECTION_H
 
 #include <QMessageBox>
 #include <QSqlDatabase>
 #include <QSqlError>
 #include <QSqlQuery>
 
 /*
     This file defines a helper function to open a connection to an
     in-memory SQLITE database and to create a test table.
 
     If you want to use another database, simply modify the code
     below. All the examples in this directory use this function to
     connect to a database.
 */
 static bool createConnection()
 {
     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName(":memory:");
     if (!db.open()) {
         QMessageBox::critical(0, qApp->tr("Cannot open database"),
             qApp->tr("Unable to establish a database connection.\n"
                      "This example needs SQLite support. Please read "
                      "the Qt SQL driver documentation for information how "
                      "to build it.\n\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);
         return false;
     }
 
     QSqlQuery query;
     query.exec("create table person (id int primary key, "
                "firstname varchar(20), lastname varchar(20))");
     query.exec("insert into person values(101, 'Danny', 'Young')");
     query.exec("insert into person values(102, 'Christine', 'Holand')");
     query.exec("insert into person values(103, 'Lars', 'Gordon')");
     query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
     query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");
     return true;
 }
 
 #endif