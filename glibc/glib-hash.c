#include <glib.h>
#include <stdio.h>

void print_key_value(gpointer key, gpointer value, gpointer user_data);
void display_hash_table(GHashTable *table);
void free_key(gpointer data);
void free_value(gpointer value);

void print_key_value(gpointer key, gpointer value, gpointer user_data)
{
    printf("%s --> %s\n", key, value);
}

void display_hash_table(GHashTable *table)
{
    g_hash_table_foreach(table, print_key_value, NULL);
}

void free_key(gpointer data)
{
    printf("Free key: %s\n", data);
    free(data);
}

void free_value(gpointer data)
{
    printf("Free value: %s\n", data);
    free(data);
}

int main(int argc, const char *argv[])
{
    GHashTable *table = NULL;
    table = g_hash_table_new(g_str_hash, g_str_equal);

    return 0;
}
