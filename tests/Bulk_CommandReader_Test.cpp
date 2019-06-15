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

TEST_F(ACommandReader_WithBlockSizeEq3, BlockCompletesForciblyWhenDataEnds) {
    input << "cmd1\n"
             "cmd2\n"
             "cmd3\n"
             "cmd4\n"
             "cmd5\n";

    // Reading "cmd1 cmd2 cmd3"
    commandReader->ReadCommandsBlock();

    commands_block_t expected = {
            "cmd4", "cmd5"
    };

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}

TEST_F(ACommandReader_WithBlockSizeEq3, PreviousBlockForciblyEndsAfterCurlyBrace) {
    input << "cmd1\n"
             "cmd2\n"
             "{\n"
             "cmd3\n"
             "cmd4\n"
             "cmd5\n";

    commands_block_t expected = {
            "cmd1", "cmd2"
    };

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}

TEST_F(ACommandReader_WithBlockSizeEq3, ReadsBlockOfOtherSizeInCurlyBraces) {
    input << "cmd1\n"
             "{\n"
             "cmd2\n"
             "cmd3\n"
             "cmd4\n"
             "cmd5\n"
             "}\n";

    // Reading "cmd1"
    commandReader->ReadCommandsBlock();

    commands_block_t expected = {
            "cmd2", "cmd3", "cmd4", "cmd5"
    };

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}

TEST_F(ACommandReader_WithBlockSizeEq3, IgnoresNestedBlocks) {
    input << "cmd1\n"
             "{\n"
             "cmd2\n"
             "{\n"
             "cmd3\n"
             "cmd4\n"
             "}\n"
             "cmd5\n"
             "}\n";

    // Reading "cmd1"
    commandReader->ReadCommandsBlock();

    commands_block_t expected = {
            "cmd2", "cmd3", "cmd4", "cmd5"
    };

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}

TEST_F(ACommandReader_WithBlockSizeEq3, IgnoresBlockIfDataEndsInIt) {
    input << "cmd1\n"
             "cmd2\n"
             "cmd3\n"
             "{\n"
             "cmd4\n"
             "cmd5\n"
             "cmd6\n"
             "cmd7\n";

    // Reading "cmd1 cmd2 cmd3"
    commandReader->ReadCommandsBlock();

    commands_block_t expected = {};

    ASSERT_THAT(commandReader->ReadCommandsBlock(), Eq(expected));
}