//#include <string.h>
#include "mi_config.h"

#include "mible_api.h"
#undef  MI_LOG_MODULE_NAME
#define MI_LOG_MODULE_NAME "crypto"
#include "mible_log.h"

#include "mi_mesh_otp.h"
#include "mi_crypto.h"
#include "mi_crypto_backend_msc.h"
#include "mi_crypto_backend_mbedtls.h"
#include "mi_crypto_backend_uECC.h"
#include "third_party/pt/pt.h"
#include "third_party/mbedtls/ccm.h"
#include "third_party/mbedtls/sha256_hkdf.h"

#if MI_API_ENABLE
#define CRYPTO_REC_ID_BASE   0x40

#if (HAVE_MSC == 0)
static __ALIGN(4) ecc256_sk_t dev_crt_sk;
static __ALIGN(4) ecc256_sk_t dev_sk;
static void keygen(uint8_t k[16])
{
    memset(k, 0, 16);
    mible_gap_address_get(k);
    mible_aes128_encrypt(k, k, 16, k);
}
// for certify part 
#define DEMO_CERT_TYPE0	0//telink
#define DEMO_CERT_TYPE1	1//leishi
#define DEMO_CERT_TYPE2	2
#define DEMO_CERT_TYPE3	3
#define DEMO_CERT_TYPE4	4
#define DEMO_CERT_TYPE5	5

#define DEMO_CERT_TYPE 	DEMO_CERT_TYPE1

#if MI_IOT_TELINK_MODE
	#if (DEMO_CERT_TYPE == DEMO_CERT_TYPE0)
unsigned char dev_mac_address[]={0x7C,0x49,0xEB,0x00,0x00,0x0B};
const unsigned char dev_cert_pri[32] = {    
    0x57,0x42,0x05,0xE4,0xEF,0x11,0x23,0xE4,0x25,0xCD,0x9E,0xA6,0x5B,0x8D,0x33,0x9F,
    0x6D,0xD7,0x18,0x1A,0x4C,0x35,0xF5,0xCF,0x56,0xC1,0x17,0x5C,0x5F,0x2C,0x7B,0x70,};
const unsigned char demo_certificate[]={
	0x30,0x82,0x01,0x99,0x30,0x82,0x01,0x3E,0xA0,0x03,0x02,0x01,0x02,0x02,0x04,0x3C,
    0xCB,0xF7,0x0B,0x30,0x0C,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x02,0x05,
    0x00,0x30,0x2B,0x31,0x1C,0x30,0x1A,0x06,0x03,0x55,0x04,0x0A,0x13,0x13,0x4D,0x69,
    0x6A,0x69,0x61,0x20,0x4D,0x61,0x6E,0x75,0x66,0x61,0x63,0x74,0x75,0x72,0x65,0x20,
    0x32,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x43,0x4E,0x30,0x20,
    0x17,0x0D,0x31,0x37,0x30,0x38,0x30,0x39,0x31,0x37,0x34,0x38,0x35,0x38,0x5A,0x18,
    0x0F,0x32,0x30,0x36,0x37,0x30,0x37,0x32,0x38,0x31,0x37,0x34,0x38,0x35,0x38,0x5A,
    0x30,0x35,0x31,0x15,0x30,0x13,0x06,0x03,0x55,0x04,0x0A,0x13,0x0C,0x4D,0x69,0x6A,
    0x69,0x61,0x20,0x44,0x65,0x76,0x69,0x63,0x65,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,
    0x04,0x06,0x13,0x02,0x43,0x4E,0x31,0x0F,0x30,0x0D,0x06,0x03,0x55,0x04,0x0B,0x13,
    0x06,0x66,0x74,0x73,0x61,0x66,0x65,0x30,0x59,0x30,0x13,0x06,0x07,0x2A,0x86,0x48,
    0xCE,0x3D,0x02,0x01,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,0x03,0x42,
    0x00,0x04,0xD2,0x07,0x20,0x71,0x54,0xCC,0xB7,0x57,0xE0,0x5F,0x29,0x6F,0xF6,0xE8,
    0x4C,0xCC,0x74,0x09,0xB0,0x52,0xF7,0x20,0x5B,0x29,0x41,0x5F,0xAF,0xB5,0x66,0xFE,
    0xBB,0x5E,0xB5,0x78,0x77,0x79,0x9C,0xBB,0x79,0xBC,0x70,0x4D,0x76,0x33,0x3E,0x1E,
    0x9C,0xA9,0x2D,0x9A,0xB9,0xD6,0xF5,0x86,0x79,0x64,0x3D,0xF4,0x18,0x79,0xB4,0xC7,
    0x66,0x60,0xA3,0x42,0x30,0x40,0x30,0x1D,0x06,0x03,0x55,0x1D,0x0E,0x04,0x16,0x04,
    0x14,0x4A,0x89,0x87,0x3C,0x8D,0xF8,0x0D,0x46,0xE8,0x46,0xB8,0x09,0xBC,0x19,0x0B,
    0x17,0xF8,0x9B,0xC6,0x8F,0x30,0x1F,0x06,0x03,0x55,0x1D,0x23,0x04,0x18,0x30,0x16,
    0x80,0x14,0xFD,0xEF,0xAB,0x24,0x54,0x64,0xBA,0x88,0xBD,0x04,0x90,0xAF,0xBB,0x5B,
    0x4B,0x07,0x8F,0x7B,0x49,0xB7,0x30,0x0C,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,
    0x03,0x02,0x05,0x00,0x03,0x47,0x00,0x30,0x44,0x02,0x20,0x39,0x68,0xCF,0x2A,0xCF,
    0x2E,0xD3,0x6C,0x04,0x91,0x54,0xBA,0x1D,0xBE,0x5E,0xF1,0x41,0x80,0x89,0xB3,0x6A,
    0xBD,0xF5,0xFB,0xA7,0xD3,0x45,0x4F,0x26,0xCB,0x78,0xF0,0x02,0x20,0x0E,0xAA,0x73,
    0x80,0x48,0xB8,0xC2,0xEE,0xE5,0x63,0xBD,0xDE,0x01,0xD5,0x1E,0x85,0xE3,0x4B,0xCC,
    0x89,0x81,0xA1,0x38,0x89,0x2C,0x2A,0x12,0x1B,0x23,0x59,0x1B,0x59,
};
	#elif(DEMO_CERT_TYPE == DEMO_CERT_TYPE1)

