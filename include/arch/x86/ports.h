#pragma once

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data); 
void outw(unsigned short port, unsigned short data);

unsigned int inportl(unsigned short port);
void outportl(unsigned short port, unsigned int data); 