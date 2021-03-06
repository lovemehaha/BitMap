// Bitmap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

#define BITMAP_OK       1
#define BITMAP_ERROR    0

typedef struct bitmap_s
{
	int bits;
	int zero_count;
	int one_count;
	unsigned char buf[];
}bitmap_t;

static bitmap_t *bitmap;
bitmap_t *bitmap_init(int size);
int bitmap_set(bitmap_t *bitmap, int index, int flag);
void bitmap_free(bitmap_t *bitmap);
int bitmap_get(bitmap_t *bitmap, int index);
bitmap_t *bitmap_init(int size)
{
	int nbytes=size / 8;

	if (size % 8 != 0)
		nbytes += 1;
	bitmap = static_cast<bitmap_t*>(malloc(sizeof(bitmap_t) + sizeof(char)*nbytes));
	if (bitmap == nullptr)
		return nullptr;
	bitmap->bits = size;
	memset(bitmap->buf, 0, nbytes);
	return bitmap;
}

int bitmap_get(bitmap_t *bitmap, int index)
{

	if (bitmap == nullptr || bitmap->bits < index)
		return BITMAP_ERROR;
	int bytes = index / 8;
	int offset = index % 8;
	unsigned char* p = bitmap->buf + bytes;
	if ((*p & 0x01 << (8 - offset - 1))==0 )
		return 0;
	else 
		return 1;
	
}

int bitmap_set(bitmap_t *bitmap, int index, int flag)
{

	if (bitmap == nullptr || bitmap->bits<index)
		return BITMAP_ERROR;
	int nbytes = index / 8;
	int offset = 0;
	if (index % 8 != 0)
		offset += index % 8;
	unsigned char* p = bitmap->buf + nbytes;
	if (flag == 0)
	{
		
		*p &= ~(0x01 << (8 - offset - 1));
	}
	
	else if (flag == 1)
	{
		
		*p |= 0x01 << (8 - offset - 1);
	}
	
	return BITMAP_OK;
}
void bitmap_free(bitmap_t *bitmap)
{
	free(bitmap);
}

int main()
{
	int size = 16;
	bitmap_t *b = bitmap_init(size);
	for (int i = 0; i < size; i++)
		printf("%d=%d  ", i, bitmap_get(b, i));
	printf("\n");


	for (int i = 0; i < size; i++)
	    bitmap_set(b, i, 1);
	for (int i = 0; i < size; i++)
		printf("%d=%d  ", i, bitmap_get(b, i));
	printf("\n");

	for (int i = 0; i < size; i++)
		bitmap_set(b, i, 0);
	for (int i = 0; i < size; i++)
		printf("%d=%d  ", i, bitmap_get(b, i));
	printf("\n");

	
	return 0;
}
