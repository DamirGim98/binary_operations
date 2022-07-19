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
my_struct read_record_from_file(FILE *pfile, int index);
int get_records_count_in_file(FILE *pfile);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
void write_record_in_file(FILE *pfile, const my_struct *record_to_write, int index);
int compare_records_in_file(my_struct current, my_struct next);
void Printfile(FILE * fp, int lines);
void SortArray(FILE * fp, int lines);
void search_and_insert(FILE * pfile, int index);
int check_validity(my_struct input);

int main(void) {
    int flag = 1;
    FILE * fp = NULL;
    char name[50] = "../";
    char subname[30];
    scanf("%29s", subname);
    strcat(name, subname);
    // READING FILENAME
    fp = fopen(name, "rb+");
    if (fp == NULL) {
        flag = 0;
    } else {
        int lines = get_records_count_in_file(fp);
        if (lines != 0) {
            int key = 0;
            char c = 0;
            if (scanf("%d%c", &key, &c) == 2 && (c == '\n' || c == ' ')) {
                if (key == 0) {
                    Printfile(fp, lines);
                } else if (key == 1) {
                    SortArray(fp, lines);
                    Printfile(fp, lines);
                } else if (key == 2) {
                    search_and_insert(fp, lines);
                } else {
                    flag = 0;
                }
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    }
    if (flag == 0)
        printf("n/a");
    if (fp != NULL)
        fclose(fp);
    return 0;
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

my_struct read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(my_struct);
    fseek(pfile, offset, SEEK_SET);
    my_struct record;
    fread(&record, sizeof(my_struct), 1, pfile);
    rewind(pfile);
    return record;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(my_struct);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    my_struct record1 = read_record_from_file(pfile, record_index1);
    my_struct record2 = read_record_from_file(pfile, record_index2);
    if (compare_records_in_file(record1, record2)) {
        write_record_in_file(pfile, &record1, record_index2);
        write_record_in_file(pfile, &record2, record_index1);
    }
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
    cur_time->tm_mon = current.month - 1;
    cur_time->tm_mday = current.day;
    cur_time->tm_hour = current.hour;
    cur_time->tm_min = current.minute;
    cur_time->tm_sec = current.second;
    time_t kek = mktime(cur_time);

    cur_time->tm_year = next.year - 1900;
    cur_time->tm_mon = next.month - 1;
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

void SortArray(FILE * fp, int lines) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < lines - 1; j++) {
            swap_records_in_file(fp, j, j + 1);
        }
    }
}

void search_and_insert(FILE * pfile, int index) {
    int flag = 1;
    if (get_records_count_in_file(pfile) != 0) {
        my_struct input;
        scanf("%d %d %d %d %d %d %d %d", &input.year, &input.month, &input.day,
        &input.hour, &input.minute, &input.second, &input.status, &input.code);
        flag = check_validity(input);
        if (flag == 1) {
            write_record_in_file(pfile, &input, index);
            SortArray(pfile, get_records_count_in_file(pfile));
            Printfile(pfile, get_records_count_in_file(pfile));
        }
    } else {
        flag = 0;
    }
    if (flag == 0)
        printf("n/a");
}

int check_validity(my_struct input) {
    int validity = 1;
    if (input.second < 0 || input.second > 59)
        validity = 0;
    if (input.minute < 0 || input.minute > 59)
        validity = 0;
    if (input.hour < 0 || input.hour > 23)
        validity = 0;
    if (input.day < 1 || input.day > 31)
        validity = 0;
    if (input.month < 0 || input.month > 12)
        validity = 0;
    if (input.year < 1900 || input.year > 2100)
        validity = 0;
    if (input.status != 1 && input.status != 0)
        validity = 0;
    return validity;
}
