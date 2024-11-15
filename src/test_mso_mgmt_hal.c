/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2016 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**
* @file test_mso_mgmt_hal.c
* @page mso_mgmt_hal Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the mso_mgmt_hal APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <cjson/cJSON.h>
#include "mso_mgmt_hal.h"
#include <time.h>

#define MAX_SIZE 256

char *Invalid_Pass;
char *Good_Pass;
char *Unique_Pass;
char *Expired_Pass;

#define PASSWORD_STATUS_GOOD 0
#define PASSWORD_LENGTH_TOO_HIGH 8


/**
 * @brief Test case to verify the functionality of the mso_validatepwd function with a valid password.
 *
 * This test case verifies the functionality of the mso_validatepwd function by providing a valid password as input.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 001
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * The test is performed by following the steps below:
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set up the test case | pwd = "correct_password" | - | - |
 * | 02 | Invoke the mso_validatepwd API | pwd | mso_pwd_ret_status = Good_PWD | - |
 * | 03 | Check the return value | actual | expected | - |
 *
 * Test: Invoking mso_validatepwd with valid password
 * Expected Return Value: Good_PWD
 * Actual Return Value: %d
 *
 * @see mso_validatepwd
 */
// we cannot provide valid password of the day. So this API failure is expected.

void test_l1_mso_mgmt_hal_positive1_ValidPwd(void) {
    UT_LOG("Entering test_l1_mso_mgmt_hal_positive1_ValidPwd...");

    // Set up the test case
    char *pwd = Good_Pass;
    UT_LOG("pwd: %s", pwd);
    mso_pwd_ret_status expected = Good_PWD;
    UT_LOG("expected: %d", expected);

    // Log the input password
    UT_LOG("Input Password: %s", pwd);

    // Invoke the API
    mso_pwd_ret_status actual = mso_validatepwd(pwd);

    // Log the return value
    UT_LOG("Actual Return Value from mso_validatepwd: %d", actual);

    // Check the return value
    if (actual != expected) {
        // Log detailed error information
        UT_LOG("ERROR: Expected Return Value: %d, but got: %d", expected, actual);
        
        // Add more context if needed
        UT_LOG("Investigate IPC and Client API call failures in the logs.");
    }

    // Assert the return value
    UT_ASSERT_EQUAL(actual, expected);

    // Log the test information
    UT_LOG("Test: Invoking mso_validatepwd with valid password");
    UT_LOG("Expected Return Value: Good_PWD");
    UT_LOG("Actual Return Value: %d", actual);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_positive1_ValidPwd...");
}

/**
 * @brief Test case to verify the functionality of the mso_validatepwd function when NULL is passed as input.
 *
 * This test case verifies the functionality of the mso_validatepwd function when NULL is passed as input.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 002
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * The test is performed by following the steps below:
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Set up the test case | pwd = "NULL" | - | - |
 * | 02 | Invoke the mso_validatepwd API | pwd | mso_pwd_ret_status = Good_PWD | - |
 * | 03 | Check the return value | actual | expected | - |
 *
 * Test: Invoking mso_validatepwd with valid password
 * Expected Return Value: Good_PWD
 * Actual Return Value: %d
 *
 * @see mso_validatepwd
 */
 
void test_l1_mso_mgmt_hal_negative1_NullCheck(void){
    UT_LOG("Entering test_l1_mso_mgmt_hal_negative1_NullCheck...");
    
    INT result = mso_validatepwd(NULL);
    
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_negative1_null_NullCheck...");
}


/**
 * @brief This test case verifies the functionality of the mso_validatepwd() API to validate a invalid password.
 *
 * This test case checks whether the mso_validatepwd() API correctly validates the given password as a unique password. The expected return value is Invalid_PWD, indicating a successful validation.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 003
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | -------------- | --- |
 * | 01 | Set up the test case | pwd = "invalid_password" | expected = Invalid_PWD | - |
 * | 02 | Invoke the API | mso_validatepwd(pwd) | actual = Unique_PWD | - |
 * | 03 | Check the return value | actual | expected | Should be successful |
 *
 */

