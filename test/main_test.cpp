#include <Arduino.h>
#include <unity.h>
#include <map.h>
#include <list.h>

//  MAP UNIT TEST
void test_map_on_add(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    TEST_ASSERT_EQUAL(1, test_map.size());
}

void test_map_on_add_two_simillar(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    test_map.insert(5, 10);
    TEST_ASSERT_EQUAL(1, test_map.size());
}

void test_map_on_remove(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    test_map.insert(15, 10);
    test_map.remove(15);
    TEST_ASSERT_EQUAL(1, test_map.size());
}

void test_map_on_remove_two_simillar(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    test_map.insert(15, 10);
    test_map.remove(15);
    test_map.remove(15);
    TEST_ASSERT_EQUAL(1, test_map.size());
}

void test_map_on_remove_all(void) {
    my_map<int, int> test_map;
    test_map.insert(15, 10);
    test_map.remove(15);
    TEST_ASSERT_EQUAL(0, test_map.size());
}

void test_map_on_remove_empty(void) {
    my_map<int, int> test_map;
    test_map.remove(15);
    TEST_ASSERT_EQUAL(0, test_map.size());
}

void test_map_on_contains_key(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    TEST_ASSERT_TRUE(test_map.contains(5));
}

void test_map_on_taking_value_by_key(void) {
    my_map<int, int> test_map;
    test_map.insert(5, 10);
    TEST_ASSERT_EQUAL(10, test_map.value(5));
}
//  END MAP UNIT TEST

//  LIST UNIT TEST
void test_list_on_add(void) {
    my_list<int> test_list;
    test_list.append(5);
    TEST_ASSERT_EQUAL(1, test_list.size());
}

void test_list_on_add_two_simillar(void) {
    my_list<int> test_list;
    test_list.append(5);
    test_list.append(5);
    TEST_ASSERT_EQUAL(2, test_list.size());
}

void test_list_on_remove(void) {
    my_list<int> test_list;
    test_list.append(15);
    test_list.remove(15);
    TEST_ASSERT_EQUAL(0, test_list.size());
}

void test_list_on_remove_two_simillar(void) {
    my_list<int> test_list;
    test_list.append(5);
    test_list.append(15);
    test_list.remove(15);
    test_list.remove(15);
    TEST_ASSERT_EQUAL(1, test_list.size());
}

void test_list_on_remove_all(void) {
    my_list<int> test_list;
    test_list.append(15);
    test_list.remove(15);
    TEST_ASSERT_EQUAL(0, test_list.size());
}

void test_list_on_remove_empty(void) {
    my_list<int> test_list;
    test_list.remove(15);
    TEST_ASSERT_EQUAL(0, test_list.size());
}

void test_list_on_contains_key(void) {
    my_list<int> test_list;
    test_list.append(5);
    TEST_ASSERT_TRUE(test_list.contains(5));
}

//  END LIST UNIT TEST

void unit_testing()
{
    RUN_TEST(test_map_on_add);
    RUN_TEST(test_map_on_add_two_simillar);
    RUN_TEST(test_map_on_remove);
    RUN_TEST(test_map_on_remove_two_simillar);
    RUN_TEST(test_map_on_remove_all);
    RUN_TEST(test_map_on_remove_empty);
    RUN_TEST(test_map_on_contains_key);
    RUN_TEST(test_map_on_taking_value_by_key);

    RUN_TEST(test_list_on_add);
    RUN_TEST(test_list_on_add_two_simillar);
    RUN_TEST(test_list_on_remove);
    RUN_TEST(test_list_on_remove_two_simillar);
    RUN_TEST(test_list_on_remove_all);
    RUN_TEST(test_list_on_remove_empty);
    RUN_TEST(test_list_on_contains_key);
}

void testing_map_on_add_4_and_remove()
{
    my_map<int, int> map_test;
    map_test.insert(3, 10);
    map_test.insert(2, 10);
    map_test.insert(1, 10);
    map_test.insert(0, 10);
    TEST_ASSERT_EQUAL_MESSAGE(4, map_test.size(), "add 4 nodes to map");
    for(int i = 0; i < 4; i++) {
        TEST_ASSERT_TRUE(map_test.contains(i));
    }
    map_test.remove(2);
    map_test.remove(1);
    map_test.remove(0);
    map_test.remove(3);
    TEST_ASSERT_EQUAL_MESSAGE(0, map_test.size(), "remove 4 nodes from root");
}

void testing_list_on_add_4_and_remove()
{
    my_list<int> list_test;
    list_test.append(3);
    list_test.append(2);
    list_test.append(1);
    list_test.append(0);
    TEST_ASSERT_EQUAL_MESSAGE(4, list_test.size(), "add 4 nodes to list");
    for(int i = 0; i < 4; i++) {
        TEST_ASSERT_TRUE(list_test.contains(i));
    }
    list_test.remove(3);
    list_test.remove(2);
    list_test.remove(1);
    list_test.remove(0);
    TEST_ASSERT_EQUAL_MESSAGE(0, list_test.size(), "remove 4 nodes from head");
}

void integration_testing()
{
    RUN_TEST(testing_map_on_add_4_and_remove);
    RUN_TEST(testing_list_on_add_4_and_remove);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    unit_testing();
    integration_testing();
    UNITY_END();
}

void loop() {

}
