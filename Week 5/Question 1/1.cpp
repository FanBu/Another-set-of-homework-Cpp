class MyString :public string {
public:
	MyString() : string() {};
	MyString(const char* str) : string(str) {};
	MyString(const string &str) : string(str) {};
	MyString operator () (int start, int len) {
		return this->substr(start, len);
	}
};