#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct info_s {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} my_struct;

int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
int search(FILE *pfile, my_struct current, int lines);
my_struct read_record_from_file(FILE *pfile, int index);

int main(void) {
    int flag = 1;
    FILE * fp = NULL;
    char name[50] = "../";
    char subname[30];
    scanf("%29s", subname);
    strcat(name, subname);
    // READING FILENAME
    fp = fopen(name, "rb");
    if (fp == NULL) {
        flag = 0;
    } else {
        int lines = get_records_count_in_file(fp);
        my_struct kek = {0};
        scanf("%d.%d.%d", &kek.day, &kek.month, &kek.year);
        int a = search(fp, kek, lines);
        if (a != -1)
            printf("%d", a);
        if (a == -1)
            flag = 0;
    }
    if (flag == 0)
        printf("n/a");
    if (fp != NULL)
        fclose(fp);
    return 0;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(my_struct);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int search(FILE *pfile, my_struct current, int lines) {
    int value = -1;
    my_struct kek;
    for (int i = 0; i < lines; i++) {
        kek = read_record_from_file(pfile, i);
        if (kek.day == current.day && kek.month == current.month && kek.year == current.year) {
            value = kek.code;
            break;
        }
    }
    return value;
}

my_struct read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(my_struct);
    fseek(pfile, offset, SEEK_SET);
    my_struct record;
    fread(&record, sizeof(my_struct), 1, pfile);
    rewind(pfile);
    return record;
}
