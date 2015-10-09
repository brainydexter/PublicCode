/* 
* @Author: Priyank Jain
* @Date:   2015-09-17 00:02:36
* @Last Modified by:   Priyank Jain
* @Last Modified time: 2015-10-08 21:06:57
*/

#include "utils.h"

std::string convertBoolToString(bool value)
{
    return value ? "True" : "False" ;
}

std::string convertStatusToString(const STATUS& status)
{
	static std::string statusMsgs[] = 
	{
		"NO_ERR",
		"ERR_NULL_PTR",
		"ERR_OUT_OF_BOUNDS"
	};

	return statusMsgs[status];
}