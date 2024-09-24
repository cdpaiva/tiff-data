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

static void test_should_get_IFD_offset()
{
    FILE *fptr = open_file(TIRE_LE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_IFD_offset(fptr, LE), 47410);
    close_file(fptr);
}

static void test_should_get_IFD_offset_BE()
{
    FILE *fptr = open_file(TIRE_BE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_IFD_offset(fptr, BE), 47410);
    close_file(fptr);
}

static void test_should_get_same_IFD_for_both_endianess()
{
    FILE *fptr = open_file(TIRE_BE_IMG_PATH);
    FILE *fptr_le = open_file(TIRE_LE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_IFD_offset(fptr, BE), get_IFD_offset(fptr_le, LE));
    close_file(fptr);
    close_file(fptr_le);
}


static void test_should_get_number_of_IFDs()
{
    FILE *fptr = open_file(TIRE_LE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_number_IFDs(fptr, LE), 13);
    close_file(fptr);
}

static void test_should_get_number_of_IFDs_BE()
{
    FILE *fptr = open_file(TIRE_BE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_number_IFDs(fptr, BE), 13);
    close_file(fptr);
}




int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_should_return_BE_for_big_endian_files);
    RUN_TEST(test_should_return_LE_for_little_endian_files);
    RUN_TEST(test_should_identify_valid_magic_number);
    RUN_TEST(test_should_identify_invalid_magic_number);
    RUN_TEST(test_should_get_IFD_offset);
    RUN_TEST(test_should_get_IFD_offset_BE);
    RUN_TEST(test_should_get_same_IFD_for_both_endianess);
    RUN_TEST(test_should_get_number_of_IFDs);
    RUN_TEST(test_should_get_number_of_IFDs_BE);

    return UNITY_END();
}
