# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	movq	80(%rdx), %rsi	# dstate_p_1006->cur_chain_ref, dstate_p_1006->cur_chain_ref
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	andl	$15, %ecx	#, dnum
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movl	(%rsi,%rcx,4), %ecx	# *_1015, *_1015
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1073:   return (__m256i) __builtin_ia32_permdi256 ((__v4di)__X, __M);
	vpermq	$57, %ymm1, %ymm1	#, _753, tmp1390
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	leaq	(%rax,%rcx,4), %rcx	#, _1020
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movq	%rcx, 72(%rdx)	# _1020, dstate_p_1006->cur_data_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:54:   __builtin_prefetch (__P, (__I & 0x4) >> 2, __I & 0x3);
	prefetcht2	(%rcx)	# _1020
# pipeline_avx2.c:950:    /*2*/    FProcessState * restrict dstate_p = (FProcessState *)PART_64_256(dstates_lo,0); // (3)p0 (MOVQ)
	vmovq	%xmm1, %rdx	# tmp1399, dstate_p
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmiintrin.h:106:   return __builtin_ia32_tzcnt_u32 (__X);
	xorl	%ecx, %ecx	# tmp1402
	tzcntl	68(%rdx), %ecx	# dstate_p_1027->items_mask, tmp1402
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	movq	80(%rdx), %rsi	# dstate_p_1027->cur_chain_ref, dstate_p_1027->cur_chain_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1073:   return (__m256i) __builtin_ia32_permdi256 ((__v4di)__X, __M);
	vpermq	$57, %ymm1, %ymm1	#, tmp1390, tmp1400
	vpermq	$57, %ymm2, %ymm7	#, tmp1373, _1115
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	andl	$15, %ecx	#, dnum
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movl	(%rsi,%rcx,4), %ecx	# *_1036, *_1036
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1098:   return (__m128i) __builtin_ia32_extract128i256 ((__v4di)__X, __M);
	vextracti128	$0x1, %ymm0, %xmm2	# MEM[(const __m256i_u * {ref-all})_145], tmp1433
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	leaq	(%rax,%rcx,4), %rcx	#, _1041
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movq	%rcx, 72(%rdx)	# _1041, dstate_p_1027->cur_data_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:54:   __builtin_prefetch (__P, (__I & 0x4) >> 2, __I & 0x3);
	prefetcht2	(%rcx)	# _1041
# pipeline_avx2.c:950:    /*2*/    FProcessState * restrict dstate_p = (FProcessState *)PART_64_256(dstates_lo,0); // (3)p0 (MOVQ)
	vmovq	%xmm1, %rdx	# tmp1409, dstate_p
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmiintrin.h:106:   return __builtin_ia32_tzcnt_u32 (__X);
	xorl	%ecx, %ecx	# tmp1412
	tzcntl	68(%rdx), %ecx	# dstate_p_1048->items_mask, tmp1412
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	movq	80(%rdx), %rsi	# dstate_p_1048->cur_chain_ref, dstate_p_1048->cur_chain_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1073:   return (__m256i) __builtin_ia32_permdi256 ((__v4di)__X, __M);
	vpermq	$57, %ymm1, %ymm1	#, tmp1400, tmp1410
	vpermq	$57, %ymm1, %ymm8	#, tmp1410, _1070
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	andl	$15, %ecx	#, dnum
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movl	(%rsi,%rcx,4), %ecx	# *_1057, *_1057
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:519:   return (__m256i) __builtin_ia32_pmovzxdq256 ((__v4si)__X);
	vpmovzxdq	%xmm2, %ymm2	# tmp1433, _766
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	leaq	(%rax,%rcx,4), %rcx	#, _1062
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movq	%rcx, 72(%rdx)	# _1062, dstate_p_1048->cur_data_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:54:   __builtin_prefetch (__P, (__I & 0x4) >> 2, __I & 0x3);
	prefetcht2	(%rcx)	# _1062
# pipeline_avx2.c:950:    /*2*/    FProcessState * restrict dstate_p = (FProcessState *)PART_64_256(dstates_lo,0); // (3)p0 (MOVQ)
	vmovq	%xmm1, %rdx	# tmp1419, dstate_p
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmiintrin.h:106:   return __builtin_ia32_tzcnt_u32 (__X);
	xorl	%ecx, %ecx	# tmp1422
	tzcntl	68(%rdx), %ecx	# dstate_p_1069->items_mask, tmp1422
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	movq	80(%rdx), %rsi	# dstate_p_1069->cur_chain_ref, dstate_p_1069->cur_chain_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1098:   return (__m128i) __builtin_ia32_extract128i256 ((__v4di)__X, __M);
	vextracti128	$0x1, %ymm3, %xmm1	# MEM[(const __m256i_u * {ref-all})_124], tmp1429
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:519:   return (__m256i) __builtin_ia32_pmovzxdq256 ((__v4si)__X);
	vpmovzxdq	%xmm1, %ymm1	# tmp1429, _773
# pipeline_avx2.c:953:             uint32_t ccr = dstate_p->cur_chain_ref[dnum]; // (4)p23 (MOV) -> (4)p23 (MOV))
	andl	$15, %ecx	#, dnum
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movl	(%rsi,%rcx,4), %ecx	# *_1078, *_1078
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	leaq	(%rax,%rcx,4), %rcx	#, _1083
# pipeline_avx2.c:954:    /*2*/    dstate_p->cur_data_ref = (char *)&ht->data[ccr]; // ((4)p23 (MOV) -> (1)p15 (LEA)
	movq	%rcx, 72(%rdx)	# _1083, dstate_p_1069->cur_data_ref
# pipeline_avx2.c:963: /*1*/       FProcessState * restrict hstate_p = (FProcessState *)PART_64_256(hstates_hi,0); // (3)p0 (MOVQ)
	vmovq	%xmm1, %rdx	# tmp1440, hstate_p
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:54:   __builtin_prefetch (__P, (__I & 0x4) >> 2, __I & 0x3);
	movq	88(%rdx), %rdx	# hstate_p_514->next_chain_ref, hstate_p_514->next_chain_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:54:   __builtin_prefetch (__P, (__I & 0x4) >> 2, __I & 0x3);
	prefetcht2	(%rcx)	# _1083