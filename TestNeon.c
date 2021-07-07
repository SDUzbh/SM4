#include "TestFuns.h"
#include "SM4_neon.h"
#include "SM4_Std.h"
#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

static const u8i Sm4ALIGN(  akey[SM4_BLOCK_SIZE] )= { 0x01,0x23,0x45,0x67, 0x89,0xab,0xcd,0xef,   0xfe,0xdc,0xba,0x98, 0x76,0x54,0x32,0x10 };
static const u8i Sm4ALIGN(  refpl[SM4_BLOCK_SIZE] )= { 0x01,0x23,0x45,0x67, 0x89,0xab,0xcd,0xef,   0xfe,0xdc,0xba,0x98, 0x76,0x54,0x32,0x10 };
static const u8i Sm4ALIGN( refcp[SM4_BLOCK_SIZE] )={   0x68 ,0x1e ,0xdf ,0x34 ,0xd2 ,0x06 ,0x96 ,0x5e ,0x86 ,0xb3 ,0xe9 ,0x4f ,0x53 ,0x6e ,0x42 ,0x46};
static const u8i Sm4ALIGN( refcp1000000[SM4_BLOCK_SIZE] )={0x59 ,0x52 ,0x98 ,0xc7 ,0xc6 ,0xfd ,0x27 ,0x1f ,0x04 ,0x02 ,0xf8 ,0x04 ,0xc3 ,0x3d ,0x3f ,0x66};
static unsigned char Sm4ALIGN(iv[16])={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};

u64i difftimeval(const struct timeval *start, const struct timeval *end)
{
        u64i d;
        time_t s;
        suseconds_t u;

        s = start->tv_sec - end->tv_sec;
        u = start->tv_usec - end->tv_usec;
        //if (u < 0)
        //        --s;

        d = s;
        d *= 1000000;//1 秒 = 10^6 微秒
        d += u;

        return d;
}

