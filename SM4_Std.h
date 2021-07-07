#ifndef _H_SM4_STD_
#define _H_SM4_STD_
#include <stdio.h>
#include <stdint.h>

#ifndef u8i 
#define  u8i unsigned char
#endif 

#ifndef u32i 
#define  u32i uint32_t 
#endif


#ifndef u64i 
#define  u64i uint64_t 
#endif

#define SM4_BLOCK_SIZE 16

#ifdef  __GNUC__
   #define __SM4ALIGNN(n, A) A  __attribute__ ((aligned (n)) )
#elif _MSC_VER 
   #define __SM4ALIGNN(n, A)  __declspec( align(n) ) A
#elif __BORLANDC__
   #define __SM4ALIGNN(n, A)  __declspec( align(n) ) A
#endif 

#define Sm4ALIGN(A)  __SM4ALIGNN(4,A)  
/*
typedef struct _SM4_CTX_Std {
  u32i T_RK[32]; 
  u8i Sm4ALIGN(IV[16]); 
} SM4_CTX_Std;

*/
  
  #define SM4_DecStd_OFB_Normal SM4_EncStd_OFB_Normal 
  #define SM4_DecStd_CTR_Normal SM4_EncStd_CTR_Normal 
  
  
  void KeySchedule_SM4(const u8i *key, u32i *rk);
  void Enc_SM4_Normal(u8i *pt, u32i *rk, u8i *out);
  void Dec_SM4_Normal(u8i *cp,u32i *rk, u8i *out); 
u64i SM4_EncStd_ECB_Normal(unsigned char *out, unsigned char *in,const u32i *rk,const  u64i datalen);
u64i SM4_DecStd_ECB_Normal(unsigned char *out, unsigned char *in,const u32i *rk,const  u64i datalen);
u64i SM4_EncStd_CBC_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_DecStd_CBC_Normal(unsigned char *out, unsigned char *in, const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_EncStd_OFB_Normal(unsigned char *out, unsigned char *in, const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_EncStd_CFB128_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_DecStd_CFB128_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_EncStd_CFB64_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_DecStd_CFB64_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_EncStd_CFB8_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_DecStd_CFB8_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_EncStd_CFB1_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
u64i SM4_DecStd_CFB1_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);

u64i SM4_EncStd_CTR_Normal(unsigned char *out, unsigned char *in,const u32i *rk, const u8i *IV,const  u64i datalen);
 
#endif
