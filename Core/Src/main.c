#include <stdint.h>

#define RCC_BASE 0x40021000U
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18U))

#define AFIO_BASE 0x40010000U
#define AFIO_MAPR (*(volatile uint32_t *)(AFIO_BASE + 0x04U))

#define GPIOA_BASE 0x40010800U
#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + 0x00U))
#define GPIOA_CRH (*(volatile uint32_t *)(GPIOA_BASE + 0x04U))
#define GPIOA_BSRR (*(volatile uint32_t *)(GPIOA_BASE + 0x10U))

int main(void) {
  // Enable clock for AFIO and GPIOA
  RCC_APB2ENR |= 0x05U; // Set bit 2 to enable GPIOA clock
  // Disable JTAG and enable SWD
  AFIO_MAPR &= 0xF8FFFFFFU;
  AFIO_MAPR |= 0x02000000U; // Set bit 25 to disable JTAG and enable SWD
  // Clear mode settings
  GPIOA_CRL &= 0x00000000U; // Clear bits for pins 0-7
  GPIOA_CRH &= 0x0FF00000U; // Clear bits for pins 8-15
  // Set PA0-12 & PA15 as output push-pull, max speed 10 MHz
  GPIOA_CRL |= 0x11111111U; // Set bits for pins 0-7
  GPIOA_CRH |= 0x10011111U; // Set bits for pins 8-15
  // Reset PA0-12 & PA15 low
  GPIOA_BSRR = 0x9FFF0000U; 
  // Set PA0-12 & PA15 high
  GPIOA_BSRR = 0x00009FFFU; 
}