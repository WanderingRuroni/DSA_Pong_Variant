#ifndef STRING_H
#define STRING_H


#include <Shared/Types.h>

#include <sstream>


#define STRINGIFY String::toString


/**
 * Utility functions for working with strings.
 *
 * @author Peter B. Tummillo
 */
namespace String
{

	/**
	 * Converts any type to a string using its string stream operator overload.
	 *
	 * @param Non-string value.
	 * @return A string representing that value.
	 */
	template<typename T>
	inline string toString(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	/**
	 * Converts any type to a wide string (Unicode) using its wide string stream operator overload.
	 *
	 * @param Non-string value.
	 * @return A wide string representing that value.
	 */
	template<typename T>
	inline wstring toWideString(const T& value)
	{
		std::wostringstream woss;
		woss << value;
		return woss.str();
	}

	/**
	 * Converts an 8-bit integer (byte) to its binary representation.
	 *
	 * @param 8-bit integer (byte).
	 * @return String holding a binary numeral.
	 */
	inline string toBinary(BYTE integer)
	{
		string binaryStr;

		// Resizes the string to be 9 characters long
		// (8 bits, 1 null)
		binaryStr.resize(9);

		// Null-terminate
		binaryStr[8] = '\0';

		// For least-significant to most-significant
		for (int i = 7; i >= 0; --i)
		{
			// Divide integer by 2; the remainder is the value of the bit
			binaryStr[i] = (integer % 2 == 1) ? '1' : '0';
			integer /= 2;
		}

		return binaryStr;
	}

	/*
	 * Splits a string up into individual tokens.
	 *
	 * @param tokens List of string tokens.
	 * @param str String to split.
	 * @param splitOn Character to split the string on.
	 */
	inline void split(StringList& tokens, string str, char splitOn)
	{
		tokens.clear();

		// Find all instances of the split character, then add that chunk of the string to a list
		UINT i = 0;
		UINT last = 0;
		UINT length = str.size();
		for(; i < length; ++i)
		{
			if(str[i] == splitOn)
			{
				if(i > last) 
					tokens.push_back( str.substr(last, i - last) );
				
				last = i + 1;
			}
		}

		// Add the piece of the string after the last split character
		if(i > last) 
			tokens.push_back( str.substr(last) );
	}

}; // String


#endif // STRING_H
