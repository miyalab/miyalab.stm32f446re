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

#ifndef MiYALAB_STM32F446_H_
#define MiYALAB_STM32F446_H_

//--------------------------
// インクルード
//--------------------------
#include <sys/_stdint.h>

//------------------------------------------------------------------------------
// MiYA LAB OSS
//------------------------------------------------------------------------------
namespace MiYALAB{
	//--------------------------------------------------------------------------
	// MultiAccessクラス (割り込み処理処理 バグ回避用)
	//--------------------------------------------------------------------------
	template <typename type> class MultiAccess{
	public:
		MultiAccess();
		MultiAccess(type SetData);
		void Set(type SetData);
		void Add(type Add);
		void Clear();
		type Read();
	private:
		type Data;
	};

	//--------------------------------------------------------------------------
	// PIDクラス
	//--------------------------------------------------------------------------
	template <typename type> class PID{
	public:
		PID();
		void Calculation(type SensorVal);
		void SetGain(type _Kp, type _Ki, type _Kd);
		void SetTarget(type Target);
		type Read();
		void Reset();
		void SetLimit(type Limit);

	private:
		type Kp, Ki, Kd;
		type Error, ErrorBefore, ErrorInt;
		type TargetVal;
		type ControlVal;
		type LimitVal;
	};
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス インストラクタ
//--------------------------------------------------------------------------------------------
template <typename type> MiYALAB::MultiAccess<type>::MultiAccess(){Data = 0;}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス インストラクタ
// SetData : 格納するデータ
//--------------------------------------------------------------------------------------------
template <typename type> MiYALAB::MultiAccess<type>::MultiAccess(type SetData){Data = SetData;}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス Set関数
// SetData : 格納するデータ
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::MultiAccess<type>::Set(type SetData){Data = SetData;}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス Add関数
// Add : 加算するデータ
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::MultiAccess<type>::Add(type Add){Data += Add;}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス Clear関数
// 格納されているデータを0にする
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::MultiAccess<type>::Clear(){Data = 0;}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス Read関数
// return : 格納されているデータ
//--------------------------------------------------------------------------------------------
template <typename type> type MiYALAB::MultiAccess<type>::Read(){return Data;}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// MultiAccessクラス インストラクタ
//--------------------------------------------------------------------------------------------
template <typename type> MiYALAB::PID<type>::PID()
{
	SetTarget(0);
	SetGain(0,0,0);
	SetLimit(1);
	Reset();
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// PIDクラス Calculation関数
// SensorVal : フィードバックされるセンサ値
//
// 一定周期で呼び出してください.
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::PID<type>::Calculation(type SensorVal)
{
	type Ret;
	type P, I, D;

	// 偏差計算
	ErrorBefore = Error;				// 前回の偏差を格納
	Error = TargetVal - SensorVal;		// 偏差計算
	ErrorInt += Error;					// 累積偏差

	// PID計算
	P = Kp * Error;						// 比例制御
	I = Ki * ErrorInt;					// 積分制御
	D = Kd * (Error - ErrorBefore);		// 微分制御

	Ret = P + I + D;

	// 操作量上限計算
	if(LimitVal != 0){
		if(Ret >  LimitVal) Ret = LimitVal;
		if(Ret < -LimitVal) Ret = -LimitVal;
	}

	ControlVal = Ret;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// PIDクラス SetGain関数
// _Kp : 比例ゲイン
// _Ki : 積分ゲイン
// _Kd : 微分ゲイン
//
// 各ゲインを設定します.
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::PID<type>::SetGain(type _Kp, type _Ki, type _Kd)
{
	Kp = _Kp;
	Ki = _Ki;
	Kd = _Kd;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// PIDクラス SetTarget関数
// Target : 目標値
//
// 目標値を設定します.
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::PID<type>::SetTarget(type Target)
{
	TargetVal = Target;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// PIDクラス Read関数
// return : 操作量
//--------------------------------------------------------------------------------------------
template <typename type> type MiYALAB::PID<type>::Read()
{
	return ControlVal;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// PIDクラス Reset関数
// すべての偏差を初期化します.
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::PID<type>::Reset()
{
	Error = 0;
	ErrorBefore = 0;
	ErrorInt = 0;
}

//--------------------------------------------------------------------------------------------
// MiYA LAB OSS
// PIDクラス SetLimit関数
// Limit : 0（操作量制限なし）
//       : otherwise(操作量制限あり)
//--------------------------------------------------------------------------------------------
template <typename type> void MiYALAB::PID<type>::SetLimit(type Limit)
{
	LimitVal = Limit;
}

#endif /* MiYALAB_STM32F446_H_ */

//--------------------------------------------------------------------------------------------
// end of file
//--------------------------------------------------------------------------------------------
