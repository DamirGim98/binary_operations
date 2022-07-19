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
my_struct read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const my_struct *record_to_write, int index);
void Printfile(FILE * fp, int lines);
int compare_records_in_file(my_struct current, my_struct next);

int main(void) {
    int flag = 1;
    FILE * fp = NULL;
    FILE * fp_new = NULL;
    char name[50] = "../";
    char subname[30];
    scanf("%29s", subname);
    strcat(name, subname);
    fp = fopen(name, "rb");
    fp_new = fopen("../datasets/temp___file", "wb+");
    if (fp == NULL) {
        flag = 0;
    } else {
        int lines = get_records_count_in_file(fp);
        my_struct start = {0};
        scanf("%d.%d.%d", &start.day, &start.month, &start.year);
        my_struct end = {0};
        scanf("%d.%d.%d", &end.day, &end.month, &end.year);
        int j = 0;
        int counter = 0;
        for (int i = 0; i < lines; i++) {
            my_struct temp = read_record_from_file(fp, i);
            if (compare_records_in_file(temp, start) == 0) {
                write_record_in_file(fp_new, &temp, j);
                j++;
            }
            if (compare_records_in_file(temp, end) == 1) {
                if (counter != 1) {
                    counter++;
                    continue;
                }
                write_record_in_file(fp_new, &temp, j);
                j++;
            }
        }
    }
    Printfile(fp_new, get_records_count_in_file(fp_new));
    if (flag == 0)
        printf("n/a");
    if (fp != NULL)
        fclose(fp);
    if (fp_new != NULL)
        fclose(fp_new);
    remove(name);
    rename("../datasets/temp___file", "../datasets/door_state_3");
    return 0;
}

my_struct read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(my_struct);
    my_struct record = {0};
    if (pfile != NULL) {
        fseek(pfile, offset, SEEK_SET);
        fread(&record, sizeof(my_struct), 1, pfile);
        rewind(pfile);
    }
    return record;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(my_struct);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    if (pfile != NULL) {
        fseek(pfile, 0, SEEK_END);
        size = ftell(pfile);
        rewind(pfile);
    }
    return size;
}

void write_record_in_file(FILE *pfile, const my_struct *record_to_write, int index) {
    int offset = index * sizeof(my_struct);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(my_struct), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}


int compare_records_in_file(my_struct current, my_struct next) {
    int value = 0;
    time_t now = time(NULL);
    struct tm *cur_time = localtime(&now);
    cur_time->tm_year = current.year - 1900;
    cur_time->tm_mon = current.month;
    cur_time->tm_mday = current.day;
    cur_time->tm_hour = current.hour;
    cur_time->tm_min = current.minute;
    cur_time->tm_sec = current.second;
    time_t kek = mktime(cur_time);

    cur_time->tm_year = next.year - 1900;
    cur_time->tm_mon = next.month;
    cur_time->tm_mday = next.day;
    cur_time->tm_hour = next.hour;
    cur_time->tm_min = next.minute;
    cur_time->tm_sec = next.second;
    time_t kek2 = mktime(cur_time);
    if (kek > kek2) {
        value = 1;
    }
    return value;
}

void Printfile(FILE * fp, int lines) {
    for (int i = 0; i < lines; i++) {
        my_struct kek = read_record_from_file(fp, i);
        printf("%d %d %d %d %d %d %d %d\n", kek.year, kek.month, kek.day,
        kek.hour, kek.minute, kek.second, kek.status, kek.code);
    }
}
