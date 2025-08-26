/**
  * @file ntc.c
  * @brief NTC temperature sensor driver source file
  * @author Leon Lee (leonlee.scut@outlook.com)
  * @version 0.1
  * @date 2025/08/26
  *
  * @copyright Copyright (c) 2025 South China University of Technology.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  * @par History:
  * 	Date		Version		Author			Description
  * 	2025/08/26	0.1			Leon Lee		Preliminary version.
  */

#include "ntc.h"
#include "assert.h"

/*
 * The NTC table has 256 interpolation points.
 *      NTC Parameter:
 *             Type: 10K/1%/3950
 *     Manufacturer:
 *              R25: 10kohm
 *             Beta: 3950
 *        Tolerance: F (F=1%, G=2%, H=3%, J=5%)
 *       Dimensions:
 *       Topologies: pull-up resistor:   3.3kohm
 *
 *               Vref
 *               ---
 *                |
 *               +-+
 *               | |
 *               | | Rpu = 3.3kohm
 *               +-+
 *                |                                      B*TN
 *                +---------- Vout          T = -------------------
 *                |                                       RT
 *               +-+ _                            B + ln[----]*TN
 *               | |/                                     RN
 *               |/| NTC
 *             _/+-+
 *                |
 *               ---
 *               GND
 *
 * Unit: 0.1 °C x10
 *
 */
const uint16_t ntc_table[] = {
                                3255,    // 0
                                3255,
                                2683,
                                2395,
                                2208,
                                2072,
                                1965,
                                1879,
                                1806,
                                1743,
                                1688,
                                1640,
                                1596,
                                1557,
                                1520,
                                1487,
                                1457,
                                1428,
                                1401,
                                1376,
                                1353,
                                1330,
                                1309,
                                1289,
                                1270,
                                1252,
                                1234,
                                1218,
                                1202,
                                1186,
                                1172,
                                1157,
                                1143,
                                1130,
                                1117,
                                1105,
                                1092,
                                1081,
                                1069,
                                1058,
                                1047,
                                1037,
                                1026,
                                1016,
                                1006,
                                997,
                                987,
                                978,
                                969,
                                961,
                                952,
                                943,
                                935,
                                927,
                                919,
                                911,
                                903,
                                896,
                                888,
                                881,
                                874,
                                867,
                                860,
                                853,
                                846,
                                839,
                                833,
                                826,
                                820,
                                813,
                                807,
                                801,
                                795,
                                789,
                                783,
                                777,
                                771,
                                765,
                                760,
                                754,
                                748,
                                743,
                                737,
                                732,
                                726,
                                721,
                                716,
                                711,
                                705,
                                700,
                                695,
                                690,
                                685,
                                680,
                                675,
                                670,
                                665,
                                660,
                                656,
                                651,
                                646,
                                641,
                                637,
                                632,
                                627,
                                623,
                                618,
                                614,
                                609,
                                604,
                                600,
                                596,
                                591,
                                587,
                                582,
                                578,
                                573,
                                569,
                                565,
                                560,
                                556,
                                552,
                                548,
                                543,
                                539,
                                535,
                                531,
                                526,
                                522,
                                518,
                                514,
                                510,
                                506,
                                501,
                                497,
                                493,
                                489,
                                485,
                                481,
                                477,
                                473,
                                469,
                                464,
                                460,
                                456,
                                452,
                                448,
                                444,
                                440,
                                436,
                                432,
                                428,
                                424,
                                420,
                                415,
                                411,
                                407,
                                403,
                                399,
                                395,
                                391,
                                387,
                                383,
                                379,
                                374,
                                370,
                                366,
                                362,
                                358,
                                354,
                                349,
                                345,
                                341,
                                337,
                                332,
                                328,
                                324,
                                320,
                                315,
                                311,
                                307,
                                302,
                                298,
                                293,
                                289,
                                284,
                                280,
                                275,
                                271,
                                266,
                                262,
                                257,
                                252,
                                248,
                                243,
                                238,
                                233,
                                228,
                                223,
                                218,
                                213,
                                208,
                                203,
                                198,
                                193,
                                188,
                                182,
                                177,
                                172,
                                166,
                                161,
                                155,
                                149,
                                143,
                                137,
                                131,
                                125,
                                119,
                                113,
                                107,
                                100,
                                93,
                                87,
                                80,
                                73,
                                66,
                                58,
                                51,
                                43,
                                35,
                                27,
                                19,
                                10,
                                1,
                                -8,
                                -18,
                                -27,
                                -38,
                                -48,
                                -60,
                                -71,
                                -83,
                                -96,
                                -110,
                                -125,
                                -140,
                                -157,
                                -175,
                                -195,
                                -217,
                                -242,
                                -271,
                                -306,
                                -348,
                                -406,
                                -497,       // 256
};



/**
 * @brief Calculates the temperature in Celsius from an ADC value
 *        of the NTC thermistor.
 *
 * @param[out] temp_celsius The calculated temperature in Celsius.
 * @param[in] adc_value The ADC value of the thermistor.
 * @param[in] adc_bits The number of bits of the ADC value.
 *
 * @return The temperature in Celsius.
 *
 * @note The ADC value is assumed to be a 12-bit value.
 *       The adc_bits parameter is used to scale the ADC value to an 8-bit index.
 *       The temperature is calculated by linear interpolation between two adjacent
 *       points in the ntc_table.
 *       The temperature is returned in tenths of a Celsius degree.
 */
int ntc_temp_calc(float* temp_celsius, uint16_t adc_value, uint8_t adc_bits)
{
    assert(temp_celsius != NULL);
    assert(adc_bits >= 8 && adc_bits <= 12);

    uint8_t shift = adc_bits - 8;
    uint16_t index = (adc_value >> shift) & 0xFF;

    int p1 = ntc_table[index];
    int p2 = ntc_table[index + 1];

    int temp = p1 + (((p2 - p1) * (adc_value & ((1 << shift) - 1))) >> shift);

    *temp_celsius = (float)temp / 10.0f;

    return temp;
}

/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/