void test_l1_mso_mgmt_hal_negative2_PwdLength(void){
    UT_LOG("Entering test_l1_mso_mgmt_hal_positive2_PwdLength...");
    
    char *pwd = Invalid_Pass;
    UT_LOG("Input value: %s", pwd);
    mso_pwd_ret_status expected = Invalid_PWD;
    
    mso_pwd_ret_status actual = mso_validatepwd(pwd);
    
    UT_ASSERT_EQUAL(actual, expected);
    // Check the return value   
    UT_LOG("Test: Invoking mso_validatepwd with Invalid password");
    UT_LOG("Expected Return Value: Invalid_PWD");
    UT_LOG("Actual Return Value: %d", actual);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_positive2_UniquePwd...");
}

/**
* @brief This test case is used to verify the behavior of the mso_validatepwd function when an invalid password is provided.
*
* The purpose of this test is to ensure that the mso_validatepwd function returns the expected status when an invalid password is provided as input.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 004
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Set up the test case | pwd = "incorrect_password" | expected = Invalid_PWD | - |
* | 02 | Invoke the API | mso_validatepwd(pwd) | actual = return value of mso_validatepwd | - |
* | 03 | Check the return value | actual | expected | Should be equal |
* | 04 | Log the test information | - | - | - |
*
* */

void test_l1_mso_mgmt_hal_negative3_PwdLengthGreater(void){
    UT_LOG("Entering test_l1_mso_mgmt_hal_negative3_PwdLengthGreater...");
    
    char *pwd = "1234567890";
    UT_LOG("Input value: %s", pwd);
    
    mso_pwd_ret_status expected = Invalid_PWD;
    
    mso_pwd_ret_status actual = mso_validatepwd(pwd);
    
    UT_ASSERT_EQUAL(actual, expected);
    // Check the return value   
    UT_LOG("Test: Invoking mso_validatepwd with Invalid password");
    UT_LOG("Expected Return Value: Invalid_PWD");
    UT_LOG("Actual Return Value: %d", actual);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_negative3_PwdLengthGreater...");
}

/**
* @brief Unit test to verify the handling of an empty buffer in the mso_set_pod_seed function.
*
* This test is used to verify that the mso_set_pod_seed function handles an empty buffer correctly.
* The objective of this test is to ensure that the function returns RETURN_ERR when invoked with an empty buffer.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 005
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ------ |
* | 01 | Invoking mso_set_pod_seed with valid buffer | buffer = [64 bytes initialized with random values] | RETURN_OK | The result is expected to be RETURN_OK and the buffer should not be empty |
*/
void test_l1_mso_mgmt_hal_positive1_Valid_Buffer(void){
    UT_LOG("Entering test_l1_mso_mgmt_hal_positive1_Valid_Buffer...");

    // Preallocate a valid buffer
    char buffer[64];

    // Invoke the API
    INT result = mso_set_pod_seed(buffer);

    // Verify the result
    UT_LOG("Invoking mso_get_pod_seed with valid buffer.");
    UT_LOG("Return Value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_positive1_Valid_Buffer...");
}

/**
* @brief Test case to verify the behavior of the mso_set_pod_seed function when invoked with a NULL pointer.
*
* This test case checks if the mso_set_pod_seed function returns the expected result when invoked with a NULL pointer as input.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 006
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking the function with a NULL pointer | pointer = NULL | RETURN_ERR | Should return an error |
*/

void test_l1_mso_mgmt_hal_negative1_null_pointer(void){
    UT_LOG("Entering test_l1_mso_mgmt_hal_negative1_null_pointer...");

    // Invoke the API with a NULL pointer
    INT result = mso_set_pod_seed(NULL);

    // Check the return value
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_negative1_null_pointer...");
}

/**
* @brief Test the functionality of the mso_get_pod_seed() API with a valid buffer
*
* This test case verifies the functionality of the mso_get_pod_seed() API when a valid buffer is passed.
*
* **T4est Group ID:** Basic: 01
* **Test Case ID:** 007
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking mso_get_pod_seed with valid buffer | buffer = [64 bytes initialized with random values] | RETURN_OK | The result is expected to be RETURN_OK and the buffer should not be empty |
*/
void test_l1_mso_mgmt_hal_positive1_valid_Buffer(void) {
    UT_LOG("Entering test_l1_mso_mgmt_hal_positive1_valid_Buffer...");

    // Preallocate a valid buffer
    char buffer[64];

    // Invoke the API
    INT result = mso_get_pod_seed(buffer);

    // Verify the result
    UT_LOG("Invoking mso_get_pod_seed with valid buffer.");
    UT_LOG("Return Value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_OK);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_positive1_valid_Buffer...");
}

