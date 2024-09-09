#include "../src/tiff_data.h"
#include "../unity/unity.h"

char* TIRE_LE_IMG_PATH = "./images/tire.tif";
char* TIRE_BE_IMG_PATH = "./images/tireBE.tif";

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
}

static void test_should_return_LE_for_little_endian_files()
{
    FILE *fptr = open_file(TIRE_LE_IMG_PATH);
    TEST_ASSERT_EQUAL(get_endianess(fptr), LE);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_should_return_BE_for_big_endian_files);
    RUN_TEST(test_should_return_LE_for_little_endian_files);

    return UNITY_END();
}
