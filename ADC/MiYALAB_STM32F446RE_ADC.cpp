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
 * File  : MiYALAB_STM32F446RE_ADC.cpp
 * Author: Koshiro Miyauchi
 *
 * Version : 1.00
 */

//--------------------------
// インクルード
//--------------------------
#include "MiYALAB_STM32F446RE_ADC.h"

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode クラス　Enable関数
// 指定したIN端子のADC値を読み込みます。
// In : MiYALAB::STM32F446RE::AD::IN_X(X=0~15)
// return : ADC値
//------------------------------------------------------------------------------
uint16_t MiYALAB::STM32F446RE::ADC_Mode::Read(uint16_t In)
{
	uint16_t AdcValue = 0;

	// ハードウェア設定用データ群
	ADC_ChannelConfTypeDef Config = {0};

	// 端子設定（アナログ入力モードに切り替え）
	Enable(In);

	// チャンネル設定
	Config.Rank = 1;
	Config.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	if((In & MiYALAB::STM32F446RE::AD::IN_0) == MiYALAB::STM32F446RE::AD::IN_0) Config.Channel = ADC_CHANNEL_0;
	else if((In & MiYALAB::STM32F446RE::AD::IN_1) == MiYALAB::STM32F446RE::AD::IN_1) Config.Channel = ADC_CHANNEL_1;
	else if((In & MiYALAB::STM32F446RE::AD::IN_2) == MiYALAB::STM32F446RE::AD::IN_2) Config.Channel = ADC_CHANNEL_2;
	else if((In & MiYALAB::STM32F446RE::AD::IN_3) == MiYALAB::STM32F446RE::AD::IN_3) Config.Channel = ADC_CHANNEL_3;
	else if((In & MiYALAB::STM32F446RE::AD::IN_4) == MiYALAB::STM32F446RE::AD::IN_4) Config.Channel = ADC_CHANNEL_4;
	else if((In & MiYALAB::STM32F446RE::AD::IN_5) == MiYALAB::STM32F446RE::AD::IN_5) Config.Channel = ADC_CHANNEL_5;
	else if((In & MiYALAB::STM32F446RE::AD::IN_6) == MiYALAB::STM32F446RE::AD::IN_6) Config.Channel = ADC_CHANNEL_6;
	else if((In & MiYALAB::STM32F446RE::AD::IN_7) == MiYALAB::STM32F446RE::AD::IN_7) Config.Channel = ADC_CHANNEL_7;
	else if((In & MiYALAB::STM32F446RE::AD::IN_8) == MiYALAB::STM32F446RE::AD::IN_8) Config.Channel = ADC_CHANNEL_8;
	else if((In & MiYALAB::STM32F446RE::AD::IN_9) == MiYALAB::STM32F446RE::AD::IN_9) Config.Channel = ADC_CHANNEL_9;
	else if((In & MiYALAB::STM32F446RE::AD::IN_10) == MiYALAB::STM32F446RE::AD::IN_10) Config.Channel = ADC_CHANNEL_10;
	else if((In & MiYALAB::STM32F446RE::AD::IN_11) == MiYALAB::STM32F446RE::AD::IN_11) Config.Channel = ADC_CHANNEL_11;
	else if((In & MiYALAB::STM32F446RE::AD::IN_12) == MiYALAB::STM32F446RE::AD::IN_12) Config.Channel = ADC_CHANNEL_12;
	else if((In & MiYALAB::STM32F446RE::AD::IN_13) == MiYALAB::STM32F446RE::AD::IN_13) Config.Channel = ADC_CHANNEL_13;
	else if((In & MiYALAB::STM32F446RE::AD::IN_14) == MiYALAB::STM32F446RE::AD::IN_14) Config.Channel = ADC_CHANNEL_14;
	else if((In & MiYALAB::STM32F446RE::AD::IN_15) == MiYALAB::STM32F446RE::AD::IN_15) Config.Channel = ADC_CHANNEL_15;
	else return 0;

	// チャンネル設定 適用
	if(HAL_ADC_ConfigChannel(&hAdc, &Config) != HAL_OK){
		return 0;
	}

	// ADC開始
	if(HAL_ADC_Start(&hAdc) != HAL_OK){
		return 0;
	}

	// AD変換
	if(HAL_ADC_PollForConversion(&hAdc, 10) != HAL_OK){
		return 0;
	}

	// ADC値取得
	if((HAL_ADC_GetState(&hAdc) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC){
		AdcValue = HAL_ADC_GetValue(&hAdc);
	}

	// ADC停止
	if(HAL_ADC_Stop(&hAdc) != HAL_OK){
		return 0;
	}

	return AdcValue;
}

//------------------------------------------------------------------------------
// MiYA LAB OSS
// ADC Mode クラス　Enable関数
// 使用するADCのIN端子を設定します。
// In : MiYALAB::STM32F446RE::AD::IN_X(X=0~15)
// return : 0(正常)
//			otherwise(エラー)
//------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::ADC_Mode::Enable(uint16_t In)
{
	// ハードウェア設定用データ群
	GPIO_InitTypeDef GpioInitStruct = {0};

	//　GPIO設定
	GpioInitStruct.Mode = GPIO_MODE_ANALOG;
	GpioInitStruct.Pull = GPIO_NOPULL;

	// IN0 ~ IN7 の設定
	if(In & (MiYALAB::STM32F446RE::AD::IN_0 | MiYALAB::STM32F446RE::AD::IN_1 | MiYALAB::STM32F446RE::AD::IN_2 |
			MiYALAB::STM32F446RE::AD::IN_3 | MiYALAB::STM32F446RE::AD::IN_4 | MiYALAB::STM32F446RE::AD::IN_5 |
			MiYALAB::STM32F446RE::AD::IN_6 | MiYALAB::STM32F446RE::AD::IN_7)){
		// クロック設定
		__HAL_RCC_GPIOA_CLK_ENABLE();

		if(In & MiYALAB::STM32F446RE::AD::IN_0) GpioInitStruct.Pin = GPIO_PIN_0;
		else if(In & MiYALAB::STM32F446RE::AD::IN_1) GpioInitStruct.Pin = GPIO_PIN_1;
		else if(In & MiYALAB::STM32F446RE::AD::IN_2) GpioInitStruct.Pin = GPIO_PIN_2;
		else if(In & MiYALAB::STM32F446RE::AD::IN_3) GpioInitStruct.Pin = GPIO_PIN_3;
		else if(In & MiYALAB::STM32F446RE::AD::IN_4) GpioInitStruct.Pin = GPIO_PIN_4;
		else if(In & MiYALAB::STM32F446RE::AD::IN_5) GpioInitStruct.Pin = GPIO_PIN_5;
		else if(In & MiYALAB::STM32F446RE::AD::IN_6) GpioInitStruct.Pin = GPIO_PIN_6;
		else if(In & MiYALAB::STM32F446RE::AD::IN_7) GpioInitStruct.Pin = GPIO_PIN_7;
		else return HAL_ERROR;

		// GPIO設定 適用
		HAL_GPIO_Init(GPIOA, &GpioInitStruct);

		return HAL_OK;
	}

	// IN8 ~ IN9 の設定
	if(In & (MiYALAB::STM32F446RE::AD::IN_8 | MiYALAB::STM32F446RE::AD::IN_9)){
		// クロック設定
		__HAL_RCC_GPIOB_CLK_ENABLE();

		if(In & MiYALAB::STM32F446RE::AD::IN_8) GpioInitStruct.Pin = GPIO_PIN_0;
		else if(In & MiYALAB::STM32F446RE::AD::IN_9) GpioInitStruct.Pin = GPIO_PIN_1;
		else return HAL_ERROR;

		// GPIO設定 適用
		HAL_GPIO_Init(GPIOB, &GpioInitStruct);

		return HAL_OK;
	}

	// IN10 ~ IN5 の設定
	if(In & (MiYALAB::STM32F446RE::AD::IN_10 | MiYALAB::STM32F446RE::AD::IN_11 | MiYALAB::STM32F446RE::AD::IN_12 |
			MiYALAB::STM32F446RE::AD::IN_13 |MiYALAB::STM32F446RE::AD::IN_14 | MiYALAB::STM32F446RE::AD::IN_15)){
		// クロック設定
		__HAL_RCC_GPIOC_CLK_ENABLE();

		if(In & MiYALAB::STM32F446RE::AD::IN_10) GpioInitStruct.Pin = GPIO_PIN_0;
		else if(In & MiYALAB::STM32F446RE::AD::IN_11) GpioInitStruct.Pin = GPIO_PIN_1;
		else if(In & MiYALAB::STM32F446RE::AD::IN_12) GpioInitStruct.Pin = GPIO_PIN_2;
		else if(In & MiYALAB::STM32F446RE::AD::IN_13) GpioInitStruct.Pin = GPIO_PIN_3;
		else if(In & MiYALAB::STM32F446RE::AD::IN_14) GpioInitStruct.Pin = GPIO_PIN_4;
		else if(In & MiYALAB::STM32F446RE::AD::IN_15) GpioInitStruct.Pin = GPIO_PIN_5;
		else return HAL_ERROR;

		// GPIO設定 適用
		HAL_GPIO_Init(GPIOC, &GpioInitStruct);

		return HAL_OK;
	}

	return HAL_ERROR;
}

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
