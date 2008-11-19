#ifndef DATE_H_
#define DATE_H_

#include <string>

class Date{

	public:

		Date();
		Date(unsigned int  year,unsigned int month,unsigned int day,unsigned int hour,
				unsigned int min,unsigned int seg);
		~Date();

		int operator==(Date d);

		unsigned int getYear() const;
		unsigned int getMonth() const;
		unsigned int getDay() const;
		unsigned int getHour() const;
		unsigned int getMin() const;
		unsigned int getSeg() const;
		unsigned int getSize() const;
		std::string toString() const;
		/**
		 * Devuelve la fecha del archivo file
		 */
		static Date getDate(const char* file);

	private:
		unsigned int year;
		unsigned int month;
		unsigned int day;
		unsigned int hour;
		unsigned int min;
		unsigned int seg;
};

#endif /* DATE_H_ */
