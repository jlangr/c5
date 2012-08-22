#include "gmock/gmock.h"

#include "stringutil.h"

using namespace std;
using namespace testing;
using stringutil::ticToQuote;

TEST(StringUtilTicToQuote, ReplacesTicWithDoubleQuote) {
   ASSERT_THAT(ticToQuote("abc'def"), Eq("abc\"def"));
}

TEST(StringUtilTicToQuote, ReplacesAllTicsWithQuotes) {
   ASSERT_THAT(ticToQuote("'abc'def'"), Eq("\"abc\"def\""));
}

TEST(StringUtilTicToQuote, AnswersSameStringWhenNoTicFound) {
   ASSERT_THAT(ticToQuote("abcdef"), Eq("abcdef"));
}
