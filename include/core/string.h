#pragma once

char to_uppercase(char c);

char to_lowercase(char c);

int strlen(const char* str);

void reverse(char* str);

void itoa(int num, char* str, int base);

int strcmp(const char *s1, char *s2);

void append_str(char* str, char c);

void pop_last_str(char* str);

char* strcpy(char* dest, const char* src);

char* strtok(char* str, const char* delim);

char* strpbrk(const char* str, const char* accept);

char* strdup(const char* str);

char* strrchr(const char* str, int c);