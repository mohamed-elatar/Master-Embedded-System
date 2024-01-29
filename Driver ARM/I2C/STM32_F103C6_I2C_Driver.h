/***********************************************
 * @file           : STM32_F103C6_I2C_Driver.h	*
 * @author         : mohamed elatar             *
 * @Data           : November 11, 2023			*
 ************************************************/


#ifndef STM32_F103C6_I2C_Driver_H_
#define STM32_F103C6_I2C_Driver_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103C6_GPIO_Driver.h"


//-----------------------------
//Structure
//-----------------------------
typedef struct
{
	uint8_t	Enable_Dual_ADD;			//@ref_I2C_Enable_Dual_ADD
	uint8_t	Primary_Slave_ADD_OAR1;		//OAR1
	uint8_t	Secondary_Slave_ADD_OAR2;	//OAR2
	uint8_t	I2C_Addressing_Slave_Mode;	//@ref_I2C_Addressing_Slave_Mode
}S_I2C_Slave_Device_Address;


typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_MATCH,
	I2C_EV_DATA_REQ,		// slave send data to master
	I2C_EV_DATA_RCV			// slave receive data from master
}E_Slave_State_Irq;


typedef struct
{
	uint32_t 						I2C_SCLK;				// Specifics I2C clock master Based on @ref_I2C_SCLK

	uint16_t 						I2C_Stretch_Mode;		// Specifics enable stretch or not Based on @ref_I2C_Clock_stretching

	uint16_t						I2C_Mode;				// Specifics among I2C or SMBus Based on @ref_I2C_mode

	S_I2C_Slave_Device_Address 		I2C_Slave_Address;		// Specifics 7B Or 10B Address Based on @ref_I2C_Addressing_Slave_Mode
	// enable or disable dual addressing Based on @ref_I2C_Enable_Dual_ADD

	uint16_t						I2C_ACK_Control;		// Specifics 8\16 bits transmit  Based on @ref_I2C_Ack

	uint16_t						I2C_General_Call;		// Specifics idle clock 1 or 0  Based on @ref_I2C_General call

	void(* PF_IRQ_Slave_Event_CallBack)(E_Slave_State_Irq); // will be called once the irq happen
}I2C_Config;


//-----------------------------
//References Macros
//-----------------------------
//@ref_I2C_SCLK
//clock pin (SCL) Master , It can be connected with a standard (up to 100 kHz) or fast (up to 400 kHz) I2C bus.
//The peripheral input(Slave) clock frequency must be at least:
//• 2 MHz in Sm mode
//• 4 MHz in Fm mode
//The Bottom line is --> Master Max Out(100 KHz) Slave At Least In(2 MHz) For standard mode

//(1) Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
//Bits 5:0 FREQ[5:0]: Peripheral clock frequency
//The FREQ bits must be configured with the APB clock frequency value (I2C peripheral
//connected to APB). the maximum frequency is limited by the maximum APB frequency and cannot exceed
//50 MHz (peripheral intrinsic maximum limit).
//The Bottom line is --> frequency APB == FREQ[5:0]
//0b000000: Not allowed
//0b000001: Not allowed
//0b000010: 2 MHz
//...
//0b110010: 50 MHz
//Higher than 0b100100: Not allowed


//(2) Configure the clock control registers
//Bits 11:0 CCR[11:0]:Clock control register in Fm/Sm mode (Master mode)
//Controls the SCL clock in master mode.
//Sm mode or SMBus:
//Thigh= CCR * TPCLK1
//Tlow= CCR * TPCLK1

//(3) Configure the rise time register (I2C_TRISE)
//the maximum allowed SCL rise time is 1000 ns
//FREQ[5:0] bits is equal to 0x08 --> TPCLK1= 125 ns
//therefore the TRISE[5:0] bits must be programmed with 09h.
//(1000 ns / 125 ns = 8 + 1)

//(4) Program the I2C_CR1 register to enable the peripheral

#define I2C_SCLK_SM_50K					(50000UL)
#define I2C_SCLK_SM_100K				(100000UL)
#define I2C_SCLK_FM_200K				(200000UL)//Fast Mode not support yet
#define I2C_SCLK_FM_400K				(400000UL)


//@ref_I2C_Clock_stretching
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
//it is Reset_flag by software.
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_Clock_stretching_Enable		(0x0 << 7) //I2C_CR1
#define I2C_Clock_stretching_Disable	(0x1 << 7) //I2C_CR1


