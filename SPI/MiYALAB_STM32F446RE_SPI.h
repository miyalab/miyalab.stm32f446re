/*
 * MIT License
 *
 * Copyright (c) 2020 MiYA LAB(K.Miyauchi)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * File   : MiYALAB_STM32F446RE_SPI.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef MIYALAB_STM32F446RE_SPI_H_
#define MIYALAB_STM32F446RE_SPI_H_

//--------------------------
// SPI機能使用許可
//--------------------------
#define HAL_SPI_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal_spi.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE{
		//----------------------------------------------------------------------
		// SPI Master Mode スーパークラス
		//----------------------------------------------------------------------
		class SPI_MasterMode{
		public:
			uint8_t Init(uint32_t BaudrateDivide, uint32_t DataSize, uint32_t FirstBit);
			void TransmitReceive(uint8_t *SendData, uint8_t *ReadData, uint16_t Size);
		protected:
			SPI_HandleTypeDef hSpi;
		};

		//----------------------------------------------------------------------
		// SPI1 Master Mode クラス
		//----------------------------------------------------------------------
		class SPI1_MasterMode : public SPI_MasterMode{
			SPI1_MasterMode();
			~SPI1_MasterMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// SPI2 Master Mode クラス
		//----------------------------------------------------------------------
		class SPI2_MasterMode : public SPI_MasterMode{
			SPI2_MasterMode();
			~SPI2_MasterMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// SPI3 Master Mode クラス　MISO(PC11), MOSI(PC12) ,SCK(PC10)
		//----------------------------------------------------------------------
		class SPI3_MasterMode : public SPI_MasterMode{
			SPI3_MasterMode();
			~SPI3_MasterMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// SPI Slave Mode スーパークラス
		//----------------------------------------------------------------------
		class SPI_SlaveMode{
		public:
			uint8_t Init(uint32_t DataSize, uint32_t FirstBit);
			void TransmitReceive(uint8_t *SendData, uint8_t *ReadData, uint16_t Size);
		protected:
			SPI_HandleTypeDef hSpi;
		};

		//----------------------------------------------------------------------
		// SPI1 Slave Mode クラス　MISO(), MOSI() ,SCK(), NSS()
		//----------------------------------------------------------------------
		class SPI1_SlaveMode : public SPI_SlaveMode{
			SPI1_SlaveMode();
			~SPI1_SlaveMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// SPI2 Slave Mode クラス　MISO(), MOSI() ,SCK(), NSS()
		//----------------------------------------------------------------------
		class SPI2_SlaveMode : public SPI_SlaveMode{
			SPI2_SlaveMode();
			~SPI2_SlaveMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// SPI3 Slave Mode クラス　MISO(PC11), MOSI(PC12) ,SCK(PC10), NSS(PA15)
		//----------------------------------------------------------------------
		class SPI3_SlaveMode : public SPI_SlaveMode{
			SPI3_SlaveMode();
			~SPI3_SlaveMode();
			uint8_t Enable();
		};
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI Master Mode TransmitReceive関数
// SendData : 送信データ
// ReadData :　受信データ格納用
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::SPI_MasterMode::TransmitReceive(uint8_t *SendData, uint8_t *ReadData, uint16_t Size)
{
	HAL_SPI_TransmitReceive(&hSpi, SendData, ReadData, Size, 100);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Master Mode クラス コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::SPI3_MasterMode::SPI3_MasterMode()
{
	__HAL_RCC_SPI3_CLK_ENABLE();
	hSpi.Instance = SPI3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Master Mode クラス デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::SPI3_MasterMode::~SPI3_MasterMode()
{
	HAL_SPI_DeInit(&hSpi);
	__HAL_RCC_SPI3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Master Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::SPI3_MasterMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI Slave Mode TransmitReceive関数
// SendData : 送信データ
// ReadData :　受信データ格納用
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::SPI_SlaveMode::TransmitReceive(uint8_t *SendData, uint8_t *ReadData, uint16_t Size)
{
	HAL_SPI_TransmitReceive(&hSpi, SendData, ReadData, Size, 100);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Slave Mode クラス コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::SPI3_SlaveMode::SPI3_SlaveMode()
{
	__HAL_RCC_SPI3_CLK_ENABLE();
	hSpi.Instance = SPI3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Slave Mode クラス デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::SPI3_SlaveMode::~SPI3_SlaveMode()
{
	HAL_SPI_DeInit(&hSpi);
	__HAL_RCC_SPI3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// SPI3 Slave Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::SPI3_SlaveMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_15;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	GpioInitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

#endif /* MIYALAB_STM32F446RE_SPI_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.11.25 ファイル作成
 */
