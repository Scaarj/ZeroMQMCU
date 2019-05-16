#include <Arduino.h>
#include <unity.h>
#include <map.h>

void test_tree_on_add(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    TEST_ASSERT_EQUAL(1, test_map.size());
}

void test_tree_on_remove(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    test_map.insert(15, 10);
    test_map.remove(15);
    TEST_ASSERT_EQUAL(1, test_map.size());
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_tree_on_add);
    RUN_TEST(test_tree_on_remove);
    UNITY_END();
}

void loop() {

}
