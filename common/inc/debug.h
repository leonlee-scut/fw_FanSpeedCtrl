/**
  * @file debug.h
  * @brief 
  * @author Leon Lee (leonlee.scut@gmail.com)
  * @version 0.1
  * @date 2023/05/09
  * 
  * @copyright Copyright (c) 2023 South China University of Technology.
  * All rights reserved.
  * 
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * 
  * @par History:
  * 	Date		Version		Author			Description
  * 	2023/05/09	0.1			Leon Lee		Preliminary version.
  */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

#if !defined(NDEBUG)
#define debug(fmt, args...)                 printf(fmt, ##args) 
#define debug_if(cond, fmt, args...)        if(cond) printf(fmt, ##args)
#else
#define debug(fmt, ...)
#define debug_if(cond, fmt, ...)
#endif // !defined(NDEBUG)

// void debug_print(const char *const fmt, ...);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // __DEBUG_H__
/************* (C) COPYRIGHT South China Univ. of Tech. ****** END OF FILE ****/