unsigned char dev_mac_address[]={0x4F, 0x01, 0x00, 0xBE, 0xBE, 0x8C};
const unsigned char dev_cert_pri[32] = {	
		0x07,0xED,0xC2,0xAF,0x05,0x98,0x1B,0x25,0x45,0x35,0x09,0x87,0x20,0x67,0x90,0x2F,
		0xF0,0x3A,0xBF,0x28,0x0B,0xA4,0xD3,0x7A,0x0E,0x38,0x4E,0xD1,0xC2,0x5D,0x6F,0x3D};
const unsigned char demo_certificate[]={
	0x30, 0x82, 0x01, 0x99, 0x30, 0x82, 0x01, 0x3E, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x04, 0x3C,
	0xCB, 0xF7, 0x12, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x05,
	0x00, 0x30, 0x2B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x13, 0x4D, 0x69,
	0x6A, 0x69, 0x61, 0x20, 0x4D, 0x61, 0x6E, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x20,
	0x32, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x30, 0x20,
	0x17, 0x0D, 0x31, 0x37, 0x30, 0x38, 0x30, 0x39, 0x31, 0x37, 0x34, 0x39, 0x35, 0x30, 0x5A, 0x18,
	0x0F, 0x32, 0x30, 0x36, 0x37, 0x30, 0x37, 0x32, 0x38, 0x31, 0x37, 0x34, 0x39, 0x35, 0x30, 0x5A,
	0x30, 0x35, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x0C, 0x4D, 0x69, 0x6A,
	0x69, 0x61, 0x20, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55,
	0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13,
	0x06, 0x66, 0x74, 0x73, 0x61, 0x66, 0x65, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48,
	0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42,
	0x00, 0x04, 0xA8, 0x57, 0xCD, 0x30, 0x4C, 0x9E, 0x28, 0xB5, 0x94, 0x64, 0x22, 0x46, 0xDE, 0xDF,
	0xA5, 0x88, 0x5F, 0xC6, 0xD2, 0x59, 0x05, 0xA5, 0x5F, 0xB4, 0x11, 0xD1, 0x7A, 0x5A, 0x99, 0x45,
	0x18, 0x18, 0x68, 0x9B, 0x19, 0x06, 0x1C, 0xED, 0xFF, 0x17, 0x33, 0x2C, 0x14, 0xF9, 0xF3, 0x30,
	0x1A, 0x58, 0x13, 0xAB, 0xB3, 0xDC, 0x7F, 0xDB, 0x83, 0x95, 0x34, 0xCC, 0xD7, 0x0E, 0x0A, 0x44,
	0x76, 0xEE, 0xA3, 0x42, 0x30, 0x40, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04,
	0x14, 0x0E, 0xD9, 0xDF, 0x73, 0x97, 0xFE, 0x88, 0x6F, 0x9A, 0xA1, 0x68, 0x6C, 0xA1, 0xEF, 0xA3,
	0x81, 0x6E, 0x9B, 0xCF, 0x2D, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16,
	0x80, 0x14, 0xFD, 0xEF, 0xAB, 0x24, 0x54, 0x64, 0xBA, 0x88, 0xBD, 0x04, 0x90, 0xAF, 0xBB, 0x5B,
	0x4B, 0x07, 0x8F, 0x7B, 0x49, 0xB7, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04,
	0x03, 0x02, 0x05, 0x00, 0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x27, 0x51, 0xB8, 0x98, 0x07,
	0x61, 0xCD, 0x24, 0x61, 0xB6, 0x56, 0x27, 0x0B, 0xE2, 0xBF, 0x67, 0x04, 0x6F, 0x21, 0x9C, 0xB9,
	0x5D, 0x9E, 0xE5, 0xB8, 0x67, 0x1E, 0x95, 0x77, 0x5F, 0x88, 0x7A, 0x02, 0x20, 0x23, 0x6E, 0xF4,
	0xB3, 0xE5, 0x27, 0x4D, 0x54, 0x4C, 0x99, 0xA6, 0x72, 0x07, 0xB4, 0x31, 0x54, 0xD5, 0x65, 0x02,
	0xD0, 0xCD, 0x82, 0x75, 0x56, 0xC7, 0xF8, 0xAF, 0x91, 0x76, 0x88, 0x1F, 0x3E
	};
	#elif(DEMO_CERT_TYPE == DEMO_CERT_TYPE2)
unsigned char dev_mac_address[]={0x4B, 0x01, 0x00, 0xBE, 0xBE, 0x8C};
const unsigned char dev_cert_pri[32] = {	
	0x20, 0x29, 0x4E, 0x1A, 0xF4, 0xE5, 0x7B, 0x70, 0x53, 0x05, 0x8F, 0xB8, 0xAA, 0xAC, 0x2D, 0xE1,
	0xE5, 0xE3, 0xBD, 0x27, 0x3F, 0x25, 0x90, 0x3A, 0x5E, 0x2F, 0x90, 0x9D, 0xC0, 0x03, 0xA1, 0xFF};
