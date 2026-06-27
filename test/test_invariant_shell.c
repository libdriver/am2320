#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// Include the actual shell.c header or declare the function prototype
// Assuming shell.c has a function that processes input with a buffer
void shell_process_input(const char *input, char *output_buffer, size_t buffer_size);

START_TEST(test_buffer_reads_never_exceed_declared_length)
{
    // Invariant: Buffer reads never exceed the declared length
    const char *payloads[] = {
        "normal_input",                     // Valid input
        "A",                                // Boundary: single char
        "very_long_input_that_exceeds_buffer_by_more_than_double_AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"  // Exploit: oversized input
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);
    const size_t BUFFER_SIZE = 32;          // Match the buffer size used in shell.c

    for (int i = 0; i < num_payloads; i++) {
        char output_buffer[BUFFER_SIZE + 16];  // Extra guard bytes
        memset(output_buffer, 0xAA, sizeof(output_buffer));  // Fill with sentinel value
        
        // Call the actual production function
        shell_process_input(payloads[i], output_buffer, BUFFER_SIZE);
        
        // Check that sentinel bytes after buffer boundary are untouched
        for (size_t j = BUFFER_SIZE; j < sizeof(output_buffer); j++) {
            ck_assert_msg(output_buffer[j] == (char)0xAA,
                         "Buffer overflow detected at byte %zu for payload: %s",
                         j, payloads[i]);
        }
        
        // Additional check: ensure NULL termination within bounds
        if (strlen(payloads[i]) >= BUFFER_SIZE) {
            ck_assert_msg(output_buffer[BUFFER_SIZE - 1] == '\0',
                         "Buffer not properly terminated for oversized input: %s",
                         payloads[i]);
        }
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_buffer_reads_never_exceed_declared_length);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}