#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "encoder.h"
#include "pwm.h"
#include "step_test.h"

bool step_test_active = true;
static FILE *step_test_data = NULL;

void step_test_init()
{
    printf ("Stepping init recording data...\n") ;
    step_test_data = fopen("/home/user-4700/dev/gameController/step_test_data.csv", "w");
    if (step_test_data == NULL)
    {
        perror("Failed to open step_test_data.csv");
        step_test_active = false;
        return;
    }
    step_test_active = true;
}


#define STEP_TEST_LENGTH 1500
int step_test(unsigned int loop_count)
{
    int speed_toggle = 0;
    float speed = 0.3;

    if(!step_test_active)
    {
        return 0;
    }

    if (step_test_data != NULL)
    {
        //printf("%ld,%.6f\n", encoder_get_count(1), encoder_get_speed(1));
        fprintf(step_test_data, "%d,%ld,%.6f\n", loop_count, encoder_get_count(1), encoder_get_speed(1));
        fflush(step_test_data);
    }
    
    switch(loop_count)
    {
        case 0:

            printf ("Case 0...\n");
            break;
        case 100*STEP_TEST_LENGTH:
            pwm_set_duty(0, 0); // Perform step test actions for loop_count 100
            pwm_set_duty(1, 0); // Perform step test actions for loop_count 100
            printf ("Case 2...\n");
            break;
        case 100+2*STEP_TEST_LENGTH:
            pwm_set_duty(0, 0.3);
            pwm_set_duty(1, 0.3);
            printf ("Case 3...\n");
            break;
        case 100+3*STEP_TEST_LENGTH:
            pwm_set_duty(0, -0.3);
            pwm_set_duty(1, -0.3);
            printf ("Case 4...\n");
            break;
        case 100+4*STEP_TEST_LENGTH:
            pwm_set_duty(0, 0.3);
            pwm_set_duty(1, -0.3);
            printf ("Case 5...\n");
            break;
        case 100+5*STEP_TEST_LENGTH:
            pwm_set_duty(0, -0.3);
            pwm_set_duty(1, 0.3);
            printf ("Case 6...\n");
            break;
        case 100+6*STEP_TEST_LENGTH:
            pwm_set_duty(0, 0.0); // Perform step test actions for loop_count 100
            pwm_set_duty(1, 0.0); // Perform step test actions for loop_count 100
            speed = 0.6;
            speed_toggle = 1;
            printf ("Case 7...\n");
            break;
        case 100+7*STEP_TEST_LENGTH: //Begin Speed Switch Test
                pwm_set_duty(0, 0.6);
                pwm_set_duty(1, 0.6);
            printf ("Case 3...\n");
            break;
        case 100+8*STEP_TEST_LENGTH:
                pwm_set_duty(0, -0.6);
                pwm_set_duty(1, -0.6);
            printf ("Case 4...\n");
            break;
        case 100+9*STEP_TEST_LENGTH:
                pwm_set_duty(0, 0.6);
                pwm_set_duty(1, -0.6);
            printf ("Case 5...\n");
            break;
        case 100+10*STEP_TEST_LENGTH:
                pwm_set_duty(0, -0.6);
                pwm_set_duty(1, 0.6);
            printf ("Case 6...\n");
            break;
        case 100+11*STEP_TEST_LENGTH:
            pwm_set_duty(0, 0.0); // Perform step test actions for loop_count 100
            pwm_set_duty(1, 0.0); // Perform step test actions for loop_count 100
            printf ("Case 7...\n");
            break;
        case 100+12*STEP_TEST_LENGTH:
            step_test_active = false;
            break;
        // Add more cases as needed
        default:
            // Perform step test actions for other loop_count values
            break;
    }
    return 1;
}

void step_test_cleanup()
{
    if (step_test_data != NULL)
    {
        fflush(step_test_data);
        fclose(step_test_data);
        step_test_data = NULL;
    }
}