const unsigned char demo_certificate[]={
	0x30, 0x82, 0x01, 0x9B, 0x30, 0x82, 0x01, 0x3E, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x04, 0x3C,
	0xCB, 0xF7, 0x08, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x05,
	0x00, 0x30, 0x2B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x13, 0x4D, 0x69,
	0x6A, 0x69, 0x61, 0x20, 0x4D, 0x61, 0x6E, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x20,
	0x32, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x30, 0x20,
	0x17, 0x0D, 0x31, 0x37, 0x30, 0x38, 0x30, 0x39, 0x31, 0x37, 0x34, 0x37, 0x35, 0x30, 0x5A, 0x18,
	0x0F, 0x32, 0x30, 0x36, 0x37, 0x30, 0x37, 0x32, 0x38, 0x31, 0x37, 0x34, 0x37, 0x35, 0x30, 0x5A,
	0x30, 0x35, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x0C, 0x4D, 0x69, 0x6A,
	0x69, 0x61, 0x20, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55,
	0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13,
	0x06, 0x66, 0x74, 0x73, 0x61, 0x66, 0x65, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48,
	0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42,
	0x00, 0x04, 0xA6, 0xA6, 0x6D, 0x24, 0xFB, 0x28, 0xBC, 0xC7, 0x76, 0xA1, 0x63, 0x18, 0x18, 0xCD,
	0x09, 0xAF, 0xA3, 0x1F, 0xF8, 0xC4, 0x5F, 0x80, 0x56, 0xB4, 0xD5, 0xC9, 0x27, 0xFD, 0xFF, 0xEA,
	0x47, 0xC0, 0x36, 0x2B, 0x56, 0x06, 0x26, 0x27, 0x79, 0x26, 0xFD, 0x12, 0xA2, 0x64, 0xFC, 0xDE,
	0xC9, 0xB8, 0xC7, 0x79, 0x1B, 0xF2, 0x4B, 0xD9, 0xAD, 0x6F, 0x4C, 0x96, 0xBD, 0x5F, 0xDB, 0xCE,
	0xC7, 0x0B, 0xA3, 0x42, 0x30, 0x40, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04,
	0x14, 0x5F, 0x7D, 0x6D, 0x90, 0xE5, 0x8B, 0xF6, 0x21, 0x24, 0xEB, 0xFA, 0xFC, 0xFB, 0xC2, 0xBB,
	0x61, 0x3C, 0x78, 0xCA, 0xB0, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16,
	0x80, 0x14, 0xFD, 0xEF, 0xAB, 0x24, 0x54, 0x64, 0xBA, 0x88, 0xBD, 0x04, 0x90, 0xAF, 0xBB, 0x5B,
	0x4B, 0x07, 0x8F, 0x7B, 0x49, 0xB7, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 
	0x03, 0x02, 0x05, 0x00, 0x03, 0x49, 0x00, 0x30, 0x46, 0x02, 0x21, 0x00, 0xAD, 0x21, 0x69, 0xAB,
	0x55, 0x7A, 0xBB, 0xA4, 0x00, 0x84, 0x08, 0x57, 0x34, 0x17, 0xD6, 0x7E, 0xD7, 0x66, 0x90, 0xAE,
	0x06, 0x85, 0xE1, 0xF7, 0xE6, 0x72, 0x49, 0xB2, 0x26, 0x0B, 0x2C, 0xFC, 0x02, 0x21, 0x00, 0xFF,
	0xC3, 0xFB, 0x12, 0x5F, 0x08, 0x41, 0xAB, 0x88, 0x6C, 0x44, 0x3A, 0xAB, 0xE7, 0x4B, 0x65, 0x2F,
	0xE1, 0x70, 0x08, 0xDB, 0x2E, 0xC7, 0x71, 0x6E, 0x6F, 0xC0, 0xC1, 0x81, 0xAD, 0xD1, 0x07
	};
	#elif(DEMO_CERT_TYPE == DEMO_CERT_TYPE3)
unsigned char dev_mac_address[]={0x4D, 0x01, 0x00, 0xBE, 0xBE, 0x8C};
const unsigned char dev_cert_pri[32] = {	
	0x45, 0xFC, 0xEE, 0x88, 0x7C, 0xE3, 0x39, 0x43, 0x38, 0x70, 0x64, 0x9E, 0x65, 0xEF, 0xEE, 0xD4,
	0xFB, 0xC4, 0x1C, 0x1B, 0x9B, 0xB4, 0xEA, 0x4D, 0xF0, 0x8C, 0x0A, 0xDC, 0xCC, 0xA6, 0xE0, 0x62};
const unsigned char demo_certificate[]={
    0x30, 0x82, 0x01, 0x99, 0x30, 0x82, 0x01, 0x3E, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x04, 0x3C,
	0xCB, 0xF7, 0x10, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x05, 
	0x00, 0x30, 0x2B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x13, 0x4D, 0x69, 
	0x6A, 0x69, 0x61, 0x20, 0x4D, 0x61, 0x6E, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x20,
	0x32, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x30, 0x20,
	0x17, 0x0D, 0x31, 0x37, 0x30, 0x38, 0x30, 0x39, 0x31, 0x37, 0x34, 0x39, 0x32, 0x37, 0x5A, 0x18, 
	0x0F, 0x32, 0x30, 0x36, 0x37, 0x30, 0x37, 0x32, 0x38, 0x31, 0x37, 0x34, 0x39, 0x32, 0x37, 0x5A,
	0x30, 0x35, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x0C, 0x4D, 0x69, 0x6A, 
	0x69, 0x61, 0x20, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 
	0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 
	0x06, 0x66, 0x74, 0x73, 0x61, 0x66, 0x65, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48, 
	0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42, 
	0x00, 0x04, 0x84, 0xF3, 0xBB, 0xBC, 0xAA, 0xFC, 0x3B, 0xB6, 0x51, 0xB0, 0xDA, 0x57, 0x23, 0x76, 
	0xEA, 0xF8, 0xEC, 0xE3, 0xAF, 0x96, 0x93, 0x65, 0xAA, 0x71, 0xF5, 0x55, 0x6A, 0x3C, 0x12, 0xFA, 
	0xF0, 0x1C, 0xFA, 0x93, 0x9C, 0x80, 0x4C, 0x20, 0x3E, 0x6B, 0xC0, 0x52, 0xB0, 0x97, 0xA3, 0x56,  
	0x14, 0x44, 0x7F, 0x89, 0xF7, 0x97, 0x70, 0x46, 0xED, 0xCA, 0x9D, 0xFE, 0x27, 0x3C, 0x3B, 0x1B, 
	0x5B, 0xEB, 0xA3, 0x42, 0x30, 0x40, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04,  
	0x14, 0x08, 0x6F, 0x6C, 0xDD, 0x5F, 0xEE, 0x37, 0xE4, 0x5F, 0x2E, 0xD4, 0x7B, 0xCF, 0x66, 0xB4, 
	0xC0, 0x6F, 0xE7, 0x7B, 0xA4, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 
	0x80, 0x14, 0xFD, 0xEF, 0xAB, 0x24, 0x54, 0x64, 0xBA, 0x88, 0xBD, 0x04, 0x90, 0xAF, 0xBB, 0x5B,  
	0x4B, 0x07, 0x8F, 0x7B, 0x49, 0xB7, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 
	0x03, 0x02, 0x05, 0x00, 0x03, 0x47, 0x00, 0x30, 0x44, 0x02, 0x20, 0x0D, 0x9F, 0x21, 0xB2, 0x63,  
	0x5B, 0x03, 0x43, 0x9E, 0x9B, 0x61, 0x08, 0x70, 0x70, 0x27, 0xC6, 0x91, 0x45, 0x49, 0x7F, 0x7F, 
	0xF4, 0x1F, 0x71, 0xCC, 0x8B, 0xF6, 0x2D, 0xD0, 0xA1, 0x3A, 0xBA, 0x02, 0x20, 0x3E, 0x9F, 0x6E, 
	0xFF, 0x38, 0xEA, 0x9A, 0x72, 0xF5, 0xAF, 0x2B, 0xF2, 0x55, 0x92, 0xBF, 0xF2, 0x30, 0x38, 0x62, 
	0xE7, 0xF0, 0x99, 0xA4, 0x3A, 0x6A, 0x26, 0xF2, 0xF0, 0xF8, 0xE1, 0xCD, 0x37
	};	
	#elif(DEMO_CERT_TYPE == DEMO_CERT_TYPE4)
