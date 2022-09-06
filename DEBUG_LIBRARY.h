#ifndef __DEBUG_LIBRARY_H_
#define __DEBUG_LIBRARY_H_

#include <stdio.h>



/* ---- Global Debug Switch 全局打印调试开关 ---- */

#define GENERAL_DEBUG	// 总开关

/*-- Simple style just Base on printf --*/
#define DEBUG_Simple_FUNCTION		// 简易的Debug函数 高性能
#define DEBUG_Professional_FUNCTION	// 专业的Debug函数 功能更强但资源开销更多

/* ---- 各个模块的日志输出的开关 ---- */
#define ALL_FACTORY_LOG
#define ALL_SURFER_LOG
#define ALL_TVSH_LOG
#define ALL_MPLAYER_LOG
#define ALL_EPG_LOG
#define ALL_GWIN_LOG
#define ALL_PIE_LOG



/* ---- Global Switch debug funciton Option ---- */

typedef enum{ 
  DEBUG_OFF = 0,
  DEBUG_ON,
}SWITCH_DEBUG_EN;	// Swtich Debug 函数的开关枚举


/* ---- Print tools ---- */

#if defined (DEBUG_Simple_FUNCTION)
#define print_1 printf  
#elif defined (DEBUG_Professional_FUNCTION)
#define print_2 fprintf
#else
#undef GENERAL_DEBUG
#endif

#if defined (print_1) 
#define log_print print_1		
#define log_file 
#elif defined (print_2)
#define log_pirnt print_2
#define log_file stderr,		// 指定Log输出路径
#endif


#ifdef GENERAL_DEBUG

#define STR_BOOL(bool)  ((bool)!=0 ? (#bool " is true") : (#bool " is false"))

#define BOOL_COMP(val, true, false)  ((val)==(true) ? (#val " = " #true) : \
			((val)==(false) ? (#val " = " #false) : (#val " = other") ))
			

/* ---- SWITCH 字符输出 ---- */
#define STR_SWITCH(val, switch_debug_en) \
		char *const str_switch_p_ = #val; \
		int str_switch_en_ = switch_debug_en
		
#define STR_CASE(val) do{ \
		if(str_switch_en_) log_print (log_file "[%s] switch(%s) to %s:\n", \
		__FUNCTION__, str_switch_p_, #val); }while(0)



#if defined(DEBUG_Simple_FUNCTION)

  /*-- Switch printf Debug Integer only --*/

#define SWITCH_START(switch_val, case_val, switch_debug_en) do{	\
		char const *_var_str = #switch_val;	\
		int _val = switch_val;	\
		if (!switch_debug_en) break;	\
		switch (switch_val)	{	SWITCH_CASE(case_val)

#define SWITCH_CASE(case_val) case (case_val): \
				log_print(log_file "[DEBUG] (%s): %s = %s[%d] .\n", __FUNCTION__, \
				_var_str, #case_val, case_val);	break

#define SWITCH_END(case_val) SWITCH_CASE(case_val); default: log_print\
		(log_file "[DEBUG] (%s): %s[%d] = other.\n", __FUNCTION__, _var_str, _val); }	\
		}while(0)

#elif defined(DEBUG_Professional_FUNCTION)

  /*--- Switch printf Debug ---*/
#define SWITCH_START(switch_val, case_val, switch_debug_en) do{	\
		char const *_var_str = #switch_val;	\
		auto _val = switch_val;	\
		if (!switch_debug_en) break;	\
		if ((_val) == (case_val))	{	\
			log_print(log_file "[DEBUG] (%s): %s = %s[%d] .\n", __FUNCTION__, _var_str, #case_val, case_val)

#define SWITCH_CASE(case_val) } else if ((_val) == (case_val))	 { \
		log_print(log_file "[DEBUG] (%s): %s = %s[%d] .\n", __FUNCTION__, _var_str, #case_val, case_val)

#define SWITCH_END(case_val) SWITCH_CASE(case_val);	\
 		} else { log_print	(log_file \
 		"[DEBUG] (%s): %s[%d] = other.\n", __FUNCTION__, _var_str, _val); }	\
		}while(0)

#endif


/* ---- 检查返回值 ---- */

#if defined(DEBUG_Simple_FUNCTION)
#define CHECK_RET(ret, min, max)  ( int __flg__=0, _temp_ = ret;\
		if ((_temp_) < (min) || (_temp_) > (max)) { log_print (log_file 	\
			"[RET] (%s)=%d %s %d! In line[%d] of file[%s].\n", #ret, (_temp_ < min ? "<" : ">"), \
			(_temp_ < min ? min : max), __LINE__, __FILE__); 	__flg__=1;	}\
		__flg__; )
#elif defined(DEBUG_Professional_FUNCTION)
  /*-- Professional provide a feature that you can use function directly instead of "ret" variables. --*/
#define CHECK_RET(ret, min, max)  ({ auto _temp_ = ret; int __flg__=0;\
		if (max < min) {	\
			if (_temp_ < (max) || _temp_ > (min)) { log_print (log_file 	\
			"[RET] (%s)=%d %s %d! In line[%d] of file[%s].\n", #ret, (_temp_ < max ? "<" : ">"), \
			(_temp_ < max ? max : min), __LINE__, __FILE__);	 __flg__=1; }\
		} else if (_temp_ < (min) || _temp_ > (max)) { log_print (log_file 	\
			"[RET] (%s)=%d %s %d! In line[%d] of file[%s].\n", #ret, (_temp_ < min ? "<" : ">"), \
			(_temp_ < min ? min : max), __LINE__, __FILE__);	 __flg__=1; }\
		__flg__; })
#endif


/* ---- 带标签的Debug输出 ---- */

#if defined(DEBUG_Simple_FUNCTION)
#define DEBUG_TAG(info) do{ \
		log_print (log_file "[DEBUG] (%s):in file[%s] line[%d]" \
		"-- %s.\n", info, __FILE__, __LINE__, __FUNCTION__); \
		}while(0)
