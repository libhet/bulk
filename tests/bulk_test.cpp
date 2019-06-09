//#include "gmock/gmock.h"
//#include "../src/bulk.h"
//#include <sstream>
//
//using namespace testing;
//
//TEST(ABulk, CommandsReadLineByLineFromStdIn) {
//    Bulk bulk;
//    std::stringstream ss;
//    ss << "cmd1\ncmd2\n\ncmd3";
//
//    bulk.readCommands(ss);
//
//    std::list<std::string> expected = {
//            "cmd1", "cmd2"
//    };
//
//    ASSERT_THAT(bulk.commands(), Eq(expected));
//}
