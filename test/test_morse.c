#include "unity.h"
#include "morse.h"
#include "mock_stm32f1xx_hal.h"
#include "mock_stm32f1xx_hal_gpio.h"
#include "mock_stub_cmsis_os.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void setUp_squeak(uint32_t Duration)
{
  HAL_GPIO_WritePin_Expect(MY_PIN_13_GPIO_Port, MY_PIN_13_Pin, GPIO_PIN_RESET);
//  osDelay_ExpectAndReturn(Duration, osOK);
  HAL_Delay_Expect(Duration);
  HAL_GPIO_WritePin_Expect(MY_PIN_13_GPIO_Port, MY_PIN_13_Pin, GPIO_PIN_SET);
}

void test_morse_squeak(void)
{
  setUp_squeak(143);
  squeak(143);
}

void test_morse_dot(void)
{
  setUp_squeak(DOT_DURATION);
//  osDelay_ExpectAndReturn(DOT_DURATION, osOK);
  HAL_Delay_Expect(DOT_DURATION);
  dot();
}

void test_morse_dash(void)
{
  setUp_squeak(DASH_DURATION);
//  osDelay_ExpectAndReturn(DOT_DURATION, osOK);
  HAL_Delay_Expect(DOT_DURATION);
  dash();
}
