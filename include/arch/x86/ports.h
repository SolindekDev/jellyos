#pragma once

unsigned char inb(unsigned short port);

void outb(unsigned short port, unsigned char data); 

void outw(unsigned short port, unsigned short data);

unsigned short inw(unsigned short port);

unsigned int inportl(unsigned short port);

void outportl(unsigned short port, unsigned int data); 

void insl(unsigned int addr, unsigned int buffer, unsigned int count);

void insw(unsigned int addr, unsigned int buffer, unsigned int count);

void insb(unsigned int addr, unsigned int buffer, unsigned int count);

void outsl(unsigned int addr, unsigned int buffer, unsigned int count);

void outsw(unsigned int addr, unsigned int buffer, unsigned int count);

void outsb(unsigned int addr, unsigned int buffer, unsigned int count);