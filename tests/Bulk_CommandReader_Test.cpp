#include "gmock/gmock.h"
#include "../src/Bulk_CommandReader.h"
#include <sstream>

using namespace testing;

class ACommandReader_WithBlockSizeEq3 : public Test {
public:
    std::stringstream input;
    std::unique_ptr<CommandReader> commandReader;

    void SetUp() {
        commandReader = std::make_unique<CommandReader>(3, input);
    }
};

TEST_F(ACommandReader_WithBlockSizeEq3, ReadsFirstCommandFromSream) {
    input << "cmd1\n"
             "cmd2\n"
             "cmd3\n";

    ASSERT_THAT(commandReader->ReadCommand(), Eq("cmd1"));
}

TEST_F(ACommandReader_WithBlockSizeEq3, ReadsCommandsBlockWithSpecifiedSizeFromSream) {
    input << "cmd1\n"
             "cmd2\n"
             "cmd3\n"
             "cmd4\n"
             "cmd5\n";

    commands_block_t expected = {
            "cmd1", "cmd2", "cmd3"
    };

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}

TEST_F(ACommandReader_WithBlockSizeEq3, IgnoresLineBreaks) {
    input << "cmd1\n"
             "cmd2\n"
             "\n"
             "cmd3\n"
             "cmd4\n"
             "cmd5\n";

    commands_block_t expected = {
            "cmd1", "cmd2"
    };

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}