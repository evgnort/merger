	vmovups	(%rcx), %ymm1	# MEM[(__m256_u * {ref-all})B_112], MEM[(__m256_u * {ref-all})B_112]
	vmovups	32(%rcx), %ymm0	# MEM[(__m256_u * {ref-all})B_112 + 32B], MEM[(__m256_u * {ref-all})B_112 + 32B]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1320:   return __extension__ (__m256){ __A, __A, __A, __A,
	vbroadcastss	(%rdx), %ymm3	# MEM[(const matrixtype_t *)A_113], tmp153
	vbroadcastss	4(%rdx), %ymm2	# MEM[(const matrixtype_t *)A_113 + 4B], tmp154
# /usr/lib/gcc/x86_64-linux-gnu/11/include/fmaintrin.h:65:   return (__m256)__builtin_ia32_vfmaddps256 ((__v8sf)__A, (__v8sf)__B,
	vfmadd231ps	%ymm1, %ymm3, %ymm14	# MEM[(__m256_u * {ref-all})B_112], tmp153, c00
	vfmadd231ps	%ymm0, %ymm3, %ymm13	# MEM[(__m256_u * {ref-all})B_112 + 32B], tmp153, c01
	vfmadd231ps	%ymm1, %ymm2, %ymm12	# MEM[(__m256_u * {ref-all})B_112], tmp154, c10
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1320:   return __extension__ (__m256){ __A, __A, __A, __A,
	vbroadcastss	8(%rdx), %ymm3	# MEM[(const matrixtype_t *)A_113 + 8B], tmp159
# /usr/lib/gcc/x86_64-linux-gnu/11/include/fmaintrin.h:65:   return (__m256)__builtin_ia32_vfmaddps256 ((__v8sf)__A, (__v8sf)__B,
	vfmadd231ps	%ymm0, %ymm2, %ymm11	# MEM[(__m256_u * {ref-all})B_112 + 32B], tmp154, c11
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1320:   return __extension__ (__m256){ __A, __A, __A, __A,
	vbroadcastss	12(%rdx), %ymm2	# MEM[(const matrixtype_t *)A_113 + 12B], tmp160
# /usr/lib/gcc/x86_64-linux-gnu/11/include/fmaintrin.h:65:   return (__m256)__builtin_ia32_vfmaddps256 ((__v8sf)__A, (__v8sf)__B,
	vfmadd231ps	%ymm1, %ymm3, %ymm10	# MEM[(__m256_u * {ref-all})B_112], tmp159, c20
	vfmadd231ps	%ymm0, %ymm3, %ymm9	# MEM[(__m256_u * {ref-all})B_112 + 32B], tmp159, c21
	vfmadd231ps	%ymm1, %ymm2, %ymm8	# MEM[(__m256_u * {ref-all})B_112], tmp160, c30
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1320:   return __extension__ (__m256){ __A, __A, __A, __A,
	vbroadcastss	16(%rdx), %ymm3	# MEM[(const matrixtype_t *)A_113 + 16B], tmp165
# /usr/lib/gcc/x86_64-linux-gnu/11/include/fmaintrin.h:65:   return (__m256)__builtin_ia32_vfmaddps256 ((__v8sf)__A, (__v8sf)__B,
	vfmadd231ps	%ymm0, %ymm2, %ymm7	# MEM[(__m256_u * {ref-all})B_112 + 32B], tmp160, c31
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1320:   return __extension__ (__m256){ __A, __A, __A, __A,
	vbroadcastss	20(%rdx), %ymm2	# MEM[(const matrixtype_t *)A_113 + 20B], tmp166
# gemm.c:81:       B += MICROCORE_WIDTH * ITEMS_PER_REGISTRY; 
	addq	$64, %rcx	#, B
# /usr/lib/gcc/x86_64-linux-gnu/11/include/fmaintrin.h:65:   return (__m256)__builtin_ia32_vfmaddps256 ((__v8sf)__A, (__v8sf)__B,
	vfmadd231ps	%ymm1, %ymm3, %ymm6	# MEM[(__m256_u * {ref-all})B_112], tmp165, c40
	vfmadd231ps	%ymm0, %ymm3, %ymm5	# MEM[(__m256_u * {ref-all})B_112 + 32B], tmp165, c41
	vfmadd231ps	%ymm1, %ymm2, %ymm4	# MEM[(__m256_u * {ref-all})B_112], tmp166, c50
	vfmadd231ps	%ymm0, %ymm2, %ymm15	# MEM[(__m256_u * {ref-all})B_112 + 32B], tmp166, c51
# gemm.c:92:       A += MICROCORE_HEIGHT;
	addq	$24, %rdx	#, A