//@ref_I2C_mode
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C					(0x0 << 1) //I2C_CR1
#define I2C_Mode_SMBus					(0x1 << 1) //I2C_CR1

//@ref_I2C_Enable_Dual_ADD
//Bit 0 ENDUAL: Dual addressing mode enable (OAR2 register)
//0: Only OAR1 is recognized in 7-bit addressing mode
//1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
#define I2C_Dual_ADD_Enable			(0x1 << 0) //I2C_OAR2
#define I2C_Dual_ADD_Disable		(0x0 << 0) //I2C_OAR2

//@ref_I2C_Addressing_Slave_Mode
//Bit 15 ADDMODEAddressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_Slave_Mode_7B	(0x0 << 15) //I2C_OAR1
#define I2C_Addressing_Slave_Mode_10B	(0x1 << 15) //I2C_OAR1


//@ref_I2C_Ack
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Enable					(0x1 << 10) //I2C_CR1
#define I2C_ACK_Disable					(0x0 << 10) //I2C_CR1


//@ref_I2C_General call
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_General_call_Disable		(0x0 << 6) //I2C_CR1
#define I2C_General_call_Enable			(0x1 << 6) //I2C_CR1


typedef enum
{
	With_Stop,
	Without_Stop
}E_Stop_Condition;

typedef enum
{
	Send_Start,
	Send_Repeated_Start
}E_Repeated_Start;

typedef enum
{
	Disable_Send_Start,
	Enable_Send_Start,
	Disable_Send_Stop,
	Enable_Send_Stop,
	Disable_Send_ACK,
	Enable_Send_ACK
}E_Function_State;

typedef enum
{
	Direction_TX_W,
	Direction_RX_R
}E_I2C_Direction;

typedef enum
{
	Reset_flag,
	Set_flag
}E_Flag_Status;

typedef enum
{
	I2C_Flag_Busy,
	EV5,//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	EV6,//EV6:ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7,//RxNE=1 cleared by reading DR register
	EV7_1,//RxNE=1 cleared by reading DR register
	EV8,//EV8:TxE=1, shift register not empty, dataregister empty, cleared by writing DR register
	EV8_1,//EV8_1: TxE=1 , shift register empty, dataregister empty, write Data1 in DR
	EV8_2,//TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	Master_Byte_Transmitting = ((uint32_t)0x00070080) // Data register empty & Master Mode & Bus busy &  Data bytes transmitted
}E_Status;
/* ===============================================
 * 			APIs Supported by "MCAL I2C DRIVER"
 * ===============================================
 */

void MCAL_I2C_Init (I2C_TypeDef * I2Cx , I2C_Config * I2C_Config);
void MCAL_I2C_DeInit (I2C_TypeDef *I2Cx);

void MCAL_I2C_GPIO_Set_Pins (I2C_TypeDef *I2Cx);

//master polling
void MCAL_I2C_Master_TX (I2C_TypeDef * I2Cx , uint16_t devive_address , uint8_t *ptr_Buffer , uint32_t Data_Length , E_Stop_Condition Stop , E_Repeated_Start Start);
void MCAL_I2C_Master_RX (I2C_TypeDef * I2Cx , uint16_t devive_address , uint8_t *ptr_Buffer , uint32_t Data_Length , E_Stop_Condition Stop , E_Repeated_Start Start);

void MCAL_I2C_Slave_TX (I2C_TypeDef * I2Cx , uint8_t data);
uint8_t MCAL_I2C_Slave_RX (I2C_TypeDef * I2Cx );

void I2C_Generate_Start (I2C_TypeDef * I2Cx , E_Function_State New_State , E_Repeated_Start Start);
void I2C_Send_Address(I2C_TypeDef * I2Cx , uint16_t address , E_I2C_Direction Direction);
void I2C_ACKnowledge_Config (I2C_TypeDef * I2Cx , E_Function_State New_State);
void I2C_Generate_Stop (I2C_TypeDef * I2Cx , E_Function_State New_State);
E_Flag_Status I2c_Get_Flag_Status (I2C_TypeDef * I2Cx , E_Status Flag);



void Slave_States (I2C_TypeDef * I2Cx , E_Slave_State_Irq Flag);





/* ===============================================
 * 			Bit definition
 * ===============================================
 */
/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset_flag */



/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< ptr_Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */



/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)



/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */



/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */


#endif /* STM32_F103C6_I2C_Driver_H_ */
