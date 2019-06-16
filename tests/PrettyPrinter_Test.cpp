#include "gmock/gmock.h"
#include "../src/PrettyPrinter.h"
#include <sstream>
#include <list>

using namespace testing;

TEST(APrintCollection, PrintsCollectionWithDelimeter) {
    std::stringstream output;

    std::list<int> collection = {1,2,3};

    print_collection(collection, ", ", output);

    ASSERT_THAT(output.str(), Eq("1, 2, 3"));
}

TEST(APrintCollection, DoesntPrintEmptyCollection) {
    std::stringstream output;

    std::list<int> collection = {};

    print_collection(collection, ", ", output);

    ASSERT_THAT(output.str(), Eq(""));
}