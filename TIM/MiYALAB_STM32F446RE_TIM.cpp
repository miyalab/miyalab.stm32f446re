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

//--------------------------
// インクルード
//--------------------------
#include "MiYALAB_STM32F446RE_TIM.h"

//--------------------------
// グローバル変数宣言
//--------------------------
TIM_HandleTypeDef hTim6;
TIM_HandleTypeDef hTim7;

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM PWM Mode スーパークラス　Init関数
// Cycle[s] = Divide * Period / APBx_TimerClock[Hz] (x=1,2)
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::TIM_PwmMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};
	TIM_BreakDeadTimeConfigTypeDef BreakDeadTimeConfig = {0};

	// TIM設定
	hTim.Init.Prescaler = Divide - 1;
	hTim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim.Init.Period = Period - 1;
	hTim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	// TIM設定適用 PWMモード
	if(HAL_TIM_PWM_Init(&hTim) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM マスタ設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	// TIM マスタ設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM1 or TIM8
	if(hTim.Instance == TIM1 || hTim.Instance == TIM8){
		// TIM ブレーキデッドタイム設定
		BreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
		BreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
		BreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
		BreakDeadTimeConfig.DeadTime = 0;
		BreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
		BreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
		BreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;

		// TIM ブレーキデッドタイム設定適用
		if(HAL_TIMEx_ConfigBreakDeadTime(&hTim, &BreakDeadTimeConfig) != HAL_OK){
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM Encoder Mode スーパークラス　Init関数
// count　= パルス数 / Divide
// return : 0(正常)
//			otherwise(エラー)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::TIM_EncoderMode::Init(uint16_t Divide)
{
	// ハードウェア設定用データ群
	TIM_Encoder_InitTypeDef Config ={0};
	TIM_MasterConfigTypeDef MasterConfig = {0};

	// TIM設定
	hTim.Init.Prescaler = Divide;
	hTim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim.Init.Period = MiYALAB::STM32F446RE::TIM::ENCODER_MAX;
	hTim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTim.Init.RepetitionCounter = 0;
	hTim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	// TIM設定(エンコーダモード)
	Config.EncoderMode = TIM_ENCODERMODE_TI12;
	Config.IC1Polarity = TIM_ICPOLARITY_RISING;
	Config.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	Config.IC1Prescaler = TIM_ICPSC_DIV1;
	Config.IC1Filter = 0;
	Config.IC2Polarity = TIM_ICPOLARITY_RISING;
	Config.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	Config.IC2Prescaler = TIM_ICPSC_DIV1;
	Config.IC2Filter = 0;

	// TIM設定(エンコーダモード)　適用
	if(HAL_TIM_Encoder_Init(&hTim, &Config) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM マスター設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	// TIM マスター設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM6 Timer Mode クラス　デストラクタ
// TIM6_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::TIM6_TimerMode::~TIM6_TimerMode()
{
	HAL_TIM_Base_Stop_IT(&hTim6);
	HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
	HAL_TIM_Base_DeInit(&hTim6);
	__HAL_RCC_TIM6_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM6 Timer Mode クラス Init関数
// Cycle[s] = Divide * Period / APB1 TimerClocks[Hz]
// Divide : 分周比
// Period : カウントリセット値
//
// main.cppに以下の関数を定義してください。
// void MiYALAB::STM32F446RE::TIM6_InterruptFunction(void)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::TIM6_TimerMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};

	// クロック許可
	__HAL_RCC_TIM7_CLK_ENABLE();

	// 割込み許可
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	// TIM6 設定
	hTim6.Instance = TIM6;
	hTim6.Init.Prescaler = Divide - 1;
	hTim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim6.Init.Period = Period - 1;
	hTim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	// TIM6設定適用 タイマーモード
	if(HAL_TIM_Base_Init(&hTim6) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM6 マスター設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;

	// TIM6 マスター設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim6, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM6 タイマー割込み許可
	HAL_TIM_Base_Start_IT(&hTim6);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// TIM6 割込み関数（未定義用）
//--------------------------------------------------------------------------------------------
__weak void MiYALAB::STM32F446RE::TIM6_InterruptFunction()
{

}

//--------------------------------------------------------------------------------------------
// TIM6 割込みハンドラ
//--------------------------------------------------------------------------------------------
void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&hTim6);

	MiYALAB::STM32F446RE::TIM6_InterruptFunction();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM7 Timer Mode クラス　デストラクタ
// TIM7_CLK 停止
//--------------------------------------------------------------------------------------------
MiYALAB::STM32F446RE::TIM7_TimerMode::~TIM7_TimerMode()
{
	HAL_TIM_Base_Stop_IT(&hTim7);
	HAL_NVIC_DisableIRQ(TIM7_IRQn);
	HAL_TIM_Base_DeInit(&hTim7);
	__HAL_RCC_TIM7_CLK_DISABLE();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// TIM7 Timer Mode クラス Init関数
// Cycle[s] = Divide * Period / APB1 TimerClocks[Hz]
// Divide : 分周比
// Period : カウントリセット値
//
// main.cppに以下の関数を定義してください。
// void MiYALAB::STM32F446RE::TIM7_InterruptFunction(void)
//--------------------------------------------------------------------------------------------
uint8_t MiYALAB::STM32F446RE::TIM7_TimerMode::Init(uint16_t Divide, uint16_t Period)
{
	// ハードウェア設定用データ群
	TIM_MasterConfigTypeDef MasterConfig = {0};

	// クロック許可
	__HAL_RCC_TIM7_CLK_ENABLE();

	// 割込み許可
	HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

	// TIM7 設定
	hTim7.Instance = TIM7;
	hTim7.Init.Prescaler = Divide - 1;
	hTim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	hTim7.Init.Period = Period - 1;
	hTim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	// TIM7設定適用 タイマーモード
	if(HAL_TIM_Base_Init(&hTim7) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM7 マスター設定
	MasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;

	// TIM7 マスター設定適用
	if(HAL_TIMEx_MasterConfigSynchronization(&hTim7, &MasterConfig) != HAL_OK){
		return HAL_ERROR;
	}

	// TIM7 タイマー割込み許可
	HAL_TIM_Base_Start_IT(&hTim7);

	return HAL_OK;
}

//--------------------------------------------------------------------------------------------
// TIM7 割込み関数（未定義用）
//--------------------------------------------------------------------------------------------
__weak void MiYALAB::STM32F446RE::TIM7_InterruptFunction()
{

}

//--------------------------------------------------------------------------------------------
// TIM7 割込みハンドラ
//--------------------------------------------------------------------------------------------
void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&hTim7);

	MiYALAB::STM32F446RE::TIM7_InterruptFunction();
}

//--------------------------------------------------------------------------------------------
// end of file
//--------------------------------------------------------------------------------------------
