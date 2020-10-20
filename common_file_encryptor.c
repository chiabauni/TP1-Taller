#include <stdio.h>
#include "common_file_encryptor.h"
#define BUFF_SIZE 64
//-------------------------------------------------------------------------
int file_encryptor_init(file_encryptor_t *self, bool is_client, 
						char* method, char* key, const char* file_name) {
	cipher_init(&(self->cipher), method, key);
	if (is_client) {
		if (file_name != NULL) {
			self->fp = fopen(file_name, "rb");
			if (self->fp == NULL) {
				return -1;
			}
		} else {
			self->fp = stdin;
		}
		return 0;
	}
	return 0;
}

int file_encryptor_uninit(file_encryptor_t *self, bool is_client) {
	cipher_uninit(&(self->cipher));
	if (is_client) {
		if (self->fp != stdin) {
			if (fclose(self->fp)) {
				return -1;
			}
		}
		return 0;
	}
	return 0;
}

int file_encryptor_encrypt(file_encryptor_t *self, 
							file_encryptor_callback_t callback,
	                    	void *callback_ctx) {
	char buffer[BUFF_SIZE];
	while (!feof(self->fp)) {
		size_t result = fread(buffer, 1, BUFF_SIZE, self->fp);
		if (ferror(self->fp)) {
			return -1;
		}
		cipher_encode(&(self->cipher), buffer, result);
		callback(buffer, result, callback_ctx);
	}
	return 0;
}

int file_encryptor_decrypt(file_encryptor_t *self, 
							char* buffer, size_t bytes_received) {
	cipher_decode(&(self->cipher), buffer, bytes_received);
	buffer[bytes_received] = '\0';
	printf("%s", buffer);
	return 0;
}
