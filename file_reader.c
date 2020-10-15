#include <stdio.h>
#include "file_reader.h"

#define BUFF_SIZE 64

int file_reader_init(file_reader_t *self, const char *file_name) {
	if(file_name != NULL) {
		self->file = fopen(file_name, "rb"); //agergar casos en el que fopen devuelve error
	} else {
		self->file = stdin;
	}
	return 0;

}

int file_reader_uninit(file_reader_t *self) {
	if (self->file != stdin) {
		fclose(self->file);//agergar casos en el que fclose devuelve error
	}
	return 0;
}

int file_reader_for_each_buffer(file_reader_t *self,
	                    		file_reader_callback_t callback,
	                    		void *callback_context) {
	char buffer[BUFF_SIZE];

	while (!feof(self->file)) {
		size_t result = fread(buffer, 1, BUFF_SIZE, self->file);//agergar casos en el que fread devuelve error

		callback(buffer, result, callback_context);
	}
	return 0;
}