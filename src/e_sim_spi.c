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
 * \brief sim spi driver
 * 
 * \internal
 * \par Modification History
 * - 1.00 16-10-13  damon.zhang, first implementation.
 * \endinternal
 */


#include "e_sim_spi.h"

/*******************************************************************************
 * Private define region: constant & MACRO defined here                              
 ******************************************************************************/
#if (SPI_MODE ==0)
    #define E_SIM_SPI_CHOL    0     /** \brief spi clk default level          */
    #define E_SIM_SPI_CPHA    0     /** \brief spi data sample at Edge 1/2    */
#elif (SPI_MODE == 1)
    #define E_SIM_SPI_CHOL    0
    #define E_SIM_SPI_CPHA    1
#elif (SPI_MODE == 2)
    #define E_SIM_SPI_CHOL    1
    #define E_SIM_SPI_CPHA    0
#elif (SPI_MODE == 3)
    #define E_SIM_SPI_CHOL    1
    #define E_SIM_SPI_CPHA    1
#else
    #error "Unsupport SPI Mode define!"
#endif

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
 * \brief  
 */
void e_sim_spi_init(void)
{
    /* 
     * Add your code here to init pinmux
     */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 15);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 24);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 26);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 25);
    /* Add end */

    SIM_SPI_MOSI_HIGHT();
    SIM_SPI_CS_HIGHT();

#if (E_SIM_SPI_CHOL == 0)
    SIM_SPI_SCK_LOW();
#else
    SIM_SPI_SCK_HIGHT();
#endif
}

/**
 * \brief  
 */
uint8_t e_sim_spi_byte_send_recv(uint8_t dat)
{
    int     i     = 0;
    uint8_t temp = 0xAA;

#if (E_SIM_SPI_CPHA == 0)

    #if (E_SIM_SPI_CHOL == 0)
        SIM_SPI_SCK_LOW();
    #else 
        SIM_SPI_SCK_HIGHT();
    #endif

    for (i = 0;i < 8;i ++){
        if(dat & 0x80) {  
            SIM_SPI_MOSI_HIGHT();
        } else {
            SIM_SPI_MOSI_LOW();
        }
        dat <<= 1;
    #if (E_SIM_SPI_CHOL == 0)
        SIM_SPI_SCK_HIGHT();
    #else
        SIM_SPI_SCK_LOW();
    #endif
        BIT_DELAY();
        temp <<= 1;  
        if(SIM_SPI_MISO_READ()) {
            temp ++;
        }
    #if (E_SIM_SPI_CHOL == 0)
        SIM_SPI_SCK_LOW();
    #else
        SIM_SPI_SCK_HIGHT();
    #endif
        BIT_DELAY();
    }

#else  //E_SIM_SPI_CPHA == 1

    BIT_DELAY();
    for (i = 0;i < 8;i ++) {
    #if (E_SIM_SPI_CHOL == 0)
        SIM_SPI_SCK_HIGHT();
    #else
        SIM_SPI_SCK_LOW();
    #endif
        BIT_DELAY();
        if(dat & 0x80) {  
            SIM_SPI_MOSI_HIGHT(); 
        } else {
            SIM_SPI_MOSI_LOW(); 
        }
        dat <<= 1;

    #if (E_SIM_SPI_CHOL == 0)
        SIM_SPI_SCK_LOW();
    #else
        SIM_SPI_SCK_HIGHT();
    #endif

        BIT_DELAY();
        temp <<= 1;  
        if(SIM_SPI_MISO_READ()) {
            temp ++;
        }
    }

#endif  //end E_SIM_SPI_CPHA == 1

    return temp;
}


/*******************************************************************************
 * main code region: function implement                                        
 ******************************************************************************/


/* end of file */


