#include "testUtils.h"

#include "utils.h"

TEST(ConversionTest, ConvertBoolToString)
{
	EXPECT_STRCASEEQ("TRUE", convertBoolToString(true));
}