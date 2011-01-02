#include <stdio.h>
#include <sqlite3.h>
int main(int argc, const char *argv[])
{
    sqlite3 *pDB = NULL;
    char *errMsg = NULL;
    int rc = sqlite3_open("test.db", &pDB);
    if(rc) {
        printf("%s %s %s\n", "Open DB", "test.db", "failed");
        return 1;
    }
    printf("create DB successful!\n");
    rc = sqlite3_exec(pDB,"CREATE TABLE chn2eng(chinese TEXT, english TEXT)", 0, 0, &errMsg);
    if (rc == SQLITE_OK) 
        printf("create table chn_to_eng ok!\n");
    else
        printf("%s\n", errMsg);
    return 0;
}