/**
* @brief This test case is used to verify the behavior of the mso_get_pod_seed function when called with a NULL pointer as input.
*
* The objective of this test is to ensure that the function correctly handles the case where a NULL pointer is passed as input.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 008
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description                                                                                      | Test Data             | Expected Result                   | Notes             |
* | :-------------: | -----------------------------------------------------------------------------------------------| ----------------------|---------------------------------- | ------------------ |
* |       01        | The function is invoked with a NULL pointer as input                                           | NULL                  | Function should return RETURN_ERR | Should be successful |
*/
void test_l1_mso_mgmt_hal_negative1_Null_Pointer(void) {
    UT_LOG("Entering test_l1_mso_mgmt_hal_negative1_Null_Pointer...");

    // Invoke the API with NULL pointer
    INT result = mso_get_pod_seed(NULL);
    // Verify the result
    UT_LOG("Invoking mso_get_pod_seed with NULL pointer.");
    UT_LOG("Return Value: %d", result);
    UT_ASSERT_EQUAL(result, RETURN_ERR);

    UT_LOG("Exiting test_l1_mso_mgmt_hal_negative1_Null_Pointer...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_mso_hal_l1_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 mso_mgmt_hal]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }

    // Allocate memory for each password string
    Invalid_Pass = (char *)malloc(MAX_SIZE * sizeof(char));
    Good_Pass = (char *)malloc(MAX_SIZE * sizeof(char));
    Unique_Pass = (char *)malloc(MAX_SIZE * sizeof(char));
    Expired_Pass = (char *)malloc(MAX_SIZE * sizeof(char));

    if (!Invalid_Pass || !Good_Pass || !Unique_Pass || !Expired_Pass) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter the Invalid password: ");
    if (fgets(Invalid_Pass, MAX_SIZE, stdin) != NULL) {
        size_t len = strlen(Invalid_Pass);
        if (len > 0 && Invalid_Pass[len - 1] == '\n') {
            Invalid_Pass[len - 1] = '\0';
        }
    }

    printf("Enter the Good password: ");
    if (fgets(Good_Pass, MAX_SIZE, stdin) != NULL) {
        size_t len = strlen(Good_Pass);
        if (len > 0 && Good_Pass[len - 1] == '\n') {
            Good_Pass[len - 1] = '\0';
        }
    }

    printf("Enter the Unique password: ");
    if (fgets(Unique_Pass, MAX_SIZE, stdin) != NULL) {
        size_t len = strlen(Unique_Pass);
        if (len > 0 && Unique_Pass[len - 1] == '\n') {
            Unique_Pass[len - 1] = '\0';
        }
    }

    printf("Enter the Expired password: ");
    if (fgets(Expired_Pass, MAX_SIZE, stdin) != NULL) {
        size_t len = strlen(Expired_Pass);
        if (len > 0 && Expired_Pass[len - 1] == '\n') {
            Expired_Pass[len - 1] = '\0';
        }
    }

    // Debug prints to verify values are fetched correctly

    printf("Invalid_Password: %s\n", Invalid_Pass);
    printf("Good_Password: %s\n", Good_Pass);
    printf("Unique_Password: %s\n", Unique_Pass);
    printf("Expired_Password: %s\n", Expired_Pass);

    // Add tests to the suite
    UT_add_test(pSuite, "l1_mso_mgmt_hal_positive1_ValidPwd", test_l1_mso_mgmt_hal_positive1_ValidPwd);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_negative1_NullCheck", test_l1_mso_mgmt_hal_negative1_NullCheck);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_negative2_PwdLength", test_l1_mso_mgmt_hal_negative2_PwdLength);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_negative3_PwdLengthGreater", test_l1_mso_mgmt_hal_negative3_PwdLengthGreater);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_positive1_Valid_Buffer", test_l1_mso_mgmt_hal_positive1_Valid_Buffer);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_negative1_null_pointer", test_l1_mso_mgmt_hal_negative1_null_pointer);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_positive1_valid_Buffer", test_l1_mso_mgmt_hal_positive1_valid_Buffer);
    UT_add_test(pSuite, "l1_mso_mgmt_hal_negative1_Null_Pointer", test_l1_mso_mgmt_hal_negative1_Null_Pointer);

    return 0;
}