unsigned char dev_mac_address[]={0x4E, 0x01, 0x00, 0xBE, 0xBE, 0x8C};
const unsigned char dev_cert_pri[32] = {	
	0x6F, 0xAB, 0x89, 0x04, 0x0D, 0x16, 0x0F, 0xB7, 0x8D, 0x90, 0xCE, 0x65, 0x43, 0x76, 0x9B, 0x27, 
	0x53, 0xFF, 0x63, 0xAD, 0x18, 0x52, 0xD1, 0x64, 0xE0, 0x00, 0x87, 0x1E, 0x56, 0x84, 0x36, 0xA9};
const unsigned char demo_certificate[]={
	0x30, 0x82, 0x01, 0x9B, 0x30, 0x82, 0x01, 0x3E, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x04, 0x3C,
	0xCB, 0xF7, 0x11, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x05,
	0x00, 0x30, 0x2B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x13, 0x4D, 0x69,
	0x6A, 0x69, 0x61, 0x20, 0x4D, 0x61, 0x6E, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x20,
	0x32, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x30, 0x20, 
	0x17, 0x0D, 0x31, 0x37, 0x30, 0x38, 0x30, 0x39, 0x31, 0x37, 0x34, 0x39, 0x32, 0x38, 0x5A, 0x18, 
	0x0F, 0x32, 0x30, 0x36, 0x37, 0x30, 0x37, 0x32, 0x38, 0x31, 0x37, 0x34, 0x39, 0x32, 0x38, 0x5A, 
	0x30, 0x35, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x0C, 0x4D, 0x69, 0x6A,  
	0x69, 0x61, 0x20, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 
	0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13,  
	0x06, 0x66, 0x74, 0x73, 0x61, 0x66, 0x65, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48,
	0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42,
	0x00, 0x04, 0x3B, 0x5C, 0xDD, 0x57, 0xED, 0x5E, 0xF2, 0x1E, 0x6F, 0x92, 0xA3, 0xF4, 0x18, 0x62, 
	0xC6, 0x0E, 0x60, 0x8C, 0x48, 0x4C, 0x59, 0xF1, 0xE3, 0x66, 0xE2, 0x90, 0xAA, 0xFD, 0x22, 0xB9, 
	0xDD, 0x5D, 0x82, 0x1F, 0x70, 0x3E, 0x70, 0xEC, 0x20, 0x0C, 0x87, 0x5D, 0x45, 0x97, 0xC2, 0x24, 
	0x48, 0x76, 0xDF, 0xB5, 0xC7, 0x0B, 0x3A, 0xAD, 0x04, 0xB7, 0xC3, 0xE8, 0xA8, 0x2E, 0x17, 0x95,  
	0xFC, 0x5D, 0xA3, 0x42, 0x30, 0x40, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 
	0x14, 0x98, 0xA1, 0x1D, 0x3F, 0xEC, 0x25, 0x63, 0x88, 0x2E, 0x43, 0xA1, 0x1F, 0xC9, 0x20, 0xD7,
	0x24, 0xBF, 0x51, 0x51, 0x03, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 
	0x80, 0x14, 0xFD, 0xEF, 0xAB, 0x24, 0x54, 0x64, 0xBA, 0x88, 0xBD, 0x04, 0x90, 0xAF, 0xBB, 0x5B,
	0x4B, 0x07, 0x8F, 0x7B, 0x49, 0xB7, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04,
	0x03, 0x02, 0x05, 0x00, 0x03, 0x49, 0x00, 0x30, 0x46, 0x02, 0x21, 0x00, 0x99, 0x03, 0xD4, 0x8F, 
	0xB5, 0x7E, 0xA0, 0x1D, 0x88, 0xDD, 0x39, 0xC1, 0x31, 0x2E, 0xEB, 0x2D, 0xC6, 0xE2, 0xB6, 0x1B, 
	0x21, 0xC2, 0xE8, 0xF9, 0xFE, 0xB9, 0x3A, 0xC1, 0xCE, 0x55, 0x90, 0xD9, 0x02, 0x21, 0x00, 0xEF, 
	0xC6, 0x9C, 0xE2, 0x68, 0x48, 0xC1, 0x3F, 0x43, 0x25, 0x80, 0x6A, 0x95, 0x8C, 0x18, 0xB2, 0x3F, 
	0xF7, 0xB2, 0x0A, 0x6E, 0x6A, 0x87, 0x06, 0xE7, 0x13, 0x78, 0x2F, 0x2B, 0x37, 0xD1, 0x6D
	};	
	#elif(DEMO_CERT_TYPE == DEMO_CERT_TYPE5)
unsigned char dev_mac_address[]={0x34, 0x12, 0x00, 0xEB, 0x49, 0x7C};
const unsigned char dev_cert_pri[32] = {	
	0x89, 0x35, 0x10, 0x71, 0xDB, 0xCA, 0x86, 0x11, 0x90, 0x67, 0x13, 0x92, 0xBD, 0x2C, 0x7B, 0x46,
	0xAF, 0x17, 0xE9, 0x45, 0x52, 0xA3, 0x1F, 0x2D, 0x8C, 0xDF, 0xD6, 0x1C, 0x87, 0xCB, 0x22, 0xAA};
