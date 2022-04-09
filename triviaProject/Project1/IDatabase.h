#pragma once
#define DATA_BASE_FILE_NAME "triviaDB.sqlite"

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual void create() = 0;
	virtual bool doesUserExist() = 0;
	virtual bool doesPasswordMatch() = 0;
	virtual void addUser() = 0;
};