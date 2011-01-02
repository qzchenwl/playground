CREATE TABLE demo(id INT, info TEXT);
CREATE TABLE "Teacher" (
    "ID" TEXT NOT NULL PRIMARY KEY,
    "Name" TEXT NOT NULL,
    "Sex" TEXT NOT NULL,
    "Tdept" TEXT
);
;
CREATE TABLE "Course" (
    "ID" TEXT NOT NULL PRIMARY KEY,
    "Name" TEXT NOT NULL,
    "Credit" INTEGER NOT NULL
);
;
CREATE TABLE "Dept" (
    "ID" TEXT NOT NULL PRIMARY KEY,
    "Name" TEXT NOT NULL,
    "Description" TEXT
);
;
CREATE TABLE "SC" (
    "Student_ID" TEXT NOT NULL,
    "Course_ID" TEXT NOT NULL,
    "Teacher_ID" TEXT NOT NULL,
    "Score" INTEGER,
    FOREIGN KEY("Student_ID") REFERENCES Student("ID"),
    FOREIGN KEY("Course_ID") REFERENCES Course("ID"),
    FOREIGN KEY("Teacher_ID") REFERENCES Teacher("ID")
);
CREATE TABLE "Student" (
    "ID" TEXT NOT NULL PRIMARY KEY,
    "Name" TEXT NOT NULL,
    "Sex" TEXT NOT NULL,
    "Age" INTEGER NOT NULL,
    "Sdept" TEXT,
    "Class" TEXT,
    FOREIGN KEY("Sdept") REFERENCES Dept("ID")
);
;
