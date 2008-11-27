#include "Date.h"
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "StrToken.h"

using std::cout;
Date::Date(unsigned int  year,unsigned int month,unsigned int day,unsigned int hour,
		unsigned int min,unsigned int seg){
	this->year=year;
	this->month=month;
	this->day=day;
	this->hour=hour;
	this->min=min;
	this->seg=seg;
}

Date::Date(){}

Date::~Date(){}

int Date::operator==(Date d){
	return ((this->year==d.year)&&(this->month==d.month)&&(this->day==d.day)&&
			(this->hour==d.hour)&&(this->min==d.min)&&(this->seg==d.seg));
}

unsigned int Date::getYear() const{return this->year;}
unsigned int Date::getMonth() const{return this->month;}
unsigned int Date::getDay() const{return this->day;}
unsigned int Date::getHour() const{return this->hour;}
unsigned int Date::getMin() const{return this->min;}
unsigned int Date::getSeg() const{return this->seg;}
unsigned int Date::getSize() const{return (sizeof(unsigned int)*6);}
string Date::toString() const{
	string year=StrToken::intToString(this->year);
	string month=StrToken::intToString(this->month);
	string day=StrToken::intToString(this->day);
	string hour=StrToken::intToString(this->hour);
	string min=StrToken::intToString(this->min);
	string seg=StrToken::intToString(this->seg);
	string ans=year;
	ans=ans.append("/");
	ans=ans.append(month.c_str());
	ans=ans.append("/");
	ans=ans.append(day.c_str());
	ans=ans.append("/");
	ans=ans.append(hour.c_str());
	ans=ans.append("/");
	ans=ans.append(min.c_str());
	ans=ans.append("/");
	ans=ans.append(seg.c_str());
	ans=ans.append("/");
	return ans;
}

Date Date::getDate(const char* file){
	//Extraigo fecha
	struct tm* clock;				// create a time structure
	struct stat attrib;			// create a file attribute structure
	stat(file, &attrib);		// get the attributes
	clock = gmtime(&(attrib.st_mtime));	// Get the last modified time and put it into the time structure
	Date date(clock->tm_year,clock->tm_mon,clock->tm_mday,clock->tm_hour,clock->tm_min,clock->tm_sec);
	return date;
}
