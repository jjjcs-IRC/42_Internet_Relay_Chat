#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <string>
# include <vector>

class ScalarConverter
{
	private:
		ScalarConverter( void );
		ScalarConverter( ScalarConverter const &copy );
		~ScalarConverter( void );
		ScalarConverter	&operator=( ScalarConverter const &copy );
	protected:
	public:
		char	convert( std::string const &str, char );
		int		convert( std::string const &str, int );
		float	convert( std::string const &str, float );
		double	convert( std::string const &str, double );
};

#endif