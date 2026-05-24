#include "unity.h"

#include "morse.h"

void setUp(void)    {}
void tearDown(void) {}

void test_encode_returns_null_for_space(void) {
    TEST_ASSERT_NULL(morse_encode(' '));
}

void test_encode_returns_null_for_digit(void) {
    TEST_ASSERT_NULL(morse_encode('5'));
}

void test_encode_returns_null_for_non_alpha(void) {
    TEST_ASSERT_NULL(morse_encode('!'));
}

void test_encode_uppercase_a(void) {
    TEST_ASSERT_EQUAL_STRING(".-", morse_encode('A'));
}

void test_encode_uppercase_z(void) {
    TEST_ASSERT_EQUAL_STRING("--..", morse_encode('Z'));
}

void test_encode_uppercase_s(void) {
    TEST_ASSERT_EQUAL_STRING("...", morse_encode('S'));
}

void test_encode_uppercase_o(void) {
    TEST_ASSERT_EQUAL_STRING("---", morse_encode('O'));
}

void test_encode_uppercase_e(void) {
    TEST_ASSERT_EQUAL_STRING(".", morse_encode('E'));
}

void test_encode_lowercase_maps_same_as_uppercase(void) {
    for (char c = 'a'; c <= 'z'; c++) {
        char upper = (char)(c - 'a' + 'A');
        TEST_ASSERT_EQUAL_STRING(morse_encode(upper), morse_encode(c));
    }
}

void test_encode_all_letters_non_null(void) {
    for (char c = 'A'; c <= 'Z'; c++) {
        TEST_ASSERT_NOT_NULL(morse_encode(c));
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_encode_returns_null_for_space);
    RUN_TEST(test_encode_returns_null_for_digit);
    RUN_TEST(test_encode_returns_null_for_non_alpha);
    RUN_TEST(test_encode_uppercase_a);
    RUN_TEST(test_encode_uppercase_z);
    RUN_TEST(test_encode_uppercase_s);
    RUN_TEST(test_encode_uppercase_o);
    RUN_TEST(test_encode_uppercase_e);
    RUN_TEST(test_encode_lowercase_maps_same_as_uppercase);
    RUN_TEST(test_encode_all_letters_non_null);
    return UNITY_END();
}
