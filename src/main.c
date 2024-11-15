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
#include "mso_mgmt_hal.h"

extern char *Invalid_Pass;
extern char *Good_Pass;
extern char *Unique_Pass;
extern char *Expired_Pass;

extern int register_hal_l1_tests( void );
extern int get_pwd(void);

int main(int argc, char** argv)
{
    //Register tests as required, then call the UT-main to support switches and triggering 
    UT_init( argc, argv );
     //Check if tests are registered successfully 
    int registerReturn = register_hal_l1_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_tests() returned success");
    }
    else
    {
        printf("register_hal_tests() returned failure");
        return 1;
    }
    //Begin test executions 
    
    UT_run_tests();
    return 0;
}

