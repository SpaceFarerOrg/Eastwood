#pragma once
#include <string>

#define SMALLSTRING_SIZE 16

class CSmallString
{
public:
	CSmallString();
	~CSmallString();

	bool operator==(const CSmallString& aCompare);
	bool operator!=(const CSmallString& aCompare);

	void operator=(const CSmallString& aSmallString);

	bool operator==(const char* aCharArray);
	bool operator!=(const char* aCharArray);

	void operator=(const char* aCharArray);

	CSmallString operator+(const CSmallString& aStringToAdd);
	void operator+=(const CSmallString& aStringToAdd);

	CSmallString operator+(const char* aCharArray);
	void operator+=(const char* aCharArray);

	std::string ToString();

private:
	char myData[SMALLSTRING_SIZE];
	unsigned int myUsedSize;
};

