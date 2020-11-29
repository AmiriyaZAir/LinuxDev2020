#include <stdio.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gmodule.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAXCHAR 80

void reformat_string(char *src, char *dst) {
    for (; *src; ++src)
        if (!ispunct((unsigned char) *src))
            *dst++ = tolower((unsigned char) *src);
    *dst = 0;
}

gboolean finder(gpointer key, gpointer value, gpointer user_data) {
    return !g_strcmp0(key, user_data);
}

void iterator(gpointer key, gpointer map) {
    if (!key) return;
    if (!g_strcmp0(key, "")) return;

    printf("%d : %s\n", GPOINTER_TO_INT(g_hash_table_find(map, (GHRFunc)finder, key)), key);
}

gint compare_func(gconstpointer x, gconstpointer y, gpointer hash) {
    gpointer x1 = g_hash_table_find(hash, (GHRFunc)finder, (gpointer)x);
    gpointer y1 = g_hash_table_find(hash, (GHRFunc)finder, (gpointer)y);
    return GPOINTER_TO_INT(y1) - GPOINTER_TO_INT(x1);
}

int main() {
    FILE *fp;
    int i;
    char str[MAXCHAR + 1];
    char dst[MAXCHAR + 1];
    char* filename = "text.txt";

    gchar ** gline;
    gchar * key;
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);
    int * value;
    GSList * result = g_slist_alloc();

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    while (fgets(str, MAXCHAR + 1, fp)) {
        reformat_string(str, dst);
        gline = g_strsplit_set(dst, " \n", -1);
        int len = g_strv_length(gline);

        for (i = 0; i < len; i++){
            key = g_strdup(gline[i]);

            if (value = g_hash_table_lookup(hash, key)){
                g_hash_table_replace(hash, key, GINT_TO_POINTER(GPOINTER_TO_INT(value) + 1));
            } else {
                g_hash_table_insert(hash, key, GINT_TO_POINTER(1));
                result = g_slist_append(result, key);
            }
        }
        g_strfreev (gline);
    }
    fclose(fp);

    result = g_slist_sort_with_data(result, (GCompareDataFunc)compare_func, hash);
    
    g_slist_foreach(result, iterator, hash);

    g_slist_free(result);
    g_hash_table_destroy(hash);

    return 0;
}
