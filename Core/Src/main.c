#include <stdint.h>

#define RCC_BASE 0x40021000U
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18U))

#define AFIO_BASE 0x40010000U
#define AFIO_MAPR (*(volatile uint32_t *)(AFIO_BASE + 0x04U))

#define GPIOA_BASE 0x40010800U
#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + 0x00U))
#define GPIOA_CRH (*(volatile uint32_t *)(GPIOA_BASE + 0x04U))
#define GPIOA_BSRR (*(volatile uint32_t *)(GPIOA_BASE + 0x10U))

#define GPIOB_BASE 0x40010C00U
#define GPIOB_CRL (*(volatile uint32_t *)(GPIOB_BASE + 0x00U))
#define GPIOB_CRH (*(volatile uint32_t *)(GPIOB_BASE + 0x04U))
#define GPIOB_BSRR (*(volatile uint32_t *)(GPIOB_BASE + 0x10U))

#define GPIOC_BASE 0x40011000U
#define GPIOC_CRH (*(volatile uint32_t *)(GPIOC_BASE + 0x04U))
#define GPIOC_BSRR (*(volatile uint32_t *)(GPIOC_BASE + 0x10U))

int main(void) {
  // Enable clock for AFIO and GPIOA
  RCC_APB2ENR |= 0x1DU; // Set bit 2 to enable GPIOA clock

  // Disable JTAG and enable SWD
  AFIO_MAPR &= 0xF8FFFFFFU;
  AFIO_MAPR |= 0x02000000U; // Set bit 25 to disable JTAG and enable SWD

  // Clear mode settings GPIOA
  GPIOA_CRL &= 0x00000000U; // Clear bits for pins 0-7
  GPIOA_CRH &= 0x0FF00000U; // Clear bits for pins 8-15
  // Clear mode settings GPIOB
  GPIOB_CRL &= 0x00000F00U; // Clear bits for pins 0-7
  GPIOB_CRH &= 0x00000000U; // Clear bits for pins 8-15
  // Clear mode settings GPIOC
  GPIOC_CRH &= 0x00000000U; // Clear bits for pins 8-15

  // Set PA as output push-pull, max speed 10 MHz
  GPIOA_CRL |= 0x11111111U; // Set bits for pins 0-7
  GPIOA_CRH |= 0x10011111U; // Set bits for pins 8-15
  // Set PB as output push-pull, max speed 10 MHz
  GPIOB_CRL |= 0x11111011U; // Set bits for pins 0-7
  GPIOB_CRH |= 0x11111111U; // Set bits for pins 8-15
  // Set PC as output push-pull, max speed 10 MHz
  GPIOC_CRH |= 0x11100000U; // Set bits for pins 8-15

  // Reset PA low
  GPIOA_BSRR = 0x9FFF0000U; 
  // Reset PB low
  GPIOB_BSRR = 0xFFFB0000U; 
  // Reset PC low
  GPIOC_BSRR = 0xE0000000U; 

  // Set PA high
  GPIOA_BSRR = 0x00009FFFU; 
  // Set PB high
  GPIOB_BSRR = 0x0000FFFBU; 
  // Set PC high
  GPIOC_BSRR = 0x0000E000U; 
}