int main()
{
  u8i Sm4ALIGN(out[16]);
  u8i Sm4ALIGN(rec[16]);
  u8i Sm4ALIGN(outsimd[2048000]);
  u8i Sm4ALIGN(recsimd[2048000]);
  u8i Sm4ALIGN(refplsimd[2048000]);
  uint8x16_t RKsimd[32];
  u32i RK[32]; 
TestAllfuns();
		KeySchedule_SM4(akey, RK);
	KeySchedule_SM4_Neon(akey, RKsimd);
SM4_CTX_Std mySM4CTX;
 
 for(int i=0;i<256;i++)
	  refplsimd[i]= i;
  memcpy( refplsimd, refpl, 16);
  Init_SM4CTX(&mySM4CTX, akey, iMODE_SM4_CBC,iv);
 // Init_SM4CTX(&mySM4CTX, akey, iMODE_SM4_ECB,NULL);
  SM4_EncNeon_ECB(outsimd, refplsimd,256,&mySM4CTX);
  for(int i=0;i<256;i++)
  {
    printf("%02x", outsimd[i]);

	if((i+1)%32==0)
    printf("\n");
	else if((i+1)%16==0)
    printf(" ");
  }
  printf("ENC NEON TEST __%s\n", memcmp(outsimd, refcp,16)?"FAIL":"PASS");
  _Enc_SM4_TBox( refpl, RKsimd ,out );
  printf("ENC TBOX TEST __%s\n", memcmp(out, refcp,16)?"FAIL":"PASS");
   SM4_DecNeon_ECB(recsimd, outsimd,256,&mySM4CTX);
    for(int i=0;i<256;i++)
  {
    printf("%02x", recsimd[i]);

	if((i+1)%32==0)
    printf("\n");
	else if((i+1)%16==0)
    printf(" ");
  }
   printf("DEC NEON TEST __%s\n", memcmp(recsimd, refpl,16)?"FAIL":"PASS");
  _Dec_SM4_TBox( refcp, RKsimd ,rec );
  printf("DEC TBOX TEST __%s\n", memcmp(rec, refpl,16)?"FAIL":"PASS");

   // 1000000 times
   for(int i=0;i<1000000 ;i++)
   _Enc_SM4_Neon( recsimd, RKsimd ,recsimd );
   printf("ENC NEON 1000000 Times __%s\n", memcmp(recsimd, refcp1000000,16)?"FAIL":"PASS");
  for(int i=0;i<1000000 ;i++)
   _Enc_SM4_TBox( rec, RKsimd ,rec );
   printf("ENC TBOX 1000000 Times __%s\n", memcmp(rec, refcp1000000,16)?"FAIL":"PASS");

   for(int i=0;i<256;i++)
	  refplsimd[i]= i;
  memcpy( refplsimd, refpl, 16);
  u64i msize=2048000;
  u64i loops=100;//5000000;
  	u64i begintime;
	u64i endtime;

   begintime = clock();
  for(int i=0;i<loops;i++)
  {
	   SM4_EncStd_CTR_Normal( outsimd, recsimd,RK , iv,msize);
//	  SM4_EncNeon_ECB(recsimd, outsimd,msize,&mySM4CTX);
  }
   endtime=clock();
 endtime=(endtime- begintime) ;
 u64i Totbits= loops*msize*8;
  printf("STD  time %lu ms, speed is %lu MBps/s\n",  endtime/1000, Totbits/ endtime);
  for(int i=0;i<256;i++)
  {
    printf("%02x", outsimd[i]);

	if((i+1)%32==0)
    printf("\n");
	else if((i+1)%16==0)
    printf(" ");
  }

	
   begintime = clock();
  for(int i=0;i<loops;i++)
  {
	 SM4_EncStd_CTR(recsimd, outsimd,msize,&mySM4CTX);
//	  SM4_EncNeon_ECB(recsimd, outsimd,msize,&mySM4CTX);
  }
   endtime=clock();
 endtime=(endtime- begintime) ;
  Totbits= loops*msize*8;
  printf("TBOX time %lu ms, speed is %lu MBps/s\n",  endtime/1000, Totbits/ endtime);
  for(int i=0;i<256;i++)
  {
    printf("%02x", outsimd[i]);

	if((i+1)%32==0)
    printf("\n");
	else if((i+1)%16==0)
    printf(" ");
  }

	
   begintime = clock();
  for(int i=0;i<loops;i++)
  {
	    SM4_EncNeon_ECB(recsimd, outsimd,msize,&mySM4CTX);
  }
   endtime=clock();
 endtime=(endtime- begintime) ;
  Totbits= loops*msize*8;
  printf("NEON time %lu ms, speed is %lu MBps/s\n",  endtime/1000, Totbits/ endtime);
  for(int i=0;i<256;i++)
  {
    printf("%02x", outsimd[i]);

	if((i+1)%32==0)
    printf("\n");
	else if((i+1)%16==0)
    printf(" ");
  }

  begintime = clock();
  for(int i=0;i<loops;i++)
  {
     //SM4_DecStd_CBC(recsimd, outsimd,msize,&mySM4CTX);
	 SM4_EncNeon_CTR(recsimd, outsimd,msize,&mySM4CTX);
	 //SM4_EncStd_ECB(recsimd, outsimd,msize,&mySM4CTX);
  }
   endtime=clock();
 endtime=(endtime- begintime) ;
   Totbits= loops*msize*8;
  printf("time %lu ms, speed is %lu MBps/s\n",  endtime/1000, Totbits/ endtime);
  for(int i=0;i<256;i++)
  {
    printf("%02x", outsimd[i]);

	if((i+1)%32==0)
    printf("\n");
	else if((i+1)%16==0)
    printf(" ");
  }
  u32i *MassMemory;
  u32i *OMassMemory;

  u8i *pmem;
  u8i *opmem;

  msize= 1024*1000*240;
  MassMemory = (u32i *)malloc(msize * sizeof(u32i));
  OMassMemory = (u32i *)malloc(msize * sizeof(u32i));

  pmem=MassMemory;
  opmem=OMassMemory;
  struct timeval start,end;
  msize =msize*4;
 Totbits= msize*8;
time_t t;
	struct tm *timeinfo;  //结构体
	time(&t);	timeinfo = localtime(&t);	printf("  ______%s\n", asctime(timeinfo));

 gettimeofday(&start, NULL);
 // change NoSUBBlocks for testing
 #define NoSUBBlocks 4
 u64i Sizesubblock=  msize/NoSUBBlocks;

 #pragma omp parallel for
	for(u64i i=0;i<NoSUBBlocks;i++)
	{ 
	 SM4_EncNeon_CTR_Parallel( opmem+i*Sizesubblock , pmem+i*Sizesubblock, Sizesubblock, mySM4CTX.T_RK , mySM4CTX.IV, i*Sizesubblock); 
	}
 gettimeofday(&end, NULL);
 endtime=difftimeval(&end, &start);

  printf("PAR time %lu ms, speed is %lu MBps/s\n",  endtime/1000, Totbits/ endtime);
	time(&t);	timeinfo = localtime(&t);	printf("  ______%s\n", asctime(timeinfo));
gettimeofday(&start, NULL);
 	 SM4_EncNeon_CTR(opmem, pmem,msize,&mySM4CTX);
 gettimeofday(&end, NULL);
 endtime=difftimeval(&end, &start);
  printf("STD time %lu ms, speed is %lu MBps/s\n",  endtime/1000, Totbits/ endtime);
 	time(&t);	timeinfo = localtime(&t);	printf("  ______%s\n", asctime(timeinfo));
 free(MassMemory);
  free(OMassMemory);
    return 0;
}
