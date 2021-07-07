#ifndef _H_SM4TestFuns_
#define _H_SM4TestFuns_ 
#include <stdio.h>
#include <stdint.h>
#include <string.h>
  #ifdef __cplusplus
extern "C" {
#endif

int Test_SM4ECB(void); 
int Test_SM4CBC(void);
int Test_SM4OFB(void);  
int Test_SM4CFB128(void);  
int Test_SM4CFB64(void);   
int Test_SM4CFB8(void);   
int Test_SM4CFB1(void);   
int Test_SM4CTR(void);   
int TestAllfuns(void);




#ifdef __cplusplus
}
#endif
#endif
