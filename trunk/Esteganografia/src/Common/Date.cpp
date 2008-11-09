#include "Date.h"

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
