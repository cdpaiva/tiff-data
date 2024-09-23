#include "../src/tiff_data.h"
#include "../unity/unity.h"

char* TIRE_LE_IMG_PATH = "./images/tire.tif";
char* TIRE_BE_IMG_PATH = "./images/tireBE.tif";
char* PNG_IMG_PATH = "./images/mountain.png";

void setUp()
{
}

void tearDown()
{
}

static void test_should_return_BE_for_big_endian_files()
{
    FILE *fptr = open_file(TIRE_BE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_endianess(fptr), BE);
    close_file(fptr);
}

static void test_should_return_LE_for_little_endian_files()
{
    FILE *fptr = open_file(TIRE_LE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_endianess(fptr), LE);
    close_file(fptr);
}

static void test_should_identify_valid_magic_number()
{
    FILE *fptr = open_file(TIRE_LE_IMG_PATH);
    TEST_ASSERT_EQUAL(is_valid_magic_number(fptr, LE), 1);
    close_file(fptr);
}

static void test_should_identify_invalid_magic_number()
{
    FILE *fptr = open_file(PNG_IMG_PATH);
    TEST_ASSERT_EQUAL(is_valid_magic_number(fptr, LE), 0);
    close_file(fptr);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_should_return_BE_for_big_endian_files);
    RUN_TEST(test_should_return_LE_for_little_endian_files);
    RUN_TEST(test_should_identify_valid_magic_number);
    RUN_TEST(test_should_identify_invalid_magic_number);

    return UNITY_END();
}
