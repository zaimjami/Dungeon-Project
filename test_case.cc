#include <gtest/gtest.h>
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"
#include "hash.hpp"
#include <string>
#include <vector>
using namespace std;

class CrawlTest : public ::testing::Test {
protected:
    EnemyGraph* graph1;
    
    void SetUp() override {

            graph1 = new EnemyGraph();
        
    }
    
    void TearDown() override {
        delete graph1;
    }
};


TEST_F(CrawlTest, searchgraphHappyPath) {

        graph1->addVertex("fong");

        Vertex* result = graph1->searchVertex("fong");

        EXPECT_NE(result, nullptr);
        EXPECT_EQ(result->id, "fong");

}

TEST_F(CrawlTest, searchGraphErrorPath) {
    EXPECT_THROW(graph1->searchVertex("doesnt exist"), std::invalid_argument);


}

TEST_F(CrawlTest, AddDuplicateVertexEdgeCase) {
    graph1->addVertex("start");

    Vertex* duplicate = graph1->addVertex("start");

    EXPECT_EQ(duplicate, nullptr);
}




//  ********   ******* PRIORITY QUEUE TESTS   ***** ****** *******
//When testing priority Queue you may wish to update line 63 to specify the capacity of the queue in the constructor

class PriorityTest : public ::testing::Test {
protected:

    PriorityQ* priority1;
    
    void SetUp() override {
            priority1 = new PriorityQ();
        
    }
    
    void TearDown() override {
        delete priority1;
    }
};


TEST_F(PriorityTest, PriorityQueueInsertHappyPath) {
ItemInfo item;
    item.characterName = "Test Enemy";
    item.itemName = "Test Sword";
    item.damage = 100;
    item.comment = "Very sharp";

    priority1->insertElement(item);

    ItemInfo* result = priority1->peek();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->characterName, "Test Enemy");
    EXPECT_EQ(result->itemName, "Test Sword");
    EXPECT_EQ(result->damage, 100);
    EXPECT_EQ(result->comment, "Very sharp");
}


TEST_F(PriorityTest, PeekEmptyQueueReturnsNullptr) {
    ItemInfo* result = priority1->peek();

    EXPECT_EQ(result, nullptr);
}

TEST_F(PriorityTest, PopOnEmptyQueueDoesNotChangeState) {
    EXPECT_TRUE(priority1->isEmpty());

    priority1->pop();

    EXPECT_TRUE(priority1->isEmpty());
}
