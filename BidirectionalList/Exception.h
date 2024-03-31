#pragma once
#include <iostream>
#include <string.h>
#define Something -1

class SetException {
	public:
		char error_message_[128];
		int error_code_;

	public:
		SetException(int code, const char* statement) {
			SetMessage(statement);
			SetCode(code);
		}

		void SetCode(int code) {
			error_code_ = code;
		}
		void SetMessage(const char* statement) {
			strncpy(error_message_, statement, 127);    
		}

		int GetErrorCode() {
			return error_code_; 
		}
		const char *GetErrorMessage() {
			return error_message_;
		}
};
