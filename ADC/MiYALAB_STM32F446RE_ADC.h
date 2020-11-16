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
 * File  : MiYALAB_STM32F446RE_ADC.h
 * Author: Koshiro Miyauchi
 *
 * Version : 1.00
 */

#ifndef MiYALAB_STM32F446_ADC_H_
#define MiYALAB_STM32F446_ADC_H_

//--------------------------
// ADC機能使用許可
//--------------------------
#define HAL_ADC_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include <stdio.h>
#include "stm32f4xx.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// STM32F446RE
	//--------------------------------------------------------------------------
	namespace STM32F446RE{
		//----------------------------------------------------------------------
		// AD 定数
		//----------------------------------------------------------------------
		namespace AD{
			constexpr uint16_t IN_0 = 0x0001;		// ADC IN0端子(PA0)
			constexpr uint16_t IN_1 = 0x0002;		// ADC IN1端子(PA1)
			constexpr uint16_t IN_2 = 0x0004;		// ADC IN2端子(PA2)
			constexpr uint16_t IN_3 = 0x0008;		// ADC IN3端子(PA3)
			constexpr uint16_t IN_4 = 0x0010;		// ADC IN4端子(PA4)
			constexpr uint16_t IN_5 = 0x0020;		// ADC IN5端子(PA5)
			constexpr uint16_t IN_6 = 0x0040;		// ADC IN6端子(PA6)
			constexpr uint16_t IN_7 = 0x0080;		// ADC IN7端子(PA7)
			constexpr uint16_t IN_8 = 0x0100;		// ADC IN8端子(PB1)
			constexpr uint16_t IN_9 = 0x0200;		// ADC IN9端子(PB2)
			constexpr uint16_t IN_10 = 0x0400;		// ADC IN10端子(PC0)
			constexpr uint16_t IN_11 = 0x0800;		// ADC IN11端子(PC1)
			constexpr uint16_t IN_12 = 0x1000;		// ADC IN12端子(PC2)
			constexpr uint16_t IN_13 = 0x2000;		// ADC IN13端子(PC3)
			constexpr uint16_t IN_14 = 0x4000;		// ADC IN14端子(PC4)
			constexpr uint16_t IN_15 = 0x8000;		// ADC IN15端子(PC5)
		}

		//----------------------------------------------------------------------
		// ADC_Modeクラス
		//----------------------------------------------------------------------
		class ADC_Mode{
		public:
			~ADC_Mode();
			uint8_t Init(uint32_t Resolution);
			uint16_t Read(uint16_t In);
		private:
			uint8_t Enable(uint16_t In);
			ADC_HandleTypeDef hAdc;
		};
	}
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode クラス デストラクタ
// ADC CLK停止
//------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::ADC_Mode::~ADC_Mode()
{
	HAL_ADC_Stop(&hAdc);
	HAL_ADC_DeInit(&hAdc);
	__HAL_RCC_ADC1_CLK_ENABLE();
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode スーパークラス　Init関数
// Resolution : ADC_RESOLUTION_6B(6bit ADC)
//            : ADC_RESOLUTION_8B(8bit ADC)
//            : ADC_RESOLUTION_10B(10bit ADC)
//            : ADC_RESOLUTION_12B(12bit ADC)
// return : 0(正常)
//			otherwise(エラー)
//------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::ADC_Mode::Init(uint32_t Resolution)
{
	// クロック設定
	__HAL_RCC_ADC1_CLK_ENABLE();

	// ADC設定
	hAdc.Instance = ADC1;
	hAdc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hAdc.Init.Resolution = Resolution;
	hAdc.Init.ScanConvMode = DISABLE;
	hAdc.Init.ContinuousConvMode = DISABLE;
	hAdc.Init.DiscontinuousConvMode = DISABLE;
	hAdc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hAdc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hAdc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hAdc.Init.NbrOfConversion = 1;
	hAdc.Init.DMAContinuousRequests = DISABLE;
	hAdc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	// ADC設定 適用
	if(HAL_ADC_Init(&hAdc) != HAL_OK){
		return 0;
	}

	return HAL_OK;
}

#endif /* MiYALAB_STM32F446_ADC_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