const unsigned char demo_certificate[]={
    0x30, 0x82, 0x01, 0x9A, 0x30, 0x82, 0x01, 0x3E, 0xA0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x04, 0x3C,  
	0xCB, 0xF7, 0x0A, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x05, 
	0x00, 0x30, 0x2B, 0x31, 0x1C, 0x30, 0x1A, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x13, 0x4D, 0x69,  
	0x6A, 0x69, 0x61, 0x20, 0x4D, 0x61, 0x6E, 0x75, 0x66, 0x61, 0x63, 0x74, 0x75, 0x72, 0x65, 0x20,  
	0x32, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x30, 0x20,
	0x17, 0x0D, 0x31, 0x37, 0x30, 0x38, 0x30, 0x39, 0x31, 0x37, 0x34, 0x38, 0x33, 0x36, 0x5A, 0x18, 
	0x0F, 0x32, 0x30, 0x36, 0x37, 0x30, 0x37, 0x32, 0x38, 0x31, 0x37, 0x34, 0x38, 0x33, 0x36, 0x5A, 
	0x30, 0x35, 0x31, 0x15, 0x30, 0x13, 0x06, 0x03, 0x55, 0x04, 0x0A, 0x13, 0x0C, 0x4D, 0x69, 0x6A, 
	0x69, 0x61, 0x20, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55,  
	0x04, 0x06, 0x13, 0x02, 0x43, 0x4E, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13,  
	0x06, 0x66, 0x74, 0x73, 0x61, 0x66, 0x65, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48,  
	0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42,  
	0x00, 0x04, 0x4E, 0x1D, 0x56, 0x55, 0x4A, 0x78, 0x56, 0x5D, 0x79, 0xC2, 0x4D, 0x6C, 0xD1, 0x7F, 
	0xEF, 0x6E, 0x93, 0xFF, 0x31, 0xC3, 0x43, 0xA0, 0x54, 0xD9, 0xF4, 0x23, 0x7A, 0xBE, 0xAC, 0x08, 
	0xD5, 0x60, 0xDA, 0x7B, 0x41, 0x48, 0x17, 0xDD, 0x84, 0xB1, 0x59, 0x37, 0x05, 0xFA, 0x56, 0x0C,  
	0x2A, 0x96, 0x8D, 0xCD, 0xD0, 0x20, 0xAA, 0xEA, 0x39, 0x72, 0xC8, 0x03, 0x27, 0xEE, 0xEB, 0x3A, 
	0xEF, 0x95, 0xA3, 0x42, 0x30, 0x40, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04, 
	0x14, 0x4D, 0x3B, 0x42, 0x17, 0xFA, 0x61, 0xBD, 0xC7, 0x72, 0x57, 0x5F, 0x09, 0xB8, 0x82, 0xF4, 
	0x2C, 0xDD, 0xBA, 0x2C, 0xEA, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 
	0x80, 0x14, 0xFD, 0xEF, 0xAB, 0x24, 0x54, 0x64, 0xBA, 0x88, 0xBD, 0x04, 0x90, 0xAF, 0xBB, 0x5B,
	0x4B, 0x07, 0x8F, 0x7B, 0x49, 0xB7, 0x30, 0x0C, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 
	0x03, 0x02, 0x05, 0x00, 0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x20, 0x0E, 0x04, 0x5B, 0x5D, 0x9C, 
	0xCB, 0xF0, 0xAE, 0xEF, 0x75, 0xF2, 0xAB, 0x9F, 0x9C, 0xF0, 0x2B, 0xF4, 0x16, 0xC4, 0x1C, 0xF0, 
	0xBA, 0x9C, 0xF9, 0x2C, 0xDA, 0x4F, 0x66, 0x37, 0x3D, 0xB0, 0x4C, 0x02, 0x21, 0x00, 0xCC, 0xFA, 
	0x39, 0xE0, 0x3B, 0x4F, 0xB6, 0xFE, 0x56, 0xB2, 0x7A, 0x5E, 0x7E, 0x65, 0x69, 0x96, 0x82, 0x84, 
	0xF2, 0xE5, 0x21, 0xA0, 0x1D, 0x4F, 0xEB, 0xA7, 0x20, 0xF3, 0xEC, 0x13, 0xE4, 0x9D
	};	
	#endif
void set_mi_mac_address(unsigned char *p_mac)
{
    memcpy(p_mac,dev_mac_address,sizeof(dev_mac_address));
}

