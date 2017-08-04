/*******************************************************************************
* -----------------------------------------------------------------------------
*									     									 
* i2c.h - definitions for the i2c-bus interface			     			 
*									     
* -----------------------------------------------------------------------------
* Copyright (C) Damon Zhang
* All rights reserved.
*
* Author : Damon Zhang
* Website: https://damon-yun.github.io/blog.github.io/
* E-mail : damoncheung@foxmail.com
*
* -----------------------------------------------------------------------------
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* -----------------------------------------------------------------------------
* 
* @file
* Dynamic memory manager
*
* -----------------------------------------------------------------------------
*******************************************************************************/

/**
 * \file
 * \brief simulation single spi interface
 * 
 * \internal
 * \par Modification History
 * - 1.00 16-10-13  damon.zhang, first implementation.
 * \endinternal
 */


#ifndef __E_SIM_SPI_H
#define __E_SIM_SPI_H


#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * Header file
 ******************************************************************************/
#include "board.h"



/*******************************************************************************
 * Config  define
 ******************************************************************************/
#define SPI_MODE               3             /* 0/1/2/3 */
#define SPI_DATA_MSB           1             /* 0/1     */

/**
 * \addtogroup am_if_uart
 * \copydoc am_uart.h
 * @{
 */

/**
 * \name
 * \note
 * @{
 */

#define     SIM_SPI_CS_LOW()		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 15, 0)
#define     SIM_SPI_CS_HIGHT()		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 15, 1)

#define     SIM_SPI_SCK_LOW()		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 24, 0)
#define     SIM_SPI_SCK_HIGHT()		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 24, 1)

#define     SIM_SPI_MOSI_LOW()		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 26, 0)
#define     SIM_SPI_MOSI_HIGHT()	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 26, 1)


#define     SIM_SPI_MISO_READ()     Chip_GPIO_GetPinState(LPC_GPIO_PORT, 0, 25)

#define     BIT_DELAY()             __NOP()

/** @} */

#ifndef INLINE

#ifdef __CC_ARM
#define INLINE  __inline
#else
#define INLINE inline
#endif

#endif
/*******************************************************************************
 * Public define region: constant & MACRO defined here                              
 ******************************************************************************/

/*******************************************************************************
 * extern region: extern global variable & function prototype                 
 ******************************************************************************/

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/


/*****************************************************************************
 * Private functions
 ****************************************************************************/


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * \brief simulation spi init
 *
 * \param[in] void
 *
 * \return void
 */
extern void e_sim_spi_init(void);

/**
 * \brief simulation spi cs
 *
 * \param[in] void
 *
 * \return void
 */
STATIC INLINE void e_sim_spi_cs_low (void)
{
    SIM_SPI_CS_LOW();
}


/**
 * \brief simulation spi cs
 *
 * \param[in] void
 *
 * \return void
 */
STATIC INLINE void e_sim_spi_cs_hight (void)
{
    SIM_SPI_CS_HIGHT();
}


/**
 * \brief spi byte send
 *
 * \param[in] data  : data
 *
 * \return void
 * \note  
 *        
 */
extern uint8_t e_sim_spi_byte_send_recv(uint8_t data);


/**
 * @}
 */
 
 #ifdef __cplusplus
}
#endif

#endif /* __E_SIM_SPI_H */

/* end of file */


