#include "gmock/gmock.h"

using namespace ::testing;

class DifficultCollaborator {
public:
// START:interface
   virtual bool calculate(int* result) 
// END:interface
   {
      throw 1;
   }
};

class Target {
public:
   int execute(DifficultCollaborator* calculator) {
      int i;
      if (!calculator->calculate(&i))
         return 0;
      return i;
   }
};

class DifficultCollaboratorMock: public DifficultCollaborator {
public:
   MOCK_METHOD1(calculate, bool(int*));
};

TEST(ATarget, ReturnsAnAmountWhenCalculatePasses) {
// START:test
   DifficultCollaboratorMock difficult;
   Target calc;
   EXPECT_CALL(difficult, calculate(_))
// START_HIGHLIGHT
      .WillOnce(DoAll(
         SetArgPointee<0>(3),
         Return(true)));
// END_HIGHLIGHT

   auto result = calc.execute(&difficult);

   ASSERT_THAT(result, Eq(3));
// END:test
}
