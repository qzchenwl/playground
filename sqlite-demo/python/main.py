#!/usr/bin/python
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from Ui_Dialog import *
import sys
class DBDialog(QDialog, Ui_Dialog):
    def __init__(self, parent = None):
        QDialog.__init__(self)
        self.setupUi(self)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    dialog = DBDialog()
    dialog.show()
    app.exec_()