#else
const unsigned char dev_cert_pri[32] = {0};
const unsigned char demo_certificate[413]={
	0x30,0x82,0x01,0x99,0x30,0x82,0x01,0x3E,0xA0,0x03,0x02,0x01,0x02,0x02,0x04,0x3C,
	0xCB,0xF7,0x0B,0x30,0x0C,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,0x03,0x02,0x05,
	0x00,0x30,0x2B,0x31,0x1C,0x30,0x1A,0x06,0x03,0x55,0x04,0x0A,0x13,0x13,0x4D,0x69,
	0x6A,0x69,0x61,0x20,0x4D,0x61,0x6E,0x75,0x66,0x61,0x63,0x74,0x75,0x72,0x65,0x20,
	0x32,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x43,0x4E,0x30,0x20,
	0x17,0x0D,0x31,0x37,0x30,0x38,0x30,0x39,0x31,0x37,0x34,0x38,0x35,0x38,0x5A,0x18,
	0x0F,0x32,0x30,0x36,0x37,0x30,0x37,0x32,0x38,0x31,0x37,0x34,0x38,0x35,0x38,0x5A,
	0x30,0x35,0x31,0x15,0x30,0x13,0x06,0x03,0x55,0x04,0x0A,0x13,0x0C,0x4D,0x69,0x6A,
	0x69,0x61,0x20,0x44,0x65,0x76,0x69,0x63,0x65,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,
	0x04,0x06,0x13,0x02,0x43,0x4E,0x31,0x0F,0x30,0x0D,0x06,0x03,0x55,0x04,0x0B,0x13,
	0x06,0x66,0x74,0x73,0x61,0x66,0x65,0x30,0x59,0x30,0x13,0x06,0x07,0x2A,0x86,0x48,
	0xCE,0x3D,0x02,0x01,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x03,0x01,0x07,0x03,0x42,
	0x00,0x04,0xD2,0x07,0x20,0x71,0x54,0xCC,0xB7,0x57,0xE0,0x5F,0x29,0x6F,0xF6,0xE8,
	0x4C,0xCC,0x74,0x09,0xB0,0x52,0xF7,0x20,0x5B,0x29,0x41,0x5F,0xAF,0xB5,0x66,0xFE,
	0xBB,0x5E,0xB5,0x78,0x77,0x79,0x9C,0xBB,0x79,0xBC,0x70,0x4D,0x76,0x33,0x3E,0x1E,
	0x9C,0xA9,0x2D,0x9A,0xB9,0xD6,0xF5,0x86,0x79,0x64,0x3D,0xF4,0x18,0x79,0xB4,0xC7,
	0x66,0x60,0xA3,0x42,0x30,0x40,0x30,0x1D,0x06,0x03,0x55,0x1D,0x0E,0x04,0x16,0x04,
	0x14,0x4A,0x89,0x87,0x3C,0x8D,0xF8,0x0D,0x46,0xE8,0x46,0xB8,0x09,0xBC,0x19,0x0B,
	0x17,0xF8,0x9B,0xC6,0x8F,0x30,0x1F,0x06,0x03,0x55,0x1D,0x23,0x04,0x18,0x30,0x16,
	0x80,0x14,0xFD,0xEF,0xAB,0x24,0x54,0x64,0xBA,0x88,0xBD,0x04,0x90,0xAF,0xBB,0x5B,
	0x4B,0x07,0x8F,0x7B,0x49,0xB7,0x30,0x0C,0x06,0x08,0x2A,0x86,0x48,0xCE,0x3D,0x04,
	0x03,0x02,0x05,0x00,0x03,0x47,0x00,0x30,0x44,0x02,0x20,0x39,0x68,0xCF,0x2A,0xCF,
	0x2E,0xD3,0x6C,0x04,0x91,0x54,0xBA,0x1D,0xBE,0x5E,0xF1,0x41,0x80,0x89,0xB3,0x6A,
	0xBD,0xF5,0xFB,0xA7,0xD3,0x45,0x4F,0x26,0xCB,0x78,0xF0,0x02,0x20,0x0E,0xAA,0x73,
	0x80,0x48,0xB8,0xC2,0xEE,0xE5,0x63,0xBD,0xDE,0x01,0xD5,0x1E,0x85,0xE3,0x4B,0xCC,
	0x89,0x81,0xA1,0x38,0x89,0x2C,0x2A,0x12,0x1B,0x23,0x59,0x1B,0x59
};
#endif


int mi_crypto_init(void)
{
    int errno = 0;

#if (HAVE_MSC==0)
    micro_ecc_init(NULL);

#if (MI_MESH_ENABLED)

    uint8_t key[16];
//    uint8_t enc_sk[32+4];
    keygen(key);
/*
    errno = mi_mesh_otp_read(OTP_DEV_CERT_PRI, enc_sk, sizeof(enc_sk));
    if (errno != sizeof(enc_sk))
        return -1;

    errno = mi_crypto_ccm_decrypt(key, key+8, 8, NULL, 0,
                          enc_sk, 32, dev_crt_sk, enc_sk+32, 4);
*/
	#if (MI_CER_MODE == DEMO_CER_MODE)
    memcpy(dev_crt_sk,dev_cert_pri,sizeof(dev_cert_pri)); 
	#elif (MI_CER_MODE == FLASH_CER_MODE)
	// read from the flash 
	mible_nvm_read(dev_crt_sk,sizeof(dev_crt_sk),DEV_SK_FLASH_ADR);
	#endif
	#if SOFT_CRYPTO_ENABLE
	return ECC_SUC_RET;
	#else
    MI_ERR_CHECK(errno);
    return errno;
	#endif
#endif
#endif
    return 0;
}

int mi_crypto_ecc_keypair_gen(ecc_curve_t curve, ecc256_pk_t pk)
{
    if (pk == 0)
        return -1;

#if (HAVE_MSC)
    return msc_ecc_keypair_gen(&curve, pk);
#else
	#if SOFT_CRYPTO_ENABLE
	tn_p256_keypair (dev_sk, pk, pk+32);
    return ECC_SUC_RET;
	#else
    int ret = micro_ecc_keypair_gen(&curve, dev_sk, pk);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : ret);
	#endif
#endif
}

int mi_crypto_ecc_pubkey_compute(ecc_curve_t curve, const ecc256_sk_t sk, ecc256_pk_t pk)
{
#if (HAVE_MSC)
    return -1;
#else
    if (sk == 0 || pk == 0)
        return -1;
	#if SOFT_CRYPTO_ENABLE
	tn_p256_keypair_sk((unsigned char *)sk,pk,pk+32);
	return ECC_SUC_RET;
	#else
    int ret = micro_ecc_public_key_compute(&curve, sk, pk);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : ret);
	#endif
#endif
}

int mi_crypto_ecc_shared_secret_compute(ecc_curve_t curve, const ecc256_pk_t pk, ecc256_ss_t ss)
{
    if (pk == 0 || ss == 0)
        return -1;

#if (HAVE_MSC)
    return msc_ecdh(&curve, pk, ss);
#else
	#if SOFT_CRYPTO_ENABLE
	tn_p256_dhkey (ss, dev_sk, (unsigned char *)pk, (unsigned char *)(pk+32));
	return ECC_SUC_RET;
	#else
    int ret = micro_ecc_shared_secret_compute(&curve, dev_sk, pk, ss);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : ret);
	#endif
#endif
}

int mi_crypto_ecc_sign(ecc_curve_t curve, const uint8_t *p_hash, uint8_t *p_sig)
{
    if (p_hash == 0 || p_sig == 0)
        return -1;

#if (HAVE_MSC)
    return msc_ecdsa_sign(&curve, p_hash, p_sig);
#else
	#if SOFT_CRYPTO_ENABLE
	const struct uECC_Curve_t * curve_t = uECC_secp256r1();
	uECC_sign((const uint8_t *)dev_crt_sk, (const uint8_t *)p_hash,
	      32, p_sig, curve_t);
	return ECC_SUC_RET;
	#else
    int ret = micro_ecc_sign(&curve, (const uint8_t *)dev_crt_sk, (const uint8_t *)p_hash, p_sig);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : PT_EXITED);
	#endif
#endif
}

