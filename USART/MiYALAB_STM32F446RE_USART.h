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
 * File   : MiYALAB_STM32F446RE_USART.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef SRC_MIYALAB_STM32F446RE_USART_H_
#define SRC_MIYALAB_STM32F446RE_USART_H_

//--------------------------
// UART機能使用許可
//--------------------------
#define HAL_UART_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"

//--------------------------
// プロトタイプ宣言
//--------------------------
extern "C"{
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
	void __io_putchar(uint8_t ch);
	int __io_getchar(void);
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE* f)
#endif
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE{
		//----------------------------------------------------------------------
		// USART用 標準入出力関数用ラッパー関数宣言
		//----------------------------------------------------------------------
		void USART_stdioEnable();
		void USART_PutChar(uint8_t C);
		uint8_t USART_GetChar(uint8_t *C);
		void USART_EchoBack(uint8_t C);

		//----------------------------------------------------------------------
		// USART UART モード 基底クラス
		//----------------------------------------------------------------------
		class USART_UartMode{
		public:
			uint8_t Init(uint32_t Baudrate, uint32_t Length, uint32_t StopBits, uint32_t Parity);
			uint8_t Receive(uint8_t *C, uint16_t TimeOut);
			uint8_t Receive(uint8_t *Str, uint16_t Size, uint16_t TimeOut);
			uint8_t Transmit(uint8_t C, uint16_t TimeOut);
			uint8_t Transmit(uint8_t *Str, uint16_t Size, uint16_t TimeOut);
		protected:
			UART_HandleTypeDef hUart;
		};

		//----------------------------------------------------------------------
		// USART1 UART モード クラス
		//----------------------------------------------------------------------
		class USART1_UartMode : public USART_UartMode{
		public:
			USART1_UartMode();
			~USART1_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// USART2 UART モード クラス
		//----------------------------------------------------------------------
		class USART2_UartMode : public USART_UartMode{
		public:
			USART2_UartMode();
			~USART2_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// USART3 UART モード クラス
		//----------------------------------------------------------------------
		class USART3_UartMode : public USART_UartMode{
		public:
			USART3_UartMode();
			~USART3_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// UART4 UART モード クラス
		//----------------------------------------------------------------------
		class UART4_UartMode : public USART_UartMode{
		public:
			UART4_UartMode();
			~UART4_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// UART5 UART モード クラス
		//----------------------------------------------------------------------
		class UART5_UartMode : public USART_UartMode{
		public:
			UART5_UartMode();
			~UART5_UartMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// USART6 UART モード クラス
		//----------------------------------------------------------------------
		class USART6_UartMode : public USART_UartMode{
		public:
			USART6_UartMode();
			~USART6_UartMode();
			uint8_t Enable();
		};
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART Uart Mode スーパークラス　Receive関数
// *C : 1文字保存用
// TimeOut: タイムアウト時間
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART_UartMode::Receive(uint8_t *C, uint16_t TimeOut)
{
	return HAL_UART_Receive(&hUart, C, 1, TimeOut);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART Uart Mode スーパークラス　Receive関数
// *Str : 文字列保存用
// Size : Sｔｒのデータサイズ
// TimeOut: タイムアウト時間
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART_UartMode::Receive(uint8_t *Str, uint16_t Size, uint16_t TimeOut)
{
	return HAL_UART_Receive(&hUart, Str, Size, TimeOut);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART Uart Mode スーパークラス　Transmit関数
// *C : 送信文字
// TimeOut: タイムアウト時間
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART_UartMode::Transmit(uint8_t C, uint16_t TimeOut)
{
	return HAL_UART_Transmit(&hUart, &C, 1, TimeOut);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART Uart Mode スーパークラス　Transmit関数
// *Str : 送信文字列
// Size : Sｔｒのデータサイズ
// TimeOut: タイムアウト時間
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART_UartMode::Transmit(uint8_t *Str, uint16_t Size, uint16_t TimeOut)
{
	return HAL_UART_Transmit(&hUart, Str, Size, TimeOut);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART1_UartMode::USART1_UartMode()
{
	__HAL_RCC_USART1_CLK_ENABLE();
	hUart.Instance = USART1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART1_UartMode::~USART1_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART1 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART1_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART2_UartMode::USART2_UartMode()
{
	__HAL_RCC_USART2_CLK_ENABLE();
	hUart.Instance = USART2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART2_UartMode::~USART2_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART2 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART2_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART3 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART3_UartMode::USART3_UartMode()
{
	__HAL_RCC_USART3_CLK_ENABLE();
	hUart.Instance = USART3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART3 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART3_UartMode::~USART3_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART3 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART3_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART4 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::UART4_UartMode::UART4_UartMode()
{
	__HAL_RCC_UART4_CLK_ENABLE();
	hUart.Instance = UART4;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART4 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::UART4_UartMode::~UART4_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_UART4_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART4 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::UART4_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF8_UART4;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART5 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::UART5_UartMode::UART5_UartMode()
{
	__HAL_RCC_UART5_CLK_ENABLE();
	hUart.Instance = UART5;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART5 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::UART5_UartMode::~UART5_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_UART5_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// UART5 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::UART5_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_12;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF8_UART5;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);
	GpioInitStruct.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOD, &GpioInitStruct);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART6 Uart Mode クラス　コンストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART6_UartMode::USART6_UartMode()
{
	__HAL_RCC_USART6_CLK_ENABLE();
	hUart.Instance = USART6;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART6 Uart Mode クラス　デストラクタ
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::USART6_UartMode::~USART6_UartMode()
{
	HAL_UART_DeInit(&hUart);
	__HAL_RCC_USART6_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// USART6 Uart Mode クラス Enable関数
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::USART6_UartMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_6;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_PULLUP;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GpioInitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	return HAL_OK;
}

#endif /* SRC_MIYALAB_STM32F446RE_USART_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
/*
 * 2020.11.24 コメントの一部を修正
 */