#elif defined(DEBUG_Professional_FUNCTION)
#define DEBUG_TAG(info, arg...) do{ char _buf_[128]={0}; \
		snprintf (_buf_, sizeof(_buf_),   info, ##arg); \
		log_print (log_file "[DEBUG] (%s):in file[%s] line[%d]" \
		"-- %s.\n", _buf_, __FILE__, __LINE__, __FUNCTION__); \
		}while(0)
#endif


#else	/* ifndef GENERAL_DEBUG */

#define STR_BOOL(bool) 
#define BOOL_COMP(val, true, false) 

#define STR_SWITCH(val, CASE_DEBUG_EN) 
#define STR_CASE(val)

#define SWITCH_START(switch_val, case_val, switch_debug_en)  
#define SWITCH_CASE(case_val) 
#define SWITCH_END(case_val) 

#define CHECK_RET(ret, min, max) 
#define DEBUG_POSITION(info, arg...) 

#endif

/* ---- Print tools End ---- */


/* ---- Global Debug Print ---- */

#ifdef GENERAL_DEBUG

#define general_log(module_name, fmt, args...) log_print (log_file \
				"[%s]%s : " fmt " .\n", #module_name, __FUNCTION__, ##args)

#if defined(DEBUG_Simple_FUNCTION)
#define general_memory_log(module_name, addr, size) do{  \
		int i=0, _size_ = (int)(size); unsigned char *_temp_ = (void *)(addr);	\
		log_print (log_file "[%s]%s : (%s)'s memory(addr:%p, len:%d): { ",	\
				#module_name, __FUNCTION__,    #addr, _temp_, _size_);	\
		while (i<_size_) log_print (log_file "%2x, ", _temp_[i++]);		\
		log_print (log_file "}\n");	}while(0)
#elif defined(DEBUG_Professional_FUNCTION)
#define general_memory_log(module_name, addr, size) do{  \
		size_t i=0, j, _size_=(size_t)(size); unsigned char *_temp_ = (void *)(addr);	\
		if (_temp_ == NULL || _size_ <= 0) break;	\
		log_print (log_file "[%s]%s : (%s)'s memory(addr:%p, len:%d): {\n", \
				#module_name, __FUNCTION__,    #addr, _temp_, _size_);	\
		while (i<_size_) {	log_print (log_file "\t");	\
			for (j=0; j<12 && i<_size_; j++) {	\
				log_print (log_file "%2x ", _temp_[i++]);	\
			}	log_print (log_file "\n");	\
		}	log_print (log_file "\t}\n");	\
		}while(0)
#endif
		
#else	/* ifndef GENERAL_DEBUG */
#define general_log(module_name, fmt, args...) 
#define general_memory_log(module_name, addr, size) 
#endif



#ifdef ALL_FACTORY_LOG
#define factory_log(fmt, args...) 	general_log(FACTORY, fmt, ##args)
#define factory_hex_log(addr, size) 	general_memory_log(FACTORY, addr, size)
#else
#define factory_log(fmt, args...)
#define factory_hex_log(addr, size) 
#endif 

#ifdef ALL_TVSH_LOG
#define tvsh_log(fmt, args...) 		general_log(TVSH, fmt, ##args)
#define tvsh_hex_log(addr, size) 	general_memory_log(TVSH, addr, size)
#else
#define tvsh_log(fmt, args...) 
#define tvsh_hex_log(addr, size) 
#endif

#ifdef ALL_SURFER_LOG
#define surfer_log(fmt, args...) 	general_log(SURFER, fmt, ##args)
#define surfer_hex_log(addr, size) 	general_memory_log(SURFER, addr, size)
#else
#define surfer_log(fmt, args...) 
#define surfer_hex_log(addr, size) 
#endif

#ifdef ALL_MPLAYER_LOG
#define mp_log(fmt, args...) 		general_log(MP, fmt, ##args)
#define mp_hex_log(addr, size) 		general_memory_log(MP, addr, size)
#else
#define mp_log(fmt, args...) 
#define mp_hex_log(addr, size) 
#endif

#ifdef ALL_EPG_LOG
#define epg_log(fmt, args...) 		general_log(EPG, fmt, ##args)
#define epg_hex_log(addr, size) 	general_memory_log(EPG, addr, size)
#else
#define epg_log(fmt, args...) 
#define epg_hex_log(addr, size) 
#endif

#ifdef ALL_GWIN_LOG
#define gwin_log(fmt, args...) 		general_log(GWIN, fmt, ##args)
#define gwin_hex_log(addr, size) 	general_memory_log(GWIN, addr, size)
#else
#define gwin_log(fmt, args...) 
#define gwin_hex_log(addr, size) 
#endif

#ifdef ALL_PIE_LOG
#define pie_log(fmt, args...) 		general_log(PIE, fmt, ##args)
#define pie_hex_log(addr, size) 	general_memory_log(PIE, addr, size)
#else
#define pie_log(fmt, args...) 
#define pie_hex_log(addr, size) 
#endif

/* ---- Global Debug Print End ---- */

#endif /*--  __DEBUG_LIBRARY_H_ --*/
