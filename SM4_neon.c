#include"SM4_neon.h"


#ifdef __cplusplus
extern "C" {
#endif
	void KeySchedule_SM4_Neon(const u8i* key, uint8x16_t* RK) {

	}

	void _Enc_SM4_TBox(u8i* pt, uint8x16_t* RK, u8i* out) {
	
	}

	void _Dec_SM4_TBox(u8i* cp, uint8x16_t* RK, u8i* out) {

	}

	void _Enc_SM4_Neon(u8i* pt, uint8x16_t* RK, u8i* out) {

	}

	void _Dec_SM4_Neon(u8i* cp, uint8x16_t* RK, u8i* out) {

	}

	u64i SM4_EncNeon_CTR_Parallel(unsigned char* out, unsigned char* in, const  u64i datalen, uint8x16_t* T_RK, u8i* IV, u64i ioutset) {

	}

	u64i SM4_EncStd_CTR_Parallel(unsigned char* out, unsigned char* in, const  u64i datalen, uint8x16_t* T_RK, u8i* IV, u64i ioutset) {

	}

	u64i Init_SM4CTX(SM4_CTX_Std* ctx, u8i* mk, const u32i mode, u8i* iv) {

	}

	void UpdateIV_SM4CTX(SM4_CTX_Std* ctx, u8i* iv) {

	}

	void UpdateMODE_SM4CTX(SM4_CTX_Std* ctx, u32i mode) {

	}

	void UpdateRK_SM4CTX(SM4_CTX_Std* ctx, u8i* mk) {

	}

	void Clear_SM4CTX(SM4_CTX_Std* ctx) {

	}
	
	void GetSoftWareInfo(char* info) {

	}

#ifdef __cplusplus
}
#endif // __cplusplus
