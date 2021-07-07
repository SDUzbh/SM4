#ifndef _H_SM4_NEON_
#define _H_SM4_NEON_

#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h> //必须


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



  #ifdef __cplusplus
extern "C" {
#endif
//1 轮密钥生成函数
// input: key 16字节主密钥
// output: RK  uint8x16_t [32]
void KeySchedule_SM4_Neon( const u8i *key,uint8x16_t * RK );
//2 T盒 加密核心函数
// input: pt 明文 16字节  要求4字节对齐
//        RK 轮密钥
// output: out 密文  16字节  要求4字节对齐
void _Enc_SM4_TBox(u8i *pt, uint8x16_t *RK, u8i *out);
//3 T盒 解密核心函数
// input: cp 密文 16字节 要求4字节对齐
//        RK 轮密钥
// output: out 明文  16字节  要求4字节对齐
void _Dec_SM4_TBox(u8i *cp, uint8x16_t *RK, u8i *out);
//4 neon 加密核心函数
// input: pt 明文 256字节 要求4字节对齐
//        RK 轮密钥
// output: out 密文  256字节  要求4字节对齐
void _Enc_SM4_Neon(u8i *pt, uint8x16_t *RK, u8i *out);
//5 neon 解密核心函数
// input: cp 密文 256字节 要求4字节对齐
//        RK 轮密钥
// output: out 明文 256字节  要求4字节对齐
void _Dec_SM4_Neon(u8i *cp, uint8x16_t *RK, u8i *out);


#define SM4_ENCRYPT 0
#define SM4_DECRYPT 1


typedef struct _SM4_CTX_Std {
  uint8x16_t T_RK[32];//8*16
  u8i Sm4ALIGN(IV[16]);
  u32i iMode;
} SM4_CTX_Std;

#define iMODE_SM4_ECB 1
#define iMODE_SM4_CBC 2
#define iMODE_SM4_OFB 4
#define iMODE_SM4_CFB128 8
#define iMODE_SM4_CFB64 16
#define iMODE_SM4_CFB8 32
#define iMODE_SM4_CFB1 64
#define iMODE_SM4_CTR 128
#define iMODE_IV_MASK 0x00FE
#define iMODE_WITH_IV  iMODE_IV_MASK  //任意需要IV的模式

#define SM4_DecStd_OFB SM4_EncStd_OFB
#define SM4_DecStd_CTR SM4_EncStd_CTR
#define SM4_DecNeon_CTR SM4_EncNeon_CTR
#define SM4_DecNeon_CTR_Parallel SM4_EncNeon_CTR_Parallel
#define SM4_DecStd_CTR_Parallel SM4_EncStd_CTR_Parallel
void KeySchedule_SM4(const u8i *key, u32i *rk);
void Enc_SM4(u8i *pt, u32i *rk, u8i *out);
void Dec_SM4(u8i *cp,u32i *rk, u8i *out);

u64i SM4_EncStd_ECB(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncNeon_ECB(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecStd_ECB(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecNeon_ECB(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_CBC(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecStd_CBC(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecNeon_CBC(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_OFB(unsigned char *out, unsigned char *in, const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_CFB128(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecStd_CFB128(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_CFB64(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecStd_CFB64(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_CFB8(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecStd_CFB8(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_CFB1(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_DecStd_CFB1(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncStd_CTR(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncNeon_CTR(unsigned char *out, unsigned char *in,const  u64i datalen,SM4_CTX_Std * ctx_sm4);
u64i SM4_EncNeon_CTR_Parallel(unsigned char *out, unsigned char *in,const  u64i datalen, uint8x16_t *T_RK, u8i *IV,u64i ioutset);
u64i SM4_EncStd_CTR_Parallel(unsigned char *out, unsigned char *in,const  u64i datalen, uint8x16_t *T_RK, u8i *IV, u64i ioutset);

u64i Init_SM4CTX(SM4_CTX_Std *ctx, u8i *mk, const u32i mode, u8i *iv  );
void UpdateIV_SM4CTX(SM4_CTX_Std *ctx,u8i *iv );
void UpdateMODE_SM4CTX(SM4_CTX_Std *ctx,u32i mode);
void UpdateRK_SM4CTX(SM4_CTX_Std *ctx,u8i *mk );
void Clear_SM4CTX(SM4_CTX_Std *ctx);
void GetSoftWareInfo(char *info);
#ifdef __cplusplus
}
#endif
#endif
