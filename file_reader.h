#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

typedef struct {
	FILE *file;
} file_reader_t;

typedef void (*file_reader_callback_t)(char *buffer, 
	                                   size_t buffer_size,
	                                   void *callback_context);

int file_reader_init(file_reader_t *self, const char *file_name);

int file_reader_uninit(file_reader_t *self);

int file_reader_for_each_buffer(file_reader_t *self,
	                    		file_reader_callback_t callback,
	                    		void *callback_context);

#endif