int mi_crypto_ecc_verify(ecc_curve_t curve, const ecc256_pk_t pk, const uint8_t *p_hash, const uint8_t *p_sig)
{
    if (pk == 0 || p_hash == 0 || p_sig == 0)
        return -1;

#if (HAVE_MSC)
    return msc_ecdsa_verify(&curve, pk, p_hash, p_sig);
#else
	#if SOFT_CRYPTO_ENABLE
	const struct uECC_Curve_t * curve_t = uECC_secp256r1();
	int ret = uECC_verify((const uint8_t *)pk,(const uint8_t *)p_hash,
				32,(const uint8_t *)p_sig,curve_t);
	if(ret) return ECC_SUC_RET;
	else return PT_EXITED;
	#else
    int ret = micro_ecc_verify(&curve, (const uint8_t *)pk, (const uint8_t *)p_hash, (const uint8_t *)p_sig);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : PT_EXITED);
	#endif
#endif
}
void test_ecdsa_sig_verify1()
{
#if 0 // just test for the caculate funtion time
	static u32 A_debug_sig_key_make0=0;
	static u32 A_debug_sig_key_make1=0;
	static u32 A_debug_sig_key_make2=0;
	
	static u32 A_debug_sig_sign0=0;
	static u32 A_debug_sig_sign1=0;
	static u32 A_debug_sig_sign2=0;
	
	static u32 A_debug_sig_ver0=0;
	static u32 A_debug_sig_ver1=0;
	static u32 A_debug_sig_ver2=0;

	micro_ecc_init(NULL);
	unsigned char dev_dsk[] = { 0x52,0x9a,0xa0,0x67,0x0d,0x72,0xcd,0x64, 0x97,0x50,0x2e,0xd4,0x73,0x50,0x2b,0x03,
						0x7e,0x88,0x03,0xb5,0xc6,0x08,0x29,0xa5, 0xa3,0xca,0xa2,0x19,0x50,0x55,0x30,0xba};
	unsigned char dev_dpk[] = { 0xf4,0x65,0xe4,0x3f,0xf2,0x3d,0x3f,0x1b, 0x9d,0xc7,0xdf,0xc0,0x4d,0xa8,0x75,0x81,
						0x84,0xdb,0xc9,0x66,0x20,0x47,0x96,0xec, 0xcf,0x0d,0x6c,0xf5,0xe1,0x65,0x00,0xcc,
						0x02,0x01,0xd0,0x48,0xbc,0xbb,0xd8,0x99, 0xee,0xef,0xc4,0x24,0x16,0x4e,0x33,0xc2,
						0x01,0xc2,0xb0,0x10,0xca,0x6b,0x4d,0x43, 0xa8,0xa1,0x55,0xca,0xd8,0xec,0xb2,0x79};
	unsigned char dev_dpk_test[64];


	unsigned char hash_dat[32]={0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7, 
								0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
	unsigned char sign_dat[64];
	A_debug_sig_key_make0=clock_time();
	mi_crypto_ecc_keypair_gen(P256R1,dev_dpk_test);
	A_debug_sig_key_make1=clock_time();
	A_debug_sig_key_make2 = (A_debug_sig_key_make1 - A_debug_sig_key_make0)/32;

	A_debug_sig_sign0 = clock_time();
	mi_crypto_ecc_sign(P256R1,hash_dat,sign_dat);
	A_debug_sig_sign1 = clock_time();
	A_debug_sig_sign2 = (A_debug_sig_sign1 - A_debug_sig_sign0)/32;

	A_debug_sig_ver0 = clock_time();
	mi_crypto_ecc_verify(P256R1,dev_dpk,hash_dat,sign_dat);
	A_debug_sig_ver1 = clock_time();
	A_debug_sig_ver2 = (A_debug_sig_ver1 -A_debug_sig_ver0 )/32;
#else
	// test for ecc part 
	/*
	micro_ecc_init(NULL);
	static u32 A_debug_sk_calc = 0;
	int ret;
	unsigned char x0[64],y0[64],k0[32],k1[32];

	unsigned char s0[32] = {
		0x20,0xb0,0x03,0xd2,0xf2,0x97,0xbe,0x2c,0x5e,0x2c,0x83,0xa7,0xe9,0xf9,0xa5,0xb9,
		0xef,0xf4,0x91,0x11,0xac,0xf4,0xfd,0xdb,0xcc,0x03,0x01,0x48,0x0e,0x35,0x9d,0xe6};

	unsigned char s1[32] = {
		0x55,0x18,0x8b,0x3d,0x32,0xf6,0xbb,0x9a,0x90,0x0a,0xfc,0xfb,0xee,0xd4,0xe7,0x2a,
		0x59,0xcb,0x9a,0xc2,0xf1,0x9d,0x7c,0xfb,0x6b,0x4f,0xdd,0x49,0xf4,0x7f,0xc5,0xfd};
	micro_ecc_keypair_gen(NULL, s0, x0);
	micro_ecc_keypair_gen(NULL, s1, y0);
	micro_ecc_shared_secret_compute(NULL, s0, y0, k0);
	micro_ecc_shared_secret_compute(NULL, s1, x0, k1);
	ret = memcmp (k0, k1, 16);
	if(ret == 0){
		A_debug_sk_calc++;
	}else{
		A_debug_sk_calc=0x55;
	}		
	*/

	// test for the part of the 
	/*
	micro_ecc_init(NULL);
	u8 ecdsa_sk[32];
	u8 ecdsa_pk[64];
	micro_ecc_keypair_gen(NULL, ecdsa_sk, ecdsa_pk);
	static u32 A_debug_sk_calc = 0;
	unsigned char hash_dat[32]={0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7, 
								0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
	unsigned char sign_dat[64];
	micro_ecc_sign(NULL, ecdsa_sk, hash_dat, sign_dat);
	if(micro_ecc_verify(NULL, ecdsa_pk, hash_dat, sign_dat)==0){
		A_debug_sk_calc =2;
	}else{
		A_debug_sk_calc =0x55;
	}
	*/
#endif
}


int mi_crypto_get_crt_len(uint16_t *p_dev_len, uint16_t *p_manu_len, uint16_t *p_root_len)
{
#if (HAVE_MSC)
    return msc_get_cert_len(p_dev_len, p_manu_len, p_root_len);
#elif defined(MI_MESH_ENABLED)
    #if (MI_CER_MODE == DEMO_CER_MODE)
    p_dev_len  ? *p_dev_len  = sizeof(demo_certificate):0;//mi_mesh_otp_read(OTP_DEV_CERT, NULL, 0) : 0;
    #elif (MI_CER_MODE == FLASH_CER_MODE)
	p_dev_len  ? *p_dev_len =  mi_mesh_otp_read(OTP_DEV_CERT, NULL, 0) : 0;
    #endif
    p_manu_len ? *p_manu_len = mi_mesh_otp_read(OTP_MANU_CERT, NULL, 0) : 0;
    p_root_len ? *p_root_len = mi_mesh_otp_read(OTP_ROOT_CERT, NULL, 0) : 0;
    return PT_ENDED;
#else
    return PT_ENDED;
#endif
}

int mi_crypto_get_crt_der(mi_cert_t type, uint8_t *p_der, uint16_t der_len)
{
    if (p_der == NULL)
        return -1;

#if (HAVE_MSC)
    msc_cmd_t cmd = MSC_NOP;
    switch(type) {
    case MI_DEV_CERT:
        cmd = MSC_DEV_CERT;
        break;
    case MI_MANU_CERT:
        cmd = MSC_MANU_CERT;
        break;
    case MI_ROOT_CERT:
        cmd = MSC_ROOT_CERT;
        break;
    }
    return msc_get_cert_der(cmd, p_der, der_len);
#elif defined(MI_MESH_ENABLED)
    uint16_t item;
    switch(type) {
    case MI_DEV_CERT:
        item = OTP_DEV_CERT;
		// certiry memcpy
		#if (MI_CER_MODE == DEMO_CER_MODE)
		memcpy(p_der,demo_certificate,der_len);
		#elif(MI_CER_MODE == FLASH_CER_MODE)
		#endif
        break;
    case MI_MANU_CERT:
        item = OTP_MANU_CERT;
        break;
    case MI_ROOT_CERT:
        item = OTP_ROOT_CERT;
        break;
    }
    mi_mesh_otp_read(item, p_der, der_len);
    return PT_ENDED;
#else
    return PT_ENDED;
#endif
}

int mi_crypto_crt_parse_der(const unsigned char *crt, size_t crt_sz,
        const msc_crt_time *now, msc_crt_t *msc_crt)
{
    return mbedtls_crt_parse_der(crt, crt_sz, now, msc_crt);
}


int mi_crypto_hash_init(void * p_ctx);

int mi_crypto_hash_update(void *p_ctx, uint8_t *p_data, uint16_t data_len);

int mi_crypto_hash_finish(void *p_ctx, uint8_t *p_digest, uint8_t *p_digest_len);

int mi_crypto_sha256(uint8_t *p_in, uint32_t in_len, uint8_t *p_out)
{
    mbedtls_sha256(p_in, in_len, p_out, 0);
    return 0;
}

int mi_crypto_hkdf_sha256(const uint8_t *key, uint8_t key_len, const uint8_t *salt, uint8_t salt_len,
                        const uint8_t *info, uint16_t info_len, uint8_t *out, uint8_t out_len)
{
    return mbedtls_sha256_hkdf(key, key_len, salt, salt_len, info, info_len, out, out_len);
}

int mi_crypto_hmac_init(void *p_ctx, uint8_t *k, uint8_t key_len);

int mi_crypto_hmac_update(void *p_ctx, uint8_t *p_data, uint16_t data_len);

int mi_crypto_hmac_finish(void *p_ctx, uint8_t *p_digest, uint8_t *p_digest_len);

int mi_crypto_hmac_sha256(const uint8_t *k, uint32_t key_len, 
    const uint8_t *p_in, uint32_t in_len, uint8_t *p_out)
{
    return mbedtls_md_hmac(k, key_len, p_in, in_len, p_out);
}


int mi_crypto_ccm_encrypt(const uint8_t *key,
                         const uint8_t *iv, size_t iv_len,
                         const uint8_t *add, size_t add_len,
                         const uint8_t *in, size_t in_len,
                         uint8_t *out,
                         uint8_t *tag, size_t tag_len )
{
    int ret = aes_ccm_encrypt_and_tag(key, iv, iv_len, add, add_len,
                                    in, in_len, out, tag, tag_len );
    return ret;
}

int mi_crypto_ccm_decrypt( const uint8_t *key,
                        const uint8_t *iv, size_t iv_len,
                        const uint8_t *add, size_t add_len,
                        const uint8_t *in, size_t in_len,
                        uint8_t *out,
                        const uint8_t *tag, size_t tag_len )
{
    int ret = aes_ccm_auth_decrypt(key, iv, iv_len, add, add_len,
                                    in, in_len, out, tag, tag_len );
    return ret;
}

int mi_crypto_record_write(uint8_t record_id, const uint8_t *p_data, uint8_t len)
{
    if (p_data == NULL)
        return -1;
#if (HAVE_MSC)
    return msc_record_write(record_id, p_data, len);
#else
    uint8_t key[16] = {0};
    uint8_t tmp[len+4];
    int ret;
    keygen(key);
    ret = mi_crypto_ccm_encrypt(key, key + 8, 8, NULL, 0, p_data, len, tmp, tmp + len, 4);
    MI_ERR_CHECK(ret);
    ret = mible_record_create(CRYPTO_REC_ID_BASE + record_id, len + 4);
    MI_ERR_CHECK(ret);
    ret = mible_record_write(CRYPTO_REC_ID_BASE + record_id, tmp, len + 4);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : PT_EXITED);
#endif

}

int mi_crypto_record_read(uint8_t record_id, uint8_t *p_data, uint8_t len)
{
    if (p_data == NULL)
        return -1;

#if (HAVE_MSC)
    return msc_record_read(record_id, p_data, len);
#else
    uint8_t key[16] = {0};
    uint8_t tmp[len+4];
    int ret = mible_record_read(CRYPTO_REC_ID_BASE + record_id, tmp, len + 4);
    MI_ERR_CHECK(ret);
    keygen(key);
    ret = mi_crypto_ccm_decrypt(key, key+8, 8, NULL, 0, tmp, len, p_data, tmp + len, 4);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : PT_EXITED);
#endif

}

int mi_crypto_record_delete(uint8_t record_id)
{
#if (HAVE_MSC)
    return msc_record_delete(record_id);
#else
    int ret = mible_record_delete(CRYPTO_REC_ID_BASE + record_id);
    MI_ERR_CHECK(ret);
    return (ret == MI_SUCCESS ? PT_ENDED : PT_EXITED);
#endif
}
#endif
#endif
