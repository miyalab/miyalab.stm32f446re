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
 * File   : MiYALAB_STM32F446RE_TIM.h
 * Author : K.Miyauchi
 *
 * Version : 1.00
 */

#ifndef SRC_MiYALAB_STM32F446RE_TIM_H_
#define SRC_MiYALAB_STM32F446RE_TIM_H_

//--------------------------
// TIM機能使用許可
//--------------------------
//#define HAL_TIM_MODULE_ENABLED

//--------------------------
// インクルード
//--------------------------
#include "stm32f4xx.h"

//--------------------------
// プロトタイプ宣言
//--------------------------
extern "C"{
	void TIM6_DAC_IRQHandler(void);
	void TIM7_IRQHandler(void);
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
		// TIM 定数
		//----------------------------------------------------------------------
		namespace TIM{
			constexpr uint8_t CHANNEL_1 = 0x01;			// TIM チャンネル1
			constexpr uint8_t CHANNEL_2 = 0x02;			// TIM チャンネル2
			constexpr uint8_t CHANNEL_3 = 0x04;			// TIM チャンネル3
			constexpr uint8_t CHANNEL_4 = 0x08;			// TIM チャンネル4
			constexpr uint8_t CHANNEL_ALL = 0x0f;		// TIM 全チャンネル

			constexpr uint16_t ENCODER_MAX = 65535;		// TIM エンコーダ最大値
			constexpr uint16_t ENCODER_CENTER = 32767;	// TIM エンコーダ中央値
		}

		//----------------------------------------------------------------------
		// TIM PWM Mode スーパークラス
		//----------------------------------------------------------------------
		class TIM_PwmMode{
		public:
			uint8_t Init(uint16_t Divide, uint16_t Period);
			void PwmOut1(uint16_t Duty);
			void PwmOut2(uint16_t Duty);
			void PwmOut3(uint16_t Duty);
			void PwmOut4(uint16_t Duty);
		protected:
			TIM_HandleTypeDef hTim;
		};

		//----------------------------------------------------------------------
		// TIM1 PWM Mode クラス CH1(PA8), CH2(PA9), CH3(PA10), CH4(PA11)
		//----------------------------------------------------------------------
		class TIM1_PwmMode : public TIM_PwmMode{
		public:
			TIM1_PwmMode();
			~TIM1_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM2 PWM Mode クラス CH1(PA5), CH2(PB3), CH3(PB10), CH4(PB2)
		//----------------------------------------------------------------------
		class TIM2_PwmMode : public TIM_PwmMode{
		public:
			TIM2_PwmMode();
			~TIM2_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM3 PWM Mode クラス CH1(PB4), CH2(PB5), CH3(PB0), CH4(PB1)
		//----------------------------------------------------------------------
		class TIM3_PwmMode : public TIM_PwmMode{
		public:
			TIM3_PwmMode();
			~TIM3_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM4 PWM Mode クラス CH1(PB6), CH2(PB7), CH3(PB8), CH4(PB9)
		//----------------------------------------------------------------------
		class TIM4_PwmMode : public TIM_PwmMode{
		public:
			TIM4_PwmMode();
			~TIM4_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM5 PWM Mode クラス CH1(PA0), CH2(PA1), CH3(PA2), CH4(PA3)
		//----------------------------------------------------------------------
		class TIM5_PwmMode : public TIM_PwmMode{
		public:
			TIM5_PwmMode();
			~TIM5_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM8 PWM Mode クラス  CH1(PC6), CH2(PC7), CH3(PC8), CH4(PC9)
		//----------------------------------------------------------------------
		class TIM8_PwmMode : public TIM_PwmMode{
		public:
			TIM8_PwmMode();
			~TIM8_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
		};

		//----------------------------------------------------------------------
		// TIM12 PWM Mode クラス   CH1(PB14), CH2(PB15)
		//----------------------------------------------------------------------
		class TIM12_PwmMode : public TIM_PwmMode{
		public:
			TIM12_PwmMode();
			~TIM12_PwmMode();
			uint8_t Enable(uint8_t UseChannel);
			void PwmOut3(uint16_t Duty){}			// 使用不可
			void PwmOut4(uint16_t Duty){}			// 使用不可
		};

		//----------------------------------------------------------------------
		// TIM Encoder Mode スーパークラス
		//----------------------------------------------------------------------
		class TIM_EncoderMode{
		public:
			uint8_t Init(uint16_t Divide);
			int16_t Read();
			void Clear();
		protected:
			TIM_HandleTypeDef hTim;
		};

		//----------------------------------------------------------------------
		// TIM1 Encoder Mode クラス CH1(PA8), CH2(PA9)
		//----------------------------------------------------------------------
		class TIM1_EncoderMode : public TIM_EncoderMode{
		public:
			TIM1_EncoderMode();
			~TIM1_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM2 Encoder Mode クラス CH1(PA5), CH2(PB3)
		//----------------------------------------------------------------------
		class TIM2_EncoderMode : public TIM_EncoderMode{
		public:
			TIM2_EncoderMode();
			~TIM2_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM3 Encoder Mode クラス CH1(PB4), CH2(PB5)
		//----------------------------------------------------------------------
		class TIM3_EncoderMode : public TIM_EncoderMode{
		public:
			TIM3_EncoderMode();
			~TIM3_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM4 Encoder Mode クラス CH1(PB6), CH2(PB7)
		//----------------------------------------------------------------------
		class TIM4_EncoderMode : public TIM_EncoderMode{
		public:
			TIM4_EncoderMode();
			~TIM4_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM5 Encoder Mode クラス CH1(PA0), CH2(PA1)
		//----------------------------------------------------------------------
		class TIM5_EncoderMode : public TIM_EncoderMode{
		public:
			TIM5_EncoderMode();
			~TIM5_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM8 Encoder Mode クラス CH1(PC6), CH2(PC7)
		//----------------------------------------------------------------------
		class TIM8_EncoderMode : public TIM_EncoderMode{
		public:
			TIM8_EncoderMode();
			~TIM8_EncoderMode();
			uint8_t Enable();
		};

		//----------------------------------------------------------------------
		// TIM6 Timer Mode クラス
		//----------------------------------------------------------------------
		class TIM6_TimerMode{
		public:
			~TIM6_TimerMode();
			uint8_t Init(uint16_t Divide, uint16_t Period);
		};

		//----------------------------------------------------------------------
		// TIM6 タイマー割込み関数
		//----------------------------------------------------------------------
		void TIM6_InterruptFunction();

		//----------------------------------------------------------------------
		// TIM7 Timer Mode クラス
		//----------------------------------------------------------------------
		class TIM7_TimerMode{
		public:
			~TIM7_TimerMode();
			uint8_t Init(uint16_t Divide, uint16_t Period);
		};

		//----------------------------------------------------------------------
		// TIM7 タイマー割込み関数
		//----------------------------------------------------------------------
		void TIM7_InterruptFunction();
	}
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut1関数
// チャンネル1のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut1(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_1, Duty);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut2関数
// チャンネル2のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut2(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_2, Duty);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut3関数
// チャンネル3のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut3(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_3, Duty);
}

//--------------------------------------------------------------------------------------------
/// MiYA LAB OSS
// TIM PWM Mode スーパークラス　PwmOut4関数
// チャンネル4のデューティ比設定
//　Duty : 0 <= Duty < Period(Init関数引数)
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_PwmMode::PwmOut4(uint16_t Duty)
{
	__HAL_TIM_SET_COMPARE(&hTim, TIM_CHANNEL_4, Duty);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 PWM Mode クラス コンストラクタ
// TIM1_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM1_PwmMode::TIM1_PwmMode()
{
	__HAL_RCC_TIM1_CLK_ENABLE();
	hTim.Instance = TIM1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 PWM Mode クラス　デストラクタ
// TIM1_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM1_PwmMode::~TIM1_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PA8)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PA9)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_3(チャンネル3(PA10)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_4(チャンネル4(PA11)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM1_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF1_TIM1;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_3){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_4){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_11;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 PWM Mode クラス コンストラクタ
// TIM2_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM2_PwmMode::TIM2_PwmMode()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	hTim.Instance = TIM2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 PWM Mode クラス　デストラクタ
// TIM2_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM2_PwmMode::~TIM2_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PA5)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PB3)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_3(チャンネル3(PB10)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_4(チャンネル4(PB2)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM2_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF1_TIM2;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_5;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_3;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_3){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_4){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_2;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 PWM Mode クラス コンストラクタ
// TIM3_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM3_PwmMode::TIM3_PwmMode()
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	hTim.Instance = TIM3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 PWM Mode クラス　デストラクタ
// TIM3_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM3_PwmMode::~TIM3_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PB4)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PB5)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_3(チャンネル3(PB0)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_4(チャンネル4(PB1)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM3_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM3;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_4;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_5;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_3){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_0;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_4){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_1;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM4 PWM Mode クラス コンストラクタ
// TIM4_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM4_PwmMode::TIM4_PwmMode()
{
	__HAL_RCC_TIM4_CLK_ENABLE();
	hTim.Instance = TIM4;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM4 PWM Mode クラス　デストラクタ
// TIM4_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM4_PwmMode::~TIM4_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM4_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM4 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PB6)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PB7)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_3(チャンネル3(PB8)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_4(チャンネル4(PB9)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM4_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM4;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_6;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_3){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_4){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM5 PWM Mode クラス コンストラクタ
// TIM5_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM5_PwmMode::TIM5_PwmMode()
{
	__HAL_RCC_TIM5_CLK_ENABLE();
	hTim.Instance = TIM5;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM5 PWM Mode クラス　デストラクタ
// TIM5_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM5_PwmMode::~TIM5_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM5_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM5 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PA1)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PA2)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_3(チャンネル3(PA3)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_4(チャンネル4(PA4)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM5_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM5;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_0;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_1;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_3){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_2;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_4){
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_3;
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM8 PWM Mode クラス コンストラクタ
// TIM8_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM8_PwmMode::TIM8_PwmMode()
{
	__HAL_RCC_TIM8_CLK_ENABLE();
	hTim.Instance = TIM8;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM8 PWM Mode クラス　デストラクタ
// TIM8_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM8_PwmMode::~TIM8_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM8_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM8 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PC6)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PC7)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_3(チャンネル3(PC8)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_4(チャンネル4(PC9)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM8_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF3_TIM8;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_6;
		HAL_GPIO_Init(GPIOC, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	// CH3 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_3){
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOC, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_3) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_3);
	}

	// CH4 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_4){
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOC, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_4) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_4);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM12 PWM Mode クラス コンストラクタ
// TIM12_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM12_PwmMode::TIM12_PwmMode()
{
	__HAL_RCC_TIM12_CLK_ENABLE();
	hTim.Instance = TIM12;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM12 PWM Mode クラス　デストラクタ
// TIM12_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM12_PwmMode::~TIM12_PwmMode()
{
	HAL_TIM_PWM_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_DeInit(&hTim);
	__HAL_RCC_TIM12_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM12 PWM Mode クラス　Enable関数
// PWMを出力するチャンネルを設定します。
// UseChannel : MiYALAB::STM32F446RE::TIM::CHANNEL_1(チャンネル1(PB14)の使用許可)
//				MiYALAB::STM32F446RE::TIM::CHANNEL_2(チャンネル2(PB15)の使用許可)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM12_PwmMode::Enable(uint8_t UseChannel)
{
	// エラー判定用
	uint8_t Ret = HAL_OK;

	// ハードウェア設定用データ群
	TIM_OC_InitTypeDef ConfigOC = {0};
	GPIO_InitTypeDef GpioInitStruct = {0};

	// GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF9_TIM12;

	// チャンネル設定
	ConfigOC.OCMode = TIM_OCMODE_PWM1;
	ConfigOC.Pulse = 0;
	ConfigOC.OCPolarity = TIM_OCNPOLARITY_HIGH;
	ConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	// CH1 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_1){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_14;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_1) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_1);
	}

	// CH2 使用
	if(UseChannel & MiYALAB::STM32F446RE::TIM::CHANNEL_2){
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GpioInitStruct.Pin = GPIO_PIN_15;
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);
		if(HAL_TIM_PWM_ConfigChannel(&hTim, &ConfigOC, TIM_CHANNEL_2) != HAL_OK){
			Ret = HAL_ERROR;
		}
		HAL_TIM_PWM_Start(&hTim, TIM_CHANNEL_2);
	}

	return Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM Encoder Mode スーパークラス　Clear関数
// パルス係数初期化
//--------------------------------------------------------------------------------------------
inline void MiYALAB::STM32F446RE::TIM_EncoderMode::Clear()
{
	hTim.Instance->CNT = MiYALAB::STM32F446RE::TIM::ENCODER_CENTER;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM Encoder Mode スーパークラス　Encode関数
// return : パルス数
//--------------------------------------------------------------------------------------------
inline int16_t MiYALAB::STM32F446RE::TIM_EncoderMode::Read()
{
	return(hTim.Instance->CNT - MiYALAB::STM32F446RE::TIM::ENCODER_CENTER);
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 Encoder Mode クラス　コンストラクタ
// TIM1_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM1_EncoderMode::TIM1_EncoderMode()
{
	__HAL_RCC_TIM1_CLK_ENABLE();
	hTim.Instance = TIM1;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 Encoder Mode クラス　デストラクタ
// TIM1_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM1_EncoderMode::~TIM1_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM1_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM1 Encoder Mode クラス　Enable関数
// TIM1 CH1(PA8), CH2(PA9) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM1_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF1_TIM1;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 Encoder Mode クラス　コンストラクタ
// TIM2_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM2_EncoderMode::TIM2_EncoderMode()
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	hTim.Instance = TIM2;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 Encoder Mode クラス　デストラクタ
// TIM2_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM2_EncoderMode::~TIM2_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM2_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM2 Encoder Mode クラス　Enable関数
// TIM2 CH1(PA5), CH2(PB3) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM2_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_5;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);
	GpioInitStruct.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOB, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 Encoder Mode クラス　コンストラクタ
// TIM3_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM3_EncoderMode::TIM3_EncoderMode()
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	hTim.Instance = TIM3;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 Encoder Mode クラス　デストラクタ
// TIM3_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM3_EncoderMode::~TIM3_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM3_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM3 Encoder Mode クラス　Enable関数
// TIM3 CH1(PB4), CH2(PB5) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM3_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOB, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM4 Encoder Mode クラス　コンストラクタ
// TIM4_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM4_EncoderMode::TIM4_EncoderMode()
{
	__HAL_RCC_TIM4_CLK_ENABLE();
	hTim.Instance = TIM4;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM4 Encoder Mode クラス　デストラクタ
// TIM4_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM4_EncoderMode::~TIM4_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM4_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM4 Encoder Mode クラス　Enable関数
// TIM4 CH1(PB6), CH2(PB7) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM4_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOB, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM5 Encoder Mode クラス　コンストラクタ
// TIM5_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM5_EncoderMode::TIM5_EncoderMode()
{
	__HAL_RCC_TIM5_CLK_ENABLE();
	hTim.Instance = TIM5;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM5 Encoder Mode クラス　デストラクタ
// TIM5_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM5_EncoderMode::~TIM5_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM5_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM5 Encoder Mode クラス　Enable関数
// TIM5 CH1(PA0), CH2(PA1) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM5_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF2_TIM5;
	HAL_GPIO_Init(GPIOA, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM8 Encoder Mode クラス　コンストラクタ
// TIM8_CLK 開始
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM8_EncoderMode::TIM8_EncoderMode()
{
	__HAL_RCC_TIM8_CLK_ENABLE();
	hTim.Instance = TIM8;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM8 Encoder Mode クラス　デストラクタ
// TIM8_CLK 停止
//--------------------------------------------------------------------------------------------
inline MiYALAB::STM32F446RE::TIM8_EncoderMode::~TIM8_EncoderMode()
{
	HAL_TIM_Encoder_Stop(&hTim, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_DeInit(&hTim);
	__HAL_RCC_TIM8_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM8 Encoder Mode クラス　Enable関数
// TIM8 CH1(PC6), CH2(PC7) のパルス入力許可
//--------------------------------------------------------------------------------------------
inline uint8_t MiYALAB::STM32F446RE::TIM8_EncoderMode::Enable()
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	// クロック許可
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO設定
	GpioInitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GpioInitStruct.Mode = GPIO_MODE_AF_PP;
	GpioInitStruct.Pull = GPIO_NOPULL;
	GpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GpioInitStruct.Alternate = GPIO_AF3_TIM8;
	HAL_GPIO_Init(GPIOC, &GpioInitStruct);

	// パルス値初期化
	Clear();

	// パルス入力許可
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_1) != HAL_OK){
		return HAL_ERROR;
	}
	if(HAL_TIM_Encoder_Start(&hTim, TIM_CHANNEL_2) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

#endif /* SRC_MiYALAB_STM32F446RE_TIM_H_ */

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
